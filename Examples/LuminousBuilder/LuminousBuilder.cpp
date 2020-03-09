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

#include <StarCompiler/RenderGraph/SRenderGraph.h>
#include <StarCompiler/RenderGraph/SRenderGraphDSL.h>
#include <StarCompiler/RenderGraph/SRenderGraphFactory.h>
#include <StarCompiler/ShaderGraph/SShaderSemantics.h>
#include <StarCompiler/ShaderGraph/SShaderGroups.h>
#include <StarCompiler/ShaderGraph/SShaderModules.h>
#include <StarCompiler/ShaderWorks/SBasicModules.h>
#include <StarCompiler/ShaderWorks/SStarModules.h>
#include <StarCompiler/ShaderWorks/SShaderCompiler.h>
#include <StarCompiler/ShaderWorks/SShaderAssetBuilder.h>
#include <Star/Graphics/SRenderSerialization.h>
#include <Star/Graphics/SRenderGraphSerialization.h>
#include <Star/Graphics/SContentSerialization.h>
#include <Star/AssetFactory/SAssetFactory.h>
#include <StarCompiler/ShaderGraph/SShaderDSL.h>

using namespace Star;
using namespace Star::Graphics;
using namespace Star::Graphics::Render;
using namespace Star::Graphics::Render::Shader;
using namespace std::string_literals;

namespace {

ClearColor DefaultClearColor{ Float4(0.251f, 0.3137255f, 0.5529f, 1.0f) };
ClearColor AlbedoClearColor{ Float4{ 0.5f, 0.5f, 0.5f, 1.0f } };
ClearColor NormalClearColor{ Float4{ 0.5f, 0.5f, 1.0f, 0.0f } };
ClearColor ZeroClearColor{ Float4{ 0.0f, 0.0f, 0.0f, 0.0f } };

using Inputs = ResourceDataViewMap<RenderValue>;
using Outputs = ResourceDataViewMap<RenderValue>;
using Queue = std::vector<UnorderedRenderContent>;
using Unordered = UnorderedRenderContent;

}

void buildForwardSolution(RenderSolutionFactory& renderSolutionFactory) {
    RenderConfigs context{};
    context.mStrictLightingColorSpace = false;
    context.mVerbose = true;

    // Forward
    {
        GraphicsRenderNodeGraph graph{ "Diffuse", context };
        graph.mRenderTargets = {
            rt("Color", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, DefaultClearColor, Device, BackBuffer),
            ds("DepthStencil", Format::S_D24_UNORM_S8_UINT, Width{ 1280 }, Height{ 720 }),
        };

        NODE(Output,
            Outputs{
                { "Color", Present },
            }
        );

        NODE(Transparent,
            Outputs{
                { "Color", RenderTarget },
                { "DepthStencil", DepthRead },
            },
            Inputs{
                { "DepthStencil", DepthRead },
            }
        );

        NODE(Lighting,
            Outputs{
                { "Color", RenderTarget },
                { "DepthStencil", DepthWrite, ClearDepthStencil{} },
            }
        );

        CONNECT(Lighting, Transparent);
        CONNECT(Transparent, Output);

        graph.compile();

        renderSolutionFactory.addPipeline(std::move(graph));

        std::cout << std::endl;
    }
}

