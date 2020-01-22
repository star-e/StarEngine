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

#include "SContentTypes.h"

namespace Star {

namespace Graphics {

namespace Render {

VertexBufferDesc::allocator_type VertexBufferDesc::get_allocator() const noexcept {
    return allocator_type(mElements.get_allocator().resource());
}

VertexBufferDesc::VertexBufferDesc(const allocator_type& alloc)
    : mElements(alloc)
{}

VertexBufferDesc::VertexBufferDesc(VertexBufferDesc const& rhs, const allocator_type& alloc)
    : mElements(rhs.mElements, alloc)
    , mVertexSize(rhs.mVertexSize)
{}

VertexBufferDesc::VertexBufferDesc(VertexBufferDesc&& rhs, const allocator_type& alloc)
    : mElements(std::move(rhs.mElements), alloc)
    , mVertexSize(std::move(rhs.mVertexSize))
{}

VertexBufferDesc::~VertexBufferDesc() = default;

MeshBufferLayout::allocator_type MeshBufferLayout::get_allocator() const noexcept {
    return allocator_type(mBuffers.get_allocator().resource());
}

MeshBufferLayout::MeshBufferLayout(const allocator_type& alloc)
    : mBuffers(alloc)
    , mIndex(alloc)
{}

MeshBufferLayout::MeshBufferLayout(MeshBufferLayout const& rhs, const allocator_type& alloc)
    : mBuffers(rhs.mBuffers, alloc)
    , mIndex(rhs.mIndex, alloc)
    , mStripCutValue(rhs.mStripCutValue)
    , mPrimitiveTopologyType(rhs.mPrimitiveTopologyType)
{}

MeshBufferLayout::MeshBufferLayout(MeshBufferLayout&& rhs, const allocator_type& alloc)
    : mBuffers(std::move(rhs.mBuffers), alloc)
    , mIndex(std::move(rhs.mIndex), alloc)
    , mStripCutValue(std::move(rhs.mStripCutValue))
    , mPrimitiveTopologyType(std::move(rhs.mPrimitiveTopologyType))
{}

MeshBufferLayout::~MeshBufferLayout() = default;

VertexBufferData::allocator_type VertexBufferData::get_allocator() const noexcept {
    return allocator_type(mDesc.get_allocator().resource());
}

VertexBufferData::VertexBufferData(const allocator_type& alloc)
    : mDesc(alloc)
    , mBuffer(alloc)
{}

VertexBufferData::VertexBufferData(VertexBufferData const& rhs, const allocator_type& alloc)
    : mDesc(rhs.mDesc, alloc)
    , mVertexCount(rhs.mVertexCount)
    , mBuffer(rhs.mBuffer, alloc)
{}

VertexBufferData::VertexBufferData(VertexBufferData&& rhs, const allocator_type& alloc)
    : mDesc(std::move(rhs.mDesc), alloc)
    , mVertexCount(std::move(rhs.mVertexCount))
    , mBuffer(std::move(rhs.mBuffer), alloc)
{}

VertexBufferData::~VertexBufferData() = default;

IndexBufferData::allocator_type IndexBufferData::get_allocator() const noexcept {
    return allocator_type(mBuffer.get_allocator().resource());
}

IndexBufferData::IndexBufferData(const allocator_type& alloc)
    : mBuffer(alloc)
{}

IndexBufferData::IndexBufferData(IndexBufferData const& rhs, const allocator_type& alloc)
    : mBuffer(rhs.mBuffer, alloc)
    , mElementSize(rhs.mElementSize)
    , mPrimitiveCount(rhs.mPrimitiveCount)
    , mPrimitiveTopology(rhs.mPrimitiveTopology)
{}

IndexBufferData::IndexBufferData(IndexBufferData&& rhs, const allocator_type& alloc)
    : mBuffer(std::move(rhs.mBuffer), alloc)
    , mElementSize(std::move(rhs.mElementSize))
    , mPrimitiveCount(std::move(rhs.mPrimitiveCount))
    , mPrimitiveTopology(std::move(rhs.mPrimitiveTopology))
{}

IndexBufferData::~IndexBufferData() = default;

MeshData::allocator_type MeshData::get_allocator() const noexcept {
    return allocator_type(mVertexBuffers.get_allocator().resource());
}

MeshData::MeshData(const allocator_type& alloc)
    : mVertexBuffers(alloc)
    , mIndexBuffer(alloc)
    , mSubMeshes(alloc)
    , mLayoutName(alloc)
{}

MeshData::MeshData(MeshData const& rhs, const allocator_type& alloc)
    : mVertexBuffers(rhs.mVertexBuffers, alloc)
    , mIndexBuffer(rhs.mIndexBuffer, alloc)
    , mSubMeshes(rhs.mSubMeshes, alloc)
    , mLayoutID(rhs.mLayoutID)
    , mLayoutName(rhs.mLayoutName, alloc)
{}

MeshData::MeshData(MeshData&& rhs, const allocator_type& alloc)
    : mVertexBuffers(std::move(rhs.mVertexBuffers), alloc)
    , mIndexBuffer(std::move(rhs.mIndexBuffer), alloc)
    , mSubMeshes(std::move(rhs.mSubMeshes), alloc)
    , mLayoutID(std::move(rhs.mLayoutID))
    , mLayoutName(std::move(rhs.mLayoutName), alloc)
{}

MeshData::~MeshData() = default;

TextureData::allocator_type TextureData::get_allocator() const noexcept {
    return allocator_type(mBuffer.get_allocator().resource());
}

TextureData::TextureData(const allocator_type& alloc)
    : mBuffer(alloc)
{}

TextureData::TextureData(TextureData const& rhs, const allocator_type& alloc)
    : mDesc(rhs.mDesc)
    , mFormat(rhs.mFormat)
    , mBuffer(rhs.mBuffer, alloc)
{}

TextureData::TextureData(TextureData&& rhs, const allocator_type& alloc)
    : mDesc(std::move(rhs.mDesc))
    , mFormat(std::move(rhs.mFormat))
    , mBuffer(std::move(rhs.mBuffer), alloc)
{}

TextureData::~TextureData() = default;

ShaderProgramData::allocator_type ShaderProgramData::get_allocator() const noexcept {
    return allocator_type(mVS.get_allocator().resource());
}

ShaderProgramData::ShaderProgramData(const allocator_type& alloc)
    : mVS(alloc)
    , mHS(alloc)
    , mDS(alloc)
    , mGS(alloc)
    , mPS(alloc)
{}

ShaderProgramData::ShaderProgramData(ShaderProgramData const& rhs, const allocator_type& alloc)
    : mVS(rhs.mVS, alloc)
    , mHS(rhs.mHS, alloc)
    , mDS(rhs.mDS, alloc)
    , mGS(rhs.mGS, alloc)
    , mPS(rhs.mPS, alloc)
{}

ShaderProgramData::ShaderProgramData(ShaderProgramData&& rhs, const allocator_type& alloc)
    : mVS(std::move(rhs.mVS), alloc)
    , mHS(std::move(rhs.mHS), alloc)
    , mDS(std::move(rhs.mDS), alloc)
    , mGS(std::move(rhs.mGS), alloc)
    , mPS(std::move(rhs.mPS), alloc)
{}

ShaderProgramData::~ShaderProgramData() = default;

ShaderInputLayout::allocator_type ShaderInputLayout::get_allocator() const noexcept {
    return allocator_type(mSemantics.get_allocator().resource());
}

ShaderInputLayout::ShaderInputLayout(const allocator_type& alloc)
    : mSemantics(alloc)
{}

ShaderInputLayout::ShaderInputLayout(ShaderInputLayout const& rhs, const allocator_type& alloc)
    : mSemantics(rhs.mSemantics, alloc)
    , mStripCutValue(rhs.mStripCutValue)
    , mPrimitiveTopologyType(rhs.mPrimitiveTopologyType)
{}

ShaderInputLayout::ShaderInputLayout(ShaderInputLayout&& rhs, const allocator_type& alloc)
    : mSemantics(std::move(rhs.mSemantics), alloc)
    , mStripCutValue(std::move(rhs.mStripCutValue))
    , mPrimitiveTopologyType(std::move(rhs.mPrimitiveTopologyType))
{}

ShaderInputLayout::~ShaderInputLayout() = default;

ShaderSubpassData::allocator_type ShaderSubpassData::get_allocator() const noexcept {
    return allocator_type(mProgram.get_allocator().resource());
}

ShaderSubpassData::ShaderSubpassData(const allocator_type& alloc)
    : mProgram(alloc)
    , mInputLayout(alloc)
    , mVertexLayouts(alloc)
    , mTextures(alloc)
{}

ShaderSubpassData::ShaderSubpassData(ShaderSubpassData const& rhs, const allocator_type& alloc)
    : mState(rhs.mState)
    , mProgram(rhs.mProgram, alloc)
    , mInputLayout(rhs.mInputLayout, alloc)
    , mVertexLayouts(rhs.mVertexLayouts, alloc)
    , mTextures(rhs.mTextures, alloc)
{}

ShaderSubpassData::ShaderSubpassData(ShaderSubpassData&& rhs, const allocator_type& alloc)
    : mState(std::move(rhs.mState))
    , mProgram(std::move(rhs.mProgram), alloc)
    , mInputLayout(std::move(rhs.mInputLayout), alloc)
    , mVertexLayouts(std::move(rhs.mVertexLayouts), alloc)
    , mTextures(std::move(rhs.mTextures), alloc)
{}

ShaderSubpassData::~ShaderSubpassData() = default;

ShaderPassData::allocator_type ShaderPassData::get_allocator() const noexcept {
    return allocator_type(mSubpasses.get_allocator().resource());
}

ShaderPassData::ShaderPassData(const allocator_type& alloc)
    : mSubpasses(alloc)
{}

ShaderPassData::ShaderPassData(ShaderPassData const& rhs, const allocator_type& alloc)
    : mSubpasses(rhs.mSubpasses, alloc)
{}

ShaderPassData::ShaderPassData(ShaderPassData&& rhs, const allocator_type& alloc)
    : mSubpasses(std::move(rhs.mSubpasses), alloc)
{}

ShaderPassData::~ShaderPassData() = default;

ShaderLevelData::allocator_type ShaderLevelData::get_allocator() const noexcept {
    return allocator_type(mPasses.get_allocator().resource());
}

ShaderLevelData::ShaderLevelData(const allocator_type& alloc)
    : mPasses(alloc)
{}

ShaderLevelData::ShaderLevelData(ShaderLevelData const& rhs, const allocator_type& alloc)
    : mPasses(rhs.mPasses, alloc)
{}

ShaderLevelData::ShaderLevelData(ShaderLevelData&& rhs, const allocator_type& alloc)
    : mPasses(std::move(rhs.mPasses), alloc)
{}

ShaderLevelData::~ShaderLevelData() = default;

ShaderQueueData::allocator_type ShaderQueueData::get_allocator() const noexcept {
    return allocator_type(mLevels.get_allocator().resource());
}

ShaderQueueData::ShaderQueueData(const allocator_type& alloc)
    : mLevels(alloc)
{}

ShaderQueueData::ShaderQueueData(ShaderQueueData const& rhs, const allocator_type& alloc)
    : mLevels(rhs.mLevels, alloc)
{}

ShaderQueueData::ShaderQueueData(ShaderQueueData&& rhs, const allocator_type& alloc)
    : mLevels(std::move(rhs.mLevels), alloc)
{}

ShaderQueueData::~ShaderQueueData() = default;

ShaderPipelineData::allocator_type ShaderPipelineData::get_allocator() const noexcept {
    return allocator_type(mQueues.get_allocator().resource());
}

ShaderPipelineData::ShaderPipelineData(const allocator_type& alloc)
    : mQueues(alloc)
{}

ShaderPipelineData::ShaderPipelineData(ShaderPipelineData const& rhs, const allocator_type& alloc)
    : mQueues(rhs.mQueues, alloc)
{}

ShaderPipelineData::ShaderPipelineData(ShaderPipelineData&& rhs, const allocator_type& alloc)
    : mQueues(std::move(rhs.mQueues), alloc)
{}

ShaderPipelineData::~ShaderPipelineData() = default;

ShaderSolutionData::allocator_type ShaderSolutionData::get_allocator() const noexcept {
    return allocator_type(mPipelines.get_allocator().resource());
}

ShaderSolutionData::ShaderSolutionData(const allocator_type& alloc)
    : mPipelines(alloc)
{}

ShaderSolutionData::ShaderSolutionData(ShaderSolutionData const& rhs, const allocator_type& alloc)
    : mPipelines(rhs.mPipelines, alloc)
{}

ShaderSolutionData::ShaderSolutionData(ShaderSolutionData&& rhs, const allocator_type& alloc)
    : mPipelines(std::move(rhs.mPipelines), alloc)
{}

ShaderSolutionData::~ShaderSolutionData() = default;

ShaderData::allocator_type ShaderData::get_allocator() const noexcept {
    return allocator_type(mName.get_allocator().resource());
}

ShaderData::ShaderData(const allocator_type& alloc)
    : mName(alloc)
    , mSolutions(alloc)
{}

ShaderData::ShaderData(ShaderData const& rhs, const allocator_type& alloc)
    : mName(rhs.mName, alloc)
    , mSolutions(rhs.mSolutions, alloc)
{}

ShaderData::ShaderData(ShaderData&& rhs, const allocator_type& alloc)
    : mName(std::move(rhs.mName), alloc)
    , mSolutions(std::move(rhs.mSolutions), alloc)
{}

ShaderData::~ShaderData() = default;

MaterialData::allocator_type MaterialData::get_allocator() const noexcept {
    return allocator_type(mShader.get_allocator().resource());
}

MaterialData::MaterialData(const allocator_type& alloc)
    : mShader(alloc)
    , mTextures(alloc)
    , mConstantBuffer(alloc)
{}

MaterialData::MaterialData(MaterialData const& rhs, const allocator_type& alloc)
    : mShader(rhs.mShader, alloc)
    , mTextures(rhs.mTextures, alloc)
    , mConstantBuffer(rhs.mConstantBuffer, alloc)
{}

MaterialData::MaterialData(MaterialData&& rhs, const allocator_type& alloc)
    : mShader(std::move(rhs.mShader), alloc)
    , mTextures(std::move(rhs.mTextures), alloc)
    , mConstantBuffer(std::move(rhs.mConstantBuffer), alloc)
{}

MaterialData::~MaterialData() = default;

DrawCallData::allocator_type DrawCallData::get_allocator() const noexcept {
    return allocator_type(mConstantBuffer.get_allocator().resource());
}

DrawCallData::DrawCallData(const allocator_type& alloc)
    : mConstantBuffer(alloc)
{}

DrawCallData::DrawCallData(DrawCallData const& rhs, const allocator_type& alloc)
    : mType(rhs.mType)
    , mMesh(rhs.mMesh)
    , mMaterial(rhs.mMaterial)
    , mInstanceSize(rhs.mInstanceSize)
    , mInstanceCount(rhs.mInstanceCount)
    , mConstantBuffer(rhs.mConstantBuffer, alloc)
{}

DrawCallData::DrawCallData(DrawCallData&& rhs, const allocator_type& alloc)
    : mType(std::move(rhs.mType))
    , mMesh(std::move(rhs.mMesh))
    , mMaterial(std::move(rhs.mMaterial))
    , mInstanceSize(std::move(rhs.mInstanceSize))
    , mInstanceCount(std::move(rhs.mInstanceCount))
    , mConstantBuffer(std::move(rhs.mConstantBuffer), alloc)
{}

DrawCallData::~DrawCallData() = default;

MeshRenderer::allocator_type MeshRenderer::get_allocator() const noexcept {
    return allocator_type(mMaterialIDs.get_allocator().resource());
}

MeshRenderer::MeshRenderer(const allocator_type& alloc)
    : mMaterialIDs(alloc)
{}

MeshRenderer::MeshRenderer(MeshRenderer const& rhs, const allocator_type& alloc)
    : mMeshID(rhs.mMeshID)
    , mMaterialIDs(rhs.mMaterialIDs, alloc)
{}

MeshRenderer::MeshRenderer(MeshRenderer&& rhs, const allocator_type& alloc)
    : mMeshID(std::move(rhs.mMeshID))
    , mMaterialIDs(std::move(rhs.mMaterialIDs), alloc)
{}

MeshRenderer::~MeshRenderer() = default;

FlattenedObjects::allocator_type FlattenedObjects::get_allocator() const noexcept {
    return allocator_type(mWorldTransforms.get_allocator().resource());
}

FlattenedObjects::FlattenedObjects(const allocator_type& alloc)
    : mWorldTransforms(alloc)
    , mWorldTransformInvs(alloc)
    , mBoundingBoxes(alloc)
    , mMeshRenderers(alloc)
{}

FlattenedObjects::FlattenedObjects(FlattenedObjects const& rhs, const allocator_type& alloc)
    : mWorldTransforms(rhs.mWorldTransforms, alloc)
    , mWorldTransformInvs(rhs.mWorldTransformInvs, alloc)
    , mBoundingBoxes(rhs.mBoundingBoxes, alloc)
    , mMeshRenderers(rhs.mMeshRenderers, alloc)
{}

FlattenedObjects::FlattenedObjects(FlattenedObjects&& rhs, const allocator_type& alloc)
    : mWorldTransforms(std::move(rhs.mWorldTransforms), alloc)
    , mWorldTransformInvs(std::move(rhs.mWorldTransformInvs), alloc)
    , mBoundingBoxes(std::move(rhs.mBoundingBoxes), alloc)
    , mMeshRenderers(std::move(rhs.mMeshRenderers), alloc)
{}

FlattenedObjects::~FlattenedObjects() = default;

ContentSettings::allocator_type ContentSettings::get_allocator() const noexcept {
    return allocator_type(mVertexLayouts.get_allocator().resource());
}

ContentSettings::ContentSettings(const allocator_type& alloc)
    : mVertexLayouts(alloc)
    , mIndex(alloc)
{}

ContentSettings::ContentSettings(ContentSettings const& rhs, const allocator_type& alloc)
    : mVertexLayouts(rhs.mVertexLayouts, alloc)
    , mIndex(rhs.mIndex, alloc)
{}

ContentSettings::ContentSettings(ContentSettings&& rhs, const allocator_type& alloc)
    : mVertexLayouts(std::move(rhs.mVertexLayouts), alloc)
    , mIndex(std::move(rhs.mIndex), alloc)
{}

ContentSettings::~ContentSettings() = default;

ContentData::allocator_type ContentData::get_allocator() const noexcept {
    return allocator_type(mIDs.get_allocator().resource());
}

ContentData::ContentData(const allocator_type& alloc)
    : mIDs(alloc)
    , mDrawCalls(alloc)
    , mFlattenedObjects(alloc)
{}

ContentData::ContentData(ContentData const& rhs, const allocator_type& alloc)
    : mIDs(rhs.mIDs, alloc)
    , mDrawCalls(rhs.mDrawCalls, alloc)
    , mFlattenedObjects(rhs.mFlattenedObjects, alloc)
{}

ContentData::ContentData(ContentData&& rhs, const allocator_type& alloc)
    : mIDs(std::move(rhs.mIDs), alloc)
    , mDrawCalls(std::move(rhs.mDrawCalls), alloc)
    , mFlattenedObjects(std::move(rhs.mFlattenedObjects), alloc)
{}

ContentData::~ContentData() = default;

RenderGraphData::allocator_type RenderGraphData::get_allocator() const noexcept {
    return allocator_type(mRenderGraph.get_allocator().resource());
}

RenderGraphData::RenderGraphData(const allocator_type& alloc)
    : mRenderGraph(alloc)
    , mShaderIndex(alloc)
{}

RenderGraphData::RenderGraphData(RenderGraphData const& rhs, const allocator_type& alloc)
    : mRenderGraph(rhs.mRenderGraph, alloc)
    , mShaderIndex(rhs.mShaderIndex, alloc)
{}

RenderGraphData::RenderGraphData(RenderGraphData&& rhs, const allocator_type& alloc)
    : mRenderGraph(std::move(rhs.mRenderGraph), alloc)
    , mShaderIndex(std::move(rhs.mShaderIndex), alloc)
{}

RenderGraphData::~RenderGraphData() = default;

Resources::allocator_type Resources::get_allocator() const noexcept {
    return allocator_type(mSettings.get_allocator().resource());
}

Resources::Resources(const allocator_type& alloc)
    : mSettings(alloc)
    , mMeshes(alloc)
    , mTextures(alloc)
    , mShaders(alloc)
    , mMaterials(alloc)
    , mContents(alloc)
    , mRenderGraphs(alloc)
{}

Resources::Resources(Resources const& rhs, const allocator_type& alloc)
    : mSettings(rhs.mSettings, alloc)
    , mMeshes(rhs.mMeshes, alloc)
    , mTextures(rhs.mTextures, alloc)
    , mShaders(rhs.mShaders, alloc)
    , mMaterials(rhs.mMaterials, alloc)
    , mContents(rhs.mContents, alloc)
    , mRenderGraphs(rhs.mRenderGraphs, alloc)
{}

Resources::Resources(Resources&& rhs, const allocator_type& alloc)
    : mSettings(std::move(rhs.mSettings), alloc)
    , mMeshes(std::move(rhs.mMeshes), alloc)
    , mTextures(std::move(rhs.mTextures), alloc)
    , mShaders(std::move(rhs.mShaders), alloc)
    , mMaterials(std::move(rhs.mMaterials), alloc)
    , mContents(std::move(rhs.mContents), alloc)
    , mRenderGraphs(std::move(rhs.mRenderGraphs), alloc)
{}

Resources::~Resources() = default;

} // namespace Render

} // namespace Graphics

} // namespace Star
