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

#include "SUnityShaderBuilder.h"
#include <StarCompiler/ShaderGraph/SShaderPrototype.h>
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include "SHLSLGenerator.h"

namespace Star::Graphics::Render::Shader {

namespace {

struct UnityIsPropertyVisitor {
    bool operator()(const uint4&) const { return false; }
    bool operator()(const uint2&) const { return false; }
    bool operator()(const uint1&) const { return false; }

    bool operator()(InputPatch_) const { return false; }
    bool operator()(OutputPatch_) const { return false; }

    bool operator()(Buffer_) const { return false; }
    bool operator()(ByteAddressBuffer_) const { return false; }
    bool operator()(StructuredBuffer_) const { return false; }
    
    bool operator()(Texture1D_) const { return false; }
    bool operator()(Texture1DArray_) const { return false; }
    //bool operator()(Texture2DArray_) const { return false; }
    bool operator()(Texture2DMS_) const { return false; }
    bool operator()(Texture2DMSArray_) const { return false; }
    bool operator()(TextureCubeArray_) const { return false; }

    bool operator()(AppendStructuredBuffer_) const { return false; }
    bool operator()(ConsumeStructuredBuffer_) const { return false; }

    bool operator()(RWBuffer_) const { return false; }
    bool operator()(RWByteAddressBuffer_) const { return false; }
    bool operator()(RWStructuredBuffer_) const { return false; }

    bool operator()(RWTexture1D_) const { return false; }
    bool operator()(RWTexture1DArray_) const { return false; }
    bool operator()(RWTexture2D_) const { return false; }
    bool operator()(RWTexture2DArray_) const { return false; }
    bool operator()(RWTexture3D_) const { return false; }

    bool operator()(SamplerState_) const { return false; }

    template<class T> bool operator()(const T&) const { return true; }
};

struct UnityPropertyNameVisitor {
    std::string operator()(const matrix& v) const { return "Matrix"; }
    std::string operator()(const float4& v) const { return "Vector"; }
    std::string operator()(const int4& v) const { return "Int4"; }

    std::string operator()(const float2& v) const { return "Float2"; }
    std::string operator()(const int2& v) const { return "Int2"; }
    std::string operator()(const half4& v) const { return "Vector"; }

    std::string operator()(const float1& v) const { return "Float"; }
    std::string operator()(const int1& v) const { return "Int"; }
    std::string operator()(const half2& v) const { return "Float2"; }
    std::string operator()(const fixed4& v) const { return "Color"; }

    std::string operator()(const half1& v) const { return "Float"; }

    //std::string operator()(const Texture1D_& v) const { return "1D"; }
    std::string operator()(const Texture2D_& v) const { return "2D"; }
    std::string operator()(const Texture2DArray_& v) const { return "2DArray"; }
    std::string operator()(const Texture3D_& v) const { return "3D"; }
    std::string operator()(const TextureCube_& v) const { return "Cube"; }
    std::string operator()(const SamplerState_& v) const { return "Sampler"; }

    std::string operator()(const FloatRange& v) const {
        return std::string("Range(") + std::to_string(float(v.mMin)) + ", " +
            std::to_string(float(v.mMax)) + ")";
    }
    std::string operator()(const HalfRange& v) const {
        return std::string("Range(") + std::to_string(float(v.mMin)) + ", " +
            std::to_string(float(v.mMax)) + ")";
    }

    template<class T>
    std::string operator()(const T&) const { return ""; }
};

struct UnityPropertyDefaultValueVisitor {
    const ShaderAttribute& mAttribute;
    // matrix
    template<class T, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
    std::string operator()(const Eigen::Matrix<T, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v) const {
        std::string str = "(";
        for (int i = 0; i != _Rows; ++i) {
            if (i != 0) {
                str += "\n";
            }
            for (int j = 0; j != _Cols; ++j) {
                if (j != 0) {
                    str += ", ";
                }
                str += std::to_string(float(v(i, j)));
            }
        }
        str += ")";
        return str;
    }

