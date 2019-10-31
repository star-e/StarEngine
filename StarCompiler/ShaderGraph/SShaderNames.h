// Copyright (C) 2019 star.engine at outlook dot com
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
#include <StarCompiler/ShaderGraph/SShaderFwd.h>
#include <Star/Graphics/SShaderNames.h>
#include <Star/Graphics/SRenderNames.h>
#include <StarCompiler/Graphics/SRenderNames.h>

namespace Star {

namespace Graphics {

namespace Render {

namespace Shader {

inline const char* getName(const HLSL_& v) noexcept { return "HLSL"; }
inline const char* getName(const GLSL_& v) noexcept { return "GLSL"; }
inline const char* getName(const Metal_& v) noexcept { return "Metal"; }
inline const char* getName(const UnityCG_& v) noexcept { return "UnityCG"; }
inline const char* getName(const Content& v) noexcept { return "Content"; }
inline const char* getName(const OM_& v) noexcept { return "OM"; }
inline const char* getName(const PS_& v) noexcept { return "PS"; }
inline const char* getName(const GS_& v) noexcept { return "GS"; }
inline const char* getName(const DS_& v) noexcept { return "DS"; }
inline const char* getName(const TS_& v) noexcept { return "TS"; }
inline const char* getName(const HS_& v) noexcept { return "HS"; }
inline const char* getName(const VS_& v) noexcept { return "VS"; }
inline const char* getName(const CS_& v) noexcept { return "CS"; }
inline const char* getName(RootAccessEnum e) noexcept {
    switch(e) {
    case RA_All: return "RA_All";
    case RA_PS: return "RA_PS";
    case RA_GS: return "RA_GS";
    case RA_DS: return "RA_DS";
    case RA_HS: return "RA_HS";
    case RA_VS: return "RA_VS";
    case RA_Count: return "RA_Count";
    }
    return "";
}
inline const char* getName(const ShaderStruct& v) noexcept { return "ShaderStruct"; }
inline const char* getName(const ShaderValue& v) noexcept { return "ShaderValue"; }
inline const char* getName(const InputPatch_& v) noexcept { return "InputPatch"; }
inline const char* getName(const OutputPatch_& v) noexcept { return "OutputPatch"; }
inline const char* getName(const ConstantBuffer_& v) noexcept { return "ConstantBuffer"; }
inline const char* getName(const Buffer_& v) noexcept { return "Buffer"; }
inline const char* getName(const ByteAddressBuffer_& v) noexcept { return "ByteAddressBuffer"; }
inline const char* getName(const StructuredBuffer_& v) noexcept { return "StructuredBuffer"; }
inline const char* getName(const AppendStructuredBuffer_& v) noexcept { return "AppendStructuredBuffer"; }
inline const char* getName(const ConsumeStructuredBuffer_& v) noexcept { return "ConsumeStructuredBuffer"; }
inline const char* getName(const Texture1D_& v) noexcept { return "Texture1D"; }
inline const char* getName(const Texture1DArray_& v) noexcept { return "Texture1DArray"; }
inline const char* getName(const Texture2D_& v) noexcept { return "Texture2D"; }
inline const char* getName(const Texture2DArray_& v) noexcept { return "Texture2DArray"; }
inline const char* getName(const Texture2DMS_& v) noexcept { return "Texture2DMS"; }
inline const char* getName(const Texture2DMSArray_& v) noexcept { return "Texture2DMSArray"; }
inline const char* getName(const Texture3D_& v) noexcept { return "Texture3D"; }
inline const char* getName(const TextureCube_& v) noexcept { return "TextureCube"; }
inline const char* getName(const TextureCubeArray_& v) noexcept { return "TextureCubeArray"; }
inline const char* getName(const RWBuffer_& v) noexcept { return "RWBuffer"; }
inline const char* getName(const RWByteAddressBuffer_& v) noexcept { return "RWByteAddressBuffer"; }
inline const char* getName(const RWStructuredBuffer_& v) noexcept { return "RWStructuredBuffer"; }
inline const char* getName(const RWTexture1D_& v) noexcept { return "RWTexture1D"; }
inline const char* getName(const RWTexture1DArray_& v) noexcept { return "RWTexture1DArray"; }
inline const char* getName(const RWTexture2D_& v) noexcept { return "RWTexture2D"; }
inline const char* getName(const RWTexture2DArray_& v) noexcept { return "RWTexture2DArray"; }
inline const char* getName(const RWTexture3D_& v) noexcept { return "RWTexture3D"; }
inline const char* getName(const SamplerState_& v) noexcept { return "SamplerState"; }
inline const char* getName(const FloatRange& v) noexcept { return "FloatRange"; }
inline const char* getName(const HalfRange& v) noexcept { return "HalfRange"; }
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
inline const char* getName(const Table_& v) noexcept { return "Table"; }
inline const char* getName(const Constants_& v) noexcept { return "Constants"; }

inline const char* getName(const DefaultView_& v) noexcept { return "DefaultView"; }
inline const char* getName(const ShaderAttribute& v) noexcept { return "ShaderAttribute"; }
inline const char* getName(const AttributeKey& v) noexcept { return "AttributeKey"; }
inline const char* getName(const AttributeUsage& v) noexcept { return "AttributeUsage"; }
inline const char* getName(const ShaderModule& v) noexcept { return "ShaderModule"; }
inline const char* getName(const ShaderSemanticValue& v) noexcept { return "ShaderSemanticValue"; }
inline const char* getName(const ShaderStageContent& v) noexcept { return "ShaderStageContent"; }
inline const char* getName(const RangeUnbounded& v) noexcept { return "RangeUnbounded"; }
inline const char* getName(const RangeBounded& v) noexcept { return "RangeBounded"; }
inline const char* getName(const ShaderConstant& v) noexcept { return "ShaderConstant"; }
inline const char* getName(const ShaderConstantBuffer& v) noexcept { return "ShaderConstantBuffer"; }
inline const char* getName(const Descriptor& v) noexcept { return "Descriptor"; }
inline const char* getName(const DescriptorTable& v) noexcept { return "DescriptorTable"; }
inline const char* getName(const DescriptorCapacity& v) noexcept { return "DescriptorCapacity"; }
inline const char* getName(const DescriptorTableCapacity& v) noexcept { return "DescriptorTableCapacity"; }
inline const char* getName(const DescriptorIndex& v) noexcept { return "DescriptorIndex"; }
inline const char* getName(const MergeStages_& v) noexcept { return "MergeStages"; }
inline const char* getName(const RootSignatureOptimizeStrategy& v) noexcept { return "RootSignatureOptimizeStrategy"; }
inline const char* getName(const Zero_& v) noexcept { return "Zero"; }
inline const char* getName(const One_& v) noexcept { return "One"; }
inline const char* getName(const SrcColor_& v) noexcept { return "SrcColor"; }
inline const char* getName(const InvSrcColor_& v) noexcept { return "InvSrcColor"; }
inline const char* getName(const SrcAlpha_& v) noexcept { return "SrcAlpha"; }
inline const char* getName(const InvSrcAlpha_& v) noexcept { return "InvSrcAlpha"; }
inline const char* getName(const DstAlpha_& v) noexcept { return "DstAlpha"; }
inline const char* getName(const InvDstAlpha_& v) noexcept { return "InvDstAlpha"; }
inline const char* getName(const DstColor_& v) noexcept { return "DstColor"; }
inline const char* getName(const InvDstColor_& v) noexcept { return "InvDstColor"; }
inline const char* getName(const SrcAlphaSat_& v) noexcept { return "SrcAlphaSat"; }
inline const char* getName(const BlendFactor_& v) noexcept { return "BlendFactor"; }
inline const char* getName(const InvBlendFactor_& v) noexcept { return "InvBlendFactor"; }
inline const char* getName(const Src1Color_& v) noexcept { return "Src1Color"; }
inline const char* getName(const InvSrc1Color_& v) noexcept { return "InvSrc1Color"; }
inline const char* getName(const Src1Alpha_& v) noexcept { return "Src1Alpha"; }
inline const char* getName(const InvSrc1Alpha_& v) noexcept { return "InvSrc1Alpha"; }
inline const char* getName(const Add_& v) noexcept { return "Add"; }
inline const char* getName(const Subtract_& v) noexcept { return "Subtract"; }
inline const char* getName(const RevSubtract_& v) noexcept { return "RevSubtract"; }
inline const char* getName(const Min_& v) noexcept { return "Min"; }
inline const char* getName(const Max_& v) noexcept { return "Max"; }
inline const char* getName(const Clear_& v) noexcept { return "Clear"; }
inline const char* getName(const Set_& v) noexcept { return "Set"; }
inline const char* getName(const Copy_& v) noexcept { return "Copy"; }
inline const char* getName(const CopyInverted_& v) noexcept { return "CopyInverted"; }
inline const char* getName(const NoOp_& v) noexcept { return "NoOp"; }
inline const char* getName(const Invert_& v) noexcept { return "Invert"; }
inline const char* getName(const And_& v) noexcept { return "And"; }
inline const char* getName(const Nand_& v) noexcept { return "Nand"; }
inline const char* getName(const Or_& v) noexcept { return "Or"; }
inline const char* getName(const Nor_& v) noexcept { return "Nor"; }
inline const char* getName(const Xor_& v) noexcept { return "Xor"; }
inline const char* getName(const Equiv_& v) noexcept { return "Equiv"; }
inline const char* getName(const AndReverse_& v) noexcept { return "AndReverse"; }
inline const char* getName(const AndInverted_& v) noexcept { return "AndInverted"; }
inline const char* getName(const OrReverse_& v) noexcept { return "OrReverse"; }
inline const char* getName(const OrInverted_& v) noexcept { return "OrInverted"; }

inline const char* getName(const Blend& v) noexcept { return "Blend"; }
inline const char* getName(const BlendState& v) noexcept { return "BlendState"; }
inline const char* getName(const Wireframe_& v) noexcept { return "Wireframe"; }
inline const char* getName(const Solid_& v) noexcept { return "Solid"; }
inline const char* getName(const None_& v) noexcept { return "None"; }
inline const char* getName(const Front_& v) noexcept { return "Front"; }
inline const char* getName(const Back_& v) noexcept { return "Back"; }
inline const char* getName(const RasterizerState& v) noexcept { return "RasterizerState"; }
inline const char* getName(const Never_& v) noexcept { return "Never"; }
inline const char* getName(const Less_& v) noexcept { return "Less"; }
inline const char* getName(const Equal_& v) noexcept { return "Equal"; }
inline const char* getName(const LessEqual_& v) noexcept { return "LessEqual"; }
inline const char* getName(const Greater_& v) noexcept { return "Greater"; }
inline const char* getName(const NotEqual_& v) noexcept { return "NotEqual"; }
inline const char* getName(const GreaterEqual_& v) noexcept { return "GreaterEqual"; }
inline const char* getName(const Always_& v) noexcept { return "Always"; }
inline const char* getName(const Keep_& v) noexcept { return "Keep"; }
inline const char* getName(const Replace_& v) noexcept { return "Replace"; }
inline const char* getName(const IncrSat_& v) noexcept { return "IncrSat"; }
inline const char* getName(const DecrSat_& v) noexcept { return "DecrSat"; }
inline const char* getName(const Incr_& v) noexcept { return "Incr"; }
inline const char* getName(const Decr_& v) noexcept { return "Decr"; }
inline const char* getName(const StencilOpState& v) noexcept { return "StencilOpState"; }
inline const char* getName(const DepthStencilState& v) noexcept { return "DepthStencilState"; }
inline const char* getName(const PipelineState& v) noexcept { return "PipelineState"; }
inline const char* getName(const PerVertexData_& v) noexcept { return "PerVertexData"; }
inline const char* getName(const PerInstanceData_& v) noexcept { return "PerInstanceData"; }
inline const char* getName(const InputElement& v) noexcept { return "InputElement"; }
inline const char* getName(const Disabled_& v) noexcept { return "Disabled"; }
inline const char* getName(const FFFF_& v) noexcept { return "FFFF"; }
inline const char* getName(const FFFFFFFF_& v) noexcept { return "FFFFFFFF"; }
inline const char* getName(const Point_& v) noexcept { return "Point"; }
inline const char* getName(const Line_& v) noexcept { return "Line"; }
inline const char* getName(const Triangle_& v) noexcept { return "Triangle"; }
inline const char* getName(const Patch_& v) noexcept { return "Patch"; }
inline const char* getName(const InputLayoutState& v) noexcept { return "InputLayoutState"; }
inline const char* getName(const AttributeCollection& v) noexcept { return "AttributeCollection"; }
inline const char* getName(const DrawCall& v) noexcept { return "DrawCall"; }
inline const char* getName(const DrawCallQueue& v) noexcept { return "DrawCallQueue"; }
inline const char* getName(const UnorderedSubmissions& v) noexcept { return "UnorderedSubmissions"; }
inline const char* getName(const PassSubmissions& v) noexcept { return "PassSubmissions"; }

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
