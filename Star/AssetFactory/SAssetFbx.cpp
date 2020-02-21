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

#include "SAssetFbx.h"
#include <Star/Graphics/SContentUtils.h>
#include "SAssetTypes.h"
#include "SAssetFbxUtils.h"
#include "SAssetUtils.h"
#include <Star/Graphics/SContentSerialization.h>

using namespace fbxsdk;

namespace Star::Asset {

using namespace Graphics::Render;

namespace {

void checkLayoutRequirement(const MeshBufferLayout& layout, const fbxsdk::FbxMesh* pMesh) {
    std::array<int, 10> count = {};
    for (const auto& vb : layout.mBuffers) {
        for (const auto& e : vb.mElements) {
            visit(overload(
                [&](BINORMAL_) {
                    if (!(count.at(e.mType.index()) < pMesh->GetElementBinormalCount())) {
                        throw std::invalid_argument("binormal index exceeds count");
                    }
                    ++count.at(e.mType.index());
                },
                [&](BLENDINDICES_) {
                    throw std::invalid_argument("blend index not supported yet");
                },
                [&](BLENDWEIGHT_) {
                    throw std::invalid_argument("blend weight not supported yet");
                },
                [&](NORMAL_) {
                    if (!(count.at(e.mType.index()) < pMesh->GetElementNormalCount())) {
                        throw std::invalid_argument("normal index exceeds count");
                    }
                    ++count.at(e.mType.index());
                },
                [&](POSITIONT_) {
                    throw std::invalid_argument("positiont not supported yet");
                },
                [&](PSIZE_) {
                    throw std::invalid_argument("psize not supported yet");
                },
                [&](TANGENT_) {
                    if (!(count.at(e.mType.index()) < pMesh->GetElementTangentCount())) {
                        throw std::invalid_argument("texcoord index exceeds uv count");
                    }
                    ++count.at(e.mType.index());
                },
                [&](TEXCOORD_) {
                    if (!(count.at(e.mType.index()) < pMesh->GetElementUVCount())) {
                        throw std::invalid_argument("texcoord index exceeds uv count");
                    }
                    ++count.at(e.mType.index());
                },
                [&](SV_Position_) {
                    if (count.at(e.mType.index())) {
                        throw std::invalid_argument("only one position supported");
                    }
                    ++count.at(e.mType.index());
                },
                [&](SV_Target_) {
                    if (!(count.at(e.mType.index()) < pMesh->GetElementVertexColorCount())) {
                        throw std::invalid_argument("color index exceeds count");
                    }
                    ++count.at(e.mType.index());
                }
            ), e.mType);
        }
    }

    auto checkMappingMode = [&](FbxGeometryElement::EMappingMode mode) {
        switch (mode) {
        case FbxGeometryElement::eByControlPoint:
            break;
        case FbxGeometryElement::eByPolygonVertex:
            break;
        case FbxGeometryElement::eByPolygon:
            break;
        default:
            throw std::invalid_argument("invalid fbx mesh mapping mode");
        }
    };

    for (int i = 0; i != pMesh->GetElementBinormalCount(); ++i) {
        checkMappingMode(pMesh->GetElementBinormal(i)->GetMappingMode());
    }
    for (int i = 0; i != pMesh->GetElementNormalCount(); ++i) {
        checkMappingMode(pMesh->GetElementNormal(i)->GetMappingMode());
    }
    for (int i = 0; i != pMesh->GetElementTangentCount(); ++i) {
        checkMappingMode(pMesh->GetElementTangent(i)->GetMappingMode());
    }
    for (int i = 0; i != pMesh->GetElementUVCount(); ++i) {
        checkMappingMode(pMesh->GetElementUV(i)->GetMappingMode());
    }
    for (int i = 0; i != pMesh->GetElementVertexColorCount(); ++i) {
        checkMappingMode(pMesh->GetElementVertexColor(i)->GetMappingMode());
    }
}

void fillBufferByVertex(const MeshBufferLayout& layout,
    const fbxsdk::FbxMesh* pMesh, MeshData& mesh
) {
    static const int PolygonSize = 3;
    const int faceCount = pMesh->GetPolygonCount();
    const int vertexCount = PolygonSize * faceCount;

    mesh.mVertexBuffers.reserve(layout.mBuffers.size());
    for (const auto& desc : layout.mBuffers) {
        auto& vb = mesh.mVertexBuffers.emplace_back();
        vb.mDesc = desc;
        vb.mVertexCount = vertexCount;
        vb.mBuffer.resize(desc.mVertexSize * vb.mVertexCount);
    }

    std::array<int, 10> count = {};

    for (auto& vb : mesh.mVertexBuffers) {
        auto start = vb.mBuffer.data();
        for (const auto& e : vb.mDesc.mElements) {
            const auto& slot = count.at(e.mType.index())++;
            auto buffer = start + e.mAlignedByteOffset;
            auto stride = vb.mDesc.mVertexSize;
            visit(overload(
                [&](BINORMAL_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByVertex<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByVertex<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByVertex<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("binormal Format not support");
                    }
                },
                [&](BLENDINDICES_) {
                    throw std::invalid_argument("blend index not supported yet");
                },
                [&](BLENDWEIGHT_) {
                    throw std::invalid_argument("blend weight not supported yet");
                },
                [&](NORMAL_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByVertex<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByVertex<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByVertex<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("normal Format not support");
                    }
                },
                [&](POSITIONT_) {
                    throw std::invalid_argument("positiont not supported yet");
                },
                [&](PSIZE_) {
                    throw std::invalid_argument("psize not supported yet");
                },
                [&](TANGENT_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByVertex<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByVertex<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByVertex<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("tangent Format not support");
                    }
                },
                [&](TEXCOORD_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByVertex<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByVertex<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32G32_SFLOAT:
                        readByVertex<PolygonSize, Vector2fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32_SFLOAT:
                        readByVertex<PolygonSize, Vector1fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByVertex<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R16G16_SFLOAT:
                        readByVertex<PolygonSize, Vector2hu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("texcoord Format not support");
                    }
                },
                [&](SV_Position_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readPointByVertex<PolygonSize, Vector4fu>(pMesh, buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readPointByVertex<PolygonSize, Vector3fu>(pMesh, buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readPointByVertex<PolygonSize, Vector4hu>(pMesh, buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("position Format not support");
                    }
                },
                [&](SV_Target_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByVertex<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByVertex<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    case Format::R8G8B8A8_UNORM:
                        readByVertex<PolygonSize, Unorm4>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("color Format not support");
                    }
                }
            ), e.mType);

        }
    }

    // IB
    mesh.mIndexBuffer.mPrimitiveTopology = GFX_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    mesh.mIndexBuffer.mPrimitiveCount = faceCount;
    if (vertexCount <= 65536) {
        mesh.mIndexBuffer.mElementSize = 2;
    } else {
        mesh.mIndexBuffer.mElementSize = 4;
    }
    mesh.mIndexBuffer.mBuffer.resize(mesh.mIndexBuffer.mElementSize * faceCount * PolygonSize);

    auto indexCount = mesh.mIndexBuffer.mPrimitiveCount * PolygonSize;
    if (mesh.mIndexBuffer.mElementSize == 2) {
        for (uint32_t i = 0; i != indexCount; ++i) {
            reinterpret_cast<uint16_t*>(mesh.mIndexBuffer.mBuffer.data())[i] = gsl::narrow_cast<uint16_t>(i);
        }
    } else if (mesh.mIndexBuffer.mElementSize == 4) {
        for (uint32_t i = 0; i != indexCount; ++i) {
            reinterpret_cast<uint32_t*>(mesh.mIndexBuffer.mBuffer.data())[i] = i;
        }
    }
}

