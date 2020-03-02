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

#pragma once
#include <Star/AssetFactory/SConfig.h>
#include <Star/SMemory.h>

namespace Star::Graphics::Render {

class RenderSolutionFactory;
struct MaterialData;
struct ContentData;
struct FlattenedObjects;

namespace Shader {
class ShaderModules;
class ShaderDatabase;
}

}

namespace Star::Asset {

class STAR_ASSETFACTORY_API AssetFactory {
public:
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    AssetFactory(std::string_view assetPath, std::string_view libPath, const allocator_type& alloc);
    ~AssetFactory();
    AssetFactory(const AssetFactory&) = delete;
    AssetFactory& operator=(const AssetFactory&) = delete;

    void cleanup() const;
    void scan();
    void processAssets();

    void registerProducers();
    
    // shaders
    Graphics::Render::Shader::ShaderModules& getShaderModules();
    const Graphics::Render::Shader::ShaderModules& getShaderModules() const;

    // materials
    bool try_createMaterial(std::string_view material, std::string_view shaderName);

    // content
    std::pair<std::pair<const MetaID, Graphics::Render::ContentData>&, bool>
        try_createContent(std::string_view content);
    void clearContent(std::string_view content);
    Graphics::Render::FlattenedObjects& contentInstantiateFlattenedObjects(std::string_view content, std::string_view fbx);
    void contentAddFullscreenTriangle(std::string_view content, std::string_view material);
    void saveContent(std::string_view content);

    // render graph
    bool try_createRenderGraph(std::string_view assetPath, std::string_view name, uint32_t width, uint32_t height);
    void editRenderGraph(std::string_view assetPath, std::string_view shaderFolder);
    std::pair<Graphics::Render::RenderSolutionFactory&, bool> try_createRenderSolution(std::string_view renderGraph, std::string_view solution);
    Graphics::Render::Shader::ShaderDatabase& setupRenderGraph(std::string_view assetPath);
    void addContent(std::string_view contentPath, std::string_view renderGraphPath, std::string_view solution,
        std::string_view pipeline, std::string_view queue);

    void saveRenderGraph(std::string_view renderGraph);

    void build() const;
private:
#pragma warning(push)
#pragma warning(disable: 4251)
    struct Impl; std::unique_ptr<Impl, polymorphic_delete<Impl>> mImpl;
#pragma warning(pop)
};

}
