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

#include "SRenderGraph.h"
#include "SRenderGraphUtils.h"
#include "SRenderGraphDSL.h"
#include <Star/SGraphUtils.h>
#include <StarCompiler/Graphics/SRenderFormatUtils.h>

namespace Star::Graphics::Render {

size_t GraphicsRenderNodeGraph::createNode(RenderNode node) {
    for (const auto& output : node.mOutputs) {
        for (const auto& input : node.mInputs) {
            if (output.mName == input.mName && output != input) {
                throw std::invalid_argument("node inputs and outputs are inconsistent");
            }
        }
    }

    auto& outputs = node.mOutputs;
    for (auto iter = outputs.begin(); iter != outputs.end(); ++iter) {
        const auto& output = *iter;
        const auto& rt = at(mRenderTargets, output.mName);
        auto model = validateRenderTargetBinding(node.mColorSpace, rt);

        auto output2 = output;
        output2.mModel = model;
        outputs.replace(iter, output2);
    }

    auto& inputs = node.mInputs;
    for (auto iter = inputs.begin(); iter != inputs.end(); ++iter) {
        const auto& input = *iter;
        const auto& rt = at(mRenderTargets, input.mName);
        auto model = validateRenderTargetBinding(node.mColorSpace, rt);

        auto input2 = input;
        input2.mModel = model;
        inputs.replace(iter, input2);
    }

    size_t nodeID0 = add_vertex(mDependencyGraph);
    size_t nodeID = add_vertex(mNodeGraph);
    Expects(nodeID0 == nodeID);

    auto name = node.mName;
    mDependencyGraph[nodeID0] = name;
    mNodeGraph[nodeID] = std::move(node);
    mNodeIndex.emplace(name, nodeID);

    createValues(nodeID);

    return nodeID;
}

size_t GraphicsRenderNodeGraph::connectNode(size_t srcNodeID, size_t dstNodeID) {
    addNodeEdge(srcNodeID, dstNodeID);

    size_t valueConnected = 0;
    for (const auto& input : mNodeGraph[dstNodeID].mInputs) {
        for (const auto& output : mNodeGraph[srcNodeID].mOutputs) {
            if (output.mName != input.mName)
                continue;

            if (try_addValueEdge(srcNodeID, output, dstNodeID, input))
                ++valueConnected;
        }
    }

    for (const auto& dst : mNodeGraph[dstNodeID].mOutputs) {
        for (const auto& output : mNodeGraph[srcNodeID].mOutputs) {
            if (output.mName != dst.mName)
                continue;

            if (try_addValueEdge(srcNodeID, output, dstNodeID, dst))
                ++valueConnected;
        }
    }

    return valueConnected;
}

void GraphicsRenderNodeGraph::addDependency(size_t srcNodeID, size_t dstNodeID) {
    if (edge(dstNodeID, srcNodeID, mDependencyGraph).second) {
        throw std::invalid_argument("dependency incorrect");
    }
    if (!edge(srcNodeID, dstNodeID, mDependencyGraph).second)
        add_edge(srcNodeID, dstNodeID, mDependencyGraph);
}

bool GraphicsRenderNodeGraph::try_addNodeEdge(size_t srcNodeID, size_t dstNodeID) {
    if (edge(srcNodeID, dstNodeID, mNodeGraph).second) {
        return false;
    }

    add_edge(srcNodeID, dstNodeID, mNodeGraph);
    addDependency(srcNodeID, dstNodeID);
    return true;
}

void GraphicsRenderNodeGraph::addNodeEdge(size_t srcNodeID, size_t dstNodeID) {
    if (!try_addNodeEdge(srcNodeID, dstNodeID)) {
        throw std::invalid_argument("node edge already exists");
    }
}

bool GraphicsRenderNodeGraph::try_addValueEdge(size_t srcNodeID, const RenderValue& output,
    size_t dstNodeID, const RenderValue& input
) {
    bool added = false;

    auto srcValueID = mValueIndex.at(make_key(srcNodeID, output));
    auto dstValueID = mValueIndex.at(make_key(dstNodeID, input));

    auto edges = in_edges(dstValueID, mValueGraph);
    if (edges.first != edges.second) {
        // already has input, do not added
        return added;
    }

    Expects(output.mName == input.mName);
   
    if (!equal(output, input)) {
        throw std::invalid_argument("input value not equal output value");
    }
       
    validateTextureViewTransition(input.mState, output.mState);

    add_edge(srcValueID, dstValueID, mValueGraph);

    added = true;

    return added;
}

void GraphicsRenderNodeGraph::addValueEdge(size_t srcNodeID, const RenderValue& output,
    size_t dstNodeID, const RenderValue& input
) {
    auto added = try_addValueEdge(srcNodeID, output, dstNodeID, input);
    if (added == false) {
        throw std::runtime_error("value edge already exists");
    }
}

int GraphicsRenderNodeGraph::compile() {
    std::cout << "compiling: ";
    {
        CONSOLE_COLOR(Magenta);
        std::cout << "Pipeline " << mName << std::endl;
    }

    int error = 0;

    if (!isFullyConnected()) {
        std::cout << "render graph has multiple components" << std::endl;
        return ++error;
    }

    try {
        sortNodes();
    } catch (boost::not_a_dag) {
        std::cout << "render graph is not a dag" << std::endl;
        return ++error;
    }

    try {
        validate();
    } catch (const std::exception& e) {
        std::cout << "validateRenderNodes failed: " << e.what() << std::endl;
        return ++error;
    }

    try {
        validateCompleteness();
    } catch (const std::invalid_argument& e) {
        std::cout << "validateCompleteness failed: " << e.what() << std::endl;
        return ++error;
    }

    try {
        buildRenderStatePaths();
    } catch (const std::exception& e) {
        std::cout << "buildRenderStatePaths failed: " << e.what() << std::endl;
        return ++error;
    }

    //if (mConfig.mVerbose) {
    //    try {
    //        outputViews();
    //    } catch (const std::exception& e) {
    //        std::cout << "outputViews failed: " << e.what() << std::endl;
    //    }
    //}

    {
        CONSOLE_COLOR(Cyan);
        std::cout << "render graph compile succeeded" << std::endl;
    }
    return 0;
}

int32_t GraphicsRenderNodeGraph::build() {

    return 0;
}

void GraphicsRenderNodeGraph::validate() const {
    Expects(!mNodeSorted.empty());
    auto sz = num_vertices(mNodeGraph);
    Expects(mNodeSorted.size() == sz);

    for (const auto& rt : mRenderTargets) {
        validateRenderTarget(rt);
    }

    // validate render node binding
    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = k;
        const auto& node = mNodeGraph[nodeID];

        ResourceType dimension = {};
        for (const auto& v : node.mOutputs) {
            const auto& rt = at(mRenderTargets, v.mName);
            if (dimension == ResourceType{}) {
                dimension = rt.mResource.mDimension;
            }
            if (dimension != rt.mResource.mDimension) {
                throw std::invalid_argument("rtv, dsv have different dimension");
            }
            validateRenderValue(rt.mResource, v, Target, Direct3D);
        }

        for (const auto& v : node.mInputs) {
            const auto& rt = at(mRenderTargets, v.mName);
            validateRenderValue(rt.mResource, v, Source, Direct3D);
        }

        for (const auto& output : node.mOutputs) {
            auto iter = node.mInputs.get<Index::Name>().find(get_key(output));
            if (iter != node.mInputs.get<Index::Name>().end()) {
                const auto& input = *iter;
                if (std::holds_alternative<DepthRead_>(output.mState) &&
                    std::holds_alternative<DepthRead_>(input.mState))
                {
                    std::cout << "resource is both DepthRead and ShaderResource" << std::endl;
                    continue;
                }

                if (mConfig.mFramebufferFetch) {
                    visit(overload(
                        [](RenderTarget_, RenderTarget_) {},
                        [](auto, auto) {
                            throw std::invalid_argument("[FBF enabled]only rtv can be both input and output");
                        }
                    ), input.mState, output.mState);
                } else {
                    visit(overload(
                        [](RenderTarget_) {
                            throw std::invalid_argument("[FBF disabled]rtv cannot be bound to input");
                        },
                        [](auto) {
                        }
                    ), input.mState);
                    throw std::invalid_argument("[FBF disabled]framebuffer cannot be bound to both input and output");
                }
            }
        }
    }
}

