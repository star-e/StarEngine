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

namespace Star::Graphics::Render::Shader {

inline bool isConsistent(const ShaderValue& lhs, const ShaderValue& rhs) noexcept {
    if (lhs.mName == rhs.mName) {
        if (lhs.mValue.index() == rhs.mValue.index()) {
            if (std::holds_alternative<ShaderStruct>(lhs.mValue)) {
                if (std::get<ShaderStruct>(lhs.mValue).mName ==
                    std::get<ShaderStruct>(rhs.mValue).mName)
                    return true;
                else
                    return false;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

inline bool isSemanticBlank(const ShaderValue& v) noexcept {
    return std::holds_alternative<std::monostate>(v.mSemantic);
}

inline bool isGlobalState(const ShaderValue& v) noexcept {
    return
        std::holds_alternative<std::monostate>(v.mValue) &&
        std::holds_alternative<std::monostate>(v.mSemantic);
}

const char* getModelName(const ValueModel& v, Language l) noexcept;
std::string getSemanticName(const SemanticType& type, size_t slot, const ShaderStageType& stage, bool bInput);

ShaderStageEnum getShaderStageAll(const ShaderStageType& stage) noexcept;
ShaderStageEnum getShaderStageInput(const ShaderStageType& stage) noexcept;
ShaderStageEnum getShaderStageOutput(const ShaderStageType& stage) noexcept;
ShaderStageEnum getShaderStageInterp(const ShaderStageType& stage) noexcept;

void validateShaderValueSemantics(const ShaderValue& v, const ShaderStageType& stage, bool bInput);

void validateShaderValueStageOutput(ShaderStageEnum all, const ShaderStageType& stage);

}
