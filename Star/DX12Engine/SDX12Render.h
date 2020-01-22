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
#include <Star/SAliasCast.h>

namespace Star::Graphics::Render {

inline D3D12_COMMAND_LIST_TYPE getDX12(COMMAND_LIST_TYPE v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_LIST_TYPE) == sizeof(COMMAND_LIST_TYPE));
    static_assert(alignof(D3D12_COMMAND_LIST_TYPE) == alignof(COMMAND_LIST_TYPE));
    return *alias_cast<D3D12_COMMAND_LIST_TYPE*>(&v);
}

inline D3D12_COMMAND_QUEUE_FLAGS getDX12(COMMAND_QUEUE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_QUEUE_FLAGS) == sizeof(COMMAND_QUEUE_FLAGS));
    static_assert(alignof(D3D12_COMMAND_QUEUE_FLAGS) == alignof(COMMAND_QUEUE_FLAGS));
    return *alias_cast<D3D12_COMMAND_QUEUE_FLAGS*>(&v);
}

inline D3D12_COMMAND_QUEUE_PRIORITY getDX12(COMMAND_QUEUE_PRIORITY v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_QUEUE_PRIORITY) == sizeof(COMMAND_QUEUE_PRIORITY));
    static_assert(alignof(D3D12_COMMAND_QUEUE_PRIORITY) == alignof(COMMAND_QUEUE_PRIORITY));
    return *alias_cast<D3D12_COMMAND_QUEUE_PRIORITY*>(&v);
}

inline D3D12_COMMAND_QUEUE_DESC getDX12(const COMMAND_QUEUE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_QUEUE_DESC) == sizeof(COMMAND_QUEUE_DESC));
    static_assert(alignof(D3D12_COMMAND_QUEUE_DESC) == alignof(COMMAND_QUEUE_DESC));
    return *alias_cast<const D3D12_COMMAND_QUEUE_DESC*>(&v);
}

inline D3D12_PRIMITIVE_TOPOLOGY_TYPE getDX12(PRIMITIVE_TOPOLOGY_TYPE v) noexcept {
    static_assert(sizeof(D3D12_PRIMITIVE_TOPOLOGY_TYPE) == sizeof(PRIMITIVE_TOPOLOGY_TYPE));
    static_assert(alignof(D3D12_PRIMITIVE_TOPOLOGY_TYPE) == alignof(PRIMITIVE_TOPOLOGY_TYPE));
    return *alias_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE*>(&v);
}

inline D3D12_INPUT_CLASSIFICATION getDX12(INPUT_CLASSIFICATION v) noexcept {
    static_assert(sizeof(D3D12_INPUT_CLASSIFICATION) == sizeof(INPUT_CLASSIFICATION));
    static_assert(alignof(D3D12_INPUT_CLASSIFICATION) == alignof(INPUT_CLASSIFICATION));
    return *alias_cast<D3D12_INPUT_CLASSIFICATION*>(&v);
}

inline D3D12_INPUT_ELEMENT_DESC getDX12(const INPUT_ELEMENT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_INPUT_ELEMENT_DESC) == sizeof(INPUT_ELEMENT_DESC));
    static_assert(alignof(D3D12_INPUT_ELEMENT_DESC) == alignof(INPUT_ELEMENT_DESC));
    return *alias_cast<const D3D12_INPUT_ELEMENT_DESC*>(&v);
}

inline D3D12_FILL_MODE getDX12(FILL_MODE v) noexcept {
    static_assert(sizeof(D3D12_FILL_MODE) == sizeof(FILL_MODE));
    static_assert(alignof(D3D12_FILL_MODE) == alignof(FILL_MODE));
    return *alias_cast<D3D12_FILL_MODE*>(&v);
}

inline D3D12_CULL_MODE getDX12(CULL_MODE v) noexcept {
    static_assert(sizeof(D3D12_CULL_MODE) == sizeof(CULL_MODE));
    static_assert(alignof(D3D12_CULL_MODE) == alignof(CULL_MODE));
    return *alias_cast<D3D12_CULL_MODE*>(&v);
}

inline D3D12_SO_DECLARATION_ENTRY getDX12(const SO_DECLARATION_ENTRY& v) noexcept {
    static_assert(sizeof(D3D12_SO_DECLARATION_ENTRY) == sizeof(SO_DECLARATION_ENTRY));
    static_assert(alignof(D3D12_SO_DECLARATION_ENTRY) == alignof(SO_DECLARATION_ENTRY));
    return *alias_cast<const D3D12_SO_DECLARATION_ENTRY*>(&v);
}

inline D3D12_VIEWPORT getDX12(const VIEWPORT& v) noexcept {
    static_assert(sizeof(D3D12_VIEWPORT) == sizeof(VIEWPORT));
    static_assert(alignof(D3D12_VIEWPORT) == alignof(VIEWPORT));
    return *alias_cast<const D3D12_VIEWPORT*>(&v);
}

inline D3D12_BOX getDX12(const BOX& v) noexcept {
    static_assert(sizeof(D3D12_BOX) == sizeof(BOX));
    static_assert(alignof(D3D12_BOX) == alignof(BOX));
    return *alias_cast<const D3D12_BOX*>(&v);
}

inline D3D12_COMPARISON_FUNC getDX12(COMPARISON_FUNC v) noexcept {
    static_assert(sizeof(D3D12_COMPARISON_FUNC) == sizeof(COMPARISON_FUNC));
    static_assert(alignof(D3D12_COMPARISON_FUNC) == alignof(COMPARISON_FUNC));
    return *alias_cast<D3D12_COMPARISON_FUNC*>(&v);
}

inline D3D12_DEPTH_WRITE_MASK getDX12(DEPTH_WRITE_MASK v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_WRITE_MASK) == sizeof(DEPTH_WRITE_MASK));
    static_assert(alignof(D3D12_DEPTH_WRITE_MASK) == alignof(DEPTH_WRITE_MASK));
    return *alias_cast<D3D12_DEPTH_WRITE_MASK*>(&v);
}

inline D3D12_STENCIL_OP getDX12(STENCIL_OP v) noexcept {
    static_assert(sizeof(D3D12_STENCIL_OP) == sizeof(STENCIL_OP));
    static_assert(alignof(D3D12_STENCIL_OP) == alignof(STENCIL_OP));
    return *alias_cast<D3D12_STENCIL_OP*>(&v);
}

inline D3D12_DEPTH_STENCILOP_DESC getDX12(const DEPTH_STENCILOP_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_STENCILOP_DESC) == sizeof(DEPTH_STENCILOP_DESC));
    static_assert(alignof(D3D12_DEPTH_STENCILOP_DESC) == alignof(DEPTH_STENCILOP_DESC));
    return *alias_cast<const D3D12_DEPTH_STENCILOP_DESC*>(&v);
}

inline D3D12_DEPTH_STENCIL_DESC getDX12(const DEPTH_STENCIL_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_STENCIL_DESC) == sizeof(DEPTH_STENCIL_DESC));
    static_assert(alignof(D3D12_DEPTH_STENCIL_DESC) == alignof(DEPTH_STENCIL_DESC));
    return *alias_cast<const D3D12_DEPTH_STENCIL_DESC*>(&v);
}

inline D3D12_DEPTH_STENCIL_DESC1 getDX12(const DEPTH_STENCIL_DESC1& v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_STENCIL_DESC1) == sizeof(DEPTH_STENCIL_DESC1));
    static_assert(alignof(D3D12_DEPTH_STENCIL_DESC1) == alignof(DEPTH_STENCIL_DESC1));
    return *alias_cast<const D3D12_DEPTH_STENCIL_DESC1*>(&v);
}

inline D3D12_BLEND getDX12(BLEND v) noexcept {
    static_assert(sizeof(D3D12_BLEND) == sizeof(BLEND));
    static_assert(alignof(D3D12_BLEND) == alignof(BLEND));
    return *alias_cast<D3D12_BLEND*>(&v);
}

inline D3D12_BLEND_OP getDX12(BLEND_OP v) noexcept {
    static_assert(sizeof(D3D12_BLEND_OP) == sizeof(BLEND_OP));
    static_assert(alignof(D3D12_BLEND_OP) == alignof(BLEND_OP));
    return *alias_cast<D3D12_BLEND_OP*>(&v);
}

inline D3D12_COLOR_WRITE_ENABLE getDX12(COLOR_WRITE_ENABLE v) noexcept {
    static_assert(sizeof(D3D12_COLOR_WRITE_ENABLE) == sizeof(COLOR_WRITE_ENABLE));
    static_assert(alignof(D3D12_COLOR_WRITE_ENABLE) == alignof(COLOR_WRITE_ENABLE));
    return *alias_cast<D3D12_COLOR_WRITE_ENABLE*>(&v);
}

inline D3D12_LOGIC_OP getDX12(LOGIC_OP v) noexcept {
    static_assert(sizeof(D3D12_LOGIC_OP) == sizeof(LOGIC_OP));
    static_assert(alignof(D3D12_LOGIC_OP) == alignof(LOGIC_OP));
    return *alias_cast<D3D12_LOGIC_OP*>(&v);
}

inline D3D12_RENDER_TARGET_BLEND_DESC getDX12(const RENDER_TARGET_BLEND_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_TARGET_BLEND_DESC) == sizeof(RENDER_TARGET_BLEND_DESC));
    static_assert(alignof(D3D12_RENDER_TARGET_BLEND_DESC) == alignof(RENDER_TARGET_BLEND_DESC));
    return *alias_cast<const D3D12_RENDER_TARGET_BLEND_DESC*>(&v);
}

inline D3D12_BLEND_DESC getDX12(const BLEND_DESC& v) noexcept {
    static_assert(sizeof(D3D12_BLEND_DESC) == sizeof(BLEND_DESC));
    static_assert(alignof(D3D12_BLEND_DESC) == alignof(BLEND_DESC));
    return *alias_cast<const D3D12_BLEND_DESC*>(&v);
}

inline D3D12_CONSERVATIVE_RASTERIZATION_MODE getDX12(CONSERVATIVE_RASTERIZATION_MODE v) noexcept {
    static_assert(sizeof(D3D12_CONSERVATIVE_RASTERIZATION_MODE) == sizeof(CONSERVATIVE_RASTERIZATION_MODE));
    static_assert(alignof(D3D12_CONSERVATIVE_RASTERIZATION_MODE) == alignof(CONSERVATIVE_RASTERIZATION_MODE));
    return *alias_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE*>(&v);
}

inline D3D12_RASTERIZER_DESC getDX12(const RASTERIZER_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RASTERIZER_DESC) == sizeof(RASTERIZER_DESC));
    static_assert(alignof(D3D12_RASTERIZER_DESC) == alignof(RASTERIZER_DESC));
    return *alias_cast<const D3D12_RASTERIZER_DESC*>(&v);
}

inline D3D12_SHADER_BYTECODE getDX12(const SHADER_BYTECODE& v) noexcept {
    static_assert(sizeof(D3D12_SHADER_BYTECODE) == sizeof(SHADER_BYTECODE));
    static_assert(alignof(D3D12_SHADER_BYTECODE) == alignof(SHADER_BYTECODE));
    return *alias_cast<const D3D12_SHADER_BYTECODE*>(&v);
}

inline D3D12_STREAM_OUTPUT_DESC getDX12(const STREAM_OUTPUT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_STREAM_OUTPUT_DESC) == sizeof(STREAM_OUTPUT_DESC));
    static_assert(alignof(D3D12_STREAM_OUTPUT_DESC) == alignof(STREAM_OUTPUT_DESC));
    return *alias_cast<const D3D12_STREAM_OUTPUT_DESC*>(&v);
}

inline D3D12_INPUT_LAYOUT_DESC getDX12(const INPUT_LAYOUT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_INPUT_LAYOUT_DESC) == sizeof(INPUT_LAYOUT_DESC));
    static_assert(alignof(D3D12_INPUT_LAYOUT_DESC) == alignof(INPUT_LAYOUT_DESC));
    return *alias_cast<const D3D12_INPUT_LAYOUT_DESC*>(&v);
}

inline D3D12_INDEX_BUFFER_STRIP_CUT_VALUE getDX12(INDEX_BUFFER_STRIP_CUT_VALUE v) noexcept {
    static_assert(sizeof(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE) == sizeof(INDEX_BUFFER_STRIP_CUT_VALUE));
    static_assert(alignof(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE) == alignof(INDEX_BUFFER_STRIP_CUT_VALUE));
    return *alias_cast<D3D12_INDEX_BUFFER_STRIP_CUT_VALUE*>(&v);
}

inline D3D12_CACHED_PIPELINE_STATE getDX12(const CACHED_PIPELINE_STATE& v) noexcept {
    static_assert(sizeof(D3D12_CACHED_PIPELINE_STATE) == sizeof(CACHED_PIPELINE_STATE));
    static_assert(alignof(D3D12_CACHED_PIPELINE_STATE) == alignof(CACHED_PIPELINE_STATE));
    return *alias_cast<const D3D12_CACHED_PIPELINE_STATE*>(&v);
}

inline D3D12_PIPELINE_STATE_FLAGS getDX12(PIPELINE_STATE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_PIPELINE_STATE_FLAGS) == sizeof(PIPELINE_STATE_FLAGS));
    static_assert(alignof(D3D12_PIPELINE_STATE_FLAGS) == alignof(PIPELINE_STATE_FLAGS));
    return *alias_cast<D3D12_PIPELINE_STATE_FLAGS*>(&v);
}

inline D3D12_GRAPHICS_PIPELINE_STATE_DESC getDX12(const GRAPHICS_PIPELINE_STATE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC) == sizeof(GRAPHICS_PIPELINE_STATE_DESC));
    static_assert(alignof(D3D12_GRAPHICS_PIPELINE_STATE_DESC) == alignof(GRAPHICS_PIPELINE_STATE_DESC));
    return *alias_cast<const D3D12_GRAPHICS_PIPELINE_STATE_DESC*>(&v);
}

inline D3D12_COMPUTE_PIPELINE_STATE_DESC getDX12(const COMPUTE_PIPELINE_STATE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_COMPUTE_PIPELINE_STATE_DESC) == sizeof(COMPUTE_PIPELINE_STATE_DESC));
    static_assert(alignof(D3D12_COMPUTE_PIPELINE_STATE_DESC) == alignof(COMPUTE_PIPELINE_STATE_DESC));
    return *alias_cast<const D3D12_COMPUTE_PIPELINE_STATE_DESC*>(&v);
}

inline D3D12_PIPELINE_STATE_STREAM_DESC getDX12(const PIPELINE_STATE_STREAM_DESC& v) noexcept {
    static_assert(sizeof(D3D12_PIPELINE_STATE_STREAM_DESC) == sizeof(PIPELINE_STATE_STREAM_DESC));
    static_assert(alignof(D3D12_PIPELINE_STATE_STREAM_DESC) == alignof(PIPELINE_STATE_STREAM_DESC));
    return *alias_cast<const D3D12_PIPELINE_STATE_STREAM_DESC*>(&v);
}

inline D3D12_PIPELINE_STATE_SUBOBJECT_TYPE getDX12(PIPELINE_STATE_SUBOBJECT_TYPE v) noexcept {
    static_assert(sizeof(D3D12_PIPELINE_STATE_SUBOBJECT_TYPE) == sizeof(PIPELINE_STATE_SUBOBJECT_TYPE));
    static_assert(alignof(D3D12_PIPELINE_STATE_SUBOBJECT_TYPE) == alignof(PIPELINE_STATE_SUBOBJECT_TYPE));
    return *alias_cast<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE*>(&v);
}

inline D3D12_FEATURE getDX12(FEATURE v) noexcept {
    static_assert(sizeof(D3D12_FEATURE) == sizeof(FEATURE));
    static_assert(alignof(D3D12_FEATURE) == alignof(FEATURE));
    return *alias_cast<D3D12_FEATURE*>(&v);
}

inline D3D12_SHADER_MIN_PRECISION_SUPPORT getDX12(SHADER_MIN_PRECISION_SUPPORT v) noexcept {
    static_assert(sizeof(D3D12_SHADER_MIN_PRECISION_SUPPORT) == sizeof(SHADER_MIN_PRECISION_SUPPORT));
    static_assert(alignof(D3D12_SHADER_MIN_PRECISION_SUPPORT) == alignof(SHADER_MIN_PRECISION_SUPPORT));
    return *alias_cast<D3D12_SHADER_MIN_PRECISION_SUPPORT*>(&v);
}