void fillBufferByPoint(const MeshBufferLayout& layout,
    const fbxsdk::FbxMesh* pMesh, MeshData& mesh
) {
    static const int PolygonSize = 3;
    const int faceCount = pMesh->GetPolygonCount();
    const int pointCount = pMesh->GetControlPointsCount();
    const int vertexCount = pointCount;

    mesh.mVertexBuffers.reserve(layout.mBuffers.size());
    for (const auto& desc : layout.mBuffers) {
        auto& vb = mesh.mVertexBuffers.emplace_back();
        vb.mDesc = desc;
        vb.mVertexCount = vertexCount;
        vb.mBuffer.resize(desc.mVertexSize * vb.mVertexCount);
    }

    std::array<int, 10> count = {};
    
    for (auto& vb : mesh.mVertexBuffers) {
        auto start = vb.mBuffer.data();
        for (const auto& e : vb.mDesc.mElements) {
            const auto& slot = count.at(e.mType.index())++;
            auto buffer = start + e.mAlignedByteOffset;
            auto stride = vb.mDesc.mVertexSize;
            visit(overload(
                [&](BINORMAL_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByPoint<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByPoint<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByPoint<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementBinormal(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("binormal Format not support");
                    }
                },
                [&](BLENDINDICES_) {
                    throw std::invalid_argument("blend index not supported yet");
                },
                [&](BLENDWEIGHT_) {
                    throw std::invalid_argument("blend weight not supported yet");
                },
                [&](NORMAL_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByPoint<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByPoint<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByPoint<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementNormal(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("normal Format not support");
                    }
                },
                [&](POSITIONT_) {
                    throw std::invalid_argument("positiont not supported yet");
                },
                [&](PSIZE_) {
                    throw std::invalid_argument("psize not supported yet");
                },
                [&](TANGENT_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByPoint<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByPoint<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByPoint<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementTangent(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("tangent Format not support");
                    }
                },
                [&](TEXCOORD_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByPoint<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readByPoint<PolygonSize, Vector3fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32G32_SFLOAT:
                        readByPoint<PolygonSize, Vector2fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R32_SFLOAT:
                        readByPoint<PolygonSize, Vector1fu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByPoint<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    case Format::R16G16_SFLOAT:
                        readByPoint<PolygonSize, Vector2hu>(pMesh, pMesh->GetElementUV(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("texcoord Format not support");
                    }
                },
                [&](SV_Position_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readPointByPoint<PolygonSize, Vector4fu>(pMesh, buffer, stride);
                        break;
                    case Format::R32G32B32_SFLOAT:
                        readPointByPoint<PolygonSize, Vector3fu>(pMesh, buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readPointByPoint<PolygonSize, Vector4hu>(pMesh, buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("position Format not support");
                    }
                },
                [&](SV_Target_) {
                    switch (e.mFormat) {
                    case Format::R32G32B32A32_SFLOAT:
                        readByPoint<PolygonSize, Vector4fu>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    case Format::R16G16B16A16_SFLOAT:
                        readByPoint<PolygonSize, Vector4hu>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    case Format::R8G8B8A8_UNORM:
                        readByPoint<PolygonSize, Unorm4>(pMesh, pMesh->GetElementVertexColor(slot), buffer, stride);
                        break;
                    default:
                        throw std::invalid_argument("color Format not support");
                    }
                }
            ), e.mType);

        }
    }

    // IB
    mesh.mIndexBuffer.mPrimitiveTopology = GFX_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    mesh.mIndexBuffer.mPrimitiveCount = faceCount;
    if (vertexCount <= 65536) {
        mesh.mIndexBuffer.mElementSize = 2;
    } else {
        mesh.mIndexBuffer.mElementSize = 4;
    }
    mesh.mIndexBuffer.mBuffer.resize(mesh.mIndexBuffer.mElementSize * faceCount * PolygonSize);

    auto indexCount = mesh.mIndexBuffer.mPrimitiveCount * PolygonSize;
    if (mesh.mIndexBuffer.mElementSize == 2) {
        for (int faceID = 0, vertexID = 0; faceID != faceCount; ++faceID) {
            int lPolygonSize = pMesh->GetPolygonSize(faceID);
            Expects(lPolygonSize == PolygonSize);

            for (int j = 0; j < lPolygonSize; ++j, ++vertexID) {
                uint16_t pointID = gsl::narrow<uint16_t>(pMesh->GetPolygonVertex(faceID, j));
                reinterpret_cast<uint16_t*>(mesh.mIndexBuffer.mBuffer.data())[vertexID] = pointID;
            }
        }
    } else if (mesh.mIndexBuffer.mElementSize == 4) {
        for (int faceID = 0, vertexID = 0; faceID != faceCount; ++faceID) {
            int lPolygonSize = pMesh->GetPolygonSize(faceID);
            Expects(lPolygonSize == PolygonSize);

            for (int j = 0; j < lPolygonSize; ++j, ++vertexID) {
                int pointID = pMesh->GetPolygonVertex(faceID, j);
                reinterpret_cast<uint32_t*>(mesh.mIndexBuffer.mBuffer.data())[vertexID] = pointID;
            }
        }
    }
}

} // namespace

void AssetFbxDeleter::operator()(fbxsdk::FbxManager* pManager) const noexcept {
    if (pManager)
        pManager->Destroy();
}

void AssetFbxDeleter::operator()(fbxsdk::FbxObject* pObject) const noexcept {
    if (pObject)
        pObject->Destroy();
}

AssetFbxScene::AssetFbxScene(FbxPtr<fbxsdk::FbxScene> ptr, const MetaID& metaID,
    const std::filesystem::path& assetFolder, const std::filesystem::path& assetPath)
    : mScene(std::move(ptr))
    , mMetaID(metaID)
    , mAssetFolder(assetFolder)
    , mAssetPath(assetPath)
    , mMaterialFolder(mAssetPath.parent_path() / "materials")
{

}

AssetFbxScene::~AssetFbxScene() = default;

std::filesystem::path AssetFbxScene::getMaterialPath(std::string_view nodeName, size_t id, size_t count) const {
    if (count > 1) {
        return mMaterialFolder / (str(nodeName) + "-" + std::to_string(id) + ".material");
    } else {
        return mMaterialFolder / (str(nodeName) + ".material");
    }
}

std::string AssetFbxScene::getMeshName(const fbxsdk::FbxMesh* pMesh, std::set<std::string>& names, size_t& meshID) const {
    std::string meshName = pMesh->GetName();
    if (meshName.empty()) {
        meshName = "Mesh" + std::to_string(meshID);
        ++meshID;
    }

    while (true) {
        auto res = names.emplace(meshName);
        if (res.second) {
            break;
        }
        meshName = "Mesh" + std::to_string(meshID);
        ++meshID;
    }
    return meshName;
}

void AssetFbxScene::createMaterials(const std::function<void(std::string_view, const Map<std::string, std::string>&)>& func) const {
    uint32_t nodeID = 0;
    createMaterials(func, mScene->GetRootNode(), nodeID);
}

void AssetFbxScene::createMaterials(const std::function<void(std::string_view, const Map<std::string, std::string>&)>& func,
    fbxsdk::FbxNode* pFbxNode, uint32_t& nodeID
) const {
    std::string nodeName = pFbxNode->GetName();

    Expects(pFbxNode);
    auto sz = pFbxNode->GetMaterialCount();
    for (int i = 0; i != sz; ++i) {
        fbxsdk::FbxSurfaceMaterial* pMat = pFbxNode->GetMaterial(i);
        Expects(pMat);

        auto materialFilename = getMaterialPath(nodeName, i, sz);
        auto materialName = getAssetNameFromFullPath(materialFilename, mAssetFolder);

        Map<std::string, std::string> textures;

        FbxProperty prop = pMat->FindProperty("DiffuseColor");
        auto type = prop.GetPropertyDataType();
        auto typeEnum = type.GetType();
        std::string typeName = type.GetName();
        std::ignore = type;
        std::ignore = typeEnum;
        std::ignore = typeName;
        
        if (prop.IsValid()) {
            auto pTex = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxTexture>(0));
            if (pTex) {
                auto texFilename = std::filesystem::path(getRelativeFilename(mAssetPath, pTex->GetRelativeFileName()));
                auto texAssetName = getAssetNameFromFullPath(texFilename, mAssetFolder);
                textures.try_emplace("BaseColor", texAssetName);
            }
        }
        func(materialName, textures);
    }

    ++nodeID;

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        auto pChildFbxNode = pFbxNode->GetChild(i);
        createMaterials(func, pChildFbxNode, nodeID);
    }
}

