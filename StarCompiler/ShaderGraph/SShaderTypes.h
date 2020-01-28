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
#include <StarCompiler/ShaderGraph/SShaderFwd.h>
#include <Star/Graphics/SRenderTypes.h>
#include <StarCompiler/Graphics/SRenderTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

namespace Shader {

struct HLSL_ {} static constexpr HLSL;
struct GLSL_ {} static constexpr GLSL;
struct Metal_ {} static constexpr Metal;
struct UnityCG_ {} static constexpr UnityCG;

using Language = std::variant<std::monostate, HLSL_, GLSL_, Metal_, UnityCG_>;

struct Content {
    Content() = default;
    Content(std::string content, Language variant)
        : mContent(std::move(content))
        , mVariant(std::move(variant))
    {}
    Content(std::string content)
        : mContent(std::move(content))
    {}
    std::string mContent;
    Language mVariant;
};

enum ShaderStageEnum : uint32_t {
    CS_In = 1 << 0,
    CS_Out = 1 << 1,
    VS_In = 1 << 2,
    VS_Out = 1 << 3,
    HS_In = 1 << 4,
    HS_Out = 1 << 5,
    TS_In = 1 << 6,
    TS_Out = 1 << 7,
    DS_In = 1 << 8,
    DS_Out = 1 << 9,
    GS_In = 1 << 10,
    GS_Out = 1 << 11,
    PS_In = 1 << 12,
    PS_Out = 1 << 13,
    OM_In = 1 << 14,
    OM_Out = 1 << 15,
    VS_Interp = 1 << 16,
    HS_Interp = 1 << 17,
    TS_Interp = 1 << 18,
    DS_Interp = 1 << 19,
    GS_Interp = 1 << 20,
    PS_Interp = 1 << 21,
    OM_Interp = 1 << 22,
    CS_SV = CS_In | CS_Out,
    VS_SV = VS_In | VS_Out,
    HS_SV = HS_In | HS_Out,
    TS_SV = TS_In | TS_Out,
    DS_SV = DS_In | DS_Out,
    GS_SV = GS_In | GS_Out,
    PS_SV = PS_In | PS_Out,
    SS_SV = VS_SV | HS_SV | TS_SV | DS_SV | GS_SV | PS_SV,
    VS_Value = VS_Interp | VS_Out,
    HS_Value = HS_Interp | HS_Out,
    TS_Value = TS_Interp | TS_Out,
    DS_Value = DS_Interp | DS_Out,
    GS_Value = GS_Interp | GS_Out,
    PS_Value = PS_Interp | PS_Out,
    OM_Value = OM_Interp | OM_Out,
    SS_Value = VS_Value | HS_Value | TS_Value | DS_Value | GS_Value | PS_Value,
    CS_All = CS_In | CS_Out,
    VS_All = VS_In | VS_Out | VS_Interp,
    HS_All = HS_In | HS_Out | HS_Interp,
    TS_All = TS_In | TS_Out | TS_Interp,
    DS_All = DS_In | DS_Out | DS_Interp,
    GS_All = GS_In | GS_Out | GS_Interp,
    PS_All = PS_In | PS_Out | PS_Interp,
    OM_All = OM_In | OM_Out | OM_Interp,
    SS_All = VS_All | HS_All | TS_All | DS_All | GS_All | PS_All,
};

struct ShaderStruct {
    std::string mName;
};

inline bool operator==(const ShaderStruct&lhs, const ShaderStruct&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName) ==
        std::forward_as_tuple(rhs.mName);
}
inline bool operator!=(const ShaderStruct&lhs, const ShaderStruct&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const ShaderStruct&lhs, const ShaderStruct&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName) <
        std::forward_as_tuple(rhs.mName);
}

using ValueModel = std::variant<std::monostate, float4, float3, float2, float1, half4, half3, half2, half1, fixed4, fixed3, fixed2, fixed1, uint4, uint3, uint2, uint1, int4, int3, int2, int1, ShaderStruct>;

inline bool operator<(const ValueModel& lhs, const ValueModel& rhs) noexcept {
    return lhs.index() < rhs.index();
}

enum ValueBuilderFlags : uint32_t {
    DefaultValue = 0,
    NoDeclare = 1 << 0,
};

struct ShaderValue {
    ShaderValue() = default;
    ShaderValue(std::string name, ValueModel value)
        : mName(std::move(name))
        , mValue(std::move(value))
    {}
    ShaderValue(std::string name, ValueModel value, SemanticType semantic)
        : mName(std::move(name))
        , mValue(std::move(value))
        , mSemantic(std::move(semantic))
    {}
    ShaderValue(std::string name, ValueModel value, ValueBuilderFlags builderFlags)
        : mName(std::move(name))
        , mValue(std::move(value))
        , mBuilderFlags(std::move(builderFlags))
    {}
    ShaderValue(std::string name, ValueModel value, SemanticType semantic, ValueBuilderFlags builderFlags)
        : mName(std::move(name))
        , mValue(std::move(value))
        , mSemantic(std::move(semantic))
        , mBuilderFlags(std::move(builderFlags))
    {}
    std::string mName;
    ValueModel mValue;
    SemanticType mSemantic;
    ValueBuilderFlags mBuilderFlags = DefaultValue;
};

