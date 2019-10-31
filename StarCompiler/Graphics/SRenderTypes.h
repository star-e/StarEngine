// Copyright (C) 2019 star.engine at outlook dot com
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
#include <StarCompiler/Graphics/SRenderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct CBV_ {} static constexpr CBV;
inline bool operator==(const CBV_&, const CBV_&) noexcept { return true; }
inline bool operator!=(const CBV_&, const CBV_&) noexcept { return false; }
inline bool operator<(const CBV_&, const CBV_&) noexcept { return false; }
struct UAV_ {} static constexpr UAV;
inline bool operator==(const UAV_&, const UAV_&) noexcept { return true; }
inline bool operator!=(const UAV_&, const UAV_&) noexcept { return false; }
inline bool operator<(const UAV_&, const UAV_&) noexcept { return false; }
struct SRV_ {} static constexpr SRV;
inline bool operator==(const SRV_&, const SRV_&) noexcept { return true; }
inline bool operator!=(const SRV_&, const SRV_&) noexcept { return false; }
inline bool operator<(const SRV_&, const SRV_&) noexcept { return false; }
struct SSV_ {} static constexpr SSV;
inline bool operator==(const SSV_&, const SSV_&) noexcept { return true; }
inline bool operator!=(const SSV_&, const SSV_&) noexcept { return false; }
inline bool operator<(const SSV_&, const SSV_&) noexcept { return false; }
struct RTV_ {} static constexpr RTV;
inline bool operator==(const RTV_&, const RTV_&) noexcept { return true; }
inline bool operator!=(const RTV_&, const RTV_&) noexcept { return false; }
inline bool operator<(const RTV_&, const RTV_&) noexcept { return false; }
struct DSV_ {} static constexpr DSV;
inline bool operator==(const DSV_&, const DSV_&) noexcept { return true; }
inline bool operator!=(const DSV_&, const DSV_&) noexcept { return false; }
inline bool operator<(const DSV_&, const DSV_&) noexcept { return false; }
struct IBV_ {} static constexpr IBV;
inline bool operator==(const IBV_&, const IBV_&) noexcept { return true; }
inline bool operator!=(const IBV_&, const IBV_&) noexcept { return false; }
inline bool operator<(const IBV_&, const IBV_&) noexcept { return false; }
struct VBV_ {} static constexpr VBV;
inline bool operator==(const VBV_&, const VBV_&) noexcept { return true; }
inline bool operator!=(const VBV_&, const VBV_&) noexcept { return false; }
inline bool operator<(const VBV_&, const VBV_&) noexcept { return false; }
struct SOV_ {} static constexpr SOV;
inline bool operator==(const SOV_&, const SOV_&) noexcept { return true; }
inline bool operator!=(const SOV_&, const SOV_&) noexcept { return false; }
inline bool operator<(const SOV_&, const SOV_&) noexcept { return false; }
struct BufferRaw_ {} static constexpr BufferRaw;
inline bool operator==(const BufferRaw_&, const BufferRaw_&) noexcept { return true; }
inline bool operator!=(const BufferRaw_&, const BufferRaw_&) noexcept { return false; }
inline bool operator<(const BufferRaw_&, const BufferRaw_&) noexcept { return false; }

using BufferFlag = std::variant<std::monostate, BufferRaw_>;

struct BufferView {
    uint64_t mFirstElement = 0;
    uint32_t mNumElements = 0;
    uint32_t mStructureByteStride = 0;
    BufferFlag mFlags;
};

inline bool operator==(const BufferView&lhs, const BufferView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstElement, lhs.mNumElements, lhs.mStructureByteStride, lhs.mFlags) ==
        std::forward_as_tuple(rhs.mFirstElement, rhs.mNumElements, rhs.mStructureByteStride, rhs.mFlags);
}
inline bool operator!=(const BufferView&lhs, const BufferView&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const BufferView&lhs, const BufferView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstElement, lhs.mNumElements, lhs.mStructureByteStride, lhs.mFlags) <
        std::forward_as_tuple(rhs.mFirstElement, rhs.mNumElements, rhs.mStructureByteStride, rhs.mFlags);
}

struct MipChainView {
    uint32_t mMostDetailedMip = 0;
    float mResourceMinLODClamp = 0;
};

inline bool operator==(const MipChainView&lhs, const MipChainView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMostDetailedMip, lhs.mResourceMinLODClamp) ==
        std::forward_as_tuple(rhs.mMostDetailedMip, rhs.mResourceMinLODClamp);
}
inline bool operator!=(const MipChainView&lhs, const MipChainView&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const MipChainView&lhs, const MipChainView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMostDetailedMip, lhs.mResourceMinLODClamp) <
        std::forward_as_tuple(rhs.mMostDetailedMip, rhs.mResourceMinLODClamp);
}

struct MipRangeView {
    uint32_t mMostDetailedMip = 0;
    uint32_t mMipLevels = 0;
    float mResourceMinLODClamp = 0;
};

