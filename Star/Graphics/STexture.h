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
#include <Star/Core0/SConfig.h>
#include <Star/Graphics/SRenderFormat.h>
#include <Star/Graphics/SRenderTypes.h>
#include <Star/Graphics/STextureUtils.h>
#include <boost/iterator/iterator_facade.hpp>

namespace Star {

namespace Graphics {

struct MipSize {
    static const uint32_t sPitchAlignment = 256;
    static const uint32_t sSliceAlignment = 512;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mRowCount;
    uint32_t mPitchSize;
    uint64_t mSliceSize;
    uint32_t mUploadPitchSize;
    uint64_t mUploadSliceSize;
};

struct TextureSize {
    uint64_t mBufferSize;
    uint64_t mUploadSize;
};

class alignas(16) TextureInfo {
public:
    MipSize STAR_CORE_API getMipSize(uint32_t width, uint32_t height) const noexcept;
    TextureSize STAR_CORE_API getTextureSize() const noexcept;

    struct MipDesc {
        Render::Format mFormat;
        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mDepth;
        uint32_t mRowPitch;
    };

    class UploadMipIterator : public boost::iterator_facade< UploadMipIterator,
        std::pair<uint64_t, MipDesc>,
        boost::forward_traversal_tag,
        std::pair<uint64_t, MipDesc>
    > {
    public:
        UploadMipIterator() noexcept = default;
        UploadMipIterator(const TextureInfo& info) noexcept
            : mInfo(&info)
            , mWidth(info.mWidth)
            , mHeight(info.mHeight)
        {
        }
    private:
        friend class boost::iterator_core_access;

        void increment() noexcept {
            auto mip = mInfo->getMipSize(mWidth, mHeight);
            mOffset += mip.mUploadSliceSize;

            if (mWidth == 1 && mHeight == 1) {
                mWidth = 0;
                mHeight = 0;
            } else {
                mWidth = half_size(mWidth);
                mHeight = half_size(mHeight);
            }
        }

        bool equal(const UploadMipIterator& other) const noexcept {
            return mWidth == other.mWidth && mHeight == other.mHeight;
        }

        std::pair<uint64_t, MipDesc> dereference() const noexcept {
            auto mip = mInfo->getMipSize(mWidth, mHeight);
            return std::pair(mOffset,
                MipDesc{
                    mInfo->mFormat,
                    mip.mWidth, mip.mHeight, mInfo->mDepth,
                    mip.mUploadPitchSize
                }
            );
        }

        const TextureInfo* mInfo = nullptr;
        uint64_t mOffset = 0;
        uint32_t mWidth = 0;
        uint32_t mHeight = 0;
    };

    typedef UploadMipIterator const_iterator;

    const_iterator begin() const noexcept {
        return const_iterator(*this);
    }
    const_iterator end() const noexcept {
        return const_iterator();
    }

    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mDepth;
    uint16_t mArraySize;
    uint16_t mMipLevels;
    uint32_t mMiscFlags;
    uint32_t mMiscFlags2;
    Render::Format mFormat;
    Render::RESOURCE_DIMENSION mDimension;
};

static_assert(sizeof(TextureInfo) == 4 * 8);

}

}
