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

#include "SShaderGraph.h"
#include "SShaderValue.h"
#include <Star/SGraphUtils.h>
#include <StarCompiler/ShaderGraph/SShaderSemantics.h>
#include "SShaderAttribute.h"
#include "SShaderModule.h"

namespace Star::Graphics::Render::Shader {

ShaderGraph::ShaderGraph() {
    mNodeGraph.m_vertices.reserve(128);
    mNodeStages.reserve(128);
    mNodeIndex.reserve(128);
    mDependencyGraph.m_vertices.reserve(128);
    mValueGraph.m_vertices.reserve(512);
    mValueIndex.reserve(512);
}

bool ShaderGraph::empty() const noexcept {
    if (mNodeStages.empty() &&
        num_vertices(mDependencyGraph) == 0 &&
        num_vertices(mNodeGraph) == 0 &&
        num_vertices(mValueGraph) == 0 &&
        mNodeIndex.empty() &&
        mValueIndex.empty() &&
        mNodeSorted.empty())
        return true;
    return false;
}

size_t ShaderGraph::createNode(const ShaderModule& node, ShaderStageType stage) {
    for (const auto& output : node.mOutputs) {
        for (const auto& input : node.mInputs) {
            if (output.mName == input.mName && !isConsistent(output, input)) {
                throw std::invalid_argument("node inputs and outputs are inconsistent");
            }
        }
    }

    for (const auto& attr : node.mAttributes) {
        validate(attr);
    }

    mNodeStages.emplace_back(stage);
    size_t nodeID = add_vertex(mNodeGraph);
    size_t nodeID1 = add_vertex(mDependencyGraph);
    Ensures(nodeID == nodeID1);
    mNodeGraph[nodeID] = node;
    mDependencyGraph[nodeID] = node.mName;
    mNodeIndex.emplace(std::make_pair(mNodeStages.back(), node.mName), nodeID);

    for (const auto& attr : node.mAttributes) {
        auto res = mAttributeUsages.emplace(attr);
        if (res.second) {
            if (attr != *res.first) {
                throw std::runtime_error("ShaderAttribute inconsistent");
            }
        }
    }

    createValues(nodeID);
    return nodeID;
}

void ShaderGraph::connectNodeAndValues(size_t srcNodeID, size_t dstNodeID) {
    addNodeEdge(srcNodeID, dstNodeID);

    for (const auto& input : mNodeGraph[dstNodeID].mInputs) {
        for (const auto& output : mNodeGraph[srcNodeID].mOutputs) {
            if (!isConsistent(output, input))
                continue;

            try_addValueEdge(srcNodeID, output, dstNodeID, input.mName);
        }
    }
}

void ShaderGraph::addDependency(size_t srcNodeID, size_t dstNodeID) {
    if (edge(dstNodeID, srcNodeID, mDependencyGraph).second) {
        throw std::invalid_argument("dependency incorrect");
    }
    if (!edge(srcNodeID, dstNodeID, mDependencyGraph).second)
        add_edge(srcNodeID, dstNodeID, mDependencyGraph);
}

void ShaderGraph::sortNodes() {
    std::vector<size_t> order;
    // might throw
    boost::topological_sort(mDependencyGraph, std::back_inserter(order));

    // succeeded
    if (mNodeSorted.size() >= order.size()) {
        mNodeSorted.clear();
        std::copy(order.begin(), order.end(), std::back_inserter(mNodeSorted));
    } else {
        mNodeSorted = std::move(order);
    }
}

int ShaderGraph::compile() {
    int error = 0;

    try {
        validateConnectivity();
        validateNodes();
        sortNodes();
    } catch (boost::not_a_dag) {
        std::cout << "shader graph is not a dag" << std::endl;
        return ++error;
    } catch (const std::exception& e) {
        std::cout << "validate graph failed: " << e.what() << std::endl;
        return ++error;
    }

    return error;
}

void ShaderGraph::validateConnectivity() const {
    auto count = getNumConnectedComponents(mNodeGraph);
    if (count != 1) {
        throw std::invalid_argument("validateConnectivity failed, graph is not fully connected");
    }
}

ShaderStageEnum ShaderGraph::getAllStages() const {
    ShaderStageEnum stagesAll{};
    
    for (size_t k = 0; k != mNodeStages.size(); ++k) {
        stagesAll = static_cast<ShaderStageEnum>(stagesAll | getShaderStageAll(mNodeStages[k]));
    }
    return stagesAll;
}

void ShaderGraph::validateNodes(bool bGraphCheck) const {
    auto sz = num_vertices(mNodeGraph);

    if (mNodeStages.size() != sz) {
        throw std::runtime_error("mNodeStages.size() != num_vertices(mNodeGraph)");
    }

    NameMap<ShaderValue> semantics;
    ShaderStageEnum stagesAll = getAllStages();

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];

