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

#include "SShaderGroup.h"
#include "SShaderProgram.h"
#include "SShaderDescriptor.h"
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include "SShaderRegisters.h"

namespace Star::Graphics::Render::Shader {

void ShaderGroup::validate() const {
    if (!mGroups.empty() && !mPrograms.empty()) {
        throw std::runtime_error("internal node should not have programs");
    }
    if (!mGroups.empty()) {
        int count = 0;
        int rootCount = 0;
        for (const auto& [name, pGroup] : mGroups) {
            ++count;
            if (pGroup->mGenerateRootSignature)
                ++rootCount;
        }
        if (rootCount && rootCount != count) {
            throw std::runtime_error("child group rsg generation should be the same");
        }
        if (rootCount == count) {
            if (mGenerateRootSignature == true) {
                throw std::runtime_error("if child group generate rsg, parent should not generate rsg");
            }
        }
    }
}

void ShaderGroup::buildConstantBuffers(const AttributeMap& attrs) {
    for (auto& [name, pair] : mPrograms) {
        auto& [program, rsg] = pair;
        program->buildConstantBuffers(attrs, rsg);
    }
}

void ShaderGroup::collectConstantBuffers() {
    if (mGroups.empty()) {
        for (auto& [name, pair] : mPrograms) {
            auto& [program, rsg] = pair;
            for (uint32_t i = mUpdateFrequency; i != UpdateCount; ++i) {
                rsg.mergeConstantBuffers(static_cast<UpdateEnum>(i), mRootSignature);
            }
        }
    } else {
        for (const auto& [name, pGroup] : mGroups) {
            for (uint32_t i = mUpdateFrequency; i != UpdateCount; ++i) {
                pGroup->mRootSignature.mergeConstantBuffers(static_cast<UpdateEnum>(i), mRootSignature);
            }
        }
    }
    mRootSignature.mergeConstantBuffers(mUpdateFrequency, mRootSignature);
}

void ShaderGroup::collectDescriptors(const AttributeMap& attrs) {
    for (const auto& [index, cb] : mRootSignature.mConstantBuffers) {
        mRootSignature.addConstantBufferDescriptor(index, cb);
    }

    if (mGroups.empty()) {
        // Leaf Node
        for (auto& [name, pair] : mPrograms) {
            auto& [program, rsg] = pair;
            program->buildDescriptors(attrs, rsg);
        }

        for (uint32_t i = PerInstance; i != mUpdateFrequency; ++i) {
            std::map<DescriptorIndex, DescriptorTableCapacity> caps;
            for (auto& [name, pair] : mPrograms) {
                auto& [program, rsg] = pair;
                rsg.collectCapacities(static_cast<UpdateEnum>(i), caps);
            }
            mRootSignature.resizeCapacities(caps);
        }

        if (mGenerateRootSignature) {
            for (uint32_t i = mUpdateFrequency; i != UpdateCount; ++i) {
                for (auto& [name, pair] : mPrograms) {
                    auto& [program, rsg] = pair;
                    rsg.collectDescriptors(static_cast<UpdateEnum>(i), mRootSignature);
                }
            }
        } else {
            if (hasChildGenerateRootSignature()) {
                // do nothing 
            } else {
                throw std::runtime_error("internal group not supported yet");
            }
        }
    } else {
        if (mGenerateRootSignature) {
            throw std::runtime_error("internal group not supported yet");
        } else {
            // do nothing
        }
    }
}

bool ShaderGroup::hasChildGenerateRootSignature() const {
    for (const auto& [name, pGroup] : mGroups) {
        if (pGroup->mGenerateRootSignature)
            return true;
    }
    return false;
}

bool ShaderGroup::hasIA() const {
    bool hasIA = false;
    for (const auto& [name, pair] : mPrograms) {
        auto& [program, rsg] = pair;
        if (program->hasIA()) {
            hasIA = true;
            break;
        }
    }
    for (const auto& [name, pGroup] : mGroups) {
        if (pGroup->hasIA()) {
            hasIA = true;
            break;
        }
    }
    return hasIA;
}

std::string ShaderGroup::generateRootSignature() const {
    if (!mGenerateRootSignature) {
        throw std::runtime_error("this shader group does not generate root signature");
    }

    uint32_t flags{};
    if (hasIA())
        flags |= ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    bool hasPS = false;
    bool hasGS = false;
    bool hasDS = false;
    bool hasHS = false;
    bool hasVS = false;

    for (const auto& [index, table] : mRootSignature.mTables) {
        switch (index.mVisibility) {
        case RA_All:
            hasPS = hasGS = hasDS = hasHS = hasVS = true;
            break;
        case RA_PS:
            hasPS = true;
            break;
        case RA_GS:
            hasGS = true;
            break;
        case RA_DS:
            hasDS = true;
            break;
        case RA_HS:
            hasHS = true;
            break;
        case RA_VS:
            hasVS = true;
            break;
        default:
            throw std::runtime_error("unknown visibility");
        }
    }
    if (!hasPS)
        flags |= ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

    if (!hasGS)
        flags |= ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

    if (!hasDS) 
        flags |= ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;

    if (!hasHS)
        flags |= ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;

    if (!hasVS)
        flags |= ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS;


    std::ostringstream oss;
    std::string space;

    std::string bol = "\"";
    std::string eol = "\" \\\n";

    oss << "#define main \\\n";
    OSS << bol << "RootFlags(" << eol;
    {
        int flagCount = 0;
        INDENT();

#define OUTPUT_FLAG(FLAG) \
        if (flags & BOOST_PP_CAT(ROOT_SIGNATURE_FLAG_, FLAG)) {\
            if (flagCount++) {\
                oss << " |"<< eol;\
            }\
            OSS << bol;\
            oss << BOOST_PP_STRINGIZE(FLAG);\
        }

        OUTPUT_FLAG(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        OUTPUT_FLAG(DENY_PIXEL_SHADER_ROOT_ACCESS);
        OUTPUT_FLAG(DENY_GEOMETRY_SHADER_ROOT_ACCESS);
        OUTPUT_FLAG(DENY_DOMAIN_SHADER_ROOT_ACCESS);
        OUTPUT_FLAG(DENY_HULL_SHADER_ROOT_ACCESS);
        OUTPUT_FLAG(DENY_VERTEX_SHADER_ROOT_ACCESS);
        OUTPUT_FLAG(LOCAL_ROOT_SIGNATURE);
        OUTPUT_FLAG(ALLOW_STREAM_OUTPUT);
        if (flagCount)
            oss << eol;
#undef OUTPUT_FLAG
    }
    OSS << bol << ")," << eol;

    ShaderRegister slots;
    // 1. reserve registers shared between all stages
    for (uint i = mUpdateFrequency; i != UpdateCount; ++i) {
        mRootSignature.reserveRegisters(static_cast<UpdateEnum>(i), slots);
    }
    for (uint i = PerInstance; i != mUpdateFrequency; ++i) {
        mRootSignature.reserveCapacityRegisters(static_cast<UpdateEnum>(i), slots);
    }

    // 2. build descriptors
    for (const auto& [index, table] : mRootSignature.mTables) {
        auto outputVisibility = [&]() {
            if (index.mVisibility != RA_All) {
                oss << ", visibility = ";
                int count = 0;
                if (index.mVisibility == RA_PS) {
                    if (count++)
                        oss << " | ";
                    oss << "SHADER_VISIBILITY_PIXEL";
                }
                if (index.mVisibility == RA_GS) {
                    if (count++)
                        oss << " | ";
                    oss << "SHADER_VISIBILITY_GEOMETRY";
                }
                if (index.mVisibility == RA_DS) {
                    if (count++)
                        oss << " | ";
                    oss << "SHADER_VISIBILITY_DOMAIN";
                }
                if (index.mVisibility == RA_HS) {
                    if (count++)
                        oss << " | ";
                    oss << "SHADER_VISIBILITY_HULL";
                }
                if (index.mVisibility == RA_VS) {
                    if (count++)
                        oss << " | ";
                    oss << "SHADER_VISIBILITY_VERTEX";
                }
            }
        };

        auto outputDetails = [&](const Descriptor& d) {
            if (d.mSpace)
                oss << ", space = " << d.mSpace;
            outputVisibility();
        };

        visit(overload(
            [&](Constants_) {
                for (const auto& d : table.mDescriptors) {
                    if (!std::holds_alternative<DescriptorCBV>(d.mModel)) {
                        throw std::runtime_error("contant descriptor is not cbv");
                    }
                    if (!std::holds_alternative<ConstantBuffer_>(std::get<DescriptorCBV>(d.mModel))) {
                        throw std::runtime_error("constant descriptor is not constant buffer");
                    }
                    throw std::invalid_argument("root signature Constants not supported yet");
                }
            },
            [&](auto type) {
                for (const auto& d : table.mDescriptors) {
                    if (DescriptorType(type) != getDescriptorType(d.mModel)) {
                        throw std::runtime_error("descriptor type and model inconsistent");
                    }
                    auto outputDescriptor = [&]() {
                        OSS << bol << getRootDescriptorName(type) << "(" << getRegisterPrefix(type) << slots.increase(index.mVisibility, type, d.mSpace);
                        outputDetails(d);
                        oss << ")," << eol;
                    };
                    
                    visit([&](const auto& dd) {
                        visit(overload(
                            [&](auto) {
                                outputDescriptor();
                            },
                            [&](const DescriptorRange& range) {
                                if (std::holds_alternative<RangeUnbounded>(range)) {
                                    throw std::runtime_error("root descriptor unbounded not supported");
                                }
                                const auto& arr = std::get<RangeBounded>(range);
                                for (uint32_t i = 0; i != arr.mCount; ++i) {
                                    outputDescriptor();
                                }
                            }
                        ), dd);
                    }, d.mModel);
                }
            },
            [&](SSV_) {
                for (const auto& d : table.mDescriptors) {
                    if (!std::holds_alternative<DescriptorSSV>(d.mModel)) {
                        throw std::runtime_error("contant descriptor is not srv");
                    }
                    auto outputSSV = [&]() {
                        OSS << bol << "StaticSampler(s" << slots.increase(index.mVisibility, SSV, d.mSpace);
                        outputDetails(d);
                        oss << ")," << eol;
                    };
                    visit(overload(
                        [&](auto) {
                            outputSSV();
                        },
                        [&](const DescriptorRange& range) {
                            if (std::holds_alternative<RangeUnbounded>(range)) {
                                throw std::runtime_error("root descriptor unbounded not supported");
                            }
                            const auto& arr = std::get<RangeBounded>(range);
                            for (uint32_t i = 0; i != arr.mCount; ++i) {
                                outputSSV();
                            }
                        }
                    ), std::get<DescriptorSSV>(d.mModel));
                }
            },
            [&](Table_) {
                OSS << bol << "DescriptorTable(";
                uint tableCount = 0;
                uint prevReg = 0;
                Descriptor prev{};

                auto finish = [&]() {
                    oss << getVariantName(prev.mType) << "(" << getRegisterPrefix(prev.mType);
                    oss << prevReg;

                    if (isUnbounded(prev.mModel)) {
                        oss << ", numDescriptors = unbounded";
                    } else {
                        uint numReg = slots.get(index.mVisibility, prev.mType, prev.mSpace) - prevReg;
                        if (numReg == 0)
                            throw std::runtime_error("num reg is 0");

                        if (numReg > 1) {
                            oss << ", numDescriptors = " << numReg;
                        }
                    }

                    if (prev.mSpace) {
                        oss << ", space = " << prev.mSpace;
                    }
                };

                for (const auto& d : table.mDescriptors) {
                    if (tableCount == 0 || prev.mType != d.mType || prev.mSpace != d.mSpace) {
                        if (tableCount++) {
                            finish();
                        }
                        prevReg = slots.get(index.mVisibility, d.mType, d.mSpace);
                    }

                    visit(overload(
                        [&](const auto& v) {
                            visit(overload(
                                [&](const auto&) {
                                    slots.increase(index.mVisibility, d.mType, d.mSpace);
                                },
                                [&](const DescriptorRange& r) {
                                    visit(overload(
                                        [&](const RangeBounded& arr) {
                                            slots.increase(index.mVisibility, d.mType, d.mSpace, arr.mCount);
                                        },
                                        [](RangeUnbounded) {}
                                    ), r);
                                }
                            ), v);
                        }
                    ), d.mModel);

                    prev = d;
                }

                if (tableCount) {
                    finish();
                    oss << ")";
                }
                outputVisibility();
                oss << ")," << eol;
            }
        ), index.mType);
    }

    auto content = oss.str();
    boost::algorithm::replace_last(content, "),\" \\", ")\"");

    return content;
}

const ShaderConstantBuffer& ShaderGroup::getConstantBuffer(const DescriptorIndex& index) const {
    if (index.mUpdate == mUpdateFrequency) {
        return mRootSignature.mConstantBuffers.at(index);
    } else if (index.mUpdate > mUpdateFrequency) {
        if (!mParent) {
            throw std::runtime_error("lower frequency parent not exists");
        }
        return mParent->getConstantBuffer(index);
    }
    throw std::runtime_error("contant buffer not found");
}

void ShaderGroup::getShaderPrefix(std::string& prefix) const {
    if (mParent) {
        mParent->getShaderPrefix(prefix);
        prefix += "-";
    }
    prefix += camelToUnderscore(mName);
}

const ShaderGroup& ShaderGroup::getRootSignatureShaderGroup() const {
    if (mGenerateRootSignature)
        return *this;

    if (!mParent)
        throw std::runtime_error("root signature group not found");

    return mParent->getRootSignatureShaderGroup();
}

}
