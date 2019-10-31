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
#include <Star/Graphics/SShaderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct BINORMAL_ {} static constexpr BINORMAL;
inline bool operator==(const BINORMAL_&, const BINORMAL_&) noexcept { return true; }
inline bool operator!=(const BINORMAL_&, const BINORMAL_&) noexcept { return false; }
struct BLENDINDICES_ {} static constexpr BLENDINDICES;
inline bool operator==(const BLENDINDICES_&, const BLENDINDICES_&) noexcept { return true; }
inline bool operator!=(const BLENDINDICES_&, const BLENDINDICES_&) noexcept { return false; }
struct BLENDWEIGHT_ {} static constexpr BLENDWEIGHT;
inline bool operator==(const BLENDWEIGHT_&, const BLENDWEIGHT_&) noexcept { return true; }
inline bool operator!=(const BLENDWEIGHT_&, const BLENDWEIGHT_&) noexcept { return false; }
struct NORMAL_ {} static constexpr NORMAL;
inline bool operator==(const NORMAL_&, const NORMAL_&) noexcept { return true; }
inline bool operator!=(const NORMAL_&, const NORMAL_&) noexcept { return false; }
struct POSITIONT_ {} static constexpr POSITIONT;
inline bool operator==(const POSITIONT_&, const POSITIONT_&) noexcept { return true; }
inline bool operator!=(const POSITIONT_&, const POSITIONT_&) noexcept { return false; }
struct PSIZE_ {} static constexpr PSIZE;
inline bool operator==(const PSIZE_&, const PSIZE_&) noexcept { return true; }
inline bool operator!=(const PSIZE_&, const PSIZE_&) noexcept { return false; }
struct TANGENT_ {} static constexpr TANGENT;
inline bool operator==(const TANGENT_&, const TANGENT_&) noexcept { return true; }
inline bool operator!=(const TANGENT_&, const TANGENT_&) noexcept { return false; }
struct TEXCOORD_ {} static constexpr TEXCOORD;
inline bool operator==(const TEXCOORD_&, const TEXCOORD_&) noexcept { return true; }
inline bool operator!=(const TEXCOORD_&, const TEXCOORD_&) noexcept { return false; }

using VertexElementType = std::variant<BINORMAL_, BLENDINDICES_, BLENDWEIGHT_, NORMAL_, POSITIONT_, PSIZE_, TANGENT_, TEXCOORD_>;