        for (const auto& input : node.mInputs) {
            auto valueID = mValueIndex.at(std::make_pair(nodeID, input.mName));
            auto edges = in_edges(valueID, mValueGraph);

            if (edges.first == edges.second) {
                // no input
                if (isSemanticBlank(input)) {
                    if (!std::holds_alternative<std::monostate>(input.mValue)) {
                        if (bGraphCheck)
                            throw std::invalid_argument("node[" + node.mName + "], input[" + input.mName + "] has no source, and no input semantic");
                    }
                } else {
                    validateShaderValueSemantics(input, mNodeStages[nodeID], true);
                }

                auto res = semantics.emplace(input);
                if (res.first->mSemantic != input.mSemantic) {
                    throw std::invalid_argument("inconsistent input semantics");
                }
            } else {
                // has input
                if (std::distance(edges.first, edges.second) > 1) {
                    throw std::runtime_error("input has many sources");
                }

                // only one input source
                auto& [srcNodeID, srcValueName] = mValueGraph[edges.first->m_source];
                auto& [dstNodeID, dstValueName] = mValueGraph[edges.first->m_target];
                Expects(nodeID == dstNodeID);

                const auto& srcValue = getOutputValue(edges.first->m_source);
                const auto& dstValue = getInputValue(edges.first->m_target);

                // same stage, no semantic check
                if (mNodeStages[srcNodeID] == mNodeStages[dstNodeID])
                    continue;

                if (isSemanticBlank(input)) {
                    if (!std::holds_alternative<std::monostate>(input.mValue)) {
                        throw std::runtime_error("input semantic should be set already");
                    }
                } else {
                    validateShaderValueSemantics(input, mNodeStages[nodeID], true);
                }

                if (srcValue.mSemantic.index() != dstValue.mSemantic.index()) {
                    throw std::runtime_error("src and dst semantics are inconsistent");
                }
            }
        }

        for (const auto& output : node.mOutputs) {
            auto valueID = mValueIndex.at(std::make_pair(nodeID, output.mName));
            auto edges = out_edges(valueID, mValueGraph);

            if (edges.first == edges.second) {
                // no target, is final output
                if (std::holds_alternative<std::monostate>(output.mValue)) {
                    // is global state output, do nothing
                } else {
                    if (bGraphCheck) {
                        validateShaderValueStageOutput(stagesAll, mNodeStages[nodeID]);
                    }
                    if (isSemanticBlank(output)) {
                        if (!std::holds_alternative<std::monostate>(output.mValue)) {
                            if (bGraphCheck)
                                std::cout << "[warning]" << "node[" + node.mName + "], output[" + output.mName + "] is unused" << std::endl;
                        }
                    } else {
                        if (bGraphCheck)
                            validateShaderValueSemantics(output, mNodeStages[nodeID], false);
                    }
                }
            } else {
                // has target
                for (auto iter = edges.first; iter != edges.second; ++iter) {
                    auto& [srcNodeID, srcValueName] = mValueGraph[iter->m_source];
                    auto& [dstNodeID, dstValueName] = mValueGraph[iter->m_target];
                    Expects(nodeID == srcNodeID);

                    const auto& srcValue = getOutputValue(iter->m_source);
                    const auto& dstValue = getInputValue(iter->m_target);

                    // same stage, no semantic check
                    if (mNodeStages[srcNodeID] == mNodeStages[dstNodeID])
                        continue;

                    if (isSemanticBlank(output)) {
                        if (!std::holds_alternative<std::monostate>(output.mValue)) {
                            throw std::invalid_argument("output semantic should be specified");
                        }
                    } else {
                        if (bGraphCheck)
                            validateShaderValueSemantics(output, mNodeStages[nodeID], false);
                    }

                    if (srcValue.mSemantic != dstValue.mSemantic) {
                        throw std::runtime_error("src and dst semantics are inconsistent");
                    }
                }
            }
        }
    }
}