inline D3D12_TILED_RESOURCES_TIER getDX12(TILED_RESOURCES_TIER v) noexcept {
    static_assert(sizeof(D3D12_TILED_RESOURCES_TIER) == sizeof(TILED_RESOURCES_TIER));
    static_assert(alignof(D3D12_TILED_RESOURCES_TIER) == alignof(TILED_RESOURCES_TIER));
    return *alias_cast<D3D12_TILED_RESOURCES_TIER*>(&v);
}

inline D3D12_RESOURCE_BINDING_TIER getDX12(RESOURCE_BINDING_TIER v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_BINDING_TIER) == sizeof(RESOURCE_BINDING_TIER));
    static_assert(alignof(D3D12_RESOURCE_BINDING_TIER) == alignof(RESOURCE_BINDING_TIER));
    return *alias_cast<D3D12_RESOURCE_BINDING_TIER*>(&v);
}

inline D3D12_CONSERVATIVE_RASTERIZATION_TIER getDX12(CONSERVATIVE_RASTERIZATION_TIER v) noexcept {
    static_assert(sizeof(D3D12_CONSERVATIVE_RASTERIZATION_TIER) == sizeof(CONSERVATIVE_RASTERIZATION_TIER));
    static_assert(alignof(D3D12_CONSERVATIVE_RASTERIZATION_TIER) == alignof(CONSERVATIVE_RASTERIZATION_TIER));
    return *alias_cast<D3D12_CONSERVATIVE_RASTERIZATION_TIER*>(&v);
}

inline D3D12_FORMAT_SUPPORT1 getDX12(FORMAT_SUPPORT1 v) noexcept {
    static_assert(sizeof(D3D12_FORMAT_SUPPORT1) == sizeof(FORMAT_SUPPORT1));
    static_assert(alignof(D3D12_FORMAT_SUPPORT1) == alignof(FORMAT_SUPPORT1));
    return *alias_cast<D3D12_FORMAT_SUPPORT1*>(&v);
}

inline D3D12_FORMAT_SUPPORT2 getDX12(FORMAT_SUPPORT2 v) noexcept {
    static_assert(sizeof(D3D12_FORMAT_SUPPORT2) == sizeof(FORMAT_SUPPORT2));
    static_assert(alignof(D3D12_FORMAT_SUPPORT2) == alignof(FORMAT_SUPPORT2));
    return *alias_cast<D3D12_FORMAT_SUPPORT2*>(&v);
}

inline D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS getDX12(MULTISAMPLE_QUALITY_LEVEL_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS) == sizeof(MULTISAMPLE_QUALITY_LEVEL_FLAGS));
    static_assert(alignof(D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS) == alignof(MULTISAMPLE_QUALITY_LEVEL_FLAGS));
    return *alias_cast<D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS*>(&v);
}

inline D3D12_CROSS_NODE_SHARING_TIER getDX12(CROSS_NODE_SHARING_TIER v) noexcept {
    static_assert(sizeof(D3D12_CROSS_NODE_SHARING_TIER) == sizeof(CROSS_NODE_SHARING_TIER));
    static_assert(alignof(D3D12_CROSS_NODE_SHARING_TIER) == alignof(CROSS_NODE_SHARING_TIER));
    return *alias_cast<D3D12_CROSS_NODE_SHARING_TIER*>(&v);
}

inline D3D12_RESOURCE_HEAP_TIER getDX12(RESOURCE_HEAP_TIER v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_HEAP_TIER) == sizeof(RESOURCE_HEAP_TIER));
    static_assert(alignof(D3D12_RESOURCE_HEAP_TIER) == alignof(RESOURCE_HEAP_TIER));
    return *alias_cast<D3D12_RESOURCE_HEAP_TIER*>(&v);
}

inline D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER getDX12(PROGRAMMABLE_SAMPLE_POSITIONS_TIER v) noexcept {
    static_assert(sizeof(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER) == sizeof(PROGRAMMABLE_SAMPLE_POSITIONS_TIER));
    static_assert(alignof(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER) == alignof(PROGRAMMABLE_SAMPLE_POSITIONS_TIER));
    return *alias_cast<D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER*>(&v);
}

inline D3D12_VIEW_INSTANCING_TIER getDX12(VIEW_INSTANCING_TIER v) noexcept {
    static_assert(sizeof(D3D12_VIEW_INSTANCING_TIER) == sizeof(VIEW_INSTANCING_TIER));
    static_assert(alignof(D3D12_VIEW_INSTANCING_TIER) == alignof(VIEW_INSTANCING_TIER));
    return *alias_cast<D3D12_VIEW_INSTANCING_TIER*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS getDX12(const FEATURE_DATA_D3D12_OPTIONS& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS) == sizeof(FEATURE_DATA_D3D12_OPTIONS));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS) == alignof(FEATURE_DATA_D3D12_OPTIONS));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS1 getDX12(const FEATURE_DATA_D3D12_OPTIONS1& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1) == sizeof(FEATURE_DATA_D3D12_OPTIONS1));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS1) == alignof(FEATURE_DATA_D3D12_OPTIONS1));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS1*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS2 getDX12(const FEATURE_DATA_D3D12_OPTIONS2& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS2) == sizeof(FEATURE_DATA_D3D12_OPTIONS2));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS2) == alignof(FEATURE_DATA_D3D12_OPTIONS2));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS2*>(&v);
}

inline D3D12_FEATURE_DATA_ROOT_SIGNATURE getDX12(const FEATURE_DATA_ROOT_SIGNATURE& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE) == sizeof(FEATURE_DATA_ROOT_SIGNATURE));
    static_assert(alignof(D3D12_FEATURE_DATA_ROOT_SIGNATURE) == alignof(FEATURE_DATA_ROOT_SIGNATURE));
    return *alias_cast<const D3D12_FEATURE_DATA_ROOT_SIGNATURE*>(&v);
}

inline D3D12_FEATURE_DATA_ARCHITECTURE getDX12(const FEATURE_DATA_ARCHITECTURE& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_ARCHITECTURE) == sizeof(FEATURE_DATA_ARCHITECTURE));
    static_assert(alignof(D3D12_FEATURE_DATA_ARCHITECTURE) == alignof(FEATURE_DATA_ARCHITECTURE));
    return *alias_cast<const D3D12_FEATURE_DATA_ARCHITECTURE*>(&v);
}

inline D3D12_FEATURE_DATA_ARCHITECTURE1 getDX12(const FEATURE_DATA_ARCHITECTURE1& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_ARCHITECTURE1) == sizeof(FEATURE_DATA_ARCHITECTURE1));
    static_assert(alignof(D3D12_FEATURE_DATA_ARCHITECTURE1) == alignof(FEATURE_DATA_ARCHITECTURE1));
    return *alias_cast<const D3D12_FEATURE_DATA_ARCHITECTURE1*>(&v);
}

inline D3D12_FEATURE_DATA_FEATURE_LEVELS getDX12(const FEATURE_DATA_FEATURE_LEVELS& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS) == sizeof(FEATURE_DATA_FEATURE_LEVELS));
    static_assert(alignof(D3D12_FEATURE_DATA_FEATURE_LEVELS) == alignof(FEATURE_DATA_FEATURE_LEVELS));
    return *alias_cast<const D3D12_FEATURE_DATA_FEATURE_LEVELS*>(&v);
}

inline D3D12_FEATURE_DATA_SHADER_MODEL getDX12(const FEATURE_DATA_SHADER_MODEL& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_SHADER_MODEL) == sizeof(FEATURE_DATA_SHADER_MODEL));
    static_assert(alignof(D3D12_FEATURE_DATA_SHADER_MODEL) == alignof(FEATURE_DATA_SHADER_MODEL));
    return *alias_cast<const D3D12_FEATURE_DATA_SHADER_MODEL*>(&v);
}

inline D3D12_FEATURE_DATA_FORMAT_SUPPORT getDX12(const FEATURE_DATA_FORMAT_SUPPORT& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_FORMAT_SUPPORT) == sizeof(FEATURE_DATA_FORMAT_SUPPORT));
    static_assert(alignof(D3D12_FEATURE_DATA_FORMAT_SUPPORT) == alignof(FEATURE_DATA_FORMAT_SUPPORT));
    return *alias_cast<const D3D12_FEATURE_DATA_FORMAT_SUPPORT*>(&v);
}

inline D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS getDX12(const FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS) == sizeof(FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS));
    static_assert(alignof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS) == alignof(FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS));
    return *alias_cast<const D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS*>(&v);
}

inline D3D12_FEATURE_DATA_FORMAT_INFO getDX12(const FEATURE_DATA_FORMAT_INFO& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_FORMAT_INFO) == sizeof(FEATURE_DATA_FORMAT_INFO));
    static_assert(alignof(D3D12_FEATURE_DATA_FORMAT_INFO) == alignof(FEATURE_DATA_FORMAT_INFO));
    return *alias_cast<const D3D12_FEATURE_DATA_FORMAT_INFO*>(&v);
}

inline D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT getDX12(const FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT) == sizeof(FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT));
    static_assert(alignof(D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT) == alignof(FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT));
    return *alias_cast<const D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT*>(&v);
}

inline D3D12_SHADER_CACHE_SUPPORT_FLAGS getDX12(SHADER_CACHE_SUPPORT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_SHADER_CACHE_SUPPORT_FLAGS) == sizeof(SHADER_CACHE_SUPPORT_FLAGS));
    static_assert(alignof(D3D12_SHADER_CACHE_SUPPORT_FLAGS) == alignof(SHADER_CACHE_SUPPORT_FLAGS));
    return *alias_cast<D3D12_SHADER_CACHE_SUPPORT_FLAGS*>(&v);
}

inline D3D12_FEATURE_DATA_SHADER_CACHE getDX12(const FEATURE_DATA_SHADER_CACHE& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_SHADER_CACHE) == sizeof(FEATURE_DATA_SHADER_CACHE));
    static_assert(alignof(D3D12_FEATURE_DATA_SHADER_CACHE) == alignof(FEATURE_DATA_SHADER_CACHE));
    return *alias_cast<const D3D12_FEATURE_DATA_SHADER_CACHE*>(&v);
}

inline D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY getDX12(const FEATURE_DATA_COMMAND_QUEUE_PRIORITY& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY) == sizeof(FEATURE_DATA_COMMAND_QUEUE_PRIORITY));
    static_assert(alignof(D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY) == alignof(FEATURE_DATA_COMMAND_QUEUE_PRIORITY));
    return *alias_cast<const D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY*>(&v);
}

inline D3D12_COMMAND_LIST_SUPPORT_FLAGS getDX12(COMMAND_LIST_SUPPORT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_LIST_SUPPORT_FLAGS) == sizeof(COMMAND_LIST_SUPPORT_FLAGS));
    static_assert(alignof(D3D12_COMMAND_LIST_SUPPORT_FLAGS) == alignof(COMMAND_LIST_SUPPORT_FLAGS));
    return *alias_cast<D3D12_COMMAND_LIST_SUPPORT_FLAGS*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS3 getDX12(const FEATURE_DATA_D3D12_OPTIONS3& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS3) == sizeof(FEATURE_DATA_D3D12_OPTIONS3));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS3) == alignof(FEATURE_DATA_D3D12_OPTIONS3));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS3*>(&v);
}

inline D3D12_FEATURE_DATA_EXISTING_HEAPS getDX12(const FEATURE_DATA_EXISTING_HEAPS& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_EXISTING_HEAPS) == sizeof(FEATURE_DATA_EXISTING_HEAPS));
    static_assert(alignof(D3D12_FEATURE_DATA_EXISTING_HEAPS) == alignof(FEATURE_DATA_EXISTING_HEAPS));
    return *alias_cast<const D3D12_FEATURE_DATA_EXISTING_HEAPS*>(&v);
}

inline D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER getDX12(SHARED_RESOURCE_COMPATIBILITY_TIER v) noexcept {
    static_assert(sizeof(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER) == sizeof(SHARED_RESOURCE_COMPATIBILITY_TIER));
    static_assert(alignof(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER) == alignof(SHARED_RESOURCE_COMPATIBILITY_TIER));
    return *alias_cast<D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS4 getDX12(const FEATURE_DATA_D3D12_OPTIONS4& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS4) == sizeof(FEATURE_DATA_D3D12_OPTIONS4));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS4) == alignof(FEATURE_DATA_D3D12_OPTIONS4));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS4*>(&v);
}

inline D3D12_HEAP_SERIALIZATION_TIER getDX12(HEAP_SERIALIZATION_TIER v) noexcept {
    static_assert(sizeof(D3D12_HEAP_SERIALIZATION_TIER) == sizeof(HEAP_SERIALIZATION_TIER));
    static_assert(alignof(D3D12_HEAP_SERIALIZATION_TIER) == alignof(HEAP_SERIALIZATION_TIER));
    return *alias_cast<D3D12_HEAP_SERIALIZATION_TIER*>(&v);
}

inline D3D12_FEATURE_DATA_SERIALIZATION getDX12(const FEATURE_DATA_SERIALIZATION& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_SERIALIZATION) == sizeof(FEATURE_DATA_SERIALIZATION));
    static_assert(alignof(D3D12_FEATURE_DATA_SERIALIZATION) == alignof(FEATURE_DATA_SERIALIZATION));
    return *alias_cast<const D3D12_FEATURE_DATA_SERIALIZATION*>(&v);
}

inline D3D12_FEATURE_DATA_CROSS_NODE getDX12(const FEATURE_DATA_CROSS_NODE& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_CROSS_NODE) == sizeof(FEATURE_DATA_CROSS_NODE));
    static_assert(alignof(D3D12_FEATURE_DATA_CROSS_NODE) == alignof(FEATURE_DATA_CROSS_NODE));
    return *alias_cast<const D3D12_FEATURE_DATA_CROSS_NODE*>(&v);
}

inline D3D12_RENDER_PASS_TIER getDX12(RENDER_PASS_TIER v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_TIER) == sizeof(RENDER_PASS_TIER));
    static_assert(alignof(D3D12_RENDER_PASS_TIER) == alignof(RENDER_PASS_TIER));
    return *alias_cast<D3D12_RENDER_PASS_TIER*>(&v);
}

inline D3D12_RAYTRACING_TIER getDX12(RAYTRACING_TIER v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_TIER) == sizeof(RAYTRACING_TIER));
    static_assert(alignof(D3D12_RAYTRACING_TIER) == alignof(RAYTRACING_TIER));
    return *alias_cast<D3D12_RAYTRACING_TIER*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS5 getDX12(const FEATURE_DATA_D3D12_OPTIONS5& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5) == sizeof(FEATURE_DATA_D3D12_OPTIONS5));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS5) == alignof(FEATURE_DATA_D3D12_OPTIONS5));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS5*>(&v);
}

inline D3D12_VARIABLE_SHADING_RATE_TIER getDX12(VARIABLE_SHADING_RATE_TIER v) noexcept {
    static_assert(sizeof(D3D12_VARIABLE_SHADING_RATE_TIER) == sizeof(VARIABLE_SHADING_RATE_TIER));
    static_assert(alignof(D3D12_VARIABLE_SHADING_RATE_TIER) == alignof(VARIABLE_SHADING_RATE_TIER));
    return *alias_cast<D3D12_VARIABLE_SHADING_RATE_TIER*>(&v);
}

inline D3D12_FEATURE_DATA_D3D12_OPTIONS6 getDX12(const FEATURE_DATA_D3D12_OPTIONS6& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6) == sizeof(FEATURE_DATA_D3D12_OPTIONS6));
    static_assert(alignof(D3D12_FEATURE_DATA_D3D12_OPTIONS6) == alignof(FEATURE_DATA_D3D12_OPTIONS6));
    return *alias_cast<const D3D12_FEATURE_DATA_D3D12_OPTIONS6*>(&v);
}

inline D3D12_FEATURE_DATA_QUERY_META_COMMAND getDX12(const FEATURE_DATA_QUERY_META_COMMAND& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_QUERY_META_COMMAND) == sizeof(FEATURE_DATA_QUERY_META_COMMAND));
    static_assert(alignof(D3D12_FEATURE_DATA_QUERY_META_COMMAND) == alignof(FEATURE_DATA_QUERY_META_COMMAND));
    return *alias_cast<const D3D12_FEATURE_DATA_QUERY_META_COMMAND*>(&v);
}

