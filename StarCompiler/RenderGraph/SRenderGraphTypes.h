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
#include <StarCompiler/RenderGraph/SRenderGraphFwd.h>
#include <StarCompiler/Graphics/SPixelFormatTypes.h>
#include <StarCompiler/Graphics/SRenderTypes.h>
#include <Star/Graphics/SRenderGraphTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

struct ResourceBuffer {
    uint64_t mWidth = 0;
};

inline bool operator==(const ResourceBuffer&lhs, const ResourceBuffer&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mWidth) ==
        std::forward_as_tuple(rhs.mWidth);
}
inline bool operator!=(const ResourceBuffer&lhs, const ResourceBuffer&rhs) noexcept {
    return !(lhs == rhs);
}

struct Resource1D {
    uint16_t mWidth = 0;
};

inline bool operator==(const Resource1D&lhs, const Resource1D&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mWidth) ==
        std::forward_as_tuple(rhs.mWidth);
}
inline bool operator!=(const Resource1D&lhs, const Resource1D&rhs) noexcept {
    return !(lhs == rhs);
}

struct Resource2D {
    uint16_t mWidth = 0;
    uint16_t mHeight = 0;
};

inline bool operator==(const Resource2D&lhs, const Resource2D&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mWidth, lhs.mHeight) ==
        std::forward_as_tuple(rhs.mWidth, rhs.mHeight);
}
inline bool operator!=(const Resource2D&lhs, const Resource2D&rhs) noexcept {
    return !(lhs == rhs);
}

struct Resource3D {
    uint16_t mWidth = 0;
    uint16_t mHeight = 0;
    uint16_t mDepthSize = 0;
};

inline bool operator==(const Resource3D&lhs, const Resource3D&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mWidth, lhs.mHeight, lhs.mDepthSize) ==
        std::forward_as_tuple(rhs.mWidth, rhs.mHeight, rhs.mDepthSize);
}
inline bool operator!=(const Resource3D&lhs, const Resource3D&rhs) noexcept {
    return !(lhs == rhs);
}

struct MipChain {};

inline bool operator==(const MipChain&lhs, const MipChain&rhs) noexcept {
    return
        std::forward_as_tuple() ==
        std::forward_as_tuple();
}
inline bool operator!=(const MipChain&lhs, const MipChain&rhs) noexcept {
    return !(lhs == rhs);
}

struct MipLevels {
    uint8_t mMipLevels = 0;
};

inline bool operator==(const MipLevels&lhs, const MipLevels&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mMipLevels) ==
        std::forward_as_tuple(rhs.mMipLevels);
}
inline bool operator!=(const MipLevels&lhs, const MipLevels&rhs) noexcept {
    return !(lhs == rhs);
}

struct ArraySize {
    uint16_t mArraySize = 0;
};

inline bool operator==(const ArraySize&lhs, const ArraySize&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mArraySize) ==
        std::forward_as_tuple(rhs.mArraySize);
}
inline bool operator!=(const ArraySize&lhs, const ArraySize&rhs) noexcept {
    return !(lhs == rhs);
}

struct Multisampling {
    uint32_t mCount = 0;
    uint32_t mQuality = 0;
};

inline bool operator==(const Multisampling&lhs, const Multisampling&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mCount, lhs.mQuality) ==
        std::forward_as_tuple(rhs.mCount, rhs.mQuality);
}
inline bool operator!=(const Multisampling&lhs, const Multisampling&rhs) noexcept {
    return !(lhs == rhs);
}

using ResourceType = std::variant<ResourceBuffer, Resource1D, Resource2D, Resource3D>;
using ResourceArray = std::variant<std::monostate, ArraySize>;
using ResourceMipMap = std::variant<std::monostate, MipChain, MipLevels>;
using ResourceSampling = std::variant<std::monostate, Multisampling>;

struct RowMajor_ {} static constexpr RowMajor;
inline bool operator==(const RowMajor_&, const RowMajor_&) noexcept { return true; }
inline bool operator!=(const RowMajor_&, const RowMajor_&) noexcept { return false; }
struct UndefinedSwizzle64KB_ {} static constexpr UndefinedSwizzle64KB;
inline bool operator==(const UndefinedSwizzle64KB_&, const UndefinedSwizzle64KB_&) noexcept { return true; }
inline bool operator!=(const UndefinedSwizzle64KB_&, const UndefinedSwizzle64KB_&) noexcept { return false; }
struct StandardSwizzle64KB_ {} static constexpr StandardSwizzle64KB;
inline bool operator==(const StandardSwizzle64KB_&, const StandardSwizzle64KB_&) noexcept { return true; }
inline bool operator!=(const StandardSwizzle64KB_&, const StandardSwizzle64KB_&) noexcept { return false; }

