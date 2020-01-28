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

#include "SShaderDescriptor.h"

namespace Star::Graphics::Render::Shader {

bool isUnbounded(const DescriptorModel& model) noexcept {
    return visit(overload(
        [](const auto& v) -> bool {
            return visit(overload(
                [](const DescriptorArray& r) {
                    if (std::holds_alternative<RangeUnbounded>(r))
                        return true;
                    else
                        return false;
                },
                [](const auto&) {
                    return false;
                }
            ), v);
        }
    ), model);
}

DescriptorRangeType getDescriptorType(const DescriptorModel& model) {
    return visit(overload(
        [](const DescriptorCBV&) ->DescriptorRangeType { return CBV; },
        [](const DescriptorUAV&) ->DescriptorRangeType { return UAV; },
        [](const DescriptorSRV&) ->DescriptorRangeType { return SRV; },
        [](const DescriptorSSV&) ->DescriptorRangeType { return SSV; }
    ), model);
}

DescriptorArray getDescriptorRange(const DescriptorModel& model, uint32_t count) noexcept {
    return visit(overload(
        [&](const auto& v) -> DescriptorArray {
            return visit(overload(
                [&](const DescriptorArray& r) -> DescriptorArray {
                    if (std::holds_alternative<RangeUnbounded>(r))
                        return RangeUnbounded{};
                    else
                        return RangeBounded{ count };
                },
                [&](const auto&) -> DescriptorArray {
                    return RangeBounded{ count };
                }
            ), v);
        }
    ), model);
}

Descriptor makeDescriptorRange(const DescriptorRangeType& type, uint32_t space, const DescriptorArray& range) {
    return visit(overload(
        [&](CBV_ v) {
            return Descriptor{ v, space, DescriptorCBV{ range } };
        },
        [&](UAV_ v) {
            return Descriptor{ v, space, DescriptorUAV{ range } };
        },
        [&](SRV_ v) {
            return Descriptor{ v, space, DescriptorSRV{ range } };
        },
        [&](SSV_ v) {
            return Descriptor{ v, space, DescriptorSSV{ range } };
        }
    ), type);
}

ShaderVisibilityType getShaderVisibilityType(ShaderStageType stage) {
    return visit(overload(
        [](OM_ v) -> ShaderVisibilityType { throw std::invalid_argument("output merger do not support root signature"); },
        [](PS_ v) -> ShaderVisibilityType { return v; },
        [](GS_ v) -> ShaderVisibilityType { return v; },
        [](DS_ v) -> ShaderVisibilityType { return v; },
        [](TS_ v) -> ShaderVisibilityType { throw std::invalid_argument("tessellation shader do not support root signature"); },
        [](HS_ v) -> ShaderVisibilityType { return v; },
        [](VS_ v) -> ShaderVisibilityType { return v; },
        [](CS_ v) -> ShaderVisibilityType { throw std::invalid_argument("compute shader do not support root signature"); }
    ), stage);
}

ShaderStageType getShaderStageType(ShaderVisibilityType e) {
    return visit(overload(
        [](std::monostate) -> ShaderStageType {
            throw std::runtime_error("shader visibility all cannot be converted to ShaderStageType");
        },
        [](const auto& v) -> ShaderStageType { return v; }
    ), e);
}

const char* getRootDescriptorName(const DescriptorRangeType& type) noexcept {
    return visit(overload(
        [&](CBV_ v) {
            return "CBV";
        },
        [&](UAV_ v) {
            return "UAV";
        },
        [&](SRV_ v) {
            return "SRV";
        },
        [&](SSV_ v) {
            return "StaticSampler";
        }
    ), type);
}

char getRegisterPrefix(const DescriptorRangeType& type) noexcept {
    return visit(overload(
        [&](CBV_ v) {
            return 'b';
        },
        [&](UAV_ v) {
            return 'u';
        },
        [&](SRV_ v) {
            return 't';
        },
        [&](SSV_ v) {
            return 's';
        }
    ), type);
}

}
