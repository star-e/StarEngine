// Copyright (C) 2019-2020 star.engine at outlook dot com
//
// This file is part of StarEngine
//
// StarEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// StarEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with StarEngine.  If not, see <https://www.gnu.org/licenses/>.

#include "SRenderGraphFactory.h"
#include <StarCompiler/Graphics/SRenderFormatNames.h>
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>
#include <StarCompiler/RenderGraph/SRenderGraphUtils.h>
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <Star/Graphics/SRenderFormatUtils.h>
#include <StarCompiler/ShaderWorks/SShaderCompiler.h>
#include <Star/Graphics/SRenderGraphReflection.h>
#include <StarCompiler/ShaderGraph/SShaderModules.h>
#include <Star/Graphics/SRenderUtils.h>

namespace Star {

namespace Graphics {

namespace Render {

void RenderSolutionFactory::addPipeline(GraphicsRenderNodeGraph&& graph) {
    auto name = graph.mName;
    mGraphOrder.emplace_back(name);
    auto res = mNodeGraphs.emplace(std::move(name), std::move(graph));
    if (!res.second) {
        throw std::invalid_argument("pipeline already exists" + res.first->first);
    }
}

void RenderSolutionFactory::validateGraphs() const {
    // validate framebuffer
    for (const auto& [name, graph] : mNodeGraphs) {
        graph.validate();
        auto sz = num_vertices(graph.mNodeGraph);
        // validate render node binding
        for (size_t k = 0; k != sz; ++k) {
            auto nodeID = k;
            const auto& node = graph.mNodeGraph[nodeID];

            // validate color space
            for (size_t k = 0; k != sz; ++k) {
                auto nodeID = k;
                const auto& node = graph.mNodeGraph[nodeID];

                auto validateColorSpace = [&](const RenderValue& v) {
                    const auto& rt = at(graph.mRenderTargets, v.mName);
                    visit(overload(
                        [](Linear_ dst, Linear_) {
                             // no conversion needed
                        },
                        [](Linear_ dst, Device_) {
                            // convert srgb to linear
                        },
                        [](Device_ dst, Device_) {
                            // no conversion needed
                        },
                        [&](Device_ dst, Linear_) {
                            std::string line = "cannot automatic convert linear space to device space, node: " +
                                std::string(node.mName) + ", rt: " + std::string(v.mName);
                            if (mConfig.mStrictLightingColorSpace) {
                                throw std::invalid_argument(line);
                            } else {
                                CONSOLE_WARNING();
                                std::cout << line << std::endl;
                            }
                        }
                    ), node.mColorSpace, rt.mColorSpace);
                };

                for (const auto& output : node.mOutputs) {
                    validateColorSpace(output);
                }

                // valid input framebuffers
                for (const auto& input : node.mInputs) {
                    validateColorSpace(input);
                }
            }    
        }
    }
}

void RenderSolutionFactory::buildShaderGroup(Shader::ShaderGroups& shaderWorks) const {
    using namespace Shader;

    validateGraphs();
    auto& bundle = shaderWorks.mSolutions.try_emplace(mName).first->second;

    for (auto& [graphName, graph] : mNodeGraphs) {
        auto& pipeline = bundle.try_emplace(graph.mName,
            ShaderGroups::PassGroup{}).first->second;

        auto* pParent = &pipeline[UpdateEnum::PerFrame].try_emplace(
            graph.mName, ShaderGroup{ graph.mName, (size_t)-1, PerFrame }).first->second;

        for (const auto& nodeID : graph.mNodeSorted) {
            const auto& node = graph.mNodeGraph[nodeID];
            if (nodeID == 0)
                continue;

            auto* pChild = &pipeline[UpdateEnum::PerPass].try_emplace(
                node.mName, ShaderGroup{ node.mName, nodeID, PerPass, pParent, true } ).first->second;
            pParent->mGroups.try_emplace(node.mName, pChild);
        }
    }
}

void RenderSolutionFactory::updateRenderGraph(const Shader::ShaderModules& modules,
    const Shader::ShaderGroups& shaderWorks
) {
    mShaderGroups = &shaderWorks;

    for (auto& [bundleName, bundle] : shaderWorks.mSolutions) {
        for (auto& [pipelineName, pipeline] : bundle) {
            auto& renderGraph = at(mNodeGraphs, pipelineName);
            for (auto& [name, group] : pipeline[PerPass]) {
                auto renderNodeID = renderGraph.mNodeIndex.at(name);
                auto& renderNode = renderGraph.mNodeGraph[renderNodeID];
                renderNode.mRootSignature = group.generateRootSignature();
                
                for (const auto& [nameProgram, program] : group.mPrograms) {
                    for (const auto& [type, stage] : program.first->mShaders) {
                        for (const auto& usage : stage.mGraph.mAttributeUsages) {
                            const auto& attr = at(modules.mAttributes, get_key(usage));

                            bool bTex = true;
                            visit(overload(
                                [&](Texture1D_) {},
                                [&](Texture1DArray_) {},
                                [&](Texture2D_) {},
                                [&](Texture2DArray_) {},
                                [&](Texture2DMS_) {},
                                [&](Texture2DMSArray_) {},
                                [&](Texture3D_) {},
                                [&](TextureCube_) {},
                                [&](TextureCubeArray_) {},
                                [&](auto) {
                                    bTex = false;
                                }
                            ), attr.mType);
                            if (!bTex)
                                continue;

                            auto texView = getTextureView(attr);
                            auto key = std::pair{ attr.mName, ResourceDataView{ texView } };
                            auto iter = renderNode.mInputs.find(key);
                            if (iter != renderNode.mInputs.end()) {
                                auto& v = renderGraph.mViewStates.at(key);
                                for (auto& state : v.mStates) {
                                    if (state.mNodeID == renderNodeID) {
                                        if (std::holds_alternative<DepthRead_>(state.mRenderTargetState.mState) ||
                                            std::holds_alternative<ShaderResource_>(state.mRenderTargetState.mState))
                                        {
                                            if (std::holds_alternative<PS_>(type)) {
                                                state.mRenderTargetState.mPixelShaderResource = true;
                                            } else {
                                                state.mRenderTargetState.mNonPixelShaderResource = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            renderGraph.buildRenderStatePaths2();
            renderGraph.buildResourceViews();
        }
    }
}

void RenderSolutionFactory::addContentOrdered(const UnorderedRenderQueue& content,
    std::string_view pipelineName, std::string_view passName,
    RenderSolution& renderWorks
) const {
    auto pipelineID = at(renderWorks.mPipelineIndex, pipelineName);
    auto& pipeline = renderWorks.mPipelines.at(pipelineID);
    auto passID = at(pipeline.mSubpassIndex, passName);
    auto& pass = pipeline.mPasses.at(passID.mPassID);
    auto& subpass = pass.mSubpasses.at(passID.mSubpassID);
    subpass.mOrderedRenderQueue.emplace_back(content);
}

void RenderSolutionFactory::collectFramebuffers(
    OrderedNameMap<RenderTargetResource>& bbs,
    OrderedNameMap<RenderTargetResource>& rts
) const {
    for (const auto& [graphName, graph] : mNodeGraphs) {
        auto sz = num_vertices(graph.mNodeGraph);

        for (size_t k = 0; k != sz; ++k) {
            const auto& node = graph.mNodeGraph[k];
            for (const auto& output : node.mOutputs) {
                const auto& fb = at(graph.mRenderTargets, output.mName);
                if (isBackBuffer(fb)) {
                    auto res = bbs.emplace(fb);
                    if (!res.second) {
                        if (*(res.first) != fb) {
                            throw std::invalid_argument("back buffer inconsistent");
                        }
                    }
                } else {
                    auto res = rts.emplace(fb);
                    if (!res.second) {
                        if (*(res.first) != fb) {
                            throw std::invalid_argument("render target inconsistent");
                        }
                    }
                }
            }
            for (const auto& input : node.mInputs) {
                const auto& fb = at(graph.mRenderTargets, input.mName);
                if (isBackBuffer(fb)) {
                    auto res = bbs.emplace(fb);
                    if (!res.second) {
                        if (*(res.first) != fb) {
                            throw std::invalid_argument("render target inconsistent");
                        }
                    }
                } else {
                    auto res = rts.emplace(fb);
                    if (!res.second) {
                        if (*(res.first) != fb) {
                            throw std::invalid_argument("render target inconsistent");
                        }
                    }
                }
            }
        }
    }
}

void RenderSolutionFactory::outputFramebuffers(const OrderedNameMap<RenderTargetResource>& framebuffers) const {
    std::cout << "framebuffers: " << std::endl;
    for (const auto& fb : framebuffers) {
        {
            CONSOLE_COLOR(Cyan);
            std::cout << fb.mName;
        }
        std::cout << ": " << getName(fb.mResource.mFormat);
        visit(overload(
            [](Device_) {
                std::cout << " <Device>";
            },
            [](auto) {}
        ), fb.mColorSpace);
        std::cout << std::endl;
    }
}

void RenderSolutionFactory::buildFramebuffers(
    const OrderedNameMap<RenderTargetResource>& bbs,
    const OrderedNameMap<RenderTargetResource>& rts,
    RenderSolution& rw,
    std::map<std::string, uint32_t>& rtIndex
) const {
    Expects(rw.mFramebuffers.empty());
    Expects(rtIndex.empty());

    if (bbs.size() != 1) {
        throw std::runtime_error("back buffer size is not 1");
    }

    for (const auto& f : bbs) {
        for (int i = 0; i != mBackBufferCount; ++i) {
            Expects(std::holds_alternative<Resource2D>(f.mResource.mDimension));
            const auto& tex = std::get<Resource2D>(f.mResource.mDimension);

            rw.mFramebuffers.emplace_back(
                Framebuffer{
                    RESOURCE_DESC{
                        getDimension(f.mResource.mDimension),
						0u,
						tex.mWidth,
						tex.mHeight,
						1u,
						1u,
						f.mResource.mFormat,
						{ 1u, 0u },
						{},
                        RESOURCE_FLAG_ALLOW_RENDER_TARGET,
					},
					f.mClearColor
                }
            );
        }
    }

    uint32_t id = mBackBufferCount;
    for (const auto& f : rts) {
        auto desc = buildResourceDesc(f.mResource);

        visit(overload(
            [&](const ClearColor& color) {
                desc.mFlags = RESOURCE_FLAGS{ desc.mFlags | RESOURCE_FLAG_ALLOW_RENDER_TARGET };
            },
            [&](const ClearDepthStencil& depth) {
                desc.mFlags = RESOURCE_FLAGS{ desc.mFlags | RESOURCE_FLAG_ALLOW_DEPTH_STENCIL };
            }
        ), f.mClearColor);

        auto cc = f.mClearColor;
        visit(overload(
            [&](ClearColor& c) {
                if (c.mClearFormat == Format::UNKNOWN) {
                    c.mClearFormat = f.mResource.mFormat;
                }
            },
            [&](ClearDepthStencil& c) {
                if (c.mClearFormat == Format::UNKNOWN) {
                    c.mClearFormat = f.mResource.mFormat;
                }
            }
        ), cc);


        rw.mFramebuffers.emplace_back(
            Framebuffer{ desc, cc }
        );
        auto res = rtIndex.emplace(f.mName, id);
        Ensures(res.second);
        ++id;
    }
}

void RenderSolutionFactory::collectRTVsMinimal(
    size_t rtvOffset,
    const OrderedNameMap<RenderTargetResource>& bbs,
    const OrderedNameMap<RenderTargetResource>& rts,
    OrderedIdentityMap<GraphicsRenderNodeGraph::rtv_type>& rtvs,
    std::map<rtv_key, size_t>& indexMap
) const {
    Expects(rtvs.empty());

    auto rtvMap = OrderedIdentityMap<GraphicsRenderNodeGraph::rtv_type>();

    for (const auto& [graphName, graph] : mNodeGraphs) {
        for (const auto& rtv : graph.mRTVs) {
            rtvMap.emplace(rtv);
        }
    }

    // reorder
    for (const auto& rtv : rtvMap) {
        rtvs.emplace(rtv);
    }

    for (size_t m = 0; m != mNodeGraphs.size(); ++m) {
        const auto& graph = mNodeGraphs.at(mGraphOrder[m]);
        for (const auto& nodeID : graph.mNodeSorted) {
            const auto& node = graph.mNodeGraph[nodeID];
            for (const auto& output : node.mOutputs) {
                if (exists(bbs, output.mName))
                    continue;

                const auto& rt = at(rts, output.mName);
                visit(overload(
                    [&](const RenderTarget_& view) {
                        indexMap.emplace(std::piecewise_construct,
                            std::forward_as_tuple(graph.mName, nodeID, output.mName, output.mData, output.mModel),
                            std::forward_as_tuple(rtvOffset + index(rtvs, std::tuple{ output.mName, output.mData, output.mModel }))
                        );
                    },
                    [&](auto) {}
                ), output.mState);
            }
        }
    }
}

void RenderSolutionFactory::collectDSVsMinimal(
    const OrderedNameMap<RenderTargetResource>& bbs,
    const OrderedNameMap<RenderTargetResource>& rts,
    OrderedIdentityMap<GraphicsRenderNodeGraph::dsv_type>& dsvs,
    std::map<dsv_key, size_t>& indexMap
) const {
    Expects(dsvs.empty());

    auto dsvMap = OrderedIdentityMap<GraphicsRenderNodeGraph::dsv_type>();

    for (const auto& [graphName, graph] : mNodeGraphs) {
        for (const auto& dsv : graph.mDSVs) {
            dsvMap.emplace(dsv);
        }
    }

    // reorder
    for (const auto& dsv : dsvMap) {
        dsvs.emplace(dsv);
    }

    const auto& crtvs = dsvs;

    for (size_t m = 0; m != mNodeGraphs.size(); ++m) {
        const auto& graph = mNodeGraphs.at(mGraphOrder[m]);
        for (const auto& nodeID : graph.mNodeSorted) {
            const auto& node = graph.mNodeGraph[nodeID];
            for (const auto& output : node.mOutputs) {
                if (exists(bbs, output.mName))
                    continue;

                const auto& rt = at(rts, output.mName);

                visit(overload(
                    [&](const DepthWrite_& view) {
                        indexMap.emplace(std::piecewise_construct,
                            std::forward_as_tuple(graph.mName, nodeID, output.mName, output.mData, false),
                            std::forward_as_tuple(index(dsvs, std::tuple{ output.mName, output.mData, false }))
                        );
                    },
                    [&](const DepthRead_& view) {
                        indexMap.emplace(std::piecewise_construct,
                            std::forward_as_tuple(graph.mName, nodeID, output.mName, output.mData, true),
                            std::forward_as_tuple(index(dsvs, std::tuple{ output.mName, output.mData, true }))
                        );
                    },
                    [&](auto) {}
                ), output.mState);
            }
        }
    }
}
//
//bool RenderSolutionFactory::hasRenderSubpass(std::string_view name) const {
//    auto pos = name.find_first_of('.');
//    if (pos == std::string::npos) {
//        return false;
//    }
//    auto key = name.substr(0, pos);
//    auto iter = mNodeGraphs.find(key);
//    if (iter == mNodeGraphs.end())
//        return false;
//
//    const auto& [graphName, graph] = *iter;
//
//    ++pos;
//    auto pos2 = name.find_first_of('.', pos);
//
//    if (pos2 == std::string::npos) {
//        if (pos == name.size())
//            return false;
//
//        pos2 = name.size();
//    }
//
//    key = name.substr(pos, pos2 - pos);
//
//    auto iterRenderPass = graph.mNodeIndex.find(key);
//    if (iterRenderPass == graph.mNodeIndex.end())
//        return false;
//
//    return true;
//}

void RenderSolutionFactory::compile(std::string solutionName, RenderSolution& rw) const {
    for (const auto& [graphName, graph] : mNodeGraphs) {
        {
            auto res = rw.mPipelineIndex.emplace(std::piecewise_construct,
                std::forward_as_tuple(graphName),
                std::forward_as_tuple((uint32_t)rw.mPipelines.size()));
            Ensures(res.second);
        }
        rw.mPipelines.emplace_back();
        auto& pipeline = rw.mPipelines.back();

        for (size_t k = graph.mNodeSorted.size(); k-- > 0;) {
            const auto& nodeID = graph.mNodeSorted[k];
            const auto& node = graph.mNodeGraph[nodeID];

            {
                RenderSubpassDesc desc{ (uint32_t)pipeline.mPasses.size(), 0 };
                auto res = pipeline.mSubpassIndex.emplace(std::piecewise_construct,
                    std::forward_as_tuple(node.mName),
                    std::forward_as_tuple(desc));
                Ensures(res.second);
            }

            pipeline.mPasses.emplace_back();
            auto& pass = pipeline.mPasses.back();

            pass.mSubpasses.emplace_back();
            Ensures(pass.mSubpasses.size() == 1);
        }
    }
}

void RenderSolutionFactory::collectAttributes(const Shader::ShaderModules& modules, Shader::AttributeDatabase& database) const {
    Expects(mShaderGroups);
    mShaderGroups->collectAttributes(modules, database);
}

void RenderSolutionFactory::build(const Shader::AttributeDatabase& attrs, std::string solutionName,
    RenderSolution& rw, std::ostringstream& oss
) const {
    uint32_t rsgCount = 0;
    OrderedNameMap<RenderTargetResource> bbs;
    OrderedNameMap<RenderTargetResource> rts;
    OrderedNameMap<RenderTargetResource> rtsAll;
    collectFramebuffers(bbs, rts);
    rtsAll = bbs;
    for (const auto& rt : rts) {
        rtsAll.emplace(rt);
    }

    outputFramebuffers(bbs);
    outputFramebuffers(rts);

    std::map<std::string, uint32_t> rtIndex;
    buildFramebuffers(bbs, rts, rw, rtIndex);

    // rtvs
    OrderedIdentityMap<GraphicsRenderNodeGraph::rtv_type> rtvs;
    std::map<rtv_key, size_t> rtvIndex;
    size_t rtvOffset = mBackBufferCount * 2;

    collectRTVsMinimal(rtvOffset, bbs, rts, rtvs, rtvIndex);

    rw.mRTVs.resize(rtvOffset + rtvs.size());
    rw.mRTVSources.resize(rtvOffset + rtvs.size());

    // dsvs
    OrderedIdentityMap<GraphicsRenderNodeGraph::dsv_type> dsvs;
    std::map<dsv_key, size_t> dsvIndex;
    collectDSVsMinimal(bbs, rts, dsvs, dsvIndex);
    rw.mDSVs.resize(dsvs.size());
    rw.mDSVSources.resize(dsvs.size());

    // fix format
    Format format = {};
    for (const auto& f : bbs) {
        if (isBackBuffer(f)) {
            if (isSRGB(f.mResource.mFormat)) {
                format = makeTypeless(f.mResource.mFormat);
                format = makeTypelessUNorm(format);
            } else {
                format = f.mResource.mFormat;
            }
            break;
        }
    }

    // create backbuffer rtvs
    for (auto i = 0u; i != mBackBufferCount; ++i) {
        rw.mRTVSources[i] = FramebufferHandle{ i };
        rw.mRTVSources[i + mBackBufferCount] = FramebufferHandle{ i };


        rw.mRTVs[i] = RENDER_TARGET_VIEW_DESC{
            format,
            RTV_DIMENSION_TEXTURE2D,
        };

        auto formatS = makeUNormSRGB(format);
        if (formatS == format) {
            CONSOLE_WARNING();
            std::cout << "backbuffer format srgb equal unorm" << std::endl;
        }
        rw.mRTVs[i + mBackBufferCount] = RENDER_TARGET_VIEW_DESC{
            formatS,
            RTV_DIMENSION_TEXTURE2D,
        };
    }

    // create rtvs
    {
        size_t rtvID = 0;
        for (const auto& rtv : rtvs) {
            const auto& rt = at(rts, std::get<0>(rtv));
            rw.mRTVs[rtvOffset + rtvID] = buildRenderTargetViewDesc(rt.mResource, std::get<1>(rtv), std::get<2>(rtv));
            rw.mRTVSources[rtvOffset + rtvID] = FramebufferHandle{ rtIndex.at(rt.mName) };
            ++rtvID;
        }
    }

    // create dsvs
    {
        size_t dsvID = 0;
        for (const auto& dsv : dsvs) {
            const auto& rt = at(rts, std::get<0>(dsv));
            rw.mDSVs[dsvID] = buildDepthStencilViewDesc(rt.mResource, std::get<1>(dsv), std::get<2>(dsv));
            rw.mDSVSources[dsvID] = FramebufferHandle{ rtIndex.at(rt.mName) };
            ++dsvID;
        }
    }

    // build rtv, dsv
    for (const auto& [graphName, graph] : mNodeGraphs) {
        auto& pipeline = rw.mPipelines.at(at(rw.mPipelineIndex, graphName));

        pipeline.mRTVInitialStates.resize(rtvOffset + rtvs.size());
        pipeline.mDSVInitialStates.resize(dsvs.size());

        for (auto i = 0u; i != mBackBufferCount; ++i) {
            pipeline.mRTVInitialStates[i] = buildResourceStates({ Present });
            pipeline.mRTVInitialStates[i + mBackBufferCount] = buildResourceStates({ Common });
        }

        {
            std::set<GraphicsRenderNodeGraph::key_type> resources;
            size_t rtvID = 0;
            for (const auto& rtv : rtvs) {
                auto key = std::pair(std::get<0>(rtv), std::get<1>(rtv));
                auto iter = graph.mViewStates.find(key);
                if (iter != graph.mViewStates.end()) {
                    auto res = resources.emplace(key);
                    if (res.second && !iter->second.mTransitions.empty()) {
                        pipeline.mRTVInitialStates[rtvOffset + rtvID] =
                            buildResourceStates(iter->second.mTransitions.front().mTarget);
                    }
                }
                ++rtvID;
            }
        }
        {
            std::set<GraphicsRenderNodeGraph::key_type> resources;
            size_t dsvID = 0;
            for (const auto& dsv : dsvs) {
                auto key = std::pair(std::get<0>(dsv), std::get<1>(dsv));
                auto iter = graph.mViewStates.find(key);
                if (iter != graph.mViewStates.end()) {
                    auto res = resources.emplace(key);
                    if (res.second && !iter->second.mTransitions.empty()) {
                        pipeline.mDSVInitialStates[dsvID] =
                            buildResourceStates(iter->second.mTransitions.front().mTarget);
                    }
                }
                ++dsvID;
            }
        }

        for (size_t k = graph.mNodeSorted.size(); k --> 0;) {
            bool bOutput = (k == 0);
            const auto& nodeID = graph.mNodeSorted[k];
            const auto& node = graph.mNodeGraph[nodeID];
            const auto& subpassIndex = at(pipeline.mSubpassIndex, node.mName);
            auto& pass = pipeline.mPasses.at(subpassIndex.mPassID);
            auto& subpass = pass.mSubpasses.at(subpassIndex.mSubpassID);
            Expects(pass.mSubpasses.size() == 1);

            visit(overload(
                [&](const Multisampling& s) {
                    Expects(s.mCount > 1);
                    subpass.mSampleDesc.mCount = s.mCount;
                    subpass.mSampleDesc.mQuality = s.mQuality;
                },
                [&](std::monostate) {
                    subpass.mSampleDesc.mCount = 1;
                    subpass.mSampleDesc.mQuality = 0;
                }
            ), node.mSampling);

            if (!bOutput) {
                Shader::compileShader(subpass.mRootSignature, "rootsig_1_1",
                    node.mName, node.mRootSignature);
                std::string space;
                if (rsgCount++) {
                    oss << "\n";
                }
                oss << "Solution \"" << solutionName << "\" "
                    << "Pipeline \"" << graph.mName << "\" "
                    << "Subpass \"" << node.mName << "\" {\n";
                {
                    INDENT();
                    copyString(oss, space, node.mRootSignature);
                }
                oss << "}\n";

                Expects(mShaderGroups);
                
                const auto& group = mShaderGroups->getGroup(solutionName, graphName, node.mName);
                subpass.mConstantBuffers.reserve(group.mRootSignature.mDatabase.mConstantBuffers.size());
                for (const auto& constantBufferPair : group.mRootSignature.mDatabase.mConstantBuffers) {
                    const auto& index = constantBufferPair.first;
                    const auto& constantBuffer = constantBufferPair.second;
                    if (index.mUpdate < group.mUpdateFrequency) {
                        continue;
                    }
                    Expects(index.mUpdate >= group.mUpdateFrequency);
                    auto& runtimeConstantBuffer = subpass.mConstantBuffers.emplace_back();
                    runtimeConstantBuffer.mIndex = index;
                    runtimeConstantBuffer.mConstants.reserve(constantBuffer.mValues.size());
                    Expects(runtimeConstantBuffer.mSize == 0);
                    for (const auto& constant : constantBuffer.mValues) {
                        Expects(!constant.mName.empty());
                        const auto& attr = at(attrs.mAttributes, constant.mName);
                        auto& dst = runtimeConstantBuffer.mConstants.emplace_back();
                        visit(overload(
                            [&](EngineSource_) {
                                getType(constant.mName, dst.mDataType);
                            },
                            [&](MaterialSource_) {
                                throw std::invalid_argument("PerPass attribute should not be material source");
                            }
                            ), attr.mSource);
                        dst.mSource = attr.mSource;
                        dst.mID = gsl::narrow<uint32_t>(attrs.mIndex.at(constant.mName));
                        runtimeConstantBuffer.mSize += getSize(constant.mType);
                    }
                }

                subpass.mDescriptors.reserve(group.mRootSignature.mDatabase.mDescriptors.size());
                for (const auto& collectionPair : group.mRootSignature.mDatabase.mDescriptors) {
                    const auto& index = collectionPair.first;
                    const auto& collection = collectionPair.second;
                    auto& runtimeCollection = subpass.mDescriptors.emplace_back();
                    runtimeCollection.mIndex = index;
                    runtimeCollection.mResourceViewLists.reserve(collection.mResourceViewLists.size());
                    runtimeCollection.mSamplerLists.reserve(collection.mSamplerLists.size());

                    auto buildList = [&runtimeCollection, &index, &group, &attrs](const Shader::DescriptorList& list) {
                        auto& runtimeList = runtimeCollection.mResourceViewLists.emplace_back();
                        runtimeList.mSlot = list.mSlot;
                        runtimeList.mRanges.reserve(list.mRanges.size());
                        runtimeList.mUnboundedDescriptors.reserve(list.mUnboundedDescriptors.size());
                        for (const auto& [type, range] : list.mRanges) {
                            auto& runtimeRange = runtimeList.mRanges.emplace_back();
                            runtimeRange.mType = type;
                            runtimeRange.mSubranges.reserve(range.mSubranges.size());
                            runtimeRange.mCapacity = range.mCapacity;

                            if (index.mUpdate < group.mUpdateFrequency) {
                                Expects(range.mSubranges.empty());
                                Expects(range.mCapacity != 0);
                                runtimeList.mCapacity += runtimeRange.mCapacity;
                            } else {
                                Expects(!range.mSubranges.empty());
                                Expects(range.mCapacity == 0);
                                runtimeList.mCapacity += getDescriptorCapacity(range);
                            }
                            for (const auto& [source, subrange] : range.mSubranges) {
                                auto& runtimeSubrange = runtimeRange.mSubranges.emplace_back();
                                runtimeSubrange.mSource = source;
                                runtimeSubrange.mDescriptors.reserve(subrange.mAttributes.size());
                                for (const auto& attr : subrange.mAttributes) {
                                    auto& d = runtimeSubrange.mDescriptors.emplace_back();
                                    d.mAttributeType = attr.mType;
                                    visit(overload(
                                        [&](EngineSource_) {
                                            getType(attr.mName, d.mDataType);
                                        },
                                        [&](MaterialSource_) {
                                            try_getType(attr.mName, d.mDataType);
                                        }
                                    ), source);
                                    if (attr.mName.empty()) {
                                        Expects(std::holds_alternative<CBuffer_>(attr.mType));
                                        Expects(std::holds_alternative<Descriptor::ConstantBuffer_>(d.mDataType));
                                    } else {
                                        Expects(!std::holds_alternative<Descriptor::ConstantBuffer_>(d.mDataType));
                                        d.mID = gsl::narrow<uint32_t>(attrs.mIndex.at(attr.mName));
                                    }
                                }
                            }
                        }
                        Expects(list.mUnboundedDescriptors.size() <= 1);
                        for (const auto& [type, unbounded] : list.mUnboundedDescriptors) {
                            auto& runtimeUnbounded = runtimeList.mUnboundedDescriptors.emplace_back();
                            runtimeUnbounded.mType = type;
                            runtimeUnbounded.mAttribute = unbounded.mAttribute.mName;
                        }
                    };
                    for (const auto& [space, list] : collection.mResourceViewLists) {
                        buildList(list);
                    }
                    for (const auto& [space, list] : collection.mSamplerLists) {
                        buildList(list);
                    }
                }
            }

            // Output 
            subpass.mOutputAttachments.reserve(node.mOutputs.size());
            std::map<std::pair<std::string, ResourceDataView>, RenderViewTransition> postTransitions;

            for (const auto& output : node.mOutputs) {
                // build viewports and scissor rects
                if (pass.mViewports.empty()) {
                    const auto& rt = at(rtsAll, output.mName);
                    uint32_t width{};
                    uint32_t height{};
                    visit(overload(
                        [&](const Resource1D& r) {
                            width = r.mWidth;
                        },
                        [&](const Resource2D& r) {
                            width = r.mWidth;
                            height = r.mHeight;
                        },
                        [](const auto&) {
                            throw std::runtime_error("rtv, dsv cannot be buffer or texture3d");
                        }
                    ), rt.mResource.mDimension);

                    if (!bOutput) {
                        pass.mViewports.emplace_back(VIEWPORT{ 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f });
                        pass.mScissorRects.emplace_back(RECT{ 0u, 0u, width, height });
                    }
                }

                // build rtv dsv
                bool bBackBuffer = false;
                uint32_t rtHandle = {};
                if (exists(bbs, output.mName)) {
                    bBackBuffer = true;
                    if (std::holds_alternative<SRGB_>(output.mModel)) {
                        rtHandle = { 0 };
                        if (!bOutput) {
                            subpass.mOutputAttachments.emplace_back(
                                Attachment{ 0, mBackBufferCount, output.mStoreOp, output.mLoadOp }
                            );
                        }
                    } else {
                        rtHandle = { 0 };
                        if (!bOutput) {
                            subpass.mOutputAttachments.emplace_back(
                                Attachment{ 0, 0 , output.mStoreOp, output.mLoadOp }
                            );
                        }
                    }
                } else {
                    const auto& rt = at(rts, output.mName);
                    if (isRTV(rt)) {
                        rtHandle = rtIndex.at(output.mName);
                        auto rtvHandle = rtvIndex.at(
                            std::tuple{
                                graph.mName, nodeID, output.mName, output.mData, output.mModel
                            }
                        );

                        subpass.mOutputAttachments.emplace_back(
                            Attachment{
                                gsl::narrow<uint32_t>(rtHandle),
                                gsl::narrow<uint32_t>(rtvHandle),
                                output.mStoreOp, output.mLoadOp
                            }
                        );
                    } else {
                        Expects(isDSV(rt));
                        rtHandle = rtIndex.at(output.mName);
                        auto dsvHandle = dsvIndex.at(std::tuple{ graph.mName, nodeID, output.mName, output.mData,
                            std::holds_alternative<DepthRead_>(output.mState) });

                        subpass.mDepthStencilAttachment = Attachment{
                            gsl::narrow<uint32_t>(rtHandle),
                            gsl::narrow<uint32_t>(dsvHandle),
                            output.mStoreOp, output.mLoadOp
                        };
                    }
                }

                //if (bOutput && bBackBuffer) {
                //    continue;
                //}
                //// build transition
                //auto resourceKey = std::pair{ output.mName, output.mData };
                //const auto& states = graph.mViewStates.at(resourceKey);
                //auto t = findTransition(states, nodeID);
                //if (t) {
                //    auto res = postTransitions.emplace(
                //        std::pair{
                //            resourceKey,
                //            RenderViewTransition{
                //                rtHandle, 
                //                buildResourceStates(t->mSource),
                //                buildResourceStates(t->mTarget)
                //            }
                //        }
                //    );
                //    if (res.second == false) {
                //        throw std::runtime_error("render state already exists");
                //    }
                //}
            } // foreach output in node

            //for (const auto& input : node.mInputs) {
            //    const auto& rt = at(rts, input.mName);
            //    auto rtHandle = rtIndex.at(input.mName);

            //    // build transition
            //    auto resourceKey = std::pair{ input.mName, input.mData };
            //    const auto& states = graph.mViewStates.at(resourceKey);
            //    auto t = findTransition(states, nodeID);
            //    if (t) {
            //        auto res = postTransitions.emplace(
            //            std::pair{
            //                resourceKey,
            //                RenderViewTransition{
            //                    rtHandle, 
            //                    buildResourceStates(t->mSource),
            //                    buildResourceStates(t->mTarget)
            //                }
            //            }
            //        );
            //        if (res.second == false) {
            //            if (t->mSource)
            //            bool bDSVReadOnly = false;
            //            if (res.first->second.mSource == RESOURCE_STATE_DEPTH_READ)
            //            {
            //                res.first->second.mSource = static_cast<RESOURCE_STATES>(
            //                    static_cast<uint32_t>(res.first->second.mSource) |
            //                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            //                bDSVReadOnly = true;
            //            }
            //            if (res.first->second.mTarget == RESOURCE_STATE_DEPTH_READ)
            //            {
            //                res.first->second.mTarget = static_cast<RESOURCE_STATES>(
            //                    static_cast<uint32_t>(res.first->second.mTarget) |
            //                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            //                bDSVReadOnly = true;
            //            }

            //            if (!bDSVReadOnly) {
            //                throw std::runtime_error("render state already exists");
            //            }
            //        }
            //    }
            //}

            for (const auto& path : graph.mViewStates) {
                for (const auto& trans : path.second.mTransitions) {
                    if (trans.mNodeID != nodeID)
                        continue;
                    auto resourceKey = path.first;

                    uint32_t rtHandle{};
                    if (exists(bbs, resourceKey.first)) {
                        rtHandle = 0;
                        if (std::holds_alternative<Present_>(trans.mSource.mState))
                            continue;
                    } else {
                        rtHandle = rtIndex.at(std::get<0>(resourceKey));
                    }

                    postTransitions.emplace(
                        std::pair{
                            resourceKey,
                            RenderViewTransition{
                                rtHandle,
                                buildResourceStates(trans.mSource),
                                buildResourceStates(trans.mTarget)
                            }
                        }
                    );
                }
            }

            for (const auto& v : postTransitions) {
                subpass.mPostViewTransitions.emplace_back(v.second);
            }
        }
    }
}

void RenderGraphFactory::buildShaderGroupFromSolutions() {
    for (const auto& [solutionName, solutionFactory] : mSolutionFactories) {
        solutionFactory.buildShaderGroup(mShaderGroups);
    }
}

void RenderGraphFactory::bindShadersToShaderGroups() {
    mShaderDatabase.fillShaderGroups(mShaderGroups);
}

void RenderGraphFactory::completeFactories() {
    for (auto& [solutionName, solutionFactory] : mSolutionFactories) {
        solutionFactory.updateRenderGraph(mShaderModules, mShaderGroups);
        solutionFactory.validateGraphs();
    }
}

void RenderGraphFactory::buildRootSignatureAndDescriptors() {
    mShaderGroups.buildRootSignatures(mShaderModules, PerPass);
}

void RenderGraphFactory::buildRenderGraphData(RenderSwapChain& renderGraphData) const {
    renderGraphData.mSolutionIndex.clear();
    renderGraphData.mSolutions.clear();
    for (auto& [solutionName, factory] : mSolutionFactories) {
        renderGraphData.mSolutionIndex.emplace(solutionName, gsl::narrow<uint32_t>(renderGraphData.mSolutions.size()));
        auto& solutionData = renderGraphData.mSolutions.emplace_back();
        factory.compile(solutionName, solutionData);
    }
}

void RenderGraphFactory::buildAttributeDatabase(Shader::AttributeDatabase& attributes) const {
    for (auto& [solutionName, factory] : mSolutionFactories) {
        factory.collectAttributes(mShaderModules, attributes);
    }
}

}

}

}
