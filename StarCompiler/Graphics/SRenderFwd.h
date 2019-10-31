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

struct CBV_;
struct UAV_;
struct SRV_;
struct SSV_;
struct RTV_;
struct DSV_;
struct IBV_;
struct VBV_;
struct SOV_;
struct BufferRaw_;

using BufferFlag = std::variant<std::monostate, BufferRaw_>;

struct BufferView;
struct MipChainView;
struct MipRangeView;

using MipView = std::variant<std::monostate, MipChainView, MipRangeView>;

struct PlaneSlice;

using PlaneView = std::variant<std::monostate, PlaneSlice>;

struct ArrayRange;
struct DepthRange;
struct CubeSlice;
struct CubeRange;

using ArrayOrDepthView = std::variant<std::monostate, ArrayRange, DepthRange, CubeSlice, CubeRange>;

struct TextureView;
struct RaytracingView;

using ResourceDataView = std::variant<BufferView, TextureView, RaytracingView>;

} // namespace Render

} // namespace Graphics

} // namespace Star