struct InputPatch_ {} static constexpr InputPatch;
inline bool operator==(const InputPatch_&, const InputPatch_&) noexcept { return true; }
inline bool operator!=(const InputPatch_&, const InputPatch_&) noexcept { return false; }
struct OutputPatch_ {} static constexpr OutputPatch;
inline bool operator==(const OutputPatch_&, const OutputPatch_&) noexcept { return true; }
inline bool operator!=(const OutputPatch_&, const OutputPatch_&) noexcept { return false; }
struct ConstantBuffer_ {} static constexpr ConstantBuffer;
inline bool operator<(const ConstantBuffer_&, const ConstantBuffer_&) noexcept { return false; }
struct Buffer_ {} static constexpr Buffer;
inline bool operator==(const Buffer_&, const Buffer_&) noexcept { return true; }
inline bool operator!=(const Buffer_&, const Buffer_&) noexcept { return false; }
inline bool operator<(const Buffer_&, const Buffer_&) noexcept { return false; }
struct ByteAddressBuffer_ {} static constexpr ByteAddressBuffer;
inline bool operator==(const ByteAddressBuffer_&, const ByteAddressBuffer_&) noexcept { return true; }
inline bool operator!=(const ByteAddressBuffer_&, const ByteAddressBuffer_&) noexcept { return false; }
inline bool operator<(const ByteAddressBuffer_&, const ByteAddressBuffer_&) noexcept { return false; }
struct StructuredBuffer_ {} static constexpr StructuredBuffer;
inline bool operator==(const StructuredBuffer_&, const StructuredBuffer_&) noexcept { return true; }
inline bool operator!=(const StructuredBuffer_&, const StructuredBuffer_&) noexcept { return false; }
inline bool operator<(const StructuredBuffer_&, const StructuredBuffer_&) noexcept { return false; }
struct AppendStructuredBuffer_ {} static constexpr AppendStructuredBuffer;
inline bool operator==(const AppendStructuredBuffer_&, const AppendStructuredBuffer_&) noexcept { return true; }
inline bool operator!=(const AppendStructuredBuffer_&, const AppendStructuredBuffer_&) noexcept { return false; }
inline bool operator<(const AppendStructuredBuffer_&, const AppendStructuredBuffer_&) noexcept { return false; }
struct ConsumeStructuredBuffer_ {} static constexpr ConsumeStructuredBuffer;
inline bool operator==(const ConsumeStructuredBuffer_&, const ConsumeStructuredBuffer_&) noexcept { return true; }
inline bool operator!=(const ConsumeStructuredBuffer_&, const ConsumeStructuredBuffer_&) noexcept { return false; }
inline bool operator<(const ConsumeStructuredBuffer_&, const ConsumeStructuredBuffer_&) noexcept { return false; }
struct Texture1D_ {} static constexpr Texture1D;
inline bool operator==(const Texture1D_&, const Texture1D_&) noexcept { return true; }
inline bool operator!=(const Texture1D_&, const Texture1D_&) noexcept { return false; }
inline bool operator<(const Texture1D_&, const Texture1D_&) noexcept { return false; }
struct Texture1DArray_ {} static constexpr Texture1DArray;
inline bool operator==(const Texture1DArray_&, const Texture1DArray_&) noexcept { return true; }
inline bool operator!=(const Texture1DArray_&, const Texture1DArray_&) noexcept { return false; }
inline bool operator<(const Texture1DArray_&, const Texture1DArray_&) noexcept { return false; }
struct Texture2D_ {} static constexpr Texture2D;
inline bool operator==(const Texture2D_&, const Texture2D_&) noexcept { return true; }
inline bool operator!=(const Texture2D_&, const Texture2D_&) noexcept { return false; }
inline bool operator<(const Texture2D_&, const Texture2D_&) noexcept { return false; }
struct Texture2DArray_ {} static constexpr Texture2DArray;
inline bool operator==(const Texture2DArray_&, const Texture2DArray_&) noexcept { return true; }
inline bool operator!=(const Texture2DArray_&, const Texture2DArray_&) noexcept { return false; }
inline bool operator<(const Texture2DArray_&, const Texture2DArray_&) noexcept { return false; }
struct Texture2DMS_ {} static constexpr Texture2DMS;
inline bool operator==(const Texture2DMS_&, const Texture2DMS_&) noexcept { return true; }
inline bool operator!=(const Texture2DMS_&, const Texture2DMS_&) noexcept { return false; }
inline bool operator<(const Texture2DMS_&, const Texture2DMS_&) noexcept { return false; }
struct Texture2DMSArray_ {} static constexpr Texture2DMSArray;
inline bool operator==(const Texture2DMSArray_&, const Texture2DMSArray_&) noexcept { return true; }
inline bool operator!=(const Texture2DMSArray_&, const Texture2DMSArray_&) noexcept { return false; }
inline bool operator<(const Texture2DMSArray_&, const Texture2DMSArray_&) noexcept { return false; }
struct Texture3D_ {} static constexpr Texture3D;
inline bool operator==(const Texture3D_&, const Texture3D_&) noexcept { return true; }
inline bool operator!=(const Texture3D_&, const Texture3D_&) noexcept { return false; }
inline bool operator<(const Texture3D_&, const Texture3D_&) noexcept { return false; }
struct TextureCube_ {} static constexpr TextureCube;
inline bool operator==(const TextureCube_&, const TextureCube_&) noexcept { return true; }
inline bool operator!=(const TextureCube_&, const TextureCube_&) noexcept { return false; }
inline bool operator<(const TextureCube_&, const TextureCube_&) noexcept { return false; }
struct TextureCubeArray_ {} static constexpr TextureCubeArray;
inline bool operator==(const TextureCubeArray_&, const TextureCubeArray_&) noexcept { return true; }
inline bool operator!=(const TextureCubeArray_&, const TextureCubeArray_&) noexcept { return false; }
inline bool operator<(const TextureCubeArray_&, const TextureCubeArray_&) noexcept { return false; }
struct RWBuffer_ {} static constexpr RWBuffer;
inline bool operator==(const RWBuffer_&, const RWBuffer_&) noexcept { return true; }
inline bool operator!=(const RWBuffer_&, const RWBuffer_&) noexcept { return false; }
inline bool operator<(const RWBuffer_&, const RWBuffer_&) noexcept { return false; }
struct RWByteAddressBuffer_ {} static constexpr RWByteAddressBuffer;
inline bool operator==(const RWByteAddressBuffer_&, const RWByteAddressBuffer_&) noexcept { return true; }
inline bool operator!=(const RWByteAddressBuffer_&, const RWByteAddressBuffer_&) noexcept { return false; }
inline bool operator<(const RWByteAddressBuffer_&, const RWByteAddressBuffer_&) noexcept { return false; }
struct RWStructuredBuffer_ {} static constexpr RWStructuredBuffer;
inline bool operator==(const RWStructuredBuffer_&, const RWStructuredBuffer_&) noexcept { return true; }
inline bool operator!=(const RWStructuredBuffer_&, const RWStructuredBuffer_&) noexcept { return false; }
inline bool operator<(const RWStructuredBuffer_&, const RWStructuredBuffer_&) noexcept { return false; }
struct RWTexture1D_ {} static constexpr RWTexture1D;
inline bool operator==(const RWTexture1D_&, const RWTexture1D_&) noexcept { return true; }
inline bool operator!=(const RWTexture1D_&, const RWTexture1D_&) noexcept { return false; }
inline bool operator<(const RWTexture1D_&, const RWTexture1D_&) noexcept { return false; }
struct RWTexture1DArray_ {} static constexpr RWTexture1DArray;
inline bool operator==(const RWTexture1DArray_&, const RWTexture1DArray_&) noexcept { return true; }
inline bool operator!=(const RWTexture1DArray_&, const RWTexture1DArray_&) noexcept { return false; }
inline bool operator<(const RWTexture1DArray_&, const RWTexture1DArray_&) noexcept { return false; }
struct RWTexture2D_ {} static constexpr RWTexture2D;
inline bool operator==(const RWTexture2D_&, const RWTexture2D_&) noexcept { return true; }
inline bool operator!=(const RWTexture2D_&, const RWTexture2D_&) noexcept { return false; }
inline bool operator<(const RWTexture2D_&, const RWTexture2D_&) noexcept { return false; }
struct RWTexture2DArray_ {} static constexpr RWTexture2DArray;
inline bool operator==(const RWTexture2DArray_&, const RWTexture2DArray_&) noexcept { return true; }
inline bool operator!=(const RWTexture2DArray_&, const RWTexture2DArray_&) noexcept { return false; }
inline bool operator<(const RWTexture2DArray_&, const RWTexture2DArray_&) noexcept { return false; }
struct RWTexture3D_ {} static constexpr RWTexture3D;
inline bool operator==(const RWTexture3D_&, const RWTexture3D_&) noexcept { return true; }
inline bool operator!=(const RWTexture3D_&, const RWTexture3D_&) noexcept { return false; }
inline bool operator<(const RWTexture3D_&, const RWTexture3D_&) noexcept { return false; }
struct SamplerState_ {} static constexpr SamplerState;
inline bool operator==(const SamplerState_&, const SamplerState_&) noexcept { return true; }
inline bool operator!=(const SamplerState_&, const SamplerState_&) noexcept { return false; }
inline bool operator<(const SamplerState_&, const SamplerState_&) noexcept { return false; }

