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

namespace Star {

namespace Graphics {

inline const char* getName(const Unknown_& v) noexcept { return "Unknown"; }
inline const char* getName(const RGBA_& v) noexcept { return "RGBA"; }
inline const char* getName(const BGRA_& v) noexcept { return "BGRA"; }
inline const char* getName(const ABGR_& v) noexcept { return "ABGR"; }
inline const char* getName(const ARGB_& v) noexcept { return "ARGB"; }
inline const char* getName(const RGBE_& v) noexcept { return "RGBE"; }
inline const char* getName(const D_S_& v) noexcept { return "D_S"; }
inline const char* getName(const D_X_& v) noexcept { return "D_X"; }
inline const char* getName(const D_& v) noexcept { return "D"; }
inline const char* getName(const S_& v) noexcept { return "S"; }
inline const char* getName(const X_S_& v) noexcept { return "X_S"; }
inline const char* getName(const BC_& v) noexcept { return "BC"; }
inline const char* getName(const ETC2_& v) noexcept { return "ETC2"; }
inline const char* getName(const EAC_& v) noexcept { return "EAC"; }
inline const char* getName(const ASTC_& v) noexcept { return "ASTC"; }
inline const char* getName(const RGBG_& v) noexcept { return "RGBG"; }
inline const char* getName(const GBGR_& v) noexcept { return "GBGR"; }
inline const char* getName(const GRGB_& v) noexcept { return "GRGB"; }
inline const char* getName(const BGRG_& v) noexcept { return "BGRG"; }
inline const char* getName(const G_B_R_& v) noexcept { return "G_B_R"; }
inline const char* getName(const G_BR_& v) noexcept { return "G_BR"; }
inline const char* getName(const PVRTC_& v) noexcept { return "PVRTC"; }
inline const char* getName(const Typeless_& v) noexcept { return "Typeless"; }
inline const char* getName(const UNorm_& v) noexcept { return "UNorm"; }
inline const char* getName(const SNorm_& v) noexcept { return "SNorm"; }
inline const char* getName(const UScaled_& v) noexcept { return "UScaled"; }
inline const char* getName(const SScaled_& v) noexcept { return "SScaled"; }
inline const char* getName(const UInt_& v) noexcept { return "UInt"; }
inline const char* getName(const SInt_& v) noexcept { return "SInt"; }
inline const char* getName(const SRGB_& v) noexcept { return "SRGB"; }
inline const char* getName(const XRBias_& v) noexcept { return "XRBias"; }
inline const char* getName(const UFloat_& v) noexcept { return "UFloat"; }
inline const char* getName(const SFloat_& v) noexcept { return "SFloat"; }
inline const char* getName(const Double_& v) noexcept { return "Double"; }
inline const char* getName(const Interleaved& v) noexcept { return "Interleaved"; }
inline const char* getName(const Planar& v) noexcept { return "Planar"; }
inline const char* getName(const Uniform& v) noexcept { return "Uniform"; }
inline const char* getName(const Unspecified& v) noexcept { return "Unspecified"; }
inline const char* getName(const Pack& v) noexcept { return "Pack"; }
inline const char* getName(const Block& v) noexcept { return "Block"; }
inline const char* getName(const Adaptive& v) noexcept { return "Adaptive"; }
inline const char* getName(const J444_& v) noexcept { return "J444"; }
inline const char* getName(const J422_& v) noexcept { return "J422"; }
inline const char* getName(const J420_& v) noexcept { return "J420"; }
inline const char* getName(const Video_& v) noexcept { return "Video"; }
inline const char* getName(const IMG_& v) noexcept { return "IMG"; }
inline const char* getName(const PixelFormat& v) noexcept { return "PixelFormat"; }
inline const char* getName(const PixelEncoding& v) noexcept { return "PixelEncoding"; }
inline const char* getName(const SIZING_Y_UV_420_& v) noexcept { return "SIZING_Y_UV_420"; }

} // namespace Graphics

} // namespace Star

namespace Star {

namespace Graphics {

inline const char* getTag(const Unknown_& v) noexcept { return "Unknown"; }
inline const char* getTag(const RGBA_& v) noexcept { return "RGBA"; }
inline const char* getTag(const BGRA_& v) noexcept { return "BGRA"; }
inline const char* getTag(const ABGR_& v) noexcept { return "ABGR"; }
inline const char* getTag(const ARGB_& v) noexcept { return "ARGB"; }
inline const char* getTag(const RGBE_& v) noexcept { return "RGBE"; }
inline const char* getTag(const D_S_& v) noexcept { return "D_S"; }
inline const char* getTag(const D_X_& v) noexcept { return "D_X"; }
inline const char* getTag(const D_& v) noexcept { return "D"; }
inline const char* getTag(const S_& v) noexcept { return "S"; }
inline const char* getTag(const X_S_& v) noexcept { return "X_S"; }
inline const char* getTag(const BC_& v) noexcept { return "BC"; }
inline const char* getTag(const ETC2_& v) noexcept { return "ETC2"; }
inline const char* getTag(const EAC_& v) noexcept { return "EAC"; }
inline const char* getTag(const ASTC_& v) noexcept { return "ASTC"; }
inline const char* getTag(const RGBG_& v) noexcept { return "RGBG"; }
inline const char* getTag(const GBGR_& v) noexcept { return "GBGR"; }
inline const char* getTag(const GRGB_& v) noexcept { return "GRGB"; }
inline const char* getTag(const BGRG_& v) noexcept { return "BGRG"; }
inline const char* getTag(const G_B_R_& v) noexcept { return "G_B_R"; }
inline const char* getTag(const G_BR_& v) noexcept { return "G_BR"; }
inline const char* getTag(const PVRTC_& v) noexcept { return "PVRTC"; }
inline const char* getTag(const Typeless_& v) noexcept { return "Typeless"; }
inline const char* getTag(const UNorm_& v) noexcept { return "UNorm"; }
inline const char* getTag(const SNorm_& v) noexcept { return "SNorm"; }
inline const char* getTag(const UScaled_& v) noexcept { return "UScaled"; }
inline const char* getTag(const SScaled_& v) noexcept { return "SScaled"; }
inline const char* getTag(const UInt_& v) noexcept { return "UInt"; }
inline const char* getTag(const SInt_& v) noexcept { return "SInt"; }
inline const char* getTag(const SRGB_& v) noexcept { return "SRGB"; }
inline const char* getTag(const XRBias_& v) noexcept { return "XRBias"; }
inline const char* getTag(const UFloat_& v) noexcept { return "UFloat"; }
inline const char* getTag(const SFloat_& v) noexcept { return "SFloat"; }
inline const char* getTag(const Double_& v) noexcept { return "Double"; }
inline const char* getTag(const J444_& v) noexcept { return "J444"; }
inline const char* getTag(const J422_& v) noexcept { return "J422"; }
inline const char* getTag(const J420_& v) noexcept { return "J420"; }
inline const char* getTag(const Video_& v) noexcept { return "Video"; }
inline const char* getTag(const IMG_& v) noexcept { return "IMG"; }
inline const char* getTag(const SIZING_Y_UV_420_& v) noexcept { return "SIZING_Y_UV_420"; }

} // namespace Graphics

} // namespace Star