size_t GraphicsRenderNodeGraph::getRTVSize() const {
    size_t count = 0;
    for (const auto& id : mNodeSorted) {
        const auto& node = mNodeGraph[id];
        for (const auto& v : node.mOutputs) {
            const auto& rt = at(mRenderTargets, v.mName);
            if (std::holds_alternative<ClearColor>(rt.mClearColor)) {
                ++count;
            }
        }
    }
    return count;
}

size_t GraphicsRenderNodeGraph::getDSVSize() const {
    return size_t();
}

bool GraphicsRenderNodeGraph::isFullyConnected() const {
    auto count = getNumConnectedComponents(mNodeGraph);
    return count == 1;
}

void GraphicsRenderNodeGraph::sortNodes() {
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

void GraphicsRenderNodeGraph::validateCompleteness() const {
    if (mNodeSorted.size() != num_vertices(mNodeGraph)) {
        throw std::invalid_argument("node order and node graph size inconsistent, please sort graph first");
    }

    auto sz = num_vertices(mNodeGraph);

    int outputCount = 0;

    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = mNodeSorted[k];
        const auto& node = mNodeGraph[nodeID];
        auto values = getValues(node);

        // validate output edges first
        for (const auto& v : values) {
            auto valueID = mValueIndex.at(make_key(nodeID, v));
            auto edges = out_edges(valueID, mValueGraph);
            if (std::distance(edges.first, edges.second) > 1)
                throw std::invalid_argument(("render node: " + node.mName + ", value: " + v.mName
                    + " multiple outputs not supported yet").c_str());
        }
        
        // validate input
        auto validateInputState = [](const RenderValue& v) {
            visit(overload(
                [&](std::monostate) {
                    throw std::invalid_argument(("render value has no LoadOp: " + v.mName).c_str());
                },
                [&](DontRead_) {
                    CONSOLE_WARNING();
                    std::cout << "input render value: " << v.mName << " has no input and don't care previous value, uninitialized" << std::endl;
                },
                [&](Load_) {
                    CONSOLE_WARNING();
                    std::cout << "input render value: " << v.mName << " has no input and load previous value" << std::endl;
                },
                [](auto) {
                }
            ), v.mLoadOp);
        };

        for (const auto& input : node.mInputs) {
            auto valueID = mValueIndex.at(make_key(nodeID, input));
            auto edges = in_edges(valueID, mValueGraph);

            // has input, skip
            if (edges.first != edges.second) {
                if (std::distance(edges.first, edges.second) != 1) {
                    throw std::runtime_error("render value muliple inputs");
                }

                visit(overload(
                    [&](DontRead_) {
                        throw std::invalid_argument(
                            ("input render value: " + input.mName + " has input, but don't care").c_str());
                    },
                    [&](ClearColor) {
                        throw std::invalid_argument((
                            "input render value: " + input.mName + " has input, but cleared(color)").c_str());
                    },
                    [&](ClearDepthStencil) {
                        throw std::invalid_argument((
                            "input render value: " + input.mName + " has input, but cleared(depth stencil)").c_str());
                    },
                    [](auto) {
                    }
                ), input.mLoadOp);

                continue;
            }

            // no input
            validateInputState(input);

            throw std::invalid_argument("render node input has no source");
        }

        for (const auto& output : node.mOutputs) {
            auto valueID = mValueIndex.at(make_key(nodeID, output));
            
            auto inEdges = in_edges(valueID, mValueGraph);
            if (inEdges.first == inEdges.second) {
                validateInputState(output);
            }

            auto outEdges = out_edges(valueID, mValueGraph);

            // no output
            if (outEdges.first == outEdges.second) {
                if (std::holds_alternative<DepthWrite_>(output.mState) ||
                    std::holds_alternative<DepthRead_>(output.mState))
                {
                    std::cout << "output render value: " + output.mName +
                        "(dsv) has no output, but discarded, this is permitted"
                        << std::endl;
                    return;
                }
                if (std::holds_alternative<Present_>(output.mState) &&
                    std::holds_alternative<Store_>(output.mStoreOp))
                {
                    ++outputCount;
                    return;
                }
                throw std::invalid_argument(
                    ("output render value : " + output.mName + " has no output, but discarded").c_str());
                continue;
            }

            // has output
            visit(overload(
                [&](Discard_) {
                    throw std::invalid_argument((
                        "output render value: " + output.mName + " has output, but discarded").c_str());
                },
                [](auto) {
                }
            ), output.mStoreOp);
        }
    }

    if (outputCount == 0) {
        throw std::runtime_error("internal error: no present output");
    }

    if (outputCount > 1) {
        throw std::invalid_argument("multiple present output");
    }
}

