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
                [](const DescriptorRange& r) {
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

DescriptorType getDescriptorType(const DescriptorModel& model) {
    return visit(overload(
        [](const DescriptorCBV&) ->DescriptorType { return CBV; },
        [](const DescriptorUAV&) ->DescriptorType { return UAV; },
        [](const DescriptorSRV&) ->DescriptorType { return SRV; },
        [](const DescriptorSSV&) ->DescriptorType { return SSV; }
    ), model);
}

DescriptorRange getDescriptorRange(const DescriptorModel& model, uint32_t count) noexcept {
    return visit(overload(
        [&](const auto& v) -> DescriptorRange {
            return visit(overload(
                [&](const DescriptorRange& r) -> DescriptorRange {
                    if (std::holds_alternative<RangeUnbounded>(r))
                        return RangeUnbounded{};
                    else
                        return RangeBounded{ count };
                },
                [&](const auto&) -> DescriptorRange {
                    return RangeBounded{ count };
                }
            ), v);
        }
    ), model);
}

Descriptor makeDescriptorRange(const DescriptorType& type, uint32_t space, const DescriptorRange& range) {
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

RootAccessEnum getRootAccessEnum(ShaderStageType stage) {
    return visit(overload(
        [&](OM_) -> RootAccessEnum { throw std::invalid_argument("output merger do not support root signature"); },
        [&](PS_) -> RootAccessEnum { return RA_PS; },
        [&](GS_) -> RootAccessEnum { return RA_GS; },
        [&](DS_) -> RootAccessEnum { return RA_DS; },
        [&](TS_) -> RootAccessEnum { throw std::invalid_argument("tessellation shader do not support root signature"); },
        [&](HS_) -> RootAccessEnum { return RA_HS; },
        [&](VS_) -> RootAccessEnum { return RA_VS; },
        [&](CS_) -> RootAccessEnum { throw std::invalid_argument("compute shader do not support root signature"); }
    ), stage);
}

ShaderStageType getShaderStageType(RootAccessEnum e) {
    switch (e) {
    case RA_PS: return PS;
    case RA_GS: return GS;
    case RA_DS: return DS;
    case RA_HS: return HS;
    case RA_VS: return VS;
    default:
        throw std::runtime_error("unknown root access stage");
    }
}

const char* getRootDescriptorName(const DescriptorType& type) noexcept {
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

char getRegisterPrefix(const DescriptorType& type) noexcept {
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
