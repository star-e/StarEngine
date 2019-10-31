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

namespace Star {

namespace Graphics {

namespace Render {

struct BINORMAL_;
struct BLENDINDICES_;
struct BLENDWEIGHT_;
struct NORMAL_;
struct POSITIONT_;
struct PSIZE_;
struct TANGENT_;
struct TEXCOORD_;

using VertexElementType = std::variant<BINORMAL_, BLENDINDICES_, BLENDWEIGHT_, NORMAL_, POSITIONT_, PSIZE_, TANGENT_, TEXCOORD_>;

namespace Shader {

struct SV_ClipDistance_;
struct SV_CullDistance_;
struct SV_Coverage_;
struct SV_Depth_;
struct SV_DepthGreaterEqual_;
struct SV_DepthLessEqual_;
struct SV_DispatchThreadID_;
struct SV_DomainLocation_;
struct SV_GroupID_;
struct SV_GroupIndex_;
struct SV_GroupThreadID_;
struct SV_GSInstanceID_;
struct SV_InnerCoverage_;
struct SV_InsideTessFactor_;
struct SV_InstanceID_;
struct SV_IsFrontFace_;
struct SV_OutputControlPointID_;
struct SV_Position_;
struct SV_PrimitiveID_;
struct SV_RenderTargetArrayIndex_;
struct SV_SampleIndex_;
struct SV_StencilRef_;
struct SV_Target_;
struct SV_TessFactor_;
struct SV_VertexID_;
struct SV_ViewportArrayIndex_;

using SemanticType = std::variant<std::monostate, BINORMAL_, BLENDINDICES_, BLENDWEIGHT_, NORMAL_, POSITIONT_, PSIZE_, TANGENT_, TEXCOORD_, SV_ClipDistance_, SV_CullDistance_, SV_Coverage_, SV_Depth_, SV_DepthGreaterEqual_, SV_DepthLessEqual_, SV_DispatchThreadID_, SV_DomainLocation_, SV_GroupID_, SV_GroupIndex_, SV_GroupThreadID_, SV_GSInstanceID_, SV_InnerCoverage_, SV_InsideTessFactor_, SV_InstanceID_, SV_IsFrontFace_, SV_OutputControlPointID_, SV_Position_, SV_PrimitiveID_, SV_RenderTargetArrayIndex_, SV_SampleIndex_, SV_StencilRef_, SV_Target_, SV_TessFactor_, SV_VertexID_, SV_ViewportArrayIndex_>;

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
