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

#include "SBuildShaders.h"

using namespace Star;
using namespace Star::Graphics;
using namespace Star::Graphics::Render;
using namespace Star::Graphics::Render::Shader;
using namespace Star::Graphics::Render::Shader::DSL;

void buildForwardSolution(RenderSolutionFactory& renderSolutionFactory) {
    boost::uuids::name_generator_sha1 gen(boost::uuids::ns::oid());
    using Inputs = ResourceDataViewMap<RenderValue>;
    using Outputs = ResourceDataViewMap<RenderValue>;
    using Queue = std::vector<UnorderedRenderContent>;
    using Unordered = UnorderedRenderContent;

    RenderConfigs context{};
    context.mStrictLightingColorSpace = false;
    context.mVerbose = true;

    ClearColor DefaultClearColor{ Float4(0.251f, 0.3137255f, 0.5529f, 1.0f) };
    ClearColor AlbedoClearColor{ Float4{ 0.5f, 0.5f, 0.5f, 1.0f } };
    ClearColor NormalClearColor{ Float4{ 0.5f, 0.5f, 1.0f, 0.0f } };
    ClearColor ZeroClearColor{ Float4{ 0.0f, 0.0f, 0.0f, 0.0f } };

    //// Image Effects
    //{
    //    GraphicsRenderNodeGraph graph{ "ImageEffects", context };
    //    graph.mRenderTargets = {
    //        rt("Color", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, DefaultClearColor, Device, BackBuffer),
    //    };

    //    NODE(Output,
    //        Outputs{
    //            present("Color"),
    //        }
    //    );

    //    NODE(Color,
    //        Outputs{
    //            rtv("Color", DefaultClearColor),
    //        },
    //        Queue{
    //            Unordered{
    //                { gen("Contents/Pipeline") },
    //            },
    //        }
    //    );

    //    CONNECT(Color, Output);

    //    graph.compile();

    //    renderSolutionFactory.addPipeline(std::move(graph));

    //    std::cout << std::endl;
    //}

    // Forward
    {
        GraphicsRenderNodeGraph graph{ "Diffuse", context };
        graph.mRenderTargets = {
            rt("Color", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, DefaultClearColor, Device, BackBuffer),
            ds("DepthStencil", Format::S_D24_UNORM_S8_UINT, Width{ 1280 }, Height{ 720 }),
        };

        NODE(Output,
            Outputs{
                present("Color"),
            }
        );

        //NODE(Transparent,
        //    Outputs{
        //        rtv("Color"),
        //        dsv_readonly("DepthStencil", Load),
        //    },
        //    Inputs{
        //        srv_depth("DepthStencil"),
        //    }
        //);

        NODE(Lighting,
            Outputs{
                rtv("Color", DefaultClearColor),
                dsv("DepthStencil", ClearDepthStencil()),
            }
        );

        //CONNECT(Lighting, Transparent);
        CONNECT(Lighting, Output);

        graph.compile();

        renderSolutionFactory.addPipeline(std::move(graph));

        std::cout << std::endl;
    }

    //// Deferred
    //{
    //    GraphicsRenderNodeGraph graph{ "Deferred", context };
    //    graph.mRenderTargets = {
    //        rt("Color", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, DefaultClearColor, Device, BackBuffer),
    //        ds("DepthStencil", Format::S_D24_UNORM_S8_UINT, Width{ 1280 }, Height{ 720 }),
    //        rt("Radiance", Format::S_R11G11B10_UFLOAT_PACK32, Width{ 1280 }, Height{ 720 }, ZeroClearColor),
    //        rt("Albedo", Format::S_R8G8B8A8_SRGB, Width{ 1280 }, Height{ 720 }, AlbedoClearColor, Device),
    //        rt("Normal", Format::S_R8G8B8A8_UNORM, Width{ 1280 }, Height{ 720 }, NormalClearColor),
    //    };

    //    NODE(Output,
    //        Outputs{
    //            present("Color"),
    //        }
    //    );

    //    NODE(PostProcessing, /*Device,*/
    //        Outputs{
    //            rtv("Color", DefaultClearColor),
    //        },
    //        Inputs{
    //            srv("Radiance"),
    //        },
    //        Queue{
    //            Unordered{
    //                { gen("Contents/Pipeline") },
    //            },
    //        }
    //    );

    //    NODE(Lighting,
    //        Outputs{
    //            rtv("Radiance", DontRead),
    //        },
    //        Inputs{
    //            srv("Albedo"),
    //            srv("Normal"),
    //            srv_depth("DepthStencil"),
    //        },
    //        Queue{
    //            Unordered{
    //                { gen("Contents/Pipeline") },
    //            },
    //        }
    //    );

    //    NODE(Geometry,
    //        Outputs{
    //            rtv("Albedo", AlbedoClearColor),
    //            rtv("Normal", NormalClearColor),
    //            dsv("DepthStencil", ClearDepthStencil()),
    //        }
    //    );

    //    CONNECT(PostProcessing, Output); 
    //    CONNECT(Lighting, PostProcessing);
    //    CONNECT(Geometry, Lighting);

    //    if (graph.compile()) {
    //        throw std::invalid_argument("Deferred pipline compile failed");
    //    }

    //    renderSolutionFactory.addPipeline(std::move(graph));

    //    std::cout << std::endl;
    //}
}

