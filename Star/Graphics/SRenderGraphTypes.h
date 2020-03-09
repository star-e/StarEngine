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
    Float4 mClearColor = Float4::Zero();
    Format mClearFormat = Format::UNKNOWN;
};

inline bool operator==(const ClearColor& lhs, const ClearColor& rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mClearColor, lhs.mClearFormat) ==
        std::forward_as_tuple(rhs.mClearColor, rhs.mClearFormat);
}

inline bool operator!=(const ClearColor& lhs, const ClearColor& rhs) noexcept {
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

inline bool operator==(const ClearDepthStencil& lhs, const ClearDepthStencil& rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mDepthClearValue, lhs.mStencilClearValue, lhs.mClearDepth, lhs.mClearStencil, lhs.mUnused, lhs.mClearFormat) ==
        std::forward_as_tuple(rhs.mDepthClearValue, rhs.mStencilClearValue, rhs.mClearDepth, rhs.mClearStencil, rhs.mUnused, rhs.mClearFormat);
}

inline bool operator!=(const ClearDepthStencil& lhs, const ClearDepthStencil& rhs) noexcept {
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

namespace Descriptor {

struct ConstantBuffer_ {} static constexpr ConstantBuffer;
struct MainTex_ {} static constexpr MainTex;
struct PointSampler_ {} static constexpr PointSampler;
struct LinearSampler_ {} static constexpr LinearSampler;

using Type = std::variant<std::monostate, ConstantBuffer_, MainTex_, PointSampler_, LinearSampler_>;

inline bool operator<(const Type& lhs, const Type& rhs) noexcept {
    return lhs.index() < rhs.index();
}

} // namespace Descriptor

namespace Data {

struct Proj_ {} static constexpr Proj;
struct View_ {} static constexpr View;
struct WorldView_ {} static constexpr WorldView;
struct WorldInvT_ {} static constexpr WorldInvT;

using Type = std::variant<std::monostate, Proj_, View_, WorldView_, WorldInvT_>;

inline bool operator<(const Type& lhs, const Type& rhs) noexcept {
    return lhs.index() < rhs.index();
}

} // namespace Data

struct ShaderDescriptor {
    Descriptor::Type mDataType;
    AttributeType mAttributeType;
    uint32_t mID = 0;
};

struct STAR_GRAPHICS_API ShaderDescriptorSubrange {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderDescriptorSubrange(const allocator_type& alloc);
    ShaderDescriptorSubrange(ShaderDescriptorSubrange&& rhs, const allocator_type& alloc);
    ShaderDescriptorSubrange(ShaderDescriptorSubrange const& rhs, const allocator_type& alloc);
    ~ShaderDescriptorSubrange();

    DescriptorSource mSource;
    std::pmr::vector<ShaderDescriptor> mDescriptors;
};

struct STAR_GRAPHICS_API ShaderDescriptorRange {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderDescriptorRange(const allocator_type& alloc);
    ShaderDescriptorRange(ShaderDescriptorRange&& rhs, const allocator_type& alloc);
    ShaderDescriptorRange(ShaderDescriptorRange const& rhs, const allocator_type& alloc);
    ~ShaderDescriptorRange();

    DescriptorType mType;
    std::pmr::vector<ShaderDescriptorSubrange> mSubranges;
    uint32_t mCapacity = 0;
};

struct STAR_GRAPHICS_API ShaderUnboundedDescriptor {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderUnboundedDescriptor(const allocator_type& alloc);
    ShaderUnboundedDescriptor(ShaderUnboundedDescriptor&& rhs, const allocator_type& alloc);
    ShaderUnboundedDescriptor(ShaderUnboundedDescriptor const& rhs, const allocator_type& alloc);
    ~ShaderUnboundedDescriptor();

    DescriptorType mType;
    std::pmr::string mAttribute;
    uint32_t mCapacity = 0;
};

struct STAR_GRAPHICS_API ShaderDescriptorList {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderDescriptorList(const allocator_type& alloc);
    ShaderDescriptorList(ShaderDescriptorList&& rhs, const allocator_type& alloc);
    ShaderDescriptorList(ShaderDescriptorList const& rhs, const allocator_type& alloc);
    ~ShaderDescriptorList();

    uint32_t mSlot = 0;
    uint32_t mCapacity = 0;
    std::pmr::vector<ShaderDescriptorRange> mRanges;
    std::pmr::vector<ShaderUnboundedDescriptor> mUnboundedDescriptors;
};

struct STAR_GRAPHICS_API ShaderDescriptorCollection {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderDescriptorCollection(const allocator_type& alloc);
    ShaderDescriptorCollection(ShaderDescriptorCollection&& rhs, const allocator_type& alloc);
    ShaderDescriptorCollection(ShaderDescriptorCollection const& rhs, const allocator_type& alloc);
    ~ShaderDescriptorCollection();

    DescriptorIndex mIndex;
    std::pmr::vector<ShaderDescriptorList> mResourceViewLists;
    std::pmr::vector<ShaderDescriptorList> mSamplerLists;
};

struct ShaderConstant {
    Data::Type mDataType;
    DescriptorSource mSource;
    uint32_t mID = 0;
};

struct STAR_GRAPHICS_API ShaderConstantBuffer {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderConstantBuffer(const allocator_type& alloc);
    ShaderConstantBuffer(ShaderConstantBuffer&& rhs, const allocator_type& alloc);
    ShaderConstantBuffer(ShaderConstantBuffer const& rhs, const allocator_type& alloc);
    ~ShaderConstantBuffer();

    DescriptorIndex mIndex;
    uint32_t mSize = 0;
    std::pmr::vector<ShaderConstant> mConstants;
};

struct STAR_GRAPHICS_API GraphicsSubpass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    GraphicsSubpass(const allocator_type& alloc);
    GraphicsSubpass(GraphicsSubpass&& rhs, const allocator_type& alloc);
    GraphicsSubpass(GraphicsSubpass const& rhs, const allocator_type& alloc);
    ~GraphicsSubpass();

    DISP_SAMPLE_DESC mSampleDesc;
    std::pmr::vector<Attachment> mInputAttachments;
    std::pmr::vector<Attachment> mOutputAttachments;
    std::pmr::vector<Attachment> mResolveAttachments;
    std::optional<Attachment> mDepthStencilAttachment;
    std::pmr::vector<Attachment> mPreserveAttachments;
    std::pmr::vector<RenderViewTransition> mPostViewTransitions;
    std::pmr::vector<UnorderedRenderQueue> mOrderedRenderQueue;
    std::pmr::string mRootSignature;
    std::pmr::vector<ShaderConstantBuffer> mConstantBuffers;
    std::pmr::vector<ShaderDescriptorCollection> mDescriptors;
};