struct FloatRange {
    float mValue = 0.0f;
    float mMin = 0.0f;
    float mMax = 1.0f;
};

inline bool operator==(const FloatRange&lhs, const FloatRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mValue, lhs.mMin, lhs.mMax) ==
        std::forward_as_tuple(rhs.mValue, rhs.mMin, rhs.mMax);
}
inline bool operator!=(const FloatRange&lhs, const FloatRange&rhs) noexcept {
    return !(lhs == rhs);
}

struct HalfRange {
    half mValue = half(0.0f);
    half mMin = half(0.0f);
    half mMax = half(1.0f);
};

inline bool operator==(const HalfRange&lhs, const HalfRange&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mValue, lhs.mMin, lhs.mMax) ==
        std::forward_as_tuple(rhs.mValue, rhs.mMin, rhs.mMax);
}
inline bool operator!=(const HalfRange&lhs, const HalfRange&rhs) noexcept {
    return !(lhs == rhs);
}

using AttributeType = std::variant<matrix, float4, uint4, int4, float2, uint2, int2, half4, FloatRange, float1, uint1, int1, half2, fixed4, HalfRange, half1, InputPatch_, OutputPatch_, Buffer_, ByteAddressBuffer_, StructuredBuffer_, Texture1D_, Texture1DArray_, Texture2D_, Texture2DArray_, Texture2DMS_, Texture2DMSArray_, Texture3D_, TextureCube_, TextureCubeArray_, AppendStructuredBuffer_, ConsumeStructuredBuffer_, RWBuffer_, RWByteAddressBuffer_, RWStructuredBuffer_, RWTexture1D_, RWTexture1DArray_, RWTexture2D_, RWTexture2DArray_, RWTexture3D_, SamplerState_>;

