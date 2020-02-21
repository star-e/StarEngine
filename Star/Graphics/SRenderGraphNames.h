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
#include <Star/Graphics/SRenderGraphFwd.h>
#include <Star/Graphics/SRenderNames.h>

namespace Star {

namespace Graphics {

namespace Render {

inline const char* getName(const Linear_& v) noexcept { return "Linear"; }
inline const char* getName(const Device_& v) noexcept { return "Device"; }
inline const char* getName(const Load_& v) noexcept { return "Load"; }
inline const char* getName(const DontRead_& v) noexcept { return "DontRead"; }
inline const char* getName(const Store_& v) noexcept { return "Store"; }
inline const char* getName(const Discard_& v) noexcept { return "Discard"; }
inline const char* getName(const ClearColor& v) noexcept { return "ClearColor"; }
inline const char* getName(const ClearDepthStencil& v) noexcept { return "ClearDepthStencil"; }
inline const char* getName(const FramebufferHandle& v) noexcept { return "FramebufferHandle"; }
inline const char* getName(const DescriptorHandle& v) noexcept { return "DescriptorHandle"; }
inline const char* getName(const Attachment& v) noexcept { return "Attachment"; }
inline const char* getName(const RenderViewTransition& v) noexcept { return "RenderViewTransition"; }
inline const char* getName(const UnorderedRenderQueue& v) noexcept { return "UnorderedRenderQueue"; }

namespace Descriptor {

inline const char* getName(const ConstantBuffer_& v) noexcept { return "ConstantBuffer"; }
inline const char* getName(const BaseColor_& v) noexcept { return "BaseColor"; }
inline const char* getName(const LinearSampler_& v) noexcept { return "LinearSampler"; }

} // namespace Descriptor

namespace Data {

inline const char* getName(const Proj_& v) noexcept { return "Proj"; }
inline const char* getName(const View_& v) noexcept { return "View"; }
inline const char* getName(const WorldView_& v) noexcept { return "WorldView"; }

} // namespace Data
inline const char* getName(const ShaderDescriptor& v) noexcept { return "ShaderDescriptor"; }
inline const char* getName(const ShaderDescriptorSubrange& v) noexcept { return "ShaderDescriptorSubrange"; }
inline const char* getName(const ShaderDescriptorRange& v) noexcept { return "ShaderDescriptorRange"; }
inline const char* getName(const ShaderUnboundedDescriptor& v) noexcept { return "ShaderUnboundedDescriptor"; }
inline const char* getName(const ShaderDescriptorList& v) noexcept { return "ShaderDescriptorList"; }
inline const char* getName(const ShaderDescriptorCollection& v) noexcept { return "ShaderDescriptorCollection"; }
inline const char* getName(const ShaderConstant& v) noexcept { return "ShaderConstant"; }
inline const char* getName(const ShaderConstantBuffer& v) noexcept { return "ShaderConstantBuffer"; }
inline const char* getName(const RenderSubpass& v) noexcept { return "RenderSubpass"; }
inline const char* getName(const RenderSubpassDependency& v) noexcept { return "RenderSubpassDependency"; }
inline const char* getName(const RenderPass& v) noexcept { return "RenderPass"; }
inline const char* getName(const RenderPassDependency& v) noexcept { return "RenderPassDependency"; }
inline const char* getName(const RenderSubpassDesc& v) noexcept { return "RenderSubpassDesc"; }
inline const char* getName(const RenderPipeline& v) noexcept { return "RenderPipeline"; }
inline const char* getName(const Framebuffer& v) noexcept { return "Framebuffer"; }
inline const char* getName(const RenderSolution& v) noexcept { return "RenderSolution"; }
inline const char* getName(const SwapChain& v) noexcept { return "SwapChain"; }
inline const char* getName(const RenderSwapChain& v) noexcept { return "RenderSwapChain"; }

} // namespace Render

} // namespace Graphics

} // namespace Star
