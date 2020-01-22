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
#include <Star/Graphics/SRenderGraphFwd.h>
#include <Star/Graphics/SRenderTypes.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Star {

namespace Graphics {

namespace Render {

struct Linear_ {} static constexpr Linear;
struct Device_ {} static constexpr Device;

using ColorSpace = std::variant<Linear_, Device_>;

inline bool operator==(const ColorSpace& lhs, const ColorSpace& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const ColorSpace& lhs, const ColorSpace& rhs) noexcept {
    return !(lhs == rhs);
}

struct Load_ {} static constexpr Load;
inline bool operator==(const Load_&, const Load_&) noexcept { return true; }
inline bool operator!=(const Load_&, const Load_&) noexcept { return false; }
struct DontRead_ {} static constexpr DontRead;
inline bool operator==(const DontRead_&, const DontRead_&) noexcept { return true; }
inline bool operator!=(const DontRead_&, const DontRead_&) noexcept { return false; }
struct Store_ {} static constexpr Store;
inline bool operator==(const Store_&, const Store_&) noexcept { return true; }
inline bool operator!=(const Store_&, const Store_&) noexcept { return false; }
struct Discard_ {} static constexpr Discard;
inline bool operator==(const Discard_&, const Discard_&) noexcept { return true; }
inline bool operator!=(const Discard_&, const Discard_&) noexcept { return false; }

struct ClearColor {
    float4 mClearColor = float4::Zero();
    Format mClearFormat = Format::UNKNOWN;
};

inline bool operator==(const ClearColor&lhs, const ClearColor&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mClearColor, lhs.mClearFormat) ==
        std::forward_as_tuple(rhs.mClearColor, rhs.mClearFormat);
}
inline bool operator!=(const ClearColor&lhs, const ClearColor&rhs) noexcept {
    return !(lhs == rhs);
}

struct ClearDepthStencil {
    float mDepthClearValue = 1.0f;
    uint8_t mStencilClearValue = 0;
    uint8_t mClearDepth = 1;
    uint8_t mClearStencil = 1;
    uint8_t mUnused = 0;
    Format mClearFormat = Format::UNKNOWN;
};

inline bool operator==(const ClearDepthStencil&lhs, const ClearDepthStencil&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mDepthClearValue, lhs.mStencilClearValue, lhs.mClearDepth, lhs.mClearStencil, lhs.mUnused, lhs.mClearFormat) ==
        std::forward_as_tuple(rhs.mDepthClearValue, rhs.mStencilClearValue, rhs.mClearDepth, rhs.mClearStencil, rhs.mUnused, rhs.mClearFormat);
}
inline bool operator!=(const ClearDepthStencil&lhs, const ClearDepthStencil&rhs) noexcept {
    return !(lhs == rhs);
}

using OptimizedClearColor = std::variant<ClearColor, ClearDepthStencil>;
using LoadOp = std::variant<Load_, DontRead_, ClearColor, ClearDepthStencil>;
using StoreOp = std::variant<Store_, Discard_>;

struct FramebufferHandle {
    uint32_t mHandle = 0;
};

struct DescriptorHandle {
    uint32_t mHandle = 0;
};

struct Attachment {
    FramebufferHandle mFramebuffer;
    DescriptorHandle mDescriptor;
    StoreOp mStoreOp;
    LoadOp mLoadOp;
};

struct RenderViewTransition {
    FramebufferHandle mFramebuffer;
    RESOURCE_STATES mSource = {};
    RESOURCE_STATES mTarget = {};
};

struct STAR_GRAPHICS_API UnorderedRenderQueue {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    UnorderedRenderQueue(const allocator_type& alloc);
    UnorderedRenderQueue(UnorderedRenderQueue&& rhs, const allocator_type& alloc);
    UnorderedRenderQueue(UnorderedRenderQueue const& rhs, const allocator_type& alloc);
    ~UnorderedRenderQueue();

    std::pmr::vector<MetaID> mContents;
};

