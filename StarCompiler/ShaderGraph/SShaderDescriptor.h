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

struct IsConstant {
#define MATH_TYPE_ELEM(r, _, i, NAME) bool operator()(const NAME& v) const noexcept { return true; }
#define MATH_TYPES(...) BOOST_PP_SEQ_FOR_EACH_I(MATH_TYPE_ELEM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))

    MATH_TYPES(matrix_, double4_, double3_, double2_, double1_, float4_, float3_, float2_, float1_, half4_, half3_, half2_, half1_, uint4_, uint3_, uint2_, uint1_, int4_, int3_, int2_, int1_, fixed4_, fixed3_, fixed2_, fixed1_)

    template<class T>
    bool operator()(const T&) const noexcept {
        return false;
    }

#undef MATH_TYPE_ELEM
#undef MATH_TYPES
};

ShaderVisibilityType getShaderVisibilityType(ShaderStageType stage);
ShaderStageType getShaderStageType(ShaderVisibilityType e);

const char* getRootDescriptorName(const DescriptorType& type) noexcept;
char getRegisterPrefix(const DescriptorType& type) noexcept;

}
