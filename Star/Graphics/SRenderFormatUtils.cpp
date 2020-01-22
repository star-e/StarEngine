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

#include <Star/Graphics/SRenderFormatUtils.h>

namespace Star::Graphics::Render {

bool isTypeless(Format format) noexcept {
    switch(format) {
    case Format::R32G32B32A32_TYPELESS:
    case Format::R32G32B32_TYPELESS:
    case Format::R16G16B16A16_TYPELESS:
    case Format::R32G32_TYPELESS:
    case Format::R10G10B10A2_TYPELESS_PACK32:
    case Format::R8G8B8A8_TYPELESS:
    case Format::B8G8R8A8_TYPELESS:
    case Format::B8G8R8X8_TYPELESS:
    case Format::R16G16_TYPELESS:
    case Format::R32_TYPELESS:
    case Format::R8G8_TYPELESS:
    case Format::R16_TYPELESS:
    case Format::R8_TYPELESS:
    case Format::R32G8X24_TYPELESS_2PACK32:
    case Format::R24G8_TYPELESS_PACK32:
    case Format::BC1_TYPELESS_BLOCK:
    case Format::BC2_TYPELESS_BLOCK:
    case Format::BC3_TYPELESS_BLOCK:
    case Format::BC4_TYPELESS_BLOCK:
    case Format::BC5_TYPELESS_BLOCK:
    case Format::BC6H_TYPELESS_BLOCK:
    case Format::BC7_TYPELESS_BLOCK:
        return true;
    default:
        return false;
    }
}

Format makeTypeless(Format format) noexcept {
    switch(format) {
    case Format::R32G32B32A32_UINT:
    case Format::R32G32B32A32_SINT:
    case Format::R32G32B32A32_SFLOAT:
        return Format::R32G32B32A32_TYPELESS;

    case Format::R32G32B32_UINT:
    case Format::R32G32B32_SINT:
    case Format::R32G32B32_SFLOAT:
        return Format::R32G32B32_TYPELESS;

    case Format::R16G16B16A16_UNORM:
    case Format::R16G16B16A16_SNORM:
    case Format::R16G16B16A16_USCALED:
    case Format::R16G16B16A16_SSCALED:
    case Format::R16G16B16A16_UINT:
    case Format::R16G16B16A16_SINT:
    case Format::R16G16B16A16_SFLOAT:
        return Format::R16G16B16A16_TYPELESS;

    case Format::R32G32_UINT:
    case Format::R32G32_SINT:
    case Format::R32G32_SFLOAT:
        return Format::R32G32_TYPELESS;

    case Format::R10G10B10A2_UNORM_PACK32:
    case Format::R10G10B10A2_SNORM_PACK32:
    case Format::R10G10B10A2_USCALED_PACK32:
    case Format::R10G10B10A2_SSCALED_PACK32:
    case Format::R10G10B10A2_UINT_PACK32:
    case Format::R10G10B10A2_SINT_PACK32:
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32:
        return Format::R10G10B10A2_TYPELESS_PACK32;

    case Format::R8G8B8A8_UNORM:
    case Format::R8G8B8A8_SNORM:
    case Format::R8G8B8A8_USCALED:
    case Format::R8G8B8A8_SSCALED:
    case Format::R8G8B8A8_UINT:
    case Format::R8G8B8A8_SINT:
    case Format::R8G8B8A8_SRGB:
        return Format::R8G8B8A8_TYPELESS;

    case Format::B8G8R8A8_UNORM:
    case Format::B8G8R8A8_SNORM:
    case Format::B8G8R8A8_USCALED:
    case Format::B8G8R8A8_SSCALED:
    case Format::B8G8R8A8_UINT:
    case Format::B8G8R8A8_SINT:
    case Format::B8G8R8A8_SRGB:
        return Format::B8G8R8A8_TYPELESS;

    case Format::B8G8R8X8_UNORM:
    case Format::B8G8R8X8_SRGB:
        return Format::B8G8R8X8_TYPELESS;

    case Format::R16G16_UNORM:
    case Format::R16G16_SNORM:
    case Format::R16G16_USCALED:
    case Format::R16G16_SSCALED:
    case Format::R16G16_UINT:
    case Format::R16G16_SINT:
    case Format::R16G16_SFLOAT:
        return Format::R16G16_TYPELESS;

    case Format::R32_UINT:
    case Format::R32_SINT:
    case Format::R32_SFLOAT:
    case Format::D32_SFLOAT:
        return Format::R32_TYPELESS;

    case Format::R8G8_UNORM:
    case Format::R8G8_SNORM:
    case Format::R8G8_USCALED:
    case Format::R8G8_SSCALED:
    case Format::R8G8_UINT:
    case Format::R8G8_SINT:
    case Format::R8G8_SRGB:
        return Format::R8G8_TYPELESS;

    case Format::R16_UNORM:
    case Format::R16_SNORM:
    case Format::R16_USCALED:
    case Format::R16_SSCALED:
    case Format::R16_UINT:
    case Format::R16_SINT:
    case Format::R16_SFLOAT:
    case Format::D16_UNORM:
        return Format::R16_TYPELESS;

    case Format::R8_UNORM:
    case Format::R8_SNORM:
    case Format::R8_USCALED:
    case Format::R8_SSCALED:
    case Format::R8_UINT:
    case Format::R8_SINT:
    case Format::R8_SRGB:
        return Format::R8_TYPELESS;

    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32:
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32:
    case Format::D32_SFLOAT_S8_UINT:
        return Format::R32G8X24_TYPELESS_2PACK32;

    case Format::D24_UNORM_S8_UINT:
    case Format::R24_UNORM_X8_TYPELESS_PACK32:
    case Format::X24_TYPELESS_G8_UINT_PACK32:
    case Format::D24_UNORM_X8_TYPELESS_PACK32:
        return Format::R24G8_TYPELESS_PACK32;

    case Format::BC1_UNORM_BLOCK:
    case Format::BC1_SRGB_BLOCK:
        return Format::BC1_TYPELESS_BLOCK;

    case Format::BC2_UNORM_BLOCK:
    case Format::BC2_SRGB_BLOCK:
        return Format::BC2_TYPELESS_BLOCK;

    case Format::BC3_UNORM_BLOCK:
    case Format::BC3_SRGB_BLOCK:
        return Format::BC3_TYPELESS_BLOCK;

    case Format::BC4_UNORM_BLOCK:
    case Format::BC4_SNORM_BLOCK:
        return Format::BC4_TYPELESS_BLOCK;

    case Format::BC5_UNORM_BLOCK:
    case Format::BC5_SNORM_BLOCK:
        return Format::BC5_TYPELESS_BLOCK;

    case Format::BC6H_UFLOAT_BLOCK:
    case Format::BC6H_SFLOAT_BLOCK:
        return Format::BC6H_TYPELESS_BLOCK;

    case Format::BC7_UNORM_BLOCK:
    case Format::BC7_SRGB_BLOCK:
        return Format::BC7_TYPELESS_BLOCK;
    default:
        return format;
    }
}

Format makeTypelessUNorm(Format format) noexcept {
    switch(format) {
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_UNORM;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_UNORM_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_UNORM;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_UNORM;
    case Format::B8G8R8X8_TYPELESS: return Format::B8G8R8X8_UNORM;
    case Format::R16G16_TYPELESS: return Format::R16G16_UNORM;
    case Format::R8G8_TYPELESS: return Format::R8G8_UNORM;
    case Format::R16_TYPELESS: return Format::R16_UNORM;
    case Format::R8_TYPELESS: return Format::R8_UNORM;
    case Format::R24G8_TYPELESS_PACK32: return Format::D24_UNORM_S8_UINT;
    case Format::BC1_TYPELESS_BLOCK: return Format::BC1_UNORM_BLOCK;
    case Format::BC2_TYPELESS_BLOCK: return Format::BC2_UNORM_BLOCK;
    case Format::BC3_TYPELESS_BLOCK: return Format::BC3_UNORM_BLOCK;
    case Format::BC4_TYPELESS_BLOCK: return Format::BC4_UNORM_BLOCK;
    case Format::BC5_TYPELESS_BLOCK: return Format::BC5_UNORM_BLOCK;
    case Format::BC7_TYPELESS_BLOCK: return Format::BC7_UNORM_BLOCK;
    default: return format;
    }
}

Format makeTypelessSNorm(Format format) noexcept {
    switch(format) {
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_SNORM;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_SNORM_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_SNORM;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_SNORM;
    case Format::R16G16_TYPELESS: return Format::R16G16_SNORM;
    case Format::R8G8_TYPELESS: return Format::R8G8_SNORM;
    case Format::R16_TYPELESS: return Format::R16_SNORM;
    case Format::R8_TYPELESS: return Format::R8_SNORM;
    case Format::BC4_TYPELESS_BLOCK: return Format::BC4_SNORM_BLOCK;
    case Format::BC5_TYPELESS_BLOCK: return Format::BC5_SNORM_BLOCK;
    default: return format;
    }
}

Format makeTypelessUScaled(Format format) noexcept {
    switch(format) {
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_USCALED;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_USCALED_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_USCALED;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_USCALED;
    case Format::R16G16_TYPELESS: return Format::R16G16_USCALED;
    case Format::R8G8_TYPELESS: return Format::R8G8_USCALED;
    case Format::R16_TYPELESS: return Format::R16_USCALED;
    case Format::R8_TYPELESS: return Format::R8_USCALED;
    default: return format;
    }
}

Format makeTypelessSScaled(Format format) noexcept {
    switch(format) {
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_SSCALED;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_SSCALED_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_SSCALED;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_SSCALED;
    case Format::R16G16_TYPELESS: return Format::R16G16_SSCALED;
    case Format::R8G8_TYPELESS: return Format::R8G8_SSCALED;
    case Format::R16_TYPELESS: return Format::R16_SSCALED;
    case Format::R8_TYPELESS: return Format::R8_SSCALED;
    default: return format;
    }
}

Format makeTypelessUInt(Format format) noexcept {
    switch(format) {
    case Format::R32G32B32A32_TYPELESS: return Format::R32G32B32A32_UINT;
    case Format::R32G32B32_TYPELESS: return Format::R32G32B32_UINT;
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_UINT;
    case Format::R32G32_TYPELESS: return Format::R32G32_UINT;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_UINT_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_UINT;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_UINT;
    case Format::R16G16_TYPELESS: return Format::R16G16_UINT;
    case Format::R32_TYPELESS: return Format::R32_UINT;
    case Format::R8G8_TYPELESS: return Format::R8G8_UINT;
    case Format::R16_TYPELESS: return Format::R16_UINT;
    case Format::R8_TYPELESS: return Format::R8_UINT;
    default: return format;
    }
}

Format makeTypelessSInt(Format format) noexcept {
    switch(format) {
    case Format::R32G32B32A32_TYPELESS: return Format::R32G32B32A32_SINT;
    case Format::R32G32B32_TYPELESS: return Format::R32G32B32_SINT;
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_SINT;
    case Format::R32G32_TYPELESS: return Format::R32G32_SINT;
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10A2_SINT_PACK32;
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_SINT;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_SINT;
    case Format::R16G16_TYPELESS: return Format::R16G16_SINT;
    case Format::R32_TYPELESS: return Format::R32_SINT;
    case Format::R8G8_TYPELESS: return Format::R8G8_SINT;
    case Format::R16_TYPELESS: return Format::R16_SINT;
    case Format::R8_TYPELESS: return Format::R8_SINT;
    default: return format;
    }
}

Format makeTypelessSRGB(Format format) noexcept {
    switch(format) {
    case Format::R8G8B8A8_TYPELESS: return Format::R8G8B8A8_SRGB;
    case Format::B8G8R8A8_TYPELESS: return Format::B8G8R8A8_SRGB;
    case Format::B8G8R8X8_TYPELESS: return Format::B8G8R8X8_SRGB;
    case Format::R8G8_TYPELESS: return Format::R8G8_SRGB;
    case Format::R8_TYPELESS: return Format::R8_SRGB;
    case Format::BC1_TYPELESS_BLOCK: return Format::BC1_SRGB_BLOCK;
    case Format::BC2_TYPELESS_BLOCK: return Format::BC2_SRGB_BLOCK;
    case Format::BC3_TYPELESS_BLOCK: return Format::BC3_SRGB_BLOCK;
    case Format::BC7_TYPELESS_BLOCK: return Format::BC7_SRGB_BLOCK;
    default: return format;
    }
}

Format makeTypelessXRBias(Format format) noexcept {
    switch(format) {
    case Format::R10G10B10A2_TYPELESS_PACK32: return Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32;
    default: return format;
    }
}

Format makeTypelessUFloat(Format format) noexcept {
    switch(format) {
    case Format::BC6H_TYPELESS_BLOCK: return Format::BC6H_UFLOAT_BLOCK;
    default: return format;
    }
}

Format makeTypelessSFloat(Format format) noexcept {
    switch(format) {
    case Format::R32G32B32A32_TYPELESS: return Format::R32G32B32A32_SFLOAT;
    case Format::R32G32B32_TYPELESS: return Format::R32G32B32_SFLOAT;
    case Format::R16G16B16A16_TYPELESS: return Format::R16G16B16A16_SFLOAT;
    case Format::R32G32_TYPELESS: return Format::R32G32_SFLOAT;
    case Format::R16G16_TYPELESS: return Format::R16G16_SFLOAT;
    case Format::R32_TYPELESS: return Format::R32_SFLOAT;
    case Format::R16_TYPELESS: return Format::R16_SFLOAT;
    case Format::R32G8X24_TYPELESS_2PACK32: return Format::D32_SFLOAT_S8_UINT;
    case Format::BC6H_TYPELESS_BLOCK: return Format::BC6H_SFLOAT_BLOCK;
    default: return format;
    }
}

Format makeTypelessDouble(Format format) noexcept {
    switch(format) {
    case Format::UNKNOWN:
    default: return format;
    }
}

Format makeTypelessDepthStencil(Format format) noexcept {
    switch(format) {
    case Format::R32_TYPELESS: return Format::D32_SFLOAT;
    case Format::R16_TYPELESS: return Format::D16_UNORM;
    case Format::R8_TYPELESS: return Format::S8_UINT;
    case Format::R32G8X24_TYPELESS_2PACK32: return Format::D32_SFLOAT_S8_UINT;
    case Format::R24G8_TYPELESS_PACK32: return Format::D24_UNORM_S8_UINT;
    default: return format;
    }
}

Format makeTypelessDepthOnly(Format format) noexcept {
    switch(format) {
    case Format::R32_TYPELESS: return Format::D32_SFLOAT;
    case Format::R16_TYPELESS: return Format::D16_UNORM;
    case Format::R32G8X24_TYPELESS_2PACK32: return Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32;
    case Format::R24G8_TYPELESS_PACK32: return Format::R24_UNORM_X8_TYPELESS_PACK32;
    default: return format;
    }
}

Format makeTypelessStencilOnly(Format format) noexcept {
    switch(format) {
    case Format::R8_TYPELESS: return Format::S8_UINT;
    case Format::R32G8X24_TYPELESS_2PACK32: return Format::X32_TYPELESS_G8X24_UINT_2PACK32;
    case Format::R24G8_TYPELESS_PACK32: return Format::X24_TYPELESS_G8_UINT_PACK32;
    default: return format;
    }
}

bool supportSRGB(Format format) noexcept {
    switch(format) {
    case Format::R8G8B8A8_TYPELESS:
    case Format::R8G8B8A8_UNORM:
    case Format::R8G8B8A8_UNORM_PACK32:
    case Format::R8G8B8A8_SNORM:
    case Format::R8G8B8A8_SNORM_PACK32:
    case Format::R8G8B8A8_USCALED:
    case Format::R8G8B8A8_USCALED_PACK32:
    case Format::R8G8B8A8_SSCALED:
    case Format::R8G8B8A8_SSCALED_PACK32:
    case Format::R8G8B8A8_UINT:
    case Format::R8G8B8A8_UINT_PACK32:
    case Format::R8G8B8A8_SINT:
    case Format::R8G8B8A8_SINT_PACK32:
    case Format::R8G8B8A8_SRGB:
    case Format::R8G8B8A8_SRGB_PACK32:
    case Format::B8G8R8A8_TYPELESS:
    case Format::B8G8R8A8_UNORM:
    case Format::B8G8R8A8_SNORM:
    case Format::B8G8R8A8_USCALED:
    case Format::B8G8R8A8_SSCALED:
    case Format::B8G8R8A8_UINT:
    case Format::B8G8R8A8_SINT:
    case Format::B8G8R8A8_SRGB:
    case Format::B8G8R8X8_TYPELESS:
    case Format::B8G8R8X8_UNORM:
    case Format::B8G8R8X8_SRGB:
    case Format::R8G8B8_UNORM:
    case Format::R8G8B8_SNORM:
    case Format::R8G8B8_USCALED:
    case Format::R8G8B8_SSCALED:
    case Format::R8G8B8_UINT:
    case Format::R8G8B8_SINT:
    case Format::R8G8B8_SRGB:
    case Format::B8G8R8_UNORM:
    case Format::B8G8R8_SNORM:
    case Format::B8G8R8_USCALED:
    case Format::B8G8R8_SSCALED:
    case Format::B8G8R8_UINT:
    case Format::B8G8R8_SINT:
    case Format::B8G8R8_SRGB:
    case Format::R8G8_TYPELESS:
    case Format::R8G8_UNORM:
    case Format::R8G8_SNORM:
    case Format::R8G8_USCALED:
    case Format::R8G8_SSCALED:
    case Format::R8G8_UINT:
    case Format::R8G8_SINT:
    case Format::R8G8_SRGB:
    case Format::R8_TYPELESS:
    case Format::R8_UNORM:
    case Format::R8_SNORM:
    case Format::R8_USCALED:
    case Format::R8_SSCALED:
    case Format::R8_UINT:
    case Format::R8_SINT:
    case Format::R8_SRGB:
    case Format::BC1_RGBA_UNORM_BLOCK:
    case Format::BC1_RGBA_SRGB_BLOCK:
    case Format::BC1_TYPELESS_BLOCK:
    case Format::BC1_UNORM_BLOCK:
    case Format::BC1_SRGB_BLOCK:
    case Format::BC2_TYPELESS_BLOCK:
    case Format::BC2_UNORM_BLOCK:
    case Format::BC2_SRGB_BLOCK:
    case Format::BC3_TYPELESS_BLOCK:
    case Format::BC3_UNORM_BLOCK:
    case Format::BC3_SRGB_BLOCK:
    case Format::BC7_TYPELESS_BLOCK:
    case Format::BC7_UNORM_BLOCK:
    case Format::BC7_SRGB_BLOCK:
    case Format::ETC2_R8G8B8A8_UNORM_BLOCK:
    case Format::ETC2_R8G8B8A8_SRGB_BLOCK:
    case Format::ETC2_R8G8B8A1_UNORM_BLOCK:
    case Format::ETC2_R8G8B8A1_SRGB_BLOCK:
    case Format::ETC2_R8G8B8_UNORM_BLOCK:
    case Format::ETC2_R8G8B8_SRGB_BLOCK:
    case Format::ASTC_4x4_UNORM_BLOCK:
    case Format::ASTC_4x4_SRGB_BLOCK:
    case Format::ASTC_5x4_UNORM_BLOCK:
    case Format::ASTC_5x4_SRGB_BLOCK:
    case Format::ASTC_5x5_UNORM_BLOCK:
    case Format::ASTC_5x5_SRGB_BLOCK:
    case Format::ASTC_6x5_UNORM_BLOCK:
    case Format::ASTC_6x5_SRGB_BLOCK:
    case Format::ASTC_6x6_UNORM_BLOCK:
    case Format::ASTC_6x6_SRGB_BLOCK:
    case Format::ASTC_8x5_UNORM_BLOCK:
    case Format::ASTC_8x5_SRGB_BLOCK:
    case Format::ASTC_8x6_UNORM_BLOCK:
    case Format::ASTC_8x6_SRGB_BLOCK:
    case Format::ASTC_8x8_UNORM_BLOCK:
    case Format::ASTC_8x8_SRGB_BLOCK:
    case Format::ASTC_10x5_UNORM_BLOCK:
    case Format::ASTC_10x5_SRGB_BLOCK:
    case Format::ASTC_10x6_UNORM_BLOCK:
    case Format::ASTC_10x6_SRGB_BLOCK:
    case Format::ASTC_10x8_UNORM_BLOCK:
    case Format::ASTC_10x8_SRGB_BLOCK:
    case Format::ASTC_10x10_UNORM_BLOCK:
    case Format::ASTC_10x10_SRGB_BLOCK:
    case Format::ASTC_12x10_UNORM_BLOCK:
    case Format::ASTC_12x10_SRGB_BLOCK:
    case Format::ASTC_12x12_UNORM_BLOCK:
    case Format::ASTC_12x12_SRGB_BLOCK:
    case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG:
    case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG:
    case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG:
    case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG:
    case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG:
        return true;
    default:
        return false;
    }
}

bool isSRGB(Format format) noexcept {
    switch(format) {
    case Format::R8G8B8A8_SRGB:
    case Format::R8G8B8A8_SRGB_PACK32:
    case Format::B8G8R8A8_SRGB:
    case Format::B8G8R8X8_SRGB:
    case Format::R8G8B8_SRGB:
    case Format::B8G8R8_SRGB:
    case Format::R8G8_SRGB:
    case Format::R8_SRGB:
    case Format::BC1_RGBA_SRGB_BLOCK:
    case Format::BC1_SRGB_BLOCK:
    case Format::BC2_SRGB_BLOCK:
    case Format::BC3_SRGB_BLOCK:
    case Format::BC7_SRGB_BLOCK:
    case Format::ETC2_R8G8B8A8_SRGB_BLOCK:
    case Format::ETC2_R8G8B8A1_SRGB_BLOCK:
    case Format::ETC2_R8G8B8_SRGB_BLOCK:
    case Format::ASTC_4x4_SRGB_BLOCK:
    case Format::ASTC_5x4_SRGB_BLOCK:
    case Format::ASTC_5x5_SRGB_BLOCK:
    case Format::ASTC_6x5_SRGB_BLOCK:
    case Format::ASTC_6x6_SRGB_BLOCK:
    case Format::ASTC_8x5_SRGB_BLOCK:
    case Format::ASTC_8x6_SRGB_BLOCK:
    case Format::ASTC_8x8_SRGB_BLOCK:
    case Format::ASTC_10x5_SRGB_BLOCK:
    case Format::ASTC_10x6_SRGB_BLOCK:
    case Format::ASTC_10x8_SRGB_BLOCK:
    case Format::ASTC_10x10_SRGB_BLOCK:
    case Format::ASTC_12x10_SRGB_BLOCK:
    case Format::ASTC_12x12_SRGB_BLOCK:
    case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG:
    case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG:
        return true;
    default:
        return false;
    }
}

Format makeUNormSRGB(Format format) noexcept {
    switch(format) {
    case Format::R8G8B8A8_UNORM: return Format::R8G8B8A8_SRGB;
    case Format::R8G8B8A8_UNORM_PACK32: return Format::R8G8B8A8_SRGB_PACK32;
    case Format::B8G8R8A8_UNORM: return Format::B8G8R8A8_SRGB;
    case Format::B8G8R8X8_UNORM: return Format::B8G8R8X8_SRGB;
    case Format::R8G8B8_UNORM: return Format::R8G8B8_SRGB;
    case Format::B8G8R8_UNORM: return Format::B8G8R8_SRGB;
    case Format::R8G8_UNORM: return Format::R8G8_SRGB;
    case Format::R8_UNORM: return Format::R8_SRGB;
    case Format::BC1_RGBA_UNORM_BLOCK: return Format::BC1_RGBA_SRGB_BLOCK;
    case Format::BC1_UNORM_BLOCK: return Format::BC1_SRGB_BLOCK;
    case Format::BC2_UNORM_BLOCK: return Format::BC2_SRGB_BLOCK;
    case Format::BC3_UNORM_BLOCK: return Format::BC3_SRGB_BLOCK;
    case Format::BC7_UNORM_BLOCK: return Format::BC7_SRGB_BLOCK;
    case Format::ETC2_R8G8B8A8_UNORM_BLOCK: return Format::ETC2_R8G8B8A8_SRGB_BLOCK;
    case Format::ETC2_R8G8B8A1_UNORM_BLOCK: return Format::ETC2_R8G8B8A1_SRGB_BLOCK;
    case Format::ETC2_R8G8B8_UNORM_BLOCK: return Format::ETC2_R8G8B8_SRGB_BLOCK;
    case Format::ASTC_4x4_UNORM_BLOCK: return Format::ASTC_4x4_SRGB_BLOCK;
    case Format::ASTC_5x4_UNORM_BLOCK: return Format::ASTC_5x4_SRGB_BLOCK;
    case Format::ASTC_5x5_UNORM_BLOCK: return Format::ASTC_5x5_SRGB_BLOCK;
    case Format::ASTC_6x5_UNORM_BLOCK: return Format::ASTC_6x5_SRGB_BLOCK;
    case Format::ASTC_6x6_UNORM_BLOCK: return Format::ASTC_6x6_SRGB_BLOCK;
    case Format::ASTC_8x5_UNORM_BLOCK: return Format::ASTC_8x5_SRGB_BLOCK;
    case Format::ASTC_8x6_UNORM_BLOCK: return Format::ASTC_8x6_SRGB_BLOCK;
    case Format::ASTC_8x8_UNORM_BLOCK: return Format::ASTC_8x8_SRGB_BLOCK;
    case Format::ASTC_10x5_UNORM_BLOCK: return Format::ASTC_10x5_SRGB_BLOCK;
    case Format::ASTC_10x6_UNORM_BLOCK: return Format::ASTC_10x6_SRGB_BLOCK;
    case Format::ASTC_10x8_UNORM_BLOCK: return Format::ASTC_10x8_SRGB_BLOCK;
    case Format::ASTC_10x10_UNORM_BLOCK: return Format::ASTC_10x10_SRGB_BLOCK;
    case Format::ASTC_12x10_UNORM_BLOCK: return Format::ASTC_12x10_SRGB_BLOCK;
    case Format::ASTC_12x12_UNORM_BLOCK: return Format::ASTC_12x12_SRGB_BLOCK;
    case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG: return Format::PVRTC1_4BPP_SRGB_BLOCK_IMG;
    case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG: return Format::PVRTC1_2BPP_SRGB_BLOCK_IMG;
    case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG: return Format::PVRTC2_4BPP_SRGB_BLOCK_IMG;
    case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG: return Format::PVRTC2_2BPP_SRGB_BLOCK_IMG;
    default: return format;
    }
}

}