void AssetFbxScene::getMeshNodeCount(fbxsdk::FbxNode* pFbxNode, size_t& count) const {
    auto pAttribute = pFbxNode->GetNodeAttribute();
    if (pAttribute) {
        switch (pAttribute->GetAttributeType()) {
        case fbxsdk::FbxNodeAttribute::eMesh:
            ++count;
            break;
        }
    }

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        auto pChildNode = pFbxNode->GetChild(i);
        getMeshNodeCount(pChildNode, count);
    }
}

void AssetFbxScene::validateMaterialFiles(fbxsdk::FbxNode* pFbxNode) const {
    auto pAttribute = pFbxNode->GetNodeAttribute();
    if (pAttribute) {
        switch (pAttribute->GetAttributeType()) {
        case fbxsdk::FbxNodeAttribute::eMesh:
            auto sz = pFbxNode->GetMaterialCount();
            for (int i = 0; i != sz; ++i) {
                fbxsdk::FbxSurfaceMaterial* pMat = pFbxNode->GetMaterial(i);
                Expects(pMat);

                auto materialFilename = getMaterialPath(pFbxNode->GetName(), i, sz);
                auto materialMetaFilename = materialFilename;
                materialMetaFilename.replace_extension(".material.meta");

                auto [metaID, hasMetaID] = try_readMetaIDFile(materialMetaFilename);

                if (hasMetaID) {
                    if (!exists(materialFilename)) {
                        throw std::runtime_error("material file not found");
                    }
                } else {
                    throw std::runtime_error("material meta file not found in filesystem");
                }
            }
            break;
        }
    }

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        validateMaterialFiles(pFbxNode->GetChild(i));
    }
}

