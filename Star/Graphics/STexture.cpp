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

#include "STexture.h"
#include "SRenderFormat.h"
#include "SRenderFormatUtils.h"
#include "SRenderFormatDXGI.h"
#include "SRenderFormatTextureUtils.h"
#include "STextureUtils.h"
#include <gsl/gsl_util>
#include <dxgiformat.h>

namespace Star {

namespace Graphics {

using boost::alignment::align_up;
using namespace Render;

inline namespace {

void getFormatInfo(DXGI_FORMAT format, bool& bc, bool& packed, bool& planar, uint32_t& bpe) {
    switch (format) {
    case DXGI_FORMAT_BC1_TYPELESS:
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC1_UNORM_SRGB:
    case DXGI_FORMAT_BC4_TYPELESS:
    case DXGI_FORMAT_BC4_UNORM:
    case DXGI_FORMAT_BC4_SNORM:
        bc = true;
        bpe = 8;
        break;

    case DXGI_FORMAT_BC2_TYPELESS:
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC2_UNORM_SRGB:
    case DXGI_FORMAT_BC3_TYPELESS:
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC3_UNORM_SRGB:
    case DXGI_FORMAT_BC5_TYPELESS:
    case DXGI_FORMAT_BC5_UNORM:
    case DXGI_FORMAT_BC5_SNORM:
    case DXGI_FORMAT_BC6H_TYPELESS:
    case DXGI_FORMAT_BC6H_UF16:
    case DXGI_FORMAT_BC6H_SF16:
    case DXGI_FORMAT_BC7_TYPELESS:
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        bc = true;
        bpe = 16;
        break;

    case DXGI_FORMAT_R8G8_B8G8_UNORM:
    case DXGI_FORMAT_G8R8_G8B8_UNORM:
    case DXGI_FORMAT_YUY2:
        packed = true;
        bpe = 4;
        break;

    case DXGI_FORMAT_Y210:
    case DXGI_FORMAT_Y216:
        packed = true;
        bpe = 8;
        break;

    case DXGI_FORMAT_NV12:
    case DXGI_FORMAT_420_OPAQUE:
        planar = true;
        bpe = 2;
        break;

    case DXGI_FORMAT_P010:
    case DXGI_FORMAT_P016:
        planar = true;
        bpe = 4;
        break;
    }
}

MipSize getMipSize(DXGI_FORMAT format, uint32_t width, uint32_t height) noexcept {
    Expects(width > 0);
    Expects(height > 0);

    MipSize sz{};
    sz.mWidth = width;
    sz.mHeight = height;

    uint32_t numBytes = 0;
    uint32_t rowBytes = 0;
    uint32_t numRows = 0;

    bool bc = false;
    bool packed = false;
    bool planar = false;
    uint32_t bpe = 0;

    getFormatInfo(format, bc, packed, planar, bpe);

    static const uint32_t PITCH_ALIGNMENT = 256;
    static const uint32_t PLACEMENT_ALIGNMENT = 512;

    if (bc) {
        uint32_t numBlocksWide = 0;
        if (width > 0) {
            numBlocksWide = std::max(1u, (width + 3) / 4);
        }
        uint32_t numBlocksHigh = 0;
        if (height > 0) {
            numBlocksHigh = std::max(1u, (height + 3) / 4);
        }

        sz.mWidth = numBlocksWide * 4;
        sz.mHeight = numBlocksHigh * 4;

        rowBytes = numBlocksWide * bpe;
        numRows = numBlocksHigh;
        numBytes = rowBytes * numBlocksHigh;
    } else if (packed) {
        rowBytes = ((width + 1) >> 1) * bpe;
        sz.mWidth = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(sz.mWidth, 2));
        numRows = height;
        numBytes = rowBytes * height;
    } else if (format == DXGI_FORMAT_NV11) {
        rowBytes = ((width + 3) >> 2) * 4;
        sz.mWidth = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(sz.mWidth, 4));
        numRows = height * 2; // Direct3D makes this simplifying assumption, although it is larger than the 4:1:1 data
        numBytes = rowBytes * numRows;
    } else if (planar) {
        rowBytes = ((width + 1) >> 1) * bpe;
        sz.mWidth = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(sz.mWidth, 2));
        numBytes = (rowBytes * height) + ((rowBytes * height + 1) >> 1);
        numRows = height + ((height + 1) >> 1);
    } else {
        auto [bpe, blockWidth, blockHeight] = getEncoding(getRenderFormat(format));
        Expects(blockWidth == 1);
        Expects(blockHeight == 1);
        rowBytes = bpe * (width + blockWidth - 1) / blockWidth;
        numRows = (height + blockHeight - 1) / blockHeight;
        numBytes = rowBytes * numRows;
    }