inline bool operator<(const AttributeType& lhs, const AttributeType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

enum AttributeFlags : uint32_t {
    NoFlags = 0,
    VisibleAll = 1 << 0,
    UnboundedSize = 1 << 1,
    RootConstant = 1 << 2,
    RootLevel = 1 << 3,
    CombinedSampler = 1 << 4,
    UnityFlagsOffset = 1 << 5,
};

namespace Unity {

enum UnityAttributeFlags : uint32_t {
    HideInInspector = 1 << 5,
    PerRendererData = 1 << 6,
    NoScaleOffset = 1 << 7,
    Normal = 1 << 8,
    HDR = 1 << 9,
    Gamma = 1 << 10,
    BuiltIn = 1 << 11,
    Global = 1 << 12,
    Declared = 1 << 13,
    TexScaleOffset = 1 << 14,
    SeparateSampler = 1 << 15,
    NoSampler = 1 << 16,
    PerMaterial = 1 << 17,
    PerDraw = 1 << 18,
};

} // namespace Unity

struct DefaultView_ {} static constexpr DefaultView;
inline bool operator==(const DefaultView_&, const DefaultView_&) noexcept { return true; }
inline bool operator!=(const DefaultView_&, const DefaultView_&) noexcept { return false; }
inline bool operator<(const DefaultView_&, const DefaultView_&) noexcept { return false; }

using ShaderResourceDataView = std::variant<DefaultView_, TextureView>;

struct ShaderAttribute {
    ShaderAttribute() = default;
    ShaderAttribute(std::string name, AttributeType type)
        : mName(std::move(name))
        , mType(std::move(type))
    {}
    ShaderAttribute(std::string name, AttributeType type, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, UpdateEnum updateFrequency)
        : mName(std::move(name))
        , mType(std::move(type))
        , mUpdateFrequency(std::move(updateFrequency))
    {}
    ShaderAttribute(std::string name, AttributeType type, UpdateEnum updateFrequency, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mUpdateFrequency(std::move(updateFrequency))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, UpdateEnum updateFrequency, ValueModel model)
        : mName(std::move(name))
        , mType(std::move(type))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
    {}
    ShaderAttribute(std::string name, AttributeType type, UpdateEnum updateFrequency, ValueModel model, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, ValueModel model)
        : mName(std::move(name))
        , mType(std::move(type))
        , mModel(std::move(model))
    {}
    ShaderAttribute(std::string name, AttributeType type, ValueModel model, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mModel(std::move(model))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, UpdateEnum updateFrequency)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, UpdateEnum updateFrequency, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, UpdateEnum updateFrequency, ValueModel model)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, UpdateEnum updateFrequency, ValueModel model, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, UpdateEnum updateFrequency)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mUpdateFrequency(std::move(updateFrequency))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, UpdateEnum updateFrequency, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mUpdateFrequency(std::move(updateFrequency))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, UpdateEnum updateFrequency, ValueModel model)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, UpdateEnum updateFrequency, ValueModel model, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data, UpdateEnum updateFrequency)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data, UpdateEnum updateFrequency, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data, UpdateEnum updateFrequency, ValueModel model)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
    {}
    ShaderAttribute(std::string name, AttributeType type, std::string defaultValue, ShaderResourceDataView data, UpdateEnum updateFrequency, ValueModel model, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDefaultValue(std::move(defaultValue))
        , mData(std::move(data))
        , mUpdateFrequency(std::move(updateFrequency))
        , mModel(std::move(model))
        , mFlags(std::move(flags))
    {}
    std::string mName;
    AttributeType mType;
    UpdateEnum mUpdateFrequency = PerBatch;
    uint32_t mFlags = 0;
    ValueModel mModel;
    ShaderResourceDataView mData;
    std::string mDefaultValue;
};

enum ModuleBuilderFlags : uint32_t {
    DefaultModule = 0,
    System = 1 << 0,
    Inline = 1 << 1,
};

struct AttributeKey {
    std::string mName;
    ShaderResourceDataView mData;
};

inline bool operator<(const AttributeKey&lhs, const AttributeKey&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName, lhs.mData) <
        std::forward_as_tuple(rhs.mName, rhs.mData);
}

struct AttributeUsage {
    std::string mName;
    AttributeType mType;
    ShaderResourceDataView mData;
};

inline bool operator==(const AttributeUsage&lhs, const AttributeUsage&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName, lhs.mType, lhs.mData) ==
        std::forward_as_tuple(rhs.mName, rhs.mType, rhs.mData);
}
inline bool operator!=(const AttributeUsage&lhs, const AttributeUsage&rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const AttributeUsage&lhs, const AttributeUsage&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mName, lhs.mType, lhs.mData) <
        std::forward_as_tuple(rhs.mName, rhs.mType, rhs.mData);
}