inline D3D12_RESOURCE_ALLOCATION_INFO getDX12(const RESOURCE_ALLOCATION_INFO& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_ALLOCATION_INFO) == sizeof(RESOURCE_ALLOCATION_INFO));
    static_assert(alignof(D3D12_RESOURCE_ALLOCATION_INFO) == alignof(RESOURCE_ALLOCATION_INFO));
    return *alias_cast<const D3D12_RESOURCE_ALLOCATION_INFO*>(&v);
}

inline D3D12_RESOURCE_ALLOCATION_INFO1 getDX12(const RESOURCE_ALLOCATION_INFO1& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_ALLOCATION_INFO1) == sizeof(RESOURCE_ALLOCATION_INFO1));
    static_assert(alignof(D3D12_RESOURCE_ALLOCATION_INFO1) == alignof(RESOURCE_ALLOCATION_INFO1));
    return *alias_cast<const D3D12_RESOURCE_ALLOCATION_INFO1*>(&v);
}

inline D3D12_HEAP_TYPE getDX12(HEAP_TYPE v) noexcept {
    static_assert(sizeof(D3D12_HEAP_TYPE) == sizeof(HEAP_TYPE));
    static_assert(alignof(D3D12_HEAP_TYPE) == alignof(HEAP_TYPE));
    return *alias_cast<D3D12_HEAP_TYPE*>(&v);
}

inline D3D12_CPU_PAGE_PROPERTY getDX12(CPU_PAGE_PROPERTY v) noexcept {
    static_assert(sizeof(D3D12_CPU_PAGE_PROPERTY) == sizeof(CPU_PAGE_PROPERTY));
    static_assert(alignof(D3D12_CPU_PAGE_PROPERTY) == alignof(CPU_PAGE_PROPERTY));
    return *alias_cast<D3D12_CPU_PAGE_PROPERTY*>(&v);
}

inline D3D12_MEMORY_POOL getDX12(MEMORY_POOL v) noexcept {
    static_assert(sizeof(D3D12_MEMORY_POOL) == sizeof(MEMORY_POOL));
    static_assert(alignof(D3D12_MEMORY_POOL) == alignof(MEMORY_POOL));
    return *alias_cast<D3D12_MEMORY_POOL*>(&v);
}

inline D3D12_HEAP_PROPERTIES getDX12(const HEAP_PROPERTIES& v) noexcept {
    static_assert(sizeof(D3D12_HEAP_PROPERTIES) == sizeof(HEAP_PROPERTIES));
    static_assert(alignof(D3D12_HEAP_PROPERTIES) == alignof(HEAP_PROPERTIES));
    return *alias_cast<const D3D12_HEAP_PROPERTIES*>(&v);
}

inline D3D12_HEAP_FLAGS getDX12(HEAP_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_HEAP_FLAGS) == sizeof(HEAP_FLAGS));
    static_assert(alignof(D3D12_HEAP_FLAGS) == alignof(HEAP_FLAGS));
    return *alias_cast<D3D12_HEAP_FLAGS*>(&v);
}

inline D3D12_HEAP_DESC getDX12(const HEAP_DESC& v) noexcept {
    static_assert(sizeof(D3D12_HEAP_DESC) == sizeof(HEAP_DESC));
    static_assert(alignof(D3D12_HEAP_DESC) == alignof(HEAP_DESC));
    return *alias_cast<const D3D12_HEAP_DESC*>(&v);
}

inline D3D12_RESOURCE_DIMENSION getDX12(RESOURCE_DIMENSION v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_DIMENSION) == sizeof(RESOURCE_DIMENSION));
    static_assert(alignof(D3D12_RESOURCE_DIMENSION) == alignof(RESOURCE_DIMENSION));
    return *alias_cast<D3D12_RESOURCE_DIMENSION*>(&v);
}

inline D3D12_TEXTURE_LAYOUT getDX12(TEXTURE_LAYOUT v) noexcept {
    static_assert(sizeof(D3D12_TEXTURE_LAYOUT) == sizeof(TEXTURE_LAYOUT));
    static_assert(alignof(D3D12_TEXTURE_LAYOUT) == alignof(TEXTURE_LAYOUT));
    return *alias_cast<D3D12_TEXTURE_LAYOUT*>(&v);
}

inline D3D12_RESOURCE_FLAGS getDX12(RESOURCE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_FLAGS) == sizeof(RESOURCE_FLAGS));
    static_assert(alignof(D3D12_RESOURCE_FLAGS) == alignof(RESOURCE_FLAGS));
    return *alias_cast<D3D12_RESOURCE_FLAGS*>(&v);
}

inline D3D12_RESOURCE_DESC getDX12(const RESOURCE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_DESC) == sizeof(RESOURCE_DESC));
    static_assert(alignof(D3D12_RESOURCE_DESC) == alignof(RESOURCE_DESC));
    return *alias_cast<const D3D12_RESOURCE_DESC*>(&v);
}

inline D3D12_DEPTH_STENCIL_VALUE getDX12(const DEPTH_STENCIL_VALUE& v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_STENCIL_VALUE) == sizeof(DEPTH_STENCIL_VALUE));
    static_assert(alignof(D3D12_DEPTH_STENCIL_VALUE) == alignof(DEPTH_STENCIL_VALUE));
    return *alias_cast<const D3D12_DEPTH_STENCIL_VALUE*>(&v);
}

inline D3D12_CLEAR_VALUE getDX12(const CLEAR_VALUE& v) noexcept {
    static_assert(sizeof(D3D12_CLEAR_VALUE) == sizeof(CLEAR_VALUE));
    static_assert(alignof(D3D12_CLEAR_VALUE) == alignof(CLEAR_VALUE));
    return *alias_cast<const D3D12_CLEAR_VALUE*>(&v);
}

inline D3D12_RANGE getDX12(const RANGE& v) noexcept {
    static_assert(sizeof(D3D12_RANGE) == sizeof(RANGE));
    static_assert(alignof(D3D12_RANGE) == alignof(RANGE));
    return *alias_cast<const D3D12_RANGE*>(&v);
}

inline D3D12_RANGE_UINT64 getDX12(const RANGE_UINT64& v) noexcept {
    static_assert(sizeof(D3D12_RANGE_UINT64) == sizeof(RANGE_UINT64));
    static_assert(alignof(D3D12_RANGE_UINT64) == alignof(RANGE_UINT64));
    return *alias_cast<const D3D12_RANGE_UINT64*>(&v);
}

inline D3D12_SUBRESOURCE_RANGE_UINT64 getDX12(const SUBRESOURCE_RANGE_UINT64& v) noexcept {
    static_assert(sizeof(D3D12_SUBRESOURCE_RANGE_UINT64) == sizeof(SUBRESOURCE_RANGE_UINT64));
    static_assert(alignof(D3D12_SUBRESOURCE_RANGE_UINT64) == alignof(SUBRESOURCE_RANGE_UINT64));
    return *alias_cast<const D3D12_SUBRESOURCE_RANGE_UINT64*>(&v);
}

inline D3D12_SUBRESOURCE_INFO getDX12(const SUBRESOURCE_INFO& v) noexcept {
    static_assert(sizeof(D3D12_SUBRESOURCE_INFO) == sizeof(SUBRESOURCE_INFO));
    static_assert(alignof(D3D12_SUBRESOURCE_INFO) == alignof(SUBRESOURCE_INFO));
    return *alias_cast<const D3D12_SUBRESOURCE_INFO*>(&v);
}

inline D3D12_TILED_RESOURCE_COORDINATE getDX12(const TILED_RESOURCE_COORDINATE& v) noexcept {
    static_assert(sizeof(D3D12_TILED_RESOURCE_COORDINATE) == sizeof(TILED_RESOURCE_COORDINATE));
    static_assert(alignof(D3D12_TILED_RESOURCE_COORDINATE) == alignof(TILED_RESOURCE_COORDINATE));
    return *alias_cast<const D3D12_TILED_RESOURCE_COORDINATE*>(&v);
}

inline D3D12_TILE_REGION_SIZE getDX12(const TILE_REGION_SIZE& v) noexcept {
    static_assert(sizeof(D3D12_TILE_REGION_SIZE) == sizeof(TILE_REGION_SIZE));
    static_assert(alignof(D3D12_TILE_REGION_SIZE) == alignof(TILE_REGION_SIZE));
    return *alias_cast<const D3D12_TILE_REGION_SIZE*>(&v);
}

inline D3D12_TILE_RANGE_FLAGS getDX12(TILE_RANGE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_TILE_RANGE_FLAGS) == sizeof(TILE_RANGE_FLAGS));
    static_assert(alignof(D3D12_TILE_RANGE_FLAGS) == alignof(TILE_RANGE_FLAGS));
    return *alias_cast<D3D12_TILE_RANGE_FLAGS*>(&v);
}

inline D3D12_SUBRESOURCE_TILING getDX12(const SUBRESOURCE_TILING& v) noexcept {
    static_assert(sizeof(D3D12_SUBRESOURCE_TILING) == sizeof(SUBRESOURCE_TILING));
    static_assert(alignof(D3D12_SUBRESOURCE_TILING) == alignof(SUBRESOURCE_TILING));
    return *alias_cast<const D3D12_SUBRESOURCE_TILING*>(&v);
}

inline D3D12_TILE_SHAPE getDX12(const TILE_SHAPE& v) noexcept {
    static_assert(sizeof(D3D12_TILE_SHAPE) == sizeof(TILE_SHAPE));
    static_assert(alignof(D3D12_TILE_SHAPE) == alignof(TILE_SHAPE));
    return *alias_cast<const D3D12_TILE_SHAPE*>(&v);
}

inline D3D12_PACKED_MIP_INFO getDX12(const PACKED_MIP_INFO& v) noexcept {
    static_assert(sizeof(D3D12_PACKED_MIP_INFO) == sizeof(PACKED_MIP_INFO));
    static_assert(alignof(D3D12_PACKED_MIP_INFO) == alignof(PACKED_MIP_INFO));
    return *alias_cast<const D3D12_PACKED_MIP_INFO*>(&v);
}

inline D3D12_TILE_MAPPING_FLAGS getDX12(TILE_MAPPING_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_TILE_MAPPING_FLAGS) == sizeof(TILE_MAPPING_FLAGS));
    static_assert(alignof(D3D12_TILE_MAPPING_FLAGS) == alignof(TILE_MAPPING_FLAGS));
    return *alias_cast<D3D12_TILE_MAPPING_FLAGS*>(&v);
}

inline D3D12_TILE_COPY_FLAGS getDX12(TILE_COPY_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_TILE_COPY_FLAGS) == sizeof(TILE_COPY_FLAGS));
    static_assert(alignof(D3D12_TILE_COPY_FLAGS) == alignof(TILE_COPY_FLAGS));
    return *alias_cast<D3D12_TILE_COPY_FLAGS*>(&v);
}

inline D3D12_RESOURCE_STATES getDX12(RESOURCE_STATES v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_STATES) == sizeof(RESOURCE_STATES));
    static_assert(alignof(D3D12_RESOURCE_STATES) == alignof(RESOURCE_STATES));
    return *alias_cast<D3D12_RESOURCE_STATES*>(&v);
}

inline D3D12_RESOURCE_BARRIER_TYPE getDX12(RESOURCE_BARRIER_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_BARRIER_TYPE) == sizeof(RESOURCE_BARRIER_TYPE));
    static_assert(alignof(D3D12_RESOURCE_BARRIER_TYPE) == alignof(RESOURCE_BARRIER_TYPE));
    return *alias_cast<D3D12_RESOURCE_BARRIER_TYPE*>(&v);
}

inline D3D12_RESOURCE_TRANSITION_BARRIER getDX12(const RESOURCE_TRANSITION_BARRIER& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_TRANSITION_BARRIER) == sizeof(RESOURCE_TRANSITION_BARRIER));
    static_assert(alignof(D3D12_RESOURCE_TRANSITION_BARRIER) == alignof(RESOURCE_TRANSITION_BARRIER));
    return *alias_cast<const D3D12_RESOURCE_TRANSITION_BARRIER*>(&v);
}

inline D3D12_RESOURCE_ALIASING_BARRIER getDX12(const RESOURCE_ALIASING_BARRIER& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_ALIASING_BARRIER) == sizeof(RESOURCE_ALIASING_BARRIER));
    static_assert(alignof(D3D12_RESOURCE_ALIASING_BARRIER) == alignof(RESOURCE_ALIASING_BARRIER));
    return *alias_cast<const D3D12_RESOURCE_ALIASING_BARRIER*>(&v);
}

inline D3D12_RESOURCE_UAV_BARRIER getDX12(const RESOURCE_UAV_BARRIER& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_UAV_BARRIER) == sizeof(RESOURCE_UAV_BARRIER));
    static_assert(alignof(D3D12_RESOURCE_UAV_BARRIER) == alignof(RESOURCE_UAV_BARRIER));
    return *alias_cast<const D3D12_RESOURCE_UAV_BARRIER*>(&v);
}

inline D3D12_RESOURCE_BARRIER_FLAGS getDX12(RESOURCE_BARRIER_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_BARRIER_FLAGS) == sizeof(RESOURCE_BARRIER_FLAGS));
    static_assert(alignof(D3D12_RESOURCE_BARRIER_FLAGS) == alignof(RESOURCE_BARRIER_FLAGS));
    return *alias_cast<D3D12_RESOURCE_BARRIER_FLAGS*>(&v);
}

inline D3D12_RESOURCE_BARRIER getDX12(const RESOURCE_BARRIER& v) noexcept {
    static_assert(sizeof(D3D12_RESOURCE_BARRIER) == sizeof(RESOURCE_BARRIER));
    static_assert(alignof(D3D12_RESOURCE_BARRIER) == alignof(RESOURCE_BARRIER));
    return *alias_cast<const D3D12_RESOURCE_BARRIER*>(&v);
}

inline D3D12_SUBRESOURCE_FOOTPRINT getDX12(const SUBRESOURCE_FOOTPRINT& v) noexcept {
    static_assert(sizeof(D3D12_SUBRESOURCE_FOOTPRINT) == sizeof(SUBRESOURCE_FOOTPRINT));
    static_assert(alignof(D3D12_SUBRESOURCE_FOOTPRINT) == alignof(SUBRESOURCE_FOOTPRINT));
    return *alias_cast<const D3D12_SUBRESOURCE_FOOTPRINT*>(&v);
}

inline D3D12_PLACED_SUBRESOURCE_FOOTPRINT getDX12(const PLACED_SUBRESOURCE_FOOTPRINT& v) noexcept {
    static_assert(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) == sizeof(PLACED_SUBRESOURCE_FOOTPRINT));
    static_assert(alignof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) == alignof(PLACED_SUBRESOURCE_FOOTPRINT));
    return *alias_cast<const D3D12_PLACED_SUBRESOURCE_FOOTPRINT*>(&v);
}

inline D3D12_TEXTURE_COPY_TYPE getDX12(TEXTURE_COPY_TYPE v) noexcept {
    static_assert(sizeof(D3D12_TEXTURE_COPY_TYPE) == sizeof(TEXTURE_COPY_TYPE));
    static_assert(alignof(D3D12_TEXTURE_COPY_TYPE) == alignof(TEXTURE_COPY_TYPE));
    return *alias_cast<D3D12_TEXTURE_COPY_TYPE*>(&v);
}

inline D3D12_TEXTURE_COPY_LOCATION getDX12(const TEXTURE_COPY_LOCATION& v) noexcept {
    static_assert(sizeof(D3D12_TEXTURE_COPY_LOCATION) == sizeof(TEXTURE_COPY_LOCATION));
    static_assert(alignof(D3D12_TEXTURE_COPY_LOCATION) == alignof(TEXTURE_COPY_LOCATION));
    return *alias_cast<const D3D12_TEXTURE_COPY_LOCATION*>(&v);
}

inline D3D12_RESOLVE_MODE getDX12(RESOLVE_MODE v) noexcept {
    static_assert(sizeof(D3D12_RESOLVE_MODE) == sizeof(RESOLVE_MODE));
    static_assert(alignof(D3D12_RESOLVE_MODE) == alignof(RESOLVE_MODE));
    return *alias_cast<D3D12_RESOLVE_MODE*>(&v);
}

