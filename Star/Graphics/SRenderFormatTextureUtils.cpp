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
#include <Star/Graphics/SRenderFormatTextureUtils.h>
#include <Star/Graphics/SRenderFormatUtils.h>
#include <Star/Graphics/STextureUtils.h>

namespace Star::Graphics::Render {

Encoding getEncoding(Format format) noexcept {
    switch(format) {
    case Format::UNKNOWN: return { 0u, 0u, 0u };
    case Format::R64G64B64A64_UINT: return { 32u, 1u, 1u };
    case Format::R64G64B64A64_SINT: return { 32u, 1u, 1u };
    case Format::R64G64B64A64_SFLOAT: return { 32u, 1u, 1u };
    case Format::R64G64B64_UINT: return { 24u, 1u, 1u };
    case Format::R64G64B64_SINT: return { 24u, 1u, 1u };
    case Format::R64G64B64_SFLOAT: return { 24u, 1u, 1u };
    case Format::R32G32B32A32_TYPELESS: return { 16u, 1u, 1u };
    case Format::R32G32B32A32_UINT: return { 16u, 1u, 1u };
    case Format::R32G32B32A32_SINT: return { 16u, 1u, 1u };
    case Format::R32G32B32A32_SFLOAT: return { 16u, 1u, 1u };
    case Format::R64G64_UINT: return { 16u, 1u, 1u };
    case Format::R64G64_SINT: return { 16u, 1u, 1u };
    case Format::R64G64_SFLOAT: return { 16u, 1u, 1u };
    case Format::R32G32B32_TYPELESS: return { 12u, 1u, 1u };
    case Format::R32G32B32_UINT: return { 12u, 1u, 1u };
    case Format::R32G32B32_SINT: return { 12u, 1u, 1u };
    case Format::R32G32B32_SFLOAT: return { 12u, 1u, 1u };
    case Format::R16G16B16A16_TYPELESS: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_UNORM: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_SNORM: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_USCALED: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_SSCALED: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_UINT: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_SINT: return { 8u, 1u, 1u };
    case Format::R16G16B16A16_SFLOAT: return { 8u, 1u, 1u };
    case Format::R32G32_TYPELESS: return { 8u, 1u, 1u };
    case Format::R32G32_UINT: return { 8u, 1u, 1u };
    case Format::R32G32_SINT: return { 8u, 1u, 1u };
    case Format::R32G32_SFLOAT: return { 8u, 1u, 1u };
    case Format::R64_UINT: return { 8u, 1u, 1u };
    case Format::R64_SINT: return { 8u, 1u, 1u };
    case Format::R64_SFLOAT: return { 8u, 1u, 1u };
    case Format::R16G16B16_UNORM: return { 6u, 1u, 1u };
    case Format::R16G16B16_SNORM: return { 6u, 1u, 1u };
    case Format::R16G16B16_USCALED: return { 6u, 1u, 1u };
    case Format::R16G16B16_SSCALED: return { 6u, 1u, 1u };
    case Format::R16G16B16_UINT: return { 6u, 1u, 1u };
    case Format::R16G16B16_SINT: return { 6u, 1u, 1u };
    case Format::R16G16B16_SFLOAT: return { 6u, 1u, 1u };
    case Format::R10G10B10A2_TYPELESS_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_UNORM_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_SNORM_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_USCALED_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_SSCALED_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_UINT_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10A2_SINT_PACK32: return { 4u, 1u, 1u };
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_UNORM_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_SNORM_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_USCALED_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_SSCALED_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_UINT_PACK32: return { 4u, 1u, 1u };
    case Format::B10G10R10A2_SINT_PACK32: return { 4u, 1u, 1u };
    case Format::R9G9B9E5_UFLOAT_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_TYPELESS: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_UNORM: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_UNORM_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SNORM: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SNORM_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_USCALED: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_USCALED_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SSCALED: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SSCALED_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_UINT: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_UINT_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SINT: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SINT_PACK32: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SRGB: return { 4u, 1u, 1u };
    case Format::R8G8B8A8_SRGB_PACK32: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_TYPELESS: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_UNORM: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_SNORM: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_USCALED: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_SSCALED: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_UINT: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_SINT: return { 4u, 1u, 1u };
    case Format::B8G8R8A8_SRGB: return { 4u, 1u, 1u };
    case Format::R11G11B10_UFLOAT_PACK32: return { 4u, 1u, 1u };
    case Format::B8G8R8X8_TYPELESS: return { 4u, 1u, 1u };
    case Format::B8G8R8X8_UNORM: return { 4u, 1u, 1u };
    case Format::B8G8R8X8_SRGB: return { 4u, 1u, 1u };
    case Format::R16G16_TYPELESS: return { 4u, 1u, 1u };
    case Format::R16G16_UNORM: return { 4u, 1u, 1u };
    case Format::R16G16_SNORM: return { 4u, 1u, 1u };
    case Format::R16G16_USCALED: return { 4u, 1u, 1u };
    case Format::R16G16_SSCALED: return { 4u, 1u, 1u };
    case Format::R16G16_UINT: return { 4u, 1u, 1u };
    case Format::R16G16_SINT: return { 4u, 1u, 1u };
    case Format::R16G16_SFLOAT: return { 4u, 1u, 1u };
    case Format::R32_TYPELESS: return { 4u, 1u, 1u };
    case Format::R32_UINT: return { 4u, 1u, 1u };
    case Format::R32_SINT: return { 4u, 1u, 1u };
    case Format::R32_SFLOAT: return { 4u, 1u, 1u };
    case Format::R8G8B8_UNORM: return { 3u, 1u, 1u };
    case Format::R8G8B8_SNORM: return { 3u, 1u, 1u };
    case Format::R8G8B8_USCALED: return { 3u, 1u, 1u };
    case Format::R8G8B8_SSCALED: return { 3u, 1u, 1u };
    case Format::R8G8B8_UINT: return { 3u, 1u, 1u };
    case Format::R8G8B8_SINT: return { 3u, 1u, 1u };
    case Format::R8G8B8_SRGB: return { 3u, 1u, 1u };
    case Format::B8G8R8_UNORM: return { 3u, 1u, 1u };
    case Format::B8G8R8_SNORM: return { 3u, 1u, 1u };
    case Format::B8G8R8_USCALED: return { 3u, 1u, 1u };
    case Format::B8G8R8_SSCALED: return { 3u, 1u, 1u };
    case Format::B8G8R8_UINT: return { 3u, 1u, 1u };
    case Format::B8G8R8_SINT: return { 3u, 1u, 1u };
    case Format::B8G8R8_SRGB: return { 3u, 1u, 1u };
    case Format::B5G5R5A1_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::A1B5G5R5_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::A1R5G5B5_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::A4B4G4R4_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::A4R4G4B4_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::R5G6B5_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::B5G6R5_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::R8G8_TYPELESS: return { 2u, 1u, 1u };
    case Format::R8G8_UNORM: return { 2u, 1u, 1u };
    case Format::R8G8_SNORM: return { 2u, 1u, 1u };
    case Format::R8G8_USCALED: return { 2u, 1u, 1u };
    case Format::R8G8_SSCALED: return { 2u, 1u, 1u };
    case Format::R8G8_UINT: return { 2u, 1u, 1u };
    case Format::R8G8_SINT: return { 2u, 1u, 1u };
    case Format::R8G8_SRGB: return { 2u, 1u, 1u };
    case Format::R16_TYPELESS: return { 2u, 1u, 1u };
    case Format::R16_UNORM: return { 2u, 1u, 1u };
    case Format::R16_SNORM: return { 2u, 1u, 1u };
    case Format::R16_USCALED: return { 2u, 1u, 1u };
    case Format::R16_SSCALED: return { 2u, 1u, 1u };
    case Format::R16_UINT: return { 2u, 1u, 1u };
    case Format::R16_SINT: return { 2u, 1u, 1u };
    case Format::R16_SFLOAT: return { 2u, 1u, 1u };
    case Format::G4R4_UNORM_PACK8: return { 1u, 1u, 1u };
    case Format::R8_TYPELESS: return { 1u, 1u, 1u };
    case Format::R8_UNORM: return { 1u, 1u, 1u };
    case Format::R8_SNORM: return { 1u, 1u, 1u };
    case Format::R8_USCALED: return { 1u, 1u, 1u };
    case Format::R8_SSCALED: return { 1u, 1u, 1u };
    case Format::R8_UINT: return { 1u, 1u, 1u };
    case Format::R8_SINT: return { 1u, 1u, 1u };
    case Format::R8_SRGB: return { 1u, 1u, 1u };
    case Format::A8_UNORM: return { 1u, 1u, 1u };
    case Format::R1_UNORM: return { 0u, 1u, 1u };
    case Format::R32G8X24_TYPELESS_2PACK32: return { 8u, 1u, 1u };
    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32: return { 8u, 1u, 1u };
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32: return { 8u, 1u, 1u };
    case Format::D32_SFLOAT_S8_UINT: return { 5u, 1u, 1u };
    case Format::R24G8_TYPELESS_PACK32: return { 4u, 1u, 1u };
    case Format::D24_UNORM_S8_UINT: return { 4u, 1u, 1u };
    case Format::R24_UNORM_X8_TYPELESS_PACK32: return { 4u, 1u, 1u };
    case Format::X24_TYPELESS_G8_UINT_PACK32: return { 4u, 1u, 1u };
    case Format::D24_UNORM_X8_TYPELESS_PACK32: return { 4u, 1u, 1u };
    case Format::D32_SFLOAT: return { 4u, 1u, 1u };
    case Format::D16_UNORM_S8_UINT: return { 3u, 1u, 1u };
    case Format::D16_UNORM: return { 2u, 1u, 1u };
    case Format::S8_UINT: return { 1u, 1u, 1u };
    case Format::BC1_RGBA_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::BC1_RGBA_SRGB_BLOCK: return { 8u, 4u, 4u };
    case Format::BC1_TYPELESS_BLOCK: return { 8u, 4u, 4u };
    case Format::BC1_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::BC1_SRGB_BLOCK: return { 8u, 4u, 4u };
    case Format::BC2_TYPELESS_BLOCK: return { 16u, 4u, 4u };
    case Format::BC2_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::BC2_SRGB_BLOCK: return { 16u, 4u, 4u };
    case Format::BC3_TYPELESS_BLOCK: return { 16u, 4u, 4u };
    case Format::BC3_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::BC3_SRGB_BLOCK: return { 16u, 4u, 4u };
    case Format::BC4_TYPELESS_BLOCK: return { 8u, 4u, 4u };
    case Format::BC4_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::BC4_SNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::BC5_TYPELESS_BLOCK: return { 16u, 4u, 4u };
    case Format::BC5_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::BC5_SNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::BC6H_TYPELESS_BLOCK: return { 16u, 4u, 4u };
    case Format::BC6H_UFLOAT_BLOCK: return { 16u, 4u, 4u };
    case Format::BC6H_SFLOAT_BLOCK: return { 16u, 4u, 4u };
    case Format::BC7_TYPELESS_BLOCK: return { 16u, 4u, 4u };
    case Format::BC7_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::BC7_SRGB_BLOCK: return { 16u, 4u, 4u };
    case Format::ETC2_R8G8B8A8_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::ETC2_R8G8B8A8_SRGB_BLOCK: return { 16u, 4u, 4u };
    case Format::ETC2_R8G8B8A1_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::ETC2_R8G8B8A1_SRGB_BLOCK: return { 8u, 4u, 4u };
    case Format::ETC2_R8G8B8_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::ETC2_R8G8B8_SRGB_BLOCK: return { 8u, 4u, 4u };
    case Format::EAC_R11G11_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::EAC_R11G11_SNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::EAC_R11_UNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::EAC_R11_SNORM_BLOCK: return { 8u, 4u, 4u };
    case Format::ASTC_4x4_UNORM_BLOCK: return { 16u, 4u, 4u };
    case Format::ASTC_4x4_SRGB_BLOCK: return { 16u, 4u, 4u };
    case Format::ASTC_5x4_UNORM_BLOCK: return { 16u, 5u, 4u };
    case Format::ASTC_5x4_SRGB_BLOCK: return { 16u, 5u, 4u };
    case Format::ASTC_5x5_UNORM_BLOCK: return { 16u, 5u, 5u };
    case Format::ASTC_5x5_SRGB_BLOCK: return { 16u, 5u, 5u };
    case Format::ASTC_6x5_UNORM_BLOCK: return { 16u, 6u, 5u };
    case Format::ASTC_6x5_SRGB_BLOCK: return { 16u, 6u, 5u };
    case Format::ASTC_6x6_UNORM_BLOCK: return { 16u, 6u, 6u };
    case Format::ASTC_6x6_SRGB_BLOCK: return { 16u, 6u, 6u };
    case Format::ASTC_8x5_UNORM_BLOCK: return { 16u, 8u, 5u };
    case Format::ASTC_8x5_SRGB_BLOCK: return { 16u, 8u, 5u };
    case Format::ASTC_8x6_UNORM_BLOCK: return { 16u, 8u, 6u };
    case Format::ASTC_8x6_SRGB_BLOCK: return { 16u, 8u, 6u };
    case Format::ASTC_8x8_UNORM_BLOCK: return { 16u, 8u, 8u };
    case Format::ASTC_8x8_SRGB_BLOCK: return { 16u, 8u, 8u };
    case Format::ASTC_10x5_UNORM_BLOCK: return { 16u, 10u, 5u };
    case Format::ASTC_10x5_SRGB_BLOCK: return { 16u, 10u, 5u };
    case Format::ASTC_10x6_UNORM_BLOCK: return { 16u, 10u, 6u };
    case Format::ASTC_10x6_SRGB_BLOCK: return { 16u, 10u, 6u };
    case Format::ASTC_10x8_UNORM_BLOCK: return { 16u, 10u, 8u };
    case Format::ASTC_10x8_SRGB_BLOCK: return { 16u, 10u, 8u };
    case Format::ASTC_10x10_UNORM_BLOCK: return { 16u, 10u, 10u };
    case Format::ASTC_10x10_SRGB_BLOCK: return { 16u, 10u, 10u };
    case Format::ASTC_12x10_UNORM_BLOCK: return { 16u, 12u, 10u };
    case Format::ASTC_12x10_SRGB_BLOCK: return { 16u, 12u, 10u };
    case Format::ASTC_12x12_UNORM_BLOCK: return { 16u, 12u, 12u };
    case Format::ASTC_12x12_SRGB_BLOCK: return { 16u, 12u, 12u };
    case Format::R12X4G12X4B12X4A12X4_UNORM_4PACK16: return { 8u, 1u, 1u };
    case Format::R10X6G10X6B10X6A10X6_UNORM_4PACK16: return { 8u, 1u, 1u };
    case Format::R12X4G12X4_UNORM_2PACK16: return { 4u, 1u, 1u };
    case Format::R10X6G10X6_UNORM_2PACK16: return { 4u, 1u, 1u };
    case Format::R12X4_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::R10X6_UNORM_PACK16: return { 2u, 1u, 1u };
    case Format::R8G8_B8G8_UNORM: return { 4u, 2u, 1u };
    case Format::G16B16_G16R16_422_UNORM: return { 8u, 2u, 1u };
    case Format::G12X4B12X4_G12X4R12X4_422_UNORM_4PACK16: return { 8u, 2u, 1u };
    case Format::G10X6B10X6_G10X6R10X6_422_UNORM_4PACK16: return { 8u, 2u, 1u };
    case Format::G8B8_G8R8_422_UNORM: return { 4u, 2u, 1u };
    case Format::G8R8_G8B8_UNORM: return { 4u, 2u, 1u };
    case Format::B16G16_R16G16_422_UNORM: return { 8u, 2u, 1u };
    case Format::B12X4G12X4_R12X4G12X4_422_UNORM_4PACK16: return { 8u, 2u, 1u };
    case Format::B10X6G10X6_R10X6G10X6_422_UNORM_4PACK16: return { 8u, 2u, 1u };
    case Format::B8G8_R8G8_422_UNORM: return { 4u, 2u, 1u };
    case Format::G16_B16_R16_3PLANE_444_UNORM: return { 2u, 1u, 1u };
    case Format::G16_B16_R16_3PLANE_422_UNORM: return { 2u, 1u, 1u };
    case Format::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G16_B16_R16_3PLANE_420_UNORM: return { 2u, 1u, 1u };
    case Format::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G8_B8_R8_3PLANE_444_UNORM: return { 1u, 1u, 1u };
    case Format::G8_B8_R8_3PLANE_422_UNORM: return { 1u, 1u, 1u };
    case Format::G8_B8_R8_3PLANE_420_UNORM: return { 1u, 1u, 1u };
    case Format::G16_B16R16_2PLANE_422_UNORM: return { 2u, 1u, 1u };
    case Format::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: return { 2u, 1u, 1u };
    case Format::G16_B16R16_2PLANE_420_UNORM: return { 4u, 2u, 1u };
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: return { 4u, 2u, 1u };
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: return { 4u, 2u, 1u };
    case Format::G8_B8R8_2PLANE_422_UNORM: return { 1u, 1u, 1u };
    case Format::G8_B8R8_2PLANE_420_UNORM: return { 2u, 2u, 1u };
    case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG: return { 8u, 4u, 4u };
    case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG: return { 8u, 4u, 4u };
    case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG: return { 4u, 4u, 4u };
    case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG: return { 4u, 4u, 4u };
    case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG: return { 8u, 4u, 4u };
    case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG: return { 8u, 4u, 4u };
    case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG: return { 4u, 4u, 4u };
    case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG: return { 4u, 4u, 4u };
    default: return { 0u, 0u, 0u };
    }
}

MipInfo getMipInfo(Format format, uint32_t width, uint32_t height) noexcept {
    MipInfo info;
    auto[bpe, blockX, blockY] = getEncoding(format);
    switch(format) {
    case Format::UNKNOWN:
        info = {};
        return info;
    case Format::G16_B16R16_2PLANE_420_UNORM:
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
    case Format::G8_B8R8_2PLANE_420_UNORM:
        Expects(bpe);
        std::tie(info.mRowCount, info.mRowPitchSize, info.mSliceSize, info.mRowAlignedSliceSize) =
            y_uv_420_mip_info(width, height, bpe, sPitchAlignment);
        info.mUploadRowPitchSize = boost::alignment::align_up(info.mRowPitchSize, sPitchAlignment);
        info.mUploadSliceSize = boost::alignment::align_up(info.mRowAlignedSliceSize, sSliceAlignment);
        return info;
    default:
        Expects(bpe);
        std::tie(info.mRowCount, info.mRowPitchSize, info.mSliceSize, info.mRowAlignedSliceSize) =
            mip_info(width, height, blockX, blockY, bpe, sPitchAlignment);
        info.mUploadRowPitchSize = boost::alignment::align_up(info.mRowPitchSize, sPitchAlignment);
        info.mUploadSliceSize = boost::alignment::align_up(info.mRowAlignedSliceSize, sSliceAlignment);
        return info;
    }
}

uint64_t getMipSize(Format format, uint32_t width, uint32_t height) noexcept {
    auto[bpe, blockX, blockY] = getEncoding(format);
    switch(format) {
    case Format::UNKNOWN:
        return 0;
    case Format::G16_B16R16_2PLANE_420_UNORM:
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
    case Format::G8_B8R8_2PLANE_420_UNORM:
        Expects(bpe);
        return y_uv_420_mip_size(width, height, bpe);
    default:
        Expects(bpe);
        return mip_size(width, height, blockX, blockY, bpe);
    }
}

uint64_t getMipUploadSize(Format format, uint32_t width, uint32_t height) noexcept {
    auto[bpe, blockX, blockY] = getEncoding(format);
    switch(format) {
    case Format::UNKNOWN:
        return 0;
    case Format::G16_B16R16_2PLANE_420_UNORM:
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
    case Format::G8_B8R8_2PLANE_420_UNORM:
        Expects(bpe);
        return y_uv_420_mip_size(width, height, bpe, sPitchAlignment);
    default:
        Expects(bpe);
        return mip_size(width, height, blockX, blockY, bpe, sPitchAlignment);
    }
}

uint64_t getTextureSize(Format format, uint32_t width, uint32_t height) noexcept {
    auto[bpe, blockX, blockY] = getEncoding(format);
    switch(format) {
    case Format::UNKNOWN:
        return 0;
    case Format::G16_B16R16_2PLANE_420_UNORM:
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
    case Format::G8_B8R8_2PLANE_420_UNORM:
        Expects(bpe);
        return y_uv_420_texture_size(width, height, bpe);
    default:
        Expects(bpe);
        return texture_size(width, height, blockX, blockY, bpe);
    }
}

uint64_t getTextureUploadSize(Format format, uint32_t width, uint32_t height) noexcept {
    auto[bpe, blockX, blockY] = getEncoding(format);
    switch(format) {
    case Format::UNKNOWN:
        return 0;
    case Format::G16_B16R16_2PLANE_420_UNORM:
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
    case Format::G8_B8R8_2PLANE_420_UNORM:
        Expects(bpe);
        return y_uv_420_texture_size(width, height, bpe, sPitchAlignment, sSliceAlignment);
    default:
        Expects(bpe);
        return texture_size(width, height, blockX, blockY, bpe, sPitchAlignment, sSliceAlignment);
    }
}

}
