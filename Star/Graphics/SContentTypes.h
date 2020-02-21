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
#include <Star/Graphics/SContentFwd.h>
#include <Star/Graphics/SRenderTypes.h>
#include <Star/Graphics/SRenderGraphTypes.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Star {

namespace Graphics {

namespace Render {

struct VertexElement {
    VertexElementType mType;
    uint16_t mAlignedByteOffset;
    Format mFormat;
};

inline bool operator==(const VertexElement&lhs, const VertexElement&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mType, lhs.mAlignedByteOffset, lhs.mFormat) ==
        std::forward_as_tuple(rhs.mType, rhs.mAlignedByteOffset, rhs.mFormat);
}
inline bool operator!=(const VertexElement&lhs, const VertexElement&rhs) noexcept {
    return !(lhs == rhs);
}

struct VertexElementIndex {
    uint32_t mBufferID;
    uint32_t mElementID;
};

inline bool operator==(const VertexElementIndex&lhs, const VertexElementIndex&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mBufferID, lhs.mElementID) ==
        std::forward_as_tuple(rhs.mBufferID, rhs.mElementID);
}
inline bool operator!=(const VertexElementIndex&lhs, const VertexElementIndex&rhs) noexcept {
    return !(lhs == rhs);
}

struct STAR_GRAPHICS_API VertexBufferDesc {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    VertexBufferDesc(const allocator_type& alloc);
    VertexBufferDesc(VertexBufferDesc&& rhs, const allocator_type& alloc);
    VertexBufferDesc(VertexBufferDesc const& rhs, const allocator_type& alloc);
    ~VertexBufferDesc();

    std::pmr::vector<VertexElement> mElements;
    uint32_t mVertexSize;
};

inline bool operator==(const VertexBufferDesc&lhs, const VertexBufferDesc&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mElements, lhs.mVertexSize) ==
        std::forward_as_tuple(rhs.mElements, rhs.mVertexSize);
}
inline bool operator!=(const VertexBufferDesc&lhs, const VertexBufferDesc&rhs) noexcept {
    return !(lhs == rhs);
}

struct STAR_GRAPHICS_API MeshBufferLayout {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    MeshBufferLayout(const allocator_type& alloc);
    MeshBufferLayout(MeshBufferLayout&& rhs, const allocator_type& alloc);
    MeshBufferLayout(MeshBufferLayout const& rhs, const allocator_type& alloc);
    ~MeshBufferLayout();

    std::pmr::vector<VertexBufferDesc> mBuffers;
    PmrMap<std::pmr::string, VertexElementIndex> mIndex;
    INDEX_BUFFER_STRIP_CUT_VALUE mStripCutValue = INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    PRIMITIVE_TOPOLOGY_TYPE mPrimitiveTopologyType = PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

inline bool operator==(const MeshBufferLayout&lhs, const MeshBufferLayout&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mBuffers, lhs.mIndex, lhs.mStripCutValue, lhs.mPrimitiveTopologyType) ==
        std::forward_as_tuple(rhs.mBuffers, rhs.mIndex, rhs.mStripCutValue, rhs.mPrimitiveTopologyType);
}
inline bool operator!=(const MeshBufferLayout&lhs, const MeshBufferLayout&rhs) noexcept {
    return !(lhs == rhs);
}

struct STAR_GRAPHICS_API VertexBufferData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    VertexBufferData(const allocator_type& alloc);
    VertexBufferData(VertexBufferData&& rhs, const allocator_type& alloc);
    VertexBufferData(VertexBufferData const& rhs, const allocator_type& alloc);
    ~VertexBufferData();

    VertexBufferDesc mDesc;
    uint32_t mVertexCount;
    std::pmr::vector<char> mBuffer;
};

struct STAR_GRAPHICS_API IndexBufferData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    IndexBufferData(const allocator_type& alloc);
    IndexBufferData(IndexBufferData&& rhs, const allocator_type& alloc);
    IndexBufferData(IndexBufferData const& rhs, const allocator_type& alloc);
    ~IndexBufferData();

    std::pmr::vector<char> mBuffer;
    uint32_t mElementSize;
    uint32_t mPrimitiveCount;
    GFX_PRIMITIVE_TOPOLOGY mPrimitiveTopology = GFX_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