void GraphicsRenderNodeGraph::buildRenderStatePaths() {
    if (mNodeSorted.size() != num_vertices(mNodeGraph)) {
        throw std::invalid_argument("node order and node graph size inconsistent, please sort graph first");
    }

    for (size_t k = 0; k != mNodeSorted.size(); ++k) {
        auto nodeID = mNodeSorted[k];
        const auto& node = mNodeGraph[nodeID];

        for (const auto& output : node.mOutputs) {
            auto& v = mViewStates[get_key(output)];

            if (!v.mStates.empty() && v.mStates.back().mNodeID == nodeID) {
                throw std::runtime_error("node state already exists");
            }

            v.mStates.emplace_back(
                NodeRenderTargetState{ gsl::narrow<uint32_t>(nodeID), { output.mState } }
            );
        }

        for (const auto& input : node.mInputs) {
            auto& v = mViewStates[get_key(input)];
            if (!v.mStates.empty()) {
                auto& state = v.mStates.back();
                // same node must have same states
                if (state.mNodeID == nodeID) {
                    if (state.mRenderTargetState.mState != input.mState) {
                        throw std::runtime_error("input and output have different states");
                    }
                    if (!std::holds_alternative<DepthRead_>(input.mState)) {
                        throw std::runtime_error("input is not DepthRead_");
                    }
                    continue;
                }
            }
            mViewStates[get_key(input)].mStates.emplace_back(
                NodeRenderTargetState{ gsl::narrow<uint32_t>(nodeID), { input.mState } }
            );
        }
    }
}