    // vector
    template<class T, int _Rows, int _Options, int _MaxRows, int _MaxCols>
    std::string operator()(const Eigen::Matrix<T, _Rows, 1, _Options, _MaxRows, _MaxCols>& v) const {        
        std::string str = "(";
        for (int i = 0; i != _Rows; ++i) {
            if (i != 0) {
                str += ", ";
            }
            str += std::to_string(float(v[i]));
        }
        str += ")";
        return str;
    }

    template<int _Options, int _MaxRows, int _MaxCols>
    std::string operator()(const Eigen::Matrix<uint8_t, 4, 1, _Options, _MaxRows, _MaxCols>& color) const {
        Eigen::Matrix<float, 4, 1, _Options, _MaxRows, _MaxCols> v = color.template cast<float>();
        v /= 255.f;
        return operator()(v);
    }

    std::string operator()(const FloatRange& v) const {
        return std::to_string(float(v.mValue));
    }

    std::string operator()(const HalfRange& v) const {
        return std::to_string(float(v.mValue));
    }

    //std::string operator()(const Texture1D_& v) const {
    //    if (mAttribute.mDefaultValue.empty()) {
    //        return "\"white\" {}";
    //    } else {
    //        return "\"" + mAttribute.mDefaultValue + "\" {}";
    //    }
    //}

    std::string operator()(const Texture2D_& v) const {
        if (mAttribute.mDefaultValue.empty()) {
            return "\"white\" {}";
        } else {
            return "\"" + mAttribute.mDefaultValue + "\" {}";
        }
    }

    std::string operator()(const Texture2DArray_& v) const {
        if (mAttribute.mDefaultValue.empty()) {
            return "\"\" {}";
        } else {
            return "\"" + mAttribute.mDefaultValue + "\" {}";
        }
    }

    std::string operator()(const Texture3D_& v) const {
        if (mAttribute.mDefaultValue.empty()) {
            return "\"white\" {}";
        } else {
            return "\"" + mAttribute.mDefaultValue + "\" {}";            
        }
    }

    std::string operator()(const TextureCube_& v) const {
        if (mAttribute.mDefaultValue.empty()) {
            return "\"white\" {}";
        } else {
            return "\"" + mAttribute.mDefaultValue + "\" {}";
        }
    }
    std::string operator()(const SamplerState_& v) const {
        if (mAttribute.mDefaultValue.empty()) {
            return "\"point\" {}";
        } else {
            return "\"" + mAttribute.mDefaultValue + "\" {}";
        }
    }

    template<class T>
    std::string operator()(const T&) const {
        return "";
    }
};

struct UnityHLSLNameVisitor {
    const char* operator()(const matrix& v) const { return "matrix"; }
    const char* operator()(const float4& v) const { return "float4"; }
    const char* operator()(const int4& v) const { return "int4"; }

    const char* operator()(const float2& v) const { return "float2"; }
    const char* operator()(const int2& v) const { return "int2"; }
    const char* operator()(const half4& v) const { return "half4"; }

    const char* operator()(const float1& v) const { return "float"; }
    const char* operator()(const int1& v) const { return "int"; }
    const char* operator()(const half2& v) const { return "half2"; }
    const char* operator()(const fixed4& v) const { return "fixed4"; }

    const char* operator()(const half1& v) const { return "half"; }

    const char* operator()(const Texture1D_& v) const { return "sampler1D"; }
    const char* operator()(const Texture2D_& v) const { return "sampler2D"; }
    const char* operator()(const Texture3D_& v) const { return "sampler3D"; }
    const char* operator()(const TextureCube_& v) const { return "samplerCUBE"; }
    const char* operator()(const SamplerState_& v) const { return "samplerState"; }

    const char* operator()(const FloatRange& v) const { return "float"; }
    const char* operator()(const HalfRange& v) const { return "half"; }

    template<class T>
    const char* operator()(const T&) const { return ""; }
};

} // namespace

std::string UnityShaderBuilder::generateShader(const AttributeMap& attrMap, const ShaderPrototype& p) const {
    Expects(p.mSolutions.size() == 1);
    Expects(p.mSolutions.begin()->second.mPipelines.size() == 1);

    std::ostringstream oss;
    std::string space;

    oss << R"(// This file is generated by StarEngine.
// 
// MIT License
// Copyright (c) 2019 star.engine at outlook dot com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

)";

