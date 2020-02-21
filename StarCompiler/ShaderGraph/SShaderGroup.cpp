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

#include "SShaderGroup.h"
#include "SShaderProgram.h"
#include "SShaderDescriptor.h"
#include <StarCompiler/ShaderGraph/SShaderNames.h>

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

void ShaderGroup::buildProgramConstantBuffers(const AttributeMap& attrs) {
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
}

void ShaderGroup::collectDescriptors(const AttributeMap& attrs) {
    mRootSignature.addConstantBuffersDescriptors();

    if (mGroups.empty()) {
        // Leaf Node
        for (auto& [name, pair] : mPrograms) {
            auto& [program, rsg] = pair;
            program->buildDescriptors(attrs, rsg);
        }

        for (uint32_t i = PerInstance; i != mUpdateFrequency; ++i) {
            for (auto& [name, pair] : mPrograms) {
                auto& [program, rsg] = pair;
                rsg.reserveCapacities(static_cast<UpdateEnum>(i), mRootSignature);
            }
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

void ShaderGroup::collectAttributes(const AttributeMap& attrs, AttributeDatabase& database) const {
    if (mGroups.empty()) {
        for (auto& [name, pair] : mPrograms) {
            auto& [program, rsg] = pair;
            program->collectAttributes(attrs, database);
        }
    }
}

void ShaderGroup::buildRegisters() {
    if (mGenerateRootSignature) {
        mRootSignature.mDatabase.buildRegisters();
        for (auto& pair : mPrograms) {
            auto& rsg = pair.second.second;
            rsg.mDatabase.buildRegisters(mUpdateFrequency, mRootSignature.mDatabase);
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

namespace {

void outputVisibility(std::ostream& oss, const ShaderVisibilityType& vis) {
    visit(overload(
        [&](std::monostate) {
            // output nothing
            throw std::runtime_error("SHADER_VISIBILITY_ALL not supported yet");
        },
        [&](PS_) {
            oss << ", visibility = SHADER_VISIBILITY_PIXEL";
        },
        [&](GS_) {
            oss << ", visibility = SHADER_VISIBILITY_GEOMETRY";
        },
        [&](DS_) {
            oss << ", visibility = SHADER_VISIBILITY_DOMAIN";
        },
        [&](HS_) {
            oss << ", visibility = SHADER_VISIBILITY_HULL";
        },
        [&](VS_) {
            oss << ", visibility = SHADER_VISIBILITY_VERTEX";
        }
    ), vis);
};

void outputSpace(std::ostream& oss, const DescriptorRange& range) {
    if (range.mSpace)
        oss << ", space = " << range.mSpace;
};

void outputTable(std::ostream& oss, std::string& space,
    const DescriptorList& list, const ShaderVisibilityType& vis
) {
    uint32_t rangeCount = 0;
    std::string bol = "\"";
    std::string eol = "\" \\\n";

    OSS << bol << "DescriptorTable(";
    for (const auto& rangePair : list.mRanges) {
        const auto& type = rangePair.first;
        const auto& range = rangePair.second;
        if (rangeCount++) {
            oss << ", ";
        }
        oss << getVariantName(type) << "(" << getRegisterPrefix(type) << range.mStart;
        Expects(range.mCount);

        if (range.mCapacity == 0) {
            auto sz = getDescriptorCapacity(range);
            Expects(sz == range.mCount);
        } else {
            Expects(range.mCapacity == range.mCount);
        }

        if (range.mCount > 1) {
            oss << ", numDescriptors = " << range.mCount;
        }

        if (range.mSpace) {
            oss << ", space = " << range.mSpace;
        }
        oss << ")";
    }

    for (const auto& rangePair : list.mUnboundedDescriptors) {
        const auto& type = rangePair.first;
        const auto& desc = rangePair.second;
        if (rangeCount++) {
            oss << ", ";
        }
        oss << getVariantName(type) << "(" << getRegisterPrefix(type) << desc.mStart;
        oss << ", numDescriptors = unbounded";
        if (desc.mSpace) {
            oss << ", space = " << desc.mSpace;
        }
        oss << ")";
    }
    outputVisibility(oss, vis);
    oss << ")," << eol;
}

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

    for (const auto& [index, collection] : mRootSignature.mDatabase.mDescriptors) {
        visit(overload(
            [&](std::monostate) {
                hasPS = hasGS = hasDS = hasHS = hasVS = true;
            },
            [&](PS_) {
                hasPS = true;
            },
            [&](GS_) {
                hasGS = true;
            },
            [&](DS_) {
                hasDS = true;
            },
            [&](HS_) {
                hasHS = true;
            },
            [&](VS_) {
                hasVS = true;
            }
        ), index.mVisibility);
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

    // build descriptors
    for (int update = 0; update != UpdateEnum::UpdateCount; ++update) {
        for (const auto& collectionPair : mRootSignature.mDatabase.mDescriptors) {
            const auto& index = collectionPair.first;
            const auto& collection = collectionPair.second;
            if (index.mUpdate != update)
                continue;

            visit(overload(
                [&](Constants_) {
                    throw std::invalid_argument("root signature Constants not supported yet");
                },
                [&](auto type) {
                    for (const auto& listPair : collection.mResourceViewLists) {
                        const auto& spaceName = listPair.first;
                        const auto& list = listPair.second;
                        const auto& range = list.mRanges.at(DescriptorType{ type });
                        Expects(list.mUnboundedDescriptors.empty());

                        uint32_t slot = range.mStart;
                        if (range.mCapacity == 0) {
                            auto sz = getDescriptorCapacity(range);
                            for (uint32_t i = 0; i != sz; ++i) {
                                OSS << bol << getRootDescriptorName(type)
                                    << "(" << getRegisterPrefix(type) << slot++;
                                outputSpace(oss, range);
                                outputVisibility(oss, index.mVisibility);
                                oss << ")," << eol;
                            }
                        } else {
                            for (uint32_t i = 0; i != range.mCapacity; ++i) {
                                OSS << bol << getRootDescriptorName(type)
                                    << "(" << getRegisterPrefix(type) << slot++;
                                outputSpace(oss, range);
                                outputVisibility(oss, index.mVisibility);
                                oss << ")," << eol;
                            }
                        }
                        Ensures(slot - range.mStart == range.mCount);
                    }
                },
                [&](SSV_ type) {
                    for (const auto& listPair : collection.mSamplerLists) {
                        const auto& spaceName = listPair.first;
                        const auto& list = listPair.second;
                        const auto& range = list.mRanges.at(DescriptorType{ type });
                        Expects(list.mUnboundedDescriptors.empty());
                        Expects(range.mCount);

                        uint32_t slot = range.mStart;
                        if (range.mCapacity == 0) {
                            auto sz = getDescriptorCapacity(range);
                            for (uint32_t i = 0; i != sz; ++i) {
                                OSS << bol << "StaticSampler(s" << slot++;
                                outputSpace(oss, range);
                                outputVisibility(oss, index.mVisibility);
                                oss << ")," << eol;
                            }
                        } else {
                            for (uint32_t i = 0; i != range.mCapacity; ++i) {
                                OSS << bol << "StaticSampler(s" << slot++;
                                outputSpace(oss, range);
                                outputVisibility(oss, index.mVisibility);
                                oss << ")," << eol;
                            }
                        }
                        Ensures(slot - range.mStart == range.mCount);
                    }
                },
                [&](Table_) {
                    for (const auto& listPair : collection.mResourceViewLists) {
                        const auto& list = listPair.second;
                        outputTable(oss, space, list, index.mVisibility);
                    }
                    for (const auto& listPair : collection.mSamplerLists) {
                        const auto& list = listPair.second;
                        outputTable(oss, space, list, index.mVisibility);
                    }
                }
            ), index.mType);
        } // for collection
    } // for update

    auto content = oss.str();
    boost::algorithm::replace_last(content, "),\" \\", ")\"");

    return content;
}

const ConstantBuffer& ShaderGroup::getConstantBuffer(const DescriptorIndex& index) const {
    if (index.mUpdate == mUpdateFrequency) {
        return mRootSignature.mDatabase.mConstantBuffers.at(index);
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

void ShaderGroup::getShaderPrefixSlash(std::string& prefix) const {
    if (mParent) {
        mParent->getShaderPrefixSlash(prefix);
        prefix += "/";
    }
    prefix += mName;
}

const ShaderGroup& ShaderGroup::getRootSignatureShaderGroup() const {
    if (mGenerateRootSignature)
        return *this;

    if (!mParent)
        throw std::runtime_error("root signature group not found");

    return mParent->getRootSignatureShaderGroup();
}

}
