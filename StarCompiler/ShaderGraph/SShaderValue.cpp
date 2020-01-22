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

#include "SShaderValue.h"
#include <StarCompiler/Graphics/SRenderNames.h>
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include <StarCompiler/ShaderGraph/SShaderSemantics.h>
#include <StarCompiler/SGetVariantName.h>

namespace Star::Graphics::Render::Shader {

ShaderStageEnum getShaderStageAll(const ShaderStageType& stage) noexcept {
    return visit(overload(
        [](OM_) { return static_cast<ShaderStageEnum>(OM_All); },
        [](PS_) { return static_cast<ShaderStageEnum>(PS_All); },
        [](GS_) { return static_cast<ShaderStageEnum>(GS_All); },
        [](DS_) { return static_cast<ShaderStageEnum>(DS_All); },
        [](TS_) { return static_cast<ShaderStageEnum>(TS_All); },
        [](HS_) { return static_cast<ShaderStageEnum>(HS_All); },
        [](VS_) { return static_cast<ShaderStageEnum>(VS_All); },
        [](CS_) { return static_cast<ShaderStageEnum>(CS_All); }
    ), stage);
}

ShaderStageEnum getShaderStageInput(const ShaderStageType& stage) noexcept {
    return visit(overload(
        [](OM_) { return static_cast<ShaderStageEnum>(OM_In); },
        [](PS_) { return static_cast<ShaderStageEnum>(PS_In); },
        [](GS_) { return static_cast<ShaderStageEnum>(GS_In); },
        [](DS_) { return static_cast<ShaderStageEnum>(DS_In); },
        [](TS_) { return static_cast<ShaderStageEnum>(TS_In); },
        [](HS_) { return static_cast<ShaderStageEnum>(HS_In); },
        [](VS_) { return static_cast<ShaderStageEnum>(VS_In); },
        [](CS_) { return static_cast<ShaderStageEnum>(CS_In); }
    ), stage);
}

ShaderStageEnum getShaderStageOutput(const ShaderStageType& stage) noexcept {
    return visit(overload(
        [](OM_) { return static_cast<ShaderStageEnum>(OM_Out); },
        [](PS_) { return static_cast<ShaderStageEnum>(PS_Out); },
        [](GS_) { return static_cast<ShaderStageEnum>(GS_Out); },
        [](DS_) { return static_cast<ShaderStageEnum>(DS_Out); },
        [](TS_) { return static_cast<ShaderStageEnum>(TS_Out); },
        [](HS_) { return static_cast<ShaderStageEnum>(HS_Out); },
        [](VS_) { return static_cast<ShaderStageEnum>(VS_Out); },
        [](CS_) { return static_cast<ShaderStageEnum>(CS_Out); }
    ), stage);
}

ShaderStageEnum getShaderStageInterp(const ShaderStageType& stage) noexcept {
    return visit(overload(
        [](OM_) { return static_cast<ShaderStageEnum>(0); },
        [](PS_) { return static_cast<ShaderStageEnum>(PS_Interp); },
        [](GS_) { return static_cast<ShaderStageEnum>(GS_Interp); },
        [](DS_) { return static_cast<ShaderStageEnum>(DS_Interp); },
        [](TS_) { return static_cast<ShaderStageEnum>(TS_Interp); },
        [](HS_) { return static_cast<ShaderStageEnum>(HS_Interp); },
        [](VS_) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](CS_) { return static_cast<ShaderStageEnum>(0); }
    ), stage);
}

