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
#include <Star/Graphics/SShaderTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

inline const char* getName(const BINORMAL_& v) noexcept { return "BINORMAL"; }
inline const char* getName(const BLENDINDICES_& v) noexcept { return "BLENDINDICES"; }
inline const char* getName(const BLENDWEIGHT_& v) noexcept { return "BLENDWEIGHT"; }
inline const char* getName(const NORMAL_& v) noexcept { return "NORMAL"; }
inline const char* getName(const POSITIONT_& v) noexcept { return "POSITIONT"; }
inline const char* getName(const PSIZE_& v) noexcept { return "PSIZE"; }
inline const char* getName(const TANGENT_& v) noexcept { return "TANGENT"; }
inline const char* getName(const TEXCOORD_& v) noexcept { return "TEXCOORD"; }

namespace Shader {

inline const char* getName(const SV_ClipDistance_& v) noexcept { return "SV_ClipDistance"; }
inline const char* getName(const SV_CullDistance_& v) noexcept { return "SV_CullDistance"; }
inline const char* getName(const SV_Coverage_& v) noexcept { return "SV_Coverage"; }
inline const char* getName(const SV_Depth_& v) noexcept { return "SV_Depth"; }
inline const char* getName(const SV_DepthGreaterEqual_& v) noexcept { return "SV_DepthGreaterEqual"; }
inline const char* getName(const SV_DepthLessEqual_& v) noexcept { return "SV_DepthLessEqual"; }
inline const char* getName(const SV_DispatchThreadID_& v) noexcept { return "SV_DispatchThreadID"; }
inline const char* getName(const SV_DomainLocation_& v) noexcept { return "SV_DomainLocation"; }
inline const char* getName(const SV_GroupID_& v) noexcept { return "SV_GroupID"; }
inline const char* getName(const SV_GroupIndex_& v) noexcept { return "SV_GroupIndex"; }
inline const char* getName(const SV_GroupThreadID_& v) noexcept { return "SV_GroupThreadID"; }
inline const char* getName(const SV_GSInstanceID_& v) noexcept { return "SV_GSInstanceID"; }
inline const char* getName(const SV_InnerCoverage_& v) noexcept { return "SV_InnerCoverage"; }
inline const char* getName(const SV_InsideTessFactor_& v) noexcept { return "SV_InsideTessFactor"; }
inline const char* getName(const SV_InstanceID_& v) noexcept { return "SV_InstanceID"; }
inline const char* getName(const SV_IsFrontFace_& v) noexcept { return "SV_IsFrontFace"; }
inline const char* getName(const SV_OutputControlPointID_& v) noexcept { return "SV_OutputControlPointID"; }
inline const char* getName(const SV_Position_& v) noexcept { return "SV_Position"; }
inline const char* getName(const SV_PrimitiveID_& v) noexcept { return "SV_PrimitiveID"; }
inline const char* getName(const SV_RenderTargetArrayIndex_& v) noexcept { return "SV_RenderTargetArrayIndex"; }
inline const char* getName(const SV_SampleIndex_& v) noexcept { return "SV_SampleIndex"; }
inline const char* getName(const SV_StencilRef_& v) noexcept { return "SV_StencilRef"; }
inline const char* getName(const SV_Target_& v) noexcept { return "SV_Target"; }
inline const char* getName(const SV_TessFactor_& v) noexcept { return "SV_TessFactor"; }
inline const char* getName(const SV_VertexID_& v) noexcept { return "SV_VertexID"; }
inline const char* getName(const SV_ViewportArrayIndex_& v) noexcept { return "SV_ViewportArrayIndex"; }

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
