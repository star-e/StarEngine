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
#include <Star/SSerializationUtils.h>
#include <Star/Serialization/SRuntime.h>
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>

namespace boost {

namespace serialization {

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ResourceBuffer, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ResourceBuffer, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ResourceBuffer& v, const uint32_t version) {
    ar & v.mWidth;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Resource1D, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Resource1D, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Resource1D& v, const uint32_t version) {
    ar & v.mWidth;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Resource2D, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Resource2D, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Resource2D& v, const uint32_t version) {
    ar & v.mWidth;
    ar & v.mHeight;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Resource3D, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Resource3D, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Resource3D& v, const uint32_t version) {
    ar & v.mWidth;
    ar & v.mHeight;
    ar & v.mDepthSize;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MipChain, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MipChain, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MipChain& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MipLevels, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MipLevels, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MipLevels& v, const uint32_t version) {
    ar & v.mMipLevels;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ArraySize, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ArraySize, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ArraySize& v, const uint32_t version) {
    ar & v.mArraySize;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Multisampling, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Multisampling, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Multisampling& v, const uint32_t version) {
    ar & v.mCount;
    ar & v.mQuality;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RowMajor_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RowMajor_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RowMajor_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UndefinedSwizzle64KB_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UndefinedSwizzle64KB_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UndefinedSwizzle64KB_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::StandardSwizzle64KB_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::StandardSwizzle64KB_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::StandardSwizzle64KB_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Resource, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Resource, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Resource& v, const uint32_t version) {
    ar & v.mFormat;
    ar & v.mDimension;
    ar & v.mArray;
    ar & v.mMipMap;
    ar & v.mSampling;
    ar & v.mLayout;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BarrierTransition_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BarrierTransition_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BarrierTransition_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BarrierAliasing_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BarrierAliasing_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BarrierAliasing_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BarrierUav_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BarrierUav_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BarrierUav_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Source_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Source_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Source_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Target_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Target_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Target_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Common_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Common_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Common_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VertexAndConstantBuffer_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VertexAndConstantBuffer_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VertexAndConstantBuffer_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::IndexBuffer_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::IndexBuffer_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::IndexBuffer_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderTarget_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderTarget_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderTarget_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UnorderedAccess_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UnorderedAccess_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UnorderedAccess_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DepthWrite_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DepthWrite_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DepthWrite_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DepthRead_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DepthRead_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DepthRead_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderResource_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderResource_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderResource_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::StreamOut_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::StreamOut_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::StreamOut_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::IndirectArgument_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::IndirectArgument_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::IndirectArgument_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::CopyDest_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::CopyDest_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::CopyDest_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::CopySource_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::CopySource_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::CopySource_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ResolveDest_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ResolveDest_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ResolveDest_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ResolveSource_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ResolveSource_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ResolveSource_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Present_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Present_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Present_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Raytracing_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Raytracing_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Raytracing_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Predication_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Predication_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Predication_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderTargetState, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderTargetState, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderTargetState& v, const uint32_t version) {
    ar & v.mState;
    ar & v.mNonPixelShaderResource;
    ar & v.mPixelShaderResource;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderValue, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderValue, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderValue& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mState;
    ar & v.mData;
    ar & v.mModel;
    ar & v.mLoadOp;
    ar & v.mStoreOp;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::NodeRenderTargetState, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::NodeRenderTargetState, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::NodeRenderTargetState& v, const uint32_t version) {
    ar & v.mNodeID;
    ar & v.mRenderTargetState;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderTargetStateTransition, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderTargetStateTransition, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderTargetStateTransition& v, const uint32_t version) {
    ar & v.mNodeID;
    ar & v.mSource;
    ar & v.mTarget;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderTargetStateTransitions, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderTargetStateTransitions, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderTargetStateTransitions& v, const uint32_t version) {
    ar & v.mStates;
    ar & v.mFullStates;
    ar & v.mTransitions;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderNode, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderNode, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderNode& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mColorSpace;
    ar & v.mOutputs;
    ar & v.mInputs;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderGroup, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderGroup, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderGroup& v, const uint32_t version) {
    ar & v.mRenderNodes;
    ar & v.mInputs;
    ar & v.mOutputs;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BackBuffer_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BackBuffer_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BackBuffer_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderTargetResource, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderTargetResource, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderTargetResource& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mResource;
    ar & v.mClearColor;
    ar & v.mColorSpace;
    ar & v.mType;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderPipelineBuilder, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderPipelineBuilder, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderPipelineBuilder& v, const uint32_t version) {
    ar & v.mName;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderWorksBuilder, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderWorksBuilder, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderWorksBuilder& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mPipelines;
    ar & v.mFramebuffers;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderSwapChainBuilder, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderSwapChainBuilder, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderSwapChainBuilder& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mRenderWorks;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderConfigs, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderConfigs, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderConfigs& v, const uint32_t version) {
    ar & v.mVerbose;
    ar & v.mStrictLightingColorSpace;
    ar & v.mFramebufferFetch;
}

} // namespace serialization

} // namespace boost