    sz.mRowCount = numRows;
    sz.mPitchSize = rowBytes;
    sz.mSliceSize = numBytes;

    sz.mUploadPitchSize = gsl::narrow_cast<uint32_t>(align_up(rowBytes, PITCH_ALIGNMENT));
    sz.mUploadSliceSize = gsl::narrow_cast<uint32_t>(align_up(sz.mUploadPitchSize * numRows, PLACEMENT_ALIGNMENT));

    return sz;
}

TextureSize getTextureSize(DXGI_FORMAT format, uint32_t width, uint32_t height) noexcept {
    Expects(width > 0);
    Expects(height > 0);

    TextureSize sz{};

    bool bc = false;
    bool packed = false;
    bool planar = false;
    uint32_t bpe = 0;

    getFormatInfo(format, bc, packed, planar, bpe);

    static const uint32_t PITCH_ALIGNMENT = 256;
    static const uint32_t PLACEMENT_ALIGNMENT = 512;

    if (bc) { // BC
        Expects(bpe);
        sz.mBufferSize = texture_size(width, height, 4, 4, bpe);
        sz.mUploadSize = texture_size(width, height, 4, 4, bpe, PITCH_ALIGNMENT, PLACEMENT_ALIGNMENT);
    } else if (packed) { // YUYV
        Expects(bpe);
        sz.mBufferSize = texture_size(width, height, 2, 1, bpe);
        sz.mUploadSize = texture_size(width, height, 2, 1, bpe, PITCH_ALIGNMENT, PLACEMENT_ALIGNMENT);
    } else if (format == DXGI_FORMAT_NV11) { // 411
        sz.mBufferSize = texture_size(width, 2 * height, 4, 1, 4);
        sz.mUploadSize = texture_size(width, 2 * height, 4, 1, 4, PITCH_ALIGNMENT, PLACEMENT_ALIGNMENT);
    } else if (planar) { // 420, 12bit
        sz.mBufferSize = texture_size(width, height + ((height + 1) >> 1), 2, 1, bpe);
        sz.mUploadSize = texture_size(width, height + ((height + 1) >> 1), 2, 1, bpe, PITCH_ALIGNMENT, PLACEMENT_ALIGNMENT);
    } else {
        auto [bpe, blockWidth, blockHeight] = getEncoding(getRenderFormat(format));
        Expects(blockWidth == 1);
        Expects(blockHeight == 1);
        sz.mBufferSize = texture_size(width, height, blockWidth, blockHeight, bpe);
        sz.mUploadSize = texture_size(width, height, blockWidth, blockHeight, bpe, PITCH_ALIGNMENT, PLACEMENT_ALIGNMENT);
    }

    return sz;
}

}

MipSize TextureInfo::getMipSize(uint32_t width, uint32_t height) const noexcept {
    auto[bpe, blockX, blockY] = getEncoding(mFormat);
    auto[rowCount, rowPitch, uploadRowPitchSize, slice, rowAlignedSlice, uploadSliceSize] = getMipInfo(mFormat, width, height);
    width = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(width, blockX));
    height = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(height, blockY));
    auto uploadRowPitch = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(rowPitch, sPitchAlignment));
    Expects(uploadSliceSize == boost::alignment::align_up(rowAlignedSlice, sSliceAlignment));
    return MipSize{ width, height, rowCount, rowPitch, slice, uploadRowPitch, uploadSliceSize };
}

TextureSize TextureInfo::getTextureSize() const noexcept {
    auto slice = Render::getTextureSize(mFormat, mWidth, mHeight);
    auto upload = Render::getTextureUploadSize(mFormat, mWidth, mHeight);
#ifndef NDEGUG
    auto tex = ::Star::Graphics::getTextureSize(getDXGIFormat(mFormat), mWidth, mHeight);
    Ensures(tex.mBufferSize == slice);
    Ensures(tex.mUploadSize == upload);
#endif
    return { slice, upload };
}

}

}