using ResourceLayout = std::variant<std::monostate, RowMajor_, UndefinedSwizzle64KB_, StandardSwizzle64KB_>;

struct Resource {
    Format mFormat;
    ResourceType mDimension;
    ResourceArray mArray;
    ResourceMipMap mMipMap;
    ResourceSampling mSampling;
    ResourceLayout mLayout;
};

inline bool operator==(const Resource&lhs, const Resource&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mFormat, lhs.mDimension, lhs.mArray, lhs.mMipMap, lhs.mSampling, lhs.mLayout) ==
        std::forward_as_tuple(rhs.mFormat, rhs.mDimension, rhs.mArray, rhs.mMipMap, rhs.mSampling, rhs.mLayout);
}
inline bool operator!=(const Resource&lhs, const Resource&rhs) noexcept {
    return !(lhs == rhs);
}

struct BarrierTransition_ {} static constexpr BarrierTransition;
struct BarrierAliasing_ {} static constexpr BarrierAliasing;
struct BarrierUav_ {} static constexpr BarrierUav;

using ResourceBarrierType = std::variant<BarrierTransition_, BarrierAliasing_, BarrierUav_>;
using ResourceViewType = std::variant<SRV_, UAV_, DSV_, RTV_>;
using ShaderDescriptorType = std::variant<CBV_, UAV_, SRV_>;

struct Source_ {} static constexpr Source;
struct Target_ {} static constexpr Target;

using SourceTarget = std::variant<Source_, Target_>;

struct Common_ {} static constexpr Common;
inline bool operator==(const Common_&, const Common_&) noexcept { return true; }
inline bool operator!=(const Common_&, const Common_&) noexcept { return false; }
struct VertexAndConstantBuffer_ {} static constexpr VertexAndConstantBuffer;
struct IndexBuffer_ {} static constexpr IndexBuffer;
struct RenderTarget_ {} static constexpr RenderTarget;
inline bool operator==(const RenderTarget_&, const RenderTarget_&) noexcept { return true; }
inline bool operator!=(const RenderTarget_&, const RenderTarget_&) noexcept { return false; }
struct UnorderedAccess_ {} static constexpr UnorderedAccess;
inline bool operator==(const UnorderedAccess_&, const UnorderedAccess_&) noexcept { return true; }
inline bool operator!=(const UnorderedAccess_&, const UnorderedAccess_&) noexcept { return false; }
struct DepthWrite_ {} static constexpr DepthWrite;
inline bool operator==(const DepthWrite_&, const DepthWrite_&) noexcept { return true; }
inline bool operator!=(const DepthWrite_&, const DepthWrite_&) noexcept { return false; }
struct DepthRead_ {} static constexpr DepthRead;
inline bool operator==(const DepthRead_&, const DepthRead_&) noexcept { return true; }
inline bool operator!=(const DepthRead_&, const DepthRead_&) noexcept { return false; }
struct ShaderResource_ {} static constexpr ShaderResource;
inline bool operator==(const ShaderResource_&, const ShaderResource_&) noexcept { return true; }
inline bool operator!=(const ShaderResource_&, const ShaderResource_&) noexcept { return false; }
struct StreamOut_ {} static constexpr StreamOut;
struct IndirectArgument_ {} static constexpr IndirectArgument;
struct CopyDest_ {} static constexpr CopyDest;
inline bool operator==(const CopyDest_&, const CopyDest_&) noexcept { return true; }
inline bool operator!=(const CopyDest_&, const CopyDest_&) noexcept { return false; }
struct CopySource_ {} static constexpr CopySource;
inline bool operator==(const CopySource_&, const CopySource_&) noexcept { return true; }
inline bool operator!=(const CopySource_&, const CopySource_&) noexcept { return false; }
struct ResolveDest_ {} static constexpr ResolveDest;
inline bool operator==(const ResolveDest_&, const ResolveDest_&) noexcept { return true; }
inline bool operator!=(const ResolveDest_&, const ResolveDest_&) noexcept { return false; }
struct ResolveSource_ {} static constexpr ResolveSource;
inline bool operator==(const ResolveSource_&, const ResolveSource_&) noexcept { return true; }
inline bool operator!=(const ResolveSource_&, const ResolveSource_&) noexcept { return false; }
struct Present_ {} static constexpr Present;
inline bool operator==(const Present_&, const Present_&) noexcept { return true; }
inline bool operator!=(const Present_&, const Present_&) noexcept { return false; }
struct Raytracing_ {} static constexpr Raytracing;
struct Predication_ {} static constexpr Predication;

using TextureViewState = std::variant<Common_, RenderTarget_, UnorderedAccess_, DepthWrite_, DepthRead_, ShaderResource_, CopyDest_, CopySource_, ResolveDest_, ResolveSource_, Present_>;

struct RenderTargetState {
    TextureViewState mState;
    bool mNonPixelShaderResource = false;
    bool mPixelShaderResource = false;
};

