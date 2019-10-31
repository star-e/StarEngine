// Copyright (C) 2019 star.engine at outlook dot com
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

#include "SShaderProgram.h"
#include "SShaderModule.h"
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include <StarCompiler/ShaderGraph/SShaderSemantics.h>
#include <StarCompiler/SGetVariantName.h>
#include <StarCompiler/ShaderGraph/SShaderDescriptor.h>
#include <StarCompiler/ShaderGraph/SShaderRootSignature.h>
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>

namespace Star::Graphics::Render::Shader {

using namespace ModuleDSL;

bool ShaderProgram::stageBegin(ShaderStageType stage, NameMap<ShaderValue> outputs) {
    visit(overload(
        [&](OM_) {
            mGraph.createNode(createShaderModule( "Output",
                Attributes{},
                Outputs{ outputs },
                Inputs{ outputs }
            ), OM);
        },
        [&](CS_) {},
        [&](auto s) {
            if (!outputs.empty()) {
                throw std::invalid_argument("Output["s + getName(s) + "] have no outputs");
            }
        }
    ), stage);

    if (mPrevStage == stage) {
        return false;
    }
    mPrevStage = stage;
    return true;
}

bool ShaderProgram::stageEnd(ShaderStageType stage) {
    if (mPrevStage != stage) {
        throw std::runtime_error("shader stage not match");
    }
    mPrevStage = stage;

    if (std::holds_alternative<OM_>(stage))
        return true;

    visit(overload(
        [&](OM_) {},
        [&](PS_) {
            auto outputs = mGraph.getShaderOutputs();
            if (outputs.empty()) {
                throw std::invalid_argument("PS has no output");
            }
            auto inputs = mGraph.getNodeInputsWithoutSource();
            std::set<std::string> positions;
            for (const auto& [nodeID, input] : inputs) {
                if (std::holds_alternative<SV_Position_>(input.mSemantic)) {
                    positions.emplace(input.mName);
                }
            }
            if (positions.size() > 1) {
                throw std::invalid_argument("multiple SV_Position inputs");
            }
            if (positions.size() == 1) {
                return;
            }

            auto nodeID = mGraph.createNode(createShaderModule("Input[PS]", System,
                Attributes{},
                Outputs{},
                Inputs{
                    { "clipPos", float4(), SV_Position }
                }
            ), PS);

            mGraph.connectNodeAndValues(nodeID, 0);
        },
        [&](CS_) {},
        [&](auto s) {
            auto inputsNeeded = mGraph.getNodeInputsWithoutSource();
            uint32_t count = 0;
            for (const auto& [nodeID, input] : inputsNeeded) {
                if (!std::holds_alternative<decltype(s)>(mGraph.mNodeStages[nodeID])) {
                    auto semantic = getShaderStages(input.mSemantic);
                    if (semantic & SS_Value) {
                        ++count;
                    } else {
                        throw std::invalid_argument("SV not supported yet");
                    }
                }
            }
            if (count) {
                Outputs outputs;
                Inputs inputs;

                for (const auto& [nodeID, input] : inputsNeeded) {
                    if (!std::holds_alternative<decltype(s)>(mGraph.mNodeStages[nodeID])) {
                        auto semantic = getShaderStages(input.mSemantic);
                        if (semantic & SS_Value) {
                            ++count;
                            outputs.emplace(input);
                            inputs.emplace(input);
                        }
                    }
                }
                auto inputNodeID = mGraph.createNode(
                    createShaderModule("Input["s + getName(s) + "]", System,
                        Attributes{},
                        std::move(outputs),
                        std::move(inputs)
                    ), s);

                for (const auto& [nodeID, input] : inputsNeeded) {
                    if (!std::holds_alternative<decltype(s)>(mGraph.mNodeStages[nodeID])) {
                        auto semantic = getShaderStages(input.mSemantic);
                        if (semantic & SS_Value) {
                            mGraph.connectNodeAndValues(inputNodeID, nodeID);
                        }
                    }
                }
            }
        }
    ), stage);

    auto res = mShaders.emplace(std::pair{ stage, ShaderStage{ stage } });
    if (!res.second) {
        throw std::invalid_argument("multiple shader stage definition");
    }

    return true;
}

void ShaderProgram::compile() {
    if (mGraph.compile()) {
        throw std::invalid_argument("shader program graph compilation failed");
    }

    for (auto& [stage, shader] : mShaders) {
        mGraph.getSubGraph(stage, shader.mGraph);
        auto& graph = shader.mGraph;
        graph.compile();
        auto optStage = graph.isShader();
        if (!optStage) {
            throw std::runtime_error("shader stage compilation failed, has multiple stages");
        }
        if (stage != *optStage) {
            throw std::runtime_error("shader stage compilation failed, different stages");
        }
    }
}

void ShaderProgram::buildConstantBuffers(const AttributeMap& attrs, RootSignature& rsg) const {
    for (const auto& nodeID : mGraph.mNodeSorted) {
        const auto& node = mGraph.mNodeGraph[nodeID];
        const auto& stage = mGraph.mNodeStages[nodeID];
        for (const auto& usage : node.mAttributes) {
            const auto& attr = at(attrs, get_key(usage));
            rsg.addConstant(attr, stage);
        }
    }
}

void ShaderProgram::buildDescriptors(const AttributeMap& attrs, RootSignature& rsg) const {
    for (const auto& [index, cb] : rsg.mConstantBuffers) {
        rsg.addConstantBufferDescriptor(index, cb);
    }

    for (const auto& nodeID : mGraph.mNodeSorted) {
        const auto& node = mGraph.mNodeGraph[nodeID];
        const auto& stage = mGraph.mNodeStages[nodeID];
        for (const auto& usage : node.mAttributes) {
            const auto& attr = at(attrs, get_key(usage));
            if (attr.mFlags & VisibleAll) {
                rsg.addDescriptor(attr, RA_All);
            } else {
                auto ra = getRootAccessEnum(stage);
                rsg.addDescriptor(attr, ra);
            }
        }
    }
}

bool ShaderProgram::hasIA() const {
    auto vsInputs = mShaders.at(VS).mGraph.getShaderInputs();

    bool hasIA = false;
    for (const auto& input : vsInputs) {
        auto s = getShaderStages(input.mSemantic);
        if (s & VS_Interp) {
            hasIA = true;
        }
    }

    return hasIA;
}

}
