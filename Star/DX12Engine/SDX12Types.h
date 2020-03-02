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
#include <Star/DX12Engine/SDX12Fwd.h>
#include <Star/Graphics/SContentTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

struct DX12VertexBuffer {
    com_ptr<ID3D12Resource> mBuffer;
};

struct DX12IndexBuffer {
    com_ptr<ID3D12Resource> mBuffer;
    GFX_PRIMITIVE_TOPOLOGY mPrimitiveTopology = GFX_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

struct DX12MeshData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MeshData(const allocator_type& alloc);
    DX12MeshData(MetaID metaID, const allocator_type& alloc);
    DX12MeshData(DX12MeshData&& rhs, const allocator_type& alloc);
    DX12MeshData(DX12MeshData const& rhs, const allocator_type& alloc);
    ~DX12MeshData();

    MetaID mMetaID;
    std::pmr::vector<D3D12_VERTEX_BUFFER_VIEW> mVertexBufferViews;
    D3D12_INDEX_BUFFER_VIEW mIndexBufferView = {};
    std::pmr::vector<SubMeshData> mSubMeshes;
    std::pmr::vector<DX12VertexBuffer> mVertexBuffers;
    DX12IndexBuffer mIndexBuffer;
    Core::Fetch<MeshData> mMeshData;
    uint32_t mRefCount = 0;
    uint32_t mLayoutID = 0;
    std::pmr::string mLayoutName;
};

struct DX12TextureData {
    DX12TextureData() = default;
    DX12TextureData(MetaID metaID)
        : mMetaID(std::move(metaID))
    {}
    MetaID mMetaID;
    com_ptr<ID3D12Resource> mTexture;
    DXGI_FORMAT mFormat;
    Core::Fetch<TextureData> mTextureData;
    uint32_t mRefCount = 0;
};

struct DX12ProgramData {
    com_ptr<ID3DBlob> mVS;
    com_ptr<ID3DBlob> mHS;
    com_ptr<ID3DBlob> mDS;
    com_ptr<ID3DBlob> mGS;
    com_ptr<ID3DBlob> mPS;
};

struct DX12PipelineStateData {
    com_ptr<ID3D12PipelineState> mObject;
};

struct DX12ShaderProgramData {
    com_ptr<ID3DBlob> mVS;
    com_ptr<ID3DBlob> mHS;
    com_ptr<ID3DBlob> mDS;
    com_ptr<ID3DBlob> mGS;
    com_ptr<ID3DBlob> mPS;
};

struct DX12ShaderSubpassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderSubpassData(const allocator_type& alloc);
    DX12ShaderSubpassData(DX12ShaderSubpassData&& rhs, const allocator_type& alloc);
    DX12ShaderSubpassData(DX12ShaderSubpassData const& rhs, const allocator_type& alloc);
    ~DX12ShaderSubpassData();

    DX12ShaderProgramData mProgram;
    std::pmr::vector<DX12PipelineStateData> mStates;
    PmrFlatMap<uint32_t, uint32_t> mVertexLayoutIndex;
    std::pmr::vector<ShaderConstantBuffer> mConstantBuffers;
    std::pmr::vector<ShaderDescriptorCollection> mDescriptors;
};

struct DX12ShaderPassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderPassData(const allocator_type& alloc);
    DX12ShaderPassData(DX12ShaderPassData&& rhs, const allocator_type& alloc);
    DX12ShaderPassData(DX12ShaderPassData const& rhs, const allocator_type& alloc);
    ~DX12ShaderPassData();

    std::pmr::vector<DX12ShaderSubpassData> mSubpasses;
};

struct DX12ShaderLevelData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderLevelData(const allocator_type& alloc);
    DX12ShaderLevelData(DX12ShaderLevelData&& rhs, const allocator_type& alloc);
    DX12ShaderLevelData(DX12ShaderLevelData const& rhs, const allocator_type& alloc);
    ~DX12ShaderLevelData();

    std::pmr::vector<DX12ShaderPassData> mPasses;
    PmrFlatMap<std::pmr::string, uint32_t> mPassIndex;
};

