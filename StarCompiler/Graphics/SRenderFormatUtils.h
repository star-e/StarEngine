// Copyright (C) 2019 star.engine@outlook.com
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
#include <Star/Graphics/SRenderFormat.h>
#include <StarCompiler/Graphics/SPixelFormatTypes.h>

namespace Star::Graphics::Render {

inline PixelFormat getPixelFormat(Format format) noexcept {
    const PixelSubSampling NoSubSampling{};
    const PixelUsage CommonUsage{};
    switch(format) {
    case Format::R64G64B64A64_UINT:
        return { RGBA, UInt, Interleaved{ { 64, 64, 64, 64 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64B64A64_SINT:
        return { RGBA, SInt, Interleaved{ { 64, 64, 64, 64 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64B64A64_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 64, 64, 64, 64 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64B64_UINT:
        return { RGBA, UInt, Interleaved{ { 64, 64, 64, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64B64_SINT:
        return { RGBA, SInt, Interleaved{ { 64, 64, 64, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64B64_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 64, 64, 64, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32A32_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 32, 32, 32, 32 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32A32_UINT:
        return { RGBA, UInt, Interleaved{ { 32, 32, 32, 32 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32A32_SINT:
        return { RGBA, SInt, Interleaved{ { 32, 32, 32, 32 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32A32_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 32, 32, 32, 32 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64_UINT:
        return { RGBA, UInt, Interleaved{ { 64, 64, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64_SINT:
        return { RGBA, SInt, Interleaved{ { 64, 64, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64G64_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 64, 64, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 32, 32, 32, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32_UINT:
        return { RGBA, UInt, Interleaved{ { 32, 32, 32, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32_SINT:
        return { RGBA, SInt, Interleaved{ { 32, 32, 32, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32B32_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 32, 32, 32, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_UNORM:
        return { RGBA, UNorm, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_SNORM:
        return { RGBA, SNorm, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_USCALED:
        return { RGBA, UScaled, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_UINT:
        return { RGBA, UInt, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_SINT:
        return { RGBA, SInt, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16A16_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 16, 16, 16, 16 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 32, 32, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32_UINT:
        return { RGBA, UInt, Interleaved{ { 32, 32, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32_SINT:
        return { RGBA, SInt, Interleaved{ { 32, 32, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G32_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 32, 32, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64_UINT:
        return { RGBA, UInt, Interleaved{ { 64, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64_SINT:
        return { RGBA, SInt, Interleaved{ { 64, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R64_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 64, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_UNORM:
        return { RGBA, UNorm, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_SNORM:
        return { RGBA, SNorm, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_USCALED:
        return { RGBA, UScaled, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_UINT:
        return { RGBA, UInt, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_SINT:
        return { RGBA, SInt, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16B16_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 16, 16, 16, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R10G10B10A2_TYPELESS_PACK32:
        return { RGBA, Typeless, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_UNORM_PACK32:
        return { RGBA, UNorm, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_SNORM_PACK32:
        return { RGBA, SNorm, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_USCALED_PACK32:
        return { RGBA, UScaled, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_SSCALED_PACK32:
        return { RGBA, SScaled, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_UINT_PACK32:
        return { RGBA, UInt, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10A2_SINT_PACK32:
        return { RGBA, SInt, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32:
        return { RGBA, XRBias, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_UNORM_PACK32:
        return { BGRA, UNorm, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_SNORM_PACK32:
        return { BGRA, SNorm, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_USCALED_PACK32:
        return { BGRA, UScaled, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_SSCALED_PACK32:
        return { BGRA, SScaled, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_UINT_PACK32:
        return { BGRA, UInt, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B10G10R10A2_SINT_PACK32:
        return { BGRA, SInt, Interleaved{ { 10, 10, 10, 2 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R9G9B9E5_UFLOAT_PACK32:
        return { RGBE, UFloat, Interleaved{ { 9, 9, 9, 5 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_UNORM:
        return { RGBA, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_UNORM_PACK32:
        return { RGBA, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_SNORM:
        return { RGBA, SNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_SNORM_PACK32:
        return { RGBA, SNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_USCALED:
        return { RGBA, UScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_USCALED_PACK32:
        return { RGBA, UScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_SSCALED_PACK32:
        return { RGBA, SScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_UINT:
        return { RGBA, UInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_UINT_PACK32:
        return { RGBA, UInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_SINT:
        return { RGBA, SInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_SINT_PACK32:
        return { RGBA, SInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::R8G8B8A8_SRGB:
        return { RGBA, SRGB, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8A8_SRGB_PACK32:
        return { RGBA, SRGB, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B8G8R8A8_TYPELESS:
        return { BGRA, Typeless, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_UNORM:
        return { BGRA, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_SNORM:
        return { BGRA, SNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_USCALED:
        return { BGRA, UScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_SSCALED:
        return { BGRA, SScaled, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_UINT:
        return { BGRA, UInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_SINT:
        return { BGRA, SInt, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8A8_SRGB:
        return { BGRA, SRGB, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R11G11B10_UFLOAT_PACK32:
        return { RGBA, UFloat, Interleaved{ { 11, 11, 10, 0 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::B8G8R8X8_TYPELESS:
        return { BGRA, Typeless, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{ 1, 32 }, CommonUsage };
    case Format::B8G8R8X8_UNORM:
        return { BGRA, UNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{ 1, 32 }, CommonUsage };
    case Format::B8G8R8X8_SRGB:
        return { BGRA, SRGB, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{ 1, 32 }, CommonUsage };
    case Format::R16G16_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_UNORM:
        return { RGBA, UNorm, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_SNORM:
        return { RGBA, SNorm, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_USCALED:
        return { RGBA, UScaled, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_UINT:
        return { RGBA, UInt, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_SINT:
        return { RGBA, SInt, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16G16_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 16, 16, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 32, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32_UINT:
        return { RGBA, UInt, Interleaved{ { 32, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32_SINT:
        return { RGBA, SInt, Interleaved{ { 32, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 32, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_UNORM:
        return { RGBA, UNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_SNORM:
        return { RGBA, SNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_USCALED:
        return { RGBA, UScaled, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_UINT:
        return { RGBA, UInt, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_SINT:
        return { RGBA, SInt, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8B8_SRGB:
        return { RGBA, SRGB, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_UNORM:
        return { BGRA, UNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_SNORM:
        return { BGRA, SNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_USCALED:
        return { BGRA, UScaled, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_SSCALED:
        return { BGRA, SScaled, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_UINT:
        return { BGRA, UInt, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_SINT:
        return { BGRA, SInt, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B8G8R8_SRGB:
        return { BGRA, SRGB, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::B5G5R5A1_UNORM_PACK16:
        return { BGRA, UNorm, Interleaved{ { 5, 5, 5, 1 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::A1B5G5R5_UNORM_PACK16:
        return { ABGR, UNorm, Interleaved{ { 5, 5, 5, 1 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::A1R5G5B5_UNORM_PACK16:
        return { ARGB, UNorm, Interleaved{ { 5, 5, 5, 1 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::A4B4G4R4_UNORM_PACK16:
        return { ABGR, UNorm, Interleaved{ { 4, 4, 4, 4 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::A4R4G4B4_UNORM_PACK16:
        return { ARGB, UNorm, Interleaved{ { 4, 4, 4, 4 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::R5G6B5_UNORM_PACK16:
        return { RGBA, UNorm, Interleaved{ { 5, 6, 5, 0 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::B5G6R5_UNORM_PACK16:
        return { BGRA, UNorm, Interleaved{ { 5, 6, 5, 0 } }, NoSubSampling, Pack{ 1, 16 }, CommonUsage };
    case Format::R8G8_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_UNORM:
        return { RGBA, UNorm, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_SNORM:
        return { RGBA, SNorm, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_USCALED:
        return { RGBA, UScaled, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_UINT:
        return { RGBA, UInt, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_SINT:
        return { RGBA, SInt, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8G8_SRGB:
        return { RGBA, SRGB, Interleaved{ { 8, 8, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_UNORM:
        return { RGBA, UNorm, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_SNORM:
        return { RGBA, SNorm, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_USCALED:
        return { RGBA, UScaled, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_UINT:
        return { RGBA, UInt, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_SINT:
        return { RGBA, SInt, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R16_SFLOAT:
        return { RGBA, SFloat, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::G4R4_UNORM_PACK8:
        return { BGRA, UNorm, Interleaved{ { 4, 4, 0, 0 } }, NoSubSampling, Pack{ 1, 8 }, CommonUsage };
    case Format::R8_TYPELESS:
        return { RGBA, Typeless, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_UNORM:
        return { RGBA, UNorm, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_SNORM:
        return { RGBA, SNorm, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_USCALED:
        return { RGBA, UScaled, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_SSCALED:
        return { RGBA, SScaled, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_UINT:
        return { RGBA, UInt, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_SINT:
        return { RGBA, SInt, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R8_SRGB:
        return { RGBA, SRGB, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::A8_UNORM:
        return { ABGR, UNorm, Interleaved{ { 0, 0, 0, 8 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R1_UNORM:
        return { RGBA, UNorm, Interleaved{ { 1, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::R32G8X24_TYPELESS_2PACK32:
        return { D_S, Typeless, Interleaved{ { 32, 8, 0, 0 } }, NoSubSampling, Pack{ 2, 32 }, CommonUsage };
    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32:
        return { D_X, SFloat, Interleaved{ { 32, 8, 0, 0 } }, NoSubSampling, Pack{ 2, 32 }, CommonUsage };
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32:
        return { X_S, UInt, Interleaved{ { 32, 8, 0, 0 } }, NoSubSampling, Pack{ 2, 32 }, CommonUsage };
    case Format::D32_SFLOAT_S8_UINT:
        return { D_S, SFloat, Interleaved{ { 32, 8, 0, 0 } }, NoSubSampling, Unspecified{}, CommonUsage };
    case Format::R24G8_TYPELESS_PACK32:
        return { D_S, Typeless, Interleaved{ { 24, 8, 0, 0 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::D24_UNORM_S8_UINT:
        return { D_S, UNorm, Interleaved{ { 24, 8, 0, 0 } }, NoSubSampling, Unspecified{}, CommonUsage };
    case Format::R24_UNORM_X8_TYPELESS_PACK32:
        return { D_X, UNorm, Interleaved{ { 24, 8, 0, 0 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::X24_TYPELESS_G8_UINT_PACK32:
        return { X_S, UInt, Interleaved{ { 24, 8, 0, 0 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::D24_UNORM_X8_TYPELESS_PACK32:
        return { D, UNorm, Interleaved{ { 24, 8, 0, 0 } }, NoSubSampling, Pack{ 1, 32 }, CommonUsage };
    case Format::D32_SFLOAT:
        return { D, SFloat, Interleaved{ { 32, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::D16_UNORM_S8_UINT:
        return { D_S, UNorm, Interleaved{ { 16, 8, 0, 0 } }, NoSubSampling, Unspecified{}, CommonUsage };
    case Format::D16_UNORM:
        return { D, UNorm, Interleaved{ { 16, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::S8_UINT:
        return { S, UInt, Interleaved{ { 8, 0, 0, 0 } }, NoSubSampling, Uniform{}, CommonUsage };
    case Format::BC1_RGBA_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 1, 1, 1, 1 } }, NoSubSampling, Block{ 1, 4 }, CommonUsage };
    case Format::BC1_RGBA_SRGB_BLOCK:
        return { BC, SRGB, Interleaved{ { 1, 1, 1, 1 } }, NoSubSampling, Block{ 1, 4 }, CommonUsage };
    case Format::BC1_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 1, 1, 1, 0 } }, NoSubSampling, Block{ 1, 4 }, CommonUsage };
    case Format::BC1_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 1, 1, 1, 0 } }, NoSubSampling, Block{ 1, 4 }, CommonUsage };
    case Format::BC1_SRGB_BLOCK:
        return { BC, SRGB, Interleaved{ { 1, 1, 1, 0 } }, NoSubSampling, Block{ 1, 4 }, CommonUsage };
    case Format::BC2_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 8 }, CommonUsage };
    case Format::BC2_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 8 }, CommonUsage };
    case Format::BC2_SRGB_BLOCK:
        return { BC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 8 }, CommonUsage };
    case Format::BC3_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 3, 8 }, CommonUsage };
    case Format::BC3_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 3, 8 }, CommonUsage };
    case Format::BC3_SRGB_BLOCK:
        return { BC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 3, 8 }, CommonUsage };
    case Format::BC4_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 4, 4 }, CommonUsage };
    case Format::BC4_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 4, 4 }, CommonUsage };
    case Format::BC4_SNORM_BLOCK:
        return { BC, SNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 4, 4 }, CommonUsage };
    case Format::BC5_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 5, 8 }, CommonUsage };
    case Format::BC5_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 5, 8 }, CommonUsage };
    case Format::BC5_SNORM_BLOCK:
        return { BC, SNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 5, 8 }, CommonUsage };
    case Format::BC6H_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 6, 8 }, CommonUsage };
    case Format::BC6H_UFLOAT_BLOCK:
        return { BC, UFloat, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 6, 8 }, CommonUsage };
    case Format::BC6H_SFLOAT_BLOCK:
        return { BC, SFloat, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 6, 8 }, CommonUsage };
    case Format::BC7_TYPELESS_BLOCK:
        return { BC, Typeless, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 7, 8 }, CommonUsage };
    case Format::BC7_UNORM_BLOCK:
        return { BC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 7, 8 }, CommonUsage };
    case Format::BC7_SRGB_BLOCK:
        return { BC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 7, 8 }, CommonUsage };
    case Format::ETC2_R8G8B8A8_UNORM_BLOCK:
        return { ETC2, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Block{ 0, 8 }, CommonUsage };
    case Format::ETC2_R8G8B8A8_SRGB_BLOCK:
        return { ETC2, SRGB, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Block{ 0, 8 }, CommonUsage };
    case Format::ETC2_R8G8B8A1_UNORM_BLOCK:
        return { ETC2, UNorm, Interleaved{ { 8, 8, 8, 1 } }, NoSubSampling, Block{ 0, 4 }, CommonUsage };
    case Format::ETC2_R8G8B8A1_SRGB_BLOCK:
        return { ETC2, SRGB, Interleaved{ { 8, 8, 8, 1 } }, NoSubSampling, Block{ 0, 4 }, CommonUsage };
    case Format::ETC2_R8G8B8_UNORM_BLOCK:
        return { ETC2, UNorm, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Block{ 0, 4 }, CommonUsage };
    case Format::ETC2_R8G8B8_SRGB_BLOCK:
        return { ETC2, SRGB, Interleaved{ { 8, 8, 8, 0 } }, NoSubSampling, Block{ 0, 4 }, CommonUsage };
    case Format::EAC_R11G11_UNORM_BLOCK:
        return { EAC, UNorm, Interleaved{ { 11, 11, 0, 0 } }, NoSubSampling, Block{ 0, 16 }, CommonUsage };
    case Format::EAC_R11G11_SNORM_BLOCK:
        return { EAC, SNorm, Interleaved{ { 11, 11, 0, 0 } }, NoSubSampling, Block{ 0, 16 }, CommonUsage };
    case Format::EAC_R11_UNORM_BLOCK:
        return { EAC, UNorm, Interleaved{ { 11, 0, 0, 0 } }, NoSubSampling, Block{ 0, 8 }, CommonUsage };
    case Format::EAC_R11_SNORM_BLOCK:
        return { EAC, SNorm, Interleaved{ { 11, 0, 0, 0 } }, NoSubSampling, Block{ 0, 8 }, CommonUsage };
    case Format::ASTC_4x4_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 4, 4 }, CommonUsage };
    case Format::ASTC_4x4_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 4, 4 }, CommonUsage };
    case Format::ASTC_5x4_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 5, 4 }, CommonUsage };
    case Format::ASTC_5x4_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 5, 4 }, CommonUsage };
    case Format::ASTC_5x5_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 5, 5 }, CommonUsage };
    case Format::ASTC_5x5_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 5, 5 }, CommonUsage };
    case Format::ASTC_6x5_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 6, 5 }, CommonUsage };
    case Format::ASTC_6x5_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 6, 5 }, CommonUsage };
    case Format::ASTC_6x6_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 6, 6 }, CommonUsage };
    case Format::ASTC_6x6_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 6, 6 }, CommonUsage };
    case Format::ASTC_8x5_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 5 }, CommonUsage };
    case Format::ASTC_8x5_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 5 }, CommonUsage };
    case Format::ASTC_8x6_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 6 }, CommonUsage };
    case Format::ASTC_8x6_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 6 }, CommonUsage };
    case Format::ASTC_8x8_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 8 }, CommonUsage };
    case Format::ASTC_8x8_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 8, 8 }, CommonUsage };
    case Format::ASTC_10x5_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 5 }, CommonUsage };
    case Format::ASTC_10x5_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 5 }, CommonUsage };
    case Format::ASTC_10x6_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 6 }, CommonUsage };
    case Format::ASTC_10x6_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 6 }, CommonUsage };
    case Format::ASTC_10x8_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 8 }, CommonUsage };
    case Format::ASTC_10x8_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 8 }, CommonUsage };
    case Format::ASTC_10x10_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 10 }, CommonUsage };
    case Format::ASTC_10x10_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 10, 10 }, CommonUsage };
    case Format::ASTC_12x10_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 12, 10 }, CommonUsage };
    case Format::ASTC_12x10_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 12, 10 }, CommonUsage };
    case Format::ASTC_12x12_UNORM_BLOCK:
        return { ASTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 12, 12 }, CommonUsage };
    case Format::ASTC_12x12_SRGB_BLOCK:
        return { ASTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Adaptive{ 12, 12 }, CommonUsage };
    case Format::R12X4G12X4B12X4A12X4_UNORM_4PACK16:
        return { RGBA, UNorm, Interleaved{ { 12, 12, 12, 12 } }, NoSubSampling, Pack{ 4, 16 }, Video };
    case Format::R10X6G10X6B10X6A10X6_UNORM_4PACK16:
        return { RGBA, UNorm, Interleaved{ { 10, 10, 10, 10 } }, NoSubSampling, Pack{ 4, 16 }, Video };
    case Format::R12X4G12X4_UNORM_2PACK16:
        return { RGBA, UNorm, Interleaved{ { 12, 12, 0, 0 } }, NoSubSampling, Pack{ 2, 16 }, Video };
    case Format::R10X6G10X6_UNORM_2PACK16:
        return { RGBA, UNorm, Interleaved{ { 10, 10, 0, 0 } }, NoSubSampling, Pack{ 2, 16 }, Video };
    case Format::R12X4_UNORM_PACK16:
        return { RGBA, UNorm, Interleaved{ { 12, 0, 0, 0 } }, NoSubSampling, Pack{ 1, 16 }, Video };
    case Format::R10X6_UNORM_PACK16:
        return { RGBA, UNorm, Interleaved{ { 10, 0, 0, 0 } }, NoSubSampling, Pack{ 1, 16 }, Video };
    case Format::R8G8_B8G8_UNORM:
        return { RGBG, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, Video };
    case Format::G16B16_G16R16_422_UNORM:
        return { GBGR, UNorm, Interleaved{ { 16, 16, 16, 16 } }, J422, Uniform{}, Video };
    case Format::G12X4B12X4_G12X4R12X4_422_UNORM_4PACK16:
        return { GBGR, UNorm, Interleaved{ { 12, 12, 12, 12 } }, J422, Pack{ 4, 16 }, Video };
    case Format::G10X6B10X6_G10X6R10X6_422_UNORM_4PACK16:
        return { GBGR, UNorm, Interleaved{ { 10, 10, 10, 10 } }, J422, Pack{ 4, 16 }, Video };
    case Format::G8B8_G8R8_422_UNORM:
        return { GBGR, UNorm, Interleaved{ { 8, 8, 8, 8 } }, J422, Uniform{}, Video };
    case Format::G8R8_G8B8_UNORM:
        return { GRGB, UNorm, Interleaved{ { 8, 8, 8, 8 } }, NoSubSampling, Uniform{}, Video };
    case Format::B16G16_R16G16_422_UNORM:
        return { BGRG, UNorm, Interleaved{ { 16, 16, 16, 16 } }, J422, Uniform{}, Video };
    case Format::B12X4G12X4_R12X4G12X4_422_UNORM_4PACK16:
        return { BGRG, UNorm, Interleaved{ { 12, 12, 12, 12 } }, J422, Pack{ 4, 16 }, Video };
    case Format::B10X6G10X6_R10X6G10X6_422_UNORM_4PACK16:
        return { BGRG, UNorm, Interleaved{ { 10, 10, 10, 10 } }, J422, Pack{ 4, 16 }, Video };
    case Format::B8G8_R8G8_422_UNORM:
        return { BGRG, UNorm, Interleaved{ { 8, 8, 8, 8 } }, J422, Uniform{}, Video };
    case Format::G16_B16_R16_3PLANE_444_UNORM:
        return { G_B_R, UNorm, Planar{ { 16, 16, 16, 0 } }, J444, Uniform{}, Video };
    case Format::G16_B16_R16_3PLANE_422_UNORM:
        return { G_B_R, UNorm, Planar{ { 16, 16, 16, 0 } }, J422, Uniform{}, Video };
    case Format::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 12, 12, 12, 0 } }, J444, Pack{ 3, 16 }, Video };
    case Format::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 12, 12, 12, 0 } }, J422, Pack{ 3, 16 }, Video };
    case Format::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 10, 10, 10, 0 } }, J444, Pack{ 3, 16 }, Video };
    case Format::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 10, 10, 10, 0 } }, J422, Pack{ 3, 16 }, Video };
    case Format::G16_B16_R16_3PLANE_420_UNORM:
        return { G_B_R, UNorm, Planar{ { 16, 16, 16, 0 } }, J420, Uniform{}, Video };
    case Format::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 12, 12, 12, 0 } }, J420, Pack{ 3, 16 }, Video };
    case Format::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16:
        return { G_B_R, UNorm, Planar{ { 10, 10, 10, 0 } }, J420, Pack{ 3, 16 }, Video };
    case Format::G8_B8_R8_3PLANE_444_UNORM:
        return { G_B_R, UNorm, Planar{ { 8, 8, 8, 0 } }, J444, Uniform{}, Video };
    case Format::G8_B8_R8_3PLANE_422_UNORM:
        return { G_B_R, UNorm, Planar{ { 8, 8, 8, 0 } }, J422, Uniform{}, Video };
    case Format::G8_B8_R8_3PLANE_420_UNORM:
        return { G_B_R, UNorm, Planar{ { 8, 8, 8, 0 } }, J420, Uniform{}, Video };
    case Format::G16_B16R16_2PLANE_422_UNORM:
        return { G_BR, UNorm, Planar{ { 16, 16, 16, 0 } }, J422, Uniform{}, Video };
    case Format::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16:
        return { G_BR, UNorm, Planar{ { 12, 12, 12, 0 } }, J422, Pack{ 3, 16 }, Video };
    case Format::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16:
        return { G_BR, UNorm, Planar{ { 10, 10, 10, 0 } }, J422, Pack{ 3, 16 }, Video };
    case Format::G16_B16R16_2PLANE_420_UNORM:
        return { G_BR, UNorm, Planar{ { 16, 16, 16, 0 } }, J420, Uniform{}, Video };
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
        return { G_BR, UNorm, Planar{ { 12, 12, 12, 0 } }, J420, Pack{ 3, 16 }, Video };
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
        return { G_BR, UNorm, Planar{ { 10, 10, 10, 0 } }, J420, Pack{ 3, 16 }, Video };
    case Format::G8_B8R8_2PLANE_422_UNORM:
        return { G_BR, UNorm, Planar{ { 8, 8, 8, 0 } }, J422, Uniform{}, Video };
    case Format::G8_B8R8_2PLANE_420_UNORM:
        return { G_BR, UNorm, Planar{ { 8, 8, 8, 0 } }, J420, Uniform{}, Video };
    case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG:
        return { PVRTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 1, 4 }, IMG };
    case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG:
        return { PVRTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 1, 4 }, IMG };
    case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG:
        return { PVRTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 1, 2 }, IMG };
    case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG:
        return { PVRTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 1, 2 }, IMG };
    case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG:
        return { PVRTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 4 }, IMG };
    case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG:
        return { PVRTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 4 }, IMG };
    case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG:
        return { PVRTC, UNorm, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 2 }, IMG };
    case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG:
        return { PVRTC, SRGB, Interleaved{ { 0, 0, 0, 0 } }, NoSubSampling, Block{ 2, 2 }, IMG };
    default: return {};
    }
}

}