void GraphicsRenderNodeGraph::buildRenderStatePaths2() {
    for (auto& [name, v] : mViewStates) {
        if (v.mStates.empty())
            throw std::runtime_error("empty render value states");
        Expects(v.mFullStates.empty());

        // build fullstates
        size_t i = 0;
        for (size_t k = 0; k != mNodeSorted.size(); ++k) {
            auto nodeID = mNodeSorted[k];
            if (i == v.mStates.size()) {
                i = 0;
            }
            v.mFullStates.emplace_back(
                NodeRenderTargetState{ gsl::narrow<uint32_t>(nodeID), { v.mStates[i].mRenderTargetState } }
            );

            if (nodeID == v.mStates[i].mNodeID) {
                ++i;
            }
        }

        // build transitions
        for (size_t k = 0; k != v.mFullStates.size(); ++k) {
            const auto& curr = v.mFullStates[k];
            const auto& next = getNextState(v, k);
            const auto& target = getNextDifferentState(v, k);
            if (target && next.mRenderTargetState != curr.mRenderTargetState) {
                v.mTransitions.emplace_back(
                    RenderTargetStateTransition{ curr.mNodeID, curr.mRenderTargetState, target->mRenderTargetState }
                );
            }
        }
    }

    if (mConfig.mVerbose) {
        outputValueStates();
    }
}