struct SubMeshData {
    uint32_t mIndexOffset;
    uint32_t mIndexCount;
};

struct STAR_GRAPHICS_API MeshData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    MeshData(const allocator_type& alloc);
    MeshData(MeshData&& rhs, const allocator_type& alloc);
    MeshData(MeshData const& rhs, const allocator_type& alloc);
    ~MeshData();

    std::pmr::vector<VertexBufferData> mVertexBuffers;
    IndexBufferData mIndexBuffer;
    std::pmr::vector<SubMeshData> mSubMeshes;
    uint32_t mLayoutID = 0;
    std::pmr::string mLayoutName;
};

struct STAR_GRAPHICS_API TextureData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    TextureData(const allocator_type& alloc);
    TextureData(TextureData&& rhs, const allocator_type& alloc);
    TextureData(TextureData const& rhs, const allocator_type& alloc);
    ~TextureData();

    RESOURCE_DESC mDesc = {};
    Format mFormat;
    AlignedBuffer16 mBuffer;
};

struct PipelineStateData {
    STREAM_OUTPUT_DESC mStreamOutput;
    BLEND_DESC mBlendState;
    uint32_t mSampleMask;
    RASTERIZER_DESC mRasterizerState;
    DEPTH_STENCIL_DESC mDepthStencilState;
};

struct STAR_GRAPHICS_API ShaderProgramData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderProgramData(const allocator_type& alloc);
    ShaderProgramData(ShaderProgramData&& rhs, const allocator_type& alloc);
    ShaderProgramData(ShaderProgramData const& rhs, const allocator_type& alloc);
    ~ShaderProgramData();

    std::pmr::string mVS;
    std::pmr::string mHS;
    std::pmr::string mDS;
    std::pmr::string mGS;
    std::pmr::string mPS;
};

struct STAR_GRAPHICS_API ShaderInputLayout {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderInputLayout(const allocator_type& alloc);
    ShaderInputLayout(ShaderInputLayout&& rhs, const allocator_type& alloc);
    ShaderInputLayout(ShaderInputLayout const& rhs, const allocator_type& alloc);
    ~ShaderInputLayout();

    PmrVariantIndexMap<VertexElementType, std::pmr::vector<std::pmr::string>> mSemantics;
    INDEX_BUFFER_STRIP_CUT_VALUE mStripCutValue = INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    PRIMITIVE_TOPOLOGY_TYPE mPrimitiveTopologyType = PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

struct STAR_GRAPHICS_API ShaderSubpassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderSubpassData(const allocator_type& alloc);
    ShaderSubpassData(ShaderSubpassData&& rhs, const allocator_type& alloc);
    ShaderSubpassData(ShaderSubpassData const& rhs, const allocator_type& alloc);
    ~ShaderSubpassData();

    PipelineStateData mState;
    ShaderProgramData mProgram;
    ShaderInputLayout mInputLayout;
    std::pmr::vector<uint32_t> mVertexLayouts;
    std::pmr::vector<ShaderConstantBuffer> mConstantBuffers;
    std::pmr::vector<ShaderDescriptorCollection> mDescriptors;
};

struct STAR_GRAPHICS_API ShaderPassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderPassData(const allocator_type& alloc);
    ShaderPassData(ShaderPassData&& rhs, const allocator_type& alloc);
    ShaderPassData(ShaderPassData const& rhs, const allocator_type& alloc);
    ~ShaderPassData();

    std::pmr::vector<ShaderSubpassData> mSubpasses;
};

struct STAR_GRAPHICS_API ShaderLevelData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderLevelData(const allocator_type& alloc);
    ShaderLevelData(ShaderLevelData&& rhs, const allocator_type& alloc);
    ShaderLevelData(ShaderLevelData const& rhs, const allocator_type& alloc);
    ~ShaderLevelData();

    PmrMap<std::pmr::string, ShaderPassData> mPasses;
};

