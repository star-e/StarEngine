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
#include <StarCompiler/ShaderGraph/SShaderFwd.h>
#include <StarCompiler/ShaderGraph/SShaderStage.h>
#include <StarCompiler/ShaderGraph/SShaderVariant.h>
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>

namespace Star::Graphics::Render::Shader {

class RootSignature;

class ShaderProgram {
public:
    ShaderProgram() = default;
    ShaderProgram(std::string_view name) : mName(name) {}

    bool stageBegin(ShaderStageType stage, NameMap<ShaderValue> outputs = {});
    bool stageEnd(ShaderStageType stage);
    void compile();

    void buildConstantBuffers(const AttributeMap& attrs, RootSignature& rsg) const;
    void buildDescriptors(const AttributeMap& attrs, RootSignature& rsg) const;
    bool hasIA() const;

    void collectAttributes(const AttributeMap& attrs, AttributeDatabase& database) const;

    ShaderProgram& operator<<(std::string_view content) {
        mInclude.append(content);
        return *this;
    }

    std::string mName;
    ShaderGraph mGraph;
    std::map<ShaderStageType, ShaderStage> mShaders;

    std::vector<ShaderVariant> mVariants;
    ShaderVariant mSkipVariants;
    GFX_SHADER_MODEL mShaderModel;
    std::string mInclude;

    ShaderStageType mPrevStage = CS;
};

}