void ShaderGraph::validateShaderGroup() const {
    auto prevTag = mNodeStages.at(0);
    for (size_t k = 1; k != mNodeStages.size(); ++k) {
        if (mNodeStages[k] != prevTag) {
            throw std::invalid_argument("lhs shader graph is not a shader group, constains multiple shader stages");
        }
    }

    auto outputSet = NameMap<ShaderValue>();

    auto outputs = getGroupOutputs();
    for (const auto& [nodeID, output] : outputs) {
        Expects(isGroupOutput(std::make_pair(nodeID, output.mName)));
        auto res = outputSet.emplace(output);
        if (res.second == false) {
            throw std::invalid_argument("shader graph has identical outputs[" + output.mName + "]");
        }
    }
}

std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess>
ShaderGraph::getNodeInputsWithoutSource() const {
    std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> inputs;
    auto sz = num_vertices(mNodeGraph);

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];

        for (const auto& input : node.mInputs) {
            auto valueID = mValueIndex.at(std::pair{ nodeID, input.mName });
            auto edges = in_edges(valueID, mValueGraph);
            
            if (std::distance(edges.first, edges.second) == 0) {
                inputs.emplace(std::make_pair(nodeID, input));
            }
        }
    }

    return inputs;
}

std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess>
ShaderGraph::getNodeInputs(ShaderStageType stage) const {
    std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> inputs;
    auto sz = num_vertices(mNodeGraph);

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];
        const auto& nodeStage = mNodeStages[nodeID];
        if (nodeStage != stage)
            continue;

        for (const auto& input : node.mInputs) {
            auto valueID = mValueIndex.at(std::pair{ nodeID, input.mName });
            auto edges = in_edges(valueID, mValueGraph);

            for (auto iter = edges.first; iter != edges.second; ++iter) {
                auto srcNodeID = mValueGraph[iter->m_source].first;
                if (mNodeStages[srcNodeID] != stage) {
                    inputs.emplace(std::make_pair(nodeID, input));
                }
            }
        }
    }

    return inputs;
}

std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess>
ShaderGraph::getNodeOutputsWithoutTarget() const {
    std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> outputs;
    auto sz = num_vertices(mNodeGraph);

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];

        for (const auto& output : node.mOutputs) {
            auto valueID = mValueIndex.at(std::pair{ nodeID, output.mName });
            auto edges = out_edges(valueID, mValueGraph);

            if (std::distance(edges.first, edges.second) == 0) {
                outputs.emplace(std::make_pair(nodeID, output));
            }
        }
    }

    return outputs;
}

std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess>
ShaderGraph::getNodeOutputs(ShaderStageType stage) const {
    std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> outputs;
    auto sz = num_vertices(mNodeGraph);

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];
        const auto& nodeStage = mNodeStages[nodeID];
        if (nodeStage != stage)
            continue;

        for (const auto& output : node.mOutputs) {
            auto valueID = mValueIndex.at(std::pair{ nodeID, output.mName });
            auto edges = out_edges(valueID, mValueGraph);

            for (auto iter = edges.first; iter != edges.second; ++iter) {
                auto dstNodeID = mValueGraph[iter->m_target].first;
                if (mNodeStages[dstNodeID] != stage) {
                    outputs.emplace(std::make_pair(nodeID, output));
                }
            }
        }
    }

    return outputs;
}

