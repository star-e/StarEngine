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
#include <Star/Graphics/SContentTypes.h>
#include <Star/Graphics/SRenderSerialization.h>
#include <Star/Graphics/SRenderGraphSerialization.h>

namespace boost {

namespace serialization {

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VertexElement, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VertexElement, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VertexElement& v, const uint32_t version) {
    ar & v.mType;
    ar & v.mAlignedByteOffset;
    ar & v.mFormat;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VertexElementIndex, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VertexElementIndex, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VertexElementIndex& v, const uint32_t version) {
    ar & v.mBufferID;
    ar & v.mElementID;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VertexBufferDesc, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VertexBufferDesc, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VertexBufferDesc& v, const uint32_t version) {
    ar & v.mElements;
    ar & v.mVertexSize;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::VertexBufferDesc>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::VertexBufferDesc>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::VertexBufferDesc>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::VertexBufferDesc>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MeshBufferLayout, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MeshBufferLayout, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MeshBufferLayout& v, const uint32_t version) {
    ar & v.mBuffers;
    ar & v.mIndex;
    ar & v.mStripCutValue;
    ar & v.mPrimitiveTopologyType;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::MeshBufferLayout>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::MeshBufferLayout>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::MeshBufferLayout>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::MeshBufferLayout>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VertexBufferData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VertexBufferData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VertexBufferData& v, const uint32_t version) {
    ar & v.mDesc;
    ar & v.mVertexCount;
    ar & v.mBuffer;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::VertexBufferData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::VertexBufferData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::VertexBufferData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::VertexBufferData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::IndexBufferData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::IndexBufferData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::IndexBufferData& v, const uint32_t version) {
    ar & v.mBuffer;
    ar & v.mElementSize;
    ar & v.mPrimitiveCount;
    ar & v.mPrimitiveTopology;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::IndexBufferData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::IndexBufferData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::IndexBufferData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::IndexBufferData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SubMeshData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SubMeshData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SubMeshData& v, const uint32_t version) {
    ar & v.mIndexOffset;
    ar & v.mIndexCount;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MeshData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MeshData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MeshData& v, const uint32_t version) {
    ar & v.mVertexBuffers;
    ar & v.mIndexBuffer;
    ar & v.mSubMeshes;
    ar & v.mLayoutID;
    ar & v.mLayoutName;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::MeshData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::MeshData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::MeshData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::MeshData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::TextureData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::TextureData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::TextureData& v, const uint32_t version) {
    ar & v.mDesc;
    ar & v.mFormat;
    ar & v.mBuffer;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::TextureData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::TextureData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::TextureData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::TextureData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::PipelineStateData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::PipelineStateData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::PipelineStateData& v, const uint32_t version) {
    ar & v.mStreamOutput;
    ar & v.mBlendState;
    ar & v.mSampleMask;
    ar & v.mRasterizerState;
    ar & v.mDepthStencilState;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderProgramData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderProgramData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderProgramData& v, const uint32_t version) {
    ar & v.mVS;
    ar & v.mHS;
    ar & v.mDS;
    ar & v.mGS;
    ar & v.mPS;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderProgramData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderProgramData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderProgramData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderProgramData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderInputLayout, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderInputLayout, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderInputLayout& v, const uint32_t version) {
    ar & v.mSemantics;
    ar & v.mStripCutValue;
    ar & v.mPrimitiveTopologyType;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderInputLayout>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderInputLayout>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderInputLayout>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderInputLayout>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderSubpassData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderSubpassData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderSubpassData& v, const uint32_t version) {
    ar & v.mState;
    ar & v.mProgram;
    ar & v.mInputLayout;
    ar & v.mVertexLayouts;
    ar & v.mConstantBuffers;
    ar & v.mDescriptors;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderSubpassData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderSubpassData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderSubpassData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderSubpassData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderPassData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderPassData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderPassData& v, const uint32_t version) {
    ar & v.mSubpasses;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderPassData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderPassData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderPassData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderPassData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderLevelData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderLevelData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderLevelData& v, const uint32_t version) {
    ar & v.mPasses;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderLevelData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderLevelData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderLevelData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderLevelData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderQueueData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderQueueData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderQueueData& v, const uint32_t version) {
    ar & v.mLevels;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderQueueData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderQueueData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderQueueData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderQueueData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderPipelineData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderPipelineData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderPipelineData& v, const uint32_t version) {
    ar & v.mQueues;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderPipelineData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderPipelineData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderPipelineData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderPipelineData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderSolutionData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderSolutionData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderSolutionData& v, const uint32_t version) {
    ar & v.mPipelines;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderSolutionData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderSolutionData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderSolutionData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderSolutionData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ShaderData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ShaderData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ShaderData& v, const uint32_t version) {
    ar & v.mName;
    ar & v.mSolutions;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ShaderData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ShaderData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ShaderData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ShaderData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ConstantDescriptor, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ConstantDescriptor, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ConstantDescriptor& v, const uint32_t version) {
    ar & v.mOffset;
    ar & v.mSize;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ConstantMap, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ConstantMap, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ConstantMap& v, const uint32_t version) {
    ar & v.mIndex;
    ar & v.mBuffer;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ConstantMap>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ConstantMap>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ConstantMap>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ConstantMap>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MaterialData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MaterialData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MaterialData& v, const uint32_t version) {
    ar & v.mShader;
    ar & v.mTextures;
    ar & v.mConstantMap;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::MaterialData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::MaterialData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::MaterialData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::MaterialData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::FullScreenTriangle_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::FullScreenTriangle_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::FullScreenTriangle_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DrawCallData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DrawCallData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DrawCallData& v, const uint32_t version) {
    ar & v.mType;
    ar & v.mMesh;
    ar & v.mMaterial;
    ar & v.mInstanceSize;
    ar & v.mInstanceCount;
    ar & v.mConstantMap;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::DrawCallData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::DrawCallData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::DrawCallData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::DrawCallData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BasicTransform, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BasicTransform, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BasicTransform& v, const uint32_t version) {
    ar & v.mUniformScale;
    ar & v.mTranslation;
    ar & v.mQuaternion;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::WorldTransform, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::WorldTransform, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::WorldTransform& v, const uint32_t version) {
    ar & v.mTransform;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::WorldTransformInv, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::WorldTransformInv, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::WorldTransformInv& v, const uint32_t version) {
    ar & v.mTransform;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BoundingBox, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BoundingBox, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BoundingBox& v, const uint32_t version) {
    ar & v.mLocalBounds;
    ar & v.mWorldBounds;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::CameraData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::CameraData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::CameraData& v, const uint32_t version) {
    ar & v.mView;
    ar & v.mProj;
    ar & v.mPosition;
    ar & v.mViewSpace;
    ar & v.mNDC;
    ar & v.mFlags;
    ar & v.mRight;
    ar & v.mForward;
    ar & v.mUp;
    ar & v.mYaw;
    ar & v.mPitch;
    ar & v.mRoll;
    ar & v.mNearClip;
    ar & v.mFarClip;
    ar & v.mAspect;
    ar & v.mFov;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::MeshRenderer, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::MeshRenderer, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::MeshRenderer& v, const uint32_t version) {
    ar & v.mMeshID;
    ar & v.mMaterialIDs;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::MeshRenderer>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::MeshRenderer>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::MeshRenderer>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::MeshRenderer>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::FlattenedObjects, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::FlattenedObjects, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::FlattenedObjects& v, const uint32_t version) {
    ar & v.mWorldTransforms;
    ar & v.mWorldTransformInvs;
    ar & v.mBoundingBoxes;
    ar & v.mMeshRenderers;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::FlattenedObjects>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::FlattenedObjects>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::FlattenedObjects>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::FlattenedObjects>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ContentSettings, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ContentSettings, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ContentSettings& v, const uint32_t version) {
    ar & v.mVertexLayouts;
    ar & v.mVertexLayoutIndex;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ContentSettings>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ContentSettings>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ContentSettings>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ContentSettings>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DrawCall_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DrawCall_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DrawCall_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ObjectBatch_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ObjectBatch_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ObjectBatch_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ContentID, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ContentID, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ContentID& v, const uint32_t version) {
    ar & v.mType;
    ar & v.mIndex;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ContentData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ContentData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ContentData& v, const uint32_t version) {
    ar & v.mIDs;
    ar & v.mDrawCalls;
    ar & v.mFlattenedObjects;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ContentData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ContentData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ContentData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ContentData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RenderGraphData, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RenderGraphData, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RenderGraphData& v, const uint32_t version) {
    ar & v.mRenderGraph;
    ar & v.mShaderIndex;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::RenderGraphData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::RenderGraphData>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::RenderGraphData>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::RenderGraphData>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Resources, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Resources, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Resources& v, const uint32_t version) {
    ar & v.mSettings;
    ar & v.mMeshes;
    ar & v.mTextures;
    ar & v.mShaders;
    ar & v.mMaterials;
    ar & v.mContents;
    ar & v.mRenderGraphs;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::Resources>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::Resources>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::Resources>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::Resources>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

} // namespace serialization

} // namespace boost