inline D3D12_SAMPLE_POSITION getDX12(const SAMPLE_POSITION& v) noexcept {
    static_assert(sizeof(D3D12_SAMPLE_POSITION) == sizeof(SAMPLE_POSITION));
    static_assert(alignof(D3D12_SAMPLE_POSITION) == alignof(SAMPLE_POSITION));
    return *alias_cast<const D3D12_SAMPLE_POSITION*>(&v);
}

inline D3D12_VIEW_INSTANCE_LOCATION getDX12(const VIEW_INSTANCE_LOCATION& v) noexcept {
    static_assert(sizeof(D3D12_VIEW_INSTANCE_LOCATION) == sizeof(VIEW_INSTANCE_LOCATION));
    static_assert(alignof(D3D12_VIEW_INSTANCE_LOCATION) == alignof(VIEW_INSTANCE_LOCATION));
    return *alias_cast<const D3D12_VIEW_INSTANCE_LOCATION*>(&v);
}

inline D3D12_VIEW_INSTANCING_FLAGS getDX12(VIEW_INSTANCING_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_VIEW_INSTANCING_FLAGS) == sizeof(VIEW_INSTANCING_FLAGS));
    static_assert(alignof(D3D12_VIEW_INSTANCING_FLAGS) == alignof(VIEW_INSTANCING_FLAGS));
    return *alias_cast<D3D12_VIEW_INSTANCING_FLAGS*>(&v);
}

inline D3D12_VIEW_INSTANCING_DESC getDX12(const VIEW_INSTANCING_DESC& v) noexcept {
    static_assert(sizeof(D3D12_VIEW_INSTANCING_DESC) == sizeof(VIEW_INSTANCING_DESC));
    static_assert(alignof(D3D12_VIEW_INSTANCING_DESC) == alignof(VIEW_INSTANCING_DESC));
    return *alias_cast<const D3D12_VIEW_INSTANCING_DESC*>(&v);
}

inline D3D12_SHADER_COMPONENT_MAPPING getDX12(SHADER_COMPONENT_MAPPING v) noexcept {
    static_assert(sizeof(D3D12_SHADER_COMPONENT_MAPPING) == sizeof(SHADER_COMPONENT_MAPPING));
    static_assert(alignof(D3D12_SHADER_COMPONENT_MAPPING) == alignof(SHADER_COMPONENT_MAPPING));
    return *alias_cast<D3D12_SHADER_COMPONENT_MAPPING*>(&v);
}

inline D3D12_BUFFER_SRV_FLAGS getDX12(BUFFER_SRV_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_BUFFER_SRV_FLAGS) == sizeof(BUFFER_SRV_FLAGS));
    static_assert(alignof(D3D12_BUFFER_SRV_FLAGS) == alignof(BUFFER_SRV_FLAGS));
    return *alias_cast<D3D12_BUFFER_SRV_FLAGS*>(&v);
}

inline D3D12_BUFFER_SRV getDX12(const BUFFER_SRV& v) noexcept {
    static_assert(sizeof(D3D12_BUFFER_SRV) == sizeof(BUFFER_SRV));
    static_assert(alignof(D3D12_BUFFER_SRV) == alignof(BUFFER_SRV));
    return *alias_cast<const D3D12_BUFFER_SRV*>(&v);
}

inline D3D12_TEX1D_SRV getDX12(const TEX1D_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_SRV) == sizeof(TEX1D_SRV));
    static_assert(alignof(D3D12_TEX1D_SRV) == alignof(TEX1D_SRV));
    return *alias_cast<const D3D12_TEX1D_SRV*>(&v);
}

inline D3D12_TEX1D_ARRAY_SRV getDX12(const TEX1D_ARRAY_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_ARRAY_SRV) == sizeof(TEX1D_ARRAY_SRV));
    static_assert(alignof(D3D12_TEX1D_ARRAY_SRV) == alignof(TEX1D_ARRAY_SRV));
    return *alias_cast<const D3D12_TEX1D_ARRAY_SRV*>(&v);
}

inline D3D12_TEX2D_SRV getDX12(const TEX2D_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_SRV) == sizeof(TEX2D_SRV));
    static_assert(alignof(D3D12_TEX2D_SRV) == alignof(TEX2D_SRV));
    return *alias_cast<const D3D12_TEX2D_SRV*>(&v);
}

inline D3D12_TEX2D_ARRAY_SRV getDX12(const TEX2D_ARRAY_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_ARRAY_SRV) == sizeof(TEX2D_ARRAY_SRV));
    static_assert(alignof(D3D12_TEX2D_ARRAY_SRV) == alignof(TEX2D_ARRAY_SRV));
    return *alias_cast<const D3D12_TEX2D_ARRAY_SRV*>(&v);
}

inline D3D12_TEX3D_SRV getDX12(const TEX3D_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX3D_SRV) == sizeof(TEX3D_SRV));
    static_assert(alignof(D3D12_TEX3D_SRV) == alignof(TEX3D_SRV));
    return *alias_cast<const D3D12_TEX3D_SRV*>(&v);
}

inline D3D12_TEXCUBE_SRV getDX12(const TEXCUBE_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEXCUBE_SRV) == sizeof(TEXCUBE_SRV));
    static_assert(alignof(D3D12_TEXCUBE_SRV) == alignof(TEXCUBE_SRV));
    return *alias_cast<const D3D12_TEXCUBE_SRV*>(&v);
}

inline D3D12_TEXCUBE_ARRAY_SRV getDX12(const TEXCUBE_ARRAY_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEXCUBE_ARRAY_SRV) == sizeof(TEXCUBE_ARRAY_SRV));
    static_assert(alignof(D3D12_TEXCUBE_ARRAY_SRV) == alignof(TEXCUBE_ARRAY_SRV));
    return *alias_cast<const D3D12_TEXCUBE_ARRAY_SRV*>(&v);
}

inline D3D12_TEX2DMS_SRV getDX12(const TEX2DMS_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_SRV) == sizeof(TEX2DMS_SRV));
    static_assert(alignof(D3D12_TEX2DMS_SRV) == alignof(TEX2DMS_SRV));
    return *alias_cast<const D3D12_TEX2DMS_SRV*>(&v);
}

inline D3D12_TEX2DMS_ARRAY_SRV getDX12(const TEX2DMS_ARRAY_SRV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_ARRAY_SRV) == sizeof(TEX2DMS_ARRAY_SRV));
    static_assert(alignof(D3D12_TEX2DMS_ARRAY_SRV) == alignof(TEX2DMS_ARRAY_SRV));
    return *alias_cast<const D3D12_TEX2DMS_ARRAY_SRV*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_SRV& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_SRV));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_SRV));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV*>(&v);
}

inline D3D12_SRV_DIMENSION getDX12(SRV_DIMENSION v) noexcept {
    static_assert(sizeof(D3D12_SRV_DIMENSION) == sizeof(SRV_DIMENSION));
    static_assert(alignof(D3D12_SRV_DIMENSION) == alignof(SRV_DIMENSION));
    return *alias_cast<D3D12_SRV_DIMENSION*>(&v);
}

inline D3D12_SHADER_RESOURCE_VIEW_DESC getDX12(const SHADER_RESOURCE_VIEW_DESC& v) noexcept {
    static_assert(sizeof(D3D12_SHADER_RESOURCE_VIEW_DESC) == sizeof(SHADER_RESOURCE_VIEW_DESC));
    static_assert(alignof(D3D12_SHADER_RESOURCE_VIEW_DESC) == alignof(SHADER_RESOURCE_VIEW_DESC));
    return *alias_cast<const D3D12_SHADER_RESOURCE_VIEW_DESC*>(&v);
}

inline D3D12_CONSTANT_BUFFER_VIEW_DESC getDX12(const CONSTANT_BUFFER_VIEW_DESC& v) noexcept {
    static_assert(sizeof(D3D12_CONSTANT_BUFFER_VIEW_DESC) == sizeof(CONSTANT_BUFFER_VIEW_DESC));
    static_assert(alignof(D3D12_CONSTANT_BUFFER_VIEW_DESC) == alignof(CONSTANT_BUFFER_VIEW_DESC));
    return *alias_cast<const D3D12_CONSTANT_BUFFER_VIEW_DESC*>(&v);
}

inline D3D12_FILTER getDX12(FILTER v) noexcept {
    static_assert(sizeof(D3D12_FILTER) == sizeof(FILTER));
    static_assert(alignof(D3D12_FILTER) == alignof(FILTER));
    return *alias_cast<D3D12_FILTER*>(&v);
}

inline D3D12_FILTER_TYPE getDX12(FILTER_TYPE v) noexcept {
    static_assert(sizeof(D3D12_FILTER_TYPE) == sizeof(FILTER_TYPE));
    static_assert(alignof(D3D12_FILTER_TYPE) == alignof(FILTER_TYPE));
    return *alias_cast<D3D12_FILTER_TYPE*>(&v);
}

inline D3D12_FILTER_REDUCTION_TYPE getDX12(FILTER_REDUCTION_TYPE v) noexcept {
    static_assert(sizeof(D3D12_FILTER_REDUCTION_TYPE) == sizeof(FILTER_REDUCTION_TYPE));
    static_assert(alignof(D3D12_FILTER_REDUCTION_TYPE) == alignof(FILTER_REDUCTION_TYPE));
    return *alias_cast<D3D12_FILTER_REDUCTION_TYPE*>(&v);
}

inline D3D12_TEXTURE_ADDRESS_MODE getDX12(TEXTURE_ADDRESS_MODE v) noexcept {
    static_assert(sizeof(D3D12_TEXTURE_ADDRESS_MODE) == sizeof(TEXTURE_ADDRESS_MODE));
    static_assert(alignof(D3D12_TEXTURE_ADDRESS_MODE) == alignof(TEXTURE_ADDRESS_MODE));
    return *alias_cast<D3D12_TEXTURE_ADDRESS_MODE*>(&v);
}

inline D3D12_SAMPLER_DESC getDX12(const SAMPLER_DESC& v) noexcept {
    static_assert(sizeof(D3D12_SAMPLER_DESC) == sizeof(SAMPLER_DESC));
    static_assert(alignof(D3D12_SAMPLER_DESC) == alignof(SAMPLER_DESC));
    return *alias_cast<const D3D12_SAMPLER_DESC*>(&v);
}

inline D3D12_BUFFER_UAV_FLAGS getDX12(BUFFER_UAV_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_BUFFER_UAV_FLAGS) == sizeof(BUFFER_UAV_FLAGS));
    static_assert(alignof(D3D12_BUFFER_UAV_FLAGS) == alignof(BUFFER_UAV_FLAGS));
    return *alias_cast<D3D12_BUFFER_UAV_FLAGS*>(&v);
}

inline D3D12_BUFFER_UAV getDX12(const BUFFER_UAV& v) noexcept {
    static_assert(sizeof(D3D12_BUFFER_UAV) == sizeof(BUFFER_UAV));
    static_assert(alignof(D3D12_BUFFER_UAV) == alignof(BUFFER_UAV));
    return *alias_cast<const D3D12_BUFFER_UAV*>(&v);
}

inline D3D12_TEX1D_UAV getDX12(const TEX1D_UAV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_UAV) == sizeof(TEX1D_UAV));
    static_assert(alignof(D3D12_TEX1D_UAV) == alignof(TEX1D_UAV));
    return *alias_cast<const D3D12_TEX1D_UAV*>(&v);
}

inline D3D12_TEX1D_ARRAY_UAV getDX12(const TEX1D_ARRAY_UAV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_ARRAY_UAV) == sizeof(TEX1D_ARRAY_UAV));
    static_assert(alignof(D3D12_TEX1D_ARRAY_UAV) == alignof(TEX1D_ARRAY_UAV));
    return *alias_cast<const D3D12_TEX1D_ARRAY_UAV*>(&v);
}

inline D3D12_TEX2D_UAV getDX12(const TEX2D_UAV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_UAV) == sizeof(TEX2D_UAV));
    static_assert(alignof(D3D12_TEX2D_UAV) == alignof(TEX2D_UAV));
    return *alias_cast<const D3D12_TEX2D_UAV*>(&v);
}

inline D3D12_TEX2D_ARRAY_UAV getDX12(const TEX2D_ARRAY_UAV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_ARRAY_UAV) == sizeof(TEX2D_ARRAY_UAV));
    static_assert(alignof(D3D12_TEX2D_ARRAY_UAV) == alignof(TEX2D_ARRAY_UAV));
    return *alias_cast<const D3D12_TEX2D_ARRAY_UAV*>(&v);
}

inline D3D12_TEX3D_UAV getDX12(const TEX3D_UAV& v) noexcept {
    static_assert(sizeof(D3D12_TEX3D_UAV) == sizeof(TEX3D_UAV));
    static_assert(alignof(D3D12_TEX3D_UAV) == alignof(TEX3D_UAV));
    return *alias_cast<const D3D12_TEX3D_UAV*>(&v);
}

inline D3D12_UAV_DIMENSION getDX12(UAV_DIMENSION v) noexcept {
    static_assert(sizeof(D3D12_UAV_DIMENSION) == sizeof(UAV_DIMENSION));
    static_assert(alignof(D3D12_UAV_DIMENSION) == alignof(UAV_DIMENSION));
    return *alias_cast<D3D12_UAV_DIMENSION*>(&v);
}

inline D3D12_UNORDERED_ACCESS_VIEW_DESC getDX12(const UNORDERED_ACCESS_VIEW_DESC& v) noexcept {
    static_assert(sizeof(D3D12_UNORDERED_ACCESS_VIEW_DESC) == sizeof(UNORDERED_ACCESS_VIEW_DESC));
    static_assert(alignof(D3D12_UNORDERED_ACCESS_VIEW_DESC) == alignof(UNORDERED_ACCESS_VIEW_DESC));
    return *alias_cast<const D3D12_UNORDERED_ACCESS_VIEW_DESC*>(&v);
}

inline D3D12_BUFFER_RTV getDX12(const BUFFER_RTV& v) noexcept {
    static_assert(sizeof(D3D12_BUFFER_RTV) == sizeof(BUFFER_RTV));
    static_assert(alignof(D3D12_BUFFER_RTV) == alignof(BUFFER_RTV));
    return *alias_cast<const D3D12_BUFFER_RTV*>(&v);
}

inline D3D12_TEX1D_RTV getDX12(const TEX1D_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_RTV) == sizeof(TEX1D_RTV));
    static_assert(alignof(D3D12_TEX1D_RTV) == alignof(TEX1D_RTV));
    return *alias_cast<const D3D12_TEX1D_RTV*>(&v);
}

inline D3D12_TEX1D_ARRAY_RTV getDX12(const TEX1D_ARRAY_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_ARRAY_RTV) == sizeof(TEX1D_ARRAY_RTV));
    static_assert(alignof(D3D12_TEX1D_ARRAY_RTV) == alignof(TEX1D_ARRAY_RTV));
    return *alias_cast<const D3D12_TEX1D_ARRAY_RTV*>(&v);
}

inline D3D12_TEX2D_RTV getDX12(const TEX2D_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_RTV) == sizeof(TEX2D_RTV));
    static_assert(alignof(D3D12_TEX2D_RTV) == alignof(TEX2D_RTV));
    return *alias_cast<const D3D12_TEX2D_RTV*>(&v);
}

inline D3D12_TEX2DMS_RTV getDX12(const TEX2DMS_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_RTV) == sizeof(TEX2DMS_RTV));
    static_assert(alignof(D3D12_TEX2DMS_RTV) == alignof(TEX2DMS_RTV));
    return *alias_cast<const D3D12_TEX2DMS_RTV*>(&v);
}

inline D3D12_TEX2D_ARRAY_RTV getDX12(const TEX2D_ARRAY_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_ARRAY_RTV) == sizeof(TEX2D_ARRAY_RTV));
    static_assert(alignof(D3D12_TEX2D_ARRAY_RTV) == alignof(TEX2D_ARRAY_RTV));
    return *alias_cast<const D3D12_TEX2D_ARRAY_RTV*>(&v);
}

inline D3D12_TEX2DMS_ARRAY_RTV getDX12(const TEX2DMS_ARRAY_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_ARRAY_RTV) == sizeof(TEX2DMS_ARRAY_RTV));
    static_assert(alignof(D3D12_TEX2DMS_ARRAY_RTV) == alignof(TEX2DMS_ARRAY_RTV));
    return *alias_cast<const D3D12_TEX2DMS_ARRAY_RTV*>(&v);
}

