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

#pragma once
#include <StarCompiler/Graphics/SRenderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>

namespace Star::Graphics::Render::Shader {

class ShaderRegister;
class RootSignature {
public:
    void addConstant(const ShaderAttribute& attr, ShaderStageType stage);
    void mergeConstantBuffers(UpdateEnum update, RootSignature& rhs) const;
    
    void addConstantBufferDescriptor(const DescriptorIndex& index, const ShaderConstantBuffer& cb);
    void addDescriptor(const ShaderAttribute& attr, RootAccessEnum stage);

    void collectCapacities(UpdateEnum update, std::map<DescriptorIndex, DescriptorTableCapacity>& rhs) const;
    void resizeCapacities(const std::map<DescriptorIndex, DescriptorTableCapacity>& rhs);

    void collectDescriptors(UpdateEnum update, RootSignature& rhs) const;
    void reserveRegisters(UpdateEnum update, ShaderRegister& reg) const;
    void reserveCapacityRegisters(UpdateEnum update, ShaderRegister& reg) const;

    static bool try_addDescriptor(const Descriptor& d, DescriptorTable& table, DescriptorTableCapacity& cap);
    static void maximizeCapacity(const DescriptorTableCapacity& source, DescriptorTableCapacity& target);

    // compiled
    std::map<DescriptorIndex, ShaderConstantBuffer> mConstantBuffers;
    std::map<DescriptorIndex, DescriptorTable> mTables;
    std::map<DescriptorIndex, DescriptorTableCapacity> mCapacities;
};

}
