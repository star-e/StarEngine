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

namespace Star::Graphics::Render {

inline const char* getName(Format format) noexcept {
    switch(format) {
    case Format::UNKNOWN: return "UNKNOWN";
    case Format::R64G64B64A64_UINT: return "R64G64B64A64_UINT";
    case Format::R64G64B64A64_SINT: return "R64G64B64A64_SINT";
    case Format::R64G64B64A64_SFLOAT: return "R64G64B64A64_SFLOAT";
    case Format::R64G64B64_UINT: return "R64G64B64_UINT";
    case Format::R64G64B64_SINT: return "R64G64B64_SINT";
    case Format::R64G64B64_SFLOAT: return "R64G64B64_SFLOAT";
    case Format::R32G32B32A32_TYPELESS: return "R32G32B32A32_TYPELESS";
    case Format::R32G32B32A32_UINT: return "R32G32B32A32_UINT";
    case Format::R32G32B32A32_SINT: return "R32G32B32A32_SINT";
    case Format::R32G32B32A32_SFLOAT: return "R32G32B32A32_SFLOAT";
    case Format::R64G64_UINT: return "R64G64_UINT";
    case Format::R64G64_SINT: return "R64G64_SINT";
    case Format::R64G64_SFLOAT: return "R64G64_SFLOAT";
    case Format::R32G32B32_TYPELESS: return "R32G32B32_TYPELESS";
    case Format::R32G32B32_UINT: return "R32G32B32_UINT";
    case Format::R32G32B32_SINT: return "R32G32B32_SINT";
    case Format::R32G32B32_SFLOAT: return "R32G32B32_SFLOAT";
    case Format::R16G16B16A16_TYPELESS: return "R16G16B16A16_TYPELESS";
    case Format::R16G16B16A16_UNORM: return "R16G16B16A16_UNORM";
    case Format::R16G16B16A16_SNORM: return "R16G16B16A16_SNORM";
    case Format::R16G16B16A16_USCALED: return "R16G16B16A16_USCALED";
    case Format::R16G16B16A16_SSCALED: return "R16G16B16A16_SSCALED";
    case Format::R16G16B16A16_UINT: return "R16G16B16A16_UINT";
    case Format::R16G16B16A16_SINT: return "R16G16B16A16_SINT";
    case Format::R16G16B16A16_SFLOAT: return "R16G16B16A16_SFLOAT";
    case Format::R32G32_TYPELESS: return "R32G32_TYPELESS";
    case Format::R32G32_UINT: return "R32G32_UINT";
    case Format::R32G32_SINT: return "R32G32_SINT";
    case Format::R32G32_SFLOAT: return "R32G32_SFLOAT";
    case Format::R64_UINT: return "R64_UINT";
    case Format::R64_SINT: return "R64_SINT";
    case Format::R64_SFLOAT: return "R64_SFLOAT";
    case Format::R16G16B16_UNORM: return "R16G16B16_UNORM";
    case Format::R16G16B16_SNORM: return "R16G16B16_SNORM";
    case Format::R16G16B16_USCALED: return "R16G16B16_USCALED";
    case Format::R16G16B16_SSCALED: return "R16G16B16_SSCALED";
    case Format::R16G16B16_UINT: return "R16G16B16_UINT";
    case Format::R16G16B16_SINT: return "R16G16B16_SINT";
    case Format::R16G16B16_SFLOAT: return "R16G16B16_SFLOAT";
    case Format::R10G10B10A2_TYPELESS_PACK32: return "R10G10B10A2_TYPELESS_PACK32";
    case Format::R10G10B10A2_UNORM_PACK32: return "R10G10B10A2_UNORM_PACK32";
    case Format::R10G10B10A2_SNORM_PACK32: return "R10G10B10A2_SNORM_PACK32";
    case Format::R10G10B10A2_USCALED_PACK32: return "R10G10B10A2_USCALED_PACK32";
    case Format::R10G10B10A2_SSCALED_PACK32: return "R10G10B10A2_SSCALED_PACK32";
    case Format::R10G10B10A2_UINT_PACK32: return "R10G10B10A2_UINT_PACK32";
    case Format::R10G10B10A2_SINT_PACK32: return "R10G10B10A2_SINT_PACK32";
    case Format::R10G10B10_XR_BIAS_A2_UNORM_PACK32: return "R10G10B10_XR_BIAS_A2_UNORM_PACK32";
    case Format::B10G10R10A2_UNORM_PACK32: return "B10G10R10A2_UNORM_PACK32";
    case Format::B10G10R10A2_SNORM_PACK32: return "B10G10R10A2_SNORM_PACK32";
    case Format::B10G10R10A2_USCALED_PACK32: return "B10G10R10A2_USCALED_PACK32";
    case Format::B10G10R10A2_SSCALED_PACK32: return "B10G10R10A2_SSCALED_PACK32";
    case Format::B10G10R10A2_UINT_PACK32: return "B10G10R10A2_UINT_PACK32";
    case Format::B10G10R10A2_SINT_PACK32: return "B10G10R10A2_SINT_PACK32";
    case Format::R9G9B9E5_UFLOAT_PACK32: return "R9G9B9E5_UFLOAT_PACK32";
    case Format::R8G8B8A8_TYPELESS: return "R8G8B8A8_TYPELESS";
    case Format::R8G8B8A8_UNORM: return "R8G8B8A8_UNORM";
    case Format::R8G8B8A8_UNORM_PACK32: return "R8G8B8A8_UNORM_PACK32";
    case Format::R8G8B8A8_SNORM: return "R8G8B8A8_SNORM";
    case Format::R8G8B8A8_SNORM_PACK32: return "R8G8B8A8_SNORM_PACK32";
    case Format::R8G8B8A8_USCALED: return "R8G8B8A8_USCALED";
    case Format::R8G8B8A8_USCALED_PACK32: return "R8G8B8A8_USCALED_PACK32";
    case Format::R8G8B8A8_SSCALED: return "R8G8B8A8_SSCALED";
    case Format::R8G8B8A8_SSCALED_PACK32: return "R8G8B8A8_SSCALED_PACK32";
    case Format::R8G8B8A8_UINT: return "R8G8B8A8_UINT";
    case Format::R8G8B8A8_UINT_PACK32: return "R8G8B8A8_UINT_PACK32";
    case Format::R8G8B8A8_SINT: return "R8G8B8A8_SINT";
    case Format::R8G8B8A8_SINT_PACK32: return "R8G8B8A8_SINT_PACK32";
    case Format::R8G8B8A8_SRGB: return "R8G8B8A8_SRGB";
    case Format::R8G8B8A8_SRGB_PACK32: return "R8G8B8A8_SRGB_PACK32";
    case Format::B8G8R8A8_TYPELESS: return "B8G8R8A8_TYPELESS";
    case Format::B8G8R8A8_UNORM: return "B8G8R8A8_UNORM";
    case Format::B8G8R8A8_SNORM: return "B8G8R8A8_SNORM";
    case Format::B8G8R8A8_USCALED: return "B8G8R8A8_USCALED";
    case Format::B8G8R8A8_SSCALED: return "B8G8R8A8_SSCALED";
    case Format::B8G8R8A8_UINT: return "B8G8R8A8_UINT";
    case Format::B8G8R8A8_SINT: return "B8G8R8A8_SINT";
    case Format::B8G8R8A8_SRGB: return "B8G8R8A8_SRGB";
    case Format::R11G11B10_UFLOAT_PACK32: return "R11G11B10_UFLOAT_PACK32";
    case Format::B8G8R8X8_TYPELESS: return "B8G8R8X8_TYPELESS";
    case Format::B8G8R8X8_UNORM: return "B8G8R8X8_UNORM";
    case Format::B8G8R8X8_SRGB: return "B8G8R8X8_SRGB";
    case Format::R16G16_TYPELESS: return "R16G16_TYPELESS";
    case Format::R16G16_UNORM: return "R16G16_UNORM";
    case Format::R16G16_SNORM: return "R16G16_SNORM";
    case Format::R16G16_USCALED: return "R16G16_USCALED";
    case Format::R16G16_SSCALED: return "R16G16_SSCALED";
    case Format::R16G16_UINT: return "R16G16_UINT";
    case Format::R16G16_SINT: return "R16G16_SINT";
    case Format::R16G16_SFLOAT: return "R16G16_SFLOAT";
    case Format::R32_TYPELESS: return "R32_TYPELESS";
    case Format::R32_UINT: return "R32_UINT";
    case Format::R32_SINT: return "R32_SINT";
    case Format::R32_SFLOAT: return "R32_SFLOAT";
    case Format::R8G8B8_UNORM: return "R8G8B8_UNORM";
    case Format::R8G8B8_SNORM: return "R8G8B8_SNORM";
    case Format::R8G8B8_USCALED: return "R8G8B8_USCALED";
    case Format::R8G8B8_SSCALED: return "R8G8B8_SSCALED";
    case Format::R8G8B8_UINT: return "R8G8B8_UINT";
    case Format::R8G8B8_SINT: return "R8G8B8_SINT";
    case Format::R8G8B8_SRGB: return "R8G8B8_SRGB";
    case Format::B8G8R8_UNORM: return "B8G8R8_UNORM";
    case Format::B8G8R8_SNORM: return "B8G8R8_SNORM";
    case Format::B8G8R8_USCALED: return "B8G8R8_USCALED";
    case Format::B8G8R8_SSCALED: return "B8G8R8_SSCALED";
    case Format::B8G8R8_UINT: return "B8G8R8_UINT";
    case Format::B8G8R8_SINT: return "B8G8R8_SINT";
    case Format::B8G8R8_SRGB: return "B8G8R8_SRGB";
    case Format::B5G5R5A1_UNORM_PACK16: return "B5G5R5A1_UNORM_PACK16";
    case Format::A1B5G5R5_UNORM_PACK16: return "A1B5G5R5_UNORM_PACK16";
    case Format::A1R5G5B5_UNORM_PACK16: return "A1R5G5B5_UNORM_PACK16";
    case Format::A4B4G4R4_UNORM_PACK16: return "A4B4G4R4_UNORM_PACK16";
    case Format::A4R4G4B4_UNORM_PACK16: return "A4R4G4B4_UNORM_PACK16";
    case Format::R5G6B5_UNORM_PACK16: return "R5G6B5_UNORM_PACK16";
    case Format::B5G6R5_UNORM_PACK16: return "B5G6R5_UNORM_PACK16";
    case Format::R8G8_TYPELESS: return "R8G8_TYPELESS";
    case Format::R8G8_UNORM: return "R8G8_UNORM";
    case Format::R8G8_SNORM: return "R8G8_SNORM";
    case Format::R8G8_USCALED: return "R8G8_USCALED";
    case Format::R8G8_SSCALED: return "R8G8_SSCALED";
    case Format::R8G8_UINT: return "R8G8_UINT";
    case Format::R8G8_SINT: return "R8G8_SINT";
    case Format::R8G8_SRGB: return "R8G8_SRGB";
    case Format::R16_TYPELESS: return "R16_TYPELESS";
    case Format::R16_UNORM: return "R16_UNORM";
    case Format::R16_SNORM: return "R16_SNORM";
    case Format::R16_USCALED: return "R16_USCALED";
    case Format::R16_SSCALED: return "R16_SSCALED";
    case Format::R16_UINT: return "R16_UINT";
    case Format::R16_SINT: return "R16_SINT";
    case Format::R16_SFLOAT: return "R16_SFLOAT";
    case Format::G4R4_UNORM_PACK8: return "G4R4_UNORM_PACK8";
    case Format::R8_TYPELESS: return "R8_TYPELESS";
    case Format::R8_UNORM: return "R8_UNORM";
    case Format::R8_SNORM: return "R8_SNORM";
    case Format::R8_USCALED: return "R8_USCALED";
    case Format::R8_SSCALED: return "R8_SSCALED";
    case Format::R8_UINT: return "R8_UINT";
    case Format::R8_SINT: return "R8_SINT";
    case Format::R8_SRGB: return "R8_SRGB";
    case Format::A8_UNORM: return "A8_UNORM";
    case Format::R1_UNORM: return "R1_UNORM";
    case Format::R32G8X24_TYPELESS_2PACK32: return "R32G8X24_TYPELESS_2PACK32";
    case Format::R32_SFLOAT_X8X24_TYPELESS_2PACK32: return "R32_SFLOAT_X8X24_TYPELESS_2PACK32";
    case Format::X32_TYPELESS_G8X24_UINT_2PACK32: return "X32_TYPELESS_G8X24_UINT_2PACK32";
    case Format::D32_SFLOAT_S8_UINT: return "D32_SFLOAT_S8_UINT";
    case Format::R24G8_TYPELESS_PACK32: return "R24G8_TYPELESS_PACK32";
    case Format::D24_UNORM_S8_UINT: return "D24_UNORM_S8_UINT";
    case Format::R24_UNORM_X8_TYPELESS_PACK32: return "R24_UNORM_X8_TYPELESS_PACK32";
    case Format::X24_TYPELESS_G8_UINT_PACK32: return "X24_TYPELESS_G8_UINT_PACK32";
    case Format::D24_UNORM_X8_TYPELESS_PACK32: return "D24_UNORM_X8_TYPELESS_PACK32";
    case Format::D32_SFLOAT: return "D32_SFLOAT";
    case Format::D16_UNORM_S8_UINT: return "D16_UNORM_S8_UINT";
    case Format::D16_UNORM: return "D16_UNORM";
    case Format::S8_UINT: return "S8_UINT";
    case Format::BC1_RGBA_UNORM_BLOCK: return "BC1_RGBA_UNORM_BLOCK";
    case Format::BC1_RGBA_SRGB_BLOCK: return "BC1_RGBA_SRGB_BLOCK";
    case Format::BC1_TYPELESS_BLOCK: return "BC1_TYPELESS_BLOCK";
    case Format::BC1_UNORM_BLOCK: return "BC1_UNORM_BLOCK";
    case Format::BC1_SRGB_BLOCK: return "BC1_SRGB_BLOCK";
    case Format::BC2_TYPELESS_BLOCK: return "BC2_TYPELESS_BLOCK";
    case Format::BC2_UNORM_BLOCK: return "BC2_UNORM_BLOCK";
    case Format::BC2_SRGB_BLOCK: return "BC2_SRGB_BLOCK";
    case Format::BC3_TYPELESS_BLOCK: return "BC3_TYPELESS_BLOCK";
    case Format::BC3_UNORM_BLOCK: return "BC3_UNORM_BLOCK";
    case Format::BC3_SRGB_BLOCK: return "BC3_SRGB_BLOCK";
    case Format::BC4_TYPELESS_BLOCK: return "BC4_TYPELESS_BLOCK";
    case Format::BC4_UNORM_BLOCK: return "BC4_UNORM_BLOCK";
    case Format::BC4_SNORM_BLOCK: return "BC4_SNORM_BLOCK";
    case Format::BC5_TYPELESS_BLOCK: return "BC5_TYPELESS_BLOCK";
    case Format::BC5_UNORM_BLOCK: return "BC5_UNORM_BLOCK";
    case Format::BC5_SNORM_BLOCK: return "BC5_SNORM_BLOCK";
    case Format::BC6H_TYPELESS_BLOCK: return "BC6H_TYPELESS_BLOCK";
    case Format::BC6H_UFLOAT_BLOCK: return "BC6H_UFLOAT_BLOCK";
    case Format::BC6H_SFLOAT_BLOCK: return "BC6H_SFLOAT_BLOCK";
    case Format::BC7_TYPELESS_BLOCK: return "BC7_TYPELESS_BLOCK";
    case Format::BC7_UNORM_BLOCK: return "BC7_UNORM_BLOCK";
    case Format::BC7_SRGB_BLOCK: return "BC7_SRGB_BLOCK";
    case Format::ETC2_R8G8B8A8_UNORM_BLOCK: return "ETC2_R8G8B8A8_UNORM_BLOCK";
    case Format::ETC2_R8G8B8A8_SRGB_BLOCK: return "ETC2_R8G8B8A8_SRGB_BLOCK";
    case Format::ETC2_R8G8B8A1_UNORM_BLOCK: return "ETC2_R8G8B8A1_UNORM_BLOCK";
    case Format::ETC2_R8G8B8A1_SRGB_BLOCK: return "ETC2_R8G8B8A1_SRGB_BLOCK";
    case Format::ETC2_R8G8B8_UNORM_BLOCK: return "ETC2_R8G8B8_UNORM_BLOCK";
    case Format::ETC2_R8G8B8_SRGB_BLOCK: return "ETC2_R8G8B8_SRGB_BLOCK";
    case Format::EAC_R11G11_UNORM_BLOCK: return "EAC_R11G11_UNORM_BLOCK";
    case Format::EAC_R11G11_SNORM_BLOCK: return "EAC_R11G11_SNORM_BLOCK";
    case Format::EAC_R11_UNORM_BLOCK: return "EAC_R11_UNORM_BLOCK";
    case Format::EAC_R11_SNORM_BLOCK: return "EAC_R11_SNORM_BLOCK";
    case Format::ASTC_4x4_UNORM_BLOCK: return "ASTC_4x4_UNORM_BLOCK";
    case Format::ASTC_4x4_SRGB_BLOCK: return "ASTC_4x4_SRGB_BLOCK";
    case Format::ASTC_5x4_UNORM_BLOCK: return "ASTC_5x4_UNORM_BLOCK";
    case Format::ASTC_5x4_SRGB_BLOCK: return "ASTC_5x4_SRGB_BLOCK";
    case Format::ASTC_5x5_UNORM_BLOCK: return "ASTC_5x5_UNORM_BLOCK";
    case Format::ASTC_5x5_SRGB_BLOCK: return "ASTC_5x5_SRGB_BLOCK";
    case Format::ASTC_6x5_UNORM_BLOCK: return "ASTC_6x5_UNORM_BLOCK";
    case Format::ASTC_6x5_SRGB_BLOCK: return "ASTC_6x5_SRGB_BLOCK";
    case Format::ASTC_6x6_UNORM_BLOCK: return "ASTC_6x6_UNORM_BLOCK";
    case Format::ASTC_6x6_SRGB_BLOCK: return "ASTC_6x6_SRGB_BLOCK";
    case Format::ASTC_8x5_UNORM_BLOCK: return "ASTC_8x5_UNORM_BLOCK";
    case Format::ASTC_8x5_SRGB_BLOCK: return "ASTC_8x5_SRGB_BLOCK";
    case Format::ASTC_8x6_UNORM_BLOCK: return "ASTC_8x6_UNORM_BLOCK";
    case Format::ASTC_8x6_SRGB_BLOCK: return "ASTC_8x6_SRGB_BLOCK";
    case Format::ASTC_8x8_UNORM_BLOCK: return "ASTC_8x8_UNORM_BLOCK";
    case Format::ASTC_8x8_SRGB_BLOCK: return "ASTC_8x8_SRGB_BLOCK";
    case Format::ASTC_10x5_UNORM_BLOCK: return "ASTC_10x5_UNORM_BLOCK";
    case Format::ASTC_10x5_SRGB_BLOCK: return "ASTC_10x5_SRGB_BLOCK";
    case Format::ASTC_10x6_UNORM_BLOCK: return "ASTC_10x6_UNORM_BLOCK";
    case Format::ASTC_10x6_SRGB_BLOCK: return "ASTC_10x6_SRGB_BLOCK";
    case Format::ASTC_10x8_UNORM_BLOCK: return "ASTC_10x8_UNORM_BLOCK";
    case Format::ASTC_10x8_SRGB_BLOCK: return "ASTC_10x8_SRGB_BLOCK";
    case Format::ASTC_10x10_UNORM_BLOCK: return "ASTC_10x10_UNORM_BLOCK";
    case Format::ASTC_10x10_SRGB_BLOCK: return "ASTC_10x10_SRGB_BLOCK";
    case Format::ASTC_12x10_UNORM_BLOCK: return "ASTC_12x10_UNORM_BLOCK";
    case Format::ASTC_12x10_SRGB_BLOCK: return "ASTC_12x10_SRGB_BLOCK";
    case Format::ASTC_12x12_UNORM_BLOCK: return "ASTC_12x12_UNORM_BLOCK";
    case Format::ASTC_12x12_SRGB_BLOCK: return "ASTC_12x12_SRGB_BLOCK";
    case Format::R12X4G12X4B12X4A12X4_UNORM_4PACK16: return "R12X4G12X4B12X4A12X4_UNORM_4PACK16";
    case Format::R10X6G10X6B10X6A10X6_UNORM_4PACK16: return "R10X6G10X6B10X6A10X6_UNORM_4PACK16";
    case Format::R12X4G12X4_UNORM_2PACK16: return "R12X4G12X4_UNORM_2PACK16";
    case Format::R10X6G10X6_UNORM_2PACK16: return "R10X6G10X6_UNORM_2PACK16";
    case Format::R12X4_UNORM_PACK16: return "R12X4_UNORM_PACK16";
    case Format::R10X6_UNORM_PACK16: return "R10X6_UNORM_PACK16";
    case Format::R8G8_B8G8_UNORM: return "R8G8_B8G8_UNORM";
    case Format::G16B16_G16R16_422_UNORM: return "G16B16_G16R16_422_UNORM";
    case Format::G12X4B12X4_G12X4R12X4_422_UNORM_4PACK16: return "G12X4B12X4_G12X4R12X4_422_UNORM_4PACK16";
    case Format::G10X6B10X6_G10X6R10X6_422_UNORM_4PACK16: return "G10X6B10X6_G10X6R10X6_422_UNORM_4PACK16";
    case Format::G8B8_G8R8_422_UNORM: return "G8B8_G8R8_422_UNORM";
    case Format::G8R8_G8B8_UNORM: return "G8R8_G8B8_UNORM";
    case Format::B16G16_R16G16_422_UNORM: return "B16G16_R16G16_422_UNORM";
    case Format::B12X4G12X4_R12X4G12X4_422_UNORM_4PACK16: return "B12X4G12X4_R12X4G12X4_422_UNORM_4PACK16";
    case Format::B10X6G10X6_R10X6G10X6_422_UNORM_4PACK16: return "B10X6G10X6_R10X6G10X6_422_UNORM_4PACK16";
    case Format::B8G8_R8G8_422_UNORM: return "B8G8_R8G8_422_UNORM";
    case Format::G16_B16_R16_3PLANE_444_UNORM: return "G16_B16_R16_3PLANE_444_UNORM";
    case Format::G16_B16_R16_3PLANE_422_UNORM: return "G16_B16_R16_3PLANE_422_UNORM";
    case Format::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: return "G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16";
    case Format::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: return "G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16";
    case Format::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return "G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16";
    case Format::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return "G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16";
    case Format::G16_B16_R16_3PLANE_420_UNORM: return "G16_B16_R16_3PLANE_420_UNORM";
    case Format::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: return "G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16";
    case Format::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return "G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16";
    case Format::G8_B8_R8_3PLANE_444_UNORM: return "G8_B8_R8_3PLANE_444_UNORM";
    case Format::G8_B8_R8_3PLANE_422_UNORM: return "G8_B8_R8_3PLANE_422_UNORM";
    case Format::G8_B8_R8_3PLANE_420_UNORM: return "G8_B8_R8_3PLANE_420_UNORM";
    case Format::G16_B16R16_2PLANE_422_UNORM: return "G16_B16R16_2PLANE_422_UNORM";
    case Format::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: return "G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16";
    case Format::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: return "G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16";
    case Format::G16_B16R16_2PLANE_420_UNORM: return "G16_B16R16_2PLANE_420_UNORM";
    case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: return "G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16";
    case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: return "G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16";
    case Format::G8_B8R8_2PLANE_422_UNORM: return "G8_B8R8_2PLANE_422_UNORM";
    case Format::G8_B8R8_2PLANE_420_UNORM: return "G8_B8R8_2PLANE_420_UNORM";
    case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG: return "PVRTC1_4BPP_UNORM_BLOCK_IMG";
    case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG: return "PVRTC1_4BPP_SRGB_BLOCK_IMG";
    case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG: return "PVRTC1_2BPP_UNORM_BLOCK_IMG";
    case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG: return "PVRTC1_2BPP_SRGB_BLOCK_IMG";
    case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG: return "PVRTC2_4BPP_UNORM_BLOCK_IMG";
    case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG: return "PVRTC2_4BPP_SRGB_BLOCK_IMG";
    case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG: return "PVRTC2_2BPP_UNORM_BLOCK_IMG";
    case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG: return "PVRTC2_2BPP_SRGB_BLOCK_IMG";
    default: return "UNKNOWN";
    }
}

}
