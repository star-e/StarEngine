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

#include "SDX12Utils.h"
#include <boost/range/combine.hpp>
#include <Star/Graphics/SRenderNames.h>
#include <Star/Graphics/SRenderGraphNames.h>
#include "SDX12UploadBuffer.h"
#include <Star/Graphics/SRenderFormatTextureUtils.h>
#include <Star/Graphics/SRenderUtils.h>
#include "SDX12ShaderDescriptorHeap.h"

namespace Star::Graphics::Render {

bool try_createDX12(ID3D12Device* pDevice, std::pmr::monotonic_buffer_resource* mr,
    const MetaID& render, DX12Resources& resources, const MetaID& metaID,
    Core::ResourceType tag, bool async
);

namespace {

std::pair<DX12MeshData*, bool> try_createDX12MeshData(CreationContext& context,
    DX12Resources& resources, const MetaID& metaID, bool async
) {
    bool created = false;
    auto iter = resources.mMeshes.find(metaID);
    if (iter != resources.mMeshes.end()) {

    } else {
        std::tie(iter, created) = resources.mMeshes.emplace(metaID);
        Ensures(created);
        resources.mMeshes.modify(iter, [&](DX12MeshData& mesh) {
            mesh.mMeshData.reset(metaID, async);
            if (!async) {
                Ensures(mesh.mMeshData);
                const auto& meshData = *mesh.mMeshData;
                mesh.mIndexBuffer.mPrimitiveTopology = meshData.mIndexBuffer.mPrimitiveTopology;
                mesh.mLayoutID = meshData.mLayoutID;
                mesh.mLayoutName = meshData.mLayoutName;

                if (!meshData.mIndexBuffer.mBuffer.empty()) {
                    auto buffer = context.upload(meshData.mIndexBuffer.mBuffer, 16);
                    mesh.mIndexBuffer.mBuffer = DX12::createBuffer(context.mDevice, meshData.mIndexBuffer.mBuffer.size());
                    STAR_SET_DEBUG_NAME(mesh.mIndexBuffer.mBuffer.get(), to_string(metaID) + " index buffer");

                    context.mCommandList->CopyBufferRegion(mesh.mIndexBuffer.mBuffer.get(), 0,
                        buffer.mResource, buffer.mBufferOffset, meshData.mIndexBuffer.mBuffer.size());

                    mesh.mIndexBufferView.BufferLocation = mesh.mIndexBuffer.mBuffer->GetGPUVirtualAddress();
                    mesh.mIndexBufferView.SizeInBytes = gsl::narrow_cast<uint32_t>(meshData.mIndexBuffer.mBuffer.size());
                    mesh.mIndexBufferView.Format = meshData.mIndexBuffer.mElementSize == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
                }

                mesh.mVertexBuffers.reserve(meshData.mVertexBuffers.size());
                mesh.mVertexBufferViews.reserve(meshData.mVertexBuffers.size());
                for (const auto& vertexBufferData : meshData.mVertexBuffers) {
                    auto buffer = context.upload(vertexBufferData.mBuffer, 16);
                    auto id = mesh.mVertexBuffers.size();
                    auto& vb = mesh.mVertexBuffers.emplace_back();
                    auto& vbv = mesh.mVertexBufferViews.emplace_back();
                    vb.mBuffer = DX12::createBuffer(context.mDevice, vertexBufferData.mBuffer.size());
                    STAR_SET_DEBUG_NAME(vb.mBuffer.get(), to_string(metaID) + " vertex buffer " + std::to_string(id));

                    context.mCommandList->CopyBufferRegion(vb.mBuffer.get(), 0,
                        buffer.mResource, buffer.mBufferOffset, vertexBufferData.mBuffer.size());

                    vbv.BufferLocation = vb.mBuffer->GetGPUVirtualAddress();
                    vbv.SizeInBytes = gsl::narrow_cast<uint32_t>(vertexBufferData.mBuffer.size());
                    vbv.StrideInBytes = vertexBufferData.mDesc.mVertexSize;
                    Expects(vertexBufferData.mDesc.mVertexSize);
                }

                mesh.mSubMeshes = meshData.mSubMeshes;

                auto barrierCount = mesh.mVertexBuffers.size() + !meshData.mIndexBuffer.mBuffer.empty();

                auto pBarriers = pmr_make_unique<std::pmr::vector<D3D12_RESOURCE_BARRIER>>(context.mMemoryArena);
                pBarriers->reserve(barrierCount);
                auto& barriers = *pBarriers;
                if (mesh.mIndexBuffer.mBuffer.get()) {
                    auto& barrier = barriers.emplace_back();
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                    barrier.Transition.pResource = mesh.mIndexBuffer.mBuffer.get();
                    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_INDEX_BUFFER | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                }
                for (const auto& vb : mesh.mVertexBuffers) {
                    auto& barrier = barriers.emplace_back();
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                    barrier.Transition.pResource = vb.mBuffer.get();
                    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                }
                Ensures(barrierCount == barriers.size());
                context.mCommandList->ResourceBarrier(gsl::narrow_cast<uint32_t>(barriers.size()), barriers.data());
                pBarriers.release();
                context.mMemoryArena->release();
            }
        });
    }
    return { const_cast<DX12MeshData*>(&*iter), created };
}

std::pair<DX12TextureData*, bool> try_createDX12TextureData(CreationContext& context,
    DX12Resources& resources, const MetaID& metaID, bool async
) {
    bool created = false;
    auto iter = resources.mTextures.find(metaID);
    if (iter != resources.mTextures.end()) {

    } else {
        std::tie(iter, created) = resources.mTextures.emplace(metaID);
        Ensures(created);
        resources.mTextures.modify(iter, [&](DX12TextureData& tex) {
            tex.mTextureData.reset(metaID, async);
            if (!async) {
                Ensures(tex.mTextureData);
                const auto& textureData = tex.mTextureData->mBuffer;
                auto buffer = context.upload(textureData.data(), textureData.size(), sSliceAlignment);
                auto desc = getDX12(tex.mTextureData->mDesc);
                desc.Format = getDXGIFormat(tex.mTextureData->mDesc.mFormat);
                tex.mTexture = DX12::createTexture2D(context.mDevice, desc);
                tex.mFormat = getDXGIFormat(tex.mTextureData->mFormat);
                STAR_SET_DEBUG_NAME(tex.mTexture.get(), to_string(metaID) + " texture");
                
                const auto& resource = tex.mTextureData->mDesc;
#ifdef STAR_DEV
                D3D12_RESOURCE_DESC Desc = tex.mTexture->GetDesc();
                Expects(Desc.MipLevels == resource.mMipLevels);

                std::pmr::vector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> pLayouts(resource.mMipLevels, context.mMemoryArena);
                std::pmr::vector<uint32_t> pNumRows(resource.mMipLevels);
                std::pmr::vector<uint64_t> pRowSizesInBytes(resource.mMipLevels);

                uint64_t RequiredSize = 0;
                context.mDevice->GetCopyableFootprints(&Desc, 0, resource.mMipLevels,
                    buffer.mBufferOffset, pLayouts.data(), pNumRows.data(),
                    pRowSizesInBytes.data(), &RequiredSize);
#endif
                uint64_t offset1 = 0;
                uint32_t width = gsl::narrow_cast<uint32_t>(resource.mWidth);
                uint32_t height = resource.mHeight;
                auto encoding = getEncoding(resource.mFormat);
                for (uint32_t i = 0; i != resource.mMipLevels; ++i) {
                    auto mip = getMipInfo(resource.mFormat, width, height);

                    D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout{};
                    layout.Offset = buffer.mBufferOffset + offset1;
                    layout.Footprint.Format = getDXGIFormat(resource.mFormat);
                    layout.Footprint.Width = width;
                    layout.Footprint.Height = height;
                    layout.Footprint.Depth = resource.mDepthOrArraySize;
                    layout.Footprint.RowPitch = mip.mUploadRowPitchSize;

#ifdef STAR_DEV
                    Expects(layout.Offset == pLayouts[i].Offset);
                    Expects(layout.Footprint.Format == pLayouts[i].Footprint.Format);
                    Expects(layout.Footprint.Width == pLayouts[i].Footprint.Width);
                    Expects(layout.Footprint.Height == pLayouts[i].Footprint.Height);
                    Expects(layout.Footprint.Depth == pLayouts[i].Footprint.Depth);
                    Expects(layout.Footprint.RowPitch == pLayouts[i].Footprint.RowPitch);
#endif
                    D3D12_TEXTURE_COPY_LOCATION Dst{ tex.mTexture.get(), D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, i };
                    D3D12_TEXTURE_COPY_LOCATION Src{ buffer.mResource, D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT, layout };
                    context.mCommandList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);

                    offset1 += mip.mUploadSliceSize;
                    width = half_size(width, encoding.mBlockWidth);
                    height = half_size(height, encoding.mBlockHeight);
                }

                auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(tex.mTexture.get(),
                    D3D12_RESOURCE_STATE_COPY_DEST,
                    D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

                context.mCommandList->ResourceBarrier(1, &barrier);
            }
        });
    }
    context.mMemoryArena->release();
    return { const_cast<DX12TextureData*>(&*iter), created };
}

void resizeData(DX12ShaderData& prototype, const ShaderData& prototypeData) {
    prototype.mSolutions.reserve(prototypeData.mSolutions.size());
    for (const auto& solutionData : prototypeData.mSolutions) {
        auto& solution = prototype.mSolutions.emplace_back();
        solution.mPipelines.reserve(solutionData.second.mPipelines.size());
        for (const auto& pipelineData : solutionData.second.mPipelines) {
            auto& pipeline = solution.mPipelines.emplace_back();
            pipeline.mQueues.reserve(pipelineData.second.mQueues.size());
            for (const auto& queueData : pipelineData.second.mQueues) {
                auto& queue = pipeline.mQueues.emplace_back();
                queue.mLevels.reserve(queueData.second.mLevels.size());
                for (const auto& levelData : queueData.second.mLevels) {
                    auto& level = queue.mLevels.emplace_back();
                    level.mPasses.reserve(levelData.mPasses.size());
                    for (const auto& variantData : levelData.mPasses) {
                        auto& variant = level.mPasses.emplace_back();
                        variant.mSubpasses.reserve(variantData.second.mSubpasses.size());
                        for (const auto& subpassData : variantData.second.mSubpasses) {
                            auto& subpass = variant.mSubpasses.emplace_back();
                            subpass.mVertexLayoutIndex.reserve(subpassData.mVertexLayouts.size());
                            subpass.mStates.resize(subpassData.mVertexLayouts.size());
                            // descriptors
                            //subpass.mDescriptors.reserve(subpassData.mDescriptors.size());
                            //for (const auto& collectionData : subpassData.mDescriptors) {
                            //    auto& collection = subpass.mDescriptors.emplace_back();
                            //    collection.mResourceViewLists.reserve(collectionData.mResourceViewLists.size());
                            //    for (const auto& listData : collectionData.mResourceViewLists) {
                            //        auto& list = collection.mResourceViewLists.emplace_back();
                            //        list.mRanges.reserve(listData.mRanges.size());
                            //        for (const auto& rangeData : listData.mRanges) {
                            //            auto& range = list.mRanges.emplace_back();
                            //            range.mSubranges.reserve(rangeData.mSubranges.size());
                            //            for (const auto& subrangeData : rangeData.mSubranges) {
                            //                range.mSubranges.emplace_back();
                            //            }
                            //        }
                            //        list.mUnboundedDescriptors.resize(listData.mUnboundedDescriptors.size());
                            //    }

                            //    collection.mSamplerLists.reserve(collectionData.mSamplerLists.size());
                            //    for (const auto& listData : collectionData.mSamplerLists) {
                            //        auto& list = collection.mSamplerLists.emplace_back();
                            //        list.mRanges.reserve(listData.mRanges.size());
                            //        for (const auto& rangeData : listData.mRanges) {
                            //            auto& range = list.mRanges.emplace_back();
                            //            range.mSubranges.reserve(rangeData.mSubranges.size());
                            //            for (const auto& subrangeData : rangeData.mSubranges) {
                            //                range.mSubranges.emplace_back();
                            //            }
                            //        }
                            //        list.mUnboundedDescriptors.resize(listData.mUnboundedDescriptors.size());
                            //    }
                            //}
                        }
                    }
                }
            }
        }
    }
}

void reserveIndex(DX12ShaderData& prototype) {
    prototype.mSolutionIndex.reserve(prototype.mSolutions.size());
    for (auto& solution : prototype.mSolutions) {
        solution.mPipelineIndex.reserve(solution.mPipelines.size());
        for (auto& pipeline : solution.mPipelines) {
            pipeline.mQueueIndex.reserve(pipeline.mQueues.size());
            for (auto& queue : pipeline.mQueues) {
                for (auto& level : queue.mLevels) {
                    level.mPassIndex.reserve(level.mPasses.size());
                }
            }
        }
    }
}

template<class Flatmap, class Index>
void emplaceIndex(Flatmap& flatmap, Index& index, const PmrMap<std::pmr::string, RenderSubpassDesc>& renderIndex) {
    size_t i = 0;
    for (const auto& v : index) {
        const auto& name = v.first;
        auto renderID = renderIndex.at(name);
        flatmap.try_emplace(flatmap.end(), renderID, i++);
    }
    Ensures(flatmap.size() == index.size());
}

template<class Flatmap, class Index>
void emplaceIndex(Flatmap& flatmap, Index& index, const PmrMap<std::pmr::string, uint32_t>& renderIndex) {
    size_t i = 0;
    for (const auto& v : index) {
        const auto& name = v.first;
        auto renderID = renderIndex.at(name);
        flatmap.try_emplace(flatmap.end(), renderID, i++);
    }
    Ensures(flatmap.size() == index.size());
}

template<class Flatmap, class Index>
void emplaceIndex(Flatmap& flatmap, Index& index) {
    size_t i = 0;
    for (const auto& v : index) {
        flatmap.try_emplace(flatmap.end(), v.first, i++);
    }
    Ensures(flatmap.size() == index.size());
}

void createIndex(DX12ShaderData& prototype, const ShaderData& prototypeData,
    const DX12RenderWorks& renderGraph
) {
    Expects(prototype.mSolutions.size() == prototypeData.mSolutions.size());
    emplaceIndex(prototype.mSolutionIndex, prototypeData.mSolutions, renderGraph.mSolutionIndex);
    Ensures(prototype.mSolutionIndex.size() == prototypeData.mSolutions.size());
    for (auto&& [solution, solutionData] : boost::combine(prototype.mSolutions, prototypeData.mSolutions)) {
        const auto& renderSolution = renderGraph.mSolutions.at(renderGraph.mSolutionIndex.at(solutionData.first));
        Expects(solution.mPipelines.size() == solutionData.second.mPipelines.size());
        emplaceIndex(solution.mPipelineIndex, solutionData.second.mPipelines, renderSolution.mPipelineIndex);
        Ensures(solution.mPipelineIndex.size() == solutionData.second.mPipelines.size());
        for (auto&& [pipeline, pipelineData] : boost::combine(solution.mPipelines, solutionData.second.mPipelines)) {
            const auto& renderPipeline = renderSolution.mPipelines.at(renderSolution.mPipelineIndex.at(pipelineData.first));
            Expects(pipeline.mQueues.size() == pipelineData.second.mQueues.size());
            emplaceIndex(pipeline.mQueueIndex, pipelineData.second.mQueues, renderPipeline.mSubpassIndex);
            Ensures(pipeline.mQueueIndex.size() == pipelineData.second.mQueues.size());
            for (auto&& [queue, queueData] : boost::combine(pipeline.mQueues, pipelineData.second.mQueues)) {
                //const auto& passDesc = renderPipeline.mSubpassIndex.at(queueData.first);
                //const auto& renderPass = renderPipeline.mPasses.at(passDesc.mPassID);
                //const auto& renderSubpass = renderPass.mSubpasses.at(passDesc.mSubpassID);
                for (auto&& [level, levelData] : boost::combine(queue.mLevels, queueData.second.mLevels)) {
                    Expects(level.mPasses.size() == levelData.mPasses.size());
                    emplaceIndex(level.mPassIndex, levelData.mPasses);
                    Ensures(level.mPassIndex.size() == levelData.mPasses.size());
                }
            }
        }
    }
}

void createShaderResources(const DX12RenderSolution& renderSolution, const DX12GraphicsSubpass& renderSubpass,
    DX12ShaderSubpassData& subpass, const ShaderSubpassData& subpassData,
    const ContentSettings& settings, ID3D12Device* pDevice, std::pmr::monotonic_buffer_resource* mr
) {
    subpass.mConstantBuffers = subpassData.mConstantBuffers;
    subpass.mDescriptors = subpassData.mDescriptors;
    // shader programs
    HRESULT hr = S_OK;
    if (!subpassData.mProgram.mPS.empty()) {
        V(D3DCreateBlob(subpassData.mProgram.mPS.size(), subpass.mProgram.mPS.put()));
        memcpy(subpass.mProgram.mPS->GetBufferPointer(),
            subpassData.mProgram.mPS.data(), subpassData.mProgram.mPS.size());
    }
    if (!subpassData.mProgram.mVS.empty()) {
        V(D3DCreateBlob(subpassData.mProgram.mVS.size(), subpass.mProgram.mVS.put()));
        memcpy(subpass.mProgram.mVS->GetBufferPointer(),
            subpassData.mProgram.mVS.data(), subpassData.mProgram.mVS.size());
    }

    auto pElemDescs = pmr_make_unique<std::pmr::vector<D3D12_INPUT_ELEMENT_DESC>>(mr, 16);

    // shader input layouts and pso
    for (uint32_t i = 0; i != subpassData.mVertexLayouts.size(); ++i) {
        auto vertID = subpassData.mVertexLayouts[i];
        subpass.mVertexLayoutIndex[vertID] = i;
        auto& state = subpass.mStates[i];
        const auto& meshLayout = settings.mVertexLayouts.at(vertID);

        pElemDescs->clear();

        for (const auto& [semantic, inputs] : subpassData.mInputLayout.mSemantics) {
            uint32_t semanticID = 0;
            for (const auto& input : inputs) {
                const auto& [bufferID, elementID] = meshLayout.mIndex.at(input);
                const auto& descData = meshLayout.mBuffers.at(bufferID).mElements.at(elementID);
                D3D12_INPUT_ELEMENT_DESC desc{};
                desc.SemanticName = visit(overload(
                    [](const SV_Position_&) {
                        return "POSITION";
                    },
                    [](const auto& s) {
                        return getName(s);
                    }
                ), descData.mType);
                desc.SemanticIndex = semanticID++;
                desc.Format = getDXGIFormat(descData.mFormat);
                desc.InputSlot = bufferID;
                desc.AlignedByteOffset = descData.mAlignedByteOffset;
                desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
                desc.InstanceDataStepRate = 0;
                pElemDescs->emplace_back(desc);
            }
        }
        const auto& stateData = subpassData.mState;

        D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
        // Shader Binding
        desc.pRootSignature = renderSubpass.mRootSignature.get();
        // Shader
        desc.VS.pShaderBytecode = subpass.mProgram.mVS->GetBufferPointer();
        desc.VS.BytecodeLength = subpass.mProgram.mVS->GetBufferSize();
        desc.PS.pShaderBytecode = subpass.mProgram.mPS->GetBufferPointer();
        desc.PS.BytecodeLength = subpass.mProgram.mPS->GetBufferSize();
        // Render State
        desc.BlendState = getDX12(stateData.mBlendState);
        desc.SampleMask = stateData.mSampleMask;
        desc.RasterizerState = getDX12(stateData.mRasterizerState);
        desc.DepthStencilState = getDX12(stateData.mDepthStencilState);

        // Mesh
        if (!subpassData.mInputLayout.mSemantics.empty()) {
            desc.InputLayout.pInputElementDescs = pElemDescs->data();
            desc.InputLayout.NumElements = (uint32_t)pElemDescs->size();
            desc.IBStripCutValue = getDX12(meshLayout.mStripCutValue);
            desc.PrimitiveTopologyType = getDX12(meshLayout.mPrimitiveTopologyType);
        } else {
            desc.InputLayout = {};
            desc.IBStripCutValue = getDX12(subpassData.mInputLayout.mStripCutValue);
            desc.PrimitiveTopologyType = getDX12(subpassData.mInputLayout.mPrimitiveTopologyType);
        }

        // Render Graph
        desc.NumRenderTargets = (uint32_t)renderSubpass.mOutputAttachments.size();
        for (size_t i = 0; i != renderSubpass.mOutputAttachments.size(); ++i) {
            auto rtvID = renderSubpass.mOutputAttachments[i].mDescriptor.mHandle;
            desc.RTVFormats[i] = getDXGIFormat(renderSolution.mRTVs[rtvID].mFormat);
        }
        if (renderSubpass.mDepthStencilAttachment) {
            auto dsvID = renderSubpass.mDepthStencilAttachment->mDescriptor.mHandle;
            desc.DSVFormat = getDXGIFormat(renderSolution.mDSVs[dsvID].mFormat);
            Expects(desc.DepthStencilState.DepthEnable);
        }
        desc.SampleDesc = renderSubpass.mSampleDesc;

        // Create PSO
        V(pDevice->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(state.mObject.put())));
    }