    OSS << "Shader \"" << p.mName << "\" {\n";

    if (!p.mSolutions.empty() && !p.mSolutions.begin()->second.mPipelines.empty()) {
        auto attrs = getAttributes(attrMap, p.getAttributes());
        copyString(oss, generateProperties(attrs, p));
        const auto& pipeline = p.mSolutions.begin()->second.mPipelines.begin()->second;
        for (const auto& [queueName, queue] : pipeline.mQueues) {
            for (const auto& subshader : queue.mLevels) {
                oss << "\n";
                OSS << "SubShader {\n";

                copyString(oss, generateSubShaderStates(subshader));

                for (const auto& [subpassName, passes] : subshader.mPasses) {
                    for (const auto& pass : passes) {
                        oss << "\n";
                        oss << "Pass {\n";
                        if (!pass.mName.empty()) {
                            oss << "\n";
                            OSS << "NAME \"" << pass.mName << "\"\n";
                        }
                        copyString(oss, generatePassStates(pass));
                        auto attrs = getAttributes(attrMap, pass.mProgram.mGraph.mAttributeUsages);
                        copyString(oss, generateProgram(attrs, pass));

                        oss << "\n";
                        oss << "} // Pass end\n";
                    }
                }

                if (!subshader.mUnityUsePasses.empty()) {
                    oss << "\n";
                    for (const auto& usepass : subshader.mUnityUsePasses) {
                        oss << "UsePass \"" << usepass << "\"\n";
                    }
                }

                oss << "\n";
                oss << "} // SubShader end\n";
            } // SubShader
        } // queue

        for (const auto& [name, shader] : pipeline.mUnityDependencies) {
            OSS << "Dependency \"" << name << "\" = \"" << shader << "\"\n";
        }

        if (!pipeline.mUnityCustomEditor.empty()) {
            oss << "\n";
            oss << "CustomEditor \"" << pipeline.mUnityCustomEditor << "\"\n";
        }
    }

    oss << "\n";
    OSS << "} // Shader end\n";

    return oss.str();
}

std::string UnityShaderBuilder::generateProperties(
    const AttributeMap& attrs, const ShaderPrototype& p
) const {
    std::ostringstream oss;
    std::string space;

    // Properties
    int count = 0;
    for (const auto& attr : attrs) {
        if (attr.mFlags & (Unity::Global | Unity::BuiltIn))
            continue;

        if (!visit(UnityIsPropertyVisitor(), attr.mType)) {
            continue;
        }
        ++count;
    }

    if (count == 0)
        return oss.str();

    oss << "\n";
    OSS << "Properties {\n";
    {
        INDENT();

        for (const auto& attr : attrs) {
            if (attr.mFlags & (Unity::Global | Unity::BuiltIn))
                continue;

            if (!visit(UnityIsPropertyVisitor(), attr.mType)) {
                continue;
            }

            oss << space;

            auto value = attr.mType;

            if (attr.mFlags & Unity::HideInInspector) {
                oss << "[HideInInspector] ";
            }
            if (attr.mFlags & Unity::PerRendererData) {
                oss << "[PerRendererData] ";
            }
            if (attr.mFlags & Unity::NoScaleOffset) {
                Expects(!(attr.mFlags & Unity::TexScaleOffset));
                oss << "[NoScaleOffset] ";
            }
            if (attr.mFlags & Unity::Normal) {
                oss << "[Normal] ";
            }
            if (attr.mFlags & Unity::HDR) {
                oss << "[HDR] ";
                value = fixed4();
            }
            if (attr.mFlags & Unity::Gamma) {
                oss << "[Gamma] ";
                value = fixed4();
            }

            std::string editorName = visit(UnityPropertyNameVisitor(), value);

            oss << "_" << attr.mName << "(\"" << attr.mName << "\", " << editorName << ") = "
                << visit(UnityPropertyDefaultValueVisitor{ attr }, attr.mType) << "\n";
        }
    }
    OSS << "}\n";

    return oss.str();
}

