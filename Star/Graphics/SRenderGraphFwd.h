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
struct RenderSubpass;
struct RenderSubpassDependency;
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