    pElemDescs.release();
    mr->release();
}

std::pair<DX12ShaderData*, bool> try_createDX12ShaderData(CreationContext& context,
    const DX12RenderGraphData& rg, DX12Resources& resources, const MetaID& metaID, bool async
) {
    bool created = false;
    auto iter = resources.mShaders.find(metaID);
    if (iter != resources.mShaders.end()) {

    } else {
        std::tie(iter, created) = resources.mShaders.emplace(metaID);
        Ensures(created);
        auto& shader = const_cast<DX12ShaderData&>(*iter);
        /*resources.mShaders.modify(iter, [&](DX12ShaderData& shader) */{
            shader.mShaderData.reset(metaID, async);
            if (!async) {
                Ensures(shader.mShaderData);
                const auto& prototypeData = *shader.mShaderData;
                auto& prototype = shader;
                resizeData(prototype, prototypeData);
                reserveIndex(prototype);
                createIndex(prototype, prototypeData, rg.mRenderGraph);
                Expects(prototype.mSolutions.size() == prototypeData.mSolutions.size());
                for (auto&& [solution, solutionData] : boost::combine(prototype.mSolutions, prototypeData.mSolutions)) {
                    const auto& renderSolution = rg.mRenderGraph.mSolutions.at(rg.mRenderGraph.mSolutionIndex.at(solutionData.first));
                    for (auto&& [pipeline, pipelineData] : boost::combine(solution.mPipelines, solutionData.second.mPipelines)) {
                        const auto& renderPipeline = renderSolution.mPipelines.at(renderSolution.mPipelineIndex.at(pipelineData.first));
                        for (auto&& [queue, queueData] : boost::combine(pipeline.mQueues, pipelineData.second.mQueues)) {
                            const auto& passDesc = renderPipeline.mSubpassIndex.at(queueData.first);
                            const auto& renderPass = renderPipeline.mPasses.at(passDesc.mPassID);
                            const auto& renderSubpass = renderPass.mGraphicsSubpasses.at(passDesc.mSubpassID);
                            for (auto&& [level, levelData] : boost::combine(queue.mLevels, queueData.second.mLevels)) {
                                for (auto&& [variant, variantData] : boost::combine(level.mPasses, levelData.mPasses)) {
                                    for (auto&& [subpass, subpassData0] : boost::combine(variant.mSubpasses, variantData.second.mSubpasses)) {
                                        createShaderResources(renderSolution, renderSubpass,
                                            subpass, subpassData0, resources.mSettings, context.mDevice, context.mMemoryArena);
                                    }
                                }
                            }
                        }
                    }
                }
            } // if async
        }/*);*/
    }
    return { const_cast<DX12ShaderData*>(&*iter), created };
}

void buildDX12MaterialShaderDescriptors(ID3D12Device* pDevice, DX12ShaderDescriptorHeap* pHeap,
    const DX12Resources& resources,
    const DX12MaterialData& material,
    const ShaderDescriptorCollection& collection,
    DX12ShaderDescriptorCollection& dx12Collection
) {
    dx12Collection.mIndex = collection.mIndex;
    dx12Collection.mResourceViewLists.reserve(collection.mResourceViewLists.size());
    dx12Collection.mSamplerLists.reserve(collection.mSamplerLists.size());

    for (const auto& list : collection.mResourceViewLists) {
        auto& dx12List = dx12Collection.mResourceViewLists.emplace_back();
        dx12List.mSlot = list.mSlot;
        Expects(list.mCapacity);
        dx12List.mCapacity = list.mCapacity;
        if (std::holds_alternative<Persistent_>(collection.mIndex.mPersistency)) {
            auto descs = pHeap->allocatePersistent(dx12List.mCapacity);
            dx12List.mGpuOffset = descs.first.mGpuHandle;
            dx12List.mCpuOffset = descs.first.mCpuHandle;
            uint32_t offset = 0;
            for (const auto& range : list.mRanges) {
                size_t i = 0;
                for (const auto& subrange : range.mSubranges) {
                    visit(overload(
                        [&](EngineSource_) {
                            for (const auto& attr : subrange.mDescriptors) {
                                ++i;
                                throw std::runtime_error("EngineSource Descriptor not supported yet");
                            }
                        },
                        [&](RenderTargetSource_) {
                            throw std::runtime_error("RenderTargetSource Descriptor not supported yet");
                        },
                        [&](MaterialSource_) {
                            for (const auto& attr : subrange.mDescriptors) {
                                auto visitor = overload(
                                    [&](Texture2D_) {
                                        const DX12TextureData* pTex = nullptr;
                                        auto iter = material.mMaterialData->mTextures.find(attr.mID);
                                        if (iter != material.mMaterialData->mTextures.end()) {
                                            const auto& texID = iter->second;
                                            for (const auto& tex : material.mTextures) {
                                                Expects(tex);
                                                if (texID == tex->mMetaID) {
                                                    pTex = tex.get();
                                                    break;
                                                }
                                            }
                                        } else {
                                            pTex = &resources.mDefaultTextures.at(White);
                                        }

                                        Expects(pTex);
                                        D3D12_SHADER_RESOURCE_VIEW_DESC viewDesc{
                                            pTex->mFormat,
                                            D3D12_SRV_DIMENSION_TEXTURE2D,
                                            D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
                                        };

                                        viewDesc.Texture2D = D3D12_TEX2D_SRV{ 0, (uint32_t)-1, 0, 0.f };

                                        pDevice->CreateShaderResourceView(pTex->mTexture.get(),
                                            &viewDesc, descs[i].mCpuHandle);
                                    },
                                    [&](auto) {
                                        throw std::runtime_error("currently only support Texture2D");
                                    }
                                );

                                visit(overload(
                                    [&](std::monostate) {
                                        visit(visitor, attr.mAttributeType);
                                    },
                                    [&](Descriptor::MainTex_ t) {
                                        visit(visitor, attr.mAttributeType);
                                    },
                                    [&](Descriptor::ConstantBuffer_) {
                                    },
                                    [&](Descriptor::PointSampler_) {
                                    },
                                    [&](Descriptor::LinearSampler_) {
                                    }
                                ), attr.mDataType);
                                ++i;
                            }
                        }
                    ), subrange.mSource);
                }
                {
                    // Set Null
                    D3D12_SHADER_RESOURCE_VIEW_DESC viewDesc{
                        DXGI_FORMAT_R8G8B8A8_UNORM,
                        D3D12_SRV_DIMENSION_TEXTURE2D,
                        D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
                    };
                    viewDesc.Texture2D = D3D12_TEX2D_SRV{ 0, (uint32_t)-1, 0, 0.f };
                    for (; i != range.mCapacity; ++i) {
                        pDevice->CreateShaderResourceView(nullptr,
                            &viewDesc, descs[i].mCpuHandle);
                    }
                }
                offset += range.mCapacity;
            }
            for (const auto& unbounded : list.mUnboundedDescriptors) {
                throw std::runtime_error("material resource view list unbounded not supported yet");
            }
        } else {
            dx12List.mRanges = list.mRanges;
        }
    }
    for (const auto& list : collection.mSamplerLists) {
        auto& dx12List = dx12Collection.mSamplerLists.emplace_back();
        throw std::runtime_error("material sampler list not supported yet");
    }
}

std::pair<DX12MaterialData*, bool> try_createDX12MaterialData(CreationContext& context,
    const DX12RenderGraphData& rg, DX12Resources& resources, const MetaID& metaID, bool async
) {
    bool created = false;
    auto iter = resources.mMaterials.find(metaID);
    if (iter != resources.mMaterials.end()) {

    } else {
        std::tie(iter, created) = resources.mMaterials.emplace(metaID);
        Ensures(created);
        auto& material = const_cast<DX12MaterialData&>(*iter);

        /*resources.mMaterials.modify(iter, [&](DX12MaterialData& material) */{
            material.mMaterialData.reset(metaID, async);
            if (!async) {
                Ensures(material.mMaterialData);
                const auto& materialData = *material.mMaterialData;
                const auto& shaderID = rg.mShaderIndex.at(materialData.mShader);
                material.mShader = try_createDX12ShaderData(context, rg, resources, shaderID, async).first;
                material.mDescriptorHeap = context.mDescriptorHeap;

                material.mTextures.clear();
                material.mTextures.reserve(material.mMaterialData->mTextures.size());
                for (const auto& texture : material.mMaterialData->mTextures) {
                    material.mTextures.emplace_back(try_createDX12TextureData(context, resources, texture.second, async).first);
                }

                material.mShaderData.reserve(material.mShader->mSolutions.size());
                for (size_t solutionID = 0; solutionID != material.mShader->mSolutions.size(); ++solutionID) {
                    const auto& solution = material.mShader->mSolutions[solutionID];
                    auto& materialSolution = material.mShaderData.emplace_back();

                    materialSolution.mPipelines.reserve(solution.mPipelines.size());
                    for (size_t pipelineID = 0; pipelineID != solution.mPipelines.size(); ++pipelineID) {
                        const auto& pipeline = solution.mPipelines[pipelineID];
                        auto& materialPipeline = materialSolution.mPipelines.emplace_back();

                        materialPipeline.mQueues.reserve(pipeline.mQueues.size());
                        for (size_t queueID = 0; queueID != pipeline.mQueues.size(); ++queueID) {
                            const auto& queue = pipeline.mQueues[queueID];
                            auto& materialQueue = materialPipeline.mQueues.emplace_back();

                            materialQueue.mLevels.reserve(queue.mLevels.size());
                            for (size_t levelID = 0; levelID != queue.mLevels.size(); ++levelID) {
                                const auto& level = queue.mLevels[levelID];
                                auto& materialLevel = materialQueue.mLevels.emplace_back();

                                materialLevel.mPasses.reserve(level.mPasses.size());
                                for (size_t variantID = 0; variantID != level.mPasses.size(); ++variantID) {
                                    const auto& variant = level.mPasses[variantID];
                                    auto& materialVariant = materialLevel.mPasses.emplace_back();

                                    materialVariant.mSubpasses.reserve(variant.mSubpasses.size());
                                    for (size_t passID = 0; passID != variant.mSubpasses.size(); ++passID) {
                                        const auto& pass = variant.mSubpasses[passID];
                                        auto& materialPass = materialVariant.mSubpasses.emplace_back();
                                        
                                        materialPass.mCollections.reserve(pass.mDescriptors.size());
                                        for (const auto& collection : pass.mDescriptors) {
                                            Expects(collection.mIndex.mUpdate <= UpdateEnum::PerBatch);
                                            auto& materialCollection = materialPass.mCollections.emplace_back();
                                            buildDX12MaterialShaderDescriptors(context.mDevice, context.mDescriptorHeap,
                                                resources, material, collection, materialCollection);
                                        }
                                    } // subpasses
                                } // passes
                            } // level
                        } // queue
                    } // pipeline
                } // solution
            }
        }/*);*/
    }

    return { const_cast<DX12MaterialData*>(&*iter), created };
}

void buildDX12GraphicsSubpassShaderDescriptors(ID3D12Device* pDevice, DX12ShaderDescriptorHeap* pHeap,
    const DX12RenderWorks& renderGraph,
    const DX12RenderSolution& renderSolution,
    const ShaderDescriptorCollection& collection,
    DX12ShaderDescriptorCollection& dx12Collection
) {
    dx12Collection.mIndex = collection.mIndex;
    dx12Collection.mResourceViewLists.reserve(collection.mResourceViewLists.size());
    dx12Collection.mSamplerLists.reserve(collection.mSamplerLists.size());

    for (const auto& list : collection.mResourceViewLists) {
        auto& dx12List = dx12Collection.mResourceViewLists.emplace_back();
        dx12List.mSlot = list.mSlot;
        Expects(list.mCapacity);
        dx12List.mCapacity = list.mCapacity;
        dx12List.mRanges = list.mRanges;

        visit(overload(
            [&](Persistent_) {
                uint32_t offset = 0;
                for (const auto& range : list.mRanges) {
                    for (const auto& subrange : range.mSubranges) {
                        size_t i = 0;
                        visit(overload(
                            [&](EngineSource_) {
                                for (const auto& attr : subrange.mDescriptors) {
                                    if (std::holds_alternative<SamplerState_>(attr.mAttributeType)) {
                                        throw std::runtime_error("resource view should not have samplers");
                                    } else if (!isConstant(attr.mAttributeType)) {
                                        throw std::runtime_error("GraphicsSubpass EngineSource Descriptor not supported yet");
                                    } else {
                                        throw std::runtime_error("descriptor should not be constant");
                                    }
                                }
                            },
                            [&](RenderTargetSource_) {
                                for (const auto& attr : subrange.mDescriptors) {
                                    ++i;
                                }
                            },
                            [&](MaterialSource_) {
                                throw std::runtime_error("GraphicsSubpass MaterialSource Descriptor not supported yet");
                            }
                        ), subrange.mSource);
                        Ensures(i == subrange.mDescriptors.size());
                        offset += gsl::narrow_cast<uint32_t>(subrange.mDescriptors.size());
                    }
                }

                if (collection.mIndex.mUpdate >= PerPass) {
                    Ensures(offset == dx12List.mCapacity);
                } else {
                    Ensures(offset == 0);
                }

                for (const auto& unbounded : list.mUnboundedDescriptors) {
                    throw std::runtime_error("material resource view list unbounded not supported yet");
                }
            },
            [&](Dynamic_) {
                // do nothing
            }
        ), collection.mIndex.mPersistency);
    }

    for (const auto& list : collection.mSamplerLists) {
        auto& dx12List = dx12Collection.mSamplerLists.emplace_back();
        dx12List.mSlot = list.mSlot;
        Expects(list.mCapacity);
        dx12List.mCapacity = list.mCapacity;
        dx12List.mRanges = list.mRanges;
        visit(overload(
            [&](Persistent_) {
                for (const auto& range : list.mRanges) {
                    if (std::holds_alternative<SSV_>(range.mType)) {
                        continue;
                    }
                    throw std::runtime_error("GraphicsSubpass sampler list not supported yet");
                }
                for (const auto& unbounded : list.mUnboundedDescriptors) {
                    throw std::runtime_error("material resource view list unbounded not supported yet");
                }
            },
            [&](Dynamic_) {
                // do nothing
            }
        ), collection.mIndex.mPersistency);
    }
}

std::pair<DX12RenderGraphData*, bool> try_createDX12RenderGraphData(CreationContext& context,
    DX12Resources& resources, const MetaID& metaID, bool async
) {
    bool created = false;
    auto iter = resources.mRenderGraphs.find(metaID);
    if (iter != resources.mRenderGraphs.end()) {
        // do nothing
    } else {
        std::tie(iter, created) = resources.mRenderGraphs.emplace(metaID);
        Ensures(created);
        DX12RenderGraphData& render = const_cast<DX12RenderGraphData&>(*iter);
        render.mDescriptorHeap = context.mDescriptorHeap;

        /*resources.mRenderGraphs.modify(iter, [&](DX12RenderGraphData& render)*/ {
            // render graph is always sync loaded
            render.mRenderGraphData.reset(metaID, false);
            
            Ensures(render.mRenderGraphData);
            auto& renderData = *render.mRenderGraphData;
            render.mShaderIndex = renderData.mShaderIndex;
            const auto& sc = renderData.mRenderGraph;

            render.mRenderGraph.mSolutions.reserve(sc.mSolutions.size());
            render.mRenderGraph.mFramebuffers.resize(sc.mNumReserveFramebuffers);
            render.mRenderGraph.mDSVs.resize(context.mDevice, sc.mNumReserveDSVs);
            render.mRenderGraph.mRTVs.resize(context.mDevice, sc.mNumReserveRTVs);
            render.mRenderGraph.mCBV_SRV_UAVs.resize(context.mDevice, sc.mNumReserveCBV_SRV_UAVs);
            render.mRenderGraph.mNumBackBuffers = sc.mNumBackBuffers;
            render.mRenderGraph.mSolutionIndex = sc.mSolutionIndex;

            for (const auto& solutionData : sc.mSolutions) {
                auto& solution = render.mRenderGraph.mSolutions.emplace_back();

                solution.mPipelines.reserve(solutionData.mPipelines.size());
                solution.mRTVSources = solutionData.mRTVSources;
                solution.mDSVSources = solutionData.mDSVSources;
                solution.mCBVSources = solutionData.mCBVSources;
                solution.mSRVSources = solutionData.mSRVSources;
                solution.mUAVSources = solutionData.mUAVSources;
                solution.mFramebuffers = solutionData.mFramebuffers;
                solution.mRTVs = solutionData.mRTVs;
                solution.mDSVs = solutionData.mDSVs;
                solution.mCBVs = solutionData.mCBVs;
                solution.mSRVs = solutionData.mSRVs;
                solution.mUAVs = solutionData.mUAVs;
                solution.mAttributeIndex = solutionData.mAttributeIndex;
                solution.mPipelineIndex = solutionData.mPipelineIndex;

                for (const auto& pipelineData : solutionData.mPipelines) {
                    auto& pipeline = solution.mPipelines.emplace_back();
                    pipeline.mPasses.reserve(pipelineData.mPasses.size());
                    pipeline.mDependencies = pipelineData.mDependencies;
                    pipeline.mRTVInitialStates = pipelineData.mRTVInitialStates;
                    pipeline.mDSVInitialStates = pipelineData.mDSVInitialStates;
                    pipeline.mSubpassIndex = pipelineData.mSubpassIndex;

                    for (const auto& passData : pipelineData.mPasses) {
                        auto& pass = pipeline.mPasses.emplace_back();
                        pass.mGraphicsSubpasses.reserve(passData.mGraphicsSubpasses.size());
                        pass.mViewports = passData.mViewports;
                        pass.mScissorRects = passData.mScissorRects;
                        pass.mFramebuffers = passData.mFramebuffers;
                        pass.mDependencies = passData.mDependencies;
                        
                        for (const auto& subpassData : passData.mGraphicsSubpasses) {
                            auto& subpass = pass.mGraphicsSubpasses.emplace_back();
                            subpass.mSampleDesc = getDXGI(subpassData.mSampleDesc);
                            subpass.mInputAttachments = subpassData.mInputAttachments;
                            subpass.mOutputAttachments = subpassData.mOutputAttachments;
                            subpass.mResolveAttachments = subpassData.mResolveAttachments;
                            subpass.mDepthStencilAttachment = subpassData.mDepthStencilAttachment;
                            subpass.mPreserveAttachments = subpassData.mPreserveAttachments;
                            subpass.mPostViewTransitions = subpassData.mPostViewTransitions;
                            subpass.mConstantBuffers = subpassData.mConstantBuffers;

                            subpass.mDescriptors.reserve(subpassData.mDescriptors.size());
                            for (const auto& collection : subpassData.mDescriptors) {
                                auto& dx12Collection = subpass.mDescriptors.emplace_back();
                                buildDX12GraphicsSubpassShaderDescriptors(context.mDevice, context.mDescriptorHeap,
                                    render.mRenderGraph, solution, collection, dx12Collection);
                            }

                            if (!subpassData.mRootSignature.empty()) {
                                V(context.mDevice->CreateRootSignature(0,
                                    subpassData.mRootSignature.data(),
                                    subpassData.mRootSignature.size(),
                                    IID_PPV_ARGS(subpass.mRootSignature.put())));
                            }
                        }
                    }
                }
            }
        }/*);*/

        DX12RenderGraphData& render2 = const_cast<DX12RenderGraphData&>(*iter);

        /*resources.mRenderGraphs.modify(iter, [&](DX12RenderGraphData& render2) */{
            Ensures(render2.mRenderGraphData);
            auto& renderData = *render2.mRenderGraphData;
            const auto& sc = renderData.mRenderGraph;

            Expects(render2.mRenderGraph.mSolutions.size() == sc.mSolutions.size());
            uint32_t solutionID = 0;
            for (auto&& [solution, solutionData] : boost::combine(render2.mRenderGraph.mSolutions, sc.mSolutions)) {
                Expects(solution.mPipelines.size() == solutionData.mPipelines.size());
                uint32_t pipelineID = 0;
                for (auto&& [pipeline, pipelineData] : boost::combine(solution.mPipelines, solutionData.mPipelines)) {
                    auto currentSolutionId = at(sc.mSolutionIndex, context.mCurrentSolution);
                    if (solutionID != currentSolutionId)
                        continue;

                    auto currentPipelineID = at(solutionData.mPipelineIndex, context.mCurrentPipeline);
                    if (pipelineID != currentPipelineID)
                        continue;

                    Expects(pipeline.mPasses.size() == pipelineData.mPasses.size());
                    for (auto&& [pass, passData] : boost::combine(pipeline.mPasses, pipelineData.mPasses)) {
                        Expects(pass.mGraphicsSubpasses.size() == passData.mGraphicsSubpasses.size());
                        for (auto&& [subpass, subpassData] : boost::combine(pass.mGraphicsSubpasses, passData.mGraphicsSubpasses)) {
                            subpass.mOrderedRenderQueue.reserve(subpassData.mOrderedRenderQueue.size());
                            for (const auto& unorderedQueueData : subpassData.mOrderedRenderQueue) {
                                auto& unorderedQueue = subpass.mOrderedRenderQueue.emplace_back();
                                unorderedQueue.mContents.reserve(unorderedQueueData.mContents.size());
                                for (const auto& contentID : unorderedQueueData.mContents) {
                                    try_createDX12(context, resources, contentID, Core::Content, async);
                                    unorderedQueue.mContents.emplace_back(boost::intrusive_ptr<DX12ContentData>(
                                        const_cast<DX12ContentData*>(&at(resources.mContents, contentID))));
                                }
                            }
                        }
                    }
                    ++pipelineID;
                }
                ++solutionID;
            }

            render2.mRenderGraphData.reset();
        }/*);*/
    }

    return { const_cast<DX12RenderGraphData*>(&*iter), created };
}

}