void validateShaderValueSemantics(const ShaderValue& v, const ShaderStageType& type, bool bInput) {
    if (std::holds_alternative<std::monostate>(v.mSemantic))
        return;

    auto stages = getShaderStages(v.mSemantic);
    if (bInput) {

#define VALIDATE(STAGE) \
[&](STAGE) {\
    if (stages & BOOST_PP_CAT(STAGE, Interp)) {\
        /*throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " has no interp source");*/\
    } else if (!(stages & BOOST_PP_CAT(STAGE, In))) {\
        throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not " + BOOST_PP_STRINGIZE(STAGE) + "In");\
    }\
}
        visit(overload(
            VALIDATE(OM_),
            VALIDATE(PS_),
            VALIDATE(GS_),
            VALIDATE(DS_),
            VALIDATE(TS_),
            VALIDATE(HS_),
            VALIDATE(VS_),
            [&](CS_) {
                if (!(stages & CS_In)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not CS_In");
                }
            }
        ), type);
#undef VALIDATE
    } else {
        visit(overload(
            [&](OM_) {
                if (!(stages & OM_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not OM_Out");
                }
            },
            [&](PS_) {
                if (!(stages & PS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not PS_Out");
                }
            },
            [&](GS_) {
                if (!(stages & GS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not GS_Out");
                }
            },
            [&](DS_) {
                if (!(stages & DS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not DS_Out");
                }
            },
            [&](TS_) {
                if (!(stages & TS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not TS_Out");
                }
            },
            [&](HS_) {
                if (!(stages & HS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not HS_Out");
                }
            },
            [&](VS_) {
                if (!(stages & VS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not VS_Out");
                }
            },
            [&](CS_) {
                if (!(stages & CS_Out)) {
                    throw std::invalid_argument("input: " + v.mName + ", semantic: " + getVariantName(v.mSemantic) + " is not CS_Out");
                }
            }
        ), type);
    }
}

void validateShaderValueStageOutput(ShaderStageEnum all, const ShaderStageType& stage) {
    visit(overload(
        [&](OM_) {
            // do nothing
        },
        [&](PS_) {
        },
        [&](GS_) {
            if (all & (PS_All))
                throw std::invalid_argument("GS shouldn't have output");
        },
        [&](DS_) {
            if (all & (GS_All | PS_All))
                throw std::invalid_argument("DS shouldn't have output");
        },
        [&](TS_) {
            if (all & (DS_All | GS_All | PS_All))
                throw std::invalid_argument("TS shouldn't have output");
        },
        [&](HS_) {
            if (all & (TS_All | DS_All | GS_All | PS_All))
                throw std::invalid_argument("HS shouldn't have output");
        },
        [&](VS_) {
            if (all & (HS_All | TS_All | DS_All | GS_All | PS_All))
                throw std::invalid_argument("VS shouldn't have output");
        },
        [&](CS_) {
            if (all & SS_All)
                throw std::invalid_argument("CS node is mixed with Graphics Shader");
        }
    ), stage);
}

const char* getModelName(const ValueModel& v, Language l) noexcept {
#define GET_NAME(TYPE, NAME) \
[](const TYPE##4& v) {\
    return BOOST_STRINGIZE(BOOST_PP_CAT(NAME, 4));\
},\
[](const TYPE##3& v) {\
    return BOOST_STRINGIZE(BOOST_PP_CAT(NAME, 3));\
},\
[](const TYPE##2& v) {\
    return BOOST_STRINGIZE(BOOST_PP_CAT(NAME, 2)); \
},\
[](const TYPE##1& v) {\
    return BOOST_STRINGIZE(NAME); \
}
    return visit(overload(
        [&](HLSL_) {
            return visit(overload(
                GET_NAME(float, float),
                GET_NAME(half, half),
                GET_NAME(fixed, half),
                GET_NAME(uint, uint),
                GET_NAME(int, int),
                [](const ShaderStruct& v) {
                    return v.mName.c_str();
                },
                [](std::monostate) {
                    return "";
                }
            ), v);
        },
        [&](GLSL_) {
            return visit(overload(
                GET_NAME(float, float),
                GET_NAME(half, half),
                GET_NAME(fixed, fixed),
                GET_NAME(uint, uint),
                GET_NAME(int, int),
                [](const ShaderStruct& v) {
                    return v.mName.c_str();
                },
                [](std::monostate) {
                    return "";
                }
            ), v);
        },
        [&](Metal_) {
            return visit(overload(
                GET_NAME(float, float),
                GET_NAME(half, half),
                GET_NAME(fixed, fixed),
                GET_NAME(uint, uint),
                GET_NAME(int, int),
                [](const ShaderStruct& v) {
                    return v.mName.c_str();
                },
                [](std::monostate) {
                    return "";
                }
            ), v);
        },
        [&](UnityCG_) {
            return visit(overload(
                GET_NAME(float, float),
                GET_NAME(half, half),
                GET_NAME(fixed, fixed),
                GET_NAME(uint, uint),
                GET_NAME(int, int),
                [](const ShaderStruct& v) {
                    return v.mName.c_str();
                },
                [](std::monostate) {
                    return "";
                }
            ), v);
        },
        [&](std::monostate) {
            return visit(overload(
                GET_NAME(float, float),
                GET_NAME(half, half),
                GET_NAME(fixed, fixed),
                GET_NAME(uint, uint),
                GET_NAME(int, int),
                [](const ShaderStruct& v) {
                    return v.mName.c_str();
                },
                [](std::monostate) {
                    return "";
                }
            ), v);
        }
    ), l);
#undef GET_NAME
}

std::string getSemanticName(const SemanticType& type, size_t slot,
    const ShaderStageType& stage, bool bInput
) {
    auto optSlot = slot ? std::to_string(slot) : std::string();
    return visit(overload(
        [&](BINORMAL_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](BLENDINDICES_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](BLENDWEIGHT_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](NORMAL_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](PSIZE_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](TANGENT_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](TEXCOORD_ v) -> std::string {
            return getName(v) + std::to_string(slot);
        },
        [&](SV_ClipDistance_ v) -> std::string {
            return getName(v) + std::to_string(slot);
        },
        [&](SV_CullDistance_ v) -> std::string {
            return getName(v) + std::to_string(slot);
        },
        [&](SV_DepthGreaterEqual_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](SV_DepthLessEqual_ v) -> std::string {
            return getName(v) + optSlot;
        },
        [&](SV_Position_ v) -> std::string {
            return visit(overload(
                [&](VS_ s) -> std::string {
                    if (bInput) {
                        return "POSITION" + optSlot;
                    } else {
                        if (slot) {
                            throw std::invalid_argument("SV_Position[n] only supported in VS input");
                        }
                        return getName(v);
                    }
                },
                [&](auto) -> std::string {
                    if (slot) {
                        throw std::invalid_argument("SV_Position[n] only supported in VS input");
                    }
                    return getName(v);
                }
            ), stage);
        },
        [&](SV_Target_ v) -> std::string {
            return visit(overload(
                [&](VS_) -> std::string {
                    if (bInput) {
                        return "COLOR" + optSlot;
                    } else {
                        return getName(v) + std::to_string(slot);
                    }
                },
                [&](auto) -> std::string {
                    return getName(v) + std::to_string(slot);
                }
            ), stage);
        },
        [&](std::monostate v) -> std::string {
            return "";
        },
        [](const auto& v) -> std::string {
            return getName(v);
        }
    ), type);
}

}
