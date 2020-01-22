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
#include <Star/Graphics/SContentTypes.h>
//#include <Star/AssetFactory/SAssetFwd.h>
#include <Star/AssetFactory/SAssetTypes.h>

namespace fbxsdk {
class FbxManager;
class FbxNode;
class FbxObject;
class FbxScene;
}

namespace Star::Asset {

class AssetFbxDeleter {
public:
    void operator()(fbxsdk::FbxManager* pManager) const noexcept;
    void operator()(fbxsdk::FbxObject* pObject) const noexcept;
};

template<class T>
using FbxPtr = std::unique_ptr<T, AssetFbxDeleter>;

class AssetFbxScene {
public:
    AssetFbxScene(FbxPtr<fbxsdk::FbxScene> ptr, const MetaID& metaID,
        const std::filesystem::path& assetFolder, const std::filesystem::path& assetPath);
    ~AssetFbxScene();

    void createMaterials(const std::function<void(std::string_view, const Map<std::string, std::string>&)>& func) const;

    void readInfo(const FbxInfo& info, MetaIDNameIndex<MeshInfo>& meshInfo,
        std::unordered_set<MetaID>& assets) const;

    void readMeshes(std::string_view layout, Graphics::Render::Resources& resources) const;

    void readFlattenedNodes(const MetaIDNameIndex<MeshInfo>& meshInfo,
        Graphics::Render::FlattenedObjects& batch) const;
private:
    std::filesystem::path getMaterialPath(std::string_view nodeName, size_t id, size_t count) const;
    std::string getMeshName(const fbxsdk::FbxMesh* pMesh, std::set<std::string>& names, size_t& meshID) const;

    void createMaterials(const std::function<void(std::string_view, const Map<std::string, std::string>&)>& func,
        fbxsdk::FbxNode* pFbxNode, uint32_t& nodeID) const;

    void getMeshNodeCount(fbxsdk::FbxNode* pFbxNode, size_t& count) const;
    void validateMaterialFiles(fbxsdk::FbxNode* pFbxNode) const;

    void readMeshInfo(fbxsdk::FbxNode* pFbxNode, std::set<const fbxsdk::FbxMesh*>& meshes,
        std::set<std::string>& names, size_t& meshID, const FbxInfo& info,
        MetaIDNameIndex<MeshInfo>& meshInfo, std::unordered_set<MetaID>& assets) const;

    void readMeshInfo(const fbxsdk::FbxMesh* pMesh,
        std::set<std::string>& names, size_t& meshID,
        const FbxInfo& info, MetaIDNameIndex<MeshInfo>& meshInfo,
        std::unordered_set<MetaID>& assets) const;

    void readMeshes(std::string_view layout, 
        fbxsdk::FbxNode* pFbxNode, Graphics::Render::Resources& resources,
        std::set<const fbxsdk::FbxMesh*>& meshes, std::set<std::string>& names, size_t& meshID) const;

    void readMesh(std::string_view layout,
        const fbxsdk::FbxMesh* pMesh, Graphics::Render::Resources& resources,
        std::set<std::string>& names, size_t& meshID) const;

    void readFlattenedNodes(fbxsdk::FbxNode* pFbxNode, const MetaIDNameIndex<MeshInfo>& resources,
        Graphics::Render::FlattenedObjects& batch, size_t& nodeID,
        std::map<const fbxsdk::FbxMesh*, MetaID>& meshes, std::set<std::string>& names, size_t& meshID) const;

    void readMeshRenderer(const MetaIDNameIndex<MeshInfo>& resources,
        fbxsdk::FbxNode* pFbxNode, const fbxsdk::FbxMesh* pMesh,
        const MetaID& meshMetaID, Graphics::Render::FlattenedObjects& objects, size_t& nodeID) const;

    MetaID mMetaID;
    std::filesystem::path mAssetFolder;
    std::filesystem::path mAssetPath;
    std::filesystem::path mMaterialFolder;
    FbxPtr<fbxsdk::FbxScene> mScene;
};

}
