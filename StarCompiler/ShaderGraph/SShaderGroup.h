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
#include <StarCompiler/ShaderGraph/SShaderProgram.h>
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>
#include <StarCompiler/ShaderGraph/SShaderRootSignature.h>

namespace Star::Graphics::Render::Shader {

class ShaderRegister;

class ShaderGroup {
public:
    void validate() const;
    // bottom-up
    void buildProgramConstantBuffers(const AttributeMap& attrs);

    void collectConstantBuffers();
    void collectDescriptors(const AttributeMap& attrs);
    void collectAttributes(const AttributeMap& attrs, AttributeDatabase& database) const;

    void buildRegisters();

    bool hasChildGenerateRootSignature() const;

    bool hasIA() const;
    std::string generateRootSignature() const;

    const ConstantBuffer& getConstantBuffer(const DescriptorIndex& index) const;

    void getShaderPrefix(std::string& prefix) const;
    void getShaderPrefixSlash(std::string& prefix) const;

    const ShaderGroup& getRootSignatureShaderGroup() const;

    std::string mName;
    size_t mRenderNodeID = 0;
    UpdateEnum mUpdateFrequency = PerInstance;
    const ShaderGroup* mParent = nullptr;
    bool mGenerateRootSignature = false;
    Map<std::string, gsl::not_null<const ShaderGroup*>> mGroups;
    Map<std::string, std::pair<gsl::not_null<const ShaderProgram*>, RootSignature>> mPrograms;
    RootSignature mRootSignature;
};

}