inline bool operator==(const MipRangeView&lhs, const MipRangeView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMostDetailedMip, lhs.mMipLevels, lhs.mResourceMinLODClamp) ==
        std::forward_as_tuple(rhs.mMostDetailedMip, rhs.mMipLevels, rhs.mResourceMinLODClamp);
}
inline bool operator!=(const MipRangeView&lhs, const MipRangeView&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const MipRangeView&lhs, const MipRangeView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMostDetailedMip, lhs.mMipLevels, lhs.mResourceMinLODClamp) <
        std::forward_as_tuple(rhs.mMostDetailedMip, rhs.mMipLevels, rhs.mResourceMinLODClamp);
}

using MipView = std::variant<std::monostate, MipChainView, MipRangeView>;

struct PlaneSlice {
    uint32_t mPlaneSlice = 0;
};

inline bool operator==(const PlaneSlice&lhs, const PlaneSlice&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mPlaneSlice) ==
        std::forward_as_tuple(rhs.mPlaneSlice);
}
inline bool operator!=(const PlaneSlice&lhs, const PlaneSlice&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const PlaneSlice&lhs, const PlaneSlice&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mPlaneSlice) <
        std::forward_as_tuple(rhs.mPlaneSlice);
}

using PlaneView = std::variant<std::monostate, PlaneSlice>;

struct ArrayRange {
    uint32_t mFirstArraySlice = 0;
    uint32_t mArraySize = 0;
};

inline bool operator==(const ArrayRange&lhs, const ArrayRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstArraySlice, lhs.mArraySize) ==
        std::forward_as_tuple(rhs.mFirstArraySlice, rhs.mArraySize);
}
inline bool operator!=(const ArrayRange&lhs, const ArrayRange&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const ArrayRange&lhs, const ArrayRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstArraySlice, lhs.mArraySize) <
        std::forward_as_tuple(rhs.mFirstArraySlice, rhs.mArraySize);
}

struct DepthRange {
    uint32_t mFirstWSlice = 0;
    uint32_t mWSize = 0;
};

inline bool operator==(const DepthRange&lhs, const DepthRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstWSlice, lhs.mWSize) ==
        std::forward_as_tuple(rhs.mFirstWSlice, rhs.mWSize);
}
inline bool operator!=(const DepthRange&lhs, const DepthRange&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const DepthRange&lhs, const DepthRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirstWSlice, lhs.mWSize) <
        std::forward_as_tuple(rhs.mFirstWSlice, rhs.mWSize);
}

struct CubeSlice {};

inline bool operator==(const CubeSlice&lhs, const CubeSlice&rhs) noexcept {
    return
        std::forward_as_tuple() ==
        std::forward_as_tuple();
}
inline bool operator!=(const CubeSlice&lhs, const CubeSlice&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const CubeSlice&lhs, const CubeSlice&rhs) noexcept {
    return
        std::forward_as_tuple() <
        std::forward_as_tuple();
}

struct CubeRange {
    uint32_t mFirst2DArrayFace = 0;
    uint32_t mNumCubes = 0;
};

inline bool operator==(const CubeRange&lhs, const CubeRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirst2DArrayFace, lhs.mNumCubes) ==
        std::forward_as_tuple(rhs.mFirst2DArrayFace, rhs.mNumCubes);
}
inline bool operator!=(const CubeRange&lhs, const CubeRange&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const CubeRange&lhs, const CubeRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFirst2DArrayFace, lhs.mNumCubes) <
        std::forward_as_tuple(rhs.mFirst2DArrayFace, rhs.mNumCubes);
}

using ArrayOrDepthView = std::variant<std::monostate, ArrayRange, DepthRange, CubeSlice, CubeRange>;

struct TextureView {
    MipView mMipView;
    PlaneView mPlaneView;
    ArrayOrDepthView mArrayOrDepthView;
};

inline bool operator==(const TextureView&lhs, const TextureView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMipView, lhs.mPlaneView, lhs.mArrayOrDepthView) ==
        std::forward_as_tuple(rhs.mMipView, rhs.mPlaneView, rhs.mArrayOrDepthView);
}
inline bool operator!=(const TextureView&lhs, const TextureView&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const TextureView&lhs, const TextureView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMipView, lhs.mPlaneView, lhs.mArrayOrDepthView) <
        std::forward_as_tuple(rhs.mMipView, rhs.mPlaneView, rhs.mArrayOrDepthView);
}

struct RaytracingView {
    std::string mName;
};

inline bool operator==(const RaytracingView&lhs, const RaytracingView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName) ==
        std::forward_as_tuple(rhs.mName);
}
inline bool operator!=(const RaytracingView&lhs, const RaytracingView&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const RaytracingView&lhs, const RaytracingView&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName) <
        std::forward_as_tuple(rhs.mName);
}

using ResourceDataView = std::variant<BufferView, TextureView, RaytracingView>;

} // namespace Render

} // namespace Graphics

} // namespace Star
