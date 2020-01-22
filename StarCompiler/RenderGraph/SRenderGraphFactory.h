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
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>
#include <StarCompiler/RenderGraph/SRenderGraph.h>
#include <StarCompiler/ShaderGraph/SShaderGroups.h>

namespace Star {

namespace Graphics {

namespace Render {

class RenderSolutionFactory {
public:
    using rtv_key = std::tuple<std::string/*graphName*/, size_t/*nodeID*/,
        std::string, ResourceDataView, PixelModel>;

    using dsv_key = std::tuple<std::string/*graphName*/, size_t/*nodeID*/,
        std::string, ResourceDataView, bool/*readOnly*/>;

    RenderSolutionFactory(std::string name)
        : mName(std::move(name))
    {}

    RenderSolutionFactory(const RenderSolutionFactory&) = delete;
    RenderSolutionFactory& operator=(const RenderSolutionFactory&) = delete;

    void addPipeline(GraphicsRenderNodeGraph&& graph);

    int compile();
    void validateGraphs() const;

    void buildShaderGroup(Shader::ShaderGroups& shaderWorks) const;
    void updateRenderGraph(const Shader::ShaderModules& modules, const Shader::ShaderGroups& shaderWorks);

    void build(std::string solutionName, RenderSolution& renderWorks, std::ostringstream& oss) const;

    void addContentOrdered(const UnorderedRenderQueue& content,
        std::string_view pipelineName, std::string_view passName,
        RenderSolution& renderWorks) const;
private:
    void collectFramebuffers(
        OrderedNameMap<RenderTargetResource>& bbs,
        OrderedNameMap<RenderTargetResource>& rts) const;

    void outputFramebuffers(const OrderedNameMap<RenderTargetResource>& framebuffers) const;

    void buildFramebuffers(
        const OrderedNameMap<RenderTargetResource>& bbs,
        const OrderedNameMap<RenderTargetResource>& rts,
        RenderSolution& renderWorks,
        std::map<std::string, uint32_t>& rtIndex
    ) const;

    void collectRTVsMinimal(
        size_t rtvOffset,
        const OrderedNameMap<RenderTargetResource>& bbs,
        const OrderedNameMap<RenderTargetResource>& rts,
        OrderedIdentityMap<GraphicsRenderNodeGraph::rtv_type>& rtvs,
        std::map<rtv_key, size_t>& index
    ) const;

    void collectDSVsMinimal(
        const OrderedNameMap<RenderTargetResource>& bbs,
        const OrderedNameMap<RenderTargetResource>& rts,
        OrderedIdentityMap<GraphicsRenderNodeGraph::dsv_type>& dsvs,
        std::map<dsv_key, size_t>& index
    ) const;
public:
    std::string mName;
    RenderConfigs mConfig;
    uint32_t mBackBufferCount = 3;
    std::vector<std::string> mGraphOrder;
    Map<std::string, GraphicsRenderNodeGraph> mNodeGraphs;
};

}

}

}
