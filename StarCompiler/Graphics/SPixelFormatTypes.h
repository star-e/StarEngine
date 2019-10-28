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
#include <StarCompiler/Graphics/SPixelFormatFwd.h>

namespace Star {

namespace Graphics {

struct Unknown_ {} constexpr Unknown;
struct RGBA_ {} constexpr RGBA;
struct BGRA_ {} constexpr BGRA;
struct ABGR_ {} constexpr ABGR;
struct ARGB_ {} constexpr ARGB;
struct RGBE_ {} constexpr RGBE;
struct D_S_ {} constexpr D_S;
struct D_X_ {} constexpr D_X;
struct D_ {} constexpr D;
struct S_ {} constexpr S;
struct X_S_ {} constexpr X_S;
struct BC_ {} constexpr BC;
struct ETC2_ {} constexpr ETC2;
struct EAC_ {} constexpr EAC;
struct ASTC_ {} constexpr ASTC;
struct RGBG_ {} constexpr RGBG;
struct GBGR_ {} constexpr GBGR;
struct GRGB_ {} constexpr GRGB;
struct BGRG_ {} constexpr BGRG;
struct G_B_R_ {} constexpr G_B_R;
struct G_BR_ {} constexpr G_BR;
struct PVRTC_ {} constexpr PVRTC;

using PixelLayout = std::variant<Unknown_, RGBA_, BGRA_, ABGR_, ARGB_, RGBE_, D_S_, D_X_, X_S_, D_, S_, BC_, ETC2_, EAC_, ASTC_, RGBG_, GBGR_, GRGB_, BGRG_, G_B_R_, G_BR_, PVRTC_>;

inline bool operator==(const PixelLayout& lhs, const PixelLayout& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const PixelLayout& lhs, const PixelLayout& rhs) noexcept {
    return !(lhs == rhs);
}

struct Typeless_ {} constexpr Typeless;
struct UNorm_ {} constexpr UNorm;
struct SNorm_ {} constexpr SNorm;
struct UScaled_ {} constexpr UScaled;
struct SScaled_ {} constexpr SScaled;
struct UInt_ {} constexpr UInt;
struct SInt_ {} constexpr SInt;
struct SRGB_ {} constexpr SRGB;
struct XRBias_ {} constexpr XRBias;
struct UFloat_ {} constexpr UFloat;
struct SFloat_ {} constexpr SFloat;
struct Double_ {} constexpr Double;

using PixelModel = std::variant<Typeless_, UNorm_, SNorm_, UScaled_, SScaled_, UInt_, SInt_, SRGB_, XRBias_, UFloat_, SFloat_, Double_>;

inline bool operator<(const PixelModel& lhs, const PixelModel& rhs) noexcept {
    return lhs.index() < rhs.index();
}

inline bool operator==(const PixelModel& lhs, const PixelModel& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const PixelModel& lhs, const PixelModel& rhs) noexcept {
    return !(lhs == rhs);
}

struct Interleaved {
    fixed4 mChannels = {};
};

struct Planar {
    fixed4 mChannels = {};
};

using PixelMemoryLayout = std::variant<Interleaved, Planar>;

struct Uniform {
    uint8_t mCount = 0;
    uint8_t mBitSize = 0;
};

struct Unspecified {};

struct Pack {
    uint8_t mCount = 0;
    uint8_t mBitSize = 0;
};

struct Block {
    uint8_t mVersion = 0;
    uint8_t mBPP = 0;
};

struct Adaptive {
    uint8_t mWidth = 0;
    uint8_t mHeight = 0;
};

using PixelPacking = std::variant<Uniform, Unspecified, Pack, Block, Adaptive>;

struct J444_ {} constexpr J444;
struct J422_ {} constexpr J422;
struct J420_ {} constexpr J420;

using PixelSubSampling = std::variant<std::monostate, J444_, J422_, J420_>;

struct Video_ {} constexpr Video;
struct IMG_ {} constexpr IMG;

using PixelUsage = std::variant<std::monostate, Video_, IMG_>;

struct PixelFormat {
    PixelLayout mLayout;
    PixelModel mModel;
    PixelMemoryLayout mMemoryLayout;
    PixelSubSampling mSubSampling;
    PixelPacking mPacking;
    PixelUsage mUsage;
};

struct PixelEncoding {
    uint32_t mBPE = 0;
    uint32_t mBlockWidth = 0;
    uint32_t mBlockHeight = 0;
};

struct SIZING_Y_UV_420_ {} constexpr SIZING_Y_UV_420;

using TextureSizing = std::variant<std::monostate, SIZING_Y_UV_420_>;

} // namespace Graphics

} // namespace Star