inline bool operator==(const RenderTargetState&lhs, const RenderTargetState&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mState, lhs.mNonPixelShaderResource, lhs.mPixelShaderResource) ==
        std::forward_as_tuple(rhs.mState, rhs.mNonPixelShaderResource, rhs.mPixelShaderResource);
}
inline bool operator!=(const RenderTargetState&lhs, const RenderTargetState&rhs) noexcept {
    return !(lhs == rhs);
}

struct RenderValue {
    std::string mName;
    TextureViewState mState;
    ResourceDataView mData;
    PixelModel mModel;
    LoadOp mLoadOp;
    StoreOp mStoreOp;
};

inline bool operator==(const RenderValue&lhs, const RenderValue&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName, lhs.mState, lhs.mData, lhs.mModel, lhs.mLoadOp, lhs.mStoreOp) ==
        std::forward_as_tuple(rhs.mName, rhs.mState, rhs.mData, rhs.mModel, rhs.mLoadOp, rhs.mStoreOp);
}
inline bool operator!=(const RenderValue&lhs, const RenderValue&rhs) noexcept {
    return !(lhs == rhs);
}

struct NodeRenderTargetState {
    uint32_t mNodeID = 0;
    RenderTargetState mRenderTargetState;
};

struct RenderTargetStateTransition {
    uint32_t mNodeID = 0;
    RenderTargetState mSource;
    RenderTargetState mTarget;
};

struct RenderTargetStateTransitions {
    std::vector<NodeRenderTargetState> mStates;
    std::vector<NodeRenderTargetState> mFullStates;
    std::vector<RenderTargetStateTransition> mTransitions;
};

struct UnorderedRenderContent {
    std::vector<MetaID> mContents;
};

struct RenderNode {
    RenderNode() = default;
    RenderNode(std::string name, ResourceDataViewMap<RenderValue> outputs)
        : mName(std::move(name))
        , mOutputs(std::move(outputs))
    {}
    RenderNode(std::string name, ResourceDataViewMap<RenderValue> outputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mOutputs(std::move(outputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs)
        : mName(std::move(name))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
    {}
    RenderNode(std::string name, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs)
        : mName(std::move(name))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
    {}
    RenderNode(std::string name, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs)
        : mName(std::move(name))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
    {}
    RenderNode(std::string name, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ResourceDataViewMap<RenderValue> outputs)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mOutputs(std::move(outputs))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ResourceDataViewMap<RenderValue> outputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mOutputs(std::move(outputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mQueue(std::move(queue))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
    {}
    RenderNode(std::string name, ResourceSampling sampling, ColorSpace colorSpace, ResourceDataViewMap<RenderValue> outputs, ResourceDataViewMap<RenderValue> inputs, std::vector<UnorderedRenderContent> queue)
        : mName(std::move(name))
        , mSampling(std::move(sampling))
        , mColorSpace(std::move(colorSpace))
        , mOutputs(std::move(outputs))
        , mInputs(std::move(inputs))
        , mQueue(std::move(queue))
    {}
    std::string mName;
    ColorSpace mColorSpace;
    ResourceDataViewMap<RenderValue> mOutputs;
    ResourceDataViewMap<RenderValue> mInputs;
    ResourceSampling mSampling;
    std::vector<UnorderedRenderContent> mQueue;
    std::string mRootSignature;
};

struct RenderGroup {
    std::vector<std::string> mRenderNodes;
    ResourceDataViewMap<RenderValue> mInputs;
    ResourceDataViewMap<RenderValue> mOutputs;
};

struct BackBuffer_ {} static constexpr BackBuffer;
inline bool operator==(const BackBuffer_&, const BackBuffer_&) noexcept { return true; }
inline bool operator!=(const BackBuffer_&, const BackBuffer_&) noexcept { return false; }

using RenderTargetType = std::variant<std::monostate, BackBuffer_>;

struct RenderTargetResource {
    std::string mName;
    Resource mResource;
    OptimizedClearColor mClearColor;
    ColorSpace mColorSpace;
    RenderTargetType mType;
};

inline bool operator==(const RenderTargetResource&lhs, const RenderTargetResource&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName, lhs.mResource, lhs.mClearColor, lhs.mColorSpace, lhs.mType) ==
        std::forward_as_tuple(rhs.mName, rhs.mResource, rhs.mClearColor, rhs.mColorSpace, rhs.mType);
}
inline bool operator!=(const RenderTargetResource&lhs, const RenderTargetResource&rhs) noexcept {
    return !(lhs == rhs);
}

struct RenderConfigs {
    bool mVerbose = false;
    bool mStrictLightingColorSpace = false;
    bool mFramebufferFetch = false;
};

} // namespace Render

} // namespace Graphics

} // namespace Star
