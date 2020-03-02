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
#include <Star/SGraph.h>
#include <Star/SMultiIndex.h>
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>
#include <StarCompiler/RenderGraph/SRenderValue.h>

namespace Star {

namespace Graphics {

namespace Render {

class GraphicsRenderNodeGraph {
public:
    using dependency_graph = Graph<std::string>;

    using node_type = RenderNode;
    using node_edge_type = boost::no_property;
    using node_graph = Graph<node_type, node_edge_type>;
    using node_index = FlatMap<std::string/*name*/, size_t/*nodeID*/>;

    using value_type = std::tuple<size_t/*nodeID*/, std::string/*name*/, ResourceDataView/*subresource*/>;
    using value_graph = Graph<value_type>;
    using value_index = FlatMap<value_type, size_t/*valueID*/>;

    using key_type = std::pair<std::string/*name*/, ResourceDataView/*subresource*/>;
    using rtv_type = std::tuple<std::string/*name*/, ResourceDataView/*subresource*/, PixelModel>;
    using dsv_type = std::tuple<std::string/*name*/, ResourceDataView/*subresource*/, bool/*readonly*/>;
    using cbv_srv_uav_type = std::tuple<ShaderDescriptorType, std::string/*name*/, ResourceDataView/*subresource*/, PixelModel>;

    size_t createNode(RenderNode node);

    size_t connectNode(size_t srcNodeID, size_t dstNodeID);
    void addDependency(size_t srcNodeID, size_t dstNodeID);

    int32_t compile();
    void validate() const;

    int32_t build();

    size_t getRTVSize() const;
    size_t getDSVSize() const;

    void buildRenderStatePaths2();
    void buildResourceViews();
private:
    void createValues(size_t nodeID);
    bool try_addNodeEdge(size_t srcNodeID, size_t dstNodeID);
    void addNodeEdge(size_t srcNodeID, size_t dstNodeID);

    bool try_addValueEdge(size_t srcNodeID, const RenderValue& output,
        size_t dstNodeID, const RenderValue& input);
    void addValueEdge(size_t srcNodeID, const RenderValue& output,
        size_t dstNodeID, const RenderValue& input);

    bool isFullyConnected() const;
    void validateCompleteness() const;

    void sortNodes();
    void buildRenderStatePaths();

    void outputValueStates() const;
    void outputViews() const;
public:
    std::string mName;
    RenderConfigs mConfig;
    OrderedNameMap<RenderTargetResource> mRenderTargets;

    node_graph mNodeGraph;
    node_index mNodeIndex;

    dependency_graph mDependencyGraph;

    value_graph mValueGraph;
    value_index mValueIndex;

    std::vector<size_t/*nodeID*/> mNodeSorted;
    std::map<key_type, RenderTargetStateTransitions> mViewStates;

    OrderedIdentityMap<rtv_type> mRTVs;
    OrderedIdentityMap<dsv_type> mDSVs;
    OrderedIdentityMap<cbv_srv_uav_type> mCBV_SRV_UAVs;
};

}

}

}