void AssetFbxScene::readInfo(const FbxInfo& info,
    MetaIDNameIndex<MeshInfo>& meshInfo, std::unordered_set<MetaID>& assets
) const {
    std::set<const fbxsdk::FbxMesh*> meshes;
    std::set<std::string> names;
    size_t meshID = 0;
    readMeshInfo(mScene->GetRootNode(), meshes, names, meshID, info, meshInfo, assets);
}

void AssetFbxScene::readMeshInfo(fbxsdk::FbxNode* pFbxNode, std::set<const fbxsdk::FbxMesh*>& meshes,
    std::set<std::string>& names, size_t& meshID, const FbxInfo& info,
    MetaIDNameIndex<MeshInfo>& meshInfo, std::unordered_set<MetaID>& assets
) const {
    // first pass
    auto pAttribute = pFbxNode->GetNodeAttribute();
    if (pAttribute) {
        switch (pAttribute->GetAttributeType()) {
        case fbxsdk::FbxNodeAttribute::eMesh:
            auto res = meshes.emplace(static_cast<const FbxMesh*>(pAttribute));
            if (res.second) {
                readMeshInfo(*res.first, names, meshID, info, meshInfo, assets);
            }
            break;
        }
    }

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        readMeshInfo(pFbxNode->GetChild(i), meshes, names, meshID, info, meshInfo, assets);
    }
}