void buildDeferredSolution(RenderSolutionFactory& renderSolutionFactory) {
    RenderConfigs context{};
    context.mStrictLightingColorSpace = false;
    context.mVerbose = true;

    {
        GraphicsRenderNodeGraph graph{ "Diffuse", context };
        graph.mRenderTargets = {
            rt("Color", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, DefaultClearColor, Device, BackBuffer),
            ds("DepthStencil", Format::S_D24_UNORM_S8_UINT, Width{ 1280 }, Height{ 720 }),
            rt("Radiance", Format::S_R11G11B10_UFLOAT_PACK32, Width{ 1280 }, Height{ 720 }, ZeroClearColor),
            rt("BaseColor", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, AlbedoClearColor, Device),
            rt("Normal", Format::S_R8G8B8A8_UNORM, Width{ 1280 }, Height{ 720 }, NormalClearColor),
        };

        NODE(Output,
            Outputs{
                { "Color", Present },
            }
        );

        NODE(PostProcessing, /*Device,*/
            Outputs{
                { "Color", RenderTarget, DefaultClearColor },
            },
            Inputs{
                { "Radiance", ShaderResource },
            }
        );

        NODE(Lighting,
            Outputs{
                { "Radiance", RenderTarget, DontRead },
            },
            Inputs{
                { "BaseColor", ShaderResource },
                { "Normal", ShaderResource },
                { "DepthStencil", DepthRead },
            }
        );

        NODE(Geometry,
            Outputs{
                { "BaseColor", RenderTarget, AlbedoClearColor },
                { "Normal", RenderTarget, NormalClearColor },
                { "DepthStencil", DepthWrite, ClearDepthStencil() },
            }
        );

        CONNECT(PostProcessing, Output); 
        CONNECT(Lighting, PostProcessing);
        CONNECT(Geometry, Lighting);

        if (graph.compile()) {
            throw std::invalid_argument("Deferred pipline compile failed");
        }

        renderSolutionFactory.addPipeline(std::move(graph));

        std::cout << std::endl;
    }
}

std::string to_underscore(const std::string& name) {
    auto name2 = boost::algorithm::replace_all_copy(name, " ", "_");
    boost::algorithm::to_lower(name2);
    return name2;
}

int buildMainShaders(const ShaderModules& modules, ShaderDatabase& db) {
    using namespace Star::Graphics::Render::Shader::DSL;

    for (const auto& alphatest : { ""s, " AlphaTest"s }) {
        for (const auto& normalmap : { ""s, " NormalMap"s }) {
            Shader("Star/Diffuse" + normalmap + alphatest, "diffuse" + to_underscore(normalmap) + to_underscore(alphatest) + ".shader") {
                SinglePass("Forward", "Diffuse", "Lighting", 0) {
                    PixelShader({ "color", half4, SV_Target }) {
                        Group(EvaluateDirectionalLight);
                        Group(InitColor);
                        Group(NdotL);
                        //Group(VisualizeWorldNormal);
                        Group(DirectionalLight);
                        if (!normalmap.empty()) {
                            Group(TangentNormalToWorld);
                            Group(NormalMap);
                            Group(UnpackTangent, UnpackBinormal, UnpackNormal);
                        }
                        if (!alphatest.empty()) {
                            Group(AlphaTest);
                            Group(BaseColorAndTransparency);
                        } else {
                            Group(BaseColor);
                        }
                    }
                    VertexShader() {
                        if (!normalmap.empty()) {
                            Group(PackTangentSpace);
                            Group(CalculateWorldBinormal);
                            Group(WorldNormal, WorldTangent);
                        }
                        Group(ClipPos, WorldPos, WorldGeometryNormal, LocalTangent);
                    }
                }
                SinglePass("Deferred", "Diffuse", "Geometry", 0) {
                    PixelShader({ "color0", half4, SV_Target }, { "color1", half4, SV_Target }) {
                        Group(PackGBuffers);
                        if (!normalmap.empty()) {
                            Group(TangentNormalToWorld);
                            Group(NormalMap);
                            Group(UnpackTangent, UnpackBinormal, UnpackNormal);
                        }
                        if (!alphatest.empty()) {
                            Group(AlphaTest);
                            Group(BaseColorAndTransparency);
                        } else {
                            Group(BaseColor, InitTransparency);
                        }
                    }
                    VertexShader() {
                        if (!normalmap.empty()) {
                            Group(PackTangentSpace);
                            Group(CalculateWorldBinormal);
                            Group(WorldNormal, WorldTangent);
                        }
                        Group(ClipPos, WorldPos, WorldGeometryNormal, LocalTangent);
                    }
                }
            }
        }
    }

    Shader("Star/Fullscreen/Deferred Pipeline", "fullscreen-deferred_pipeline.shader") {
        SinglePass("Deferred", "Diffuse", "PostProcessing", 0) {

            Pass.mShaderState.mDepthStencilState.mDepthEnabled = false;
            Pass.mShaderState.mDepthStencilState.mStencilEnable = false;

            PixelShader({ "color", half4, SV_Target }) {
                Group(CopyRadiance);
            }
            VertexShader() {
                Group(FullQuadClipPos, FullQuadUV);
            }
        }

        SinglePass("Deferred", "Diffuse", "Lighting", 0) {

            Pass.mShaderState.mDepthStencilState.mDepthEnabled = false;
            Pass.mShaderState.mDepthStencilState.mStencilEnable = false;

            PixelShader({ "color", half4, SV_Target }) {
                Group(EvaluateDirectionalLight);
                Group(InitColor);
                Group(NdotL);
                Group(DirectionalLight);
                Group(UnpackGBuffers);
            }
            VertexShader() {
                Group(FullQuadClipPos, FullQuadUV);
            }
        }
    }

    return 0;
}

