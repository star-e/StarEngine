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

#include "SShaderDescriptorDatabase.h"
#include "SShaderAttribute.h"

namespace Star::Graphics::Render::Shader {

bool DescriptorDatabase::try_addAttribute(const ShaderAttribute& attr, ShaderVisibilityType vis) {
    bool succeeded = false;
    const auto& d = attr.mDescriptor;
    auto index = getDescriptorIndex(d, vis);
    Expects(!std::holds_alternative<std::monostate>(index.mVisibility));

    mRegisterSpaces.emplace(std::pair{ d.mDescriptorType, d.mRegisterSpace });

    if (isConstant(attr)) {
        mConstantBuffers[index].mValues.emplace(Constant{ attr.mType, attr.mName });
        succeeded = true;
    } else {
        auto index = getDescriptorIndex(d, vis);
        visit(overload(
            [&](auto t) {
                visit(overload(
                    [&](Bounded_) {
                        auto res = mDescriptors[index].mResourceViewLists[d.mRegisterSpace].mRanges[t].mSubranges[d.mSource].mAttributes.emplace(attr);
                        succeeded = res.second;
                    },
                    [&](Unbounded_) {
                        const auto& unboundedSet = mDescriptors[index].mResourceViewLists[d.mRegisterSpace].mUnboundedDescriptors;
                        if (!unboundedSet.empty()) {
                            auto iter = unboundedSet.find(DescriptorType{ t });
                            if (iter != unboundedSet.end() && iter->second.mAttribute.mName == attr.mName) {
                                succeeded = false;
                            } else {
                                throw std::invalid_argument("resource view register space: " + d.mRegisterSpace + "already have unbounded descriptor");
                            }
                        } else {
                            mDescriptors[index].mResourceViewLists[d.mRegisterSpace].mUnboundedDescriptors[t].mAttribute = attr;
                            succeeded = true;
                        }
                    }
                ), d.mBoundedness);
            },
            [&](SSV_ t) {
                visit(overload(
                    [&](Bounded_) {
                        auto res = mDescriptors[index].mSamplerLists[d.mRegisterSpace].mRanges[t].mSubranges[d.mSource].mAttributes.emplace(attr);
                        succeeded = res.second;
                    },
                    [&](Unbounded_) {
                        const auto& unboundedSet = mDescriptors[index].mSamplerLists[d.mRegisterSpace].mUnboundedDescriptors;
                        if (!unboundedSet.empty()) {
                            auto iter = unboundedSet.find(DescriptorType{ t });
                            if (iter != unboundedSet.end() && iter->second.mAttribute.mName == attr.mName) {
                                succeeded = false;
                            } else {
                                throw std::invalid_argument("sampler view register space: " + d.mRegisterSpace + "already have unbounded descriptor");
                            }
                        } else {
                            mDescriptors[index].mSamplerLists[d.mRegisterSpace].mUnboundedDescriptors[t].mAttribute = attr;
                            succeeded = true;
                        }
                    }
                ), d.mBoundedness);
            }
        ), d.mDescriptorType);
    }
    return succeeded;
}

void DescriptorDatabase::addAttribute(const ShaderAttribute& attr, ShaderVisibilityType vis) {
    auto res = try_addAttribute(attr, vis);
    if (!res) {
        throw std::runtime_error("DescriptorDatabase add attribute failed");
    }
}

void DescriptorDatabase::mergeConstantBuffers(UpdateEnum update, DescriptorDatabase& rhs) const {
    for (const auto& [index, cb] : mConstantBuffers) {
        if (index.mUpdate != update)
            continue;

        auto& rhsTable = rhs.mConstantBuffers[index];
        for (const auto& v : cb.mValues) {
            rhsTable.mValues.emplace(v);
        }
    }
}

namespace {

void reserveDescriptorCapacity(const DescriptorList& list, DescriptorList& rhsList,
    std::string_view space, DescriptorDatabase& rhs
) {
    for (const auto& [type, range] : list.mRanges) {
        auto capacity = getDescriptorCapacity(range);
        Expects(capacity);
        auto& rhsRange = rhsList.mRanges[type];
        rhsRange.mCapacity = std::max(rhsRange.mCapacity, capacity);
        rhs.mRegisterSpaces.emplace(std::pair{
            type,
            space,
        });
    }
}

void copyDescriptors(const DescriptorList& list, ShaderVisibilityType vis, DescriptorDatabase& rhs) {
    for (const auto& [type, range] : list.mRanges) {
        for (const auto& [source, subrange] : range.mSubranges) {
            for (const auto& attr : subrange.mAttributes) {
                rhs.try_addAttribute(attr, vis);
                rhs.mRegisterSpaces.emplace(std::pair{
                    attr.mDescriptor.mDescriptorType,
                    attr.mDescriptor.mRegisterSpace,
                });
            }
        }
    }
}

void validateDescriptors(const DescriptorList& list) {
    for (const auto& [type, range] : list.mRanges) {
        for (const auto& [source, subrange] : range.mSubranges) {
            for (const auto& attr : subrange.mAttributes) {
                if (subrange.mAttributes.empty()) {
                    throw std::runtime_error("subrange is empty");
                }
            }
        }
    }
}

void buildDescriptorRegisters(DescriptorList& list, const std::string& space, DescriptorDatabase::Registers& slots) {
    for (auto& [type, range] : list.mRanges) {
        auto& registerSpace = slots.mRegisterSpaces.at(std::pair{ type, space });
        range.mSpace = registerSpace.mSpaceID;
        range.mStart = registerSpace.mIndex;
        range.mCount = range.mCapacity ? range.mCapacity : getDescriptorCapacity(range);
        registerSpace.mIndex += range.mCount;
    }
    for (auto& [type, unbounded] : list.mUnboundedDescriptors) {
        auto& registerSpace = slots.mRegisterSpaces.at(std::pair{ type, space });
        unbounded.mSpace = registerSpace.mSpaceID;
        unbounded.mStart = registerSpace.mIndex;
    }
}

void buildChildDescriptorRegisters(DescriptorList& list, const DescriptorList& parent) {
    for (auto& [type, range] : list.mRanges) {
        const auto& parentRange = parent.mRanges.at(DescriptorType{ type });
        range.mSpace = parentRange.mSpace;
        range.mStart = parentRange.mStart;
        range.mCount = range.mCapacity ? range.mCapacity : getDescriptorCapacity(range);
        Expects(range.mCount <= parentRange.mCount);
    }
    for (auto& [type, unbounded] : list.mUnboundedDescriptors) {
        const auto& parentUnbounded = parent.mUnboundedDescriptors.at(DescriptorType{ type });
        unbounded.mSpace = parentUnbounded.mSpace;
        unbounded.mStart = parentUnbounded.mStart;
    }
}

}

void DescriptorDatabase::reserveDescriptors(UpdateEnum update, DescriptorDatabase& rhs) const {
    for (const auto& [index, collection] : mDescriptors) {
        if (index.mUpdate != update) {
            continue;
        }
        auto& rhsCollection = rhs.mDescriptors[index];

        for (const auto& [space, list] : collection.mResourceViewLists) {
            auto& rhsList = rhsCollection.mResourceViewLists[space];
            reserveDescriptorCapacity(list, rhsList, space, rhs);
        }

        for (const auto& [space, list] : collection.mSamplerLists) {
            auto& rhsList = rhsCollection.mSamplerLists[space];
            reserveDescriptorCapacity(list, rhsList, space, rhs);
        }
    }
}

void DescriptorDatabase::collectDescriptors(UpdateEnum update, DescriptorDatabase& rhs) const {
    for (const auto& [index, collection] : mDescriptors) {
        if (index.mUpdate != update) {
            continue;
        }
        for (const auto& [space, list] : collection.mResourceViewLists) {
            copyDescriptors(list, index.mVisibility, rhs);
        }
        for (const auto& [space, list] : collection.mSamplerLists) {
            copyDescriptors(list, index.mVisibility, rhs);
        }
    }
}

void DescriptorDatabase::addConstantBuffersDescriptors() {
    for (const auto& [index, buffer] : mConstantBuffers) {
        auto d = AttributeDescriptor{
            index.mUpdate,
            index.mType,
            index.mPersistency,
            CBV,
            "",
            EngineSource,
            Bounded,
            ""
        };
        ShaderAttribute attr{ "", CBuffer, d };
        addAttribute(attr, index.mVisibility);
    }
}

const DescriptorRange* DescriptorDatabase::findRange(const DescriptorIndex& index,
    std::string_view space, DescriptorType type
) const {
    auto iterCollection = mDescriptors.find(index);
    if (iterCollection == mDescriptors.end())
        return nullptr;

    const DescriptorRange* ptr = nullptr;

    visit(overload(
        [&](auto t) {
            auto iterList = iterCollection->second.mResourceViewLists.find(space);
            if (iterList == iterCollection->second.mResourceViewLists.end()) {
                ptr = nullptr;
                return;
            }

            auto iterRange = iterList->second.mRanges.find(type);
            if (iterRange == iterList->second.mRanges.end()) {
                ptr = nullptr;
                return;
            }
            ptr = &iterRange->second;
        },
        [&](SSV_) {
            auto iterList = iterCollection->second.mSamplerLists.find(space);
            if (iterList == iterCollection->second.mSamplerLists.end()) {
                ptr = nullptr;
                return;
            }

            auto iterRange = iterList->second.mRanges.find(type);
            if (iterRange == iterList->second.mRanges.end()) {
                ptr = nullptr;
                return;
            }
            ptr = &iterRange->second;
        }
    ), type);

    return ptr;
}

const UnboundedDescriptor* DescriptorDatabase::findUnbounded(const DescriptorIndex& index,
    std::string_view space, DescriptorType type
) const {
    auto iterCollection = mDescriptors.find(index);
    if (iterCollection == mDescriptors.end())
        return nullptr;

    const UnboundedDescriptor* ptr = nullptr;

    visit(overload(
        [&](auto t) {
            auto iterList = iterCollection->second.mResourceViewLists.find(space);
            if (iterList == iterCollection->second.mResourceViewLists.end()) {
                ptr = nullptr;
                return;
            }

            auto iterUnbounded = iterList->second.mUnboundedDescriptors.find(type);
            if (iterUnbounded == iterList->second.mUnboundedDescriptors.end()) {
                ptr = nullptr;
                return;
            }
            ptr = &iterUnbounded->second;
        },
        [&](SSV_) {
            auto iterList = iterCollection->second.mSamplerLists.find(space);
            if (iterList == iterCollection->second.mSamplerLists.end()) {
                ptr = nullptr;
                return;
            }

            auto iterUnbounded = iterList->second.mUnboundedDescriptors.find(type);
            if (iterUnbounded == iterList->second.mUnboundedDescriptors.end()) {
                ptr = nullptr;
                return;
            }
            ptr = &iterUnbounded->second;
        }
    ), type);

    return nullptr;
}

void DescriptorDatabase::validate() const {
    for (const auto& [index, collection] : mDescriptors) {
        for (const auto& [space, list] : collection.mResourceViewLists) {
            validateDescriptors(list);
        }
        for (const auto& [space, list] : collection.mSamplerLists) {
            validateDescriptors(list);
        }
    }
}

DescriptorDatabase::Registers DescriptorDatabase::buildRegisters() {
    validate();
    Registers slots;
    {
        std::map<DescriptorType, std::set<std::string>> spaces;
        uint32_t spaceID = 0;
        for (const auto& [type, space] : mRegisterSpaces) {
            auto iter = spaces[type].find(space);
            Expects(iter == spaces[type].end());
            auto spaceID = gsl::narrow<uint32_t>(spaces[type].size());
            bool succeeded = false;
            std::tie(iter, succeeded) = spaces[type].emplace(space);
            Ensures(succeeded);
            auto res = slots.mRegisterSpaces.try_emplace(std::pair{ type, space }, RegisterSpace{ spaceID });
            Ensures(res.second);
        }
    }

    for (int update = UpdateEnum::UpdateCount; update-- > 0; ) {
        for (auto& [index, collection] : mDescriptors) {
            if (index.mUpdate != update) {
                continue;
            }
            for (auto& [space, list] : collection.mResourceViewLists) {
                buildDescriptorRegisters(list, space, slots);
            }
            for (auto& [space, list] : collection.mSamplerLists) {
                buildDescriptorRegisters(list, space, slots);
            }
        }
    }

    for (int update = 0; update != UpdateEnum::UpdateCount; ++update) {
        for (auto& [index, collection] : mDescriptors) {
            if (index.mUpdate != update) {
                continue;
            }
            for (auto& [space, list] : collection.mResourceViewLists) {
                list.mSlot = slots.mRootParameterSlots[index.mType]++;
            }
            for (auto& [space, list] : collection.mSamplerLists) {
                list.mSlot = slots.mRootParameterSlots[index.mType]++;
            }
        }
    }

    return slots;
}

void DescriptorDatabase::buildRegisters(UpdateEnum parentFrequency,
    const DescriptorDatabase& parent
) {
    validate();

    for (int update = parentFrequency; update --> 0; ) {
        for (auto& [index, collection] : mDescriptors) {
            if (index.mUpdate != update) {
                continue;
            }
            const auto& parentCollection = parent.mDescriptors.at(index);
            for (auto& [space, list] : collection.mResourceViewLists) {
                const auto& parentList = parentCollection.mResourceViewLists.at(space);
                list.mSlot = parentList.mSlot;
                buildChildDescriptorRegisters(list, parentList);
            }
            for (auto& [space, list] : collection.mSamplerLists) {
                const auto& parentList = parentCollection.mSamplerLists.at(space);
                list.mSlot = parentList.mSlot;
                buildChildDescriptorRegisters(list, parentList);
            }
        }
    }
}

}
