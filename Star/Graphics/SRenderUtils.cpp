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

#include "SRenderUtils.h"

namespace Star::Graphics::Render {

uint32_t getSize(const AttributeType& type) noexcept {
    return visit(overload(
        [](matrix_) -> uint32_t { return 64; },

        [](float4_) -> uint32_t { return 16; },
        [](uint4_) -> uint32_t { return 16; },
        [](int4_) -> uint32_t { return 16; },

        [](float2_) -> uint32_t { return 8; },
        [](uint2_) -> uint32_t { return 8; },
        [](int2_) -> uint32_t { return 8; },
        [](half4_) -> uint32_t { return 8; },

        [](float1_) -> uint32_t { return 4; },
        [](uint1_) -> uint32_t { return 4; },
        [](int1_) -> uint32_t { return 4; },
        [](half2_) -> uint32_t { return 4; },
        [](fixed4_) -> uint32_t { return 4; },

        [](half1_) -> uint32_t { return 2; },

        [](auto) -> uint32_t {
            return 0;
        }
    ), type);
}

namespace {

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

}

bool isConstant(const AttributeType& type) noexcept {
    return visit(IsConstant{}, type);
}

}
