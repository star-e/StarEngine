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

namespace Star {

namespace Graphics {

struct Unknown_;
struct RGBA_;
struct BGRA_;
struct ABGR_;
struct ARGB_;
struct RGBE_;
struct D_S_;
struct D_X_;
struct D_;
struct S_;
struct X_S_;
struct BC_;
struct ETC2_;
struct EAC_;
struct ASTC_;
struct RGBG_;
struct GBGR_;
struct GRGB_;
struct BGRG_;
struct G_B_R_;
struct G_BR_;
struct PVRTC_;

using PixelLayout = std::variant<Unknown_, RGBA_, BGRA_, ABGR_, ARGB_, RGBE_, D_S_, D_X_, X_S_, D_, S_, BC_, ETC2_, EAC_, ASTC_, RGBG_, GBGR_, GRGB_, BGRG_, G_B_R_, G_BR_, PVRTC_>;

struct Typeless_;
struct UNorm_;
struct SNorm_;
struct UScaled_;
struct SScaled_;
struct UInt_;
struct SInt_;
struct SRGB_;
struct XRBias_;
struct UFloat_;
struct SFloat_;
struct Double_;

using PixelModel = std::variant<Typeless_, UNorm_, SNorm_, UScaled_, SScaled_, UInt_, SInt_, SRGB_, XRBias_, UFloat_, SFloat_, Double_>;

struct Interleaved;
struct Planar;

using PixelMemoryLayout = std::variant<Interleaved, Planar>;

struct Uniform;
struct Unspecified;
struct Pack;
struct Block;
struct Adaptive;

using PixelPacking = std::variant<Uniform, Unspecified, Pack, Block, Adaptive>;

struct J444_;
struct J422_;
struct J420_;

using PixelSubSampling = std::variant<std::monostate, J444_, J422_, J420_>;

struct Video_;
struct IMG_;

using PixelUsage = std::variant<std::monostate, Video_, IMG_>;

struct PixelFormat;
struct PixelEncoding;
struct SIZING_Y_UV_420_;

using TextureSizing = std::variant<std::monostate, SIZING_Y_UV_420_>;

} // namespace Graphics

} // namespace Star