std::string UnityShaderBuilder::generateSubShaderStates(const ShaderLevel& subshader) const {
    std::ostringstream oss;
    std::string space;

    if (!subshader.mUnityTags.empty()) {
        oss << "\n";
        oss << "Tags {";
        for (const auto& [type, name] : subshader.mUnityTags) {
            oss << " \"" << type << "\" = \"" << name << "\"";
        }
        oss << " }\n"; // Tags
    }

    if (subshader.mUnityLOD) {
        oss << "\n";
        oss << "LOD " << std::to_string(subshader.mUnityLOD) << "\n";
    }

    return oss.str();
}

std::string UnityShaderBuilder::generatePassStates(const ShaderPass& p) const {
    std::ostringstream oss;
    std::string space;

    if (!p.mUnityTags.empty()) {
        oss << "\n";
        oss << "Tags {";
        int count = 0;
        for (const auto& [type, name] : p.mUnityTags) {
            if (count++)
                oss << " ";
            oss << " \"" << type << "\" = \"" << name << "\"";
        }
        oss << " }\n"; // Tags
    }

    const auto& pso = p.mShaderState;

    if (!pso.mBlendState.mRenderTargets.empty()) {
        oss << "\n";
        int k = 0;
        for (const auto& blend : pso.mBlendState.mRenderTargets) {
            oss << "Blend ";
            if (pso.mBlendState.mRenderTargets.size() > 1) {
                oss << k << " ";
            }
            oss << getVariantName(blend.mSrcBlend) << " " << getVariantName(blend.mDstBlend);
            if (blend.mSrcBlend != blend.mSrcBlendAlpha || blend.mDstBlend != blend.mDstBlendAlpha) {
                oss << ", " << getVariantName(blend.mSrcBlendAlpha)
                    << " " << getVariantName(blend.mDstBlendAlpha);
            }
            oss << "\n";
            ++k;
        }
    }

    if (!pso.mBlendState.mRenderTargets.empty()) {
        int k = 0;
        for (const auto& blend : pso.mBlendState.mRenderTargets) {
            if (blend.mRenderTargetWriteMask != DSL::RGBA) {
                oss << "ColorMask ";
                if (blend.mRenderTargetWriteMask == 0) {
                    oss << "0";
                } else {
                    if (blend.mRenderTargetWriteMask & DSL::R) {
                        oss << "R";
                    }
                    if (blend.mRenderTargetWriteMask & DSL::G) {
                        oss << "G";
                    }
                    if (blend.mRenderTargetWriteMask & DSL::B) {
                        oss << "B";
                    }
                    if (blend.mRenderTargetWriteMask & DSL::A) {
                        oss << "A";
                    }
                }
                if (pso.mBlendState.mRenderTargets.size() > 1) {
                    oss << " " << k;
                }
                oss << "\n";
            }
            ++k;
        }
    }

    if (pso.mBlendState.mAlphaToCoverageEnable) {
        oss << "\n";
        oss << "AlphaToMask On\n";
    }

    if (!std::holds_alternative<Back_>(pso.mRasterizerState.mCullMode)) {
        oss << "\n";
        oss << "Cull ";
        visit(overload(
            [&](None_) { oss << "Off"; },
            [&](Front_) { oss << "Front"; },
            [&](Back_) {oss << "Back"; }
        ), pso.mRasterizerState.mCullMode);
        oss << "\n";
    }

    if (pso.mDepthStencilState.mDepthWrite) {
        oss << "\n";
        oss << "ZWrite On\n";
    } else {
        oss << "\n";
        oss << "ZWrite Off\n";
    }

    if (pso.mDepthStencilState.mDepthEnabled) {
        oss << "\n";
        oss << "ZTest ";
        visit(overload(
            [&](Never_) { oss << "Never"; },
            [&](Less_) { oss << "Less"; },
            [&](Equal_) { oss << "Equal"; },
            [&](LessEqual_) { oss << "LEqual"; },
            [&](Greater_) { oss << "Greater"; },
            [&](NotEqual_) { oss << "NotEqual"; },
            [&](GreaterEqual_) { oss << "GEqual"; },
            [&](Always_) { oss << "Always"; }
        ), pso.mDepthStencilState.mDepthFunc);
        oss << "\n";
    } else {
        oss << "\n";
        oss << "ZTest Always\n";
    }

    return oss.str();
}