void buildMaterials(Resources& resources) {
    //boost::uuids::name_generator_sha1 gen(boost::uuids::ns::oid());

    //MetaID pipelineID = gen("Materials/Pipeline");

    //auto res = resources.mMaterials.emplace(std::piecewise_construct,
    //    std::forward_as_tuple(pipelineID), std::forward_as_tuple());
    //Ensures(res.second);

    //auto& mat = res.first->second;
    //mat.mShader = "Star/RenderPipeline";
}

int buildForwardShaders(const ShaderModules& modules, ShaderDatabase& db) {
    //Shader("Star/RenderPipeline") {
    //    SinglePass("Forward", "Forward", "Lighting", 0) {
    //        PixelShader({ "color", half4, SV_Target }) {
    //            Group(VisualizeWorldNormal)
    //        }

    //        VertexShader() {
    //            Group(ClipPos, WorldPos, WorldGeometryNormal)
    //        }
    //    }
    //    SinglePass("Desktop", "Deferred", "Lighting", 0) {
    //        PixelShader({ "color", half4, SV_Target }) {
    //            Group(DeferredLambertian);
    //            Group(UnpackGBuffers);
    //        }

    //        VertexShader() {
    //            Group(FullQuadClipPos, FullQuadUV);
    //        }
    //    }
    //    SinglePass("Desktop", "Deferred", "PostProcessing", 0) {
    //        PixelShader({ "color", half4, SV_Target }) {
    //            Group(CopyRadiance);
    //        }

    //        VertexShader() {
    //            Group(FullQuadClipPos, FullQuadUV);
    //        }
    //    }
    //}

    Shader("Star/Diffuse", "diffuse.shader") {
        SinglePass("Forward", "Diffuse", "Lighting", 0) {
            PixelShader({ "color", half4, SV_Target }) {
                Node(OutputAlbedo, Inline,
                    Outputs{
                        { "color", half4 },
                    },
                    Inputs{
                        { "baseColor", half3  },
                        { "transparency", half1 },
                    },
                    Content{ R"(color = half4(baseColor, transparency);
)" });
                Group(BaseColorAndTransparency);
            }
            VertexShader() {
                Group(ClipPos, WorldPos, WorldGeometryNormal);
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

        // add Forward render graph
        factory.editRenderGraph(renderGraphAsset, renderGraphShaderFolder);
        auto res = factory.try_createRenderSolution(renderGraphAsset, "Forward");
        Ensures(res.second);
        buildForwardSolution(res.first);
        auto& shadersForward = factory.setupRenderGraph(renderGraphAsset);
        // add shaders
        buildForwardShaders(modules, shadersForward);

        // save render graph
        factory.saveRenderGraph(renderGraphAsset);

        // build contents
        factory.try_createContent("scene/sponza.content");
        factory.clearContent("scene/sponza.content");
        factory.contentInstantiateFlattenedObjects("scene/sponza.content", "model/scene/sponza_pbr.fbx");
        factory.saveContent("scene/sponza.content");

        // add contents
        factory.addContent("scene/sponza.content", renderGraphAsset, "Forward", "Diffuse", "Lighting");

        factory.build();
    } catch (std::invalid_argument & e) {
        {
            CONSOLE_COLOR(Red);
            std::cout << "[error] ";
        }
        std::cout << e.what() << std::endl;
        return 1;
    }

    //try {
    //    RenderSolutionFactory renderSolutionFactory("Desktop");
    //    buildForwardSolution(renderSolutionFactory);

    //    ShaderModules modules;
    //    createBasicModules(modules);

    //    ShaderDatabase shaderDB;
    //    buildTestShaders(modules, shaderDB);

    //    ShaderGroups shaderGroups;

    //    renderSolutionFactory.buildShaderGroup(shaderGroups);
    //    shaderDB.fillShaderGroups(shaderGroups);

    //    shaderGroups.buildRootSignatures(modules, PerPass);

    //    ShaderAssetBuilder asset;
    //    asset.buildShaders(shaderDB, shaderGroups, modules);

    //    {
    //        ContentSettings settings(std::pmr::get_default_resource());
    //        auto& meshLayout = settings.mVertexLayouts.emplace_back();
    //        auto& desc = meshLayout.mBuffers.emplace_back();
    //        desc.mElements = {
    //            { POSITION, 0, Format::R32G32B32_SFLOAT },
    //            { NORMAL, 12, Format::R32G32B32_SFLOAT },
    //            { TEXCOORD, 24, Format::R32G32_SFLOAT },
    //        };
    //        meshLayout.mIndex = {
    //            { "vertex", { 0, 0} },
    //            { "normal", { 0, 1 } },
    //            { "uv", { 0, 2} },
    //        };
    //        settings.mIndex.emplace("StaticMesh", 0);

    //        std::ofstream ofs(R"(..\..\..\deploy\asset\default_settings.star)", std::ios::binary);
    //        boost::archive::binary_oarchive oa(ofs);
    //        oa << settings;
    //    }
    //    {
    //        Resources resources(std::pmr::get_default_resource());
    //        asset.build(resources);
    //        buildMaterials(resources);
    //        std::ofstream ofs(R"(..\..\..\deploy\asset\default_resources.star)", std::ios::binary);
    //        boost::archive::binary_oarchive oa(ofs);
    //        oa << resources;
    //    }

    //    MetaID contentID{};
    //    {
    //        Asset::AssetFactory manager("../../../deploy/tree", "../../../deploy/windows2",
    //            std::pmr::get_default_resource());

    //        manager.processAssets();
    //        manager.importAssetInfo();
    //        manager.exportFlattenedObjects();
    //        manager.readAssets();

    //        //ContentData scene(std::pmr::get_default_resource());
    //        //manager.try_createContent("model/scene/sponza_pbr.fbx", scene);
    //        //const auto& contentID = manager.exportContentData(scene, "model/scene/sponza.content");

    //        //Contents contents(std::pmr::get_default_resource());
    //        //boost::uuids::name_generator_sha1 gen(boost::uuids::ns::oid());
    //        //auto metaID = gen("Contents/Pipeline");
    //        //auto res = contents.mData.emplace(std::piecewise_construct,
    //        //    std::forward_as_tuple(metaID), std::forward_as_tuple());
    //        //Ensures(res.second);
    //        //auto& content = res.first->second;
    //        //content.mIDs.emplace_back(ContentID{ DrawCall, 0 });
    //        //content.mDrawCalls.emplace_back();
    //        //auto& dc = content.mDrawCalls.back();
    //        //dc.mType = FullScreenTriangle;
    //        //dc.mMaterial = gen("Materials/Pipeline");
    //        //dc.mInstanceCount = 1;
    //        //contents.mData.try_emplace(contentID, content);
    //        //std::ofstream ofs(R"(..\..\..\deploy\asset\default_contents.star)", std::ios::binary);
    //        //boost::archive::binary_oarchive oa(ofs);
    //        //oa << contents;
    //    }

    //    renderSolutionFactory.updateRenderGraph(modules, shaderGroups);
    //    {
    //        renderSolutionFactory.validateGraphs();

    //        RenderSolution renderSolution(std::pmr::get_default_resource());
    //        renderSolutionFactory.build(renderSolution);
    //        UnorderedRenderQueue queue(std::pmr::get_default_resource());
    //        queue.mContents.emplace_back(contentID);

    //        renderSolutionFactory.addContentOrdered(queue, "Forward", "Lighting", renderSolution);
    //        renderSolutionFactory.addContentOrdered(queue, "Deferred", "Geometry", renderSolution);

    //        RenderSwapChain sc(std::pmr::get_default_resource());
    //        sc.mName = "Scene";
    //        sc.mWidth = 1280u;
    //        sc.mHeight = 720u;
    //        sc.mSolutions.emplace_back(renderSolution);
    //        sc.mNumBackBuffers = 3;
    //        sc.mNumReserveFramebuffers = gsl::narrow_cast<uint32_t>(renderSolution.mFramebuffers.size());
    //        sc.mNumReserveSRVs = 0;
    //        sc.mNumReserveUAVs = 0;
    //        sc.mNumReserveDSVs = gsl::narrow_cast<uint32_t>(renderSolution.mDSVs.size());
    //        sc.mNumReserveRTVs = gsl::narrow_cast<uint32_t>(renderSolution.mRTVs.size());
    //        sc.mSolutionIndex.emplace("Desktop", 0);

    //        {
    //            std::ofstream ofs(R"(..\..\..\deploy\asset\pipeline.star)", std::ios::binary);
    //            boost::archive::binary_oarchive oa(ofs);
    //            oa << sc;
    //        }
    //    }

    //    //shaderGroups.saveShaders(R"(..\..\Star\Shaders2)");
    //    //compileShaders(shaderGroups, R"(..\..\Star\Shaders2)", R"(..\..\..\deploy\data\shaders2)");
    //} catch (std::invalid_argument& e) {
    //    {
    //        CONSOLE_COLOR(Red);
    //        std::cout << "[error] ";
    //    } 
    //    std::cout << e.what() << std::endl;
    //    return 1;
    //}

    try {
        ShaderModules modules;
        ShaderDatabase shaderDB;
        createStarModules(modules);
        buildUnityShaders(modules, shaderDB);
    } catch (std::invalid_argument & e) {
        {
            CONSOLE_COLOR(Red);
            std::cout << "[error] ";
        }
        std::cout << e.what() << std::endl;
        return 1;
    }

    //try {

    //} catch (std::invalid_argument & e) {
    //    {
    //        CONSOLE_COLOR(Red);
    //        std::cout << "[error] ";
    //    }
    //    std::cout << e.what() << std::endl;
    //    return 1;
    //}

    CONSOLE_COLOR(Green);
    std::cout << "[succeeded]";

    return 0;
}