struct DX12ShaderQueueData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderQueueData(const allocator_type& alloc);
    DX12ShaderQueueData(DX12ShaderQueueData&& rhs, const allocator_type& alloc);
    DX12ShaderQueueData(DX12ShaderQueueData const& rhs, const allocator_type& alloc);
    ~DX12ShaderQueueData();

    std::pmr::vector<DX12ShaderLevelData> mLevels;
};

struct DX12ShaderPipelineData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderPipelineData(const allocator_type& alloc);
    DX12ShaderPipelineData(DX12ShaderPipelineData&& rhs, const allocator_type& alloc);
    DX12ShaderPipelineData(DX12ShaderPipelineData const& rhs, const allocator_type& alloc);
    ~DX12ShaderPipelineData();

    std::pmr::vector<DX12ShaderQueueData> mQueues;
    PmrFlatMap<RenderSubpassDesc, uint32_t> mQueueIndex;
};

struct DX12ShaderSolutionData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderSolutionData(const allocator_type& alloc);
    DX12ShaderSolutionData(DX12ShaderSolutionData&& rhs, const allocator_type& alloc);
    DX12ShaderSolutionData(DX12ShaderSolutionData const& rhs, const allocator_type& alloc);
    ~DX12ShaderSolutionData();

    std::pmr::vector<DX12ShaderPipelineData> mPipelines;
    PmrFlatMap<uint32_t, uint32_t> mPipelineIndex;
};

struct DX12ShaderData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderData(const allocator_type& alloc);
    DX12ShaderData(MetaID metaID, const allocator_type& alloc);
    DX12ShaderData(DX12ShaderData&& rhs, const allocator_type& alloc);
    DX12ShaderData(DX12ShaderData const& rhs, const allocator_type& alloc);
    ~DX12ShaderData();

    MetaID mMetaID;
    std::pmr::vector<DX12ShaderSolutionData> mSolutions;
    PmrFlatMap<uint32_t, uint32_t> mSolutionIndex;
    Core::Fetch<ShaderData> mShaderData;
    uint32_t mRefCount = 0;
};

struct DX12ShaderDescriptorList {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderDescriptorList(const allocator_type& alloc);
    DX12ShaderDescriptorList(DX12ShaderDescriptorList&& rhs, const allocator_type& alloc);
    DX12ShaderDescriptorList(DX12ShaderDescriptorList const& rhs, const allocator_type& alloc);
    ~DX12ShaderDescriptorList();

    uint32_t mSlot = 0;
    uint32_t mCapacity = 0;
    D3D12_GPU_DESCRIPTOR_HANDLE mGpuOffset = {};
    D3D12_CPU_DESCRIPTOR_HANDLE mCpuOffset = {};
    std::pmr::vector<ShaderDescriptorRange> mRanges;
    std::pmr::vector<ShaderUnboundedDescriptor> mUnboundedDescriptors;
};

struct DX12ShaderDescriptorCollection {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ShaderDescriptorCollection(const allocator_type& alloc);
    DX12ShaderDescriptorCollection(DX12ShaderDescriptorCollection&& rhs, const allocator_type& alloc);
    DX12ShaderDescriptorCollection(DX12ShaderDescriptorCollection const& rhs, const allocator_type& alloc);
    ~DX12ShaderDescriptorCollection();

    DescriptorIndex mIndex;
    std::pmr::vector<DX12ShaderDescriptorList> mResourceViewLists;
    std::pmr::vector<DX12ShaderDescriptorList> mSamplerLists;
};

struct DX12MaterialSubpassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialSubpassData(const allocator_type& alloc);
    DX12MaterialSubpassData(DX12MaterialSubpassData&& rhs, const allocator_type& alloc);
    DX12MaterialSubpassData(DX12MaterialSubpassData const& rhs, const allocator_type& alloc);
    ~DX12MaterialSubpassData();

    std::pmr::vector<DX12ShaderDescriptorCollection> mCollections;
};

struct DX12MaterialPassData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialPassData(const allocator_type& alloc);
    DX12MaterialPassData(DX12MaterialPassData&& rhs, const allocator_type& alloc);
    DX12MaterialPassData(DX12MaterialPassData const& rhs, const allocator_type& alloc);
    ~DX12MaterialPassData();

    std::pmr::vector<DX12MaterialSubpassData> mSubpasses;
};

