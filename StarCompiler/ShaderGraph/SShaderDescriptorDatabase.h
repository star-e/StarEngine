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
#include <Star/SSet.h>

namespace Star::Graphics::Render::Shader {

class DescriptorDatabase {
public:
    struct RegisterSpace {
        uint32_t mSpaceID = 0;
        uint32_t mIndex = 0;
    };
    struct Registers {
        std::map<std::pair<DescriptorType, std::string>, RegisterSpace> mRegisterSpaces;
        std::map<RootParameterType, uint32_t> mRootParameterSlots;
    };
    // attributes
    bool try_addAttribute(const ShaderAttribute& attr, ShaderVisibilityType vis);
    void addAttribute(const ShaderAttribute& attr, ShaderVisibilityType vis);

    // constant buffer
    void mergeConstantBuffers(UpdateEnum update, DescriptorDatabase& rhs) const;

    // descriptor
    void addConstantBuffersDescriptors();
    void reserveDescriptors(UpdateEnum update, DescriptorDatabase& rhs) const;
    void collectDescriptors(UpdateEnum update, DescriptorDatabase& rhs) const;

    // register
    Registers buildRegisters();
    void buildRegisters(UpdateEnum parentFrequency, const DescriptorDatabase& parent);

    // lookup
    const DescriptorRange* findRange(const DescriptorIndex& index,
        std::string_view space, DescriptorType type) const;

    const UnboundedDescriptor* findUnbounded(const DescriptorIndex& index,
        std::string_view space, DescriptorType type) const;
private:
    void validate() const;
public:
    std::map<DescriptorIndex, ConstantBuffer> mConstantBuffers;
    std::map<DescriptorIndex, DescriptorCollection> mDescriptors;
    std::set<std::pair<DescriptorType, std::string>> mRegisterSpaces;
};

}
