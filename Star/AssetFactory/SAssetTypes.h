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
#include <Star/AssetFactory/SConfig.h>
#include <Star/AssetFactory/SAssetFwd.h>
#include <Star/Graphics/SRenderTypes.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Star {

namespace Asset {

struct FbxInfo {
    FbxInfo() = default;
    FbxInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
    std::vector<MetaID> mMeshes;
};

struct MeshInfo {
    MetaID mMetaID;
    std::string mName;
    std::string mMeshName;
    const FbxInfo* mFbx = nullptr;
    size_t mNumSubMeshes;
};

struct TextureInfo {
    TextureInfo() = default;
    TextureInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
};

struct ShaderInfo {
    ShaderInfo() = default;
    ShaderInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
    std::string mShaderName;
    std::string mContent;
};

struct MaterialInfo {
    MaterialInfo() = default;
    MaterialInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
    std::string mShader;
    StringMap<MetaID> mTextures;
};

struct ContentInfo {
    ContentInfo() = default;
    ContentInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
};

struct RenderGraphInfo {
    RenderGraphInfo() = default;
    RenderGraphInfo(MetaID metaID, std::string_view name)
        : mMetaID(std::move(metaID))
        , mName(std::move(name))
    {}
    MetaID mMetaID;
    std::string mName;
    std::string mRenderGraphName;
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
};

struct FbxImportSettings {
    std::string mMeshBufferLayout;
};

struct AssetDatabase {
    MetaIDNameIndex<FbxInfo> mFbxInfo;
    MetaIDNameIndex<MeshInfo> mMeshInfo;
    MetaIDNameIndex<TextureInfo> mTextureInfo;
    MetaIDNameIndex<ShaderInfo> mShaderInfo;
    MetaIDNameIndex<MaterialInfo> mMaterialInfo;
    MetaIDNameIndex<ContentInfo> mContentInfo;
    MetaIDNameIndex<RenderGraphInfo> mRenderGraphInfo;
};

struct Direct_ {} static constexpr Direct;
struct IndexToDirect_ {} static constexpr IndexToDirect;

using ReferenceMode = std::variant<Direct_, IndexToDirect_>;

struct ByControlPoint_ {} static constexpr ByControlPoint;
struct ByPolygonVertex_ {} static constexpr ByPolygonVertex;
struct ByPolygon_ {} static constexpr ByPolygon;

using MappingMode = std::variant<ByControlPoint_, ByPolygonVertex_, ByPolygon_>;

struct TextureImportSettings {
    Graphics::Render::Format mFormat = Graphics::Render::Format::UNKNOWN;
    bool mGenerateMipMaps = true;
    bool mFlipY = true;
};

} // namespace Asset

} // namespace Star

#ifdef _MSC_VER
#pragma warning(pop)
#endif
