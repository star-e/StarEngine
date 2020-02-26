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

#include "SRenderGraphTypes.h"

namespace Star {

namespace Graphics {

namespace Render {

UnorderedRenderQueue::allocator_type UnorderedRenderQueue::get_allocator() const noexcept {
    return allocator_type(mContents.get_allocator().resource());
}

UnorderedRenderQueue::UnorderedRenderQueue(const allocator_type& alloc)
    : mContents(alloc)
{}

UnorderedRenderQueue::UnorderedRenderQueue(UnorderedRenderQueue const& rhs, const allocator_type& alloc)
    : mContents(rhs.mContents, alloc)
{}

UnorderedRenderQueue::UnorderedRenderQueue(UnorderedRenderQueue&& rhs, const allocator_type& alloc)
    : mContents(std::move(rhs.mContents), alloc)
{}

UnorderedRenderQueue::~UnorderedRenderQueue() = default;

ShaderDescriptorSubrange::allocator_type ShaderDescriptorSubrange::get_allocator() const noexcept {
    return allocator_type(mDescriptors.get_allocator().resource());
}

ShaderDescriptorSubrange::ShaderDescriptorSubrange(const allocator_type& alloc)
    : mDescriptors(alloc)
{}

ShaderDescriptorSubrange::ShaderDescriptorSubrange(ShaderDescriptorSubrange const& rhs, const allocator_type& alloc)
    : mSource(rhs.mSource)
    , mDescriptors(rhs.mDescriptors, alloc)
{}

ShaderDescriptorSubrange::ShaderDescriptorSubrange(ShaderDescriptorSubrange&& rhs, const allocator_type& alloc)
    : mSource(std::move(rhs.mSource))
    , mDescriptors(std::move(rhs.mDescriptors), alloc)
{}

ShaderDescriptorSubrange::~ShaderDescriptorSubrange() = default;

ShaderDescriptorRange::allocator_type ShaderDescriptorRange::get_allocator() const noexcept {
    return allocator_type(mSubranges.get_allocator().resource());
}

ShaderDescriptorRange::ShaderDescriptorRange(const allocator_type& alloc)
    : mSubranges(alloc)
{}

ShaderDescriptorRange::ShaderDescriptorRange(ShaderDescriptorRange const& rhs, const allocator_type& alloc)
    : mType(rhs.mType)
    , mSubranges(rhs.mSubranges, alloc)
    , mCapacity(rhs.mCapacity)
{}

ShaderDescriptorRange::ShaderDescriptorRange(ShaderDescriptorRange&& rhs, const allocator_type& alloc)
    : mType(std::move(rhs.mType))
    , mSubranges(std::move(rhs.mSubranges), alloc)
    , mCapacity(std::move(rhs.mCapacity))
{}

ShaderDescriptorRange::~ShaderDescriptorRange() = default;

ShaderUnboundedDescriptor::allocator_type ShaderUnboundedDescriptor::get_allocator() const noexcept {
    return allocator_type(mAttribute.get_allocator().resource());
}

ShaderUnboundedDescriptor::ShaderUnboundedDescriptor(const allocator_type& alloc)
    : mAttribute(alloc)
{}

ShaderUnboundedDescriptor::ShaderUnboundedDescriptor(ShaderUnboundedDescriptor const& rhs, const allocator_type& alloc)
    : mType(rhs.mType)
    , mAttribute(rhs.mAttribute, alloc)
    , mCapacity(rhs.mCapacity)
{}

ShaderUnboundedDescriptor::ShaderUnboundedDescriptor(ShaderUnboundedDescriptor&& rhs, const allocator_type& alloc)
    : mType(std::move(rhs.mType))
    , mAttribute(std::move(rhs.mAttribute), alloc)
    , mCapacity(std::move(rhs.mCapacity))
{}

ShaderUnboundedDescriptor::~ShaderUnboundedDescriptor() = default;

ShaderDescriptorList::allocator_type ShaderDescriptorList::get_allocator() const noexcept {
    return allocator_type(mRanges.get_allocator().resource());
}

ShaderDescriptorList::ShaderDescriptorList(const allocator_type& alloc)
    : mRanges(alloc)
    , mUnboundedDescriptors(alloc)
{}

ShaderDescriptorList::ShaderDescriptorList(ShaderDescriptorList const& rhs, const allocator_type& alloc)
    : mSlot(rhs.mSlot)
    , mCapacity(rhs.mCapacity)
    , mRanges(rhs.mRanges, alloc)
    , mUnboundedDescriptors(rhs.mUnboundedDescriptors, alloc)
{}

ShaderDescriptorList::ShaderDescriptorList(ShaderDescriptorList&& rhs, const allocator_type& alloc)
    : mSlot(std::move(rhs.mSlot))
    , mCapacity(std::move(rhs.mCapacity))
    , mRanges(std::move(rhs.mRanges), alloc)
    , mUnboundedDescriptors(std::move(rhs.mUnboundedDescriptors), alloc)
{}

ShaderDescriptorList::~ShaderDescriptorList() = default;

ShaderDescriptorCollection::allocator_type ShaderDescriptorCollection::get_allocator() const noexcept {
    return allocator_type(mResourceViewLists.get_allocator().resource());
}

ShaderDescriptorCollection::ShaderDescriptorCollection(const allocator_type& alloc)
    : mResourceViewLists(alloc)
    , mSamplerLists(alloc)
{}

ShaderDescriptorCollection::ShaderDescriptorCollection(ShaderDescriptorCollection const& rhs, const allocator_type& alloc)
    : mIndex(rhs.mIndex)
    , mResourceViewLists(rhs.mResourceViewLists, alloc)
    , mSamplerLists(rhs.mSamplerLists, alloc)
{}

ShaderDescriptorCollection::ShaderDescriptorCollection(ShaderDescriptorCollection&& rhs, const allocator_type& alloc)
    : mIndex(std::move(rhs.mIndex))
    , mResourceViewLists(std::move(rhs.mResourceViewLists), alloc)
    , mSamplerLists(std::move(rhs.mSamplerLists), alloc)
{}

ShaderDescriptorCollection::~ShaderDescriptorCollection() = default;

ShaderConstantBuffer::allocator_type ShaderConstantBuffer::get_allocator() const noexcept {
    return allocator_type(mConstants.get_allocator().resource());
}

ShaderConstantBuffer::ShaderConstantBuffer(const allocator_type& alloc)
    : mConstants(alloc)
{}

ShaderConstantBuffer::ShaderConstantBuffer(ShaderConstantBuffer const& rhs, const allocator_type& alloc)
    : mIndex(rhs.mIndex)
    , mSize(rhs.mSize)
    , mConstants(rhs.mConstants, alloc)
{}

ShaderConstantBuffer::ShaderConstantBuffer(ShaderConstantBuffer&& rhs, const allocator_type& alloc)
    : mIndex(std::move(rhs.mIndex))
    , mSize(std::move(rhs.mSize))
    , mConstants(std::move(rhs.mConstants), alloc)
{}

ShaderConstantBuffer::~ShaderConstantBuffer() = default;

RasterSubpass::allocator_type RasterSubpass::get_allocator() const noexcept {
    return allocator_type(mInputAttachments.get_allocator().resource());
}

RasterSubpass::RasterSubpass(const allocator_type& alloc)
    : mInputAttachments(alloc)
    , mOutputAttachments(alloc)
    , mResolveAttachments(alloc)
    , mPreserveAttachments(alloc)
    , mSRVs(alloc)
    , mUAVs(alloc)
    , mPostViewTransitions(alloc)
    , mOrderedRenderQueue(alloc)
    , mRootSignature(alloc)
    , mConstantBuffers(alloc)
    , mDescriptors(alloc)
{}

RasterSubpass::RasterSubpass(RasterSubpass const& rhs, const allocator_type& alloc)
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
    , mRootSignature(rhs.mRootSignature, alloc)
    , mConstantBuffers(rhs.mConstantBuffers, alloc)
    , mDescriptors(rhs.mDescriptors, alloc)
{}

RasterSubpass::RasterSubpass(RasterSubpass&& rhs, const allocator_type& alloc)
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
    , mRootSignature(std::move(rhs.mRootSignature), alloc)
    , mConstantBuffers(std::move(rhs.mConstantBuffers), alloc)
    , mDescriptors(std::move(rhs.mDescriptors), alloc)
{}

RasterSubpass::~RasterSubpass() = default;

ComputeSubpass::allocator_type ComputeSubpass::get_allocator() const noexcept {
    return allocator_type(mAttachments.get_allocator().resource());
}

ComputeSubpass::ComputeSubpass(const allocator_type& alloc)
    : mAttachments(alloc)
{}

ComputeSubpass::ComputeSubpass(ComputeSubpass const& rhs, const allocator_type& alloc)
    : mAttachments(rhs.mAttachments, alloc)
{}

ComputeSubpass::ComputeSubpass(ComputeSubpass&& rhs, const allocator_type& alloc)
    : mAttachments(std::move(rhs.mAttachments), alloc)
{}

ComputeSubpass::~ComputeSubpass() = default;

RaytracingSubpass::allocator_type RaytracingSubpass::get_allocator() const noexcept {
    return allocator_type(mOutputAttachments.get_allocator().resource());
}

RaytracingSubpass::RaytracingSubpass(const allocator_type& alloc)
    : mOutputAttachments(alloc)
{}

RaytracingSubpass::RaytracingSubpass(RaytracingSubpass const& rhs, const allocator_type& alloc)
    : mOutputAttachments(rhs.mOutputAttachments, alloc)
{}

RaytracingSubpass::RaytracingSubpass(RaytracingSubpass&& rhs, const allocator_type& alloc)
    : mOutputAttachments(std::move(rhs.mOutputAttachments), alloc)
{}

RaytracingSubpass::~RaytracingSubpass() = default;

RenderPass::allocator_type RenderPass::get_allocator() const noexcept {
    return allocator_type(mViewports.get_allocator().resource());
}

RenderPass::RenderPass(const allocator_type& alloc)
    : mViewports(alloc)
    , mScissorRects(alloc)
    , mFramebuffers(alloc)
    , mRasterSubpasses(alloc)
    , mDependencies(alloc)
    , mComputeSubpasses(alloc)
    , mRaytracingSubpasses(alloc)
{}

RenderPass::RenderPass(RenderPass const& rhs, const allocator_type& alloc)
    : mViewports(rhs.mViewports, alloc)
    , mScissorRects(rhs.mScissorRects, alloc)
    , mFramebuffers(rhs.mFramebuffers, alloc)
    , mRasterSubpasses(rhs.mRasterSubpasses, alloc)
    , mDependencies(rhs.mDependencies, alloc)
    , mComputeSubpasses(rhs.mComputeSubpasses, alloc)
    , mRaytracingSubpasses(rhs.mRaytracingSubpasses, alloc)
{}

RenderPass::RenderPass(RenderPass&& rhs, const allocator_type& alloc)
    : mViewports(std::move(rhs.mViewports), alloc)
    , mScissorRects(std::move(rhs.mScissorRects), alloc)
    , mFramebuffers(std::move(rhs.mFramebuffers), alloc)
    , mRasterSubpasses(std::move(rhs.mRasterSubpasses), alloc)
    , mDependencies(std::move(rhs.mDependencies), alloc)
    , mComputeSubpasses(std::move(rhs.mComputeSubpasses), alloc)
    , mRaytracingSubpasses(std::move(rhs.mRaytracingSubpasses), alloc)
{}

RenderPass::~RenderPass() = default;

RenderPipeline::allocator_type RenderPipeline::get_allocator() const noexcept {
    return allocator_type(mPasses.get_allocator().resource());
}

RenderPipeline::RenderPipeline(const allocator_type& alloc)
    : mPasses(alloc)
    , mDependencies(alloc)
    , mRTVInitialStates(alloc)
    , mDSVInitialStates(alloc)
    , mSubpassIndex(alloc)
{}

RenderPipeline::RenderPipeline(RenderPipeline const& rhs, const allocator_type& alloc)
    : mPasses(rhs.mPasses, alloc)
    , mDependencies(rhs.mDependencies, alloc)
    , mRTVInitialStates(rhs.mRTVInitialStates, alloc)
    , mDSVInitialStates(rhs.mDSVInitialStates, alloc)
    , mSubpassIndex(rhs.mSubpassIndex, alloc)
{}

RenderPipeline::RenderPipeline(RenderPipeline&& rhs, const allocator_type& alloc)
    : mPasses(std::move(rhs.mPasses), alloc)
    , mDependencies(std::move(rhs.mDependencies), alloc)
    , mRTVInitialStates(std::move(rhs.mRTVInitialStates), alloc)
    , mDSVInitialStates(std::move(rhs.mDSVInitialStates), alloc)
    , mSubpassIndex(std::move(rhs.mSubpassIndex), alloc)
{}

RenderPipeline::~RenderPipeline() = default;

RenderSolution::allocator_type RenderSolution::get_allocator() const noexcept {
    return allocator_type(mPipelines.get_allocator().resource());
}

RenderSolution::RenderSolution(const allocator_type& alloc)
    : mPipelines(alloc)
    , mFramebuffers(alloc)
    , mRTVSources(alloc)
    , mDSVSources(alloc)
    , mRTVs(alloc)
    , mDSVs(alloc)
    , mPipelineIndex(alloc)
{}

RenderSolution::RenderSolution(RenderSolution const& rhs, const allocator_type& alloc)
    : mPipelines(rhs.mPipelines, alloc)
    , mFramebuffers(rhs.mFramebuffers, alloc)
    , mRTVSources(rhs.mRTVSources, alloc)
    , mDSVSources(rhs.mDSVSources, alloc)
    , mRTVs(rhs.mRTVs, alloc)
    , mDSVs(rhs.mDSVs, alloc)
    , mPipelineIndex(rhs.mPipelineIndex, alloc)
{}

RenderSolution::RenderSolution(RenderSolution&& rhs, const allocator_type& alloc)
    : mPipelines(std::move(rhs.mPipelines), alloc)
    , mFramebuffers(std::move(rhs.mFramebuffers), alloc)
    , mRTVSources(std::move(rhs.mRTVSources), alloc)
    , mDSVSources(std::move(rhs.mDSVSources), alloc)
    , mRTVs(std::move(rhs.mRTVs), alloc)
    , mDSVs(std::move(rhs.mDSVs), alloc)
    , mPipelineIndex(std::move(rhs.mPipelineIndex), alloc)
{}

RenderSolution::~RenderSolution() = default;

RenderSwapChain::allocator_type RenderSwapChain::get_allocator() const noexcept {
    return allocator_type(mName.get_allocator().resource());
}

RenderSwapChain::RenderSwapChain(const allocator_type& alloc)
    : mName(alloc)
    , mSolutions(alloc)
    , mSolutionIndex(alloc)
{}

RenderSwapChain::RenderSwapChain(RenderSwapChain const& rhs, const allocator_type& alloc)
    : mName(rhs.mName, alloc)
    , mWidth(rhs.mWidth)
    , mHeight(rhs.mHeight)
    , mSolutions(rhs.mSolutions, alloc)
    , mNumBackBuffers(rhs.mNumBackBuffers)
    , mNumReserveFramebuffers(rhs.mNumReserveFramebuffers)
    , mNumReserveSRVs(rhs.mNumReserveSRVs)
    , mNumReserveUAVs(rhs.mNumReserveUAVs)
    , mNumReserveDSVs(rhs.mNumReserveDSVs)
    , mNumReserveRTVs(rhs.mNumReserveRTVs)
    , mSolutionIndex(rhs.mSolutionIndex, alloc)
{}

RenderSwapChain::RenderSwapChain(RenderSwapChain&& rhs, const allocator_type& alloc)
    : mName(std::move(rhs.mName), alloc)
    , mWidth(std::move(rhs.mWidth))
    , mHeight(std::move(rhs.mHeight))
    , mSolutions(std::move(rhs.mSolutions), alloc)
    , mNumBackBuffers(std::move(rhs.mNumBackBuffers))
    , mNumReserveFramebuffers(std::move(rhs.mNumReserveFramebuffers))
    , mNumReserveSRVs(std::move(rhs.mNumReserveSRVs))
    , mNumReserveUAVs(std::move(rhs.mNumReserveUAVs))
    , mNumReserveDSVs(std::move(rhs.mNumReserveDSVs))
    , mNumReserveRTVs(std::move(rhs.mNumReserveRTVs))
    , mSolutionIndex(std::move(rhs.mSolutionIndex), alloc)
{}

RenderSwapChain::~RenderSwapChain() = default;

} // namespace Render

} // namespace Graphics

} // namespace Star
