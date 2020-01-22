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
#include <StarCompiler/Graphics/SRenderFwd.h>

namespace Star {

namespace Graphics {

namespace Render {

namespace Shader {

struct HLSL_;
struct GLSL_;
struct Metal_;
struct UnityCG_;

using Language = std::variant<std::monostate, HLSL_, GLSL_, Metal_, UnityCG_>;

struct Content;

enum ShaderStageEnum : uint32_t;

struct OM_;
struct PS_;
struct GS_;
struct DS_;
struct TS_;
struct HS_;
struct VS_;
struct CS_;

using ShaderStageType = std::variant<OM_, PS_, GS_, DS_, TS_, HS_, VS_, CS_>;

struct ShaderStruct;

using ValueModel = std::variant<std::monostate, float4, float3, float2, float1, half4, half3, half2, half1, fixed4, fixed3, fixed2, fixed1, uint4, uint3, uint2, uint1, int4, int3, int2, int1, ShaderStruct>;

enum ValueBuilderFlags : uint32_t;

struct ShaderValue;
struct InputPatch_;
struct OutputPatch_;
struct ConstantBuffer_;
struct Buffer_;
struct ByteAddressBuffer_;
struct StructuredBuffer_;
struct AppendStructuredBuffer_;
struct ConsumeStructuredBuffer_;
struct Texture1D_;
struct Texture1DArray_;
struct Texture2D_;
struct Texture2DArray_;
struct Texture2DMS_;
struct Texture2DMSArray_;
struct Texture3D_;
struct TextureCube_;
struct TextureCubeArray_;
struct RWBuffer_;
struct RWByteAddressBuffer_;
struct RWStructuredBuffer_;
struct RWTexture1D_;
struct RWTexture1DArray_;
struct RWTexture2D_;
struct RWTexture2DArray_;
struct RWTexture3D_;
struct SamplerState_;
struct FloatRange;
struct HalfRange;

using AttributeType = std::variant<matrix, float4, uint4, int4, float2, uint2, int2, half4, FloatRange, float1, uint1, int1, half2, fixed4, HalfRange, half1, InputPatch_, OutputPatch_, Buffer_, ByteAddressBuffer_, StructuredBuffer_, Texture1D_, Texture1DArray_, Texture2D_, Texture2DArray_, Texture2DMS_, Texture2DMSArray_, Texture3D_, TextureCube_, TextureCubeArray_, AppendStructuredBuffer_, ConsumeStructuredBuffer_, RWBuffer_, RWByteAddressBuffer_, RWStructuredBuffer_, RWTexture1D_, RWTexture1DArray_, RWTexture2D_, RWTexture2DArray_, RWTexture3D_, SamplerState_>;

enum AttributeFlags : uint32_t;

namespace Unity {

enum UnityAttributeFlags : uint32_t;

} // namespace Unity

struct DefaultView_;

using ShaderResourceDataView = std::variant<DefaultView_, TextureView>;

struct ShaderAttribute;

enum ModuleBuilderFlags : uint32_t;

struct AttributeKey;
struct AttributeUsage;
struct ShaderModule;
struct ShaderSemanticValue;
struct ShaderStageContent;

using DescriptorType = std::variant<CBV_, UAV_, SRV_, SSV_>;

struct RangeUnbounded;
struct RangeBounded;

using DescriptorRange = std::variant<RangeBounded, RangeUnbounded>;

struct ShaderConstant;
struct ShaderConstantBuffer;

using DescriptorCBV = std::variant<ConstantBuffer_, Buffer_, ByteAddressBuffer_, StructuredBuffer_, DescriptorRange>;
using DescriptorSRV = std::variant<Texture1D_, Texture1DArray_, Texture2D_, Texture2DArray_, Texture2DMS_, Texture2DMSArray_, Texture3D_, TextureCube_, TextureCubeArray_, DescriptorRange>;
using DescriptorUAV = std::variant<AppendStructuredBuffer_, ConsumeStructuredBuffer_, RWBuffer_, RWByteAddressBuffer_, RWStructuredBuffer_, RWTexture1D_, RWTexture1DArray_, RWTexture2D_, RWTexture2DArray_, RWTexture3D_, DescriptorRange>;
using DescriptorSSV = std::variant<SamplerState_, DescriptorRange>;
using DescriptorModel = std::variant<DescriptorCBV, DescriptorUAV, DescriptorSRV, DescriptorSSV>;

struct Descriptor;
struct DescriptorTable;
struct DescriptorCapacity;
struct DescriptorTableCapacity;
struct DescriptorIndex;
struct MergeStages_;

using StageOptimization = std::variant<std::monostate, MergeStages_>;

struct RootSignatureOptimizeStrategy;
struct Zero_;
struct One_;
struct SrcColor_;
struct InvSrcColor_;
struct SrcAlpha_;
struct InvSrcAlpha_;
struct DstAlpha_;
struct InvDstAlpha_;
struct DstColor_;
struct InvDstColor_;
struct SrcAlphaSat_;
struct BlendFactor_;
struct InvBlendFactor_;
struct Src1Color_;
struct InvSrc1Color_;
struct Src1Alpha_;
struct InvSrc1Alpha_;

using BlendType = std::variant<Zero_, One_, SrcColor_, InvSrcColor_, SrcAlpha_, InvSrcAlpha_, DstAlpha_, InvDstAlpha_, DstColor_, InvDstColor_, SrcAlphaSat_, BlendFactor_, InvBlendFactor_, Src1Color_, InvSrc1Color_, Src1Alpha_, InvSrc1Alpha_>;

struct Add_;
struct Subtract_;
struct RevSubtract_;
struct Min_;
struct Max_;

using BlendOp = std::variant<Add_, Subtract_, RevSubtract_, Min_, Max_>;

struct Clear_;
struct Set_;
struct Copy_;
struct CopyInverted_;
struct NoOp_;
struct Invert_;
struct And_;
struct Nand_;
struct Or_;
struct Nor_;
struct Xor_;
struct Equiv_;
struct AndReverse_;
struct AndInverted_;
struct OrReverse_;
struct OrInverted_;

using LogicalOp = std::variant<Clear_, Set_, Copy_, CopyInverted_, NoOp_, Invert_, And_, Nand_, Or_, Nor_, Xor_, Equiv_, AndReverse_, AndInverted_, OrReverse_, OrInverted_>;

namespace DSL {

enum ColorWrite : uint32_t;

} // namespace DSL

struct Blend;
struct BlendState;
struct Wireframe_;
struct Solid_;

using FillMode = std::variant<Wireframe_, Solid_>;

struct None_;
struct Front_;
struct Back_;

using CullMode = std::variant<None_, Front_, Back_>;

struct RasterizerState;
struct Never_;
struct Less_;
struct Equal_;
struct LessEqual_;
struct Greater_;
struct NotEqual_;
struct GreaterEqual_;
struct Always_;

using ComparisonFunc = std::variant<Never_, Less_, Equal_, LessEqual_, Greater_, NotEqual_, GreaterEqual_, Always_>;

struct Keep_;
struct Replace_;
struct IncrSat_;
struct DecrSat_;
struct Incr_;
struct Decr_;

using StencilOp = std::variant<Keep_, Zero_, Replace_, IncrSat_, DecrSat_, Invert_, Incr_, Decr_>;

struct StencilOpState;
struct DepthStencilState;
struct PipelineState;
struct PerVertexData_;
struct PerInstanceData_;

using InputClassification = std::variant<PerVertexData_, PerInstanceData_>;

struct InputElement;
struct Disabled_;
struct FFFF_;
struct FFFFFFFF_;

using IndexBufferStripCutValue = std::variant<Disabled_, FFFF_, FFFFFFFF_>;

struct Point_;
struct Line_;
struct Triangle_;
struct Patch_;

using PrimitiveTopologyType = std::variant<Point_, Line_, Triangle_, Patch_>;

struct InputLayoutState;

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