int ShaderGraph::fillGraph(ShaderGraph& rhs) const {
    int error = 0;

    try {
        validateShaderGroup();
    } catch (const std::invalid_argument& e) {
        std::cout << "validate shader group failed, " << e.what() << std::endl;
        return ++error;
    }
    
    auto rhsInputs = rhs.getNodeInputsWithoutSource();
    auto outputs = getGroupOutputs();

    size_t rhsNodeCount = num_vertices(rhs.mNodeGraph);

    // find all nodes to add
    std::map<size_t, size_t> srcNodes;
    std::set<std::pair<size_t, size_t>> connections;

    for (const auto&[rhsDstNodeID, input] : rhsInputs) {
        for (const auto&[srcNodeID, output] : outputs) {
            if (isConsistent(input, output)) {
                srcNodes.emplace(std::pair{ srcNodeID, size_t(-1) });
                connections.emplace(std::pair{ srcNodeID, rhsDstNodeID });
            }
        }
    }
    
    // add nodes and sources
    for (auto&[srcNodeID, rhsSrcNodeID] : srcNodes) {
        rhsSrcNodeID = copyNodeAndSourcesFromShaderGroup(srcNodeID, rhs);
        for (size_t k = 0; k != rhsNodeCount; ++k) {
            rhs.addDependency(rhsSrcNodeID, k);
        }
    }

    // add dependencies
    for (auto& [srcNodeID, rhsSrcNodeID] : srcNodes) {
        copyNodeDependenciesFromShaderGroup(srcNodeID, rhs, rhsSrcNodeID);
    }

    // add node edges
    for (const auto&[srcNodeID, rhsDstNodeID] : connections) {
        auto rhsSrcNodeID = srcNodes.at(srcNodeID);
        rhs.addNodeEdge(rhsSrcNodeID, rhsDstNodeID);        
    }

    // add value edges
    for (const auto&[rhsDstNodeID, input] : rhsInputs) {
        for (const auto&[srcNodeID, output] : outputs) {
            if (isConsistent(input, output)) {
                const auto& stage = mNodeStages[srcNodeID];
                const auto& name = mNodeGraph[srcNodeID].mName;

                auto rhsSrcNodeID = rhs.mNodeIndex.at(std::make_pair(stage, name));
                rhs.addValueEdge(rhsSrcNodeID, output, rhsDstNodeID, input.mName);
            }
        }
    }

    return error;
}

std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> ShaderGraph::getGroupOutputs() const {
    std::set<std::pair<size_t, ShaderValue>, ShaderGraph::NodeValueLess> outputs;

    auto sz = num_vertices(mNodeGraph);

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];

        for (const auto& output : node.mOutputs) {
            if (isGroupOutput(std::make_pair(nodeID, output.mName))) {
                outputs.emplace(std::make_pair(nodeID, output));
            }
        }
    }

    return outputs;
}

bool ShaderGraph::isGroupOutput(const std::pair<size_t, std::string>& valueKey) const {
    auto valueID = mValueIndex.at(valueKey);
    auto edges = out_edges(valueID, mValueGraph);
    if (std::distance(edges.first, edges.second) == 0) {
        return true;
    } else {
        for (auto iter = edges.first; iter != edges.second; ++iter) {
            auto srcNodeID = mValueGraph[iter->m_source].first;
            auto dstNodeID = mValueGraph[iter->m_target].first;
            if (mNodeStages[srcNodeID] != mNodeStages[dstNodeID]) {
                throw std::runtime_error("shader group should be in same stage");
            }
            // if current value will be modified by any target node, it is not group output
            auto valueIter = mNodeGraph[dstNodeID].mOutputs.find(valueKey.second);
            if (valueIter != mNodeGraph[dstNodeID].mOutputs.end()) {
                return false;
            }
        }
        return true;
    }
}

const ShaderValue& ShaderGraph::getInputValue(size_t valueID) const {
    const auto&[nodeID, name] = mValueGraph[valueID];
    auto iter = mNodeGraph[nodeID].mInputs.find(name);
    if (iter == mNodeGraph[nodeID].mInputs.end())
        throw std::runtime_error("node output value not found");

    return *iter;
}

const ShaderValue& ShaderGraph::getOutputValue(size_t valueID) const {
    const auto&[nodeID, name] = mValueGraph[valueID];
    auto iter = mNodeGraph[nodeID].mOutputs.find(name);
    if (iter == mNodeGraph[nodeID].mOutputs.end())
        throw std::runtime_error("node output value not found");

    return *iter;
}

