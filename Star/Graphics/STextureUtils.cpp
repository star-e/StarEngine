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

#include "STextureUtils.h"

namespace Star {

static_assert(mip_border(0) == 0, "border size of miplevel 0 is 0");
static_assert(mip_border(1) == 1, "border size of miplevel 1 is 1");
static_assert(mip_border(2) == 2, "border size of miplevel 2 is 2");
static_assert(mip_border(3) == 4, "border size of miplevel 3 is 4");

static_assert(!is_power_of_two(0), "is_power_of_two incorrect");
static_assert(is_power_of_two(1), "is_power_of_two incorrect");
static_assert(is_power_of_two(2), "is_power_of_two incorrect");
static_assert(!is_power_of_two(3), "is_power_of_two incorrect");

static_assert(half_size(1u), "half_size of 1 should be 1");
static_assert(half_size(2u), "half_size of 2 should be 1");
static_assert(half_size(3u), "half_size of 3 should be 1");

static_assert(block_count(0, 4) == 0, "aligned_pixel_count<4> of 0 should be 0");
static_assert(block_count(1, 4) == 1, "aligned_pixel_count<4> of 1 should be 4");
static_assert(block_count(3, 4) == 1, "aligned_pixel_count<4> of 3 should be 4");
static_assert(block_count(4, 4) == 1, "aligned_pixel_count<4> of 4 should be 4");
static_assert(block_count(5, 4) == 2, "aligned_pixel_count<4> of 5 should be 8");

static_assert(block_count(0, 1) == 0, "block_count<4> of 0 should be 0");
static_assert(block_count(1, 1) == 1, "block_count<4> of 1 should be 1");
static_assert(block_count(2, 1) == 2, "block_count<4> of 2 should be 2");
static_assert(block_count(3, 1) == 3, "block_count<4> of 3 should be 3");
static_assert(block_count(4, 1) == 4, "block_count<4> of 4 should be 4");
static_assert(block_count(5, 1) == 5, "block_count<4> of 5 should be 5");

static_assert(aligned_pixel_count(0, 4) == 0, "aligned_pixel_count<4> of 0 should be 0");
static_assert(aligned_pixel_count(1, 4) == 4, "aligned_pixel_count<4> of 1 should be 4");
static_assert(aligned_pixel_count(3, 4) == 4, "aligned_pixel_count<4> of 3 should be 4");
static_assert(aligned_pixel_count(4, 4) == 4, "aligned_pixel_count<4> of 4 should be 4");
static_assert(aligned_pixel_count(5, 4) == 8, "aligned_pixel_count<4> of 5 should be 8");

// dxt5 
static_assert(mip_size(1, 1, 4, 4, 16) == 16, "dxt5 mip_size<8, 4> of 1x1 should be 16");
static_assert(mip_size(1, 1, 4, 4, 8) == 8, "dxt1 mip_size<4, 4> of 1x1 should be 8");

static_assert(mip_size(1, 1, 4, 4, 8, 256) == 256, "dxt1 mip_size<4, 4> of 1x1 should be 8");

static_assert(mip_size(2, 2, 4, 4, 16) == 16, "dxt5 mip_size<8, 4> of 2x2 should be 16");
static_assert(mip_size(2, 2, 4, 4, 8) == 8, "dxt1 mip_size<4, 4> of 2x2 should be 8");

static_assert(mip_size(4, 4, 4, 4, 16) == 16, "dxt5 mip_size<8, 4> of 4x4 should be 16");
static_assert(mip_size(4, 4, 4, 4, 8) == 8, "dxt1 mip_size<4, 4> of 4x4 should be 8");
static_assert(mip_size(5, 5, 4, 4, 8) == 32);

static_assert(mip_size(1, 1, 1, 1, 4) == 4, "dxt5 mip_size<32, 1> of 1x1 should be 4");
static_assert(mip_size(2, 2, 1, 1, 4) == 16, "dxt5 mip_size<32, 1> of 2x2 should be 16");
static_assert(mip_size(4, 4, 1, 1, 4) == 64, "dxt5 mip_size<32, 1> of 4x4 should be 64");

static_assert(texture_size(1, 1, 4, 4, 8) == 8);
static_assert(texture_size(2, 2, 4, 4, 8) == 16);
static_assert(texture_size(3, 3, 4, 4, 8) == 16);
static_assert(texture_size(4, 4, 4, 4, 8) == 24);
static_assert(texture_size(5, 5, 4, 4, 8) == 48); // 5x5(8x8) -> 2x2(4x4) -> 1x1(4x4)
static_assert(texture_size(8, 8, 4, 4, 8) == 56); // 8x8(8x8) -> 4x4(4x4)-> 2x2(4x4) -> 1x1(4x4)

}
