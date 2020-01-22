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
#include <StarCompiler/Graphics/SPixelFormatFwd.h>
#include <StarCompiler/Graphics/SRenderFwd.h>
#include <Star/Graphics/SRenderGraphFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct ResourceBuffer;
struct Resource1D;
struct Resource2D;
struct Resource3D;
struct MipChain;
struct MipLevels;
struct ArraySize;
struct Multisampling;

using ResourceType = std::variant<ResourceBuffer, Resource1D, Resource2D, Resource3D>;
using ResourceArray = std::variant<std::monostate, ArraySize>;
using ResourceMipMap = std::variant<std::monostate, MipChain, MipLevels>;
using ResourceSampling = std::variant<std::monostate, Multisampling>;

struct RowMajor_;
struct UndefinedSwizzle64KB_;
struct StandardSwizzle64KB_;

using ResourceLayout = std::variant<std::monostate, RowMajor_, UndefinedSwizzle64KB_, StandardSwizzle64KB_>;

struct Resource;
struct BarrierTransition_;
struct BarrierAliasing_;
struct BarrierUav_;

using ResourceBarrierType = std::variant<BarrierTransition_, BarrierAliasing_, BarrierUav_>;
using ResourceViewType = std::variant<SRV_, UAV_, DSV_, RTV_>;
using ShaderDescriptorType = std::variant<CBV_, UAV_, SRV_>;

struct Source_;
struct Target_;

using SourceTarget = std::variant<Source_, Target_>;

struct Common_;
struct VertexAndConstantBuffer_;
struct IndexBuffer_;
struct RenderTarget_;
struct UnorderedAccess_;
struct DepthWrite_;
struct DepthRead_;
struct ShaderResource_;
struct StreamOut_;
struct IndirectArgument_;
struct CopyDest_;
struct CopySource_;
struct ResolveDest_;
struct ResolveSource_;
struct Present_;
struct Raytracing_;
struct Predication_;

using TextureViewState = std::variant<Common_, RenderTarget_, UnorderedAccess_, DepthWrite_, DepthRead_, ShaderResource_, CopyDest_, CopySource_, ResolveDest_, ResolveSource_, Present_>;

struct RenderTargetState;
struct RenderValue;
struct NodeRenderTargetState;
struct RenderTargetStateTransition;
struct RenderTargetStateTransitions;
struct UnorderedRenderContent;
struct RenderNode;
struct RenderGroup;
struct BackBuffer_;

using RenderTargetType = std::variant<std::monostate, BackBuffer_>;

struct RenderTargetResource;
struct RenderConfigs;

} // namespace Render

} // namespace Graphics

} // namespace Star
