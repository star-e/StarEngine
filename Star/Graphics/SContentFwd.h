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
#include <Star/Graphics/SRenderFwd.h>
#include <Star/Graphics/SRenderGraphFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

struct VertexElement;
struct VertexElementIndex;
struct VertexBufferDesc;
struct MeshBufferLayout;
struct VertexBufferData;
struct IndexBufferData;
struct SubMeshData;
struct MeshData;
struct TextureData;
struct PipelineStateData;
struct ShaderProgramData;
struct ShaderInputLayout;
struct ShaderSubpassData;
struct ShaderPassData;
struct ShaderLevelData;
struct ShaderQueueData;
struct ShaderPipelineData;
struct ShaderSolutionData;
struct ShaderData;
struct ConstantDescriptor;
struct ConstantMap;
struct MaterialData;
struct FullScreenTriangle_;

using DrawCallType = std::variant<std::monostate, FullScreenTriangle_>;

struct DrawCallData;
struct BasicTransform;
struct WorldTransform;
struct WorldTransformInv;
struct BoundingBox;

using CameraView = std::variant<std::monostate, Direct3D_, Vulkan_, OpenGL_>;
using CameraNDC = std::variant<Direct3D_, Vulkan_>;

struct CameraData;
struct MeshRenderer;
struct FlattenedObjects;
struct ContentSettings;
struct DrawCall_;
struct ObjectBatch_;

using ContentType = std::variant<DrawCall_, ObjectBatch_>;

struct ContentID;
struct ContentData;
struct RenderGraphData;
struct Resources;

} // namespace Render

} // namespace Graphics

} // namespace Star
