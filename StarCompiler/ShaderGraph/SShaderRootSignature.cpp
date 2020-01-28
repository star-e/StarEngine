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

#include "SShaderRootSignature.h"
#include "SShaderDescriptor.h"
#include "SShaderRegisters.h"
#include "SShaderAttribute.h"

namespace Star::Graphics::Render::Shader {

void RootSignature::addConstant(const ShaderAttribute& attr, ShaderStageType stage) {
    IsConstant visitor;
    if (!visit(visitor, attr.mType)) {
        return;
    }

    ShaderVisibilityType stageID = getShaderVisibilityType(stage);
    DescriptorIndex index{ attr.mUpdateFrequency, getRootParameterType(attr), stageID };
    mConstantBuffers[index].mValues.emplace(
        ShaderConstant{ static_cast<bool>(attr.mFlags & UnboundedSize), attr.mType, attr.mName });
}

namespace {

uint32_t getUnboundedSpace(const DescriptorTable& table, const ShaderAttribute& attr) {
    bool found = false;
    int32_t space = -1;
    for (const auto& d : table.mDescriptors) {
        visit(overload(
            [&](const auto& desc) {
                if (std::holds_alternative<DescriptorArray>(desc)) {
                    const auto& range = std::get<DescriptorArray>(desc);
                    if (std::holds_alternative<RangeUnbounded>(range)) {
                        if (d.mName == attr.mName &&
                            d.mType == getDescriptorType(attr))
                        {
                            found = true;
                            space = d.mSpace;
                        } else {
                            space = std::max(space, static_cast<int32_t>(d.mSpace));
                        }
                    }
                }
            }
        ), d.mModel);
        if (found)
            break;
    }

    if (!found) {
        space = space + 1;
    }
    return gsl::narrow<uint32_t>(space);
}

struct AddAttributeVisitor {
    RootSignature& mRoot;
    const DescriptorIndex& mIndex;
    const ShaderAttribute& mAttribute;

    template<class Scalar, int Rows, int Cols>
    void operator()(const Eigen::Matrix<Scalar, Rows, Cols>& v) {
        throw std::runtime_error("Constant not supported");
    }

    void operator()(const InputPatch_& v) {
        throw std::invalid_argument("InputPatch_ not supported");
    }
    void operator()(const OutputPatch_& v) {
        throw std::invalid_argument("OutputPatch_ not supported");
    }

