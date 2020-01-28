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

#include "SHLSLGenerator.h"
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderValue.h>
#include <StarCompiler/ShaderGraph/SShaderGroup.h>
#include <StarCompiler/ShaderGraph/SShaderRootSignature.h>
#include <StarCompiler/ShaderGraph/SShaderDescriptor.h>
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include <StarCompiler/ShaderGraph/SShaderRegisters.h>
#include <StarCompiler/Graphics/SRenderNames.h>

namespace Star::Graphics::Render::Shader {

HLSLGenerator::HLSLGenerator(const ShaderProgram& program, Language l)
    : mProgram(program)
    , mLanguage(l)
{
    for (const auto& [stage, shader] : mProgram.mShaders) {
        mInputs.emplace(stage, shader.mGraph.getShaderInputs());
        mOutputs.emplace(stage, shader.mGraph.getShaderOutputs());
    }
    mNamings.emplace(PS, ShaderStageContent{
        "PSInput", "input", "PSOutput", "output", "main"
    });
    mNamings.emplace(VS, ShaderStageContent{
        "VSInput", "input", "VSOutput", "output", "main"
    });
}

std::string HLSLGenerator::generateInput(const ShaderStageType& stage) const {
    std::ostringstream oss;
    std::string space;

    const auto& inputs = mInputs.at(stage);
    const auto& content = mNamings.at(stage);
    OSS << "struct " << content.mInputStruct << " {\n";
    INDENT();
    int slot = 0;
    auto prevSemantic = SemanticType();
    for (const auto& v : inputs) {
        if (v.mSemantic != prevSemantic) {
            slot = 0;
            prevSemantic = v.mSemantic;
        }

        OSS << getModelName(v.mValue, HLSL) << " "
            << v.mName << " : " << getSemanticName(v.mSemantic, slot, stage, true) << ";\n";
        ++slot;
    }
    UNINDENT();
    OSS << "};\n";

    return oss.str();
}

std::string HLSLGenerator::generateOutput(const ShaderStageType& stage) const {
    std::ostringstream oss;
    std::string space;

    const auto& outputs = mOutputs.at(stage);
    const auto& content = mNamings.at(stage);
    OSS << "struct " << content.mOutputStruct << " {\n";
    INDENT();
    int slot = 0;
    auto prevSemantic = SemanticType();
    for (const auto& v : outputs) {
        if (v.mSemantic != prevSemantic) {
            slot = 0;
            prevSemantic = v.mSemantic;
        }

        OSS << getModelName(v.mValue, HLSL) << " "
            << v.mName << " : " << getSemanticName(v.mSemantic, slot, stage, false) << ";\n";
        ++slot;
    }
    UNINDENT();
    OSS << "};\n";

    return oss.str();
}

std::string HLSLGenerator::generateModules() const {
    std::ostringstream oss;
    std::string space;

    for (const auto& p : mProgram.mGraph.mNodeIndex) {
        const auto& node = mProgram.mGraph.mNodeGraph[p.second];
        if (getContent(node).empty())
            continue;
        if (node.mBuilderFlags & Inline)
            continue;

        oss << "\n";
        copyString(oss, space, generateModule(node));
    }

    return oss.str();
}

std::string HLSLGenerator::generateShader(const ShaderStageType& stage) const {
    std::ostringstream oss;
    bool bOuputByParameters = std::holds_alternative<PS_>(stage);
    const auto& inputs = mInputs.at(stage);
    if (bOuputByParameters) {
        if (!inputs.empty()) {
            oss << generateInput(stage) << std::endl;
        }
        oss << generateMain(stage);
    } else {
        if (!inputs.empty()) {
            oss << generateInput(stage) << std::endl;
        }
        oss << generateOutput(stage);
        oss << "\n";
        oss << generateMain(stage);
    }

    return oss.str();
}

namespace {

void outputDescriptor(std::ostream& oss, std::string space,
    const AttributeMap& attrs,
    const ShaderProgram& program,
    const ShaderGroup* pGroup, const RootSignature* pRSG,
    const DescriptorIndex& index, const Descriptor& d,
    ShaderRegister& slots
) {
    visit(overload(
        [&](const auto& v) {
            visit(overload(
                [&](ConstantBuffer_) {
                    oss << "cbuffer " << getName(index.mUpdate) << " : register(b"
                        << slots.get(index.mVisibility, d.mType, d.mSpace) << ") {\n";
                    {
                        INDENT();
                        if (pGroup) {
                            const auto& cb = pGroup->getConstantBuffer(index);
                            for (const auto& c : cb.mValues) {
                                oss << space << getHLSLName(c.mType) << " m" << c.mName << ";\n";
                            }
                        } else if (pRSG) {
                            const auto& cb = pRSG->mConstantBuffers.at(index);
                            for (const auto& c : cb.mValues) {
                                oss << space << getHLSLName(c.mType) << " m" << c.mName << ";\n";
                            }
                        } else {
                            throw std::runtime_error("constant buffer not found");
                        }
                    }
                    oss << "};\n";
                    slots.increase(index.mVisibility, d.mType, d.mSpace);
                },
                [&](const auto& v) {
                    const auto& attr = at<Index::Name>(attrs, d.mName);
                    oss << getName(v);
                    if (!std::holds_alternative<std::monostate>(attr.mModel)) {
                        oss << "<" << getModelName(attr.mModel, HLSL) << ">";
                    }
                    oss << " m" << d.mName << " : register(" << getRegisterPrefix(d.mType)
                        << slots.get(index.mVisibility, d.mType, d.mSpace) << ");\n";
                    slots.increase(index.mVisibility, d.mType, d.mSpace);
                },
                [&](const DescriptorArray& r) {
                    throw std::runtime_error("should not reach here");
                }
            ), v);
        }
    ), d.mModel);
}

}

std::string HLSLGenerator::generateAttributes(const AttributeMap& attrs,
    const ShaderStageType& stage, const ShaderGroup& currGroup, const RootSignature& rsg
) const {
    const auto& group = currGroup.getRootSignatureShaderGroup();
    ShaderRegister slots;
    for (uint i = group.mUpdateFrequency; i != UpdateCount; ++i) {
        group.mRootSignature.reserveRegisters(static_cast<UpdateEnum>(i), slots);
    }
    for (uint i = PerInstance; i != group.mUpdateFrequency; ++i) {
        rsg.reserveRegisters(static_cast<UpdateEnum>(i), slots);
    }

    std::ostringstream oss;
    std::string space;
    int count = 0;
    for (const auto& t : group.mRootSignature.mTables) {
        const auto& index = t.first;
        const auto& table = t.second;
        auto ra = getShaderVisibilityType(stage);
        if (!std::holds_alternative<std::monostate>(index.mVisibility) && index.mVisibility != ra)
            continue;

        if (count++)
            oss << "\n";

        oss << "// " << getName(index.mUpdate);
        if (std::holds_alternative<std::monostate>(index.mVisibility)) {
            oss << ", all stages";
        }
        oss << "\n";
        auto output = [&](const Descriptor& d) {
            visit(overload(
                [&](const auto& v) {
                    visit(overload(
                        [&](const auto&) {
                            outputDescriptor(oss, space, attrs, mProgram, &group, nullptr, index, d, slots);
                        },
                        [&](const DescriptorArray& r) {
                            visit(overload(
                                [&](const RangeBounded& arr) {
                                    auto begSlot = slots.get(index.mVisibility, d.mType, d.mSpace);
                                    auto iter = rsg.mTables.find(index);
                                    if (iter != rsg.mTables.end()) {
                                        for (const auto& d2 : iter->second.mDescriptors) {
                                            if (d2.mType != d.mType || d2.mSpace != d.mSpace) {
                                                throw std::runtime_error("program descriptor inconsistent");
                                            }
                                            outputDescriptor(oss, space, attrs, mProgram, nullptr, &rsg, index, d2, slots);
                                        }
                                    }
                                    auto current = slots.get(index.mVisibility, d.mType, d.mSpace);
                                    auto endSlot = begSlot + arr.mCount;
                                    if (current != endSlot && mDebug) {
                                        if (endSlot - current == 1) {
                                            oss << "// " << getVariantName(index.mVisibility) << ", register(" << getRegisterPrefix(d.mType) << current << ") not used\n";
                                        } else {
                                            oss << "// " << getVariantName(index.mVisibility) << ", register(" << getRegisterPrefix(d.mType) << current << "-" << endSlot << ") not used\n";
                                        }
                                    }
                                    slots.increase(index.mVisibility, d.mType, d.mSpace, endSlot - current);
                                },
                                [](RangeUnbounded) {
                                    throw std::runtime_error("not supported yet");
                                }
                            ), r);
                        }
                    ), v);
                }
            ), d.mModel);
        };

        visit(overload(
            [&](Constants_) {
                throw std::invalid_argument("root signature Constants not supported yet");
            },
            [&](auto) {
                for (const auto& d : table.mDescriptors) {
                    output(d);
                }
            }
        ), index.mType);
    }

    return oss.str();
}

std::string HLSLGenerator::renameAttributes(const ShaderModule& node) const {
    auto content = std::string(getContent(node));
    for (const auto& attr : node.mAttributes) {
        std::string name = "\\b(" + attr.mName + ")\\b";
        std::regex e(name);
        if (mAttributeRegex.empty()) {
            content = std::regex_replace(content, e, "m$1");
        } else {
            content = std::regex_replace(content, e, mAttributeRegex);
        }
    }
    return content;
}

std::string HLSLGenerator::generateModule(const ShaderModule& node) const {
    std::ostringstream oss;
    std::string space;

    OSS << "void " << node.mName << "(";
    int count = 0;
    // input
    for (const auto& v : node.mInputs) {
        auto iter = node.mOutputs.find(v.mName);
        if (iter != node.mOutputs.end()) {
            continue;
        }
        if (count) {
            oss << ", ";
        }
        oss << getModelName(v.mValue, HLSL) << " " << v.mName;
        ++count;
    }

    // output and inout
    for (const auto& v : node.mOutputs) {
        if (count) {
            oss << ", ";
        }

        auto iter = node.mInputs.find(v.mName);
        if (iter != node.mInputs.end()) {
            oss << "inout ";
        } else {
            oss << "out ";
        }

        oss << getModelName(v.mValue, HLSL) << " " << v.mName;
        ++count;
    }

    oss << ") {\n";
    {
        INDENT();
        copyString(oss, space, renameAttributes(node));
    }

    OSS << "}\n";

    return oss.str();
}

std::string_view HLSLGenerator::getContent(const ShaderModule& node) const {
    if (node.mContents.empty())
        return {};

    auto iter = node.mContents.find(mLanguage.index());
    if (iter != node.mContents.end()) {
        return iter->mContent;
    } else {
        iter = node.mContents.find(0);
        if (iter != node.mContents.end()) {
            return iter->mContent;
        }
    }
    
    return {};
}

std::string HLSLGenerator::generateMain(const ShaderStageType& stage) const {
    std::ostringstream oss;
    std::string space;
    std::set<std::string> declared;

    const auto& shader = mProgram.mShaders.at(stage);

    bool bOuputByParameters = std::holds_alternative<PS_>(stage);

    if (bOuputByParameters) {
        copyString(oss, space, generateMainSignatureByParameters(shader, declared) + " {\n");
    } else {
        copyString(oss, space, generateMainSignature(shader, declared) + " {\n");
    }

    INDENT();    
    copyString(oss, space, generateInputCopy(shader, declared));
    
    int count = 0;
    for (auto iter = shader.mGraph.mNodeSorted.rbegin();
        iter != shader.mGraph.mNodeSorted.rend(); ++iter)
    {
        const auto& node = shader.mGraph.mNodeGraph[*iter];
        if (!getContent(node).empty()) {
            if (count++ == 0) {
                if (!mInputs.at(stage).empty()) {
                    oss << "\n";
                }
            } else {
                oss << "\n";
            }
            copyString(oss, space, generateModuleExec(node, declared));
        }
    }

    if (!bOuputByParameters) {
        copyString(oss, space, generateMainReturn(shader));
    }

    UNINDENT();
    OSS << "}\n";
    return oss.str();
}

std::string HLSLGenerator::generateMainSignature(const ShaderStage& shader, std::set<std::string>& locals) const {
    std::ostringstream oss;
    const auto& stage = shader.mStage;
    const auto& naming = mNamings.at(stage);

    const auto& inputs = mInputs.at(stage);
    if (inputs.empty()) {
        oss << naming.mOutputStruct << " " << naming.mMain << "()";
    } else {
        oss << naming.mOutputStruct << " " << naming.mMain << "("
            << naming.mInputStruct << " " << naming.mInputVariable << ")";
    }

    return oss.str();
}

std::string HLSLGenerator::generateMainSignatureByParameters(const ShaderStage& shader, std::set<std::string>& locals) const {
    std::ostringstream oss;
    const auto& stage = shader.mStage;
    const auto& naming = mNamings.at(stage);

    const auto& inputs = mInputs.at(stage);
    int count = 0;
    if (inputs.empty()) {
        oss << "void " << naming.mMain << "(";
    } else {
        oss << "void " << naming.mMain << "(" << naming.mInputStruct << " " << naming.mInputVariable;
        ++count;
    }

    auto outputs = mOutputs.at(stage);
    auto prevSemantic = SemanticType();
    size_t slot = 0;
    for (const auto& output : outputs) {
        const auto& v = output;
        if (prevSemantic != output.mSemantic) {
            prevSemantic = output.mSemantic;
            slot = 0;
        }
        if (count++)
            oss << ", ";
        oss << "out " << getModelName(v.mValue, HLSL) << " " << v.mName << " : " << getSemanticName(v.mSemantic, slot, stage, false);
        locals.emplace(v.mName);
        ++slot;
    }
    oss << ")";

    return oss.str();
}

std::string HLSLGenerator::generateInputCopy(const ShaderStage& shader, std::set<std::string>& locals) const {
    std::ostringstream oss;

    const auto& stage = shader.mStage;
    const auto& naming = mNamings.at(stage);

    auto inputs = mInputs.at(stage);
    for (const auto& v : inputs) {
        auto res = locals.emplace(v.mName);
        if (res.second) {
            oss << getModelName(v.mValue, HLSL) << " " << v.mName << " = "
                << naming.mInputVariable << "." << v.mName << ";\n";
        } else {
            oss << v.mName << " = "
                << naming.mInputVariable << "." << v.mName << ";\n";
        }
    }

    return oss.str();
}

std::string HLSLGenerator::generateModuleExec(const ShaderModule& node, std::set<std::string>& locals) const {
    std::ostringstream oss;
    std::string space;

    // declare input
    for (const auto& v : node.mInputs) {
        auto iter = locals.find(v.mName);
        if (iter == locals.end()) {
            throw std::runtime_error("variable not declared");
        }
    }

    // declare output
    for (const auto& v : node.mOutputs) {
        auto iter = locals.find(v.mName);
        if (iter == locals.end()) {
            locals.emplace(v.mName);
            if (!(v.mBuilderFlags & NoDeclare))
                oss << getModelName(v.mValue, HLSL) << " " << v.mName << ";\n";
        }
    }

    if (node.mBuilderFlags& Inline) {
        if (!getContent(node).empty()) {
            copyString(oss, space, renameAttributes(node));
        }
    } else {
        OSS << node.mName << "(";
        int count = 0;
        // input
        for (const auto& v : node.mInputs) {
            auto iter = node.mOutputs.find(v.mName);
            if (iter != node.mOutputs.end()) {
                continue;
            }
            if (count) {
                oss << ", ";
            }
            oss << v.mName;
            ++count;
        }

        // output and inout
        for (const auto& v : node.mOutputs) {
            if (count) {
                oss << ", ";
            }
            oss << v.mName;
            ++count;
        }
        oss << ");\n";
    }

    return oss.str();
}

std::string HLSLGenerator::generateOutputCopy(const ShaderStage& shader) const {
    std::ostringstream oss;
    const auto& naming = mNamings.at(shader.mStage);
    const auto& outputs = mOutputs.at(shader.mStage);
    for (const auto& output : outputs) {
        const auto& v = output;
        oss << naming.mOutputVariable << "." << v.mName << " = " << v.mName << ";\n";
    }
    return oss.str();
}

std::string HLSLGenerator::generateMainReturn(const ShaderStage& shader) const {
    std::ostringstream oss;
    const auto& naming = mNamings.at(shader.mStage);
    oss << "\n";
    oss << naming.mOutputStruct << " " << naming.mOutputVariable << ";\n";
    copyString(oss, generateOutputCopy(shader));
    oss << "\n";
    oss << "return " << naming.mOutputVariable << ";\n";
    return oss.str();
}

}