inline D3D12_TEX3D_RTV getDX12(const TEX3D_RTV& v) noexcept {
    static_assert(sizeof(D3D12_TEX3D_RTV) == sizeof(TEX3D_RTV));
    static_assert(alignof(D3D12_TEX3D_RTV) == alignof(TEX3D_RTV));
    return *alias_cast<const D3D12_TEX3D_RTV*>(&v);
}

inline D3D12_RTV_DIMENSION getDX12(RTV_DIMENSION v) noexcept {
    static_assert(sizeof(D3D12_RTV_DIMENSION) == sizeof(RTV_DIMENSION));
    static_assert(alignof(D3D12_RTV_DIMENSION) == alignof(RTV_DIMENSION));
    return *alias_cast<D3D12_RTV_DIMENSION*>(&v);
}

inline D3D12_RENDER_TARGET_VIEW_DESC getDX12(const RENDER_TARGET_VIEW_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_TARGET_VIEW_DESC) == sizeof(RENDER_TARGET_VIEW_DESC));
    static_assert(alignof(D3D12_RENDER_TARGET_VIEW_DESC) == alignof(RENDER_TARGET_VIEW_DESC));
    return *alias_cast<const D3D12_RENDER_TARGET_VIEW_DESC*>(&v);
}

inline D3D12_TEX1D_DSV getDX12(const TEX1D_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_DSV) == sizeof(TEX1D_DSV));
    static_assert(alignof(D3D12_TEX1D_DSV) == alignof(TEX1D_DSV));
    return *alias_cast<const D3D12_TEX1D_DSV*>(&v);
}

inline D3D12_TEX1D_ARRAY_DSV getDX12(const TEX1D_ARRAY_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX1D_ARRAY_DSV) == sizeof(TEX1D_ARRAY_DSV));
    static_assert(alignof(D3D12_TEX1D_ARRAY_DSV) == alignof(TEX1D_ARRAY_DSV));
    return *alias_cast<const D3D12_TEX1D_ARRAY_DSV*>(&v);
}

inline D3D12_TEX2D_DSV getDX12(const TEX2D_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_DSV) == sizeof(TEX2D_DSV));
    static_assert(alignof(D3D12_TEX2D_DSV) == alignof(TEX2D_DSV));
    return *alias_cast<const D3D12_TEX2D_DSV*>(&v);
}

inline D3D12_TEX2D_ARRAY_DSV getDX12(const TEX2D_ARRAY_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2D_ARRAY_DSV) == sizeof(TEX2D_ARRAY_DSV));
    static_assert(alignof(D3D12_TEX2D_ARRAY_DSV) == alignof(TEX2D_ARRAY_DSV));
    return *alias_cast<const D3D12_TEX2D_ARRAY_DSV*>(&v);
}

inline D3D12_TEX2DMS_DSV getDX12(const TEX2DMS_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_DSV) == sizeof(TEX2DMS_DSV));
    static_assert(alignof(D3D12_TEX2DMS_DSV) == alignof(TEX2DMS_DSV));
    return *alias_cast<const D3D12_TEX2DMS_DSV*>(&v);
}

inline D3D12_TEX2DMS_ARRAY_DSV getDX12(const TEX2DMS_ARRAY_DSV& v) noexcept {
    static_assert(sizeof(D3D12_TEX2DMS_ARRAY_DSV) == sizeof(TEX2DMS_ARRAY_DSV));
    static_assert(alignof(D3D12_TEX2DMS_ARRAY_DSV) == alignof(TEX2DMS_ARRAY_DSV));
    return *alias_cast<const D3D12_TEX2DMS_ARRAY_DSV*>(&v);
}

inline D3D12_DSV_FLAGS getDX12(DSV_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_DSV_FLAGS) == sizeof(DSV_FLAGS));
    static_assert(alignof(D3D12_DSV_FLAGS) == alignof(DSV_FLAGS));
    return *alias_cast<D3D12_DSV_FLAGS*>(&v);
}

inline D3D12_DSV_DIMENSION getDX12(DSV_DIMENSION v) noexcept {
    static_assert(sizeof(D3D12_DSV_DIMENSION) == sizeof(DSV_DIMENSION));
    static_assert(alignof(D3D12_DSV_DIMENSION) == alignof(DSV_DIMENSION));
    return *alias_cast<D3D12_DSV_DIMENSION*>(&v);
}

inline D3D12_DEPTH_STENCIL_VIEW_DESC getDX12(const DEPTH_STENCIL_VIEW_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DEPTH_STENCIL_VIEW_DESC) == sizeof(DEPTH_STENCIL_VIEW_DESC));
    static_assert(alignof(D3D12_DEPTH_STENCIL_VIEW_DESC) == alignof(DEPTH_STENCIL_VIEW_DESC));
    return *alias_cast<const D3D12_DEPTH_STENCIL_VIEW_DESC*>(&v);
}

inline D3D12_CLEAR_FLAGS getDX12(CLEAR_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_CLEAR_FLAGS) == sizeof(CLEAR_FLAGS));
    static_assert(alignof(D3D12_CLEAR_FLAGS) == alignof(CLEAR_FLAGS));
    return *alias_cast<D3D12_CLEAR_FLAGS*>(&v);
}

inline D3D12_FENCE_FLAGS getDX12(FENCE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_FENCE_FLAGS) == sizeof(FENCE_FLAGS));
    static_assert(alignof(D3D12_FENCE_FLAGS) == alignof(FENCE_FLAGS));
    return *alias_cast<D3D12_FENCE_FLAGS*>(&v);
}

inline D3D12_DESCRIPTOR_HEAP_TYPE getDX12(DESCRIPTOR_HEAP_TYPE v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_HEAP_TYPE) == sizeof(DESCRIPTOR_HEAP_TYPE));
    static_assert(alignof(D3D12_DESCRIPTOR_HEAP_TYPE) == alignof(DESCRIPTOR_HEAP_TYPE));
    return *alias_cast<D3D12_DESCRIPTOR_HEAP_TYPE*>(&v);
}

inline D3D12_DESCRIPTOR_HEAP_FLAGS getDX12(DESCRIPTOR_HEAP_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_HEAP_FLAGS) == sizeof(DESCRIPTOR_HEAP_FLAGS));
    static_assert(alignof(D3D12_DESCRIPTOR_HEAP_FLAGS) == alignof(DESCRIPTOR_HEAP_FLAGS));
    return *alias_cast<D3D12_DESCRIPTOR_HEAP_FLAGS*>(&v);
}

inline D3D12_DESCRIPTOR_HEAP_DESC getDX12(const DESCRIPTOR_HEAP_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_HEAP_DESC) == sizeof(DESCRIPTOR_HEAP_DESC));
    static_assert(alignof(D3D12_DESCRIPTOR_HEAP_DESC) == alignof(DESCRIPTOR_HEAP_DESC));
    return *alias_cast<const D3D12_DESCRIPTOR_HEAP_DESC*>(&v);
}

inline D3D12_DESCRIPTOR_RANGE_TYPE getDX12(DESCRIPTOR_RANGE_TYPE v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_RANGE_TYPE) == sizeof(DESCRIPTOR_RANGE_TYPE));
    static_assert(alignof(D3D12_DESCRIPTOR_RANGE_TYPE) == alignof(DESCRIPTOR_RANGE_TYPE));
    return *alias_cast<D3D12_DESCRIPTOR_RANGE_TYPE*>(&v);
}

inline D3D12_DESCRIPTOR_RANGE getDX12(const DESCRIPTOR_RANGE& v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_RANGE) == sizeof(DESCRIPTOR_RANGE));
    static_assert(alignof(D3D12_DESCRIPTOR_RANGE) == alignof(DESCRIPTOR_RANGE));
    return *alias_cast<const D3D12_DESCRIPTOR_RANGE*>(&v);
}

inline D3D12_ROOT_DESCRIPTOR_TABLE getDX12(const ROOT_DESCRIPTOR_TABLE& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_DESCRIPTOR_TABLE) == sizeof(ROOT_DESCRIPTOR_TABLE));
    static_assert(alignof(D3D12_ROOT_DESCRIPTOR_TABLE) == alignof(ROOT_DESCRIPTOR_TABLE));
    return *alias_cast<const D3D12_ROOT_DESCRIPTOR_TABLE*>(&v);
}

inline D3D12_ROOT_CONSTANTS getDX12(const ROOT_CONSTANTS& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_CONSTANTS) == sizeof(ROOT_CONSTANTS));
    static_assert(alignof(D3D12_ROOT_CONSTANTS) == alignof(ROOT_CONSTANTS));
    return *alias_cast<const D3D12_ROOT_CONSTANTS*>(&v);
}

inline D3D12_ROOT_DESCRIPTOR getDX12(const ROOT_DESCRIPTOR& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_DESCRIPTOR) == sizeof(ROOT_DESCRIPTOR));
    static_assert(alignof(D3D12_ROOT_DESCRIPTOR) == alignof(ROOT_DESCRIPTOR));
    return *alias_cast<const D3D12_ROOT_DESCRIPTOR*>(&v);
}

inline D3D12_SHADER_VISIBILITY getDX12(SHADER_VISIBILITY v) noexcept {
    static_assert(sizeof(D3D12_SHADER_VISIBILITY) == sizeof(SHADER_VISIBILITY));
    static_assert(alignof(D3D12_SHADER_VISIBILITY) == alignof(SHADER_VISIBILITY));
    return *alias_cast<D3D12_SHADER_VISIBILITY*>(&v);
}

inline D3D12_ROOT_PARAMETER_TYPE getDX12(ROOT_PARAMETER_TYPE v) noexcept {
    static_assert(sizeof(D3D12_ROOT_PARAMETER_TYPE) == sizeof(ROOT_PARAMETER_TYPE));
    static_assert(alignof(D3D12_ROOT_PARAMETER_TYPE) == alignof(ROOT_PARAMETER_TYPE));
    return *alias_cast<D3D12_ROOT_PARAMETER_TYPE*>(&v);
}

inline D3D12_ROOT_PARAMETER getDX12(const ROOT_PARAMETER& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_PARAMETER) == sizeof(ROOT_PARAMETER));
    static_assert(alignof(D3D12_ROOT_PARAMETER) == alignof(ROOT_PARAMETER));
    return *alias_cast<const D3D12_ROOT_PARAMETER*>(&v);
}

inline D3D12_ROOT_SIGNATURE_FLAGS getDX12(ROOT_SIGNATURE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_ROOT_SIGNATURE_FLAGS) == sizeof(ROOT_SIGNATURE_FLAGS));
    static_assert(alignof(D3D12_ROOT_SIGNATURE_FLAGS) == alignof(ROOT_SIGNATURE_FLAGS));
    return *alias_cast<D3D12_ROOT_SIGNATURE_FLAGS*>(&v);
}

inline D3D12_STATIC_BORDER_COLOR getDX12(STATIC_BORDER_COLOR v) noexcept {
    static_assert(sizeof(D3D12_STATIC_BORDER_COLOR) == sizeof(STATIC_BORDER_COLOR));
    static_assert(alignof(D3D12_STATIC_BORDER_COLOR) == alignof(STATIC_BORDER_COLOR));
    return *alias_cast<D3D12_STATIC_BORDER_COLOR*>(&v);
}

inline D3D12_STATIC_SAMPLER_DESC getDX12(const STATIC_SAMPLER_DESC& v) noexcept {
    static_assert(sizeof(D3D12_STATIC_SAMPLER_DESC) == sizeof(STATIC_SAMPLER_DESC));
    static_assert(alignof(D3D12_STATIC_SAMPLER_DESC) == alignof(STATIC_SAMPLER_DESC));
    return *alias_cast<const D3D12_STATIC_SAMPLER_DESC*>(&v);
}

inline D3D12_ROOT_SIGNATURE_DESC getDX12(const ROOT_SIGNATURE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_SIGNATURE_DESC) == sizeof(ROOT_SIGNATURE_DESC));
    static_assert(alignof(D3D12_ROOT_SIGNATURE_DESC) == alignof(ROOT_SIGNATURE_DESC));
    return *alias_cast<const D3D12_ROOT_SIGNATURE_DESC*>(&v);
}

inline D3D12_DESCRIPTOR_RANGE_FLAGS getDX12(DESCRIPTOR_RANGE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_RANGE_FLAGS) == sizeof(DESCRIPTOR_RANGE_FLAGS));
    static_assert(alignof(D3D12_DESCRIPTOR_RANGE_FLAGS) == alignof(DESCRIPTOR_RANGE_FLAGS));
    return *alias_cast<D3D12_DESCRIPTOR_RANGE_FLAGS*>(&v);
}

inline D3D12_DESCRIPTOR_RANGE1 getDX12(const DESCRIPTOR_RANGE1& v) noexcept {
    static_assert(sizeof(D3D12_DESCRIPTOR_RANGE1) == sizeof(DESCRIPTOR_RANGE1));
    static_assert(alignof(D3D12_DESCRIPTOR_RANGE1) == alignof(DESCRIPTOR_RANGE1));
    return *alias_cast<const D3D12_DESCRIPTOR_RANGE1*>(&v);
}

inline D3D12_ROOT_DESCRIPTOR_TABLE1 getDX12(const ROOT_DESCRIPTOR_TABLE1& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_DESCRIPTOR_TABLE1) == sizeof(ROOT_DESCRIPTOR_TABLE1));
    static_assert(alignof(D3D12_ROOT_DESCRIPTOR_TABLE1) == alignof(ROOT_DESCRIPTOR_TABLE1));
    return *alias_cast<const D3D12_ROOT_DESCRIPTOR_TABLE1*>(&v);
}

inline D3D12_ROOT_DESCRIPTOR_FLAGS getDX12(ROOT_DESCRIPTOR_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_ROOT_DESCRIPTOR_FLAGS) == sizeof(ROOT_DESCRIPTOR_FLAGS));
    static_assert(alignof(D3D12_ROOT_DESCRIPTOR_FLAGS) == alignof(ROOT_DESCRIPTOR_FLAGS));
    return *alias_cast<D3D12_ROOT_DESCRIPTOR_FLAGS*>(&v);
}

inline D3D12_ROOT_DESCRIPTOR1 getDX12(const ROOT_DESCRIPTOR1& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_DESCRIPTOR1) == sizeof(ROOT_DESCRIPTOR1));
    static_assert(alignof(D3D12_ROOT_DESCRIPTOR1) == alignof(ROOT_DESCRIPTOR1));
    return *alias_cast<const D3D12_ROOT_DESCRIPTOR1*>(&v);
}

inline D3D12_ROOT_PARAMETER1 getDX12(const ROOT_PARAMETER1& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_PARAMETER1) == sizeof(ROOT_PARAMETER1));
    static_assert(alignof(D3D12_ROOT_PARAMETER1) == alignof(ROOT_PARAMETER1));
    return *alias_cast<const D3D12_ROOT_PARAMETER1*>(&v);
}

inline D3D12_ROOT_SIGNATURE_DESC1 getDX12(const ROOT_SIGNATURE_DESC1& v) noexcept {
    static_assert(sizeof(D3D12_ROOT_SIGNATURE_DESC1) == sizeof(ROOT_SIGNATURE_DESC1));
    static_assert(alignof(D3D12_ROOT_SIGNATURE_DESC1) == alignof(ROOT_SIGNATURE_DESC1));
    return *alias_cast<const D3D12_ROOT_SIGNATURE_DESC1*>(&v);
}

inline D3D12_VERSIONED_ROOT_SIGNATURE_DESC getDX12(const VERSIONED_ROOT_SIGNATURE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_VERSIONED_ROOT_SIGNATURE_DESC) == sizeof(VERSIONED_ROOT_SIGNATURE_DESC));
    static_assert(alignof(D3D12_VERSIONED_ROOT_SIGNATURE_DESC) == alignof(VERSIONED_ROOT_SIGNATURE_DESC));
    return *alias_cast<const D3D12_VERSIONED_ROOT_SIGNATURE_DESC*>(&v);
}