void AssetFbxScene::readMeshInfo(const fbxsdk::FbxMesh* pMesh,
    std::set<std::string>& names, size_t& meshID,
    const FbxInfo& info, MetaIDNameIndex<MeshInfo>& meshInfo,
    std::unordered_set<MetaID>& assets
) const {
    auto meshName = getMeshName(pMesh, names, meshID);
    boost::uuids::name_generator_latest gen(mMetaID);
    auto metaID = gen(meshName);
    const_cast<std::vector<MetaID>&>(info.mMeshes).emplace_back(metaID);

    auto iter = meshInfo.find(metaID);
    if (iter != meshInfo.end()) {
        throw std::runtime_error("mesh name uuid collision");
    }

    std::ostringstream oss;
    oss << metaID << ".mesh";
    auto assetPath = std::filesystem::path("star_meshes") / oss.str();

    MeshInfo mesh{ metaID, getAssetName(assetPath), meshName, &info };

    int faceCount = pMesh->GetPolygonCount();
    int polygonGroupCount = pMesh->GetElementPolygonGroupCount();
    int smoothingCount = pMesh->GetElementSmoothingCount();

    // fill submeshes
    int matElemCount = pMesh->GetElementMaterialCount();
    if (matElemCount == 0) {
        throw std::invalid_argument("Mesh ElementMaterialCount == 0");
    }
    if (matElemCount > 1) {
        throw std::invalid_argument("Mesh ElementMaterialCount > 1");
    }

    uint32_t meshFaceCount = faceCount;

    auto matElem = pMesh->GetElementMaterial(0);
    if (matElem->GetReferenceMode() == FbxGeometryElement::eDirect) {
        throw std::invalid_argument("element material index incorrect");
    }

    uint32_t lIndexArrayCount = matElem->GetIndexArray().GetCount();
    if (lIndexArrayCount == 1) {
        mesh.mNumSubMeshes = 1;
    } else if (meshFaceCount != lIndexArrayCount) {
        throw std::invalid_argument("face count inconsistent");
    } else {
        uint32_t prevMatID = -1;

        for (uint32_t j = 0; j < lIndexArrayCount; j++) {
            auto matID = matElem->GetIndexArray().GetAt(j);
            if (matID != prevMatID) {
                if (prevMatID != -1) {
                    ++mesh.mNumSubMeshes;
                }
                prevMatID = matID;
            }
        } // for each element
        if (prevMatID == -1)
            throw std::invalid_argument("no material");
        ++mesh.mNumSubMeshes;
    }

    bool added;
    std::tie(iter, added) = meshInfo.emplace(mesh);
    Ensures(added);
    auto res = assets.emplace(mesh.mMetaID);
    Ensures(res.second);
}