struct ShaderModule {
    std::string mName;
    IdentityMap<AttributeUsage> mAttributes;
    NameMap<ShaderValue> mOutputs;
    NameMap<ShaderValue> mInputs;
    OrderedVariantIDMap2<Content> mContents;
    ModuleBuilderFlags mBuilderFlags = DefaultModule;
};

struct ShaderSemanticValue {
    SemanticType mSemantic;
    ValueModel mValue;
    std::string mName;
};

inline bool operator<(const ShaderSemanticValue&lhs, const ShaderSemanticValue&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mSemantic, lhs.mValue, lhs.mName) <
        std::forward_as_tuple(rhs.mSemantic, rhs.mValue, rhs.mName);
}

struct ShaderStageContent {
    std::string mInputStruct;
    std::string mInputVariable;
    std::string mOutputStruct;
    std::string mOutputVariable;
    std::string mMain;
};

using DescriptorRangeType = std::variant<CBV_, UAV_, SRV_, SSV_>;

inline bool operator<(const DescriptorRangeType& lhs, const DescriptorRangeType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

inline bool operator==(const DescriptorRangeType& lhs, const DescriptorRangeType& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const DescriptorRangeType& lhs, const DescriptorRangeType& rhs) noexcept {
    return !(lhs == rhs);
}

struct DescriptorRegisterSpace {
    DescriptorRangeType mType;
    std::string mName;
    uint32_t mSpace = 0;
};

inline bool operator<(const DescriptorRegisterSpace&lhs, const DescriptorRegisterSpace&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mType, lhs.mName, lhs.mSpace) <
        std::forward_as_tuple(rhs.mType, rhs.mName, rhs.mSpace);
}

struct Bounded_ {} static constexpr Bounded;
struct Unbounded_ {} static constexpr Unbounded;

using Boundedness = std::variant<Bounded_, Unbounded_>;

inline bool operator<(const Boundedness& lhs, const Boundedness& rhs) noexcept {
    return lhs.index() < rhs.index();
}
using ShaderCBV = std::variant<ConstantBuffer_, Buffer_, ByteAddressBuffer_, StructuredBuffer_>;

inline bool operator<(const ShaderCBV& lhs, const ShaderCBV& rhs) noexcept {
    return lhs.index() < rhs.index();
}
using ShaderSRV = std::variant<Texture1D_, Texture1DArray_, Texture2D_, Texture2DArray_, Texture2DMS_, Texture2DMSArray_, Texture3D_, TextureCube_, TextureCubeArray_>;

inline bool operator<(const ShaderSRV& lhs, const ShaderSRV& rhs) noexcept {
    return lhs.index() < rhs.index();
}
using ShaderUAV = std::variant<AppendStructuredBuffer_, ConsumeStructuredBuffer_, RWBuffer_, RWByteAddressBuffer_, RWStructuredBuffer_, RWTexture1D_, RWTexture1DArray_, RWTexture2D_, RWTexture2DArray_, RWTexture3D_>;

inline bool operator<(const ShaderUAV& lhs, const ShaderUAV& rhs) noexcept {
    return lhs.index() < rhs.index();
}
using ShaderSSV = std::variant<SamplerState_>;

inline bool operator<(const ShaderSSV& lhs, const ShaderSSV& rhs) noexcept {
    return lhs.index() < rhs.index();
}
using ShaderDescriptor = std::variant<ShaderCBV, ShaderUAV, ShaderSRV, ShaderSSV>;

struct DescriptorValue {
    ShaderDescriptor mShaderDescriptor;
    Boundedness mBoundedness;
    std::string mName;
};

inline bool operator<(const DescriptorValue&lhs, const DescriptorValue&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mShaderDescriptor, lhs.mBoundedness, lhs.mName) <
        std::forward_as_tuple(rhs.mShaderDescriptor, rhs.mBoundedness, rhs.mName);
}

struct DescriptorSubrange {
    Set<DescriptorValue> mValues;
    uint32_t mCapacity = 0;
};

struct MaterialSource_ {} static constexpr MaterialSource;
struct LightSource_ {} static constexpr LightSource;
struct CameraSource_ {} static constexpr CameraSource;
struct EngineSource_ {} static constexpr EngineSource;

using DescriptorSource = std::variant<MaterialSource_, LightSource_, CameraSource_, EngineSource_>;