inline D3D12_CPU_DESCRIPTOR_HANDLE getDX12(const CPU_DESCRIPTOR_HANDLE& v) noexcept {
    static_assert(sizeof(D3D12_CPU_DESCRIPTOR_HANDLE) == sizeof(CPU_DESCRIPTOR_HANDLE));
    static_assert(alignof(D3D12_CPU_DESCRIPTOR_HANDLE) == alignof(CPU_DESCRIPTOR_HANDLE));
    return *alias_cast<const D3D12_CPU_DESCRIPTOR_HANDLE*>(&v);
}

inline D3D12_GPU_DESCRIPTOR_HANDLE getDX12(const GPU_DESCRIPTOR_HANDLE& v) noexcept {
    static_assert(sizeof(D3D12_GPU_DESCRIPTOR_HANDLE) == sizeof(GPU_DESCRIPTOR_HANDLE));
    static_assert(alignof(D3D12_GPU_DESCRIPTOR_HANDLE) == alignof(GPU_DESCRIPTOR_HANDLE));
    return *alias_cast<const D3D12_GPU_DESCRIPTOR_HANDLE*>(&v);
}

inline D3D12_DISCARD_REGION getDX12(const DISCARD_REGION& v) noexcept {
    static_assert(sizeof(D3D12_DISCARD_REGION) == sizeof(DISCARD_REGION));
    static_assert(alignof(D3D12_DISCARD_REGION) == alignof(DISCARD_REGION));
    return *alias_cast<const D3D12_DISCARD_REGION*>(&v);
}

inline D3D12_QUERY_HEAP_TYPE getDX12(QUERY_HEAP_TYPE v) noexcept {
    static_assert(sizeof(D3D12_QUERY_HEAP_TYPE) == sizeof(QUERY_HEAP_TYPE));
    static_assert(alignof(D3D12_QUERY_HEAP_TYPE) == alignof(QUERY_HEAP_TYPE));
    return *alias_cast<D3D12_QUERY_HEAP_TYPE*>(&v);
}

inline D3D12_QUERY_HEAP_DESC getDX12(const QUERY_HEAP_DESC& v) noexcept {
    static_assert(sizeof(D3D12_QUERY_HEAP_DESC) == sizeof(QUERY_HEAP_DESC));
    static_assert(alignof(D3D12_QUERY_HEAP_DESC) == alignof(QUERY_HEAP_DESC));
    return *alias_cast<const D3D12_QUERY_HEAP_DESC*>(&v);
}

inline D3D12_QUERY_TYPE getDX12(QUERY_TYPE v) noexcept {
    static_assert(sizeof(D3D12_QUERY_TYPE) == sizeof(QUERY_TYPE));
    static_assert(alignof(D3D12_QUERY_TYPE) == alignof(QUERY_TYPE));
    return *alias_cast<D3D12_QUERY_TYPE*>(&v);
}

inline D3D12_PREDICATION_OP getDX12(PREDICATION_OP v) noexcept {
    static_assert(sizeof(D3D12_PREDICATION_OP) == sizeof(PREDICATION_OP));
    static_assert(alignof(D3D12_PREDICATION_OP) == alignof(PREDICATION_OP));
    return *alias_cast<D3D12_PREDICATION_OP*>(&v);
}

inline D3D12_QUERY_DATA_PIPELINE_STATISTICS getDX12(const QUERY_DATA_PIPELINE_STATISTICS& v) noexcept {
    static_assert(sizeof(D3D12_QUERY_DATA_PIPELINE_STATISTICS) == sizeof(QUERY_DATA_PIPELINE_STATISTICS));
    static_assert(alignof(D3D12_QUERY_DATA_PIPELINE_STATISTICS) == alignof(QUERY_DATA_PIPELINE_STATISTICS));
    return *alias_cast<const D3D12_QUERY_DATA_PIPELINE_STATISTICS*>(&v);
}

inline D3D12_QUERY_DATA_SO_STATISTICS getDX12(const QUERY_DATA_SO_STATISTICS& v) noexcept {
    static_assert(sizeof(D3D12_QUERY_DATA_SO_STATISTICS) == sizeof(QUERY_DATA_SO_STATISTICS));
    static_assert(alignof(D3D12_QUERY_DATA_SO_STATISTICS) == alignof(QUERY_DATA_SO_STATISTICS));
    return *alias_cast<const D3D12_QUERY_DATA_SO_STATISTICS*>(&v);
}

inline D3D12_STREAM_OUTPUT_BUFFER_VIEW getDX12(const STREAM_OUTPUT_BUFFER_VIEW& v) noexcept {
    static_assert(sizeof(D3D12_STREAM_OUTPUT_BUFFER_VIEW) == sizeof(STREAM_OUTPUT_BUFFER_VIEW));
    static_assert(alignof(D3D12_STREAM_OUTPUT_BUFFER_VIEW) == alignof(STREAM_OUTPUT_BUFFER_VIEW));
    return *alias_cast<const D3D12_STREAM_OUTPUT_BUFFER_VIEW*>(&v);
}

inline D3D12_DRAW_ARGUMENTS getDX12(const DRAW_ARGUMENTS& v) noexcept {
    static_assert(sizeof(D3D12_DRAW_ARGUMENTS) == sizeof(DRAW_ARGUMENTS));
    static_assert(alignof(D3D12_DRAW_ARGUMENTS) == alignof(DRAW_ARGUMENTS));
    return *alias_cast<const D3D12_DRAW_ARGUMENTS*>(&v);
}

inline D3D12_DRAW_INDEXED_ARGUMENTS getDX12(const DRAW_INDEXED_ARGUMENTS& v) noexcept {
    static_assert(sizeof(D3D12_DRAW_INDEXED_ARGUMENTS) == sizeof(DRAW_INDEXED_ARGUMENTS));
    static_assert(alignof(D3D12_DRAW_INDEXED_ARGUMENTS) == alignof(DRAW_INDEXED_ARGUMENTS));
    return *alias_cast<const D3D12_DRAW_INDEXED_ARGUMENTS*>(&v);
}

inline D3D12_DISPATCH_ARGUMENTS getDX12(const DISPATCH_ARGUMENTS& v) noexcept {
    static_assert(sizeof(D3D12_DISPATCH_ARGUMENTS) == sizeof(DISPATCH_ARGUMENTS));
    static_assert(alignof(D3D12_DISPATCH_ARGUMENTS) == alignof(DISPATCH_ARGUMENTS));
    return *alias_cast<const D3D12_DISPATCH_ARGUMENTS*>(&v);
}

inline D3D12_VERTEX_BUFFER_VIEW getDX12(const VERTEX_BUFFER_VIEW& v) noexcept {
    static_assert(sizeof(D3D12_VERTEX_BUFFER_VIEW) == sizeof(VERTEX_BUFFER_VIEW));
    static_assert(alignof(D3D12_VERTEX_BUFFER_VIEW) == alignof(VERTEX_BUFFER_VIEW));
    return *alias_cast<const D3D12_VERTEX_BUFFER_VIEW*>(&v);
}

inline D3D12_INDEX_BUFFER_VIEW getDX12(const INDEX_BUFFER_VIEW& v) noexcept {
    static_assert(sizeof(D3D12_INDEX_BUFFER_VIEW) == sizeof(INDEX_BUFFER_VIEW));
    static_assert(alignof(D3D12_INDEX_BUFFER_VIEW) == alignof(INDEX_BUFFER_VIEW));
    return *alias_cast<const D3D12_INDEX_BUFFER_VIEW*>(&v);
}

inline D3D12_INDIRECT_ARGUMENT_TYPE getDX12(INDIRECT_ARGUMENT_TYPE v) noexcept {
    static_assert(sizeof(D3D12_INDIRECT_ARGUMENT_TYPE) == sizeof(INDIRECT_ARGUMENT_TYPE));
    static_assert(alignof(D3D12_INDIRECT_ARGUMENT_TYPE) == alignof(INDIRECT_ARGUMENT_TYPE));
    return *alias_cast<D3D12_INDIRECT_ARGUMENT_TYPE*>(&v);
}

inline D3D12_INDIRECT_ARGUMENT_DESC getDX12(const INDIRECT_ARGUMENT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_INDIRECT_ARGUMENT_DESC) == sizeof(INDIRECT_ARGUMENT_DESC));
    static_assert(alignof(D3D12_INDIRECT_ARGUMENT_DESC) == alignof(INDIRECT_ARGUMENT_DESC));
    return *alias_cast<const D3D12_INDIRECT_ARGUMENT_DESC*>(&v);
}

inline D3D12_COMMAND_SIGNATURE_DESC getDX12(const COMMAND_SIGNATURE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_SIGNATURE_DESC) == sizeof(COMMAND_SIGNATURE_DESC));
    static_assert(alignof(D3D12_COMMAND_SIGNATURE_DESC) == alignof(COMMAND_SIGNATURE_DESC));
    return *alias_cast<const D3D12_COMMAND_SIGNATURE_DESC*>(&v);
}

inline D3D12_WRITEBUFFERIMMEDIATE_PARAMETER getDX12(const WRITEBUFFERIMMEDIATE_PARAMETER& v) noexcept {
    static_assert(sizeof(D3D12_WRITEBUFFERIMMEDIATE_PARAMETER) == sizeof(WRITEBUFFERIMMEDIATE_PARAMETER));
    static_assert(alignof(D3D12_WRITEBUFFERIMMEDIATE_PARAMETER) == alignof(WRITEBUFFERIMMEDIATE_PARAMETER));
    return *alias_cast<const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER*>(&v);
}

inline D3D12_WRITEBUFFERIMMEDIATE_MODE getDX12(WRITEBUFFERIMMEDIATE_MODE v) noexcept {
    static_assert(sizeof(D3D12_WRITEBUFFERIMMEDIATE_MODE) == sizeof(WRITEBUFFERIMMEDIATE_MODE));
    static_assert(alignof(D3D12_WRITEBUFFERIMMEDIATE_MODE) == alignof(WRITEBUFFERIMMEDIATE_MODE));
    return *alias_cast<D3D12_WRITEBUFFERIMMEDIATE_MODE*>(&v);
}

inline D3D12_MULTIPLE_FENCE_WAIT_FLAGS getDX12(MULTIPLE_FENCE_WAIT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_MULTIPLE_FENCE_WAIT_FLAGS) == sizeof(MULTIPLE_FENCE_WAIT_FLAGS));
    static_assert(alignof(D3D12_MULTIPLE_FENCE_WAIT_FLAGS) == alignof(MULTIPLE_FENCE_WAIT_FLAGS));
    return *alias_cast<D3D12_MULTIPLE_FENCE_WAIT_FLAGS*>(&v);
}

inline D3D12_RESIDENCY_PRIORITY getDX12(RESIDENCY_PRIORITY v) noexcept {
    static_assert(sizeof(D3D12_RESIDENCY_PRIORITY) == sizeof(RESIDENCY_PRIORITY));
    static_assert(alignof(D3D12_RESIDENCY_PRIORITY) == alignof(RESIDENCY_PRIORITY));
    return *alias_cast<D3D12_RESIDENCY_PRIORITY*>(&v);
}

inline D3D12_RESIDENCY_FLAGS getDX12(RESIDENCY_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RESIDENCY_FLAGS) == sizeof(RESIDENCY_FLAGS));
    static_assert(alignof(D3D12_RESIDENCY_FLAGS) == alignof(RESIDENCY_FLAGS));
    return *alias_cast<D3D12_RESIDENCY_FLAGS*>(&v);
}

inline D3D12_COMMAND_LIST_FLAGS getDX12(COMMAND_LIST_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_LIST_FLAGS) == sizeof(COMMAND_LIST_FLAGS));
    static_assert(alignof(D3D12_COMMAND_LIST_FLAGS) == alignof(COMMAND_LIST_FLAGS));
    return *alias_cast<D3D12_COMMAND_LIST_FLAGS*>(&v);
}

inline D3D12_COMMAND_POOL_FLAGS getDX12(COMMAND_POOL_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_POOL_FLAGS) == sizeof(COMMAND_POOL_FLAGS));
    static_assert(alignof(D3D12_COMMAND_POOL_FLAGS) == alignof(COMMAND_POOL_FLAGS));
    return *alias_cast<D3D12_COMMAND_POOL_FLAGS*>(&v);
}

inline D3D12_COMMAND_RECORDER_FLAGS getDX12(COMMAND_RECORDER_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_COMMAND_RECORDER_FLAGS) == sizeof(COMMAND_RECORDER_FLAGS));
    static_assert(alignof(D3D12_COMMAND_RECORDER_FLAGS) == alignof(COMMAND_RECORDER_FLAGS));
    return *alias_cast<D3D12_COMMAND_RECORDER_FLAGS*>(&v);
}

inline D3D12_PROTECTED_SESSION_STATUS getDX12(PROTECTED_SESSION_STATUS v) noexcept {
    static_assert(sizeof(D3D12_PROTECTED_SESSION_STATUS) == sizeof(PROTECTED_SESSION_STATUS));
    static_assert(alignof(D3D12_PROTECTED_SESSION_STATUS) == alignof(PROTECTED_SESSION_STATUS));
    return *alias_cast<D3D12_PROTECTED_SESSION_STATUS*>(&v);
}

inline D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS getDX12(PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS) == sizeof(PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS));
    static_assert(alignof(D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS) == alignof(PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS));
    return *alias_cast<D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS*>(&v);
}

inline D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT getDX12(const FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT& v) noexcept {
    static_assert(sizeof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT) == sizeof(FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT));
    static_assert(alignof(D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT) == alignof(FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT));
    return *alias_cast<const D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT*>(&v);
}

inline D3D12_PROTECTED_RESOURCE_SESSION_FLAGS getDX12(PROTECTED_RESOURCE_SESSION_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_PROTECTED_RESOURCE_SESSION_FLAGS) == sizeof(PROTECTED_RESOURCE_SESSION_FLAGS));
    static_assert(alignof(D3D12_PROTECTED_RESOURCE_SESSION_FLAGS) == alignof(PROTECTED_RESOURCE_SESSION_FLAGS));
    return *alias_cast<D3D12_PROTECTED_RESOURCE_SESSION_FLAGS*>(&v);
}

inline D3D12_PROTECTED_RESOURCE_SESSION_DESC getDX12(const PROTECTED_RESOURCE_SESSION_DESC& v) noexcept {
    static_assert(sizeof(D3D12_PROTECTED_RESOURCE_SESSION_DESC) == sizeof(PROTECTED_RESOURCE_SESSION_DESC));
    static_assert(alignof(D3D12_PROTECTED_RESOURCE_SESSION_DESC) == alignof(PROTECTED_RESOURCE_SESSION_DESC));
    return *alias_cast<const D3D12_PROTECTED_RESOURCE_SESSION_DESC*>(&v);
}

inline D3D12_LIFETIME_STATE getDX12(LIFETIME_STATE v) noexcept {
    static_assert(sizeof(D3D12_LIFETIME_STATE) == sizeof(LIFETIME_STATE));
    static_assert(alignof(D3D12_LIFETIME_STATE) == alignof(LIFETIME_STATE));
    return *alias_cast<D3D12_LIFETIME_STATE*>(&v);
}

inline D3D12_META_COMMAND_PARAMETER_TYPE getDX12(META_COMMAND_PARAMETER_TYPE v) noexcept {
    static_assert(sizeof(D3D12_META_COMMAND_PARAMETER_TYPE) == sizeof(META_COMMAND_PARAMETER_TYPE));
    static_assert(alignof(D3D12_META_COMMAND_PARAMETER_TYPE) == alignof(META_COMMAND_PARAMETER_TYPE));
    return *alias_cast<D3D12_META_COMMAND_PARAMETER_TYPE*>(&v);
}

inline D3D12_META_COMMAND_PARAMETER_FLAGS getDX12(META_COMMAND_PARAMETER_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_META_COMMAND_PARAMETER_FLAGS) == sizeof(META_COMMAND_PARAMETER_FLAGS));
    static_assert(alignof(D3D12_META_COMMAND_PARAMETER_FLAGS) == alignof(META_COMMAND_PARAMETER_FLAGS));
    return *alias_cast<D3D12_META_COMMAND_PARAMETER_FLAGS*>(&v);
}

