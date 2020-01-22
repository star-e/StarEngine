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
#include <StarCompiler/Graphics/SRenderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

inline const char* getName(const BufferRaw_& v) noexcept { return "BufferRaw"; }
inline const char* getName(const BufferView& v) noexcept { return "BufferView"; }
inline const char* getName(const MipChainView& v) noexcept { return "MipChainView"; }
inline const char* getName(const MipRangeView& v) noexcept { return "MipRangeView"; }
inline const char* getName(const PlaneSlice& v) noexcept { return "PlaneSlice"; }
inline const char* getName(const ArrayRange& v) noexcept { return "ArrayRange"; }
inline const char* getName(const DepthRange& v) noexcept { return "DepthRange"; }
inline const char* getName(const CubeSlice& v) noexcept { return "CubeSlice"; }
inline const char* getName(const CubeRange& v) noexcept { return "CubeRange"; }
inline const char* getName(const TextureView& v) noexcept { return "TextureView"; }
inline const char* getName(const RaytracingView& v) noexcept { return "RaytracingView"; }

} // namespace Render

} // namespace Graphics

} // namespace Star