std::string UnityShaderBuilder::generateProgram(const AttributeMap& attrs, const ShaderPass& pass) const {
    std::ostringstream oss;
    std::string space;

    HLSLGenerator hlsl(pass.mProgram, UnityCG);
    hlsl.mAttributeRegex = "_$1";
    hlsl.mAttributeInstancingRegex = "UNITY_ACCESS_INSTANCED_PROP(Props, _$1)";

    oss << "\n";
    OSS << "CGPROGRAM\n";

    copyString(oss, pass.mProgram.mInclude);

    hlsl.mNamings[VS].mInputStruct = getName(pass.mUnityAppData);
    hlsl.mNamings[VS].mInputVariable = "v";

    bool hasGS = pass.mProgram.mShaders.find(GS) != pass.mProgram.mShaders.end();

    if (hasGS) {
        hlsl.mNamings[VS].mOutputStruct = "v2g";
        hlsl.mNamings[VS].mOutputVariable = "o";
        hlsl.mNamings[VS].mMain = "vert";

        hlsl.mNamings[GS].mInputStruct = "v2g";
        hlsl.mNamings[GS].mInputVariable = "IN";
        hlsl.mNamings[GS].mOutputStruct = "g2f";
        hlsl.mNamings[GS].mOutputVariable = "o";
        hlsl.mNamings[GS].mMain = "geom";

        hlsl.mNamings[PS].mInputStruct = "g2f";
        hlsl.mNamings[PS].mInputVariable = "IN";
        hlsl.mNamings[PS].mOutputStruct = "f2s";
        hlsl.mNamings[PS].mOutputVariable = "o";
        hlsl.mNamings[PS].mMain = "frag";
    } else {
        hlsl.mNamings[VS].mOutputStruct = "v2f";
        hlsl.mNamings[VS].mOutputVariable = "o";
        hlsl.mNamings[VS].mMain = "vert";

        hlsl.mNamings[GS].mInputStruct = "";
        hlsl.mNamings[GS].mInputVariable = "";
        hlsl.mNamings[GS].mOutputStruct = "";
        hlsl.mNamings[GS].mOutputVariable = "";
        hlsl.mNamings[GS].mMain = "";

        hlsl.mNamings[PS].mInputStruct = "v2f";
        hlsl.mNamings[PS].mInputVariable = "IN";
        hlsl.mNamings[PS].mOutputStruct = "f2s";
        hlsl.mNamings[PS].mOutputVariable = "o";
        hlsl.mNamings[PS].mMain = "frag";
    }

    auto attrSet = getAttributes(attrs, pass.mProgram.mGraph.mAttributeUsages);
    copyString(oss, space, generateAttributes(attrSet, pass.mUnityInstancing));

    copyString(oss, hlsl.generateModules());

    if (pass.mUnityAppData == Unity::AppData::Default) {
        oss << "\n";
        copyString(oss, space, hlsl.generateInput(VS));
    }

    oss << "\n";
    {
        auto content = hlsl.generateOutput(VS);
        if (pass.mUnityReceiveShadow && !pass.isShadowCaster() && !pass.isMeta()) {
            boost::replace_all(content, "clipPos : SV_Position", "pos : SV_Position");
            auto pos = content.find("}");
            if (pos == std::string::npos) {
                throw std::runtime_error("shader input format incorrect");
            }
            const auto& outputs = hlsl.mOutputs.at(VS);
            uint32_t texCount = 0;
            for (const auto& output : outputs) {
                if (std::holds_alternative<TEXCOORD_>(output.mSemantic)) {
                    ++texCount;
                }
            }
            content.insert(pos, "    UNITY_SHADOW_COORDS(" + std::to_string(texCount) + ")\n");
        }
        if (pass.mUnityInstancing) {
            auto pos = content.find("}");
            if (pos == std::string::npos) {
                throw std::runtime_error("shader input format incorrect");
            }
            content.insert(pos, "    UNITY_VERTEX_INPUT_INSTANCE_ID\n");
        }
        copyString(oss, space, content);
    }
    oss << "\n";
    {
        auto content = hlsl.generateMain(VS);
        boost::replace_all(content, "    v2f o;\n", "");
        if (pass.mUnityReceiveShadow && !pass.isShadowCaster() && !pass.isMeta()) {
            boost::replace_all(content, ".clipPos", ".pos");
        }

        std::string v2f = R"({
    v2f o;
    UNITY_INITIALIZE_OUTPUT(v2f, o);
)";
        if (pass.mUnityInstancing) {
            v2f += "    UNITY_SETUP_INSTANCE_ID(v);\n";
        }
        boost::replace_first(content, "{\n", v2f);

        if (pass.mUnityReceiveShadow && !pass.isShadowCaster() && !pass.isMeta()) {
            auto pos = content.find("return");
            if (pos == std::string::npos) {
                throw std::runtime_error("shader return format incorrect");
            }
            content.insert(pos, "UNITY_TRANSFER_SHADOW(o, texcoord1.xy);\n    ");
        }
        copyString(oss, space, content);
    }
    

    if (hasGS) {
        oss << "\n";
        copyString(oss, space, hlsl.generateOutput(GS));
        oss << "\n";
        copyString(oss, space, hlsl.generateMain(GS));
    }

    oss << "\n";
    copyString(oss, space, hlsl.generateMain(PS));

    oss << '\n';
    OSS << "ENDCG\n";

    return oss.str();
}