inline D3D12_META_COMMAND_PARAMETER_STAGE getDX12(META_COMMAND_PARAMETER_STAGE v) noexcept {
    static_assert(sizeof(D3D12_META_COMMAND_PARAMETER_STAGE) == sizeof(META_COMMAND_PARAMETER_STAGE));
    static_assert(alignof(D3D12_META_COMMAND_PARAMETER_STAGE) == alignof(META_COMMAND_PARAMETER_STAGE));
    return *alias_cast<D3D12_META_COMMAND_PARAMETER_STAGE*>(&v);
}

inline D3D12_META_COMMAND_PARAMETER_DESC getDX12(const META_COMMAND_PARAMETER_DESC& v) noexcept {
    static_assert(sizeof(D3D12_META_COMMAND_PARAMETER_DESC) == sizeof(META_COMMAND_PARAMETER_DESC));
    static_assert(alignof(D3D12_META_COMMAND_PARAMETER_DESC) == alignof(META_COMMAND_PARAMETER_DESC));
    return *alias_cast<const D3D12_META_COMMAND_PARAMETER_DESC*>(&v);
}

inline D3D12_GRAPHICS_STATES getDX12(GRAPHICS_STATES v) noexcept {
    static_assert(sizeof(D3D12_GRAPHICS_STATES) == sizeof(GRAPHICS_STATES));
    static_assert(alignof(D3D12_GRAPHICS_STATES) == alignof(GRAPHICS_STATES));
    return *alias_cast<D3D12_GRAPHICS_STATES*>(&v);
}

inline D3D12_META_COMMAND_DESC getDX12(const META_COMMAND_DESC& v) noexcept {
    static_assert(sizeof(D3D12_META_COMMAND_DESC) == sizeof(META_COMMAND_DESC));
    static_assert(alignof(D3D12_META_COMMAND_DESC) == alignof(META_COMMAND_DESC));
    return *alias_cast<const D3D12_META_COMMAND_DESC*>(&v);
}

inline D3D12_STATE_SUBOBJECT_TYPE getDX12(STATE_SUBOBJECT_TYPE v) noexcept {
    static_assert(sizeof(D3D12_STATE_SUBOBJECT_TYPE) == sizeof(STATE_SUBOBJECT_TYPE));
    static_assert(alignof(D3D12_STATE_SUBOBJECT_TYPE) == alignof(STATE_SUBOBJECT_TYPE));
    return *alias_cast<D3D12_STATE_SUBOBJECT_TYPE*>(&v);
}

inline D3D12_STATE_SUBOBJECT getDX12(const STATE_SUBOBJECT& v) noexcept {
    static_assert(sizeof(D3D12_STATE_SUBOBJECT) == sizeof(STATE_SUBOBJECT));
    static_assert(alignof(D3D12_STATE_SUBOBJECT) == alignof(STATE_SUBOBJECT));
    return *alias_cast<const D3D12_STATE_SUBOBJECT*>(&v);
}

inline D3D12_STATE_OBJECT_FLAGS getDX12(STATE_OBJECT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_STATE_OBJECT_FLAGS) == sizeof(STATE_OBJECT_FLAGS));
    static_assert(alignof(D3D12_STATE_OBJECT_FLAGS) == alignof(STATE_OBJECT_FLAGS));
    return *alias_cast<D3D12_STATE_OBJECT_FLAGS*>(&v);
}

inline D3D12_STATE_OBJECT_CONFIG getDX12(const STATE_OBJECT_CONFIG& v) noexcept {
    static_assert(sizeof(D3D12_STATE_OBJECT_CONFIG) == sizeof(STATE_OBJECT_CONFIG));
    static_assert(alignof(D3D12_STATE_OBJECT_CONFIG) == alignof(STATE_OBJECT_CONFIG));
    return *alias_cast<const D3D12_STATE_OBJECT_CONFIG*>(&v);
}

inline D3D12_GLOBAL_ROOT_SIGNATURE getDX12(const GLOBAL_ROOT_SIGNATURE& v) noexcept {
    static_assert(sizeof(D3D12_GLOBAL_ROOT_SIGNATURE) == sizeof(GLOBAL_ROOT_SIGNATURE));
    static_assert(alignof(D3D12_GLOBAL_ROOT_SIGNATURE) == alignof(GLOBAL_ROOT_SIGNATURE));
    return *alias_cast<const D3D12_GLOBAL_ROOT_SIGNATURE*>(&v);
}

inline D3D12_LOCAL_ROOT_SIGNATURE getDX12(const LOCAL_ROOT_SIGNATURE& v) noexcept {
    static_assert(sizeof(D3D12_LOCAL_ROOT_SIGNATURE) == sizeof(LOCAL_ROOT_SIGNATURE));
    static_assert(alignof(D3D12_LOCAL_ROOT_SIGNATURE) == alignof(LOCAL_ROOT_SIGNATURE));
    return *alias_cast<const D3D12_LOCAL_ROOT_SIGNATURE*>(&v);
}

inline D3D12_NODE_MASK getDX12(const NODE_MASK& v) noexcept {
    static_assert(sizeof(D3D12_NODE_MASK) == sizeof(NODE_MASK));
    static_assert(alignof(D3D12_NODE_MASK) == alignof(NODE_MASK));
    return *alias_cast<const D3D12_NODE_MASK*>(&v);
}

inline D3D12_EXPORT_FLAGS getDX12(EXPORT_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_EXPORT_FLAGS) == sizeof(EXPORT_FLAGS));
    static_assert(alignof(D3D12_EXPORT_FLAGS) == alignof(EXPORT_FLAGS));
    return *alias_cast<D3D12_EXPORT_FLAGS*>(&v);
}

inline D3D12_EXPORT_DESC getDX12(const EXPORT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_EXPORT_DESC) == sizeof(EXPORT_DESC));
    static_assert(alignof(D3D12_EXPORT_DESC) == alignof(EXPORT_DESC));
    return *alias_cast<const D3D12_EXPORT_DESC*>(&v);
}

inline D3D12_DXIL_LIBRARY_DESC getDX12(const DXIL_LIBRARY_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DXIL_LIBRARY_DESC) == sizeof(DXIL_LIBRARY_DESC));
    static_assert(alignof(D3D12_DXIL_LIBRARY_DESC) == alignof(DXIL_LIBRARY_DESC));
    return *alias_cast<const D3D12_DXIL_LIBRARY_DESC*>(&v);
}

inline D3D12_EXISTING_COLLECTION_DESC getDX12(const EXISTING_COLLECTION_DESC& v) noexcept {
    static_assert(sizeof(D3D12_EXISTING_COLLECTION_DESC) == sizeof(EXISTING_COLLECTION_DESC));
    static_assert(alignof(D3D12_EXISTING_COLLECTION_DESC) == alignof(EXISTING_COLLECTION_DESC));
    return *alias_cast<const D3D12_EXISTING_COLLECTION_DESC*>(&v);
}

inline D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION getDX12(const SUBOBJECT_TO_EXPORTS_ASSOCIATION& v) noexcept {
    static_assert(sizeof(D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION) == sizeof(SUBOBJECT_TO_EXPORTS_ASSOCIATION));
    static_assert(alignof(D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION) == alignof(SUBOBJECT_TO_EXPORTS_ASSOCIATION));
    return *alias_cast<const D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION*>(&v);
}

inline D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION getDX12(const DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION& v) noexcept {
    static_assert(sizeof(D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION) == sizeof(DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION));
    static_assert(alignof(D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION) == alignof(DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION));
    return *alias_cast<const D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION*>(&v);
}

inline D3D12_HIT_GROUP_TYPE getDX12(HIT_GROUP_TYPE v) noexcept {
    static_assert(sizeof(D3D12_HIT_GROUP_TYPE) == sizeof(HIT_GROUP_TYPE));
    static_assert(alignof(D3D12_HIT_GROUP_TYPE) == alignof(HIT_GROUP_TYPE));
    return *alias_cast<D3D12_HIT_GROUP_TYPE*>(&v);
}

inline D3D12_HIT_GROUP_DESC getDX12(const HIT_GROUP_DESC& v) noexcept {
    static_assert(sizeof(D3D12_HIT_GROUP_DESC) == sizeof(HIT_GROUP_DESC));
    static_assert(alignof(D3D12_HIT_GROUP_DESC) == alignof(HIT_GROUP_DESC));
    return *alias_cast<const D3D12_HIT_GROUP_DESC*>(&v);
}

inline D3D12_RAYTRACING_SHADER_CONFIG getDX12(const RAYTRACING_SHADER_CONFIG& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_SHADER_CONFIG) == sizeof(RAYTRACING_SHADER_CONFIG));
    static_assert(alignof(D3D12_RAYTRACING_SHADER_CONFIG) == alignof(RAYTRACING_SHADER_CONFIG));
    return *alias_cast<const D3D12_RAYTRACING_SHADER_CONFIG*>(&v);
}

inline D3D12_RAYTRACING_PIPELINE_CONFIG getDX12(const RAYTRACING_PIPELINE_CONFIG& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_PIPELINE_CONFIG) == sizeof(RAYTRACING_PIPELINE_CONFIG));
    static_assert(alignof(D3D12_RAYTRACING_PIPELINE_CONFIG) == alignof(RAYTRACING_PIPELINE_CONFIG));
    return *alias_cast<const D3D12_RAYTRACING_PIPELINE_CONFIG*>(&v);
}

inline D3D12_STATE_OBJECT_TYPE getDX12(STATE_OBJECT_TYPE v) noexcept {
    static_assert(sizeof(D3D12_STATE_OBJECT_TYPE) == sizeof(STATE_OBJECT_TYPE));
    static_assert(alignof(D3D12_STATE_OBJECT_TYPE) == alignof(STATE_OBJECT_TYPE));
    return *alias_cast<D3D12_STATE_OBJECT_TYPE*>(&v);
}

inline D3D12_STATE_OBJECT_DESC getDX12(const STATE_OBJECT_DESC& v) noexcept {
    static_assert(sizeof(D3D12_STATE_OBJECT_DESC) == sizeof(STATE_OBJECT_DESC));
    static_assert(alignof(D3D12_STATE_OBJECT_DESC) == alignof(STATE_OBJECT_DESC));
    return *alias_cast<const D3D12_STATE_OBJECT_DESC*>(&v);
}

inline D3D12_RAYTRACING_GEOMETRY_FLAGS getDX12(RAYTRACING_GEOMETRY_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_GEOMETRY_FLAGS) == sizeof(RAYTRACING_GEOMETRY_FLAGS));
    static_assert(alignof(D3D12_RAYTRACING_GEOMETRY_FLAGS) == alignof(RAYTRACING_GEOMETRY_FLAGS));
    return *alias_cast<D3D12_RAYTRACING_GEOMETRY_FLAGS*>(&v);
}

inline D3D12_RAYTRACING_GEOMETRY_TYPE getDX12(RAYTRACING_GEOMETRY_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_GEOMETRY_TYPE) == sizeof(RAYTRACING_GEOMETRY_TYPE));
    static_assert(alignof(D3D12_RAYTRACING_GEOMETRY_TYPE) == alignof(RAYTRACING_GEOMETRY_TYPE));
    return *alias_cast<D3D12_RAYTRACING_GEOMETRY_TYPE*>(&v);
}

inline D3D12_RAYTRACING_INSTANCE_FLAGS getDX12(RAYTRACING_INSTANCE_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_INSTANCE_FLAGS) == sizeof(RAYTRACING_INSTANCE_FLAGS));
    static_assert(alignof(D3D12_RAYTRACING_INSTANCE_FLAGS) == alignof(RAYTRACING_INSTANCE_FLAGS));
    return *alias_cast<D3D12_RAYTRACING_INSTANCE_FLAGS*>(&v);
}

inline D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE getDX12(const GPU_VIRTUAL_ADDRESS_AND_STRIDE& v) noexcept {
    static_assert(sizeof(D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE) == sizeof(GPU_VIRTUAL_ADDRESS_AND_STRIDE));
    static_assert(alignof(D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE) == alignof(GPU_VIRTUAL_ADDRESS_AND_STRIDE));
    return *alias_cast<const D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE*>(&v);
}

inline D3D12_GPU_VIRTUAL_ADDRESS_RANGE getDX12(const GPU_VIRTUAL_ADDRESS_RANGE& v) noexcept {
    static_assert(sizeof(D3D12_GPU_VIRTUAL_ADDRESS_RANGE) == sizeof(GPU_VIRTUAL_ADDRESS_RANGE));
    static_assert(alignof(D3D12_GPU_VIRTUAL_ADDRESS_RANGE) == alignof(GPU_VIRTUAL_ADDRESS_RANGE));
    return *alias_cast<const D3D12_GPU_VIRTUAL_ADDRESS_RANGE*>(&v);
}

inline D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE getDX12(const GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE& v) noexcept {
    static_assert(sizeof(D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE) == sizeof(GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE));
    static_assert(alignof(D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE) == alignof(GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE));
    return *alias_cast<const D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE*>(&v);
}

inline D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC getDX12(const RAYTRACING_GEOMETRY_TRIANGLES_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC) == sizeof(RAYTRACING_GEOMETRY_TRIANGLES_DESC));
    static_assert(alignof(D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC) == alignof(RAYTRACING_GEOMETRY_TRIANGLES_DESC));
    return *alias_cast<const D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC*>(&v);
}

inline D3D12_RAYTRACING_AABB getDX12(const RAYTRACING_AABB& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_AABB) == sizeof(RAYTRACING_AABB));
    static_assert(alignof(D3D12_RAYTRACING_AABB) == alignof(RAYTRACING_AABB));
    return *alias_cast<const D3D12_RAYTRACING_AABB*>(&v);
}

inline D3D12_RAYTRACING_GEOMETRY_AABBS_DESC getDX12(const RAYTRACING_GEOMETRY_AABBS_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_GEOMETRY_AABBS_DESC) == sizeof(RAYTRACING_GEOMETRY_AABBS_DESC));
    static_assert(alignof(D3D12_RAYTRACING_GEOMETRY_AABBS_DESC) == alignof(RAYTRACING_GEOMETRY_AABBS_DESC));
    return *alias_cast<const D3D12_RAYTRACING_GEOMETRY_AABBS_DESC*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS getDX12(RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS));
    return *alias_cast<D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE getDX12(RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE));
    return *alias_cast<D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE getDX12(RAYTRACING_ACCELERATION_STRUCTURE_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_TYPE));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_TYPE));
    return *alias_cast<D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE*>(&v);
}

inline D3D12_ELEMENTS_LAYOUT getDX12(ELEMENTS_LAYOUT v) noexcept {
    static_assert(sizeof(D3D12_ELEMENTS_LAYOUT) == sizeof(ELEMENTS_LAYOUT));
    static_assert(alignof(D3D12_ELEMENTS_LAYOUT) == alignof(ELEMENTS_LAYOUT));
    return *alias_cast<D3D12_ELEMENTS_LAYOUT*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE getDX12(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE));
    return *alias_cast<D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC*>(&v);
}

inline D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER getDX12(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER& v) noexcept {
    static_assert(sizeof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER) == sizeof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER));
    static_assert(alignof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER) == alignof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER));
    return *alias_cast<const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC*>(&v);
}

inline D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER getDX12(const SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER& v) noexcept {
    static_assert(sizeof(D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER) == sizeof(SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER));
    static_assert(alignof(D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER) == alignof(SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER));
    return *alias_cast<const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER*>(&v);
}

inline D3D12_SERIALIZED_DATA_TYPE getDX12(SERIALIZED_DATA_TYPE v) noexcept {
    static_assert(sizeof(D3D12_SERIALIZED_DATA_TYPE) == sizeof(SERIALIZED_DATA_TYPE));
    static_assert(alignof(D3D12_SERIALIZED_DATA_TYPE) == alignof(SERIALIZED_DATA_TYPE));
    return *alias_cast<D3D12_SERIALIZED_DATA_TYPE*>(&v);
}

inline D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS getDX12(DRIVER_MATCHING_IDENTIFIER_STATUS v) noexcept {
    static_assert(sizeof(D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS) == sizeof(DRIVER_MATCHING_IDENTIFIER_STATUS));
    static_assert(alignof(D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS) == alignof(DRIVER_MATCHING_IDENTIFIER_STATUS));
    return *alias_cast<D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS*>(&v);
}

inline D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER getDX12(const SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER& v) noexcept {
    static_assert(sizeof(D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER) == sizeof(SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER));
    static_assert(alignof(D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER) == alignof(SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER));
    return *alias_cast<const D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC*>(&v);
}