struct GraphicsSubpassDependency {
    uint32_t mSrcSubpass = 0;
    uint32_t mDstSubpass = 0;
};

struct STAR_GRAPHICS_API ComputeSubpass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ComputeSubpass(const allocator_type& alloc);
    ComputeSubpass(ComputeSubpass&& rhs, const allocator_type& alloc);
    ComputeSubpass(ComputeSubpass const& rhs, const allocator_type& alloc);
    ~ComputeSubpass();

    std::pmr::vector<Attachment> mAttachments;
};

struct STAR_GRAPHICS_API RaytracingSubpass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RaytracingSubpass(const allocator_type& alloc);
    RaytracingSubpass(RaytracingSubpass&& rhs, const allocator_type& alloc);
    RaytracingSubpass(RaytracingSubpass const& rhs, const allocator_type& alloc);
    ~RaytracingSubpass();

    std::pmr::vector<Attachment> mOutputAttachments;
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
    std::pmr::vector<ComputeSubpass> mComputeSubpasses;
    std::pmr::vector<GraphicsSubpass> mGraphicsSubpasses;
    std::pmr::vector<GraphicsSubpassDependency> mDependencies;
    std::pmr::vector<RaytracingSubpass> mRaytracingSubpasses;
};

struct RenderPassDependency {
    uint32_t mSrcPass = 0;
    uint32_t mDstPass = 0;
};

struct RenderSubpassDesc {
    uint32_t mPassID = 0;
    uint32_t mSubpassID = 0;
};

inline bool operator<(const RenderSubpassDesc& lhs, const RenderSubpassDesc& rhs) noexcept {
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
    PmrMap<std::pmr::string, RenderSubpassDesc> mSubpassIndex;
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
    std::pmr::vector<FramebufferHandle> mCBVSources;
    std::pmr::vector<FramebufferHandle> mSRVSources;
    std::pmr::vector<FramebufferHandle> mUAVSources;
    std::pmr::vector<RENDER_TARGET_VIEW_DESC> mRTVs;
    std::pmr::vector<DEPTH_STENCIL_VIEW_DESC> mDSVs;
    std::pmr::vector<CONSTANT_BUFFER_VIEW_DESC> mCBVs;
    std::pmr::vector<SHADER_RESOURCE_VIEW_DESC> mSRVs;
    std::pmr::vector<UNORDERED_ACCESS_VIEW_DESC> mUAVs;
    PmrFlatMap<uint32_t, uint32_t> mAttributeIndex;
    PmrMap<std::pmr::string, uint32_t> mPipelineIndex;
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
    uint32_t mNumReserveCBV_SRV_UAVs = 0;
    uint32_t mNumReserveDSVs = 0;
    uint32_t mNumReserveRTVs = 0;
    PmrMap<std::pmr::string, uint32_t> mSolutionIndex;
};

} // namespace Render

} // namespace Graphics

} // namespace Star

#ifdef _MSC_VER
#pragma warning(pop)
#endif