void AssetFbxScene::readMeshes(std::string_view layout, Resources& resources) const {
    size_t meshID = 0;
    std::set<const fbxsdk::FbxMesh*> meshes;
    std::set<std::string> names;
    readMeshes(layout, mScene->GetRootNode(), resources, meshes, names, meshID);
    Ensures(meshes.size() == names.size());
}

void AssetFbxScene::readMeshes(std::string_view layout,
    fbxsdk::FbxNode* pFbxNode, Resources& resources,
    std::set<const fbxsdk::FbxMesh*>& meshes, std::set<std::string>& names, size_t& meshID
) const {
    // first pass
    auto pAttribute = pFbxNode->GetNodeAttribute();
    if (pAttribute) {
        switch (pAttribute->GetAttributeType()) {
        case fbxsdk::FbxNodeAttribute::eMesh:
            auto res = meshes.emplace(static_cast<const FbxMesh*>(pAttribute));
            if (res.second) {
                readMesh(layout, *res.first, resources, names, meshID);
            }
            break;
        }
    }

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        readMeshes(layout, pFbxNode->GetChild(i), resources, meshes, names, meshID);
    }
}

void AssetFbxScene::readMesh(std::string_view layoutName,
    const fbxsdk::FbxMesh* pMesh, Resources& resources,
    std::set<std::string>& names, size_t& meshID
) const {
    auto meshName = getMeshName(pMesh, names, meshID);
    boost::uuids::name_generator_latest gen(mMetaID);
    auto metaID = gen(meshName);
    auto iter = resources.mMeshes.find(metaID);
    if (iter != resources.mMeshes.end()) {
        throw std::runtime_error("mesh name uuid collision");
    }

    bool added;
    std::tie(iter, added) = resources.mMeshes.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(metaID),
        std::forward_as_tuple());
    Ensures(added);

    auto& mesh = iter->second;
    mesh.mLayoutName = layoutName;
    mesh.mLayoutID = resources.mSettings.mVertexLayoutIndex.at(mesh.mLayoutName);
    const auto& layout = resources.mSettings.mVertexLayouts.at(mesh.mLayoutID);
    checkLayoutRequirement(layout, pMesh);

    int faceCount = pMesh->GetPolygonCount();
    int polygonGroupCount = pMesh->GetElementPolygonGroupCount();
    int smoothingCount = pMesh->GetElementSmoothingCount();

    // check loading type
    bool byControlPoint = false;
    bool byVertex = false;
    bool byPolygon = false;

    auto setMode = [&](FbxGeometryElement::EMappingMode mode) {
        switch (mode) {
        case FbxGeometryElement::eByControlPoint:
            byControlPoint = true;
            break;
        case FbxGeometryElement::eByPolygonVertex:
            byVertex = true;
            break;
        case FbxGeometryElement::eByPolygon:
            byPolygon = true;
            break;
        default:
            throw std::invalid_argument("Fbx getElementID only supports eByControlPoint, eByPolygon, or eByPolygonVertex");
        }
    };

    if (pMesh->GetElementBinormalCount() > 0)
        setMode(pMesh->GetElementBinormal(0)->GetMappingMode());

    if (pMesh->GetElementNormalCount() > 0)
        setMode(pMesh->GetElementNormal(0)->GetMappingMode());

    if (pMesh->GetElementTangentCount() > 0)
        setMode(pMesh->GetElementTangent(0)->GetMappingMode());

    if (pMesh->GetElementVertexColorCount() > 0)
        setMode(pMesh->GetElementVertexColor(0)->GetMappingMode());

    auto uvCount = pMesh->GetElementUVCount();
    for (int i = 0; i != uvCount; ++i) {
        auto pUV = pMesh->GetElementUV(i);
        setMode(pUV->GetMappingMode());
    }

    if (byPolygon)
        byVertex = true;

    const int PolygonSize = 3;

    if (byVertex) {
        fillBufferByVertex(layout, pMesh, mesh);
    } else {
        fillBufferByPoint(layout, pMesh, mesh);
    }

    // fill submeshes
    int matElemCount = pMesh->GetElementMaterialCount();
    if (matElemCount == 0) {
        throw std::invalid_argument("Mesh ElementMaterialCount == 0");
    }
    if (matElemCount > 1) {
        throw std::invalid_argument("Mesh ElementMaterialCount > 1");
    }

    uint32_t meshFaceCount = faceCount;

    auto matElem = pMesh->GetElementMaterial(0);
    if (matElem->GetReferenceMode() == FbxGeometryElement::eDirect) {
        throw std::invalid_argument("element material index incorrect");
    }

    uint32_t lIndexArrayCount = matElem->GetIndexArray().GetCount();
    if (lIndexArrayCount == 1) {
        mesh.mSubMeshes.emplace_back(SubMeshData{ 0u, meshFaceCount * PolygonSize });
    } else if (meshFaceCount != lIndexArrayCount) {
        throw std::invalid_argument("face count inconsistent");
    } else {
        uint32_t prevMatID = -1;
        uint32_t prevOffset = -1;

        for (uint32_t j = 0; j < lIndexArrayCount; j++) {
            auto matID = matElem->GetIndexArray().GetAt(j);
            if (matID != prevMatID) {
                if (prevMatID != -1) {
                    mesh.mSubMeshes.emplace_back(SubMeshData{ prevOffset * PolygonSize, (j - prevOffset) * PolygonSize });
                }
                prevMatID = matID;
                prevOffset = j;
            }
        } // for each element
        if (prevMatID == -1)
            throw std::invalid_argument("no material");

        mesh.mSubMeshes.emplace_back(SubMeshData{ prevOffset * PolygonSize, (meshFaceCount - prevOffset) * PolygonSize });
    }
}