void GraphicsRenderNodeGraph::buildResourceViews() {
    if (mNodeSorted.size() != num_vertices(mNodeGraph)) {
        throw std::invalid_argument("node order and node graph size inconsistent, please sort graph first");
    }

    OrderedIdentityMap<rtv_type> rtvs;
    OrderedIdentityMap<dsv_type> dsvs;

    for (size_t k = 0; k != mNodeSorted.size(); ++k) {
        auto nodeID = mNodeSorted[k];
        const auto& node = mNodeGraph[nodeID];

        for (const auto& output : node.mOutputs) {
            const auto& rt = at(mRenderTargets, output.mName);
            if (isBackBuffer(rt))
                continue;

            visit(overload(
                [&](const RenderTarget_& view) {
                    rtvs.emplace(output.mName, output.mData, output.mModel);
                },
                [&](const DepthWrite_& view) {
                    dsvs.emplace(output.mName, output.mData, false);
                },
                [&](const DepthRead_& view) {
                    dsvs.emplace(output.mName, output.mData, true);
                },
                [&](auto) {}
            ), output.mState);
        }

        OrderedIdentityMap<descriptor_type> table;
        for (const auto& input : node.mInputs) {
            const auto& rt = at(mRenderTargets, input.mName);
            if (isBackBuffer(rt))
                continue;

            visit(overload(
                [&](const DepthRead_& view) {
                    auto res = table.emplace(SRV, input.mName, input.mData, input.mModel);
                    if (res.second == false) {
                        throw std::runtime_error("srv already exists: " + input.mName);
                    }
                },
                [&](const ShaderResource_& view) {
                    auto res = table.emplace(SRV, input.mName, input.mData, input.mModel);
                    if (res.second == false) {
                        throw std::runtime_error("dsv already exists: " + input.mName);
                    }
                },
                [&](const UnorderedAccess_& view) {
                    auto res = table.emplace(UAV, input.mName, input.mData, input.mModel);
                    if (res.second == false) {
                        throw std::runtime_error("uav already exists: " + input.mName);
                    }
                },
                [&](auto) {}
            ), input.mState);
        }

        for (const auto& d : table) {
            mCBV_SRV_UAVs.emplace_back(d);
        }

        mRangeCBV_SRV_UAVs.emplace_back(gsl::narrow<uint32_t>(table.size()));
    }

    // reorder rtv, dsv
    for (const auto& rtv : rtvs) {
        mRTVs.emplace(rtv);
    }
    for (const auto& dsv : dsvs) {
        mDSVs.emplace(dsv);
    }
}

void GraphicsRenderNodeGraph::createValues(size_t nodeID) {
    // this function will only be called in ShaderGraph
    auto& node = mNodeGraph[nodeID];

    auto createValue = [&](const RenderValue& value) {


        auto valueID = add_vertex(mValueGraph);
        mValueGraph[valueID] = make_key(nodeID, value);
        auto res = mValueIndex.emplace(make_key(nodeID, value), valueID);
        // this is assured by algorithm
        Ensures(res.second);
        std::ignore = res;
        return valueID;
    };

    // step 1
    for (const auto& output : node.mOutputs) {
        auto key = make_key(nodeID, output);
        auto iter = mValueIndex.find(key);
        // this is assured by algorithm
        Expects(iter == mValueIndex.end());
        createValue(output);
    }

    // step 2
    for (const auto& input : node.mInputs) {
        auto key = make_key(nodeID, input);
        auto iter = mValueIndex.find(key);
        if (iter == mValueIndex.end()) {
            createValue(input);
        } else { // already exists, must be added by step 1
            bool bOutput = (node.mOutputs.find(get_key(input)) != node.mOutputs.end());
            Ensures(bOutput);
            std::ignore = bOutput;
        }
    }
}

