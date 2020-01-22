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
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>
#include <Star/SGraph.h>

namespace Star::Graphics::Render::Shader {

class ShaderGraph {
public:
    using node_edge_type = boost::no_property;
    using node_graph = boost::adjacency_list<vecS, vecS, bidirectionalS, ShaderModule, node_edge_type>;
    using dependency_graph = boost::adjacency_list<vecS, vecS, bidirectionalS, std::string>;
    using value_graph = boost::adjacency_list<vecS, vecS, bidirectionalS, std::pair<size_t/*nodeID*/, std::string>>;
    using node_index = boost::container::flat_map<std::pair<ShaderStageType/*stage*/, std::string/*name*/>, size_t/*nodeID*/>;
    using value_index = boost::container::flat_map<std::pair<size_t/*nodeID*/, std::string/*name*/>, size_t/*valueID*/>;

    struct SemanticLess {
        bool operator()(const ShaderValue& lhs, const ShaderValue& rhs) const noexcept {
            return std::forward_as_tuple(lhs.mSemantic.index(), lhs.mName) <
                std::forward_as_tuple(rhs.mSemantic.index(), rhs.mName);
        }
    };

    struct NodeValueLess {
        bool operator()(const std::pair<size_t, ShaderValue>& lhs, const std::pair<size_t, ShaderValue>& rhs) const noexcept {
            return std::forward_as_tuple(lhs.first, lhs.second.mName) < std::forward_as_tuple(rhs.first, rhs.second.mName);
        }
    };

    // graph construction
    ShaderGraph();
    size_t createNode(const ShaderModule& node, ShaderStageType stage);
    void connectNodeAndValues(size_t srcNodeID, size_t dstNodeID);
    void addDependency(size_t srcNodeID, size_t dstNodeID);

    // API: validation not required
    bool empty() const noexcept;
    std::set<std::pair<size_t/*nodeID*/, ShaderValue>, NodeValueLess> getNodeInputsWithoutSource() const;
    std::set<std::pair<size_t/*nodeID*/, ShaderValue>, NodeValueLess> getNodeInputs(ShaderStageType stage) const;
    std::set<std::pair<size_t/*nodeID*/, ShaderValue>, NodeValueLess> getNodeOutputsWithoutTarget() const;
    std::set<std::pair<size_t/*nodeID*/, ShaderValue>, NodeValueLess> getNodeOutputs(ShaderStageType stage) const;
    void validateNodes(bool bFullCheck = true) const;
    void validateConnectivity() const;

    //-----------------------------------------------------------------------------
    // API: validation required
    // Shader Group
    int fillGraph(ShaderGraph& rhs) const;

    // Shader Graph
    void getSubGraph(ShaderStageType stage, ShaderGraph& rhs) const;
    int compile();

    std::optional<ShaderStageType> isShader() const;
    IdentityMap<ShaderSemanticValue> getShaderInputs() const;
    IdentityMap<ShaderSemanticValue> getShaderOutputs() const;
private:
    // construction
    void createValues(size_t nodeID);
    bool try_addNodeEdge(size_t srcNodeID, size_t dstNodeID);
    void addNodeEdge(size_t srcNodeID, size_t dstNodeID);
    bool try_addValueEdge(size_t srcNodeID, const ShaderValue& output, size_t dstNodeID, const std::string& input);
    void addValueEdge(size_t srcNodeID, const ShaderValue& output, size_t dstNodeID, const std::string& input);

    //-----------------------------------------------------------------------------
    // API: validation not required
    // Common
    ShaderStageEnum getAllStages() const;
    bool hasNode(const std::string& name, ShaderStageType tag) const;
    const ShaderValue& getInputValue(size_t valueID) const;
    const ShaderValue& getOutputValue(size_t valueID) const;

    // Shader Group
    bool isGroupOutput(const std::pair<size_t/*nodeID*/, std::string>& valueKey) const;
    std::set<std::pair<size_t/*nodeID*/, ShaderValue>, NodeValueLess> getGroupOutputs() const;
    void validateShaderGroup() const;
    size_t copyNodeAndSourcesFromShaderGroup(size_t nodeID, ShaderGraph& rhs) const; // validation required
    void copyNodeDependenciesFromShaderGroup(size_t nodeID, ShaderGraph& rhs, size_t rhsNodeID) const; // validation required

    // Shader Graph
    void sortNodes();
public:
    std::vector<ShaderStageType> mNodeStages;
    dependency_graph mDependencyGraph;
    node_graph mNodeGraph;
    node_index mNodeIndex;
    value_graph mValueGraph;
    value_index mValueIndex;

    std::vector<size_t/*nodeID*/> mNodeSorted;
    AttributeUsageMap mAttributeUsages;
};

}