    template<class T>
    void operator()(const T& v) {
        auto& table = mRoot.mTables[mIndex];
        auto& cap = mRoot.mCapacities[mIndex];

        if (mAttribute.mFlags & UnboundedSize) {
            auto space = getUnboundedSpace(table, mAttribute);
            Descriptor d = getDescriptor(mAttribute, space);
            auto added = RootSignature::try_addDescriptor(d, table, cap);
            if (added == false) {
                throw std::runtime_error("copy unbounded descriptor failed");
            }
            return;
        } else {
            Descriptor d = getDescriptor(mAttribute, 0);
            RootSignature::try_addDescriptor(d, table, cap);
        }
    }
};

}

void RootSignature::addDescriptor(const ShaderAttribute& attr, ShaderVisibilityType stage) {
    IsConstant visitor;
    if (visit(visitor, attr.mType)) {
        return;
    }

    DescriptorIndex index{ attr.mUpdateFrequency, getRootParameterType(attr), stage };

    AddAttributeVisitor visitor2{ *this, index, attr };
    visit(visitor2, attr.mType);
}

void RootSignature::collectCapacities(UpdateEnum update, std::map<DescriptorIndex, DescriptorTableCapacity>& rhs) const {
    for (const auto& [index, cap] : mCapacities) {
        if (index.mUpdate != update)
            continue;

        auto& rhsCap = rhs[index];
        maximizeCapacity(cap, rhsCap);
    }
}

void RootSignature::resizeCapacities(const std::map<DescriptorIndex, DescriptorTableCapacity>& rhs) {
    for (const auto& [index, source] : rhs) {
        auto& target = mCapacities[index];
        for (const auto& range : source.mNumDescriptors) {
            auto iter = target.mNumDescriptors.find(range);
            if (iter != target.mNumDescriptors.end()) {
                auto r = *iter;
                visit(overload(
                    [](const RangeBounded& src, RangeBounded& dst) {
                        dst.mCount += src.mCount;
                        if (dst.mCount == 0) {
                            throw std::runtime_error("descriptor array capacity should never be empty");
                        }
                    },
                    [](const RangeBounded& src, RangeUnbounded) {
                        throw std::runtime_error("add unbounded with array, should never happen");
                    },
                    [](RangeUnbounded, RangeUnbounded) {
                        throw std::invalid_argument("add unbounded with unbounded, not supported yet");
                    },
                    [](RangeUnbounded, RangeBounded& v) {
                        throw std::runtime_error("add array with unbounded, should never happen");
                    }
                ), range.mCount, r.mCount);
                target.mNumDescriptors.replace(iter, r);
            } else {
                target.mNumDescriptors.emplace(range);
            }
        }

        auto& table = mTables[index];
        for (const auto& range : source.mNumDescriptors) {
            auto desc = makeDescriptorRange(range.mType, range.mSpace, range.mCount);
            auto iter = table.mDescriptors.find(desc);
            if (iter != table.mDescriptors.end()) {
                auto range1 = *iter;
                visit(overload(
                    [&](auto& d) {
                        visit(overload(
                            [](const RangeBounded& src, RangeBounded& dst) {
                                dst.mCount += src.mCount;
                                if (dst.mCount == 0) {
                                    throw std::runtime_error("descriptor table array capacity should never be empty");
                                }
                            },
                            [](const RangeBounded& src, RangeUnbounded) {
                                throw std::runtime_error("add unbounded with array, should never happen");
                            },
                            [](RangeUnbounded, RangeUnbounded) {
                                throw std::invalid_argument("add unbounded with unbounded, not supported yet");
                            },
                            [](RangeUnbounded, RangeBounded& v) {
                                throw std::runtime_error("add array with unbounded, should never happen");
                            }
                        ), range.mCount, std::get<DescriptorArray>(d));
                    }
                ), range1.mModel);
                table.mDescriptors.replace(iter, range1);
            } else {
                table.mDescriptors.emplace(desc);
            }
        }
    }
}

void RootSignature::collectDescriptors(UpdateEnum update, RootSignature& rhs) const {
    for (const auto& [index, table] : mTables) {
        if (index.mUpdate != update)
            continue;

        auto& rhsTable = rhs.mTables[index];
        auto& rhsCap = rhs.mCapacities[index];

        for (const auto& d : table.mDescriptors) {
            try_addDescriptor(d, rhsTable, rhsCap);
        }
    }
}

void RootSignature::reserveRegisters(UpdateEnum update, ShaderRegister& reg) const {
    for (const auto& [index, table] : mTables) {
        if (!std::holds_alternative<std::monostate>(index.mVisibility))
            continue;
        if (index.mUpdate != update)
            continue;

        for (const auto& d : table.mDescriptors) {
            visit(overload(
                [&](const auto& m) {
                    visit(overload(
                        [&](const auto& v) {
                            reg.reserveAll(d.mType, d.mSpace);
                        },
                        [&](const DescriptorArray& range) {
                            visit(overload(
                                [&](const RangeBounded& arr) {
                                    reg.reserveAll(d.mType, d.mSpace, arr.mCount);
                                },
                                [&](RangeUnbounded) {}
                            ), range);
                        }
                    ), m);
                }
            ), d.mModel);
        }
    }
}

void RootSignature::reserveCapacityRegisters(UpdateEnum update, ShaderRegister& reg) const {
    for (const auto& [index, cap] : mCapacities) {
        if (!std::holds_alternative<std::monostate>(index.mVisibility))
            continue;
        if (index.mUpdate != update)
            continue;

        for (const auto& d : cap.mNumDescriptors) {
            visit(overload(
                [&](const RangeBounded& arr) {
                    reg.reserveAll(d.mType, d.mSpace, arr.mCount);
                },
                [&](RangeUnbounded) {
                    throw std::runtime_error("reserve vis all unbounded not supported");
                }
            ), d.mCount);
        }
    }
}

bool RootSignature::try_addDescriptor(const Descriptor& d,
    DescriptorTable& table, DescriptorTableCapacity& cap
) {
    auto res = table.mDescriptors.emplace(d);
    if (res.second) {
        auto range = getDescriptorRange(d.mModel, 1);
        auto iter = cap.mNumDescriptors.find(DescriptorCapacity{ d.mType, d.mSpace, range });
        if (iter != cap.mNumDescriptors.end()) {
            DescriptorCapacity capacity = *iter;
            visit(overload(
                [](const RangeUnbounded&) {
                    throw std::runtime_error("should never increase unbounded descriptor count");
                },
                [](RangeBounded& v) {
                    ++v.mCount;
                }
            ), capacity.mCount);
            cap.mNumDescriptors.replace(iter, capacity);
        } else {
            cap.mNumDescriptors.emplace(DescriptorCapacity{ d.mType, d.mSpace, range });
        }
    }
    return res.second;
}

void RootSignature::maximizeCapacity(const DescriptorTableCapacity& source, DescriptorTableCapacity& target) {
    for (const auto& range : source.mNumDescriptors) {
        auto iter = target.mNumDescriptors.find(range);
        if (iter != target.mNumDescriptors.end()) {
            auto r = *iter;
            visit(overload(
                [](const RangeBounded& src, RangeBounded& dst) {
                    dst.mCount = std::max(dst.mCount, src.mCount);
                    if (dst.mCount == 0) {
                        throw std::runtime_error("descriptor array capacity should never be empty");
                    }
                },
                [](const RangeBounded& src, RangeUnbounded) {
                    throw std::runtime_error("maximize unbounded with array, should never happen");
                },
                [](RangeUnbounded, RangeUnbounded) {
                    // do nothing
                },
                [](RangeUnbounded, RangeBounded& v) {
                    throw std::runtime_error("maximize array with unbounded, should never happen");
                }
            ), range.mCount, r.mCount);
            target.mNumDescriptors.replace(iter, r);
        } else {
             visit(overload(
                [](const RangeBounded& src) {
                     if (src.mCount == 0) {
                         throw std::runtime_error("descriptor array should never be empty");
                     }
                },
                [](RangeUnbounded) {
                }
            ), range.mCount);
            target.mNumDescriptors.emplace(range);
        }
    }
}

void RootSignature::mergeConstantBuffers(UpdateEnum update, RootSignature& rhs) const {
    for (const auto& [index, cb] : mConstantBuffers) {
        if (index.mUpdate != update)
            continue;

        auto& rhsTable = rhs.mConstantBuffers[index];
        for (const auto& v : cb.mValues) {
            rhsTable.mValues.emplace(v);
        }
    }
}

void RootSignature::addConstantBufferDescriptor(const DescriptorIndex& index,
    const ShaderConstantBuffer& cb
) {
    mTables[index].mDescriptors.emplace(Descriptor{ CBV, 0, ConstantBuffer, "" });
    auto iter = mCapacities[index].mNumDescriptors.find(DescriptorCapacity{ CBV, 0, RangeBounded{} });
    if (iter != mCapacities[index].mNumDescriptors.end()) {
        DescriptorCapacity capacity = *iter;
        ++std::get<RangeBounded>(capacity.mCount).mCount;
        mCapacities[index].mNumDescriptors.replace(iter, capacity);
    } else {
        mCapacities[index].mNumDescriptors.emplace(DescriptorCapacity{ CBV, 0, RangeBounded{ 1 } });
    }
}

}
