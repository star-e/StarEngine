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

struct ShaderStruct;

using ValueModel = std::variant<std::monostate, float4_, float3_, float2_, float1_, half4_, half3_, half2_, half1_, fixed4_, fixed3_, fixed2_, fixed1_, uint4_, uint3_, uint2_, uint1_, int4_, int3_, int2_, int1_, ShaderStruct>;

enum ValueBuilderFlags : uint32_t;

struct ShaderValue;
struct FloatRange;
struct HalfRange;

enum AttributeFlags : uint32_t;

namespace Unity {

enum UnityAttributeFlags : uint32_t;

} // namespace Unity

struct DefaultView_;

using ShaderResourceDataView = std::variant<DefaultView_, TextureView>;

struct Bounded_;
struct Unbounded_;

using Boundedness = std::variant<Bounded_, Unbounded_>;

struct AttributeDescriptor;
struct AttributeDatabase;
struct ShaderAttribute;

enum ModuleBuilderFlags : uint32_t;

struct AttributeKey;
struct AttributeUsage;
struct ShaderModule;
struct ShaderSemanticValue;
struct ShaderStageContent;
struct DescriptorSubrange;
struct DescriptorRange;
struct UnboundedDescriptor;
struct DescriptorList;
struct DescriptorCollection;
struct Constant;
struct ConstantBuffer;
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
