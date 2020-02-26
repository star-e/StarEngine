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
#include <Star/Graphics/SRenderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct Linear_;
struct Device_;

using ColorSpace = std::variant<Linear_, Device_>;

struct Load_;
struct DontRead_;
struct Store_;
struct Discard_;
struct ClearColor;
struct ClearDepthStencil;

using OptimizedClearColor = std::variant<ClearColor, ClearDepthStencil>;
using LoadOp = std::variant<Load_, DontRead_, ClearColor, ClearDepthStencil>;
using StoreOp = std::variant<Store_, Discard_>;

struct FramebufferHandle;
struct DescriptorHandle;
struct Attachment;
struct RenderViewTransition;
struct UnorderedRenderQueue;

namespace Descriptor {

struct ConstantBuffer_;
struct BaseColor_;
struct LinearSampler_;

using Type = std::variant<std::monostate, ConstantBuffer_, BaseColor_, LinearSampler_>;

} // namespace Descriptor

namespace Data {

struct Proj_;
struct View_;
struct WorldView_;
struct WorldInvT_;

using Type = std::variant<std::monostate, Proj_, View_, WorldView_, WorldInvT_>;

} // namespace Data

struct ShaderDescriptor;
struct ShaderDescriptorSubrange;
struct ShaderDescriptorRange;
struct ShaderUnboundedDescriptor;
struct ShaderDescriptorList;
struct ShaderDescriptorCollection;
struct ShaderConstant;
struct ShaderConstantBuffer;
struct RasterSubpass;
struct RasterSubpassDependency;
struct ComputeSubpass;
struct RaytracingSubpass;
struct RenderPass;
struct RenderPassDependency;
struct RenderSubpassDesc;
struct RenderPipeline;
struct Framebuffer;
struct RenderSolution;
struct SwapChain;
struct RenderSwapChain;

} // namespace Render

} // namespace Graphics

} // namespace Star