struct STAR_GRAPHICS_API RenderSubpass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderSubpass(const allocator_type& alloc);
    RenderSubpass(RenderSubpass&& rhs, const allocator_type& alloc);
    RenderSubpass(RenderSubpass const& rhs, const allocator_type& alloc);
    ~RenderSubpass();

    DISP_SAMPLE_DESC mSampleDesc;
    std::pmr::vector<Attachment> mInputAttachments;
    std::pmr::vector<Attachment> mOutputAttachments;
    std::pmr::vector<Attachment> mResolveAttachments;
    std::optional<Attachment> mDepthStencilAttachment;
    std::pmr::vector<Attachment> mPreserveAttachments;
    std::pmr::vector<Attachment> mSRVs;
    std::pmr::vector<Attachment> mUAVs;
    std::pmr::vector<RenderViewTransition> mPostViewTransitions;
    std::pmr::vector<UnorderedRenderQueue> mOrderedRenderQueue;
    std::pmr::string mRootSignature;
    ConstantBuffer mConstantBuffer;
};

struct RenderSubpassDependency {
    uint32_t mSrcSubpass = 0;
    uint32_t mDstSubpass = 0;
};

struct STAR_GRAPHICS_API RenderPass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderPass(const allocator_type& alloc);
    RenderPass(RenderPass&& rhs, const allocator_type& alloc);
    RenderPass(RenderPass const& rhs, const allocator_type& alloc);
    ~RenderPass();

    std::pmr::vector<VIEWPORT> mViewports;
    std::pmr::vector<RECT> mScissorRects;
    std::pmr::vector<FramebufferHandle> mFramebuffers;
    std::pmr::vector<RenderSubpass> mSubpasses;
    std::pmr::vector<RenderSubpassDependency> mDependencies;
};

struct RenderPassDependency {
    uint32_t mSrcPass = 0;
    uint32_t mDstPass = 0;
};

struct RenderSubpassDesc {
    uint32_t mPassID = 0;
    uint32_t mSubpassID = 0;
};

inline bool operator<(const RenderSubpassDesc&lhs, const RenderSubpassDesc&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mPassID, lhs.mSubpassID) <
        std::forward_as_tuple(rhs.mPassID, rhs.mSubpassID);
}

struct STAR_GRAPHICS_API RenderPipeline {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderPipeline(const allocator_type& alloc);
    RenderPipeline(RenderPipeline&& rhs, const allocator_type& alloc);
    RenderPipeline(RenderPipeline const& rhs, const allocator_type& alloc);
    ~RenderPipeline();

    std::pmr::vector<RenderPass> mPasses;
    std::pmr::vector<RenderPassDependency> mDependencies;
    std::pmr::vector<RESOURCE_STATES> mRTVInitialStates;
    std::pmr::vector<RESOURCE_STATES> mDSVInitialStates;
    ConstantBuffer mConstantBuffer;
    PmrStringMap<RenderSubpassDesc> mSubpassIndex;
};

struct Framebuffer {
    RESOURCE_DESC mResource;
    OptimizedClearColor mClear;
};

struct STAR_GRAPHICS_API RenderSolution {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderSolution(const allocator_type& alloc);
    RenderSolution(RenderSolution&& rhs, const allocator_type& alloc);
    RenderSolution(RenderSolution const& rhs, const allocator_type& alloc);
    ~RenderSolution();

    std::pmr::vector<RenderPipeline> mPipelines;
    std::pmr::vector<Framebuffer> mFramebuffers;
    std::pmr::vector<FramebufferHandle> mRTVSources;
    std::pmr::vector<FramebufferHandle> mDSVSources;
    std::pmr::vector<RENDER_TARGET_VIEW_DESC> mRTVs;
    std::pmr::vector<DEPTH_STENCIL_VIEW_DESC> mDSVs;
    PmrStringMap<uint32_t> mPipelineIndex;
};

struct SwapChain {
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
};

struct STAR_GRAPHICS_API RenderSwapChain {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderSwapChain(const allocator_type& alloc);
    RenderSwapChain(RenderSwapChain&& rhs, const allocator_type& alloc);
    RenderSwapChain(RenderSwapChain const& rhs, const allocator_type& alloc);
    ~RenderSwapChain();

    std::pmr::string mName;
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
    std::pmr::vector<RenderSolution> mSolutions;
    uint32_t mNumBackBuffers = 3;
    uint32_t mNumReserveFramebuffers = 0;
    uint32_t mNumReserveSRVs = 0;
    uint32_t mNumReserveUAVs = 0;
    uint32_t mNumReserveDSVs = 0;
    uint32_t mNumReserveRTVs = 0;
    ConstantBuffer mConstantBuffer;
    PmrStringMap<uint32_t> mSolutionIndex;
};

} // namespace Render

} // namespace Graphics

} // namespace Star

#ifdef _MSC_VER
#pragma warning(pop)
#endif