inline D3D12_RAYTRACING_INSTANCE_DESC getDX12(const RAYTRACING_INSTANCE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_INSTANCE_DESC) == sizeof(RAYTRACING_INSTANCE_DESC));
    static_assert(alignof(D3D12_RAYTRACING_INSTANCE_DESC) == alignof(RAYTRACING_INSTANCE_DESC));
    return *alias_cast<const D3D12_RAYTRACING_INSTANCE_DESC*>(&v);
}

inline D3D12_RAYTRACING_GEOMETRY_DESC getDX12(const RAYTRACING_GEOMETRY_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_GEOMETRY_DESC) == sizeof(RAYTRACING_GEOMETRY_DESC));
    static_assert(alignof(D3D12_RAYTRACING_GEOMETRY_DESC) == alignof(RAYTRACING_GEOMETRY_DESC));
    return *alias_cast<const D3D12_RAYTRACING_GEOMETRY_DESC*>(&v);
}

inline D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS getDX12(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS& v) noexcept {
    static_assert(sizeof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS) == sizeof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS));
    static_assert(alignof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS) == alignof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS));
    return *alias_cast<const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS*>(&v);
}

inline D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC getDX12(const BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC& v) noexcept {
    static_assert(sizeof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC) == sizeof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC));
    static_assert(alignof(D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC) == alignof(BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC));
    return *alias_cast<const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC*>(&v);
}

inline D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO getDX12(const RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO& v) noexcept {
    static_assert(sizeof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO) == sizeof(RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO));
    static_assert(alignof(D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO) == alignof(RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO));
    return *alias_cast<const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*>(&v);
}

inline D3D12_RAY_FLAGS getDX12(RAY_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RAY_FLAGS) == sizeof(RAY_FLAGS));
    static_assert(alignof(D3D12_RAY_FLAGS) == alignof(RAY_FLAGS));
    return *alias_cast<D3D12_RAY_FLAGS*>(&v);
}

inline D3D12_HIT_KIND getDX12(HIT_KIND v) noexcept {
    static_assert(sizeof(D3D12_HIT_KIND) == sizeof(HIT_KIND));
    static_assert(alignof(D3D12_HIT_KIND) == alignof(HIT_KIND));
    return *alias_cast<D3D12_HIT_KIND*>(&v);
}

inline D3D12_AUTO_BREADCRUMB_OP getDX12(AUTO_BREADCRUMB_OP v) noexcept {
    static_assert(sizeof(D3D12_AUTO_BREADCRUMB_OP) == sizeof(AUTO_BREADCRUMB_OP));
    static_assert(alignof(D3D12_AUTO_BREADCRUMB_OP) == alignof(AUTO_BREADCRUMB_OP));
    return *alias_cast<D3D12_AUTO_BREADCRUMB_OP*>(&v);
}

inline D3D12_AUTO_BREADCRUMB_NODE getDX12(const AUTO_BREADCRUMB_NODE& v) noexcept {
    static_assert(sizeof(D3D12_AUTO_BREADCRUMB_NODE) == sizeof(AUTO_BREADCRUMB_NODE));
    static_assert(alignof(D3D12_AUTO_BREADCRUMB_NODE) == alignof(AUTO_BREADCRUMB_NODE));
    return *alias_cast<const D3D12_AUTO_BREADCRUMB_NODE*>(&v);
}

inline D3D12_DRED_VERSION getDX12(DRED_VERSION v) noexcept {
    static_assert(sizeof(D3D12_DRED_VERSION) == sizeof(DRED_VERSION));
    static_assert(alignof(D3D12_DRED_VERSION) == alignof(DRED_VERSION));
    return *alias_cast<D3D12_DRED_VERSION*>(&v);
}

inline D3D12_DRED_FLAGS getDX12(DRED_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_DRED_FLAGS) == sizeof(DRED_FLAGS));
    static_assert(alignof(D3D12_DRED_FLAGS) == alignof(DRED_FLAGS));
    return *alias_cast<D3D12_DRED_FLAGS*>(&v);
}

inline D3D12_DRED_ENABLEMENT getDX12(DRED_ENABLEMENT v) noexcept {
    static_assert(sizeof(D3D12_DRED_ENABLEMENT) == sizeof(DRED_ENABLEMENT));
    static_assert(alignof(D3D12_DRED_ENABLEMENT) == alignof(DRED_ENABLEMENT));
    return *alias_cast<D3D12_DRED_ENABLEMENT*>(&v);
}

inline D3D12_DEVICE_REMOVED_EXTENDED_DATA getDX12(const DEVICE_REMOVED_EXTENDED_DATA& v) noexcept {
    static_assert(sizeof(D3D12_DEVICE_REMOVED_EXTENDED_DATA) == sizeof(DEVICE_REMOVED_EXTENDED_DATA));
    static_assert(alignof(D3D12_DEVICE_REMOVED_EXTENDED_DATA) == alignof(DEVICE_REMOVED_EXTENDED_DATA));
    return *alias_cast<const D3D12_DEVICE_REMOVED_EXTENDED_DATA*>(&v);
}

inline D3D12_DRED_ALLOCATION_TYPE getDX12(DRED_ALLOCATION_TYPE v) noexcept {
    static_assert(sizeof(D3D12_DRED_ALLOCATION_TYPE) == sizeof(DRED_ALLOCATION_TYPE));
    static_assert(alignof(D3D12_DRED_ALLOCATION_TYPE) == alignof(DRED_ALLOCATION_TYPE));
    return *alias_cast<D3D12_DRED_ALLOCATION_TYPE*>(&v);
}

inline D3D12_DRED_ALLOCATION_NODE getDX12(const DRED_ALLOCATION_NODE& v) noexcept {
    static_assert(sizeof(D3D12_DRED_ALLOCATION_NODE) == sizeof(DRED_ALLOCATION_NODE));
    static_assert(alignof(D3D12_DRED_ALLOCATION_NODE) == alignof(DRED_ALLOCATION_NODE));
    return *alias_cast<const D3D12_DRED_ALLOCATION_NODE*>(&v);
}

inline D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT getDX12(const DRED_AUTO_BREADCRUMBS_OUTPUT& v) noexcept {
    static_assert(sizeof(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT) == sizeof(DRED_AUTO_BREADCRUMBS_OUTPUT));
    static_assert(alignof(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT) == alignof(DRED_AUTO_BREADCRUMBS_OUTPUT));
    return *alias_cast<const D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT*>(&v);
}

inline D3D12_DRED_PAGE_FAULT_OUTPUT getDX12(const DRED_PAGE_FAULT_OUTPUT& v) noexcept {
    static_assert(sizeof(D3D12_DRED_PAGE_FAULT_OUTPUT) == sizeof(DRED_PAGE_FAULT_OUTPUT));
    static_assert(alignof(D3D12_DRED_PAGE_FAULT_OUTPUT) == alignof(DRED_PAGE_FAULT_OUTPUT));
    return *alias_cast<const D3D12_DRED_PAGE_FAULT_OUTPUT*>(&v);
}

inline D3D12_DEVICE_REMOVED_EXTENDED_DATA1 getDX12(const DEVICE_REMOVED_EXTENDED_DATA1& v) noexcept {
    static_assert(sizeof(D3D12_DEVICE_REMOVED_EXTENDED_DATA1) == sizeof(DEVICE_REMOVED_EXTENDED_DATA1));
    static_assert(alignof(D3D12_DEVICE_REMOVED_EXTENDED_DATA1) == alignof(DEVICE_REMOVED_EXTENDED_DATA1));
    return *alias_cast<const D3D12_DEVICE_REMOVED_EXTENDED_DATA1*>(&v);
}

inline D3D12_VERSIONED_DEVICE_REMOVED_EXTENDED_DATA getDX12(const VERSIONED_DEVICE_REMOVED_EXTENDED_DATA& v) noexcept {
    static_assert(sizeof(D3D12_VERSIONED_DEVICE_REMOVED_EXTENDED_DATA) == sizeof(VERSIONED_DEVICE_REMOVED_EXTENDED_DATA));
    static_assert(alignof(D3D12_VERSIONED_DEVICE_REMOVED_EXTENDED_DATA) == alignof(VERSIONED_DEVICE_REMOVED_EXTENDED_DATA));
    return *alias_cast<const D3D12_VERSIONED_DEVICE_REMOVED_EXTENDED_DATA*>(&v);
}

inline D3D12_BACKGROUND_PROCESSING_MODE getDX12(BACKGROUND_PROCESSING_MODE v) noexcept {
    static_assert(sizeof(D3D12_BACKGROUND_PROCESSING_MODE) == sizeof(BACKGROUND_PROCESSING_MODE));
    static_assert(alignof(D3D12_BACKGROUND_PROCESSING_MODE) == alignof(BACKGROUND_PROCESSING_MODE));
    return *alias_cast<D3D12_BACKGROUND_PROCESSING_MODE*>(&v);
}

inline D3D12_MEASUREMENTS_ACTION getDX12(MEASUREMENTS_ACTION v) noexcept {
    static_assert(sizeof(D3D12_MEASUREMENTS_ACTION) == sizeof(MEASUREMENTS_ACTION));
    static_assert(alignof(D3D12_MEASUREMENTS_ACTION) == alignof(MEASUREMENTS_ACTION));
    return *alias_cast<D3D12_MEASUREMENTS_ACTION*>(&v);
}

inline D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE getDX12(RENDER_PASS_BEGINNING_ACCESS_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE) == sizeof(RENDER_PASS_BEGINNING_ACCESS_TYPE));
    static_assert(alignof(D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE) == alignof(RENDER_PASS_BEGINNING_ACCESS_TYPE));
    return *alias_cast<D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE*>(&v);
}

inline D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS getDX12(const RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS) == sizeof(RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS));
    static_assert(alignof(D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS) == alignof(RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS));
    return *alias_cast<const D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS*>(&v);
}

inline D3D12_RENDER_PASS_BEGINNING_ACCESS getDX12(const RENDER_PASS_BEGINNING_ACCESS& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_BEGINNING_ACCESS) == sizeof(RENDER_PASS_BEGINNING_ACCESS));
    static_assert(alignof(D3D12_RENDER_PASS_BEGINNING_ACCESS) == alignof(RENDER_PASS_BEGINNING_ACCESS));
    return *alias_cast<const D3D12_RENDER_PASS_BEGINNING_ACCESS*>(&v);
}

inline D3D12_RENDER_PASS_ENDING_ACCESS_TYPE getDX12(RENDER_PASS_ENDING_ACCESS_TYPE v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_ENDING_ACCESS_TYPE) == sizeof(RENDER_PASS_ENDING_ACCESS_TYPE));
    static_assert(alignof(D3D12_RENDER_PASS_ENDING_ACCESS_TYPE) == alignof(RENDER_PASS_ENDING_ACCESS_TYPE));
    return *alias_cast<D3D12_RENDER_PASS_ENDING_ACCESS_TYPE*>(&v);
}

inline D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS getDX12(const RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS) == sizeof(RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS));
    static_assert(alignof(D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS) == alignof(RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS));
    return *alias_cast<const D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS*>(&v);
}

inline D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS getDX12(const RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS) == sizeof(RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS));
    static_assert(alignof(D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS) == alignof(RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS));
    return *alias_cast<const D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS*>(&v);
}

inline D3D12_RENDER_PASS_ENDING_ACCESS getDX12(const RENDER_PASS_ENDING_ACCESS& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_ENDING_ACCESS) == sizeof(RENDER_PASS_ENDING_ACCESS));
    static_assert(alignof(D3D12_RENDER_PASS_ENDING_ACCESS) == alignof(RENDER_PASS_ENDING_ACCESS));
    return *alias_cast<const D3D12_RENDER_PASS_ENDING_ACCESS*>(&v);
}

inline D3D12_RENDER_PASS_RENDER_TARGET_DESC getDX12(const RENDER_PASS_RENDER_TARGET_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_RENDER_TARGET_DESC) == sizeof(RENDER_PASS_RENDER_TARGET_DESC));
    static_assert(alignof(D3D12_RENDER_PASS_RENDER_TARGET_DESC) == alignof(RENDER_PASS_RENDER_TARGET_DESC));
    return *alias_cast<const D3D12_RENDER_PASS_RENDER_TARGET_DESC*>(&v);
}

inline D3D12_RENDER_PASS_DEPTH_STENCIL_DESC getDX12(const RENDER_PASS_DEPTH_STENCIL_DESC& v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_DEPTH_STENCIL_DESC) == sizeof(RENDER_PASS_DEPTH_STENCIL_DESC));
    static_assert(alignof(D3D12_RENDER_PASS_DEPTH_STENCIL_DESC) == alignof(RENDER_PASS_DEPTH_STENCIL_DESC));
    return *alias_cast<const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC*>(&v);
}

inline D3D12_RENDER_PASS_FLAGS getDX12(RENDER_PASS_FLAGS v) noexcept {
    static_assert(sizeof(D3D12_RENDER_PASS_FLAGS) == sizeof(RENDER_PASS_FLAGS));
    static_assert(alignof(D3D12_RENDER_PASS_FLAGS) == alignof(RENDER_PASS_FLAGS));
    return *alias_cast<D3D12_RENDER_PASS_FLAGS*>(&v);
}

inline D3D12_DISPATCH_RAYS_DESC getDX12(const DISPATCH_RAYS_DESC& v) noexcept {
    static_assert(sizeof(D3D12_DISPATCH_RAYS_DESC) == sizeof(DISPATCH_RAYS_DESC));
    static_assert(alignof(D3D12_DISPATCH_RAYS_DESC) == alignof(DISPATCH_RAYS_DESC));
    return *alias_cast<const D3D12_DISPATCH_RAYS_DESC*>(&v);
}

inline D3D12_SUBRESOURCE_DATA getDX12(const SUBRESOURCE_DATA& v) noexcept {
    static_assert(sizeof(D3D12_SUBRESOURCE_DATA) == sizeof(SUBRESOURCE_DATA));
    static_assert(alignof(D3D12_SUBRESOURCE_DATA) == alignof(SUBRESOURCE_DATA));
    return *alias_cast<const D3D12_SUBRESOURCE_DATA*>(&v);
}

inline D3D12_MEMCPY_DEST getDX12(const MEMCPY_DEST& v) noexcept {
    static_assert(sizeof(D3D12_MEMCPY_DEST) == sizeof(MEMCPY_DEST));
    static_assert(alignof(D3D12_MEMCPY_DEST) == alignof(MEMCPY_DEST));
    return *alias_cast<const D3D12_MEMCPY_DEST*>(&v);
}

inline D3D12_AXIS_SHADING_RATE getDX12(AXIS_SHADING_RATE v) noexcept {
    static_assert(sizeof(D3D12_AXIS_SHADING_RATE) == sizeof(AXIS_SHADING_RATE));
    static_assert(alignof(D3D12_AXIS_SHADING_RATE) == alignof(AXIS_SHADING_RATE));
    return *alias_cast<D3D12_AXIS_SHADING_RATE*>(&v);
}

inline D3D12_SHADING_RATE getDX12(SHADING_RATE v) noexcept {
    static_assert(sizeof(D3D12_SHADING_RATE) == sizeof(SHADING_RATE));
    static_assert(alignof(D3D12_SHADING_RATE) == alignof(SHADING_RATE));
    return *alias_cast<D3D12_SHADING_RATE*>(&v);
}

inline D3D12_SHADING_RATE_COMBINER getDX12(SHADING_RATE_COMBINER v) noexcept {
    static_assert(sizeof(D3D12_SHADING_RATE_COMBINER) == sizeof(SHADING_RATE_COMBINER));
    static_assert(alignof(D3D12_SHADING_RATE_COMBINER) == alignof(SHADING_RATE_COMBINER));
    return *alias_cast<D3D12_SHADING_RATE_COMBINER*>(&v);
}

inline DXGI_SAMPLE_DESC getDXGI(const DISP_SAMPLE_DESC& v) noexcept {
    static_assert(sizeof(DXGI_SAMPLE_DESC) == sizeof(DISP_SAMPLE_DESC));
    static_assert(alignof(DXGI_SAMPLE_DESC) == alignof(DISP_SAMPLE_DESC));
    return *alias_cast<const DXGI_SAMPLE_DESC*>(&v);
}

}