std::string UnityShaderBuilder::generateAttributes(
    const AttributeMap& attrs, bool instancing
) const {
    std::ostringstream oss;

    int count = 0;
    int instanced = 0;
    for (const auto& attr : attrs) {
        if (attr.mFlags & Unity::Declared)
            continue;

        if (attr.mFlags & Unity::BuiltIn)
            continue;

        if (instancing && attr.mUpdateFrequency == PerInstance) {
            ++instanced;
            continue;
        }

        if (!visit(UnityIsPropertyVisitor{}, attr.mType))
            continue;

        visit(overload(
            [&](Texture2D_) {
                if (attr.mFlags & Unity::SeparateSampler) {
                    Expects(!(attr.mFlags & Unity::NoSampler));
                    oss << "UNITY_DECLARE_TEX2D(_" << attr.mName << ");\n";
                } else if (attr.mFlags & Unity::NoSampler) {
                    Expects(!(attr.mFlags & Unity::SeparateSampler));
                    oss << "UNITY_DECLARE_TEX2D_NOSAMPLER(_" << attr.mName << ");\n";
                } else {
                    oss << visit(UnityHLSLNameVisitor{}, attr.mType) << " _" + attr.mName << ";\n";
                }
            },
            [&](Texture2DArray_) {
                oss << "UNITY_DECLARE_TEX2DARRAY(_" << attr.mName << ");\n";
            },
            [&](const auto&) {
                oss << visit(UnityHLSLNameVisitor{}, attr.mType) << " _" + attr.mName << ";\n";
            }
        ), attr.mType);

        if (attr.mFlags & Unity::TexScaleOffset) {
            oss << "float4 " << "_" + attr.mName << "_ST;\n";
        }
        ++count;
    }

    if (instancing && instanced) {
        oss << "\n";
        oss << "UNITY_INSTANCING_BUFFER_START(Props)\n";
        for (const auto& attr : attrs) {
            if (!(attr.mUpdateFrequency == PerInstance))
                continue;

            if (attr.mFlags & Unity::Declared)
                continue;

            if (attr.mFlags & Unity::BuiltIn)
                continue;

            if (!visit(UnityIsPropertyVisitor{}, attr.mType))
                continue;

            oss << "    UNITY_DEFINE_INSTANCED_PROP(" <<
                visit(UnityHLSLNameVisitor{}, attr.mType) << ", "
                << "_" + attr.mName << ");\n";
        }
        oss << "UNITY_INSTANCING_BUFFER_END(Props)\n";
    }

    if (count)
        return "\n" + oss.str();

    return oss.str();
}

}
