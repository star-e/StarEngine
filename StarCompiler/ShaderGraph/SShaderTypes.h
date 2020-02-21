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

using ValueModel = std::variant<std::monostate, float4_, float3_, float2_, float1_, half4_, half3_, half2_, half1_, fixed4_, fixed3_, fixed2_, fixed1_, uint4_, uint3_, uint2_, uint1_, int4_, int3_, int2_, int1_, ShaderStruct>;

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

struct FloatRange {
    float mValue = 0.0f;
    float mMin = 0.0f;
    float mMax = 1.0f;
};

struct HalfRange {
    half mValue = half(0.0f);
    half mMin = half(0.0f);
    half mMax = half(1.0f);
};

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

struct Bounded_ {} static constexpr Bounded;
struct Unbounded_ {} static constexpr Unbounded;

using Boundedness = std::variant<Bounded_, Unbounded_>;

inline bool operator<(const Boundedness& lhs, const Boundedness& rhs) noexcept {
    return lhs.index() < rhs.index();
}

struct AttributeDescriptor {
    AttributeDescriptor() = default;
    AttributeDescriptor(UpdateEnum update, RootParameterType rootParameterType, Persistency persistency, DescriptorType descriptorType, std::string registerSpace, DescriptorSource source, Boundedness boundedness, std::string name)
        : mUpdate(std::move(update))
        , mRootParameterType(std::move(rootParameterType))
        , mPersistency(std::move(persistency))
        , mDescriptorType(std::move(descriptorType))
        , mRegisterSpace(std::move(registerSpace))
        , mSource(std::move(source))
        , mBoundedness(std::move(boundedness))
        , mName(std::move(name))
    {}
    AttributeDescriptor(UpdateEnum update, RootParameterType rootParameterType, Persistency persistency, std::string registerSpace, DescriptorSource source, Boundedness boundedness)
        : mUpdate(std::move(update))
        , mRootParameterType(std::move(rootParameterType))
        , mPersistency(std::move(persistency))
        , mRegisterSpace(std::move(registerSpace))
        , mSource(std::move(source))
        , mBoundedness(std::move(boundedness))
    {}
    AttributeDescriptor(UpdateEnum update, RootParameterType rootParameterType, Persistency persistency, DescriptorSource source)
        : mUpdate(std::move(update))
        , mRootParameterType(std::move(rootParameterType))
        , mPersistency(std::move(persistency))
        , mSource(std::move(source))
    {}
    UpdateEnum mUpdate = PerBatch;
    RootParameterType mRootParameterType = Table;
    Persistency mPersistency = Persistent;
    DescriptorType mDescriptorType;
    std::string mRegisterSpace;
    DescriptorSource mSource = MaterialSource;
    Boundedness mBoundedness;
    std::string mName;
};

inline bool operator<(const AttributeDescriptor&lhs, const AttributeDescriptor&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mUpdate, lhs.mRootParameterType, lhs.mPersistency, lhs.mDescriptorType, lhs.mRegisterSpace, lhs.mSource, lhs.mBoundedness, lhs.mName) <
        std::forward_as_tuple(rhs.mUpdate, rhs.mRootParameterType, rhs.mPersistency, rhs.mDescriptorType, rhs.mRegisterSpace, rhs.mSource, rhs.mBoundedness, rhs.mName);
}

struct AttributeDatabase {
    IdentityNameMap<AttributeDescriptor> mAttributes;
    Map<std::string, uint32_t> mIndex;
};

struct ShaderAttribute {
    ShaderAttribute() = default;
    ShaderAttribute(std::string name, AttributeType type, AttributeDescriptor descriptor)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
    {}
    ShaderAttribute(std::string name, AttributeType type, AttributeDescriptor descriptor, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, AttributeDescriptor descriptor, uint32_t flags, std::string defaultValue)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, AttributeType type, AttributeDescriptor descriptor, std::string defaultValue)
        : mName(std::move(name))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, uint32_t flags)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, uint32_t flags, std::string defaultValue)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, std::string defaultValue)
        : mName(std::move(name))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, AttributeDescriptor descriptor)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, AttributeDescriptor descriptor, uint32_t flags)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, AttributeDescriptor descriptor, uint32_t flags, std::string defaultValue)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, AttributeDescriptor descriptor, std::string defaultValue)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mDescriptor(std::move(descriptor))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, uint32_t flags)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, uint32_t flags, std::string defaultValue)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mFlags(std::move(flags))
        , mDefaultValue(std::move(defaultValue))
    {}
    ShaderAttribute(std::string name, ValueModel model, AttributeType type, ShaderResourceDataView data, AttributeDescriptor descriptor, std::string defaultValue)
        : mName(std::move(name))
        , mModel(std::move(model))
        , mType(std::move(type))
        , mData(std::move(data))
        , mDescriptor(std::move(descriptor))
        , mDefaultValue(std::move(defaultValue))
    {}
    std::string mName;
    ValueModel mModel;
    AttributeType mType;
    ShaderResourceDataView mData;
    AttributeDescriptor mDescriptor;
    uint32_t mFlags = 0;
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

struct DescriptorSubrange {
    NameMap<ShaderAttribute> mAttributes;
};

struct DescriptorRange {
    Map<DescriptorSource, DescriptorSubrange> mSubranges;
    uint32_t mCapacity = 0;
    uint32_t mSpace = 0;
    uint32_t mStart = 0;
    uint32_t mCount = 0;
};

struct UnboundedDescriptor {
    ShaderAttribute mAttribute;
    uint32_t mSpace = 0;
    uint32_t mStart = 0;
};

struct DescriptorList {
    uint32_t mSlot = 0;
    Map<DescriptorType, DescriptorRange> mRanges;
    Map<DescriptorType, UnboundedDescriptor> mUnboundedDescriptors;
};

struct DescriptorCollection {
    Map<std::string, DescriptorList> mResourceViewLists;
    Map<std::string, DescriptorList> mSamplerLists;
};

struct Constant {
    AttributeType mType;
    std::string mName;
};

inline bool operator<(const Constant&lhs, const Constant&rhs) noexcept {
    return
        std::forward_as_tuple(lhs.mType, lhs.mName) <
        std::forward_as_tuple(rhs.mType, rhs.mName);
}

struct ConstantBuffer {
    IdentityMap<Constant> mValues;
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