struct DX12MaterialLevelData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialLevelData(const allocator_type& alloc);
    DX12MaterialLevelData(DX12MaterialLevelData&& rhs, const allocator_type& alloc);
    DX12MaterialLevelData(DX12MaterialLevelData const& rhs, const allocator_type& alloc);
    ~DX12MaterialLevelData();

    std::pmr::vector<DX12MaterialPassData> mPasses;
};

struct DX12MaterialQueueData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialQueueData(const allocator_type& alloc);
    DX12MaterialQueueData(DX12MaterialQueueData&& rhs, const allocator_type& alloc);
    DX12MaterialQueueData(DX12MaterialQueueData const& rhs, const allocator_type& alloc);
    ~DX12MaterialQueueData();

    std::pmr::vector<DX12MaterialLevelData> mLevels;
};

struct DX12MaterialPipelineData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialPipelineData(const allocator_type& alloc);
    DX12MaterialPipelineData(DX12MaterialPipelineData&& rhs, const allocator_type& alloc);
    DX12MaterialPipelineData(DX12MaterialPipelineData const& rhs, const allocator_type& alloc);
    ~DX12MaterialPipelineData();

    std::pmr::vector<DX12MaterialQueueData> mQueues;
};

struct DX12MaterialSolutionData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialSolutionData(const allocator_type& alloc);
    DX12MaterialSolutionData(DX12MaterialSolutionData&& rhs, const allocator_type& alloc);
    DX12MaterialSolutionData(DX12MaterialSolutionData const& rhs, const allocator_type& alloc);
    ~DX12MaterialSolutionData();

    std::pmr::vector<DX12MaterialPipelineData> mPipelines;
};

struct DX12MaterialData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MaterialData(const allocator_type& alloc);
    DX12MaterialData(MetaID metaID, const allocator_type& alloc);
    DX12MaterialData(DX12MaterialData&& rhs, const allocator_type& alloc);
    DX12MaterialData(DX12MaterialData const& rhs, const allocator_type& alloc);
    ~DX12MaterialData();

    MetaID mMetaID;
    boost::intrusive_ptr<DX12ShaderData> mShader;
    DX12ShaderDescriptorHeap* mDescriptorHeap = nullptr;
    std::pmr::vector<DX12MaterialSolutionData> mShaderData;
    std::pmr::vector<boost::intrusive_ptr<DX12TextureData>> mTextures;
    ConstantMap mConstantMap;
    Core::Fetch<MaterialData> mMaterialData;
    uint32_t mRefCount = 0;
};

struct DX12DrawCallData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12DrawCallData(const allocator_type& alloc);
    DX12DrawCallData(DX12DrawCallData&& rhs, const allocator_type& alloc);
    DX12DrawCallData(DX12DrawCallData const& rhs, const allocator_type& alloc);
    ~DX12DrawCallData();

    DrawCallType mType;
    boost::intrusive_ptr<DX12MeshData> mMesh;
    boost::intrusive_ptr<DX12MaterialData> mMaterial;
    uint16_t mInstanceSize;
    uint16_t mInstanceCount;
    ConstantMap mConstantMap;
};

struct DX12MeshRenderer {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12MeshRenderer(const allocator_type& alloc);
    DX12MeshRenderer(DX12MeshRenderer&& rhs, const allocator_type& alloc);
    DX12MeshRenderer(DX12MeshRenderer const& rhs, const allocator_type& alloc);
    ~DX12MeshRenderer();

    boost::intrusive_ptr<DX12MeshData> mMesh;
    std::pmr::vector<boost::intrusive_ptr<DX12MaterialData>> mMaterials;
};

struct DX12FlattenedObjects {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12FlattenedObjects(const allocator_type& alloc);
    DX12FlattenedObjects(DX12FlattenedObjects&& rhs, const allocator_type& alloc);
    DX12FlattenedObjects(DX12FlattenedObjects const& rhs, const allocator_type& alloc);
    ~DX12FlattenedObjects();