void ShaderGraph::createValues(size_t nodeID) {
    // this function will only be called in ShaderGraph
    auto& node = mNodeGraph[nodeID];

    auto createValue = [&](const ShaderValue& value) {
        auto valueID = add_vertex(mValueGraph);
        mValueGraph[valueID] = std::make_pair(nodeID, value.mName);
        auto res = mValueIndex.emplace(std::make_pair(nodeID, value.mName), valueID);
        // this is assured by algorithm
        Ensures(res.second);
        std::ignore = res;
        return valueID;
    };

    // step 1
    for (const auto& output : node.mOutputs) {
        auto key = std::make_pair(nodeID, output.mName);
        auto iter = mValueIndex.find(key);
        // this is assured by algorithm
        Expects(iter == mValueIndex.end());
        createValue(output);        
    }

    // step 2
    for (const auto& input : node.mInputs) {
        auto key = std::make_pair(nodeID, input.mName);               
        auto iter = mValueIndex.find(key);
        if (iter == mValueIndex.end()) {
            createValue(input);
        } else { // already exists, must be added by previous step 1
            bool bOutput = (node.mOutputs.find(input.mName) != node.mOutputs.end());
            Ensures(bOutput);
            std::ignore = bOutput;
        }
    }
}

bool ShaderGraph::hasNode(const std::string& name, ShaderStageType stage) const {
    return mNodeIndex.find(std::make_pair(stage, name)) != mNodeIndex.end();
}

size_t ShaderGraph::copyNodeAndSourcesFromShaderGroup(size_t nodeID, ShaderGraph& rhs) const {
    const auto& node = mNodeGraph[nodeID];
    const auto& stage = mNodeStages[nodeID];

    // create target node
    auto rhsNodeID = rhs.createNode(node, stage);

    // add node dependencies
    auto edges = in_edges(nodeID, mNodeGraph);
    for (auto iter = edges.first; iter != edges.second; ++iter) {
        // for each source node
        auto srcNodeID = iter->m_source;
        const auto& srcName = mNodeGraph[srcNodeID].mName;
        const auto& srcTag = mNodeStages[srcNodeID];

        // Add Node Edge
        size_t rhsSrcNodeID;
        if (!rhs.hasNode(srcName, srcTag)) {
            // not found, create a new one
            rhsSrcNodeID = copyNodeAndSourcesFromShaderGroup(srcNodeID, rhs);
            rhs.addNodeEdge(rhsSrcNodeID, rhsNodeID);
        } else {
            // found, try add node edge
            rhsSrcNodeID = rhs.mNodeIndex.at(std::pair{ srcTag, srcName });
            auto[iter, hasEdge] = edge(rhsSrcNodeID, rhsNodeID, rhs.mNodeGraph);
            Expects(!hasEdge);
            if (!hasEdge) {
                rhs.addNodeEdge(rhsSrcNodeID, rhsNodeID);
            }
        }

        // Add Value Edges
        for (const auto& output : rhs.mNodeGraph[rhsSrcNodeID].mOutputs) {
            auto edges = out_edges(mValueIndex.at(std::make_pair(srcNodeID, output.mName)), mValueGraph);
            for (auto iter = edges.first; iter != edges.second; ++iter) {
                if (mValueGraph[iter->m_target].first == nodeID)
                    rhs.addValueEdge(rhsSrcNodeID, output, rhsNodeID, output.mName);
            }
        }
    }


    return rhsNodeID;
}

void ShaderGraph::copyNodeDependenciesFromShaderGroup(size_t dstNodeID, ShaderGraph& rhs, size_t rhsDstNodeID) const {
    // add node dependency dependencies
    auto edges = in_edges(dstNodeID, mDependencyGraph);
    for (auto iter = edges.first; iter != edges.second; ++iter) {
        auto srcNodeID = iter->m_source;
        const auto& srcName = mNodeGraph[srcNodeID].mName;
        const auto& srcTag = mNodeStages[srcNodeID];

        if (auto iter = rhs.mNodeIndex.find(std::pair{ srcTag, srcName }); iter != rhs.mNodeIndex.end()) {
            auto rhsSrcNodeID = iter->second;
            rhs.addDependency(rhsSrcNodeID, rhsDstNodeID);
            copyNodeDependenciesFromShaderGroup(srcNodeID, rhs, rhsSrcNodeID);
        }
    }
}

bool ShaderGraph::try_addNodeEdge(size_t srcNodeID, size_t dstNodeID) {
    if (edge(srcNodeID, dstNodeID, mNodeGraph).second) {
        return false;
    }

    add_edge(srcNodeID, dstNodeID, mNodeGraph);
    addDependency(srcNodeID, dstNodeID);
    return true;
}

