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

#include "SDX12Types.h"

namespace Star {

namespace Graphics {

namespace Render {

DX12MeshData::allocator_type DX12MeshData::get_allocator() const noexcept {
    return allocator_type(mVertexBufferViews.get_allocator().resource());
}

DX12MeshData::DX12MeshData(const allocator_type& alloc)
    : mVertexBufferViews(alloc)
    , mSubMeshes(alloc)
    , mVertexBuffers(alloc)
    , mLayoutName(alloc)
{}

DX12MeshData::DX12MeshData(MetaID metaID, const allocator_type& alloc)
    : mMetaID(std::move(metaID))
    , mVertexBufferViews(alloc)
    , mSubMeshes(alloc)
    , mVertexBuffers(alloc)
    , mLayoutName(alloc)
{}

DX12MeshData::DX12MeshData(DX12MeshData const& rhs, const allocator_type& alloc)
    : mMetaID(rhs.mMetaID)
    , mVertexBufferViews(rhs.mVertexBufferViews, alloc)
    , mIndexBufferView(rhs.mIndexBufferView)
    , mSubMeshes(rhs.mSubMeshes, alloc)
    , mVertexBuffers(rhs.mVertexBuffers, alloc)
    , mIndexBuffer(rhs.mIndexBuffer)
    , mMeshData(rhs.mMeshData)
    , mRefCount(rhs.mRefCount)
    , mLayoutID(rhs.mLayoutID)
    , mLayoutName(rhs.mLayoutName, alloc)
{}

DX12MeshData::DX12MeshData(DX12MeshData&& rhs, const allocator_type& alloc)
    : mMetaID(std::move(rhs.mMetaID))
    , mVertexBufferViews(std::move(rhs.mVertexBufferViews), alloc)
    , mIndexBufferView(std::move(rhs.mIndexBufferView))
    , mSubMeshes(std::move(rhs.mSubMeshes), alloc)
    , mVertexBuffers(std::move(rhs.mVertexBuffers), alloc)
    , mIndexBuffer(std::move(rhs.mIndexBuffer))
    , mMeshData(std::move(rhs.mMeshData))
    , mRefCount(std::move(rhs.mRefCount))
    , mLayoutID(std::move(rhs.mLayoutID))
    , mLayoutName(std::move(rhs.mLayoutName), alloc)
{}

DX12MeshData::~DX12MeshData() = default;

DX12ShaderSubpassData::allocator_type DX12ShaderSubpassData::get_allocator() const noexcept {
    return allocator_type(mStates.get_allocator().resource());
}

DX12ShaderSubpassData::DX12ShaderSubpassData(const allocator_type& alloc)
    : mStates(alloc)
    , mVertexLayoutIndex(alloc)
    , mConstantBuffers(alloc)
    , mDescriptors(alloc)
{}

DX12ShaderSubpassData::DX12ShaderSubpassData(DX12ShaderSubpassData const& rhs, const allocator_type& alloc)
    : mProgram(rhs.mProgram)
    , mStates(rhs.mStates, alloc)
    , mVertexLayoutIndex(rhs.mVertexLayoutIndex, alloc)
    , mConstantBuffers(rhs.mConstantBuffers, alloc)
    , mDescriptors(rhs.mDescriptors, alloc)
{}

DX12ShaderSubpassData::DX12ShaderSubpassData(DX12ShaderSubpassData&& rhs, const allocator_type& alloc)
    : mProgram(std::move(rhs.mProgram))
    , mStates(std::move(rhs.mStates), alloc)
    , mVertexLayoutIndex(std::move(rhs.mVertexLayoutIndex), alloc)
    , mConstantBuffers(std::move(rhs.mConstantBuffers), alloc)
    , mDescriptors(std::move(rhs.mDescriptors), alloc)
{}

DX12ShaderSubpassData::~DX12ShaderSubpassData() = default;

DX12ShaderPassData::allocator_type DX12ShaderPassData::get_allocator() const noexcept {
    return allocator_type(mSubpasses.get_allocator().resource());
}

DX12ShaderPassData::DX12ShaderPassData(const allocator_type& alloc)
    : mSubpasses(alloc)
{}

DX12ShaderPassData::DX12ShaderPassData(DX12ShaderPassData const& rhs, const allocator_type& alloc)
    : mSubpasses(rhs.mSubpasses, alloc)
{}

DX12ShaderPassData::DX12ShaderPassData(DX12ShaderPassData&& rhs, const allocator_type& alloc)
    : mSubpasses(std::move(rhs.mSubpasses), alloc)
{}

DX12ShaderPassData::~DX12ShaderPassData() = default;

DX12ShaderLevelData::allocator_type DX12ShaderLevelData::get_allocator() const noexcept {
    return allocator_type(mPasses.get_allocator().resource());
}

DX12ShaderLevelData::DX12ShaderLevelData(const allocator_type& alloc)
    : mPasses(alloc)
    , mPassIndex(alloc)
{}

DX12ShaderLevelData::DX12ShaderLevelData(DX12ShaderLevelData const& rhs, const allocator_type& alloc)
    : mPasses(rhs.mPasses, alloc)
    , mPassIndex(rhs.mPassIndex, alloc)
{}

DX12ShaderLevelData::DX12ShaderLevelData(DX12ShaderLevelData&& rhs, const allocator_type& alloc)
    : mPasses(std::move(rhs.mPasses), alloc)
    , mPassIndex(std::move(rhs.mPassIndex), alloc)
{}

DX12ShaderLevelData::~DX12ShaderLevelData() = default;

DX12ShaderQueueData::allocator_type DX12ShaderQueueData::get_allocator() const noexcept {
    return allocator_type(mLevels.get_allocator().resource());
}

DX12ShaderQueueData::DX12ShaderQueueData(const allocator_type& alloc)
    : mLevels(alloc)
{}

DX12ShaderQueueData::DX12ShaderQueueData(DX12ShaderQueueData const& rhs, const allocator_type& alloc)
    : mLevels(rhs.mLevels, alloc)
{}

DX12ShaderQueueData::DX12ShaderQueueData(DX12ShaderQueueData&& rhs, const allocator_type& alloc)
    : mLevels(std::move(rhs.mLevels), alloc)
{}

DX12ShaderQueueData::~DX12ShaderQueueData() = default;

DX12ShaderPipelineData::allocator_type DX12ShaderPipelineData::get_allocator() const noexcept {
    return allocator_type(mQueues.get_allocator().resource());
}

DX12ShaderPipelineData::DX12ShaderPipelineData(const allocator_type& alloc)
    : mQueues(alloc)
    , mQueueIndex(alloc)
{}

DX12ShaderPipelineData::DX12ShaderPipelineData(DX12ShaderPipelineData const& rhs, const allocator_type& alloc)
    : mQueues(rhs.mQueues, alloc)
    , mQueueIndex(rhs.mQueueIndex, alloc)
{}

DX12ShaderPipelineData::DX12ShaderPipelineData(DX12ShaderPipelineData&& rhs, const allocator_type& alloc)
    : mQueues(std::move(rhs.mQueues), alloc)
    , mQueueIndex(std::move(rhs.mQueueIndex), alloc)
{}

DX12ShaderPipelineData::~DX12ShaderPipelineData() = default;

DX12ShaderSolutionData::allocator_type DX12ShaderSolutionData::get_allocator() const noexcept {
    return allocator_type(mPipelines.get_allocator().resource());
}

DX12ShaderSolutionData::DX12ShaderSolutionData(const allocator_type& alloc)
    : mPipelines(alloc)
    , mPipelineIndex(alloc)
{}

DX12ShaderSolutionData::DX12ShaderSolutionData(DX12ShaderSolutionData const& rhs, const allocator_type& alloc)
    : mPipelines(rhs.mPipelines, alloc)
    , mPipelineIndex(rhs.mPipelineIndex, alloc)
{}

DX12ShaderSolutionData::DX12ShaderSolutionData(DX12ShaderSolutionData&& rhs, const allocator_type& alloc)
    : mPipelines(std::move(rhs.mPipelines), alloc)
    , mPipelineIndex(std::move(rhs.mPipelineIndex), alloc)
{}

DX12ShaderSolutionData::~DX12ShaderSolutionData() = default;

DX12ShaderData::allocator_type DX12ShaderData::get_allocator() const noexcept {
    return allocator_type(mSolutions.get_allocator().resource());
}

DX12ShaderData::DX12ShaderData(const allocator_type& alloc)
    : mSolutions(alloc)
    , mSolutionIndex(alloc)
{}

DX12ShaderData::DX12ShaderData(MetaID metaID, const allocator_type& alloc)
    : mMetaID(std::move(metaID))
    , mSolutions(alloc)
    , mSolutionIndex(alloc)
{}

DX12ShaderData::DX12ShaderData(DX12ShaderData const& rhs, const allocator_type& alloc)
    : mMetaID(rhs.mMetaID)
    , mSolutions(rhs.mSolutions, alloc)
    , mSolutionIndex(rhs.mSolutionIndex, alloc)
    , mShaderData(rhs.mShaderData)
    , mRefCount(rhs.mRefCount)
{}

DX12ShaderData::DX12ShaderData(DX12ShaderData&& rhs, const allocator_type& alloc)
    : mMetaID(std::move(rhs.mMetaID))
    , mSolutions(std::move(rhs.mSolutions), alloc)
    , mSolutionIndex(std::move(rhs.mSolutionIndex), alloc)
    , mShaderData(std::move(rhs.mShaderData))
    , mRefCount(std::move(rhs.mRefCount))
{}

DX12ShaderData::~DX12ShaderData() = default;

DX12MaterialDescriptorList::allocator_type DX12MaterialDescriptorList::get_allocator() const noexcept {
    return allocator_type(mRanges.get_allocator().resource());
}

DX12MaterialDescriptorList::DX12MaterialDescriptorList(const allocator_type& alloc)
    : mRanges(alloc)
    , mUnboundedDescriptors(alloc)
{}

DX12MaterialDescriptorList::DX12MaterialDescriptorList(DX12MaterialDescriptorList const& rhs, const allocator_type& alloc)
    : mSlot(rhs.mSlot)
    , mCapacity(rhs.mCapacity)
    , mGpuOffset(rhs.mGpuOffset)
    , mCpuOffset(rhs.mCpuOffset)
    , mRanges(rhs.mRanges, alloc)
    , mUnboundedDescriptors(rhs.mUnboundedDescriptors, alloc)
{}

DX12MaterialDescriptorList::DX12MaterialDescriptorList(DX12MaterialDescriptorList&& rhs, const allocator_type& alloc)
    : mSlot(std::move(rhs.mSlot))
    , mCapacity(std::move(rhs.mCapacity))
    , mGpuOffset(std::move(rhs.mGpuOffset))
    , mCpuOffset(std::move(rhs.mCpuOffset))
    , mRanges(std::move(rhs.mRanges), alloc)
    , mUnboundedDescriptors(std::move(rhs.mUnboundedDescriptors), alloc)
{}

DX12MaterialDescriptorList::~DX12MaterialDescriptorList() = default;

DX12MaterialDescriptorCollection::allocator_type DX12MaterialDescriptorCollection::get_allocator() const noexcept {
    return allocator_type(mResourceViewLists.get_allocator().resource());
}

DX12MaterialDescriptorCollection::DX12MaterialDescriptorCollection(const allocator_type& alloc)
    : mResourceViewLists(alloc)
    , mSamplerLists(alloc)
{}

DX12MaterialDescriptorCollection::DX12MaterialDescriptorCollection(DX12MaterialDescriptorCollection const& rhs, const allocator_type& alloc)
    : mIndex(rhs.mIndex)
    , mResourceViewLists(rhs.mResourceViewLists, alloc)
    , mSamplerLists(rhs.mSamplerLists, alloc)
{}

DX12MaterialDescriptorCollection::DX12MaterialDescriptorCollection(DX12MaterialDescriptorCollection&& rhs, const allocator_type& alloc)
    : mIndex(std::move(rhs.mIndex))
    , mResourceViewLists(std::move(rhs.mResourceViewLists), alloc)
    , mSamplerLists(std::move(rhs.mSamplerLists), alloc)
{}

DX12MaterialDescriptorCollection::~DX12MaterialDescriptorCollection() = default;

DX12MaterialSubpassData::allocator_type DX12MaterialSubpassData::get_allocator() const noexcept {
    return allocator_type(mCollections.get_allocator().resource());
}

DX12MaterialSubpassData::DX12MaterialSubpassData(const allocator_type& alloc)
    : mCollections(alloc)
{}

DX12MaterialSubpassData::DX12MaterialSubpassData(DX12MaterialSubpassData const& rhs, const allocator_type& alloc)
    : mCollections(rhs.mCollections, alloc)
{}

DX12MaterialSubpassData::DX12MaterialSubpassData(DX12MaterialSubpassData&& rhs, const allocator_type& alloc)
    : mCollections(std::move(rhs.mCollections), alloc)
{}

DX12MaterialSubpassData::~DX12MaterialSubpassData() = default;

DX12MaterialPassData::allocator_type DX12MaterialPassData::get_allocator() const noexcept {
    return allocator_type(mSubpasses.get_allocator().resource());
}

DX12MaterialPassData::DX12MaterialPassData(const allocator_type& alloc)
    : mSubpasses(alloc)
{}

DX12MaterialPassData::DX12MaterialPassData(DX12MaterialPassData const& rhs, const allocator_type& alloc)
    : mSubpasses(rhs.mSubpasses, alloc)
{}

DX12MaterialPassData::DX12MaterialPassData(DX12MaterialPassData&& rhs, const allocator_type& alloc)
    : mSubpasses(std::move(rhs.mSubpasses), alloc)
{}

DX12MaterialPassData::~DX12MaterialPassData() = default;

DX12MaterialLevelData::allocator_type DX12MaterialLevelData::get_allocator() const noexcept {
    return allocator_type(mPasses.get_allocator().resource());
}

DX12MaterialLevelData::DX12MaterialLevelData(const allocator_type& alloc)
    : mPasses(alloc)
{}

DX12MaterialLevelData::DX12MaterialLevelData(DX12MaterialLevelData const& rhs, const allocator_type& alloc)
    : mPasses(rhs.mPasses, alloc)
{}

DX12MaterialLevelData::DX12MaterialLevelData(DX12MaterialLevelData&& rhs, const allocator_type& alloc)
    : mPasses(std::move(rhs.mPasses), alloc)
{}

DX12MaterialLevelData::~DX12MaterialLevelData() = default;

DX12MaterialQueueData::allocator_type DX12MaterialQueueData::get_allocator() const noexcept {
    return allocator_type(mLevels.get_allocator().resource());
}

DX12MaterialQueueData::DX12MaterialQueueData(const allocator_type& alloc)
    : mLevels(alloc)
{}

DX12MaterialQueueData::DX12MaterialQueueData(DX12MaterialQueueData const& rhs, const allocator_type& alloc)
    : mLevels(rhs.mLevels, alloc)
{}

DX12MaterialQueueData::DX12MaterialQueueData(DX12MaterialQueueData&& rhs, const allocator_type& alloc)
    : mLevels(std::move(rhs.mLevels), alloc)
{}

DX12MaterialQueueData::~DX12MaterialQueueData() = default;

DX12MaterialPipelineData::allocator_type DX12MaterialPipelineData::get_allocator() const noexcept {
    return allocator_type(mQueues.get_allocator().resource());
}

DX12MaterialPipelineData::DX12MaterialPipelineData(const allocator_type& alloc)
    : mQueues(alloc)
{}

DX12MaterialPipelineData::DX12MaterialPipelineData(DX12MaterialPipelineData const& rhs, const allocator_type& alloc)
    : mQueues(rhs.mQueues, alloc)
{}

DX12MaterialPipelineData::DX12MaterialPipelineData(DX12MaterialPipelineData&& rhs, const allocator_type& alloc)
    : mQueues(std::move(rhs.mQueues), alloc)
{}

DX12MaterialPipelineData::~DX12MaterialPipelineData() = default;

DX12MaterialSolutionData::allocator_type DX12MaterialSolutionData::get_allocator() const noexcept {
    return allocator_type(mPipelines.get_allocator().resource());
}

DX12MaterialSolutionData::DX12MaterialSolutionData(const allocator_type& alloc)
    : mPipelines(alloc)
{}

DX12MaterialSolutionData::DX12MaterialSolutionData(DX12MaterialSolutionData const& rhs, const allocator_type& alloc)
    : mPipelines(rhs.mPipelines, alloc)
{}

DX12MaterialSolutionData::DX12MaterialSolutionData(DX12MaterialSolutionData&& rhs, const allocator_type& alloc)
    : mPipelines(std::move(rhs.mPipelines), alloc)
{}

DX12MaterialSolutionData::~DX12MaterialSolutionData() = default;

DX12MaterialData::allocator_type DX12MaterialData::get_allocator() const noexcept {
    return allocator_type(mShaderData.get_allocator().resource());
}

DX12MaterialData::DX12MaterialData(const allocator_type& alloc)
    : mShaderData(alloc)
    , mTextures(alloc)
    , mConstantMap(alloc)
{}

DX12MaterialData::DX12MaterialData(MetaID metaID, const allocator_type& alloc)
    : mMetaID(std::move(metaID))
    , mShaderData(alloc)
    , mTextures(alloc)
    , mConstantMap(alloc)
{}

DX12MaterialData::DX12MaterialData(DX12MaterialData const& rhs, const allocator_type& alloc)
    : mMetaID(rhs.mMetaID)
    , mShader(rhs.mShader)
    , mDescriptorHeap(rhs.mDescriptorHeap)
    , mShaderData(rhs.mShaderData, alloc)
    , mTextures(rhs.mTextures, alloc)
    , mConstantMap(rhs.mConstantMap, alloc)
    , mMaterialData(rhs.mMaterialData)
    , mRefCount(rhs.mRefCount)
{}

DX12MaterialData::DX12MaterialData(DX12MaterialData&& rhs, const allocator_type& alloc)
    : mMetaID(std::move(rhs.mMetaID))
    , mShader(std::move(rhs.mShader))
    , mDescriptorHeap(std::move(rhs.mDescriptorHeap))
    , mShaderData(std::move(rhs.mShaderData), alloc)
    , mTextures(std::move(rhs.mTextures), alloc)
    , mConstantMap(std::move(rhs.mConstantMap), alloc)
    , mMaterialData(std::move(rhs.mMaterialData))
    , mRefCount(std::move(rhs.mRefCount))
{}

DX12MaterialData::~DX12MaterialData() = default;

DX12DrawCallData::allocator_type DX12DrawCallData::get_allocator() const noexcept {
    return allocator_type(mConstantMap.get_allocator().resource());
}

DX12DrawCallData::DX12DrawCallData(const allocator_type& alloc)
    : mConstantMap(alloc)
{}

DX12DrawCallData::DX12DrawCallData(DX12DrawCallData const& rhs, const allocator_type& alloc)
    : mType(rhs.mType)
    , mMesh(rhs.mMesh)
    , mMaterial(rhs.mMaterial)
    , mInstanceSize(rhs.mInstanceSize)
    , mInstanceCount(rhs.mInstanceCount)
    , mConstantMap(rhs.mConstantMap, alloc)
{}

DX12DrawCallData::DX12DrawCallData(DX12DrawCallData&& rhs, const allocator_type& alloc)
    : mType(std::move(rhs.mType))
    , mMesh(std::move(rhs.mMesh))
    , mMaterial(std::move(rhs.mMaterial))
    , mInstanceSize(std::move(rhs.mInstanceSize))
    , mInstanceCount(std::move(rhs.mInstanceCount))
    , mConstantMap(std::move(rhs.mConstantMap), alloc)
{}

DX12DrawCallData::~DX12DrawCallData() = default;

DX12MeshRenderer::allocator_type DX12MeshRenderer::get_allocator() const noexcept {
    return allocator_type(mMaterials.get_allocator().resource());
}

DX12MeshRenderer::DX12MeshRenderer(const allocator_type& alloc)
    : mMaterials(alloc)
{}

DX12MeshRenderer::DX12MeshRenderer(DX12MeshRenderer const& rhs, const allocator_type& alloc)
    : mMesh(rhs.mMesh)
    , mMaterials(rhs.mMaterials, alloc)
{}

DX12MeshRenderer::DX12MeshRenderer(DX12MeshRenderer&& rhs, const allocator_type& alloc)
    : mMesh(std::move(rhs.mMesh))
    , mMaterials(std::move(rhs.mMaterials), alloc)
{}

DX12MeshRenderer::~DX12MeshRenderer() = default;

DX12FlattenedObjects::allocator_type DX12FlattenedObjects::get_allocator() const noexcept {
    return allocator_type(mWorldTransforms.get_allocator().resource());
}

DX12FlattenedObjects::DX12FlattenedObjects(const allocator_type& alloc)
    : mWorldTransforms(alloc)
    , mWorldTransformInvs(alloc)
    , mBoundingBoxes(alloc)
    , mMeshRenderers(alloc)
{}

DX12FlattenedObjects::DX12FlattenedObjects(DX12FlattenedObjects const& rhs, const allocator_type& alloc)
    : mWorldTransforms(rhs.mWorldTransforms, alloc)
    , mWorldTransformInvs(rhs.mWorldTransformInvs, alloc)
    , mBoundingBoxes(rhs.mBoundingBoxes, alloc)
    , mMeshRenderers(rhs.mMeshRenderers, alloc)
{}

DX12FlattenedObjects::DX12FlattenedObjects(DX12FlattenedObjects&& rhs, const allocator_type& alloc)
    : mWorldTransforms(std::move(rhs.mWorldTransforms), alloc)
    , mWorldTransformInvs(std::move(rhs.mWorldTransformInvs), alloc)
    , mBoundingBoxes(std::move(rhs.mBoundingBoxes), alloc)
    , mMeshRenderers(std::move(rhs.mMeshRenderers), alloc)
{}

DX12FlattenedObjects::~DX12FlattenedObjects() = default;

DX12ContentData::allocator_type DX12ContentData::get_allocator() const noexcept {
    return allocator_type(mIDs.get_allocator().resource());
}

DX12ContentData::DX12ContentData(const allocator_type& alloc)
    : mIDs(alloc)
    , mDrawCalls(alloc)
    , mFlattenedObjects(alloc)
{}

DX12ContentData::DX12ContentData(MetaID metaID, const allocator_type& alloc)
    : mMetaID(std::move(metaID))
    , mIDs(alloc)
    , mDrawCalls(alloc)
    , mFlattenedObjects(alloc)
{}

DX12ContentData::DX12ContentData(DX12ContentData const& rhs, const allocator_type& alloc)
    : mMetaID(rhs.mMetaID)
    , mIDs(rhs.mIDs, alloc)
    , mDrawCalls(rhs.mDrawCalls, alloc)
    , mFlattenedObjects(rhs.mFlattenedObjects, alloc)
    , mContentData(rhs.mContentData)
    , mRefCount(rhs.mRefCount)
{}

DX12ContentData::DX12ContentData(DX12ContentData&& rhs, const allocator_type& alloc)
    : mMetaID(std::move(rhs.mMetaID))
    , mIDs(std::move(rhs.mIDs), alloc)
    , mDrawCalls(std::move(rhs.mDrawCalls), alloc)
    , mFlattenedObjects(std::move(rhs.mFlattenedObjects), alloc)
    , mContentData(std::move(rhs.mContentData))
    , mRefCount(std::move(rhs.mRefCount))
{}

DX12ContentData::~DX12ContentData() = default;

DX12UnorderedRenderQueue::allocator_type DX12UnorderedRenderQueue::get_allocator() const noexcept {
    return allocator_type(mContents.get_allocator().resource());
}

DX12UnorderedRenderQueue::DX12UnorderedRenderQueue(const allocator_type& alloc)
    : mContents(alloc)
{}

DX12UnorderedRenderQueue::DX12UnorderedRenderQueue(DX12UnorderedRenderQueue const& rhs, const allocator_type& alloc)
    : mContents(rhs.mContents, alloc)
{}

DX12UnorderedRenderQueue::DX12UnorderedRenderQueue(DX12UnorderedRenderQueue&& rhs, const allocator_type& alloc)
    : mContents(std::move(rhs.mContents), alloc)
{}

DX12UnorderedRenderQueue::~DX12UnorderedRenderQueue() = default;

DX12RenderSubpass::allocator_type DX12RenderSubpass::get_allocator() const noexcept {
    return allocator_type(mInputAttachments.get_allocator().resource());
}

DX12RenderSubpass::DX12RenderSubpass(const allocator_type& alloc)
    : mInputAttachments(alloc)
    , mOutputAttachments(alloc)
    , mResolveAttachments(alloc)
    , mPreserveAttachments(alloc)
    , mSRVs(alloc)
    , mUAVs(alloc)
    , mPostViewTransitions(alloc)
    , mOrderedRenderQueue(alloc)
    , mConstantBuffers(alloc)
    , mDescriptors(alloc)
{}

DX12RenderSubpass::DX12RenderSubpass(DX12RenderSubpass const& rhs, const allocator_type& alloc)
    : mSampleDesc(rhs.mSampleDesc)
    , mInputAttachments(rhs.mInputAttachments, alloc)
    , mOutputAttachments(rhs.mOutputAttachments, alloc)
    , mResolveAttachments(rhs.mResolveAttachments, alloc)
    , mDepthStencilAttachment(rhs.mDepthStencilAttachment)
    , mPreserveAttachments(rhs.mPreserveAttachments, alloc)
    , mSRVs(rhs.mSRVs, alloc)
    , mUAVs(rhs.mUAVs, alloc)
    , mPostViewTransitions(rhs.mPostViewTransitions, alloc)
    , mOrderedRenderQueue(rhs.mOrderedRenderQueue, alloc)
    , mRootSignature(rhs.mRootSignature)
    , mConstantBuffers(rhs.mConstantBuffers, alloc)
    , mDescriptors(rhs.mDescriptors, alloc)
{}

DX12RenderSubpass::DX12RenderSubpass(DX12RenderSubpass&& rhs, const allocator_type& alloc)
    : mSampleDesc(std::move(rhs.mSampleDesc))
    , mInputAttachments(std::move(rhs.mInputAttachments), alloc)
    , mOutputAttachments(std::move(rhs.mOutputAttachments), alloc)
    , mResolveAttachments(std::move(rhs.mResolveAttachments), alloc)
    , mDepthStencilAttachment(std::move(rhs.mDepthStencilAttachment))
    , mPreserveAttachments(std::move(rhs.mPreserveAttachments), alloc)
    , mSRVs(std::move(rhs.mSRVs), alloc)
    , mUAVs(std::move(rhs.mUAVs), alloc)
    , mPostViewTransitions(std::move(rhs.mPostViewTransitions), alloc)
    , mOrderedRenderQueue(std::move(rhs.mOrderedRenderQueue), alloc)
    , mRootSignature(std::move(rhs.mRootSignature))
    , mConstantBuffers(std::move(rhs.mConstantBuffers), alloc)
    , mDescriptors(std::move(rhs.mDescriptors), alloc)
{}

DX12RenderSubpass::~DX12RenderSubpass() = default;

DX12RenderPass::allocator_type DX12RenderPass::get_allocator() const noexcept {
    return allocator_type(mSubpasses.get_allocator().resource());
}

DX12RenderPass::DX12RenderPass(const allocator_type& alloc)
    : mSubpasses(alloc)
    , mViewports(alloc)
    , mScissorRects(alloc)
    , mFramebuffers(alloc)
    , mDependencies(alloc)
{}

DX12RenderPass::DX12RenderPass(DX12RenderPass const& rhs, const allocator_type& alloc)
    : mSubpasses(rhs.mSubpasses, alloc)
    , mViewports(rhs.mViewports, alloc)
    , mScissorRects(rhs.mScissorRects, alloc)
    , mFramebuffers(rhs.mFramebuffers, alloc)
    , mDependencies(rhs.mDependencies, alloc)
{}

DX12RenderPass::DX12RenderPass(DX12RenderPass&& rhs, const allocator_type& alloc)
    : mSubpasses(std::move(rhs.mSubpasses), alloc)
    , mViewports(std::move(rhs.mViewports), alloc)
    , mScissorRects(std::move(rhs.mScissorRects), alloc)
    , mFramebuffers(std::move(rhs.mFramebuffers), alloc)
    , mDependencies(std::move(rhs.mDependencies), alloc)
{}

DX12RenderPass::~DX12RenderPass() = default;

DX12RenderPipeline::allocator_type DX12RenderPipeline::get_allocator() const noexcept {
    return allocator_type(mPasses.get_allocator().resource());
}

DX12RenderPipeline::DX12RenderPipeline(const allocator_type& alloc)
    : mPasses(alloc)
    , mDependencies(alloc)
    , mRTVInitialStates(alloc)
    , mDSVInitialStates(alloc)
    , mSubpassIndex(alloc)
{}

DX12RenderPipeline::DX12RenderPipeline(DX12RenderPipeline const& rhs, const allocator_type& alloc)
    : mPasses(rhs.mPasses, alloc)
    , mDependencies(rhs.mDependencies, alloc)
    , mRTVInitialStates(rhs.mRTVInitialStates, alloc)
    , mDSVInitialStates(rhs.mDSVInitialStates, alloc)
    , mSubpassIndex(rhs.mSubpassIndex, alloc)
{}

DX12RenderPipeline::DX12RenderPipeline(DX12RenderPipeline&& rhs, const allocator_type& alloc)
    : mPasses(std::move(rhs.mPasses), alloc)
    , mDependencies(std::move(rhs.mDependencies), alloc)
    , mRTVInitialStates(std::move(rhs.mRTVInitialStates), alloc)
    , mDSVInitialStates(std::move(rhs.mDSVInitialStates), alloc)
    , mSubpassIndex(std::move(rhs.mSubpassIndex), alloc)
{}

DX12RenderPipeline::~DX12RenderPipeline() = default;

DX12RenderSolution::allocator_type DX12RenderSolution::get_allocator() const noexcept {
    return allocator_type(mPipelines.get_allocator().resource());
}

DX12RenderSolution::DX12RenderSolution(const allocator_type& alloc)
    : mPipelines(alloc)
    , mRTVSources(alloc)
    , mDSVSources(alloc)
    , mFramebuffers(alloc)
    , mRTVs(alloc)
    , mDSVs(alloc)
    , mPipelineIndex(alloc)
{}

DX12RenderSolution::DX12RenderSolution(DX12RenderSolution const& rhs, const allocator_type& alloc)
    : mPipelines(rhs.mPipelines, alloc)
    , mRTVSources(rhs.mRTVSources, alloc)
    , mDSVSources(rhs.mDSVSources, alloc)
    , mFramebuffers(rhs.mFramebuffers, alloc)
    , mRTVs(rhs.mRTVs, alloc)
    , mDSVs(rhs.mDSVs, alloc)
    , mPipelineIndex(rhs.mPipelineIndex, alloc)
{}

DX12RenderSolution::DX12RenderSolution(DX12RenderSolution&& rhs, const allocator_type& alloc)
    : mPipelines(std::move(rhs.mPipelines), alloc)
    , mRTVSources(std::move(rhs.mRTVSources), alloc)
    , mDSVSources(std::move(rhs.mDSVSources), alloc)
    , mFramebuffers(std::move(rhs.mFramebuffers), alloc)
    , mRTVs(std::move(rhs.mRTVs), alloc)
    , mDSVs(std::move(rhs.mDSVs), alloc)
    , mPipelineIndex(std::move(rhs.mPipelineIndex), alloc)
{}

DX12RenderSolution::~DX12RenderSolution() = default;

DX12RenderWorks::allocator_type DX12RenderWorks::get_allocator() const noexcept {
    return allocator_type(mSolutions.get_allocator().resource());
}

DX12RenderWorks::DX12RenderWorks(const allocator_type& alloc)
    : mSolutions(alloc)
    , mFramebuffers(alloc)
    , mSolutionIndex(alloc)
{}

DX12RenderWorks::DX12RenderWorks(DX12RenderWorks const& rhs, const allocator_type& alloc)
    : mSolutions(rhs.mSolutions, alloc)
    , mFramebuffers(rhs.mFramebuffers, alloc)
    , mRTVs(rhs.mRTVs)
    , mDSVs(rhs.mDSVs)
    , mNumBackBuffers(rhs.mNumBackBuffers)
    , mSolutionIndex(rhs.mSolutionIndex, alloc)
{}

DX12RenderWorks::DX12RenderWorks(DX12RenderWorks&& rhs, const allocator_type& alloc)
    : mSolutions(std::move(rhs.mSolutions), alloc)
    , mFramebuffers(std::move(rhs.mFramebuffers), alloc)
    , mRTVs(std::move(rhs.mRTVs))
    , mDSVs(std::move(rhs.mDSVs))
    , mNumBackBuffers(std::move(rhs.mNumBackBuffers))
    , mSolutionIndex(std::move(rhs.mSolutionIndex), alloc)
{}

DX12RenderWorks::~DX12RenderWorks() = default;

DX12RenderGraphData::allocator_type DX12RenderGraphData::get_allocator() const noexcept {
    return allocator_type(mRenderGraph.get_allocator().resource());
}

DX12RenderGraphData::DX12RenderGraphData(const allocator_type& alloc)
    : mRenderGraph(alloc)
    , mShaderIndex(alloc)
{}

DX12RenderGraphData::DX12RenderGraphData(MetaID metaID, const allocator_type& alloc)
    : mMetaID(std::move(metaID))
    , mRenderGraph(alloc)
    , mShaderIndex(alloc)
{}

DX12RenderGraphData::DX12RenderGraphData(DX12RenderGraphData const& rhs, const allocator_type& alloc)
    : mMetaID(rhs.mMetaID)
    , mRenderGraph(rhs.mRenderGraph, alloc)
    , mShaderIndex(rhs.mShaderIndex, alloc)
    , mRenderGraphData(rhs.mRenderGraphData)
    , mRefCount(rhs.mRefCount)
{}

DX12RenderGraphData::DX12RenderGraphData(DX12RenderGraphData&& rhs, const allocator_type& alloc)
    : mMetaID(std::move(rhs.mMetaID))
    , mRenderGraph(std::move(rhs.mRenderGraph), alloc)
    , mShaderIndex(std::move(rhs.mShaderIndex), alloc)
    , mRenderGraphData(std::move(rhs.mRenderGraphData))
    , mRefCount(std::move(rhs.mRefCount))
{}

DX12RenderGraphData::~DX12RenderGraphData() = default;

DX12Resources::allocator_type DX12Resources::get_allocator() const noexcept {
    return allocator_type(mSettings.get_allocator().resource());
}

DX12Resources::DX12Resources(const allocator_type& alloc)
    : mSettings(alloc)
    , mDefaultTextures(alloc)
    , mMeshes(alloc)
    , mTextures(alloc)
    , mShaders(alloc)
    , mMaterials(alloc)
    , mContents(alloc)
    , mRenderGraphs(alloc)
{}

DX12Resources::DX12Resources(DX12Resources const& rhs, const allocator_type& alloc)
    : mSettings(rhs.mSettings, alloc)
    , mDefaultTextures(rhs.mDefaultTextures, alloc)
    , mMeshes(rhs.mMeshes, alloc)
    , mTextures(rhs.mTextures, alloc)
    , mShaders(rhs.mShaders, alloc)
    , mMaterials(rhs.mMaterials, alloc)
    , mContents(rhs.mContents, alloc)
    , mRenderGraphs(rhs.mRenderGraphs, alloc)
{}

DX12Resources::DX12Resources(DX12Resources&& rhs, const allocator_type& alloc)
    : mSettings(std::move(rhs.mSettings), alloc)
    , mDefaultTextures(std::move(rhs.mDefaultTextures), alloc)
    , mMeshes(std::move(rhs.mMeshes), alloc)
    , mTextures(std::move(rhs.mTextures), alloc)
    , mShaders(std::move(rhs.mShaders), alloc)
    , mMaterials(std::move(rhs.mMaterials), alloc)
    , mContents(std::move(rhs.mContents), alloc)
    , mRenderGraphs(std::move(rhs.mRenderGraphs), alloc)
{}

DX12Resources::~DX12Resources() = default;

} // namespace Render

} // namespace Graphics

} // namespace Star