bool try_createDX12(CreationContext& context, DX12Resources& resources, const MetaID& metaID,
    Core::ResourceType tag, bool async
) {
    Expects(!metaID.is_nil());
    return visit(overload(
        [&](Core::Mesh_) {
            return try_createDX12MeshData(context, resources, metaID, async).second;
        },
        [&](Core::Texture_) {
            return try_createDX12TextureData(context, resources, metaID, async).second;
        },
        [&](Core::Shader_) {
            auto iter = resources.mRenderGraphs.find(context.mRenderGraph);
            Expects(iter != resources.mRenderGraphs.end());
            return try_createDX12ShaderData(context, *iter, resources, metaID, async).second;
        },
        [&](Core::Material_) {
            auto iter = resources.mRenderGraphs.find(context.mRenderGraph);
            Expects(iter != resources.mRenderGraphs.end());
            return try_createDX12MaterialData(context, *iter, resources, metaID, async).second;
        },
        [&](Core::Content_) {
            auto res = resources.mContents.emplace(metaID);
            if (res.second) {
                const auto& metaID2 = res.first->mMetaID;
                Expects(res.first->mMetaID == metaID);
                auto& content = const_cast<DX12ContentData&>(*res.first);

                /*resources.mContents.modify(res.first, [&](DX12ContentData& content) */{
                    content.mContentData.reset(metaID, async);
                    if (!async) {
                        auto iter = resources.mRenderGraphs.find(context.mRenderGraph);
                        Expects(iter != resources.mRenderGraphs.end());

                        Ensures(content.mContentData);
                        const auto& contentData = *content.mContentData;
                        content.mIDs = contentData.mIDs;
                        content.mDrawCalls.reserve(contentData.mDrawCalls.size());
                        content.mFlattenedObjects.reserve(contentData.mFlattenedObjects.size());
                        for (const auto& data : contentData.mDrawCalls) {
                            auto& dc = content.mDrawCalls.emplace_back();
                            dc.mType = data.mType;
                            // mesh
                            if (data.mMesh.is_nil()) {
                                dc.mMesh = nullptr;
                            } else {
                                dc.mMesh = try_createDX12MeshData(context, resources, data.mMesh, async).first;
                            }
                            dc.mMaterial = try_createDX12MaterialData(context, *iter, resources, data.mMaterial, async).first;
                        }
                        for (const auto& data : contentData.mFlattenedObjects) {
                            auto& object = content.mFlattenedObjects.emplace_back();
                            object.mWorldTransforms = data.mWorldTransforms;
                            object.mWorldTransformInvs = data.mWorldTransformInvs;
                            object.mBoundingBoxes = data.mBoundingBoxes;
                            object.mMeshRenderers.reserve(data.mMeshRenderers.size());
                            for (const auto& rendererData : data.mMeshRenderers) {
                                auto& renderer = object.mMeshRenderers.emplace_back();
                                renderer.mMesh = try_createDX12MeshData(context, resources, rendererData.mMeshID, async).first;
                                renderer.mMaterials.reserve(rendererData.mMaterialIDs.size());
                                for (const auto& materialID : rendererData.mMaterialIDs) {
                                    renderer.mMaterials.emplace_back(
                                        try_createDX12MaterialData(context, *iter, resources, materialID, async).first);
                                }
                            }
                        }
                    }
                }/*);*/

                return true;
            } else {
                auto& content = *res.first;
                Expects(content.mContentData.valid());
                Expects(content.mContentData.metaID() == metaID);
                return false;
            }
        },
        [&](Core::RenderGraph_) {
            return try_createDX12RenderGraphData(context, resources, metaID, async).second;
        }
    ), tag);
}

}