void GraphicsRenderNodeGraph::outputValueStates() const {
    for (const auto& v : mViewStates) {
        {
            CONSOLE_COLOR(Yellow);
            std::cout << v.first.second << "\n";
        }
        std::cout << "value: ";
        {
            CONSOLE_COLOR(Green);
            std::cout << v.first.first;
        }
        std::cout << std::string(std::max(0, 14 - (int)v.first.first.size()), ' ');

        int i = 0;
        for (const auto& state : v.second.mStates) {
            if (i++)
                std::cout << ", ";
            std::cout << state.mNodeID << " " << getRenderTargetStateName(state.mRenderTargetState);
        }
        {
            std::cout << ", ";
            CONSOLE_COLOR(Cyan);
            auto idx = findIndex(v.second, v.second.mStates.back().mNodeID);
            std::cout << "initial: " <<
                getStateName(getPrevState(v.second, idx).mRenderTargetState.mState);
        }
        std::cout << std::endl;

        i = 0;
        std::cout << "full states:         ";
        for (const auto& state : v.second.mFullStates) {
            if (i++)
                std::cout << ", ";
            std::cout << state.mNodeID << " " << getRenderTargetStateName(state.mRenderTargetState);
        }
        std::cout << std::endl;

        i = 0;
        std::cout << "transitions:         ";
        for (const auto& t : v.second.mTransitions) {
            if (i++)
                std::cout << ", ";

            std::cout << t.mNodeID << " "
                << getRenderTargetStateName(t.mTarget) << " <- "
                << getRenderTargetStateName(t.mSource);
        }
        std::cout << std::endl;
    }
}

void GraphicsRenderNodeGraph::outputViews() const {
    {
        std::cout << "\n";
        CONSOLE_COLOR(Cyan);
        std::cout << "RTVs:" << "\n";
    }
    for (const auto& rtv : mRTVs) {
        std::cout << get<0>(rtv);
        std::cout << ": " << get<1>(rtv) << ", " << get<2>(rtv) << "\n";
    }

    {
        std::cout << "\n";
        CONSOLE_COLOR(Cyan);
        std::cout << "DSVs:" << "\n";
    }
    for (const auto& dsv : mDSVs) {
        std::cout << get<0>(dsv);
        std::cout << ": " << get<1>(dsv) << ", " << (get<2>(dsv) ? "Read":"Write") << "\n";
    }

    {
        std::cout << "\n";
        CONSOLE_COLOR(Cyan);
        std::cout << "CBV_SRV_UAVs:" << "\n";
    }

    auto sz = mNodeSorted.size();
    size_t idx = 0;
    for (size_t k = 0; k != sz; ++k) {
        auto nodeID = mNodeSorted[k];
        const auto& node = mNodeGraph[nodeID];
        std::cout << "\n";
        {
            std::cout << "RenderNode: ";
            CONSOLE_COLOR(Magenta);
            std::cout << node.mName << std::endl;
        }

        auto space = std::string(4, ' ');

        if (mRangeCBV_SRV_UAVs[k] == 0) {
            std::cout << space << "[none]" << std::endl;
        } else {
            for (size_t i = 0; i != mRangeCBV_SRV_UAVs[k]; ++i) {
                const auto& view = mCBV_SRV_UAVs[idx++];
                std::cout << space << get<0>(view) << ", " << get<1>(view) << ", " << get<2>(view) << ", " << get<3>(view) << std::endl;
            }
        }
    }
}

}