inline bool operator<(const DescriptorSource& lhs, const DescriptorSource& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct DescriptorRange {
    Map<DescriptorSource, DescriptorSubrange> mSubranges;
    uint32_t mMaxUnboundedSize = 0;
};

struct RootParameter {
    Map<DescriptorRegisterSpace, DescriptorRange> mRanges;
};

struct RangeUnbounded {};

struct RangeBounded {
    uint32_t mCount = 0;
};

using DescriptorArray = std::variant<RangeBounded, RangeUnbounded>;

inline bool operator<(const DescriptorArray& lhs, const DescriptorArray& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct ShaderConstant {
    bool mUnbounded = false;
    AttributeType mType;
    std::string mName;
};

inline bool operator<(const ShaderConstant&lhs, const ShaderConstant&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mUnbounded, lhs.mType, lhs.mName) <
        std::forward_as_tuple(rhs.mUnbounded, rhs.mType, rhs.mName);
}

struct ShaderConstantBuffer {
    IdentityMap<ShaderConstant> mValues;
};

using DescriptorCBV = std::variant<ConstantBuffer_, Buffer_, ByteAddressBuffer_, StructuredBuffer_, DescriptorArray>;
using DescriptorSRV = std::variant<Texture1D_, Texture1DArray_, Texture2D_, Texture2DArray_, Texture2DMS_, Texture2DMSArray_, Texture3D_, TextureCube_, TextureCubeArray_, DescriptorArray>;
using DescriptorUAV = std::variant<AppendStructuredBuffer_, ConsumeStructuredBuffer_, RWBuffer_, RWByteAddressBuffer_, RWStructuredBuffer_, RWTexture1D_, RWTexture1DArray_, RWTexture2D_, RWTexture2DArray_, RWTexture3D_, DescriptorArray>;
using DescriptorSSV = std::variant<SamplerState_, DescriptorArray>;
using DescriptorModel = std::variant<DescriptorCBV, DescriptorUAV, DescriptorSRV, DescriptorSSV>;

struct Descriptor {
    DescriptorRangeType mType;
    uint32_t mSpace = 0;
    DescriptorModel mModel;
    std::string mName;
};

inline bool operator<(const Descriptor&lhs, const Descriptor&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mType, lhs.mSpace, lhs.mModel, lhs.mName) <
        std::forward_as_tuple(rhs.mType, rhs.mSpace, rhs.mModel, rhs.mName);
}

struct DescriptorTable {
    IdentityMap<Descriptor> mDescriptors;
};

struct DescriptorCapacity {
    DescriptorRangeType mType;
    uint32_t mSpace = 0;
    DescriptorArray mCount = {};
};

inline bool operator<(const DescriptorCapacity&lhs, const DescriptorCapacity&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mType, lhs.mSpace, lhs.mCount) <
        std::forward_as_tuple(rhs.mType, rhs.mSpace, rhs.mCount);
}

struct DescriptorTableCapacity {
    IdentityMap<DescriptorCapacity> mNumDescriptors;
};

struct MergeStages_ {} static constexpr MergeStages;

using StageOptimization = std::variant<std::monostate, MergeStages_>;

struct RootSignatureOptimizeStrategy {
    StageOptimization mStageOptimization;
};

struct Zero_ {} static constexpr Zero;
struct One_ {} static constexpr One;
struct SrcColor_ {} static constexpr SrcColor;
struct InvSrcColor_ {} static constexpr InvSrcColor;
struct SrcAlpha_ {} static constexpr SrcAlpha;
struct InvSrcAlpha_ {} static constexpr InvSrcAlpha;
struct DstAlpha_ {} static constexpr DstAlpha;
struct InvDstAlpha_ {} static constexpr InvDstAlpha;
struct DstColor_ {} static constexpr DstColor;
struct InvDstColor_ {} static constexpr InvDstColor;
struct SrcAlphaSat_ {} static constexpr SrcAlphaSat;
struct BlendFactor_ {} static constexpr BlendFactor;
struct InvBlendFactor_ {} static constexpr InvBlendFactor;
struct Src1Color_ {} static constexpr Src1Color;
struct InvSrc1Color_ {} static constexpr InvSrc1Color;
struct Src1Alpha_ {} static constexpr Src1Alpha;
struct InvSrc1Alpha_ {} static constexpr InvSrc1Alpha;

using BlendType = std::variant<Zero_, One_, SrcColor_, InvSrcColor_, SrcAlpha_, InvSrcAlpha_, DstAlpha_, InvDstAlpha_, DstColor_, InvDstColor_, SrcAlphaSat_, BlendFactor_, InvBlendFactor_, Src1Color_, InvSrc1Color_, Src1Alpha_, InvSrc1Alpha_>;