void AssetFbxScene::readFlattenedNodes(const MetaIDNameIndex<MeshInfo>& meshInfo,
    FlattenedObjects& batch
) const {
    validateMaterialFiles(mScene->GetRootNode());

    size_t nodeCount = 0;
    getMeshNodeCount(mScene->GetRootNode(), nodeCount);
    resize(batch, nodeCount);

    std::map<const fbxsdk::FbxMesh*, MetaID> meshes;
    std::set<std::string> names;
    size_t meshID = 0;
    size_t nodeID = 0;

    readFlattenedNodes(mScene->GetRootNode(), meshInfo, batch, nodeID, meshes, names, meshID);
}

void AssetFbxScene::readFlattenedNodes(fbxsdk::FbxNode* pFbxNode, const MetaIDNameIndex<MeshInfo>& meshInfo,
    FlattenedObjects& batch, size_t& nodeID,
    std::map<const fbxsdk::FbxMesh*, MetaID>& meshes, std::set<std::string>& names, size_t& meshID
) const {
    // transform
    Eigen::Map<const Matrix4du> transform(pFbxNode->EvaluateGlobalTransform());
    batch.mWorldTransforms[nodeID].mTransform = transform.cast<float>();
    batch.mWorldTransformInvs[nodeID].mTransform = batch.mWorldTransforms[nodeID].mTransform.inverse();

    // mesh renderer
    auto pAttribute = pFbxNode->GetNodeAttribute();
    if (pAttribute) {
        switch (pAttribute->GetAttributeType()) {
        case fbxsdk::FbxNodeAttribute::eMesh:
            MetaID meshMetaID{};
            auto res = meshes.emplace(static_cast<const FbxMesh*>(pAttribute), meshMetaID);
            if (res.second) {
                boost::uuids::name_generator_latest gen(mMetaID);
                auto meshName = getMeshName(res.first->first, names, meshID);
                meshMetaID = gen(meshName);
                res.first->second = meshMetaID;
            } else {
                meshMetaID = res.first->second;
            }
            readMeshRenderer(meshInfo, pFbxNode, res.first->first, meshMetaID, batch, nodeID);
            ++nodeID;
            break;
        }
    }

    int childCount = pFbxNode->GetChildCount();
    for (int i = 0; i != childCount; ++i) {
        readFlattenedNodes(pFbxNode->GetChild(i), meshInfo, batch, nodeID, meshes, names, meshID);
    }
}