void ShaderGraph::addNodeEdge(size_t srcNodeID, size_t dstNodeID) {
    if (!try_addNodeEdge(srcNodeID, dstNodeID)) {
        throw std::invalid_argument("node edge already exists");
    }
}

bool ShaderGraph::try_addValueEdge(size_t srcNodeID, const ShaderValue& output,
    size_t dstNodeID, const std::string& inputName
) {
    bool added = false;

    auto srcValueID = mValueIndex.at(std::make_pair(srcNodeID, output.mName));
    auto dstValueID = mValueIndex.at(std::make_pair(dstNodeID, inputName));
    if (output.mName != inputName) {
        throw std::runtime_error("input and output name not equal");
    }

    auto edges = in_edges(dstValueID, mValueGraph);
    if (edges.first != edges.second) {
        // already has input, do not added
        return added;
    }

    added = true;

    add_edge(srcValueID, dstValueID, mValueGraph);

    // try modify semantic
    if (mNodeStages.at(srcNodeID) != mNodeStages.at(dstNodeID)) {
        if (isSemanticBlank(output)) {
            auto iter = mNodeGraph[dstNodeID].mInputs.find(inputName);
            if (iter == mNodeGraph[dstNodeID].mInputs.end()) {
                throw std::invalid_argument("shader stage output:" + output.mName + " has blank semantic and is not input of dst node");
            }
            const auto& input = *iter;
            if (isSemanticBlank(input)) {
                if (!std::holds_alternative<std::monostate>(input.mValue)) {
                    throw std::invalid_argument("shader stage output:" + output.mName + " has blank semantic");
                }
            } else {
                auto iter = mNodeGraph[srcNodeID].mOutputs.find(inputName);
                if (iter == mNodeGraph[srcNodeID].mOutputs.end()) {
                    throw std::runtime_error("output value not found");
                }

                // notice the output and the below might be the same
                // modify semantic
                mNodeGraph[srcNodeID].mOutputs.modify(iter, [&](ShaderValue& v) {
                    v.mSemantic = input.mSemantic;
                });
            }
        } else {
            // modify semantic
            auto iter = mNodeGraph[dstNodeID].mInputs.find(inputName);
            mNodeGraph[dstNodeID].mInputs.modify(iter, [&](ShaderValue& v) {
                v.mSemantic = output.mSemantic;
            });
        }
    }

    return added;
}

void ShaderGraph::addValueEdge(size_t srcNodeID, const ShaderValue& output,
    size_t dstNodeID, const std::string& input
) {
    auto added = try_addValueEdge(srcNodeID, output, dstNodeID, input);
    if (added == false) {
        throw std::runtime_error("value edge already exists");
    }
}

