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

namespace Star {

namespace Graphics {

namespace Render {

inline const char* getName(const RECT& v) noexcept { return "RECT"; }
inline const char* getName(const DISP_RATIONAL& v) noexcept { return "DISP_RATIONAL"; }
inline const char* getName(const DISP_SAMPLE_DESC& v) noexcept { return "DISP_SAMPLE_DESC"; }
inline const char* getName(const COMMAND_QUEUE_DESC& v) noexcept { return "COMMAND_QUEUE_DESC"; }
inline const char* getName(const INPUT_ELEMENT_DESC& v) noexcept { return "INPUT_ELEMENT_DESC"; }
inline const char* getName(const SO_DECLARATION_ENTRY& v) noexcept { return "SO_DECLARATION_ENTRY"; }
inline const char* getName(const VIEWPORT& v) noexcept { return "VIEWPORT"; }
inline const char* getName(const BOX& v) noexcept { return "BOX"; }
inline const char* getName(const DEPTH_STENCILOP_DESC& v) noexcept { return "DEPTH_STENCILOP_DESC"; }
inline const char* getName(const DEPTH_STENCIL_DESC& v) noexcept { return "DEPTH_STENCIL_DESC"; }
inline const char* getName(const DEPTH_STENCIL_DESC1& v) noexcept { return "DEPTH_STENCIL_DESC1"; }
inline const char* getName(const RENDER_TARGET_BLEND_DESC& v) noexcept { return "RENDER_TARGET_BLEND_DESC"; }
inline const char* getName(const BLEND_DESC& v) noexcept { return "BLEND_DESC"; }
inline const char* getName(const RASTERIZER_DESC& v) noexcept { return "RASTERIZER_DESC"; }
inline const char* getName(const SHADER_BYTECODE& v) noexcept { return "SHADER_BYTECODE"; }
inline const char* getName(const STREAM_OUTPUT_DESC& v) noexcept { return "STREAM_OUTPUT_DESC"; }
inline const char* getName(const INPUT_LAYOUT_DESC& v) noexcept { return "INPUT_LAYOUT_DESC"; }
inline const char* getName(const CACHED_PIPELINE_STATE& v) noexcept { return "CACHED_PIPELINE_STATE"; }
inline const char* getName(const GRAPHICS_PIPELINE_STATE_DESC& v) noexcept { return "GRAPHICS_PIPELINE_STATE_DESC"; }
inline const char* getName(const COMPUTE_PIPELINE_STATE_DESC& v) noexcept { return "COMPUTE_PIPELINE_STATE_DESC"; }
inline const char* getName(const PIPELINE_STATE_STREAM_DESC& v) noexcept { return "PIPELINE_STATE_STREAM_DESC"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS1& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS1"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS2& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS2"; }
inline const char* getName(const FEATURE_DATA_ROOT_SIGNATURE& v) noexcept { return "FEATURE_DATA_ROOT_SIGNATURE"; }
inline const char* getName(const FEATURE_DATA_ARCHITECTURE& v) noexcept { return "FEATURE_DATA_ARCHITECTURE"; }
inline const char* getName(const FEATURE_DATA_ARCHITECTURE1& v) noexcept { return "FEATURE_DATA_ARCHITECTURE1"; }
inline const char* getName(const FEATURE_DATA_FEATURE_LEVELS& v) noexcept { return "FEATURE_DATA_FEATURE_LEVELS"; }
inline const char* getName(const FEATURE_DATA_SHADER_MODEL& v) noexcept { return "FEATURE_DATA_SHADER_MODEL"; }
inline const char* getName(const FEATURE_DATA_FORMAT_SUPPORT& v) noexcept { return "FEATURE_DATA_FORMAT_SUPPORT"; }
inline const char* getName(const FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS& v) noexcept { return "FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS"; }
inline const char* getName(const FEATURE_DATA_FORMAT_INFO& v) noexcept { return "FEATURE_DATA_FORMAT_INFO"; }
inline const char* getName(const FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT& v) noexcept { return "FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT"; }
inline const char* getName(const FEATURE_DATA_SHADER_CACHE& v) noexcept { return "FEATURE_DATA_SHADER_CACHE"; }
inline const char* getName(const FEATURE_DATA_COMMAND_QUEUE_PRIORITY& v) noexcept { return "FEATURE_DATA_COMMAND_QUEUE_PRIORITY"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS3& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS3"; }
inline const char* getName(const FEATURE_DATA_EXISTING_HEAPS& v) noexcept { return "FEATURE_DATA_EXISTING_HEAPS"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS4& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS4"; }
inline const char* getName(const FEATURE_DATA_SERIALIZATION& v) noexcept { return "FEATURE_DATA_SERIALIZATION"; }
inline const char* getName(const FEATURE_DATA_CROSS_NODE& v) noexcept { return "FEATURE_DATA_CROSS_NODE"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS5& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS5"; }
inline const char* getName(const FEATURE_DATA_D3D12_OPTIONS6& v) noexcept { return "FEATURE_DATA_D3D12_OPTIONS6"; }
inline const char* getName(const FEATURE_DATA_QUERY_META_COMMAND& v) noexcept { return "FEATURE_DATA_QUERY_META_COMMAND"; }
inline const char* getName(const RESOURCE_ALLOCATION_INFO& v) noexcept { return "RESOURCE_ALLOCATION_INFO"; }
inline const char* getName(const RESOURCE_ALLOCATION_INFO1& v) noexcept { return "RESOURCE_ALLOCATION_INFO1"; }
inline const char* getName(const HEAP_PROPERTIES& v) noexcept { return "HEAP_PROPERTIES"; }
inline const char* getName(const HEAP_DESC& v) noexcept { return "HEAP_DESC"; }
inline const char* getName(const RESOURCE_DESC& v) noexcept { return "RESOURCE_DESC"; }
inline const char* getName(const DEPTH_STENCIL_VALUE& v) noexcept { return "DEPTH_STENCIL_VALUE"; }
inline const char* getName(const CLEAR_VALUE& v) noexcept { return "CLEAR_VALUE"; }
inline const char* getName(const RANGE& v) noexcept { return "RANGE"; }
inline const char* getName(const RANGE_UINT64& v) noexcept { return "RANGE_UINT64"; }
inline const char* getName(const SUBRESOURCE_RANGE_UINT64& v) noexcept { return "SUBRESOURCE_RANGE_UINT64"; }
inline const char* getName(const SUBRESOURCE_INFO& v) noexcept { return "SUBRESOURCE_INFO"; }
inline const char* getName(const TILED_RESOURCE_COORDINATE& v) noexcept { return "TILED_RESOURCE_COORDINATE"; }
inline const char* getName(const TILE_REGION_SIZE& v) noexcept { return "TILE_REGION_SIZE"; }
inline const char* getName(const SUBRESOURCE_TILING& v) noexcept { return "SUBRESOURCE_TILING"; }
inline const char* getName(const TILE_SHAPE& v) noexcept { return "TILE_SHAPE"; }
inline const char* getName(const PACKED_MIP_INFO& v) noexcept { return "PACKED_MIP_INFO"; }
inline const char* getName(const RESOURCE_TRANSITION_BARRIER& v) noexcept { return "RESOURCE_TRANSITION_BARRIER"; }
inline const char* getName(const RESOURCE_ALIASING_BARRIER& v) noexcept { return "RESOURCE_ALIASING_BARRIER"; }
inline const char* getName(const RESOURCE_UAV_BARRIER& v) noexcept { return "RESOURCE_UAV_BARRIER"; }
inline const char* getName(const RESOURCE_BARRIER& v) noexcept { return "RESOURCE_BARRIER"; }
inline const char* getName(const SUBRESOURCE_FOOTPRINT& v) noexcept { return "SUBRESOURCE_FOOTPRINT"; }
inline const char* getName(const PLACED_SUBRESOURCE_FOOTPRINT& v) noexcept { return "PLACED_SUBRESOURCE_FOOTPRINT"; }
inline const char* getName(const TEXTURE_COPY_LOCATION& v) noexcept { return "TEXTURE_COPY_LOCATION"; }
inline const char* getName(const SAMPLE_POSITION& v) noexcept { return "SAMPLE_POSITION"; }
inline const char* getName(const VIEW_INSTANCE_LOCATION& v) noexcept { return "VIEW_INSTANCE_LOCATION"; }
inline const char* getName(const VIEW_INSTANCING_DESC& v) noexcept { return "VIEW_INSTANCING_DESC"; }
inline const char* getName(const BUFFER_SRV& v) noexcept { return "BUFFER_SRV"; }
inline const char* getName(const TEX1D_SRV& v) noexcept { return "TEX1D_SRV"; }
inline const char* getName(const TEX1D_ARRAY_SRV& v) noexcept { return "TEX1D_ARRAY_SRV"; }
inline const char* getName(const TEX2D_SRV& v) noexcept { return "TEX2D_SRV"; }
inline const char* getName(const TEX2D_ARRAY_SRV& v) noexcept { return "TEX2D_ARRAY_SRV"; }
inline const char* getName(const TEX3D_SRV& v) noexcept { return "TEX3D_SRV"; }
inline const char* getName(const TEXCUBE_SRV& v) noexcept { return "TEXCUBE_SRV"; }
inline const char* getName(const TEXCUBE_ARRAY_SRV& v) noexcept { return "TEXCUBE_ARRAY_SRV"; }
inline const char* getName(const TEX2DMS_SRV& v) noexcept { return "TEX2DMS_SRV"; }
inline const char* getName(const TEX2DMS_ARRAY_SRV& v) noexcept { return "TEX2DMS_ARRAY_SRV"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_SRV& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_SRV"; }
inline const char* getName(const SHADER_RESOURCE_VIEW_DESC& v) noexcept { return "SHADER_RESOURCE_VIEW_DESC"; }
inline const char* getName(const CONSTANT_BUFFER_VIEW_DESC& v) noexcept { return "CONSTANT_BUFFER_VIEW_DESC"; }
inline const char* getName(const SAMPLER_DESC& v) noexcept { return "SAMPLER_DESC"; }
inline const char* getName(const BUFFER_UAV& v) noexcept { return "BUFFER_UAV"; }
inline const char* getName(const TEX1D_UAV& v) noexcept { return "TEX1D_UAV"; }
inline const char* getName(const TEX1D_ARRAY_UAV& v) noexcept { return "TEX1D_ARRAY_UAV"; }
inline const char* getName(const TEX2D_UAV& v) noexcept { return "TEX2D_UAV"; }
inline const char* getName(const TEX2D_ARRAY_UAV& v) noexcept { return "TEX2D_ARRAY_UAV"; }
inline const char* getName(const TEX3D_UAV& v) noexcept { return "TEX3D_UAV"; }
inline const char* getName(const UNORDERED_ACCESS_VIEW_DESC& v) noexcept { return "UNORDERED_ACCESS_VIEW_DESC"; }
inline const char* getName(const BUFFER_RTV& v) noexcept { return "BUFFER_RTV"; }
inline const char* getName(const TEX1D_RTV& v) noexcept { return "TEX1D_RTV"; }
inline const char* getName(const TEX1D_ARRAY_RTV& v) noexcept { return "TEX1D_ARRAY_RTV"; }
inline const char* getName(const TEX2D_RTV& v) noexcept { return "TEX2D_RTV"; }
inline const char* getName(const TEX2DMS_RTV& v) noexcept { return "TEX2DMS_RTV"; }
inline const char* getName(const TEX2D_ARRAY_RTV& v) noexcept { return "TEX2D_ARRAY_RTV"; }
inline const char* getName(const TEX2DMS_ARRAY_RTV& v) noexcept { return "TEX2DMS_ARRAY_RTV"; }
inline const char* getName(const TEX3D_RTV& v) noexcept { return "TEX3D_RTV"; }
inline const char* getName(const RENDER_TARGET_VIEW_DESC& v) noexcept { return "RENDER_TARGET_VIEW_DESC"; }
inline const char* getName(const TEX1D_DSV& v) noexcept { return "TEX1D_DSV"; }
inline const char* getName(const TEX1D_ARRAY_DSV& v) noexcept { return "TEX1D_ARRAY_DSV"; }
inline const char* getName(const TEX2D_DSV& v) noexcept { return "TEX2D_DSV"; }
inline const char* getName(const TEX2D_ARRAY_DSV& v) noexcept { return "TEX2D_ARRAY_DSV"; }
inline const char* getName(const TEX2DMS_DSV& v) noexcept { return "TEX2DMS_DSV"; }
inline const char* getName(const TEX2DMS_ARRAY_DSV& v) noexcept { return "TEX2DMS_ARRAY_DSV"; }
inline const char* getName(const DEPTH_STENCIL_VIEW_DESC& v) noexcept { return "DEPTH_STENCIL_VIEW_DESC"; }
inline const char* getName(const DESCRIPTOR_HEAP_DESC& v) noexcept { return "DESCRIPTOR_HEAP_DESC"; }
inline const char* getName(const DESCRIPTOR_RANGE& v) noexcept { return "DESCRIPTOR_RANGE"; }
inline const char* getName(const ROOT_DESCRIPTOR_TABLE& v) noexcept { return "ROOT_DESCRIPTOR_TABLE"; }
inline const char* getName(const ROOT_CONSTANTS& v) noexcept { return "ROOT_CONSTANTS"; }
inline const char* getName(const ROOT_DESCRIPTOR& v) noexcept { return "ROOT_DESCRIPTOR"; }
inline const char* getName(const ROOT_PARAMETER& v) noexcept { return "ROOT_PARAMETER"; }
inline const char* getName(const STATIC_SAMPLER_DESC& v) noexcept { return "STATIC_SAMPLER_DESC"; }
inline const char* getName(const ROOT_SIGNATURE_DESC& v) noexcept { return "ROOT_SIGNATURE_DESC"; }
inline const char* getName(const DESCRIPTOR_RANGE1& v) noexcept { return "DESCRIPTOR_RANGE1"; }
inline const char* getName(const ROOT_DESCRIPTOR_TABLE1& v) noexcept { return "ROOT_DESCRIPTOR_TABLE1"; }
inline const char* getName(const ROOT_DESCRIPTOR1& v) noexcept { return "ROOT_DESCRIPTOR1"; }
inline const char* getName(const ROOT_PARAMETER1& v) noexcept { return "ROOT_PARAMETER1"; }
inline const char* getName(const ROOT_SIGNATURE_DESC1& v) noexcept { return "ROOT_SIGNATURE_DESC1"; }
inline const char* getName(const VERSIONED_ROOT_SIGNATURE_DESC& v) noexcept { return "VERSIONED_ROOT_SIGNATURE_DESC"; }
inline const char* getName(const CPU_DESCRIPTOR_HANDLE& v) noexcept { return "CPU_DESCRIPTOR_HANDLE"; }
inline const char* getName(const GPU_DESCRIPTOR_HANDLE& v) noexcept { return "GPU_DESCRIPTOR_HANDLE"; }
inline const char* getName(const DISCARD_REGION& v) noexcept { return "DISCARD_REGION"; }
inline const char* getName(const QUERY_HEAP_DESC& v) noexcept { return "QUERY_HEAP_DESC"; }
inline const char* getName(const QUERY_DATA_PIPELINE_STATISTICS& v) noexcept { return "QUERY_DATA_PIPELINE_STATISTICS"; }
inline const char* getName(const QUERY_DATA_SO_STATISTICS& v) noexcept { return "QUERY_DATA_SO_STATISTICS"; }
inline const char* getName(const STREAM_OUTPUT_BUFFER_VIEW& v) noexcept { return "STREAM_OUTPUT_BUFFER_VIEW"; }
inline const char* getName(const DRAW_ARGUMENTS& v) noexcept { return "DRAW_ARGUMENTS"; }
inline const char* getName(const DRAW_INDEXED_ARGUMENTS& v) noexcept { return "DRAW_INDEXED_ARGUMENTS"; }
inline const char* getName(const DISPATCH_ARGUMENTS& v) noexcept { return "DISPATCH_ARGUMENTS"; }
inline const char* getName(const VERTEX_BUFFER_VIEW& v) noexcept { return "VERTEX_BUFFER_VIEW"; }
inline const char* getName(const INDEX_BUFFER_VIEW& v) noexcept { return "INDEX_BUFFER_VIEW"; }
inline const char* getName(const INDIRECT_ARGUMENT_DESC& v) noexcept { return "INDIRECT_ARGUMENT_DESC"; }
inline const char* getName(const COMMAND_SIGNATURE_DESC& v) noexcept { return "COMMAND_SIGNATURE_DESC"; }
inline const char* getName(const WRITEBUFFERIMMEDIATE_PARAMETER& v) noexcept { return "WRITEBUFFERIMMEDIATE_PARAMETER"; }
inline const char* getName(const FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT& v) noexcept { return "FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT"; }
inline const char* getName(const PROTECTED_RESOURCE_SESSION_DESC& v) noexcept { return "PROTECTED_RESOURCE_SESSION_DESC"; }
inline const char* getName(const META_COMMAND_PARAMETER_DESC& v) noexcept { return "META_COMMAND_PARAMETER_DESC"; }
inline const char* getName(const META_COMMAND_DESC& v) noexcept { return "META_COMMAND_DESC"; }
inline const char* getName(const STATE_SUBOBJECT& v) noexcept { return "STATE_SUBOBJECT"; }
inline const char* getName(const STATE_OBJECT_CONFIG& v) noexcept { return "STATE_OBJECT_CONFIG"; }
inline const char* getName(const GLOBAL_ROOT_SIGNATURE& v) noexcept { return "GLOBAL_ROOT_SIGNATURE"; }
inline const char* getName(const LOCAL_ROOT_SIGNATURE& v) noexcept { return "LOCAL_ROOT_SIGNATURE"; }
inline const char* getName(const NODE_MASK& v) noexcept { return "NODE_MASK"; }
inline const char* getName(const EXPORT_DESC& v) noexcept { return "EXPORT_DESC"; }
inline const char* getName(const DXIL_LIBRARY_DESC& v) noexcept { return "DXIL_LIBRARY_DESC"; }
inline const char* getName(const EXISTING_COLLECTION_DESC& v) noexcept { return "EXISTING_COLLECTION_DESC"; }
inline const char* getName(const SUBOBJECT_TO_EXPORTS_ASSOCIATION& v) noexcept { return "SUBOBJECT_TO_EXPORTS_ASSOCIATION"; }
inline const char* getName(const DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION& v) noexcept { return "DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION"; }
inline const char* getName(const HIT_GROUP_DESC& v) noexcept { return "HIT_GROUP_DESC"; }
inline const char* getName(const RAYTRACING_SHADER_CONFIG& v) noexcept { return "RAYTRACING_SHADER_CONFIG"; }
inline const char* getName(const RAYTRACING_PIPELINE_CONFIG& v) noexcept { return "RAYTRACING_PIPELINE_CONFIG"; }
inline const char* getName(const STATE_OBJECT_DESC& v) noexcept { return "STATE_OBJECT_DESC"; }
inline const char* getName(const GPU_VIRTUAL_ADDRESS_AND_STRIDE& v) noexcept { return "GPU_VIRTUAL_ADDRESS_AND_STRIDE"; }
inline const char* getName(const GPU_VIRTUAL_ADDRESS_RANGE& v) noexcept { return "GPU_VIRTUAL_ADDRESS_RANGE"; }
inline const char* getName(const GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE& v) noexcept { return "GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE"; }
inline const char* getName(const RAYTRACING_GEOMETRY_TRIANGLES_DESC& v) noexcept { return "RAYTRACING_GEOMETRY_TRIANGLES_DESC"; }
inline const char* getName(const RAYTRACING_AABB& v) noexcept { return "RAYTRACING_AABB"; }
inline const char* getName(const RAYTRACING_GEOMETRY_AABBS_DESC& v) noexcept { return "RAYTRACING_GEOMETRY_AABBS_DESC"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC"; }
inline const char* getName(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER& v) noexcept { return "BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC"; }
inline const char* getName(const SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER& v) noexcept { return "SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER"; }
inline const char* getName(const SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER& v) noexcept { return "SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC"; }
inline const char* getName(const RAYTRACING_INSTANCE_DESC& v) noexcept { return "RAYTRACING_INSTANCE_DESC"; }
inline const char* getName(const RAYTRACING_GEOMETRY_DESC& v) noexcept { return "RAYTRACING_GEOMETRY_DESC"; }
inline const char* getName(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS& v) noexcept { return "BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS"; }
inline const char* getName(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC& v) noexcept { return "BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC"; }
inline const char* getName(const RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO& v) noexcept { return "RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO"; }
inline const char* getName(const AUTO_BREADCRUMB_NODE& v) noexcept { return "AUTO_BREADCRUMB_NODE"; }
inline const char* getName(const DEVICE_REMOVED_EXTENDED_DATA& v) noexcept { return "DEVICE_REMOVED_EXTENDED_DATA"; }
inline const char* getName(const DRED_ALLOCATION_NODE& v) noexcept { return "DRED_ALLOCATION_NODE"; }
inline const char* getName(const DRED_AUTO_BREADCRUMBS_OUTPUT& v) noexcept { return "DRED_AUTO_BREADCRUMBS_OUTPUT"; }
inline const char* getName(const DRED_PAGE_FAULT_OUTPUT& v) noexcept { return "DRED_PAGE_FAULT_OUTPUT"; }
inline const char* getName(const DEVICE_REMOVED_EXTENDED_DATA1& v) noexcept { return "DEVICE_REMOVED_EXTENDED_DATA1"; }
inline const char* getName(const VERSIONED_DEVICE_REMOVED_EXTENDED_DATA& v) noexcept { return "VERSIONED_DEVICE_REMOVED_EXTENDED_DATA"; }
inline const char* getName(const RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS& v) noexcept { return "RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS"; }
inline const char* getName(const RENDER_PASS_BEGINNING_ACCESS& v) noexcept { return "RENDER_PASS_BEGINNING_ACCESS"; }
inline const char* getName(const RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS& v) noexcept { return "RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS"; }
inline const char* getName(const RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS& v) noexcept { return "RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS"; }
inline const char* getName(const RENDER_PASS_ENDING_ACCESS& v) noexcept { return "RENDER_PASS_ENDING_ACCESS"; }
inline const char* getName(const RENDER_PASS_RENDER_TARGET_DESC& v) noexcept { return "RENDER_PASS_RENDER_TARGET_DESC"; }
inline const char* getName(const RENDER_PASS_DEPTH_STENCIL_DESC& v) noexcept { return "RENDER_PASS_DEPTH_STENCIL_DESC"; }
inline const char* getName(const DISPATCH_RAYS_DESC& v) noexcept { return "DISPATCH_RAYS_DESC"; }
inline const char* getName(const SUBRESOURCE_DATA& v) noexcept { return "SUBRESOURCE_DATA"; }
inline const char* getName(const MEMCPY_DEST& v) noexcept { return "MEMCPY_DEST"; }
inline const char* getName(const LargeWidth& v) noexcept { return "LargeWidth"; }
inline const char* getName(const Width& v) noexcept { return "Width"; }
inline const char* getName(const Height& v) noexcept { return "Height"; }
inline const char* getName(const Immediate_& v) noexcept { return "Immediate"; }
inline const char* getName(const TiledImmediate_& v) noexcept { return "TiledImmediate"; }
inline const char* getName(const TiledDeferred_& v) noexcept { return "TiledDeferred"; }
inline const char* getName(const Direct3D_& v) noexcept { return "Direct3D"; }
inline const char* getName(const Vulkan_& v) noexcept { return "Vulkan"; }
inline const char* getName(const Metal_& v) noexcept { return "Metal"; }
inline const char* getName(const OpenGL_& v) noexcept { return "OpenGL"; }
inline const char* getName(const BINORMAL_& v) noexcept { return "BINORMAL"; }
inline const char* getName(const BLENDINDICES_& v) noexcept { return "BLENDINDICES"; }
inline const char* getName(const BLENDWEIGHT_& v) noexcept { return "BLENDWEIGHT"; }
inline const char* getName(const NORMAL_& v) noexcept { return "NORMAL"; }
inline const char* getName(const POSITIONT_& v) noexcept { return "POSITIONT"; }
inline const char* getName(const PSIZE_& v) noexcept { return "PSIZE"; }
inline const char* getName(const TANGENT_& v) noexcept { return "TANGENT"; }
inline const char* getName(const TEXCOORD_& v) noexcept { return "TEXCOORD"; }
inline const char* getName(const SV_ClipDistance_& v) noexcept { return "SV_ClipDistance"; }
inline const char* getName(const SV_CullDistance_& v) noexcept { return "SV_CullDistance"; }
inline const char* getName(const SV_Coverage_& v) noexcept { return "SV_Coverage"; }
inline const char* getName(const SV_Depth_& v) noexcept { return "SV_Depth"; }
inline const char* getName(const SV_DepthGreaterEqual_& v) noexcept { return "SV_DepthGreaterEqual"; }
inline const char* getName(const SV_DepthLessEqual_& v) noexcept { return "SV_DepthLessEqual"; }
inline const char* getName(const SV_DispatchThreadID_& v) noexcept { return "SV_DispatchThreadID"; }
inline const char* getName(const SV_DomainLocation_& v) noexcept { return "SV_DomainLocation"; }
inline const char* getName(const SV_GroupID_& v) noexcept { return "SV_GroupID"; }
inline const char* getName(const SV_GroupIndex_& v) noexcept { return "SV_GroupIndex"; }
inline const char* getName(const SV_GroupThreadID_& v) noexcept { return "SV_GroupThreadID"; }
inline const char* getName(const SV_GSInstanceID_& v) noexcept { return "SV_GSInstanceID"; }
inline const char* getName(const SV_InnerCoverage_& v) noexcept { return "SV_InnerCoverage"; }
inline const char* getName(const SV_InsideTessFactor_& v) noexcept { return "SV_InsideTessFactor"; }
inline const char* getName(const SV_InstanceID_& v) noexcept { return "SV_InstanceID"; }
inline const char* getName(const SV_IsFrontFace_& v) noexcept { return "SV_IsFrontFace"; }
inline const char* getName(const SV_OutputControlPointID_& v) noexcept { return "SV_OutputControlPointID"; }
inline const char* getName(const SV_Position_& v) noexcept { return "SV_Position"; }
inline const char* getName(const SV_PrimitiveID_& v) noexcept { return "SV_PrimitiveID"; }
inline const char* getName(const SV_RenderTargetArrayIndex_& v) noexcept { return "SV_RenderTargetArrayIndex"; }
inline const char* getName(const SV_SampleIndex_& v) noexcept { return "SV_SampleIndex"; }
inline const char* getName(const SV_StencilRef_& v) noexcept { return "SV_StencilRef"; }
inline const char* getName(const SV_Target_& v) noexcept { return "SV_Target"; }
inline const char* getName(const SV_TessFactor_& v) noexcept { return "SV_TessFactor"; }
inline const char* getName(const SV_VertexID_& v) noexcept { return "SV_VertexID"; }
inline const char* getName(const SV_ViewportArrayIndex_& v) noexcept { return "SV_ViewportArrayIndex"; }
inline const char* getName(const CBV_& v) noexcept { return "CBV"; }
inline const char* getName(const UAV_& v) noexcept { return "UAV"; }
inline const char* getName(const SRV_& v) noexcept { return "SRV"; }
inline const char* getName(const SSV_& v) noexcept { return "SSV"; }
inline const char* getName(const RTV_& v) noexcept { return "RTV"; }
inline const char* getName(const DSV_& v) noexcept { return "DSV"; }
inline const char* getName(const IBV_& v) noexcept { return "IBV"; }
inline const char* getName(const VBV_& v) noexcept { return "VBV"; }
inline const char* getName(const SOV_& v) noexcept { return "SOV"; }
inline const char* getName(const Table_& v) noexcept { return "Table"; }
inline const char* getName(const Constants_& v) noexcept { return "Constants"; }
inline const char* getName(const OM_& v) noexcept { return "OM"; }
inline const char* getName(const PS_& v) noexcept { return "PS"; }
inline const char* getName(const GS_& v) noexcept { return "GS"; }
inline const char* getName(const DS_& v) noexcept { return "DS"; }
inline const char* getName(const TS_& v) noexcept { return "TS"; }
inline const char* getName(const HS_& v) noexcept { return "HS"; }
inline const char* getName(const VS_& v) noexcept { return "VS"; }
inline const char* getName(const CS_& v) noexcept { return "CS"; }
inline const char* getName(UpdateEnum e) noexcept {
    switch(e) {
    case PerInstance: return "PerInstance";
    case PerBatch: return "PerBatch";
    case PerPass: return "PerPass";
    case PerFrame: return "PerFrame";
    case UpdateCount: return "UpdateCount";
    }
    return "";
}
inline const char* getName(const DescriptorIndex& v) noexcept { return "DescriptorIndex"; }
inline const char* getName(const Matrix_& v) noexcept { return "Matrix"; }
inline const char* getName(const Float4_& v) noexcept { return "Float4"; }
inline const char* getName(const UInt4_& v) noexcept { return "UInt4"; }
inline const char* getName(const Int4_& v) noexcept { return "Int4"; }
inline const char* getName(const Float2_& v) noexcept { return "Float2"; }
inline const char* getName(const UInt2_& v) noexcept { return "UInt2"; }
inline const char* getName(const Int2_& v) noexcept { return "Int2"; }
inline const char* getName(const Half4_& v) noexcept { return "Half4"; }
inline const char* getName(const Float1_& v) noexcept { return "Float1"; }
inline const char* getName(const UInt1_& v) noexcept { return "UInt1"; }
inline const char* getName(const Int1_& v) noexcept { return "Int1"; }
inline const char* getName(const Half2_& v) noexcept { return "Half2"; }
inline const char* getName(const Fixed4_& v) noexcept { return "Fixed4"; }
inline const char* getName(const Half1_& v) noexcept { return "Half1"; }
inline const char* getName(const DataID& v) noexcept { return "DataID"; }
inline const char* getName(const ConstantBuffer& v) noexcept { return "ConstantBuffer"; }

} // namespace Render

} // namespace Graphics

} // namespace Star
