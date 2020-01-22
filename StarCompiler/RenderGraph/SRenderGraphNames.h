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
#include <StarCompiler/RenderGraph/SRenderGraphFwd.h>
#include <StarCompiler/Graphics/SPixelFormatNames.h>
#include <StarCompiler/Graphics/SRenderNames.h>
#include <Star/Graphics/SRenderGraphNames.h>

namespace Star {

namespace Graphics {

namespace Render {

inline const char* getName(const ResourceBuffer& v) noexcept { return "ResourceBuffer"; }
inline const char* getName(const Resource1D& v) noexcept { return "Resource1D"; }
inline const char* getName(const Resource2D& v) noexcept { return "Resource2D"; }
inline const char* getName(const Resource3D& v) noexcept { return "Resource3D"; }
inline const char* getName(const MipChain& v) noexcept { return "MipChain"; }
inline const char* getName(const MipLevels& v) noexcept { return "MipLevels"; }
inline const char* getName(const ArraySize& v) noexcept { return "ArraySize"; }
inline const char* getName(const Multisampling& v) noexcept { return "Multisampling"; }
inline const char* getName(const RowMajor_& v) noexcept { return "RowMajor"; }
inline const char* getName(const UndefinedSwizzle64KB_& v) noexcept { return "UndefinedSwizzle64KB"; }
inline const char* getName(const StandardSwizzle64KB_& v) noexcept { return "StandardSwizzle64KB"; }
inline const char* getName(const Resource& v) noexcept { return "Resource"; }
inline const char* getName(const BarrierTransition_& v) noexcept { return "BarrierTransition"; }
inline const char* getName(const BarrierAliasing_& v) noexcept { return "BarrierAliasing"; }
inline const char* getName(const BarrierUav_& v) noexcept { return "BarrierUav"; }
inline const char* getName(const Source_& v) noexcept { return "Source"; }
inline const char* getName(const Target_& v) noexcept { return "Target"; }
inline const char* getName(const Common_& v) noexcept { return "Common"; }
inline const char* getName(const VertexAndConstantBuffer_& v) noexcept { return "VertexAndConstantBuffer"; }
inline const char* getName(const IndexBuffer_& v) noexcept { return "IndexBuffer"; }
inline const char* getName(const RenderTarget_& v) noexcept { return "RenderTarget"; }
inline const char* getName(const UnorderedAccess_& v) noexcept { return "UnorderedAccess"; }
inline const char* getName(const DepthWrite_& v) noexcept { return "DepthWrite"; }
inline const char* getName(const DepthRead_& v) noexcept { return "DepthRead"; }
inline const char* getName(const ShaderResource_& v) noexcept { return "ShaderResource"; }
inline const char* getName(const StreamOut_& v) noexcept { return "StreamOut"; }
inline const char* getName(const IndirectArgument_& v) noexcept { return "IndirectArgument"; }
inline const char* getName(const CopyDest_& v) noexcept { return "CopyDest"; }
inline const char* getName(const CopySource_& v) noexcept { return "CopySource"; }
inline const char* getName(const ResolveDest_& v) noexcept { return "ResolveDest"; }
inline const char* getName(const ResolveSource_& v) noexcept { return "ResolveSource"; }
inline const char* getName(const Present_& v) noexcept { return "Present"; }
inline const char* getName(const Raytracing_& v) noexcept { return "Raytracing"; }
inline const char* getName(const Predication_& v) noexcept { return "Predication"; }
inline const char* getName(const RenderTargetState& v) noexcept { return "RenderTargetState"; }
inline const char* getName(const RenderValue& v) noexcept { return "RenderValue"; }
inline const char* getName(const NodeRenderTargetState& v) noexcept { return "NodeRenderTargetState"; }
inline const char* getName(const RenderTargetStateTransition& v) noexcept { return "RenderTargetStateTransition"; }
inline const char* getName(const RenderTargetStateTransitions& v) noexcept { return "RenderTargetStateTransitions"; }
inline const char* getName(const UnorderedRenderContent& v) noexcept { return "UnorderedRenderContent"; }
inline const char* getName(const RenderNode& v) noexcept { return "RenderNode"; }
inline const char* getName(const RenderGroup& v) noexcept { return "RenderGroup"; }
inline const char* getName(const BackBuffer_& v) noexcept { return "BackBuffer"; }
inline const char* getName(const RenderTargetResource& v) noexcept { return "RenderTargetResource"; }
inline const char* getName(const RenderConfigs& v) noexcept { return "RenderConfigs"; }

} // namespace Render

} // namespace Graphics

} // namespace Star