void ShaderGraph::getSubGraph(ShaderStageType stage, ShaderGraph& rhs) const {
    if (!rhs.empty()) {
        throw std::invalid_argument("rhs ShaderGraph is not empty");
    }

    size_t sz = num_vertices(mNodeGraph);
    std::map<size_t/*lhs nodeID*/, size_t /*rhs nodeID*/> nodeIndex;

    // Create Output Node
    ShaderModule Output{ "Output" };

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];
        const auto& nodeStage = mNodeStages[nodeID];
        if (nodeStage != stage) {
            continue;
        }

        for (const auto& output : node.mOutputs) {
            auto edges = out_edges(mValueIndex.at(std::make_pair(nodeID, output.mName)), mValueGraph);
            for (auto iter = edges.first; iter != edges.second; ++iter) {
                auto dstStage = mNodeStages[mValueGraph[iter->m_target].first];
                if (dstStage != stage) {
                    Output.mOutputs.emplace(output);
                    Output.mInputs.emplace(output);
                }
            }
        }
    }

    auto rhsOutput = rhs.createNode(Output, stage);

    // first pass, create nodes
    for (size_t k = 0; k != sz; ++k) {
        auto lhsNodeID = k;
        const auto& lhsNode = mNodeGraph[lhsNodeID];
        const auto& lhsNodeStage = mNodeStages[lhsNodeID];

        if (lhsNodeID == 0)
            continue;

        if (lhsNodeStage == stage) {
            auto rhsNodeID = rhs.createNode(lhsNode, stage);
            auto res = nodeIndex.emplace(std::pair{ lhsNodeID, rhsNodeID });
            Ensures(res.second);
        }
    }

    // second pass, create edges
    for (size_t k = 0; k != sz; ++k) {
        auto lhsNodeID = k;

        if (lhsNodeID == 0)
            continue;

        const auto& lhsNode = mNodeGraph[lhsNodeID];
        const auto& lhsNodeStage = mNodeStages[lhsNodeID];

        if (lhsNodeStage != stage)
            continue;

        { // Dependency Graph
            auto edges = out_edges(lhsNodeID, mDependencyGraph);
            for (auto lhsEdge = edges.first; lhsEdge != edges.second; ++lhsEdge) {
                if (mNodeStages[lhsEdge->m_target] != stage) {
                    rhs.addDependency(nodeIndex.at(lhsNodeID), rhsOutput);
                } else {
                    rhs.addDependency(nodeIndex.at(lhsNodeID), nodeIndex.at(lhsEdge->m_target));
                }
            }
        }
        { // Node Graph
            auto edges = out_edges(lhsNodeID, mNodeGraph);
            for (auto lhsEdge = edges.first; lhsEdge != edges.second; ++lhsEdge) {
                if (mNodeStages[lhsEdge->m_target] != stage) {
                    // render nodes might be 
                    //    VS/ --PS 1
                    //      \ --PS 2
                    // when convert to shader stage graph, it can be 
                    // VS /\ VS out
                    //    \/ 
                    // so it might have duplicated node edges
                    // we must use try add node edge
                    rhs.try_addNodeEdge(nodeIndex.at(lhsNodeID), rhsOutput);
                } else {
                    rhs.addNodeEdge(nodeIndex.at(lhsNodeID), nodeIndex.at(lhsEdge->m_target));
                }
            }
        }

        // Value Graph
        auto lhsSrcNodeID = lhsNodeID;
        auto rhsSrcNodeID = rhs.mNodeIndex.at(std::make_pair(stage, mNodeGraph[lhsSrcNodeID].mName));

        const auto& lhsSrcNode = lhsNode;

        for (const auto& output : lhsSrcNode.mOutputs) {
            auto edges = out_edges(mValueIndex.at(std::make_pair(lhsSrcNodeID, output.mName)), mValueGraph);

            for (auto lhsEdge = edges.first; lhsEdge != edges.second; ++lhsEdge) {
                auto lhsDstNodeID = mValueGraph[lhsEdge->m_target].first;
                if (mNodeStages[lhsDstNodeID] != stage) {
                    rhs.try_addValueEdge(rhsSrcNodeID, output, rhsOutput, output.mName);
                } else {
                    rhs.try_addValueEdge(rhsSrcNodeID, output, nodeIndex.at(lhsDstNodeID), output.mName);
                }
            }
        }
    }
}

std::optional<ShaderStageType> ShaderGraph::isShader() const {
    std::set<ShaderStageType> stages;
    for (const auto& stage : mNodeStages) {
        stages.emplace(stage);
    }

    std::optional<ShaderStageType> res;
    if (stages.size() == 1) {
        res = *stages.begin();
    }
    return res;
}

IdentityMap<ShaderSemanticValue> ShaderGraph::getShaderInputs() const {
    IdentityMap<ShaderSemanticValue> results;
    auto inputs = getNodeInputsWithoutSource();
    for (const auto& input : inputs) {
        if (isGlobalState(input.second))
            continue;
        if ((mNodeGraph[input.first].mBuilderFlags & System) &&
            std::holds_alternative<SV_Position_>(input.second.mSemantic))
        {
            continue;
        }
        results.emplace(ShaderSemanticValue{ input.second.mSemantic, input.second.mValue, input.second.mName });
    }
    return results;
}

IdentityMap<ShaderSemanticValue> ShaderGraph::getShaderOutputs() const {
    IdentityMap<ShaderSemanticValue> results;
    for (const auto& output : mNodeGraph[0].mOutputs) {
        if (isGlobalState(output)) {
            continue;
        }
        results.emplace(ShaderSemanticValue{ output.mSemantic, output.mValue, output.mName });
    }
    return results;
}

}