    std::pmr::vector<WorldTransform> mWorldTransforms;
    std::pmr::vector<WorldTransformInv> mWorldTransformInvs;
    std::pmr::vector<BoundingBox> mBoundingBoxes;
    std::pmr::vector<DX12MeshRenderer> mMeshRenderers;
};

struct DX12ContentData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12ContentData(const allocator_type& alloc);
    DX12ContentData(MetaID metaID, const allocator_type& alloc);
    DX12ContentData(DX12ContentData&& rhs, const allocator_type& alloc);
    DX12ContentData(DX12ContentData const& rhs, const allocator_type& alloc);
    ~DX12ContentData();

    MetaID mMetaID;
    std::pmr::vector<ContentID> mIDs;
    std::pmr::vector<DX12DrawCallData> mDrawCalls;
    std::pmr::vector<DX12FlattenedObjects> mFlattenedObjects;
    Core::Fetch<ContentData> mContentData;
    uint32_t mRefCount = 0;
};

struct DX12UnorderedRenderQueue {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12UnorderedRenderQueue(const allocator_type& alloc);
    DX12UnorderedRenderQueue(DX12UnorderedRenderQueue&& rhs, const allocator_type& alloc);
    DX12UnorderedRenderQueue(DX12UnorderedRenderQueue const& rhs, const allocator_type& alloc);
    ~DX12UnorderedRenderQueue();

    std::pmr::vector<boost::intrusive_ptr<DX12ContentData>> mContents;
};

struct DX12GraphicsSubpass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12GraphicsSubpass(const allocator_type& alloc);
    DX12GraphicsSubpass(DX12GraphicsSubpass&& rhs, const allocator_type& alloc);
    DX12GraphicsSubpass(DX12GraphicsSubpass const& rhs, const allocator_type& alloc);
    ~DX12GraphicsSubpass();

    DXGI_SAMPLE_DESC mSampleDesc;
    std::pmr::vector<Attachment> mInputAttachments;
    std::pmr::vector<Attachment> mOutputAttachments;
    std::pmr::vector<Attachment> mResolveAttachments;
    std::optional<Attachment> mDepthStencilAttachment;
    std::pmr::vector<Attachment> mPreserveAttachments;
    std::pmr::vector<RenderViewTransition> mPostViewTransitions;
    std::pmr::vector<DX12UnorderedRenderQueue> mOrderedRenderQueue;
    com_ptr<ID3D12RootSignature> mRootSignature;
    std::pmr::vector<ShaderConstantBuffer> mConstantBuffers;
    std::pmr::vector<DX12ShaderDescriptorCollection> mDescriptors;
};

struct DX12RenderPass {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12RenderPass(const allocator_type& alloc);
    DX12RenderPass(DX12RenderPass&& rhs, const allocator_type& alloc);
    DX12RenderPass(DX12RenderPass const& rhs, const allocator_type& alloc);
    ~DX12RenderPass();

    std::pmr::vector<DX12GraphicsSubpass> mGraphicsSubpasses;
    std::pmr::vector<VIEWPORT> mViewports;
    std::pmr::vector<RECT> mScissorRects;
    std::pmr::vector<FramebufferHandle> mFramebuffers;
    std::pmr::vector<GraphicsSubpassDependency> mDependencies;
};

struct DX12RenderPipeline {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12RenderPipeline(const allocator_type& alloc);
    DX12RenderPipeline(DX12RenderPipeline&& rhs, const allocator_type& alloc);
    DX12RenderPipeline(DX12RenderPipeline const& rhs, const allocator_type& alloc);
    ~DX12RenderPipeline();

    std::pmr::vector<DX12RenderPass> mPasses;
    std::pmr::vector<RenderPassDependency> mDependencies;
    std::pmr::vector<RESOURCE_STATES> mRTVInitialStates;
    std::pmr::vector<RESOURCE_STATES> mDSVInitialStates;
    PmrMap<std::pmr::string, RenderSubpassDesc> mSubpassIndex;
};

