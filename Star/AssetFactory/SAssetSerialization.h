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
#include <Star/AssetFactory/SAssetTypes.h>
#include <Star/Graphics/SRenderSerialization.h>

namespace boost {

namespace serialization {

STAR_CLASS_IMPLEMENTATION(Star::Asset::FbxInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::FbxInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::FbxInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("metaID", v.mMetaID);
    ar & boost::serialization::make_nvp("name", v.mName);
    ar & boost::serialization::make_nvp("meshes", v.mMeshes);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::MeshInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::MeshInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::MeshInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("metaID", v.mMetaID);
    ar & boost::serialization::make_nvp("name", v.mName);
    ar & boost::serialization::make_nvp("meshName", v.mMeshName);
    ar & boost::serialization::make_nvp("fbx", v.mFbx);
    ar & boost::serialization::make_nvp("numSubMeshes", v.mNumSubMeshes);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::TextureInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::TextureInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::TextureInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("metaID", v.mMetaID);
    ar & boost::serialization::make_nvp("name", v.mName);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::ShaderInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::ShaderInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::ShaderInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("shaderName", v.mShaderName);
    ar & boost::serialization::make_nvp("content", v.mContent);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::MaterialInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::MaterialInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::MaterialInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("shader", v.mShader);
    ar & boost::serialization::make_nvp("textures", v.mTextures);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::ContentInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::ContentInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::ContentInfo& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::RenderGraphInfo, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::RenderGraphInfo, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::RenderGraphInfo& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("renderGraphName", v.mRenderGraphName);
    ar & boost::serialization::make_nvp("width", v.mWidth);
    ar & boost::serialization::make_nvp("height", v.mHeight);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::FbxImportSettings, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::FbxImportSettings, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::FbxImportSettings& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("meshBufferLayout", v.mMeshBufferLayout);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::AssetDatabase, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::AssetDatabase, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::AssetDatabase& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("fbxInfo", v.mFbxInfo);
    ar & boost::serialization::make_nvp("meshInfo", v.mMeshInfo);
    ar & boost::serialization::make_nvp("textureInfo", v.mTextureInfo);
    ar & boost::serialization::make_nvp("shaderInfo", v.mShaderInfo);
    ar & boost::serialization::make_nvp("materialInfo", v.mMaterialInfo);
    ar & boost::serialization::make_nvp("contentInfo", v.mContentInfo);
    ar & boost::serialization::make_nvp("renderGraphInfo", v.mRenderGraphInfo);
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::Direct_, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::Direct_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::Direct_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::IndexToDirect_, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::IndexToDirect_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::IndexToDirect_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::ByControlPoint_, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::ByControlPoint_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::ByControlPoint_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::ByPolygonVertex_, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::ByPolygonVertex_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::ByPolygonVertex_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::ByPolygon_, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::ByPolygon_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::ByPolygon_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Asset::TextureImportSettings, object_serializable);
STAR_CLASS_TRACKING(Star::Asset::TextureImportSettings, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Asset::TextureImportSettings& v, const uint32_t version) {
    ar & boost::serialization::make_nvp("format", v.mFormat);
    ar & boost::serialization::make_nvp("generateMipMaps", v.mGenerateMipMaps);
    ar & boost::serialization::make_nvp("flipY", v.mFlipY);
}

} // namespace serialization

} // namespace boost
