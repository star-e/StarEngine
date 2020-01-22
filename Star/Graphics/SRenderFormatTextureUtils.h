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
#include <Star/Graphics/SConfig.h>
#include <Star/Graphics/SRenderFormat.h>
#include <Star/Graphics/STextureUtils.h>

namespace Star::Graphics::Render {

static constexpr uint32_t sPitchAlignment = 256u;
static constexpr uint32_t sSliceAlignment = 512u;

struct Encoding {
    uint32_t mBPE;
    uint32_t mBlockWidth;
    uint32_t mBlockHeight;
};

struct MipInfo {
    uint32_t mRowCount;
    uint32_t mRowPitchSize;
    uint32_t mUploadRowPitchSize;
    uint64_t mSliceSize; // mRowCount * mRowPitchSize
    uint64_t mRowAlignedSliceSize; // mRowCount * align_up(mRowPitchSize, UploadRowPitchSize)
    uint64_t mUploadSliceSize; // align_up(mRowAlignedSliceSize, UploadRowSliceSize)
};

STAR_GRAPHICS_API Encoding getEncoding(Format format) noexcept;
STAR_GRAPHICS_API MipInfo getMipInfo(Format format, uint32_t width, uint32_t height) noexcept;

STAR_GRAPHICS_API uint64_t getMipSize(Format format, uint32_t width, uint32_t height) noexcept;
STAR_GRAPHICS_API uint64_t getMipUploadSize(Format format, uint32_t width, uint32_t height) noexcept;

STAR_GRAPHICS_API uint64_t getTextureSize(Format format, uint32_t width, uint32_t height) noexcept;
STAR_GRAPHICS_API uint64_t getTextureUploadSize(Format format, uint32_t width, uint32_t height) noexcept;

}
