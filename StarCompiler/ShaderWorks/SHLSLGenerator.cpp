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

template<class T>
void outputAttribute(std::ostream& oss, std::string& space,
    const ShaderAttribute& attr, T tag, uint32_t& slotID, uint32_t spaceID
) {
    oss << getName(tag);
    if (!std::holds_alternative<std::monostate>(attr.mModel)) {
        oss << "<" << getModelName(attr.mModel, HLSL) << ">";
    }
    oss << " m" << attr.mName;
    // output array
    visit(overload(
        [&](Bounded_) {
            visit(overload(
                [](DefaultView_) {
                    // do nothing
                },
                [&](const TextureView& view) {
                    visit(overload(
                        [&](const auto&) {
                            // do nothing
                        },
                        [&](const ArrayRange& range) {
                            oss << "[" << range.mArraySize << "]";
                        },
                        [&](const CubeRange& range) {
                            oss << "[" << range.mNumCubes << "]";
                        }
                    ), view.mArrayOrDepthView);
                }
            ), attr.mData);
        },
        [&](Unbounded_) {
            oss << "[]";
        }
    ), attr.mDescriptor.mBoundedness);

    // output register, space
    oss << " : register(" << getRegisterPrefix(attr.mDescriptor.mDescriptorType)
        << slotID;
    if (spaceID) {
        oss << ", space" << spaceID;
    }
    oss << ");\n";

    // advance descriptor
    visit(overload(
        [&](Bounded_) {
            slotID += getDescriptorCapacity(attr);
        },
        [&](Unbounded_) {
            slotID = -1;
        }
    ), attr.mDescriptor.mBoundedness);
}

void outputAttribute(std::ostream& oss, std::string& space,
    const ShaderAttribute& attr, uint32_t& slotID, uint32_t spaceID,
    const ShaderGroup& parent,
    const DescriptorIndex& index,
    const RootSignature* pRSG = nullptr
) {
    visit(overload(
        [&](CBuffer_) {
            oss << "cbuffer " << getName(index.mUpdate) << " : register(b"
                << slotID;
            if (spaceID) {
                oss << ", space" << spaceID;
            }
            oss << ") {\n";
            {
                INDENT();
                if (pRSG) {
                    const auto& cb = pRSG->mDatabase.mConstantBuffers.at(index);
                    for (const auto& c : cb.mValues) {
                        oss << space << getHLSLName(c.mType) << " m" << c.mName << ";\n";
                    }
                } else {
                    const auto& cb = parent.getConstantBuffer(index);
                    for (const auto& c : cb.mValues) {
                        oss << space << getHLSLName(c.mType) << " m" << c.mName << ";\n";
                    }
                }
            }
            oss << "};\n";
            slotID += getDescriptorCapacity(attr);
        },
        [&](Buffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](ByteAddressBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](StructuredBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture1D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture1DArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture2D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture2DArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture2DMS_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture2DMSArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](Texture3D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](TextureCube_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](TextureCubeArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](AppendStructuredBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](ConsumeStructuredBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWByteAddressBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWStructuredBuffer_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWTexture1D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWTexture1DArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWTexture2D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWTexture2DArray_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](RWTexture3D_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [&](SamplerState_ tag) {
            outputAttribute(oss, space, attr, tag, slotID, spaceID);
        },
        [](const auto&) {
            throw std::runtime_error("invalid shader attribute");
        }
    ), attr.mType);
}

void outputAttributes(std::ostream& oss, std::string& space, const ShaderGroup& parent,
    const DescriptorList& list, const DescriptorIndex& index,
    const RootSignature* pRSG = nullptr
) {
    for (const auto& rangePair : list.mRanges) {
        const auto& type = rangePair.first;
        const auto& range = rangePair.second;
        Expects(!std::holds_alternative<std::monostate>(index.mVisibility));

        auto slotID = range.mStart;
        auto spaceID = range.mSpace;
        for (const auto& subrangePair : range.mSubranges) {
            const auto& source = subrangePair.first;
            const auto& subrange = subrangePair.second;
            oss << "// " << getVariantName(source) << "\n";
            for (const auto& attr : subrange.mAttributes) {
                outputAttribute(oss, space, attr, slotID, spaceID, parent, index, pRSG);
            }
        }
        Ensures(slotID - range.mStart <= range.mCount);
    }
    for (const auto& unboundedPair : list.mUnboundedDescriptors) {
        const auto& type = unboundedPair.first;
        const auto& unbounded = unboundedPair.second;
        oss << "// " << getVariantName(unbounded.mAttribute.mDescriptor.mSource) << "\n";
        auto slotID = unbounded.mStart;
        auto spaceID = unbounded.mSpace;
        outputAttribute(oss, space, unbounded.mAttribute, slotID, spaceID, parent, index, pRSG);
    }
}

}

std::string HLSLGenerator::generateAttributes(const AttributeMap& attrs,
    const ShaderStageType& stage, const ShaderGroup& currGroup, const RootSignature& rsg
) const {
    const auto& rsgGroup = currGroup.getRootSignatureShaderGroup();

    std::ostringstream oss;
    std::string space;
    int count = 0;
    for (int i = UpdateEnum::UpdateCount; i --> static_cast<int>(rsgGroup.mUpdateFrequency);) {
        for (const auto& collectionPair : rsgGroup.mRootSignature.mDatabase.mDescriptors) {
            const auto& index = collectionPair.first;
            const auto& collection = collectionPair.second;
            if (index.mUpdate != i) {
                continue;
            }
            if (index.mVisibility != getShaderVisibilityType(stage)) {
                continue;
            }

            if (count++)
                oss << "\n";

            oss << "// " << getName(index.mUpdate) << "\n";
            for (const auto& listPair : collection.mResourceViewLists) {
                const auto& spaceName = listPair.first;
                const auto& list = listPair.second;
                outputAttributes(oss, space, rsgGroup, list, index);
            }

            for (const auto& listPair : collection.mSamplerLists) {
                const auto& spaceName = listPair.first;
                const auto& list = listPair.second;
                outputAttributes(oss, space, rsgGroup, list, index);
            }
        }
    }

    for (int i = rsgGroup.mUpdateFrequency; i --> 0;) {
        for (const auto& collectionPair : rsg.mDatabase.mDescriptors) {
            const auto& index = collectionPair.first;
            const auto& collection = collectionPair.second;
            if (index.mUpdate != i) {
                continue;
            }
            if (index.mVisibility != getShaderVisibilityType(stage)) {
                continue;
            }

            if (count++)
                oss << "\n";

            oss << "// " << getName(index.mUpdate) << "\n";
            for (const auto& listPair : collection.mResourceViewLists) {
                const auto& spaceName = listPair.first;
                const auto& list = listPair.second;
                outputAttributes(oss, space, rsgGroup, list, index, &rsg);
            }

            for (const auto& listPair : collection.mSamplerLists) {
                const auto& spaceName = listPair.first;
                const auto& list = listPair.second;
                outputAttributes(oss, space, rsgGroup, list, index, &rsg);
            }
        }
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
