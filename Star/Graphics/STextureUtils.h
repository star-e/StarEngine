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
#include <Star/SBitwise.h>

namespace Star {

// see https://docs.microsoft.com/en-us/windows/desktop/direct3d12/upload-and-readback-of-texture-data
// const UINT D3D12_TEXTURE_DATA_PITCH_ALIGNMENT = 256;
// const UINT D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT = 512;

// mipmap size
constexpr uint32_t block_count(uint32_t x, const uint32_t Block) noexcept {
    return (x + (Block - 1)) / Block;
}

constexpr uint32_t row_pitch_size(uint32_t x, const uint32_t BlockX, const uint32_t BPE) noexcept {
    return block_count(x, BlockX) * BPE;
}

constexpr uint64_t mip_size(uint32_t x, uint32_t y,
    const uint32_t BlockX, const uint32_t BlockY, const uint32_t BPE, const size_t RowAlignment = 1
) noexcept {
    return /*height*/(uint64_t)block_count(y, BlockY) *
        /*width*/boost::alignment::align_up(row_pitch_size(x, BlockX, BPE), RowAlignment);
}

constexpr std::tuple<uint32_t/*row count*/, uint32_t/*row pitch*/, uint64_t/*slice*/, uint64_t/*upload*/>
mip_info(uint32_t x, uint32_t y, const uint32_t BlockX, const uint32_t BlockY,
    const uint32_t BPE, const size_t RowAlignment
) noexcept {
    auto rowCount = block_count(y, BlockY);
    auto rowPitchSize = row_pitch_size(x, BlockX, BPE);
    auto bufferSize = rowCount * rowPitchSize;
    auto uploadSize = rowCount * gsl::narrow_cast<uint64_t>(boost::alignment::align_up(rowPitchSize, RowAlignment));
    return { rowCount, rowPitchSize, bufferSize, uploadSize };
}

// texture size
constexpr uint32_t half_size(uint32_t x) noexcept {
    x /= 2;
    return x ? x : 1;
}

constexpr uint64_t half_size(uint64_t x) noexcept {
    x /= 2;
    return x ? x : 1;
}

constexpr uint32_t half_size(uint32_t x, uint32_t Block) noexcept {
    x /= 2;
    return x < Block ? Block : x;
}

constexpr uint64_t half_size(uint64_t x, uint32_t Block) noexcept {
    x /= 2;
    return x < Block ? Block : x;
}

constexpr uint64_t texture_size(uint32_t x, uint32_t y,
    const uint32_t BlockX, const uint32_t BlockY, const uint32_t BPE,
    const size_t RowAlignment = 1, const size_t DepthAlignment = 1, uint64_t offset = 0
) noexcept {
    if (x == 1 && y == 1) {
        return offset + boost::alignment::align_up(
            mip_size(x, y, BlockX, BlockY, BPE, RowAlignment), DepthAlignment);
    } else {
        offset += boost::alignment::align_up(
            mip_size(x, y, BlockX, BlockY, BPE, RowAlignment), DepthAlignment);
        return texture_size(half_size(x), half_size(y),
            BlockX, BlockY, BPE, RowAlignment, DepthAlignment, offset);
    }
}

// 420, 12bpp
constexpr uint64_t y_uv_420_mip_size(uint32_t x, uint32_t y,
    const uint32_t BPE, const size_t RowAlignment = 1
) noexcept {
    const uint32_t BlockX = 2;
    const uint32_t BlockY = 1;
    y += ((y + 1) >> 1);
    return mip_size(x, y, BlockX, BlockY, BPE, RowAlignment);
}

constexpr std::tuple<uint32_t/*row count*/, uint32_t/*row pitch*/, uint64_t/*slice*/, uint64_t/*upload*/>
y_uv_420_mip_info(uint32_t x, uint32_t y, const uint32_t BPE, const size_t RowAlignment) noexcept {
    const uint32_t BlockX = 2;
    const uint32_t BlockY = 1;
    y += ((y + 1) >> 1);
    return mip_info(x, y, BlockX, BlockY, BPE, RowAlignment);
}

constexpr uint64_t y_uv_420_texture_size(uint32_t x, uint32_t y,
    const uint32_t BPE,
    const size_t RowAlignment = 1, const size_t DepthAlignment = 1, uint64_t offset = 0
) noexcept {
    if (x == 1 && y == 1) {
        return offset + y_uv_420_mip_size(x, y, BPE, RowAlignment);
    } else {
        offset += boost::alignment::align_up(
            y_uv_420_mip_size(x, y, BPE, RowAlignment), DepthAlignment);

        return y_uv_420_texture_size(half_size(x), half_size(y), BPE, RowAlignment, DepthAlignment, offset);
    }
}

constexpr uint32_t aligned_pixel_count(uint32_t x, const uint32_t Block) noexcept {
    return block_count(x, Block) * Block;
}

// pixel, deprecated

//
//constexpr uint32_t pixel_row_pitch_size(uint32_t x, const uint32_t BlockX, const uint32_t BPP) noexcept {
//    return gsl::narrow_cast<uint32_t>((uint64_t(aligned_pixel_count(x, BlockX)) * BPP + 7) / 8);
//}
//
//constexpr uint64_t mip_size_bpp(uint32_t x, uint32_t y,
//    const uint32_t BlockX, const uint32_t BlockY, const uint32_t BPP,
//    const uint32_t RowAlignment = 1
//) noexcept {
//    return /*height*/aligned_pixel_count(y, BlockY) *
//        /*width*/boost::alignment::align_up(pixel_row_pitch_size(x, BlockX, BPP), RowAlignment);
//}
//
//constexpr uint64_t texture_size_bpp(uint32_t x, uint32_t y,
//    const uint32_t BlockX, const uint32_t BlockY, const uint32_t BPP,
//    const uint32_t RowAlignment = 1, const uint32_t DepthAlignment = 1, uint64_t offset = 0
//) noexcept {
//    if (x == 1 && y == 1) {
//        return offset + mip_size_bpp(x, y, BlockX, BlockY, BPP, RowAlignment);
//    } else {
//        offset += boost::alignment::align_up(
//            mip_size_bpp(x, y, BlockX, BlockY, BPP, RowAlignment), DepthAlignment);
//
//        return texture_size_bpp(half_size(x), half_size(y),
//            BlockX, BlockY, BPP, RowAlignment, DepthAlignment, offset);
//    }
//}

// mipmap calcuation
constexpr uint32_t mip_level(uint32_t n, uint32_t p) {
    Expects(n > 0);
    return (n <= 1) ? p : mip_level(n / 2, p + 1);
}

//constexpr uint32_t log2i_size(uint32_t width, uint32_t height) noexcept {
//    uint32_t minDim = std::min(width, height);
//    uint32_t log2min = log2i(minDim);
//    return (1 << log2min);
//}
//
//constexpr uint32_t log2i_size(uint32_t width, uint32_t height, uint32_t maxLevel) noexcept {
//    uint32_t minDim = std::min(width, height);
//    uint32_t log2min = std::min(log2i(minDim), maxLevel);
//    return (1 << log2min);
//}

constexpr uint32_t mip_count(uint32_t width, uint32_t height) noexcept {
    return 1 + log2i(std::max(width, height));
}

constexpr uint32_t mip_border(uint32_t mipLevel) noexcept {
    return (1 << mipLevel) >> 1;
}

constexpr bool is_power_of_two(uint32_t x) noexcept {
    return x && ((x & (x - 1)) == 0);
}

}