void AssetFbxScene::readMeshRenderer(const MetaIDNameIndex<MeshInfo>& meshInfo,
    fbxsdk::FbxNode* pFbxNode, const fbxsdk::FbxMesh* pMesh,
    const MetaID& meshMetaID, FlattenedObjects& batch, size_t& nodeID
) const {
    auto iter = meshInfo.find(meshMetaID);
    if (iter == meshInfo.end()) {
        throw std::runtime_error("mesh not found");
    }

    batch.mMeshRenderers[nodeID].mMeshID = meshMetaID;

    // fill submeshes
    int matElemCount = pMesh->GetElementMaterialCount();
    if (matElemCount == 0) {
        throw std::invalid_argument("Mesh ElementMaterialCount == 0");
    }
    if (matElemCount > 1) {
        throw std::invalid_argument("Mesh ElementMaterialCount > 1");
    }

    int faceCount = pMesh->GetPolygonCount();
    uint32_t meshFaceCount = faceCount;

    auto matElem = pMesh->GetElementMaterial(0);
    if (matElem->GetReferenceMode() == FbxGeometryElement::eDirect) {
        throw std::invalid_argument("element material index incorrect");
    }

    auto nodeMaterialCount = pFbxNode->GetMaterialCount();

    uint32_t lIndexArrayCount = matElem->GetIndexArray().GetCount();
    if (lIndexArrayCount == 1) {
        fbxsdk::FbxSurfaceMaterial* pMat = pFbxNode->GetMaterial(0);
        Expects(pMat);
        auto materialFilename = getMaterialPath(pFbxNode->GetName(), 0, 1);
        auto materialMetaFilename = materialFilename;
        materialMetaFilename.replace_extension(".material.meta");
        auto [materialMetaID, hasMetaID] = try_readMetaIDFile(materialMetaFilename);
        Expects(hasMetaID);
        batch.mMeshRenderers[nodeID].mMaterialIDs.emplace_back(materialMetaID);
    } else if (meshFaceCount != lIndexArrayCount) {
        throw std::invalid_argument("face count inconsistent");
    } else {
        uint32_t prevMatID = -1;
        uint32_t prevOffset = -1;

        size_t submeshMaterialID = 0;
        for (uint32_t j = 0; j < lIndexArrayCount; j++) {
            auto matID = matElem->GetIndexArray().GetAt(j);
            if (matID != prevMatID) {
                if (prevMatID != -1) {
                    fbxsdk::FbxSurfaceMaterial* pMat = pFbxNode->GetMaterial(prevMatID);
                    Expects(pMat);
                    auto materialFilename = getMaterialPath(pFbxNode->GetName(), prevMatID, nodeMaterialCount);
                    auto materialMetaFilename = materialFilename;
                    materialMetaFilename.replace_extension(".material.meta");
                    auto [materialMetaID, hasMetaID] = try_readMetaIDFile(materialMetaFilename);
                    Expects(hasMetaID);

                    batch.mMeshRenderers[nodeID].mMaterialIDs.emplace_back(materialMetaID);
                }
                prevMatID = matID;
                prevOffset = j;
            }
        } // for each element
        if (prevMatID == -1)
            throw std::invalid_argument("no material");

        fbxsdk::FbxSurfaceMaterial* pMat = pFbxNode->GetMaterial(prevMatID);
        Expects(pMat);
        auto materialFilename = getMaterialPath(pFbxNode->GetName(), prevMatID, nodeMaterialCount);
        auto materialMetaFilename = materialFilename;
        materialMetaFilename.replace_extension(".material.meta");
        auto [materialMetaID, hasMetaID] = try_readMetaIDFile(materialMetaFilename);
        Expects(hasMetaID);

        batch.mMeshRenderers[nodeID].mMaterialIDs.emplace_back(materialMetaID);
    }

    Ensures(iter->mNumSubMeshes == batch.mMeshRenderers[nodeID].mMaterialIDs.size());
}

}