struct STAR_GRAPHICS_API ShaderQueueData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderQueueData(const allocator_type& alloc);
    ShaderQueueData(ShaderQueueData&& rhs, const allocator_type& alloc);
    ShaderQueueData(ShaderQueueData const& rhs, const allocator_type& alloc);
    ~ShaderQueueData();

    std::pmr::vector<ShaderLevelData> mLevels;
};

struct STAR_GRAPHICS_API ShaderPipelineData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderPipelineData(const allocator_type& alloc);
    ShaderPipelineData(ShaderPipelineData&& rhs, const allocator_type& alloc);
    ShaderPipelineData(ShaderPipelineData const& rhs, const allocator_type& alloc);
    ~ShaderPipelineData();

    PmrMap<std::pmr::string, ShaderQueueData> mQueues;
};

struct STAR_GRAPHICS_API ShaderSolutionData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderSolutionData(const allocator_type& alloc);
    ShaderSolutionData(ShaderSolutionData&& rhs, const allocator_type& alloc);
    ShaderSolutionData(ShaderSolutionData const& rhs, const allocator_type& alloc);
    ~ShaderSolutionData();

    PmrMap<std::pmr::string, ShaderPipelineData> mPipelines;
};

struct STAR_GRAPHICS_API ShaderData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ShaderData(const allocator_type& alloc);
    ShaderData(ShaderData&& rhs, const allocator_type& alloc);
    ShaderData(ShaderData const& rhs, const allocator_type& alloc);
    ~ShaderData();

    std::pmr::string mName;
    PmrMap<std::pmr::string, ShaderSolutionData> mSolutions;
};

struct ConstantDescriptor {
    uint16_t mOffset = 0;
    uint16_t mSize = 0;
};

struct STAR_GRAPHICS_API ConstantMap {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ConstantMap(const allocator_type& alloc);
    ConstantMap(ConstantMap&& rhs, const allocator_type& alloc);
    ConstantMap(ConstantMap const& rhs, const allocator_type& alloc);
    ~ConstantMap();

    PmrFlatMap<uint32_t, ConstantDescriptor> mIndex;
    AlignedBuffer16 mBuffer;
};

struct STAR_GRAPHICS_API MaterialData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    MaterialData(const allocator_type& alloc);
    MaterialData(MaterialData&& rhs, const allocator_type& alloc);
    MaterialData(MaterialData const& rhs, const allocator_type& alloc);
    ~MaterialData();

    std::pmr::string mShader;
    PmrFlatMap<uint32_t, MetaID> mTextures;
    ConstantMap mConstantMap;
};

struct FullScreenTriangle_ {} static constexpr FullScreenTriangle;

using DrawCallType = std::variant<std::monostate, FullScreenTriangle_>;

struct STAR_GRAPHICS_API DrawCallData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DrawCallData(const allocator_type& alloc);
    DrawCallData(DrawCallData&& rhs, const allocator_type& alloc);
    DrawCallData(DrawCallData const& rhs, const allocator_type& alloc);
    ~DrawCallData();

    DrawCallType mType;
    MetaID mMesh;
    MetaID mMaterial;
    uint16_t mInstanceSize;
    uint16_t mInstanceCount;
    ConstantMap mConstantMap;
};

struct BasicTransform {
    UniformScalingf mUniformScale;
    Translation3f mTranslation;
    Quaternionf mQuaternion;
};

struct WorldTransform {
    Affine3f mTransform;
};

struct WorldTransformInv {
    Affine3f mTransform;
};

struct BoundingBox {
    Box3f mLocalBounds;
    Box3f mWorldBounds;
};

using CameraView = std::variant<std::monostate, Direct3D_, Vulkan_, OpenGL_>;
using CameraNDC = std::variant<Direct3D_, Vulkan_>;

