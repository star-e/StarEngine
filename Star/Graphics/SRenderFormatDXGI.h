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
#include <dxgiformat.h>
#include <Star/Graphics/SRenderFormat.h>

namespace Star::Graphics::Render {

inline bool isDXGIFormat(Format format) noexcept {
    switch(format) {
    case Format::UNKNOWN:
    case Format::R32G32B32A32_TYPELESS:
    case Format::R32G32B32A32_UINT:
    case Format::R32G32B32A32_SINT:
    case Format::R32G32B32A32_SFLOAT:
    case Format::R32G32B32_TYPELESS:
    case Format::R32G32B32_UINT:
    case Format::R32G32B32_SINT:
    case Format::R32G32B32_SFLOAT:
    case Format::R16G16B16A16_TYPELESS:
    case Format::R16G16B16A16_UNORM:
    case Format::R16G16B16A16_SNORM:
    case Format::R16G16B16A16_UINT:
    case Format::R16G16B16A16_SINT:
    case Format::R16G16B16A16_SFLOAT:
    case Format::R32G32_TYPELESS:
    case Format::R32G32_UINT:
    case Format::R32G32_SINT:
    case Format::R32G32_SFLOAT:
    case Format::R10G10B10A2_TYPELESS_PACK32:
    case Format::R10G10B10A2_UNORM_PACK32:
    case Format::R10G10B10A2_UINT_PACK32:
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32:
    case Format::R9G9B9E5_UFLOAT_PACK32:
    case Format::R8G8B8A8_TYPELESS:
    case Format::R8G8B8A8_UNORM:
    case Format::R8G8B8A8_SNORM:
    case Format::R8G8B8A8_UINT:
    case Format::R8G8B8A8_SINT:
    case Format::R8G8B8A8_SRGB:
    case Format::B8G8R8A8_TYPELESS:
    case Format::B8G8R8A8_UNORM:
    case Format::B8G8R8A8_SRGB:
    case Format::R11G11B10_UFLOAT_PACK32:
    case Format::B8G8R8X8_TYPELESS:
    case Format::B8G8R8X8_UNORM:
    case Format::B8G8R8X8_SRGB:
    case Format::R16G16_TYPELESS:
    case Format::R16G16_UNORM:
    case Format::R16G16_SNORM:
    case Format::R16G16_UINT:
    case Format::R16G16_SINT:
    case Format::R16G16_SFLOAT:
    case Format::R32_TYPELESS:
    case Format::R32_UINT:
    case Format::R32_SINT:
    case Format::R32_SFLOAT:
    case Format::B5G5R5A1_UNORM_PACK16:
    case Format::B5G6R5_UNORM_PACK16:
    case Format::R8G8_TYPELESS:
    case Format::R8G8_UNORM:
    case Format::R8G8_SNORM:
    case Format::R8G8_UINT:
    case Format::R8G8_SINT:
    case Format::R16_TYPELESS:
    case Format::R16_UNORM:
    case Format::R16_SNORM:
    case Format::R16_UINT:
    case Format::R16_SINT:
    case Format::R16_SFLOAT:
    case Format::R8_TYPELESS:
    case Format::R8_UNORM:
    case Format::R8_SNORM:
    case Format::R8_UINT:
    case Format::R8_SINT:
    case Format::A8_UNORM:
    case Format::R1_UNORM:
    case Format::R32G8X24_TYPELESS_2PACK32:
    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32:
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32:
    case Format::D32_SFLOAT_S8_UINT:
    case Format::R24G8_TYPELESS_PACK32:
    case Format::D24_UNORM_S8_UINT:
    case Format::R24_UNORM_X8_TYPELESS_PACK32:
    case Format::X24_TYPELESS_G8_UINT_PACK32:
    case Format::D32_SFLOAT:
    case Format::D16_UNORM:
    case Format::BC1_TYPELESS_BLOCK:
    case Format::BC1_UNORM_BLOCK:
    case Format::BC1_SRGB_BLOCK:
    case Format::BC2_TYPELESS_BLOCK:
    case Format::BC2_UNORM_BLOCK:
    case Format::BC2_SRGB_BLOCK:
    case Format::BC3_TYPELESS_BLOCK:
    case Format::BC3_UNORM_BLOCK:
    case Format::BC3_SRGB_BLOCK:
    case Format::BC4_TYPELESS_BLOCK:
    case Format::BC4_UNORM_BLOCK:
    case Format::BC4_SNORM_BLOCK:
    case Format::BC5_TYPELESS_BLOCK:
    case Format::BC5_UNORM_BLOCK:
    case Format::BC5_SNORM_BLOCK:
    case Format::BC6H_TYPELESS_BLOCK:
    case Format::BC6H_UFLOAT_BLOCK:
    case Format::BC6H_SFLOAT_BLOCK:
    case Format::BC7_TYPELESS_BLOCK:
    case Format::BC7_UNORM_BLOCK:
    case Format::BC7_SRGB_BLOCK:
    case Format::R8G8_B8G8_UNORM:
    case Format::G8R8_G8B8_UNORM:
        return true;
    default:
        return false;
    }
}

inline DXGI_FORMAT getDXGIFormat(Format format) noexcept {
    switch(format) {
    case Format::UNKNOWN: return DXGI_FORMAT_UNKNOWN;
    case Format::R32G32B32A32_TYPELESS: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
    case Format::R32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
    case Format::R32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
    case Format::R32G32B32A32_SFLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case Format::R32G32B32_TYPELESS: return DXGI_FORMAT_R32G32B32_TYPELESS;
    case Format::R32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
    case Format::R32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
    case Format::R32G32B32_SFLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
    case Format::R16G16B16A16_TYPELESS: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
    case Format::R16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
    case Format::R16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
    case Format::R16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
    case Format::R16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
    case Format::R16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case Format::R32G32_TYPELESS: return DXGI_FORMAT_R32G32_TYPELESS;
    case Format::R32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
    case Format::R32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
    case Format::R32G32_SFLOAT: return DXGI_FORMAT_R32G32_FLOAT;
    case Format::R10G10B10A2_TYPELESS_PACK32: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
    case Format::R10G10B10A2_UNORM_PACK32: return DXGI_FORMAT_R10G10B10A2_UNORM;
    case Format::R10G10B10A2_UINT_PACK32: return DXGI_FORMAT_R10G10B10A2_UINT;
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32: return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
    case Format::R9G9B9E5_UFLOAT_PACK32: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
    case Format::R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
    case Format::R8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
    case Format::R8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
    case Format::R8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
    case Format::R8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
    case Format::R8G8B8A8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    case Format::B8G8R8A8_TYPELESS: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
    case Format::B8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
    case Format::B8G8R8A8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    case Format::R11G11B10_UFLOAT_PACK32: return DXGI_FORMAT_R11G11B10_FLOAT;
    case Format::B8G8R8X8_TYPELESS: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
    case Format::B8G8R8X8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
    case Format::B8G8R8X8_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
    case Format::R16G16_TYPELESS: return DXGI_FORMAT_R16G16_TYPELESS;
    case Format::R16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
    case Format::R16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
    case Format::R16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
    case Format::R16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
    case Format::R16G16_SFLOAT: return DXGI_FORMAT_R16G16_FLOAT;
    case Format::R32_TYPELESS: return DXGI_FORMAT_R32_TYPELESS;
    case Format::R32_UINT: return DXGI_FORMAT_R32_UINT;
    case Format::R32_SINT: return DXGI_FORMAT_R32_SINT;
    case Format::R32_SFLOAT: return DXGI_FORMAT_R32_FLOAT;
    case Format::B5G5R5A1_UNORM_PACK16: return DXGI_FORMAT_B5G5R5A1_UNORM;
    case Format::B5G6R5_UNORM_PACK16: return DXGI_FORMAT_B5G6R5_UNORM;
    case Format::R8G8_TYPELESS: return DXGI_FORMAT_R8G8_TYPELESS;
    case Format::R8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
    case Format::R8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
    case Format::R8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
    case Format::R8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
    case Format::R16_TYPELESS: return DXGI_FORMAT_R16_TYPELESS;
    case Format::R16_UNORM: return DXGI_FORMAT_R16_UNORM;
    case Format::R16_SNORM: return DXGI_FORMAT_R16_SNORM;
    case Format::R16_UINT: return DXGI_FORMAT_R16_UINT;
    case Format::R16_SINT: return DXGI_FORMAT_R16_SINT;
    case Format::R16_SFLOAT: return DXGI_FORMAT_R16_FLOAT;
    case Format::R8_TYPELESS: return DXGI_FORMAT_R8_TYPELESS;
    case Format::R8_UNORM: return DXGI_FORMAT_R8_UNORM;
    case Format::R8_SNORM: return DXGI_FORMAT_R8_SNORM;
    case Format::R8_UINT: return DXGI_FORMAT_R8_UINT;
    case Format::R8_SINT: return DXGI_FORMAT_R8_SINT;
    case Format::A8_UNORM: return DXGI_FORMAT_A8_UNORM;
    case Format::R1_UNORM: return DXGI_FORMAT_R1_UNORM;
    case Format::R32G8X24_TYPELESS_2PACK32: return DXGI_FORMAT_R32G8X24_TYPELESS;
    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32: return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
    case Format::D32_SFLOAT_S8_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    case Format::R24G8_TYPELESS_PACK32: return DXGI_FORMAT_R24G8_TYPELESS;
    case Format::D24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case Format::R24_UNORM_X8_TYPELESS_PACK32: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    case Format::X24_TYPELESS_G8_UINT_PACK32: return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
    case Format::D32_SFLOAT: return DXGI_FORMAT_D32_FLOAT;
    case Format::D16_UNORM: return DXGI_FORMAT_D16_UNORM;
    case Format::BC1_TYPELESS_BLOCK: return DXGI_FORMAT_BC1_TYPELESS;
    case Format::BC1_UNORM_BLOCK: return DXGI_FORMAT_BC1_UNORM;
    case Format::BC1_SRGB_BLOCK: return DXGI_FORMAT_BC1_UNORM_SRGB;
    case Format::BC2_TYPELESS_BLOCK: return DXGI_FORMAT_BC2_TYPELESS;
    case Format::BC2_UNORM_BLOCK: return DXGI_FORMAT_BC2_UNORM;
    case Format::BC2_SRGB_BLOCK: return DXGI_FORMAT_BC2_UNORM_SRGB;
    case Format::BC3_TYPELESS_BLOCK: return DXGI_FORMAT_BC3_TYPELESS;
    case Format::BC3_UNORM_BLOCK: return DXGI_FORMAT_BC3_UNORM;
    case Format::BC3_SRGB_BLOCK: return DXGI_FORMAT_BC3_UNORM_SRGB;
    case Format::BC4_TYPELESS_BLOCK: return DXGI_FORMAT_BC4_TYPELESS;
    case Format::BC4_UNORM_BLOCK: return DXGI_FORMAT_BC4_UNORM;
    case Format::BC4_SNORM_BLOCK: return DXGI_FORMAT_BC4_SNORM;
    case Format::BC5_TYPELESS_BLOCK: return DXGI_FORMAT_BC5_TYPELESS;
    case Format::BC5_UNORM_BLOCK: return DXGI_FORMAT_BC5_UNORM;
    case Format::BC5_SNORM_BLOCK: return DXGI_FORMAT_BC5_SNORM;
    case Format::BC6H_TYPELESS_BLOCK: return DXGI_FORMAT_BC6H_TYPELESS;
    case Format::BC6H_UFLOAT_BLOCK: return DXGI_FORMAT_BC6H_UF16;
    case Format::BC6H_SFLOAT_BLOCK: return DXGI_FORMAT_BC6H_SF16;
    case Format::BC7_TYPELESS_BLOCK: return DXGI_FORMAT_BC7_TYPELESS;
    case Format::BC7_UNORM_BLOCK: return DXGI_FORMAT_BC7_UNORM;
    case Format::BC7_SRGB_BLOCK: return DXGI_FORMAT_BC7_UNORM_SRGB;
    case Format::R8G8_B8G8_UNORM: return DXGI_FORMAT_R8G8_B8G8_UNORM;
    case Format::G8R8_G8B8_UNORM: return DXGI_FORMAT_G8R8_G8B8_UNORM;
    default: return DXGI_FORMAT_UNKNOWN;
    }
}

inline Format getRenderFormat(DXGI_FORMAT format) noexcept {
    switch(format) {
    case DXGI_FORMAT_UNKNOWN: return Format::UNKNOWN;
    case DXGI_FORMAT_R32G32B32A32_TYPELESS: return Format::R32G32B32A32_TYPELESS;
    case DXGI_FORMAT_R32G32B32A32_FLOAT: return Format::R32G32B32A32_SFLOAT;
    case DXGI_FORMAT_R32G32B32A32_UINT: return Format::R32G32B32A32_UINT;
    case DXGI_FORMAT_R32G32B32A32_SINT: return Format::R32G32B32A32_SINT;
    case DXGI_FORMAT_R32G32B32_TYPELESS: return Format::R32G32B32_TYPELESS;
    case DXGI_FORMAT_R32G32B32_FLOAT: return Format::R32G32B32_SFLOAT;
    case DXGI_FORMAT_R32G32B32_UINT: return Format::R32G32B32_UINT;
    case DXGI_FORMAT_R32G32B32_SINT: return Format::R32G32B32_SINT;
    case DXGI_FORMAT_R16G16B16A16_TYPELESS: return Format::R16G16B16A16_TYPELESS;
    case DXGI_FORMAT_R16G16B16A16_FLOAT: return Format::R16G16B16A16_SFLOAT;
    case DXGI_FORMAT_R16G16B16A16_UNORM: return Format::R16G16B16A16_UNORM;
    case DXGI_FORMAT_R16G16B16A16_UINT: return Format::R16G16B16A16_UINT;
    case DXGI_FORMAT_R16G16B16A16_SNORM: return Format::R16G16B16A16_SNORM;
    case DXGI_FORMAT_R16G16B16A16_SINT: return Format::R16G16B16A16_SINT;
    case DXGI_FORMAT_R32G32_TYPELESS: return Format::R32G32_TYPELESS;
    case DXGI_FORMAT_R32G32_FLOAT: return Format::R32G32_SFLOAT;
    case DXGI_FORMAT_R32G32_UINT: return Format::R32G32_UINT;
    case DXGI_FORMAT_R32G32_SINT: return Format::R32G32_SINT;
    case DXGI_FORMAT_R32G8X24_TYPELESS: return Format::R32G8X24_TYPELESS_2PACK32;
    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: return Format::D32_SFLOAT_S8_UINT;
    case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS: return Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32;
    case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT: return Format::X32_TYPELESS_G8X24_UINT_2PACK32;
    case DXGI_FORMAT_R10G10B10A2_TYPELESS: return Format::R10G10B10A2_TYPELESS_PACK32;
    case DXGI_FORMAT_R10G10B10A2_UNORM: return Format::R10G10B10A2_UNORM_PACK32;
    case DXGI_FORMAT_R10G10B10A2_UINT: return Format::R10G10B10A2_UINT_PACK32;
    case DXGI_FORMAT_R11G11B10_FLOAT: return Format::R11G11B10_UFLOAT_PACK32;
    case DXGI_FORMAT_R8G8B8A8_TYPELESS: return Format::R8G8B8A8_TYPELESS;
    case DXGI_FORMAT_R8G8B8A8_UNORM: return Format::R8G8B8A8_UNORM;
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return Format::R8G8B8A8_SRGB;
    case DXGI_FORMAT_R8G8B8A8_UINT: return Format::R8G8B8A8_UINT;
    case DXGI_FORMAT_R8G8B8A8_SNORM: return Format::R8G8B8A8_SNORM;
    case DXGI_FORMAT_R8G8B8A8_SINT: return Format::R8G8B8A8_SINT;
    case DXGI_FORMAT_R16G16_TYPELESS: return Format::R16G16_TYPELESS;
    case DXGI_FORMAT_R16G16_FLOAT: return Format::R16G16_SFLOAT;
    case DXGI_FORMAT_R16G16_UNORM: return Format::R16G16_UNORM;
    case DXGI_FORMAT_R16G16_UINT: return Format::R16G16_UINT;
    case DXGI_FORMAT_R16G16_SNORM: return Format::R16G16_SNORM;
    case DXGI_FORMAT_R16G16_SINT: return Format::R16G16_SINT;
    case DXGI_FORMAT_R32_TYPELESS: return Format::R32_TYPELESS;
    case DXGI_FORMAT_D32_FLOAT: return Format::D32_SFLOAT;
    case DXGI_FORMAT_R32_FLOAT: return Format::R32_SFLOAT;
    case DXGI_FORMAT_R32_UINT: return Format::R32_UINT;
    case DXGI_FORMAT_R32_SINT: return Format::R32_SINT;
    case DXGI_FORMAT_R24G8_TYPELESS: return Format::R24G8_TYPELESS_PACK32;
    case DXGI_FORMAT_D24_UNORM_S8_UINT: return Format::D24_UNORM_S8_UINT;
    case DXGI_FORMAT_R24_UNORM_X8_TYPELESS: return Format::R24_UNORM_X8_TYPELESS_PACK32;
    case DXGI_FORMAT_X24_TYPELESS_G8_UINT: return Format::X24_TYPELESS_G8_UINT_PACK32;
    case DXGI_FORMAT_R8G8_TYPELESS: return Format::R8G8_TYPELESS;
    case DXGI_FORMAT_R8G8_UNORM: return Format::R8G8_UNORM;
    case DXGI_FORMAT_R8G8_UINT: return Format::R8G8_UINT;
    case DXGI_FORMAT_R8G8_SNORM: return Format::R8G8_SNORM;
    case DXGI_FORMAT_R8G8_SINT: return Format::R8G8_SINT;
    case DXGI_FORMAT_R16_TYPELESS: return Format::R16_TYPELESS;
    case DXGI_FORMAT_R16_FLOAT: return Format::R16_SFLOAT;
    case DXGI_FORMAT_D16_UNORM: return Format::D16_UNORM;
    case DXGI_FORMAT_R16_UNORM: return Format::R16_UNORM;
    case DXGI_FORMAT_R16_UINT: return Format::R16_UINT;
    case DXGI_FORMAT_R16_SNORM: return Format::R16_SNORM;
    case DXGI_FORMAT_R16_SINT: return Format::R16_SINT;
    case DXGI_FORMAT_R8_TYPELESS: return Format::R8_TYPELESS;
    case DXGI_FORMAT_R8_UNORM: return Format::R8_UNORM;
    case DXGI_FORMAT_R8_UINT: return Format::R8_UINT;
    case DXGI_FORMAT_R8_SNORM: return Format::R8_SNORM;
    case DXGI_FORMAT_R8_SINT: return Format::R8_SINT;
    case DXGI_FORMAT_A8_UNORM: return Format::A8_UNORM;
    case DXGI_FORMAT_R1_UNORM: return Format::R1_UNORM;
    case DXGI_FORMAT_R9G9B9E5_SHAREDEXP: return Format::R9G9B9E5_UFLOAT_PACK32;
    case DXGI_FORMAT_R8G8_B8G8_UNORM: return Format::R8G8_B8G8_UNORM;
    case DXGI_FORMAT_G8R8_G8B8_UNORM: return Format::G8R8_G8B8_UNORM;
    case DXGI_FORMAT_BC1_TYPELESS: return Format::BC1_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC1_UNORM: return Format::BC1_UNORM_BLOCK;
    case DXGI_FORMAT_BC1_UNORM_SRGB: return Format::BC1_SRGB_BLOCK;
    case DXGI_FORMAT_BC2_TYPELESS: return Format::BC2_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC2_UNORM: return Format::BC2_UNORM_BLOCK;
    case DXGI_FORMAT_BC2_UNORM_SRGB: return Format::BC2_SRGB_BLOCK;
    case DXGI_FORMAT_BC3_TYPELESS: return Format::BC3_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC3_UNORM: return Format::BC3_UNORM_BLOCK;
    case DXGI_FORMAT_BC3_UNORM_SRGB: return Format::BC3_SRGB_BLOCK;
    case DXGI_FORMAT_BC4_TYPELESS: return Format::BC4_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC4_UNORM: return Format::BC4_UNORM_BLOCK;
    case DXGI_FORMAT_BC4_SNORM: return Format::BC4_SNORM_BLOCK;
    case DXGI_FORMAT_BC5_TYPELESS: return Format::BC5_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC5_UNORM: return Format::BC5_UNORM_BLOCK;
    case DXGI_FORMAT_BC5_SNORM: return Format::BC5_SNORM_BLOCK;
    case DXGI_FORMAT_B5G6R5_UNORM: return Format::B5G6R5_UNORM_PACK16;
    case DXGI_FORMAT_B5G5R5A1_UNORM: return Format::B5G5R5A1_UNORM_PACK16;
    case DXGI_FORMAT_B8G8R8A8_UNORM: return Format::B8G8R8A8_UNORM;
    case DXGI_FORMAT_B8G8R8X8_UNORM: return Format::B8G8R8X8_UNORM;
    case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32;
    case DXGI_FORMAT_B8G8R8A8_TYPELESS: return Format::B8G8R8A8_TYPELESS;
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return Format::B8G8R8A8_SRGB;
    case DXGI_FORMAT_B8G8R8X8_TYPELESS: return Format::B8G8R8X8_TYPELESS;
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return Format::B8G8R8X8_SRGB;
    case DXGI_FORMAT_BC6H_TYPELESS: return Format::BC6H_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC6H_UF16: return Format::BC6H_UFLOAT_BLOCK;
    case DXGI_FORMAT_BC6H_SF16: return Format::BC6H_SFLOAT_BLOCK;
    case DXGI_FORMAT_BC7_TYPELESS: return Format::BC7_TYPELESS_BLOCK;
    case DXGI_FORMAT_BC7_UNORM: return Format::BC7_UNORM_BLOCK;
    case DXGI_FORMAT_BC7_UNORM_SRGB: return Format::BC7_SRGB_BLOCK;
    default: return Format::UNKNOWN;
    }
}

}
