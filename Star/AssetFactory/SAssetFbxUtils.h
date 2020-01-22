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

namespace Star::Asset {

template<int Size, class Scalar, int Options, int MaxRows, int MaxCols, class Vector>
void toEigen(const Vector& src, Eigen::Matrix<Scalar, Size, 1, Options, MaxRows, MaxCols>& dst) {
    for (int i = 0; i != Size; ++i) {
        dst[i] = static_cast<Scalar>(src[i]);
    }
}

template<int Size, int Options, int MaxRows, int MaxCols, class Vector>
void toEigen(const Vector& src, Eigen::Matrix<uint8_t, Size, 1, Options, MaxRows, MaxCols>& dst) {
    for (int i = 0; i != Size; ++i) {
        dst[i] = static_cast<uint8_t>(src[i] * 255.f);
    }
}

template<class LayerElement>
MappingMode getMappingMode(const LayerElement* pLayer) {
    switch (pLayer->GetMappingMode()) {
    case FbxGeometryElement::eByControlPoint:
        return ByControlPoint;
    case FbxGeometryElement::eByPolygonVertex:
        return ByPolygonVertex;
    case FbxGeometryElement::eByPolygon:
        return ByPolygon;
    default:
        throw std::runtime_error("Fbx getElementID only supports eByControlPoint, eByPolygon, or eByPolygonVertex");
    }
}

template<class LayerElement>
ReferenceMode getReferenceMode(const LayerElement* pLayer) {
    switch (pLayer->GetReferenceMode()) {
    case FbxGeometryElement::eDirect:
        return Direct;
    case FbxGeometryElement::eIndexToDirect:
        return IndexToDirect;
    default:
        throw std::runtime_error("Fbx getElementID only supports eByControlPoint, eByPolygon, or eByPolygonVertex");
    }
}

template<int PolygonSize, class Vector, class LayerElement>
void readByVertex(const fbxsdk::FbxMesh* pMesh, const LayerElement* pLayer,
    char* buffer, uint32_t stride
) {
    int faceCount = pMesh->GetPolygonCount();
    auto referenceMode = getReferenceMode(pLayer);
    auto mappingMode = getMappingMode(pLayer);
    const auto& buffer0 = pLayer->GetDirectArray();

    visit(overload(
        [&](Direct_, ByControlPoint_) {                
            for (int faceID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k) {
                    int pointID = pMesh->GetPolygonVertex(faceID, k);
                    int id = pointID;
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        },
        [&](Direct_, ByPolygonVertex_) {
            for (int faceID = 0, vertexID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k, ++vertexID) {
                    int id = vertexID;
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        },
        [&](Direct_, ByPolygon_) {
            for (int faceID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k) {
                    int id = faceID;
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        },
        [&](IndexToDirect_, ByControlPoint_) {
            const auto& index = pLayer->GetIndexArray();
            for (int faceID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k) {
                    int pointID = pMesh->GetPolygonVertex(faceID, k);
                    int id = index.GetAt(pointID);
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        },
        [&](IndexToDirect_, ByPolygonVertex_) {
            const auto& index = pLayer->GetIndexArray();
            for (int faceID = 0, vertexID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k, ++vertexID) {
                    int id = index.GetAt(vertexID);
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        },
        [&](IndexToDirect_, ByPolygon_) {
            const auto& index = pLayer->GetIndexArray();
            for (int faceID = 0; faceID != faceCount; ++faceID) {
                Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
                for (int k = 0; k != PolygonSize; ++k) {
                    int id = index.GetAt(faceID);
                    toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                    buffer += stride;
                }
            }
        }
    ), referenceMode, mappingMode);
}

template<int PolygonSize, class Vector>
void readByVertex(int faceCount, const Vector& v, char* buffer, uint32_t stride) {
    for (int faceID = 0, vertexID = 0; faceID != faceCount; ++faceID) {
        for (int k = 0; k != PolygonSize; ++k, ++vertexID) {
            Eigen::Map<Vector> dst(reinterpret_cast<typename Vector::value_type*>(buffer));
            dst = v;
            buffer += stride;
        }
    }
}

template<int PolygonSize, class Vector>
void readPointByVertex(const fbxsdk::FbxMesh* pMesh, char* buffer, uint32_t stride) {
    int faceCount = pMesh->GetPolygonCount();
    for (int faceID = 0; faceID != faceCount; ++faceID) {
        Expects(pMesh->GetPolygonSize(faceID) == PolygonSize);
        for (int k = 0; k != PolygonSize; ++k) {
            int pointID = pMesh->GetPolygonVertex(faceID, k);
            toEigen(pMesh->GetControlPoints()[pointID], *reinterpret_cast<Vector*>(buffer));
            buffer += stride;
        }
    }
}

template<int PolygonSize, class Vector, class LayerElement>
void readByPoint(const fbxsdk::FbxMesh* pMesh, const LayerElement* pLayer,
    char* buffer, uint32_t stride
) {
    auto pointCount = pMesh->GetControlPointsCount();
    auto referenceMode = getReferenceMode(pLayer);
    auto mappingMode = getMappingMode(pLayer);
    const auto& buffer0 = pLayer->GetDirectArray();

    visit(overload(
        [&](Direct_, ByControlPoint_) {
            for (int pointID = 0; pointID != pointCount; ++pointID) {
                int id = pointID;
                toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                buffer += stride;
            }
        },
        [&](IndexToDirect_, ByControlPoint_) {
            const auto& index = pLayer->GetIndexArray();
            for (int pointID = 0; pointID != pointCount; ++pointID) {
                int id = index.GetAt(pointID);
                toEigen(buffer0.GetAt(id), *reinterpret_cast<Vector*>(buffer));
                buffer += stride;
            }
        },
        [&](auto, ByPolygonVertex_) {
            throw std::runtime_error("readByPoint shouldn't have by vertex");
        },
        [&](auto, ByPolygon_) {
            throw std::runtime_error("readByPoint shouldn't have by polygon");
        }
    ), referenceMode, mappingMode);
}

template<int PolygonSize, class Vector>
void readByPoint(int pointCount, const Vector& v, char* buffer, uint32_t stride) {
    for (int pointID = 0; pointID != pointCount; ++pointID) {
        Eigen::Map<Vector> dst(reinterpret_cast<typename Vector::value_type*>(buffer));
        dst = v;
        buffer += stride;
    }
}

template<int PolygonSize, class Vector>
void readPointByPoint(const fbxsdk::FbxMesh* pMesh, char* buffer, uint32_t stride) {
    int pointCount = pMesh->GetControlPointsCount();
    for (int pointID = 0; pointID != pointCount; ++pointID) {
        toEigen(pMesh->GetControlPoints()[pointID], *reinterpret_cast<Vector*>(buffer));
        buffer += stride;
    }
}

}