struct DX12RenderSolution {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12RenderSolution(const allocator_type& alloc);
    DX12RenderSolution(DX12RenderSolution&& rhs, const allocator_type& alloc);
    DX12RenderSolution(DX12RenderSolution const& rhs, const allocator_type& alloc);
    ~DX12RenderSolution();

    std::pmr::vector<DX12RenderPipeline> mPipelines;
    std::pmr::vector<FramebufferHandle> mRTVSources;
    std::pmr::vector<FramebufferHandle> mDSVSources;
    std::pmr::vector<FramebufferHandle> mCBVSources;
    std::pmr::vector<FramebufferHandle> mSRVSources;
    std::pmr::vector<FramebufferHandle> mUAVSources;
    std::pmr::vector<Framebuffer> mFramebuffers;
    std::pmr::vector<RENDER_TARGET_VIEW_DESC> mRTVs;
    std::pmr::vector<DEPTH_STENCIL_VIEW_DESC> mDSVs;
    std::pmr::vector<CONSTANT_BUFFER_VIEW_DESC> mCBVs;
    std::pmr::vector<SHADER_RESOURCE_VIEW_DESC> mSRVs;
    std::pmr::vector<UNORDERED_ACCESS_VIEW_DESC> mUAVs;
    PmrFlatMap<uint32_t, uint32_t> mAttributeIndex;
    PmrMap<std::pmr::string, uint32_t> mPipelineIndex;
};

struct DX12RenderWorks {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12RenderWorks(const allocator_type& alloc);
    DX12RenderWorks(DX12RenderWorks&& rhs, const allocator_type& alloc);
    DX12RenderWorks(DX12RenderWorks const& rhs, const allocator_type& alloc);
    ~DX12RenderWorks();

    std::pmr::vector<DX12RenderSolution> mSolutions;
    std::pmr::vector<com_ptr<ID3D12Resource>> mFramebuffers;
    DX12DescriptorArray<D3D12_DESCRIPTOR_HEAP_TYPE_RTV> mRTVs;
    DX12DescriptorArray<D3D12_DESCRIPTOR_HEAP_TYPE_DSV> mDSVs;
    DX12DescriptorArray<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV> mCBV_SRV_UAVs;
    uint32_t mNumBackBuffers = 0;
    PmrMap<std::pmr::string, uint32_t> mSolutionIndex;
};

struct DX12RenderGraphData {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12RenderGraphData(const allocator_type& alloc);
    DX12RenderGraphData(MetaID metaID, const allocator_type& alloc);
    DX12RenderGraphData(DX12RenderGraphData&& rhs, const allocator_type& alloc);
    DX12RenderGraphData(DX12RenderGraphData const& rhs, const allocator_type& alloc);
    ~DX12RenderGraphData();

    MetaID mMetaID;
    DX12ShaderDescriptorHeap* mDescriptorHeap = nullptr;
    DX12RenderWorks mRenderGraph;
    PmrFlatMap<std::pmr::string, MetaID> mShaderIndex;
    Core::Fetch<RenderGraphData> mRenderGraphData;
    uint32_t mRefCount = 0;
};

enum DX12TextureEnum : uint32_t {
    White = 0,
};

struct DX12Resources {
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept;

    DX12Resources(const allocator_type& alloc);
    DX12Resources(DX12Resources&& rhs, const allocator_type& alloc);
    DX12Resources(DX12Resources const& rhs, const allocator_type& alloc);
    ~DX12Resources();

    ContentSettings mSettings;
    std::pmr::vector<DX12TextureData> mDefaultTextures;
    PmrMetaIDHashListIndex<DX12MeshData> mMeshes;
    PmrMetaIDHashListIndex<DX12TextureData> mTextures;
    PmrMetaIDHashListIndex<DX12ShaderData> mShaders;
    PmrMetaIDHashListIndex<DX12MaterialData> mMaterials;
    PmrMetaIDHashListIndex<DX12ContentData> mContents;
    PmrMetaIDHashListIndex<DX12RenderGraphData> mRenderGraphs;
};

struct DX12BufferData {
    ID3D12Resource* mResource = nullptr;
    uint64_t mBufferOffset = 0;
};

} // namespace Render

} // namespace Graphics

} // namespace Star