struct CameraData {
    Matrix4f mView = Matrix4f::Identity();
    Matrix4f mProj = Matrix4f::Zero();
    Vector3d mPosition = Vector3d::Zero();
    CameraView mViewSpace = OpenGL;
    CameraNDC mNDC = Direct3D;
    uint32_t mFlags = 0;
    Vector3f mRight = Vector3f(1.0f, 0.0f, 0.0f);
    Vector3f mForward = Vector3f(0.0f, 1.0f, 0.0f);
    Vector3f mUp = Vector3f(0.0f, 0.0f, 1.0f);
    float mYaw = 0.0f;
    float mPitch = 0.0f;
    float mRoll = 0.0f;
    float mNearClip = 1.0f;
    float mFarClip = 1000.0f;
    float mAspect = 16.0f / 9.0f;
    float mFov = 0.785398163f;
};

struct STAR_GRAPHICS_API MeshRenderer {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    MeshRenderer(const allocator_type& alloc);
    MeshRenderer(MeshRenderer&& rhs, const allocator_type& alloc);
    MeshRenderer(MeshRenderer const& rhs, const allocator_type& alloc);
    ~MeshRenderer();

    MetaID mMeshID;
    std::pmr::vector<MetaID> mMaterialIDs;
};

struct STAR_GRAPHICS_API FlattenedObjects {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    FlattenedObjects(const allocator_type& alloc);
    FlattenedObjects(FlattenedObjects&& rhs, const allocator_type& alloc);
    FlattenedObjects(FlattenedObjects const& rhs, const allocator_type& alloc);
    ~FlattenedObjects();

    std::pmr::vector<WorldTransform> mWorldTransforms;
    std::pmr::vector<WorldTransformInv> mWorldTransformInvs;
    std::pmr::vector<BoundingBox> mBoundingBoxes;
    std::pmr::vector<MeshRenderer> mMeshRenderers;
};

struct STAR_GRAPHICS_API ContentSettings {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ContentSettings(const allocator_type& alloc);
    ContentSettings(ContentSettings&& rhs, const allocator_type& alloc);
    ContentSettings(ContentSettings const& rhs, const allocator_type& alloc);
    ~ContentSettings();

    std::pmr::vector<MeshBufferLayout> mVertexLayouts;
    PmrMap<std::pmr::string, uint32_t> mVertexLayoutIndex;
};

struct DrawCall_ {} static constexpr DrawCall;
struct ObjectBatch_ {} static constexpr ObjectBatch;

using ContentType = std::variant<DrawCall_, ObjectBatch_>;

inline bool operator<(const ContentType& lhs, const ContentType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct ContentID {
    ContentType mType;
    uint16_t mIndex;
};

struct STAR_GRAPHICS_API ContentData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    ContentData(const allocator_type& alloc);
    ContentData(ContentData&& rhs, const allocator_type& alloc);
    ContentData(ContentData const& rhs, const allocator_type& alloc);
    ~ContentData();

    std::pmr::vector<ContentID> mIDs;
    std::pmr::vector<DrawCallData> mDrawCalls;
    std::pmr::vector<FlattenedObjects> mFlattenedObjects;
};

struct STAR_GRAPHICS_API RenderGraphData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    RenderGraphData(const allocator_type& alloc);
    RenderGraphData(RenderGraphData&& rhs, const allocator_type& alloc);
    RenderGraphData(RenderGraphData const& rhs, const allocator_type& alloc);
    ~RenderGraphData();

    RenderSwapChain mRenderGraph;
    PmrFlatMap<std::pmr::string, MetaID> mShaderIndex;
};

struct STAR_GRAPHICS_API Resources {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    Resources(const allocator_type& alloc);
    Resources(Resources&& rhs, const allocator_type& alloc);
    Resources(Resources const& rhs, const allocator_type& alloc);
    ~Resources();

    ContentSettings mSettings;
    std::pmr::unordered_map<MetaID, MeshData> mMeshes;
    std::pmr::unordered_map<MetaID, TextureData> mTextures;
    std::pmr::unordered_map<MetaID, ShaderData> mShaders;
    std::pmr::unordered_map<MetaID, MaterialData> mMaterials;
    std::pmr::unordered_map<MetaID, ContentData> mContents;
    std::pmr::unordered_map<MetaID, RenderGraphData> mRenderGraphs;
};

} // namespace Render

} // namespace Graphics

} // namespace Star

#ifdef _MSC_VER
#pragma warning(pop)
#endif
