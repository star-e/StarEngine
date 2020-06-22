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

#include "SAssetTexture.h"
#include <Star/Graphics/STextureUtils.h>
#include <Star/Graphics/SRenderFormat.h>
#include <Star/Graphics/SRenderFormatUtils.h>
#include <Star/Graphics/SRenderFormatDXGI.h>
#include <Star/Graphics/SRenderFormatTextureUtils.h>
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4275)
#pragma warning(disable:5040)
#include <Star/SGIL.h>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/io/targa.hpp>
#pragma warning(pop)
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <3rdparty/DXTCompressor/DXTCompressorDLL.h>
#include <Star/SAlignedBuffer.h>
#include <StarCompiler/Graphics/SRenderFormatNames.h>
#include <DirectXTex.h>
#include <Star/SStreamUtils.h>

namespace Star::Asset {

using namespace Graphics::Render;
using namespace boost;
using namespace boost::gil;

namespace {

template<class Tag>
void readImageInfo(std::istream& is, RESOURCE_DESC& desc) {
    Expects(is);

    const auto& img = read_image_info(is, Tag())._info;

    desc.mDimension = RESOURCE_DIMENSION_TEXTURE2D;
    desc.mAlignment = 0u;
    desc.mWidth = img._width;
    desc.mHeight = img._height;
    desc.mDepthOrArraySize = 1u;
    desc.mMipLevels = 1;
    desc.mFormat = Format::S_R8G8B8A8_UNORM;
    desc.mSampleDesc = { 1u, 0u };
    desc.mLayout = TEXTURE_LAYOUT_UNKNOWN;
    desc.mFlags = {};

    is.seekg(0);
}

// see https://www.khronos.org/opengl/wiki/S3_Texture_Compression
// For non-power-of-two images that aren't a multiple of 4 in size,
// the other colors of the 4x4 block are taken to be black.
// Each 4x4 block is independent of any other, so it can be decompressed independently.
template<class DstPixel>
void generateImageMipMaps(std::byte* dstBuffer, uint32_t width, uint32_t height,
    const uint32_t BlockX, const uint32_t BlockY,
    const size_t AlignX, uint32_t mipCount
) {
    Expects(mipCount > 0);

    size_t offset = 0;
    const uint32_t BPE = sizeof(DstPixel) * BlockX * BlockY;
    for (uint32_t k = 1; k != mipCount; ++k) {
        uint32_t width1 = boost::alignment::align_up(width, BlockX);
        uint32_t height1 = boost::alignment::align_up(height, BlockY);

        size_t rowAlignment = width1 * sizeof(DstPixel);
        auto srcView = interleaved_view(width, height, (const DstPixel*)(dstBuffer + offset), rowAlignment);

        offset += mip_size(width, height, BlockX, BlockY, BPE);
        Ensures(offset % AlignX == 0);

        width = half_size(width);
        height = half_size(height);

        uint32_t width2 = boost::alignment::align_up(width, BlockX);
        uint32_t height2 = boost::alignment::align_up(height, BlockY);

        rowAlignment = width2 * sizeof(DstPixel);

        auto dstView = interleaved_view(width, height, (DstPixel*)(dstBuffer + offset), rowAlignment);
        resize_view(srcView, dstView, boost::gil::bilinear_sampler());

        if (width2 == width && height2 == height) {
            continue;
        }

        std::array<float, num_channels<DstPixel>::value> acc{};

        float count = 0.0f;
        for_each_pixel(dstView, [&](const DstPixel& pixel) {
            for (size_t k = 0; k != num_channels<DstPixel>::value; ++k) {
                acc[k] += pixel[k];
            }
            count += 1.0f;
        });

        DstPixel avg;
        for (size_t k = 0; k != num_channels<DstPixel>::value; ++k) {
            avg[k] = boost::numeric_cast<typename channel_type<DstPixel>::type>(acc[k] / count);
        }

        auto dstView2 = interleaved_view(width2, height2, (DstPixel*)(dstBuffer + offset), rowAlignment);
        for (uint32_t i = 0; i != height2; ++i) {
            for (uint32_t j = 0; j != width2; ++j) {
                if (i < height && j < width)
                    continue;
                dstView2(j, i) = avg;
            }
        }
    }
    Ensures(width == 1 && height == 1);
}

template<class Tag, class SrcPixel, size_t AlignX>
void prepareTextureForCompression(std::istream& is, uint32_t width, uint32_t height,
    const uint32_t BlockX, const uint32_t BlockY, uint32_t mipCount, AlignedBuffer<AlignX>& buffer,
    bool generateMipMaps = true,
    bool flipY = true
) {
    auto bpe = gsl::narrow_cast<uint32_t>(sizeof(SrcPixel)) * BlockX * BlockY;
    size_t bufferSize;
    if (generateMipMaps) {
        bufferSize = texture_size(width, height, BlockX, BlockY, bpe);
    } else {
        bufferSize = mip_size(width, height, BlockX, BlockY, bpe);
    }
    buffer.resize_aligned(bufferSize);
    size_t rowAlignment = boost::alignment::align_up(width, BlockX) * sizeof(SrcPixel);
    Expects(rowAlignment % AlignX == 0);

    // first slice
    if (flipY) {
        auto texView = flipped_up_down_view(interleaved_view(width, height, reinterpret_cast<SrcPixel*>(buffer.data()), rowAlignment));
        // read and flip image
        read_and_convert_view(is, texView, Tag());
    } else {
        auto texView = interleaved_view(width, height, reinterpret_cast<SrcPixel*>(buffer.data()), rowAlignment);
        // read and flip image
        read_and_convert_view(is, texView, Tag());
    }

    if (generateMipMaps) {
        generateImageMipMaps<SrcPixel>(buffer.data(), width, height,
            BlockX, BlockY, AlignX, mipCount);
    }
}

template<class Tag, class SrcPixel>
void loadImage(std::istream& is, std::pmr::memory_resource* mr,
    uint32_t width, uint32_t height,
    uint32_t BlockX, uint32_t BlockY,
    const Asset::TextureImportSettings& info, TextureData& tex
) {
    // dst desc
    tex.mDesc.mDimension = RESOURCE_DIMENSION_TEXTURE2D;
    tex.mDesc.mAlignment = 0u;
    tex.mDesc.mWidth = width;
    tex.mDesc.mHeight = height;
    tex.mDesc.mDepthOrArraySize = 1u;
    tex.mDesc.mMipLevels = 1;
    tex.mDesc.mFormat = info.mFormat;
    tex.mDesc.mSampleDesc = { 1u, 0u };
    tex.mDesc.mLayout = TEXTURE_LAYOUT_UNKNOWN;
    tex.mDesc.mFlags = {};
    tex.mFormat = info.mFormat;

    // src
    uint32_t mipCount = mip_count(boost::alignment::align_up(width, BlockX), boost::alignment::align_up(height, BlockY));
    uint32_t srcBPE = sizeof(SrcPixel) * BlockX * BlockY;

    const int AlignX = 16;
    AlignedBuffer<16> buffer(mr);
    prepareTextureForCompression<Tag, SrcPixel>(is, width, height, BlockX, BlockY, mipCount, buffer,
        info.mGenerateMipMaps, info.mFlipY);

    auto [dstBPE, blockX, blockY] = getEncoding(info.mFormat);
    Expects(blockX == BlockX);
    Expects(blockY == BlockY);
    if (info.mGenerateMipMaps) {
        auto sz = getTextureSize(info.mFormat, width, height);
        auto sz1 = texture_size(width, height, blockX, blockY, dstBPE);
        Expects(sz == sz1);
        tex.mBuffer.resize_aligned(sz);
        tex.mDesc.mMipLevels = mipCount;
    } else {
        auto sz = getMipSize(info.mFormat, width, height);
        auto sz1 = mip_size(width, height, blockX, blockY, dstBPE);
        tex.mBuffer.resize_aligned(sz);
    }

    size_t srcOffset = 0;
    size_t dstOffset = 0;
    auto w = width;
    auto h = height;

    // convert to target texture
    switch (info.mFormat) {
    case Format::BC1_UNORM_BLOCK:
    case Format::BC1_SRGB_BLOCK:
    case Format::BC1_TYPELESS_BLOCK:
    {
        for (int k = 0; k != tex.mDesc.mMipLevels; ++k) {
            auto wa = boost::alignment::align_up(w, blockX);
            auto ha = boost::alignment::align_up(h, blockY);
            if (wa > blockX && ha > blockY) {
                DXTC::CompressImageDXT1SSE2(
                    reinterpret_cast<const uint8_t*>(buffer.data() + srcOffset),
                    reinterpret_cast<uint8_t*>(tex.mBuffer.data() + dstOffset),
                    wa, ha);
            } else {
                DXTC::CompressImageDXT1(
                    reinterpret_cast<const uint8_t*>(buffer.data() + srcOffset),
                    reinterpret_cast<uint8_t*>(tex.mBuffer.data() + dstOffset),
                    wa, ha);
            }
            srcOffset += mip_size(w, h, BlockX, BlockY, srcBPE);
            dstOffset += mip_size(w, h, blockX, blockY, dstBPE);
            w = half_size(w);
            h = half_size(h);
        }
    }
    break;
    case Format::BC3_UNORM_BLOCK:
    case Format::BC3_SRGB_BLOCK:
    case Format::BC3_TYPELESS_BLOCK:
    {
        for (int k = 0; k != tex.mDesc.mMipLevels; ++k) {
            DXTC::CompressImageDXT5SSE2(
                reinterpret_cast<const uint8_t*>(buffer.data() + srcOffset),
                reinterpret_cast<uint8_t*>(tex.mBuffer.data() + dstOffset),
                boost::alignment::align_up(w, blockX), boost::alignment::align_up(h, blockY));
            srcOffset += mip_size(w, h, BlockX, BlockY, srcBPE);
            dstOffset += mip_size(w, h, blockX, blockX, dstBPE);
            w = half_size(w);
            h = half_size(h);
        }
    }
    break;
    case Format::UNKNOWN:
    default:
        S_ERROR << "Format not supported" << getName(info.mFormat) << std::endl;
        throw std::invalid_argument("Format not supported");
    }
}

}

uint32_t getNumChannelsPNG(std::istream& is) {
    const auto& img = read_image_info(is, png_tag())._info;
    return img._num_channels;
}

bool isAlphaTestPNG(std::istream& is) {
    const auto& img = read_image_info(is, png_tag())._info;
    is.seekg(0);

    if (img._num_channels < 4)
        return false;

    rgba8_image_t im;
    read_image(is, im, png_tag());

    uint32_t whiteCount = 0;
    uint32_t blackCount = 0;
    auto imv = const_view(im);
    for (uint32_t i = 0; i != imv.height(); ++i) {
        for (uint32_t j = 0; j != imv.width(); ++j) {
            auto alpha = imv(j, i)[3];
            if (alpha == 255) {
                ++whiteCount;
            } else if (alpha == 0) {
                ++blackCount;
            }
        }
    }

    bool alphaTest = true;
    if (whiteCount == imv.height() * imv.width() ||
        blackCount == imv.height() * imv.width())
    {
        alphaTest = false;
    }
    
    return alphaTest;
}

void loadPNG(std::istream& is, std::pmr::memory_resource* mr, const TextureImportSettings& settings, TextureData& tex) {
    const auto& img = read_image_info(is, png_tag())._info;
    is.seekg(0);

    if (settings.mFormat == Format::UNKNOWN) {
        if (img._bit_depth != 8) {
            throw std::runtime_error("png only support 8 bit depth");
        }
        auto info = settings;
        if (img._num_channels < 4) {
            info.mFormat = Format::S_BC1_SRGB_BLOCK;
        } else {
            info.mFormat = Format::S_BC3_SRGB_BLOCK;
        }
        loadImage<png_tag, rgba8_pixel_t>(is, mr,
            gsl::narrow_cast<uint32_t>(img._width),
            gsl::narrow_cast<uint32_t>(img._height),
            4, 4, info, tex);
    }
}

void loadTGA(std::istream& is, std::pmr::memory_resource* mr, const TextureImportSettings& settings, TextureData& tex) {
    throw std::runtime_error("tga not supported yet");
}

namespace {

struct DDS_PIXELFORMAT {
    uint32_t    size;
    uint32_t    flags;
    uint32_t    fourCC;
    uint32_t    RGBBitCount;
    uint32_t    RBitMask;
    uint32_t    GBitMask;
    uint32_t    BBitMask;
    uint32_t    ABitMask;
};

struct DDS_HEADER {
    uint32_t        size;
    uint32_t        flags;
    uint32_t        height;
    uint32_t        width;
    uint32_t        pitchOrLinearSize;
    uint32_t        depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
    uint32_t        mipMapCount;
    uint32_t        reserved1[11];
    DDS_PIXELFORMAT ddspf;
    uint32_t        caps;
    uint32_t        caps2;
    uint32_t        caps3;
    uint32_t        caps4;
    uint32_t        reserved2;
};

}

void loadDDS(std::istream& is, std::pmr::memory_resource* mr, Graphics::Render::TextureData& tex, bool bSrgb) {
    std::array<char, 4> fourcc;
    read_data(is, fourcc);

    DDS_HEADER header;
    read_data(is, header);

    memcpy(fourcc.data(), &header.ddspf.fourCC, sizeof(fourcc));

    std::array<char, 4> dxt1{ 'D', 'X', 'T', '1' };
    std::array<char, 4> dxt5{ 'D', 'X', 'T', '5' };

    auto& desc = tex.mDesc;

    if (memcmp(fourcc.data(), dxt1.data(), 4) == 0) {
        desc.mDimension = Graphics::Render::RESOURCE_DIMENSION_TEXTURE2D;
        desc.mAlignment = 0;
        desc.mWidth = header.width;
        desc.mHeight = header.height;
        desc.mDepthOrArraySize = header.depth;
        desc.mMipLevels = header.mipMapCount;
        desc.mFormat = Graphics::Render::Format::BC1_TYPELESS_BLOCK;
        if (bSrgb) {
            tex.mFormat = makeTypelessSRGB(desc.mFormat);
        } else {
            tex.mFormat = makeTypelessUNorm(desc.mFormat);
        }
    } else if (memcmp(fourcc.data(), dxt5.data(), 4) == 0) {
        desc.mDimension = Graphics::Render::RESOURCE_DIMENSION_TEXTURE2D;
        desc.mAlignment = 0;
        desc.mWidth = header.width;
        desc.mHeight = header.height;
        desc.mDepthOrArraySize = header.depth;
        desc.mMipLevels = header.mipMapCount;
        desc.mFormat = Graphics::Render::Format::BC3_TYPELESS_BLOCK;
        if (bSrgb) {
            tex.mFormat = makeTypelessSRGB(desc.mFormat);
        } else {
            tex.mFormat = makeTypelessUNorm(desc.mFormat);
        }
    } else {
        throw std::runtime_error("dds file not found");
    }
    desc.mSampleDesc = { 1, 0 };

    auto uploadSize = Graphics::Render::getTextureUploadSize(desc.mFormat,
        gsl::narrow_cast<uint32_t>(desc.mWidth), gsl::narrow_cast<uint32_t>(desc.mHeight));
    tex.mBuffer.resize_aligned(uploadSize);
    
    auto width = gsl::narrow_cast<uint32_t>(desc.mWidth);
    auto height = gsl::narrow_cast<uint32_t>(desc.mHeight);
    int64_t readCount = 0;
    char* dstSliceBuffer = reinterpret_cast<char*>(tex.mBuffer.data());

    for (int k = 0; k != desc.mMipLevels; ++k) {
        auto [rowCount, rowPitch, uploadRowPitch, sliceSize, alignedSliceSize, uploadSliceSize] = getMipInfo(desc.mFormat, width, height);

        auto dstPitchBuffer = dstSliceBuffer;
        for (int i = 0; i != rowCount; ++i) {
            is.read(dstPitchBuffer, rowPitch);
            readCount += rowPitch;
            dstPitchBuffer += uploadRowPitch;
        }

        width = half_size(width);
        height = half_size(height);
        dstSliceBuffer += uploadSliceSize;
    }

    auto texSize = getTextureSize(desc.mFormat,
        gsl::narrow_cast<uint32_t>(desc.mWidth), gsl::narrow_cast<uint32_t>(desc.mHeight));

    if (desc.mFormat == Graphics::Render::Format::BC1_TYPELESS_BLOCK ||
        desc.mFormat == Graphics::Render::Format::BC1_UNORM_BLOCK ||
        desc.mFormat == Graphics::Render::Format::BC1_SRGB_BLOCK) {
        Expects(boost::alignment::align_up(readCount, 8) == texSize);
    } else {
        Expects(boost::alignment::align_up(readCount, 16) == texSize);
    }

    auto texUploadSize = getTextureUploadSize(desc.mFormat,
        gsl::narrow_cast<uint32_t>(desc.mWidth), gsl::narrow_cast<uint32_t>(desc.mHeight));
    auto diff = dstSliceBuffer - reinterpret_cast<char*>(tex.mBuffer.data());
    Ensures(diff == texUploadSize);
}

void saveDDS(std::ostream& os, const Graphics::Render::TextureData& tex0) {
    const auto& tex = tex0.mDesc;
    switch (tex.mDimension) {
    case RESOURCE_DIMENSION_TEXTURE1D:
    case RESOURCE_DIMENSION_TEXTURE2D:
    {
        int sz = tex.mDepthOrArraySize * tex.mMipLevels;
        
        auto formatS = makeTypeless(tex.mFormat);
        formatS = makeTypelessUNorm(formatS);
        DXGI_FORMAT format = getDXGIFormat(formatS);

        std::vector<DirectX::Image> images(sz);

        DirectX::TexMetadata meta;
        meta.width = tex.mWidth;
        meta.height = tex.mHeight;
        meta.depth = 1;
        meta.arraySize = tex.mDepthOrArraySize;
        meta.mipLevels = tex.mMipLevels;
        meta.miscFlags = 0;
        meta.miscFlags2 = 0;
        meta.format = format;
        meta.dimension = (DirectX::TEX_DIMENSION)tex.mDimension;

        int index = 0;
        int64_t offset = 0;
        for (int k = 0; k != tex.mDepthOrArraySize; ++k) {
            auto width = gsl::narrow_cast<uint32_t>(tex.mWidth);
            auto height = gsl::narrow_cast<uint32_t>(tex.mHeight);
            for (int l = 0; l != tex.mMipLevels; ++l, ++index) {
                auto [rowCount, rowPitch, uploadRowPitch, sliceSize, alignedSliceSize, uploadSliceSize] = getMipInfo(tex.mFormat, width, height);
                auto& im = images[index];
                im.format = format;
                im.width = width;
                im.height = height;
                im.rowPitch = rowPitch;
                im.slicePitch = sliceSize;
                im.pixels = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(tex0.mBuffer.data())) + offset;
                offset += im.slicePitch;

                width = half_size(width);
                height = half_size(height);
            }
        }

        DirectX::Blob blob;
        HRESULT hr = DirectX::SaveToDDSMemory(reinterpret_cast<const DirectX::Image*>(images.data()),
            images.size(), meta, DirectX::DDS_FLAGS_NONE, blob);

        if (hr) {
            S_ERROR << "Save DDS File :failed" << std::endl;
        }

        os.write(static_cast<const char*>(blob.GetBufferPointer()), blob.GetBufferSize());
    }
        break;
    case RESOURCE_DIMENSION_TEXTURE3D:
        break;
    }
}

}
