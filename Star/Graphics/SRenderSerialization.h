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
#include <Star/Graphics/SRenderTypes.h>
#include <Star/Graphics/SRenderFormat.h>

namespace boost {

namespace serialization {

STAR_SERIALIZE_BINARY(Star::Graphics::Render::Format);

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RECT, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RECT, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RECT& v, const uint32_t version) {
    ar & v.mLeft;
    ar & v.mTop;
    ar & v.mRight;
    ar & v.mBottom;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DISP_RATIONAL, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DISP_RATIONAL, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DISP_RATIONAL& v, const uint32_t version) {
    ar & v.mNumerator;
    ar & v.mDenominator;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DISP_SAMPLE_DESC, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DISP_SAMPLE_DESC, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DISP_SAMPLE_DESC& v, const uint32_t version) {
    ar & v.mCount;
    ar & v.mQuality;
}

STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_DRIVER_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_FEATURE_LEVEL);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_PRIMITIVE_TOPOLOGY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_PRIMITIVE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_SRV_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_NAME);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_RESOURCE_RETURN_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_REGISTER_COMPONENT_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_TESSELLATOR_DOMAIN);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_TESSELLATOR_PARTITIONING);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_TESSELLATOR_OUTPUT_PRIMITIVE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_MIN_PRECISION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_INTERPOLATION_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_LIST_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_QUEUE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_QUEUE_PRIORITY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_QUEUE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PRIMITIVE_TOPOLOGY_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INPUT_CLASSIFICATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INPUT_ELEMENT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FILL_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CULL_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SO_DECLARATION_ENTRY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEWPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BOX);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMPARISON_FUNC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_WRITE_MASK);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STENCIL_OP);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCILOP_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_DESC1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BLEND);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BLEND_OP);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COLOR_WRITE_ENABLE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::LOGIC_OP);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_TARGET_BLEND_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BLEND_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CONSERVATIVE_RASTERIZATION_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RASTERIZER_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_BYTECODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STREAM_OUTPUT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INPUT_LAYOUT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INDEX_BUFFER_STRIP_CUT_VALUE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CACHED_PIPELINE_STATE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PIPELINE_STATE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GRAPHICS_PIPELINE_STATE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMPUTE_PIPELINE_STATE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PIPELINE_STATE_STREAM_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PIPELINE_STATE_SUBOBJECT_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_MIN_PRECISION_SUPPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILED_RESOURCES_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_BINDING_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CONSERVATIVE_RASTERIZATION_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FORMAT_SUPPORT1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FORMAT_SUPPORT2);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::MULTISAMPLE_QUALITY_LEVEL_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CROSS_NODE_SHARING_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_HEAP_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PROGRAMMABLE_SAMPLE_POSITIONS_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEW_INSTANCING_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS2);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_ROOT_SIGNATURE_VERSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_ROOT_SIGNATURE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_ARCHITECTURE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_ARCHITECTURE1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_FEATURE_LEVELS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GFX_SHADER_MODEL);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_SHADER_MODEL);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_FORMAT_SUPPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_FORMAT_INFO);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_CACHE_SUPPORT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_SHADER_CACHE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_COMMAND_QUEUE_PRIORITY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_LIST_SUPPORT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS3);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_EXISTING_HEAPS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHARED_RESOURCE_COMPATIBILITY_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS4);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HEAP_SERIALIZATION_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_SERIALIZATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_CROSS_NODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS5);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VARIABLE_SHADING_RATE_TIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_D3D12_OPTIONS6);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_QUERY_META_COMMAND);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_ALLOCATION_INFO);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_ALLOCATION_INFO1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HEAP_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CPU_PAGE_PROPERTY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::MEMORY_POOL);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HEAP_PROPERTIES);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HEAP_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HEAP_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXTURE_LAYOUT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_VALUE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CLEAR_VALUE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RANGE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RANGE_UINT64);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBRESOURCE_RANGE_UINT64);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBRESOURCE_INFO);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILED_RESOURCE_COORDINATE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILE_REGION_SIZE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILE_RANGE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBRESOURCE_TILING);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILE_SHAPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PACKED_MIP_INFO);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILE_MAPPING_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TILE_COPY_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_STATES);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_BARRIER_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_TRANSITION_BARRIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_ALIASING_BARRIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_UAV_BARRIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_BARRIER_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_BARRIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBRESOURCE_FOOTPRINT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PLACED_SUBRESOURCE_FOOTPRINT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXTURE_COPY_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXTURE_COPY_LOCATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOLVE_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SAMPLE_POSITION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEW_INSTANCE_LOCATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEW_INSTANCING_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEW_INSTANCING_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_COMPONENT_MAPPING);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUFFER_SRV_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUFFER_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_ARRAY_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_ARRAY_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX3D_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXCUBE_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXCUBE_ARRAY_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_ARRAY_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_SRV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SRV_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_RESOURCE_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CONSTANT_BUFFER_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FILTER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FILTER_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FILTER_REDUCTION_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEXTURE_ADDRESS_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SAMPLER_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUFFER_UAV_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUFFER_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_ARRAY_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_ARRAY_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX3D_UAV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::UAV_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::UNORDERED_ACCESS_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUFFER_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_ARRAY_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_ARRAY_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_ARRAY_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX3D_RTV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RTV_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_TARGET_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX1D_ARRAY_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2D_ARRAY_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::TEX2DMS_ARRAY_DSV);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DSV_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DSV_DIMENSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CLEAR_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FENCE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_HEAP_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_HEAP_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_HEAP_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_RANGE_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_RANGE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_DESCRIPTOR_TABLE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_CONSTANTS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_DESCRIPTOR);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADER_VISIBILITY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_PARAMETER_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_PARAMETER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_SIGNATURE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATIC_BORDER_COLOR);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATIC_SAMPLER_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_SIGNATURE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_RANGE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DESCRIPTOR_RANGE1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_DESCRIPTOR_TABLE1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_DESCRIPTOR_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_DESCRIPTOR1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_PARAMETER1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ROOT_SIGNATURE_DESC1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VERSIONED_ROOT_SIGNATURE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CPU_DESCRIPTOR_HANDLE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GPU_DESCRIPTOR_HANDLE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DISCARD_REGION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::QUERY_HEAP_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::QUERY_HEAP_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::QUERY_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PREDICATION_OP);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::QUERY_DATA_PIPELINE_STATISTICS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::QUERY_DATA_SO_STATISTICS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STREAM_OUTPUT_BUFFER_VIEW);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRAW_ARGUMENTS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRAW_INDEXED_ARGUMENTS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DISPATCH_ARGUMENTS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VERTEX_BUFFER_VIEW);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INDEX_BUFFER_VIEW);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INDIRECT_ARGUMENT_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::INDIRECT_ARGUMENT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_SIGNATURE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::WRITEBUFFERIMMEDIATE_PARAMETER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::WRITEBUFFERIMMEDIATE_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::MULTIPLE_FENCE_WAIT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESIDENCY_PRIORITY);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESIDENCY_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_LIST_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_POOL_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::COMMAND_RECORDER_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PROTECTED_SESSION_STATUS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PROTECTED_RESOURCE_SESSION_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::PROTECTED_RESOURCE_SESSION_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::LIFETIME_STATE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::META_COMMAND_PARAMETER_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::META_COMMAND_PARAMETER_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::META_COMMAND_PARAMETER_STAGE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::META_COMMAND_PARAMETER_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GRAPHICS_STATES);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::META_COMMAND_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_SUBOBJECT_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_SUBOBJECT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_OBJECT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_OBJECT_CONFIG);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GLOBAL_ROOT_SIGNATURE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::LOCAL_ROOT_SIGNATURE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::NODE_MASK);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::EXPORT_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::EXPORT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DXIL_LIBRARY_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::EXISTING_COLLECTION_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBOBJECT_TO_EXPORTS_ASSOCIATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HIT_GROUP_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HIT_GROUP_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_SHADER_CONFIG);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_PIPELINE_CONFIG);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_OBJECT_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::STATE_OBJECT_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_GEOMETRY_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_GEOMETRY_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_INSTANCE_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GPU_VIRTUAL_ADDRESS_AND_STRIDE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GPU_VIRTUAL_ADDRESS_RANGE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_GEOMETRY_TRIANGLES_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_AABB);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_GEOMETRY_AABBS_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::ELEMENTS_LAYOUT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SERIALIZED_DATA_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRIVER_MATCHING_IDENTIFIER_STATUS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_INSTANCE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_GEOMETRY_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RAY_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::HIT_KIND);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::AUTO_BREADCRUMB_OP);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::AUTO_BREADCRUMB_NODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_VERSION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_ENABLEMENT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEVICE_REMOVED_EXTENDED_DATA);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_ALLOCATION_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_ALLOCATION_NODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_AUTO_BREADCRUMBS_OUTPUT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DRED_PAGE_FAULT_OUTPUT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEVICE_REMOVED_EXTENDED_DATA1);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::VERSIONED_DEVICE_REMOVED_EXTENDED_DATA);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BACKGROUND_PROCESSING_MODE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::MEASUREMENTS_ACTION);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_BEGINNING_ACCESS_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_BEGINNING_ACCESS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_ENDING_ACCESS_TYPE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_ENDING_ACCESS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_RENDER_TARGET_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_DEPTH_STENCIL_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_PASS_FLAGS);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DISPATCH_RAYS_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SUBRESOURCE_DATA);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::MEMCPY_DEST);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::AXIS_SHADING_RATE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADING_RATE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::SHADING_RATE_COMBINER);

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::LargeWidth, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::LargeWidth, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::LargeWidth& v, const uint32_t version) {
    ar & v.mValue;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Width, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Width, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Width& v, const uint32_t version) {
    ar & v.mValue;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Height, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Height, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Height& v, const uint32_t version) {
    ar & v.mValue;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Immediate_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Immediate_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Immediate_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::TiledImmediate_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::TiledImmediate_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::TiledImmediate_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::TiledDeferred_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::TiledDeferred_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::TiledDeferred_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Direct3D_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Direct3D_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Direct3D_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Vulkan_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Vulkan_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Vulkan_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Metal_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Metal_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Metal_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::OpenGL_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::OpenGL_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::OpenGL_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BINORMAL_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BINORMAL_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BINORMAL_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BLENDINDICES_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BLENDINDICES_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BLENDINDICES_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::BLENDWEIGHT_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::BLENDWEIGHT_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::BLENDWEIGHT_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::NORMAL_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::NORMAL_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::NORMAL_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::POSITIONT_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::POSITIONT_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::POSITIONT_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::PSIZE_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::PSIZE_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::PSIZE_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::TANGENT_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::TANGENT_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::TANGENT_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::TEXCOORD_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::TEXCOORD_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::TEXCOORD_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_ClipDistance_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_ClipDistance_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_ClipDistance_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_CullDistance_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_CullDistance_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_CullDistance_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_Coverage_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_Coverage_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_Coverage_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_Depth_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_Depth_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_Depth_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_DepthGreaterEqual_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_DepthGreaterEqual_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_DepthGreaterEqual_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_DepthLessEqual_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_DepthLessEqual_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_DepthLessEqual_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_DispatchThreadID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_DispatchThreadID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_DispatchThreadID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_DomainLocation_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_DomainLocation_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_DomainLocation_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_GroupID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_GroupID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_GroupID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_GroupIndex_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_GroupIndex_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_GroupIndex_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_GroupThreadID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_GroupThreadID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_GroupThreadID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_GSInstanceID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_GSInstanceID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_GSInstanceID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_InnerCoverage_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_InnerCoverage_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_InnerCoverage_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_InsideTessFactor_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_InsideTessFactor_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_InsideTessFactor_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_InstanceID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_InstanceID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_InstanceID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_IsFrontFace_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_IsFrontFace_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_IsFrontFace_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_OutputControlPointID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_OutputControlPointID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_OutputControlPointID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_Position_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_Position_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_Position_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_PrimitiveID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_PrimitiveID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_PrimitiveID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_RenderTargetArrayIndex_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_RenderTargetArrayIndex_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_RenderTargetArrayIndex_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_SampleIndex_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_SampleIndex_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_SampleIndex_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_StencilRef_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_StencilRef_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_StencilRef_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_Target_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_Target_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_Target_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_TessFactor_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_TessFactor_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_TessFactor_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_VertexID_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_VertexID_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_VertexID_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SV_ViewportArrayIndex_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SV_ViewportArrayIndex_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SV_ViewportArrayIndex_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::CBV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::CBV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::CBV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UAV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UAV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UAV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SRV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SRV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SRV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SSV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SSV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SSV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::RTV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::RTV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::RTV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DSV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DSV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DSV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::IBV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::IBV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::IBV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::VBV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::VBV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::VBV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::SOV_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::SOV_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::SOV_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Table_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Table_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Table_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Constants_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Constants_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Constants_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Matrix_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Matrix_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Matrix_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Float4_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Float4_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Float4_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UInt4_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UInt4_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UInt4_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Int4_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Int4_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Int4_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Float2_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Float2_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Float2_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UInt2_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UInt2_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UInt2_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Int2_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Int2_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Int2_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Half4_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Half4_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Half4_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Float1_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Float1_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Float1_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::UInt1_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::UInt1_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::UInt1_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Int1_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Int1_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Int1_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Half2_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Half2_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Half2_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Fixed4_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Fixed4_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Fixed4_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::Half1_, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::Half1_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::Half1_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::DataID, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::DataID, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::DataID& v, const uint32_t version) {
    ar & v.mType;
    ar & v.mOffset;
}

STAR_CLASS_IMPLEMENTATION(Star::Graphics::Render::ConstantBuffer, object_serializable);
STAR_CLASS_TRACKING(Star::Graphics::Render::ConstantBuffer, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Graphics::Render::ConstantBuffer& v, const uint32_t version) {
    ar & v.mBuffer;
    ar & v.mIndex;
}

template<class Archive>
inline void load_construct_data(
    Archive& ar, std::pair<const std::pmr::string, Star::Graphics::Render::ConstantBuffer>* t, const unsigned int file_version
) {
    ::new(t) std::pair<const std::pmr::string, Star::Graphics::Render::ConstantBuffer>(std::piecewise_construct, std::forward_as_tuple(ar.resource()), std::forward_as_tuple(ar.resource()));
}

template<class Archive, class K>
inline void load_construct_data(
    Archive& ar, std::pair<K, Star::Graphics::Render::ConstantBuffer>* t, const unsigned int file_version
) {
    ::new(t) std::pair<K, Star::Graphics::Render::ConstantBuffer>(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(ar.resource()));
}

} // namespace serialization

} // namespace boost
