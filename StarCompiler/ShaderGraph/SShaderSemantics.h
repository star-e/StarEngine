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
#include <StarCompiler/ShaderGraph/SShaderTypes.h>

namespace Star::Graphics::Render::Shader {

constexpr SV_Position_ POSITION;
constexpr SV_Target_ COLOR;

inline ShaderStageEnum getShaderStages(const SemanticType& type) noexcept {
    return visit(overload(
        [](const BINORMAL_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const BLENDINDICES_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const BLENDWEIGHT_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const NORMAL_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const POSITIONT_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const PSIZE_&) { return static_cast<ShaderStageEnum>(VS_Interp | VS_Out); },
        [](const TANGENT_&) { return static_cast<ShaderStageEnum>(VS_Interp); },
        [](const TEXCOORD_&) { return static_cast<ShaderStageEnum>(SS_Value ^ PS_Out); },
        [](const SV_ClipDistance_&) { return static_cast<ShaderStageEnum>(SS_SV ^ VS_In); },
        [](const SV_CullDistance_&) { return static_cast<ShaderStageEnum>(SS_SV ^ VS_In); },
        [](const SV_Coverage_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out); },
        [](const SV_Depth_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out | OM_Interp | OM_Out); },
        [](const SV_DepthGreaterEqual_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out); },
        [](const SV_DepthLessEqual_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out); },
        [](const SV_DispatchThreadID_&) { return static_cast<ShaderStageEnum>(CS_In); },
        [](const SV_DomainLocation_&) { return static_cast<ShaderStageEnum>(DS_In); },
        [](const SV_GroupID_&) { return static_cast<ShaderStageEnum>(CS_In); },
        [](const SV_GroupIndex_&) { return static_cast<ShaderStageEnum>(CS_In); },
        [](const SV_GroupThreadID_&) { return static_cast<ShaderStageEnum>(CS_In); },
        [](const SV_GSInstanceID_&) { return static_cast<ShaderStageEnum>(GS_In); },
        [](const SV_InnerCoverage_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out); },
        [](const SV_InsideTessFactor_&) { return static_cast<ShaderStageEnum>(HS_Out | DS_In); },
        [](const SV_InstanceID_&) { return static_cast<ShaderStageEnum>(SS_SV); },
        [](const SV_IsFrontFace_&) { return static_cast<ShaderStageEnum>(GS_Out | PS_In); },
        [](const SV_OutputControlPointID_&) { return static_cast<ShaderStageEnum>(HS_In); },
        [](const SV_Position_&) { return static_cast<ShaderStageEnum>(SS_Value ^ PS_Out); },
        [](const SV_PrimitiveID_&) { return static_cast<ShaderStageEnum>(HS_In | DS_In | GS_In | GS_Out | PS_In | PS_Out); },
        [](const SV_RenderTargetArrayIndex_&) { return static_cast<ShaderStageEnum>(GS_Out | PS_In | PS_Out); },
        [](const SV_SampleIndex_&) { return static_cast<ShaderStageEnum>(PS_In | PS_Out); },
        [](const SV_StencilRef_&) { return static_cast<ShaderStageEnum>(PS_Out); },
        [](const SV_Target_&) { return static_cast<ShaderStageEnum>(SS_Value | OM_Interp | OM_Out); },
        [](const SV_TessFactor_&) { return static_cast<ShaderStageEnum>(HS_Out | DS_In); },
        [](const SV_VertexID_&) { return static_cast<ShaderStageEnum>(SS_SV); },
        [](const SV_ViewportArrayIndex_&) { return static_cast<ShaderStageEnum>(GS_Out | PS_In | PS_Out); },
        [](std::monostate) ->ShaderStageEnum { return static_cast<ShaderStageEnum>(0); }
    ), type);
}

}