int main() {
    std::cout << "---------------------------------------\n";
    std::cout << "create render graph2\n";
    std::cout << "---------------------------------------\n";

    try {
        Asset::AssetFactory factory("../../../deploy/asset", "../../../deploy/windows2",
            std::pmr::get_default_resource());
        
        auto& modules = factory.getShaderModules();
        createBasicModules(modules);

        // cleanup meta files
        factory.cleanup();

        // read asset info
        factory.scan();

        // import assets
        factory.processAssets();

        // build render graph
        std::string_view renderGraphAsset = "main.1280x720.render";
        std::string_view renderGraphShaderFolder = "main/shaders";
        factory.try_createRenderGraph(renderGraphAsset, "main", 1280, 720);

        factory.editRenderGraph(renderGraphAsset, renderGraphShaderFolder);
        { // Forward Solution
            auto res = factory.try_createRenderSolution(renderGraphAsset, "Forward");
            Ensures(res.second);
            buildForwardSolution(res.first);

        }
        { // Deferred solution
            auto res = factory.try_createRenderSolution(renderGraphAsset, "Deferred");
            Ensures(res.second);
            buildDeferredSolution(res.first);
        }

        auto& shaders = factory.setupRenderGraph(renderGraphAsset);

        // bind shaders
        buildMainShaders(modules, shaders);

        // save render graph
        factory.saveRenderGraph(renderGraphAsset);

        // build contents
        factory.try_createContent("scene/sponza.content");
        factory.clearContent("scene/sponza.content");
        factory.contentInstantiateFlattenedObjects("scene/sponza.content", "model/scene/sponza_pbr.fbx");
        factory.saveContent("scene/sponza.content");

        factory.try_createMaterial("scene/deferred_pipeline.material", "Star/Fullscreen/Deferred Pipeline");

        factory.try_createContent("scene/deferred_pipeline.content");
        factory.clearContent("scene/deferred_pipeline.content");
        factory.contentAddFullscreenTriangle("scene/deferred_pipeline.content", "scene/deferred_pipeline.material");
        factory.saveContent("scene/deferred_pipeline.content");

        // add contents
        factory.addContent("scene/sponza.content", renderGraphAsset, "Forward", "Diffuse", "Lighting");
        factory.addContent("scene/sponza.content", renderGraphAsset, "Deferred", "Diffuse", "Geometry");
        factory.addContent("scene/deferred_pipeline.content", renderGraphAsset, "Deferred", "Diffuse", "Lighting");
        factory.addContent("scene/deferred_pipeline.content", renderGraphAsset, "Deferred", "Diffuse", "PostProcessing");

        factory.build();
    } catch (std::invalid_argument & e) {
        {
            CONSOLE_COLOR(Red);
            std::cout << "[error] ";
        }
        std::cout << e.what() << std::endl;
        return 1;
    }

    CONSOLE_COLOR(Green);
    std::cout << "[succeeded]";

    return 0;
}