inline bool operator<(const BlendType& lhs, const BlendType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

inline bool operator==(const BlendType& lhs, const BlendType& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const BlendType& lhs, const BlendType& rhs) noexcept {
    return !(lhs == rhs);
}

struct Add_ {} static constexpr Add;
struct Subtract_ {} static constexpr Subtract;
struct RevSubtract_ {} static constexpr RevSubtract;
struct Min_ {} static constexpr Min;
struct Max_ {} static constexpr Max;

using BlendOp = std::variant<Add_, Subtract_, RevSubtract_, Min_, Max_>;

inline bool operator<(const BlendOp& lhs, const BlendOp& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct Clear_ {} static constexpr Clear;
struct Set_ {} static constexpr Set;
struct Copy_ {} static constexpr Copy;
struct CopyInverted_ {} static constexpr CopyInverted;
struct NoOp_ {} static constexpr NoOp;
struct Invert_ {} static constexpr Invert;
struct And_ {} static constexpr And;
struct Nand_ {} static constexpr Nand;
struct Or_ {} static constexpr Or;
struct Nor_ {} static constexpr Nor;
struct Xor_ {} static constexpr Xor;
struct Equiv_ {} static constexpr Equiv;
struct AndReverse_ {} static constexpr AndReverse;
struct AndInverted_ {} static constexpr AndInverted;
struct OrReverse_ {} static constexpr OrReverse;
struct OrInverted_ {} static constexpr OrInverted;

using LogicalOp = std::variant<Clear_, Set_, Copy_, CopyInverted_, NoOp_, Invert_, And_, Nand_, Or_, Nor_, Xor_, Equiv_, AndReverse_, AndInverted_, OrReverse_, OrInverted_>;

inline bool operator<(const LogicalOp& lhs, const LogicalOp& rhs) noexcept {
    return lhs.index() < rhs.index();
}

namespace DSL {

enum ColorWrite : uint32_t {
    R = 1 << 0,
    G = 1 << 1,
    B = 1 << 2,
    A = 1 << 3,
    RGBA = R|G|B|A,
    RGB = R|G|B,
};

} // namespace DSL

struct Blend {
    Blend() = default;
    Blend(BlendType srcBlend, BlendType dstBlend)
        : mSrcBlend(std::move(srcBlend))
        , mDstBlend(std::move(dstBlend))
    {}
    Blend(BlendType srcBlend, BlendType dstBlend, DSL::ColorWrite renderTargetWriteMask)
        : mSrcBlend(std::move(srcBlend))
        , mDstBlend(std::move(dstBlend))
        , mRenderTargetWriteMask(std::move(renderTargetWriteMask))
    {}
    Blend(BlendType srcBlend, BlendType dstBlend, BlendType srcBlendAlpha, BlendType dstBlendAlpha, DSL::ColorWrite renderTargetWriteMask)
        : mSrcBlend(std::move(srcBlend))
        , mDstBlend(std::move(dstBlend))
        , mSrcBlendAlpha(std::move(srcBlendAlpha))
        , mDstBlendAlpha(std::move(dstBlendAlpha))
        , mRenderTargetWriteMask(std::move(renderTargetWriteMask))
    {}
    Blend(BlendType srcBlend, BlendType dstBlend, BlendOp blendOp, BlendType srcBlendAlpha, BlendType dstBlendAlpha, BlendOp blendOpAlpha, LogicalOp logicOp, DSL::ColorWrite renderTargetWriteMask)
        : mSrcBlend(std::move(srcBlend))
        , mDstBlend(std::move(dstBlend))
        , mBlendOp(std::move(blendOp))
        , mSrcBlendAlpha(std::move(srcBlendAlpha))
        , mDstBlendAlpha(std::move(dstBlendAlpha))
        , mBlendOpAlpha(std::move(blendOpAlpha))
        , mLogicOp(std::move(logicOp))
        , mRenderTargetWriteMask(std::move(renderTargetWriteMask))
    {}
    BlendType mSrcBlend = One;
    BlendType mDstBlend = Zero;
    BlendOp mBlendOp = Add;
    BlendType mSrcBlendAlpha = One;
    BlendType mDstBlendAlpha = Zero;
    BlendOp mBlendOpAlpha = Add;
    LogicalOp mLogicOp = NoOp;
    DSL::ColorWrite mRenderTargetWriteMask = DSL::RGBA;
};

struct BlendState {
    BlendState() = default;
    BlendState(std::vector<Blend> renderTargets)
        : mRenderTargets(std::move(renderTargets))
    {}
    BlendState(bool alphaToCoverageEnable, std::vector<Blend> renderTargets)
        : mAlphaToCoverageEnable(std::move(alphaToCoverageEnable))
        , mRenderTargets(std::move(renderTargets))
    {}
    std::vector<Blend> mRenderTargets;
    bool mAlphaToCoverageEnable = false;
};

struct Wireframe_ {} static constexpr Wireframe;
struct Solid_ {} static constexpr Solid;

using FillMode = std::variant<Wireframe_, Solid_>;

inline bool operator<(const FillMode& lhs, const FillMode& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct None_ {} static constexpr None;
struct Front_ {} static constexpr Front;
struct Back_ {} static constexpr Back;

using CullMode = std::variant<None_, Front_, Back_>;

inline bool operator<(const CullMode& lhs, const CullMode& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct RasterizerState {
    RasterizerState() = default;
    RasterizerState(FillMode fillMode)
        : mFillMode(std::move(fillMode))
    {}
    RasterizerState(CullMode cullMode)
        : mCullMode(std::move(cullMode))
    {}
    RasterizerState(FillMode fillMode, CullMode cullMode)
        : mFillMode(std::move(fillMode))
        , mCullMode(std::move(cullMode))
    {}
    FillMode mFillMode = Solid;
    CullMode mCullMode = Back;
    bool mFrontCounterClockwise = true;
    int32_t mDepthBias = 0;
    float mDepthBiasClamp = 0.0f;
    float mSlopeScaledDepthBias = 0.0f;
    bool mDepthClipEnabled = true;
    bool mMultisampleEnable = false;
    bool mAntialiasedLineEnable = false;
    uint32_t mForcedSampleCount = 0;
    bool mConservativeRaster = false;
};

struct Never_ {} static constexpr Never;
struct Less_ {} static constexpr Less;
struct Equal_ {} static constexpr Equal;
struct LessEqual_ {} static constexpr LessEqual;
struct Greater_ {} static constexpr Greater;
struct NotEqual_ {} static constexpr NotEqual;
struct GreaterEqual_ {} static constexpr GreaterEqual;
struct Always_ {} static constexpr Always;

using ComparisonFunc = std::variant<Never_, Less_, Equal_, LessEqual_, Greater_, NotEqual_, GreaterEqual_, Always_>;

inline bool operator<(const ComparisonFunc& lhs, const ComparisonFunc& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct Keep_ {} static constexpr Keep;
struct Replace_ {} static constexpr Replace;
struct IncrSat_ {} static constexpr IncrSat;
struct DecrSat_ {} static constexpr DecrSat;
struct Incr_ {} static constexpr Incr;
struct Decr_ {} static constexpr Decr;

using StencilOp = std::variant<Keep_, Zero_, Replace_, IncrSat_, DecrSat_, Invert_, Incr_, Decr_>;

inline bool operator<(const StencilOp& lhs, const StencilOp& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct StencilOpState {
    StencilOp mStencilFailOp = Keep;
    StencilOp mStencilDepthFailOp = Keep;
    StencilOp mStencilPassOp = Keep;
    ComparisonFunc mStencilFunc = Always;
};

struct DepthStencilState {
    bool mDepthEnabled = true;
    bool mDepthWrite = true;
    ComparisonFunc mDepthFunc = Less;
    bool mStencilEnable = true;
    uint8_t mStencilReadMask = 0xff;
    uint8_t mStencilWriteMask = 0xff;
    StencilOpState mFrontFace;
    StencilOpState mBackFace;
};

struct PipelineState {
    PipelineState() = default;
    PipelineState(BlendState blendState)
        : mBlendState(std::move(blendState))
    {}
    PipelineState(RasterizerState rasterizerState)
        : mRasterizerState(std::move(rasterizerState))
    {}
    PipelineState(DepthStencilState depthStencilState)
        : mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(BlendState blendState, RasterizerState rasterizerState)
        : mBlendState(std::move(blendState))
        , mRasterizerState(std::move(rasterizerState))
    {}
    PipelineState(BlendState blendState, DepthStencilState depthStencilState)
        : mBlendState(std::move(blendState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(BlendState blendState, RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mBlendState(std::move(blendState))
        , mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(BlendState blendState, uint32_t sampleMask, RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mBlendState(std::move(blendState))
        , mSampleMask(std::move(sampleMask))
        , mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(std::string name, BlendState blendState)
        : mName(std::move(name))
        , mBlendState(std::move(blendState))
    {}
    PipelineState(std::string name, RasterizerState rasterizerState)
        : mName(std::move(name))
        , mRasterizerState(std::move(rasterizerState))
    {}
    PipelineState(std::string name, DepthStencilState depthStencilState)
        : mName(std::move(name))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(std::string name, BlendState blendState, RasterizerState rasterizerState)
        : mName(std::move(name))
        , mBlendState(std::move(blendState))
        , mRasterizerState(std::move(rasterizerState))
    {}
    PipelineState(std::string name, BlendState blendState, DepthStencilState depthStencilState)
        : mName(std::move(name))
        , mBlendState(std::move(blendState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(std::string name, RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mName(std::move(name))
        , mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(std::string name, BlendState blendState, RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mName(std::move(name))
        , mBlendState(std::move(blendState))
        , mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    PipelineState(std::string name, BlendState blendState, uint32_t sampleMask, RasterizerState rasterizerState, DepthStencilState depthStencilState)
        : mName(std::move(name))
        , mBlendState(std::move(blendState))
        , mSampleMask(std::move(sampleMask))
        , mRasterizerState(std::move(rasterizerState))
        , mDepthStencilState(std::move(depthStencilState))
    {}
    std::string mName;
    BlendState mBlendState;
    uint32_t mSampleMask = 0xffffffff;
    RasterizerState mRasterizerState;
    DepthStencilState mDepthStencilState;
};

struct PerVertexData_ {} static constexpr PerVertexData;
struct PerInstanceData_ {} static constexpr PerInstanceData;

using InputClassification = std::variant<PerVertexData_, PerInstanceData_>;

inline bool operator<(const InputClassification& lhs, const InputClassification& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct InputElement {
    std::string mSemanticName;
    uint32_t mSemanticIndex = 0;
    Format mFormat = Format::UNKNOWN;
    uint32_t mInputSlot = 0;
    uint32_t mAlignedByteOffset = 0;
    InputClassification mInputSlotClass;
    uint32_t mInstanceDataStepRate = 0;
};

struct Disabled_ {} static constexpr Disabled;
struct FFFF_ {} static constexpr FFFF;
struct FFFFFFFF_ {} static constexpr FFFFFFFF;

using IndexBufferStripCutValue = std::variant<Disabled_, FFFF_, FFFFFFFF_>;

inline bool operator<(const IndexBufferStripCutValue& lhs, const IndexBufferStripCutValue& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct Point_ {} static constexpr Point;
struct Line_ {} static constexpr Line;
struct Triangle_ {} static constexpr Triangle;
struct Patch_ {} static constexpr Patch;

using PrimitiveTopologyType = std::variant<Point_, Line_, Triangle_, Patch_>;

inline bool operator<(const PrimitiveTopologyType& lhs, const PrimitiveTopologyType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct InputLayoutState {
    std::string mName;
    std::vector<InputElement> mInputLayout;
    IndexBufferStripCutValue mIBStripCutValue;
    PrimitiveTopologyType mPrimitiveTopologyType = Triangle;
};

} // namespace Shader

} // namespace Render

} // namespace Graphics

} // namespace Star