inline bool operator<(const VertexElementType& lhs, const VertexElementType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

namespace Shader {

struct SV_ClipDistance_ {} static constexpr SV_ClipDistance;
inline bool operator==(const SV_ClipDistance_&, const SV_ClipDistance_&) noexcept { return true; }
inline bool operator!=(const SV_ClipDistance_&, const SV_ClipDistance_&) noexcept { return false; }
struct SV_CullDistance_ {} static constexpr SV_CullDistance;
inline bool operator==(const SV_CullDistance_&, const SV_CullDistance_&) noexcept { return true; }
inline bool operator!=(const SV_CullDistance_&, const SV_CullDistance_&) noexcept { return false; }
struct SV_Coverage_ {} static constexpr SV_Coverage;
inline bool operator==(const SV_Coverage_&, const SV_Coverage_&) noexcept { return true; }
inline bool operator!=(const SV_Coverage_&, const SV_Coverage_&) noexcept { return false; }
struct SV_Depth_ {} static constexpr SV_Depth;
inline bool operator==(const SV_Depth_&, const SV_Depth_&) noexcept { return true; }
inline bool operator!=(const SV_Depth_&, const SV_Depth_&) noexcept { return false; }
struct SV_DepthGreaterEqual_ {} static constexpr SV_DepthGreaterEqual;
inline bool operator==(const SV_DepthGreaterEqual_&, const SV_DepthGreaterEqual_&) noexcept { return true; }
inline bool operator!=(const SV_DepthGreaterEqual_&, const SV_DepthGreaterEqual_&) noexcept { return false; }
struct SV_DepthLessEqual_ {} static constexpr SV_DepthLessEqual;
inline bool operator==(const SV_DepthLessEqual_&, const SV_DepthLessEqual_&) noexcept { return true; }
inline bool operator!=(const SV_DepthLessEqual_&, const SV_DepthLessEqual_&) noexcept { return false; }
struct SV_DispatchThreadID_ {} static constexpr SV_DispatchThreadID;
inline bool operator==(const SV_DispatchThreadID_&, const SV_DispatchThreadID_&) noexcept { return true; }
inline bool operator!=(const SV_DispatchThreadID_&, const SV_DispatchThreadID_&) noexcept { return false; }
struct SV_DomainLocation_ {} static constexpr SV_DomainLocation;
inline bool operator==(const SV_DomainLocation_&, const SV_DomainLocation_&) noexcept { return true; }
inline bool operator!=(const SV_DomainLocation_&, const SV_DomainLocation_&) noexcept { return false; }
struct SV_GroupID_ {} static constexpr SV_GroupID;
inline bool operator==(const SV_GroupID_&, const SV_GroupID_&) noexcept { return true; }
inline bool operator!=(const SV_GroupID_&, const SV_GroupID_&) noexcept { return false; }
struct SV_GroupIndex_ {} static constexpr SV_GroupIndex;
inline bool operator==(const SV_GroupIndex_&, const SV_GroupIndex_&) noexcept { return true; }
inline bool operator!=(const SV_GroupIndex_&, const SV_GroupIndex_&) noexcept { return false; }
struct SV_GroupThreadID_ {} static constexpr SV_GroupThreadID;
inline bool operator==(const SV_GroupThreadID_&, const SV_GroupThreadID_&) noexcept { return true; }
inline bool operator!=(const SV_GroupThreadID_&, const SV_GroupThreadID_&) noexcept { return false; }
struct SV_GSInstanceID_ {} static constexpr SV_GSInstanceID;
inline bool operator==(const SV_GSInstanceID_&, const SV_GSInstanceID_&) noexcept { return true; }
inline bool operator!=(const SV_GSInstanceID_&, const SV_GSInstanceID_&) noexcept { return false; }
struct SV_InnerCoverage_ {} static constexpr SV_InnerCoverage;
inline bool operator==(const SV_InnerCoverage_&, const SV_InnerCoverage_&) noexcept { return true; }
inline bool operator!=(const SV_InnerCoverage_&, const SV_InnerCoverage_&) noexcept { return false; }
struct SV_InsideTessFactor_ {} static constexpr SV_InsideTessFactor;
inline bool operator==(const SV_InsideTessFactor_&, const SV_InsideTessFactor_&) noexcept { return true; }
inline bool operator!=(const SV_InsideTessFactor_&, const SV_InsideTessFactor_&) noexcept { return false; }
struct SV_InstanceID_ {} static constexpr SV_InstanceID;
inline bool operator==(const SV_InstanceID_&, const SV_InstanceID_&) noexcept { return true; }
inline bool operator!=(const SV_InstanceID_&, const SV_InstanceID_&) noexcept { return false; }
struct SV_IsFrontFace_ {} static constexpr SV_IsFrontFace;
inline bool operator==(const SV_IsFrontFace_&, const SV_IsFrontFace_&) noexcept { return true; }
inline bool operator!=(const SV_IsFrontFace_&, const SV_IsFrontFace_&) noexcept { return false; }
struct SV_OutputControlPointID_ {} static constexpr SV_OutputControlPointID;
inline bool operator==(const SV_OutputControlPointID_&, const SV_OutputControlPointID_&) noexcept { return true; }
inline bool operator!=(const SV_OutputControlPointID_&, const SV_OutputControlPointID_&) noexcept { return false; }
struct SV_Position_ {} static constexpr SV_Position;
inline bool operator==(const SV_Position_&, const SV_Position_&) noexcept { return true; }
inline bool operator!=(const SV_Position_&, const SV_Position_&) noexcept { return false; }
struct SV_PrimitiveID_ {} static constexpr SV_PrimitiveID;
inline bool operator==(const SV_PrimitiveID_&, const SV_PrimitiveID_&) noexcept { return true; }
inline bool operator!=(const SV_PrimitiveID_&, const SV_PrimitiveID_&) noexcept { return false; }
struct SV_RenderTargetArrayIndex_ {} static constexpr SV_RenderTargetArrayIndex;
inline bool operator==(const SV_RenderTargetArrayIndex_&, const SV_RenderTargetArrayIndex_&) noexcept { return true; }
inline bool operator!=(const SV_RenderTargetArrayIndex_&, const SV_RenderTargetArrayIndex_&) noexcept { return false; }
struct SV_SampleIndex_ {} static constexpr SV_SampleIndex;
inline bool operator==(const SV_SampleIndex_&, const SV_SampleIndex_&) noexcept { return true; }
inline bool operator!=(const SV_SampleIndex_&, const SV_SampleIndex_&) noexcept { return false; }
struct SV_StencilRef_ {} static constexpr SV_StencilRef;
inline bool operator==(const SV_StencilRef_&, const SV_StencilRef_&) noexcept { return true; }
inline bool operator!=(const SV_StencilRef_&, const SV_StencilRef_&) noexcept { return false; }
struct SV_Target_ {} static constexpr SV_Target;
inline bool operator==(const SV_Target_&, const SV_Target_&) noexcept { return true; }
inline bool operator!=(const SV_Target_&, const SV_Target_&) noexcept { return false; }
struct SV_TessFactor_ {} static constexpr SV_TessFactor;
inline bool operator==(const SV_TessFactor_&, const SV_TessFactor_&) noexcept { return true; }
inline bool operator!=(const SV_TessFactor_&, const SV_TessFactor_&) noexcept { return false; }
struct SV_VertexID_ {} static constexpr SV_VertexID;
inline bool operator==(const SV_VertexID_&, const SV_VertexID_&) noexcept { return true; }
inline bool operator!=(const SV_VertexID_&, const SV_VertexID_&) noexcept { return false; }
struct SV_ViewportArrayIndex_ {} static constexpr SV_ViewportArrayIndex;
inline bool operator==(const SV_ViewportArrayIndex_&, const SV_ViewportArrayIndex_&) noexcept { return true; }
inline bool operator!=(const SV_ViewportArrayIndex_&, const SV_ViewportArrayIndex_&) noexcept { return false; }

using SemanticType = std::variant<std::monostate, BINORMAL_, BLENDINDICES_, BLENDWEIGHT_, NORMAL_, POSITIONT_, PSIZE_, TANGENT_, TEXCOORD_, SV_ClipDistance_, SV_CullDistance_, SV_Coverage_, SV_Depth_, SV_DepthGreaterEqual_, SV_DepthLessEqual_, SV_DispatchThreadID_, SV_DomainLocation_, SV_GroupID_, SV_GroupIndex_, SV_GroupThreadID_, SV_GSInstanceID_, SV_InnerCoverage_, SV_InsideTessFactor_, SV_InstanceID_, SV_IsFrontFace_, SV_OutputControlPointID_, SV_Position_, SV_PrimitiveID_, SV_RenderTargetArrayIndex_, SV_SampleIndex_, SV_StencilRef_, SV_Target_, SV_TessFactor_, SV_VertexID_, SV_ViewportArrayIndex_>;

inline bool operator<(const SemanticType& lhs, const SemanticType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
