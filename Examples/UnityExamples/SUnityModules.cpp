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

#include "SUnityModules.h"
#include <StarCompiler/ShaderGraph/SShaderDSL.h>

namespace Star::Graphics::Render::Shader {

using namespace DSL;
using namespace Unity;

void createUnityModules(ShaderWorks& shaderWorks) {
   ADD_ATTRIBUTES({
        { "MainTex", Texture2D, PerMaterial },
        { "BumpMap", Texture2D, PerMaterial },
        { "Material", Texture2D, PerMaterial },
    });

    ADD_MODULE(ClipPos, Inline,
        Outputs{
            { "clipPos", float4(), SV_Position }
        },
        Inputs{
            { "vertex", float4(), POSITION }
        },
        Content{
            "clipPos = UnityObjectToClipPos(vertex);\n",
        }
    );

    ADD_MODULE(WorldPos, Inline,
        Outputs{
            { "worldPos", float3(), TEXCOORD }
        },
        Inputs{
            { "vertex", float4(), POSITION }
        },
        Content{
            "worldPos = mul(unity_ObjectToWorld, vertex).xyz;\n"
        }
    );
    
    ADD_MODULE(ViewVector, Inline,
        Outputs{
            { "viewVector", float3(), TEXCOORD },
        },
        Inputs{
            { "worldPos", float3() },
        },
        Content{
            "viewVector = _WorldSpaceCameraPos - worldPos;\n"
        }
    );
        
    ADD_MODULE(ViewDir, Inline,
        Outputs{
            { "viewDir", half3(), TEXCOORD },
        },
        Inputs{
            { "viewVector", float3() },
        },
        Content{
            "viewDir = normalize(viewVector);\n"
        }
    );

    // BRDF coordinates
    ADD_MODULE(CosThetaOut, Inline,
        Outputs{
            { "cosThetaOut", half1() },
        },
        Inputs{
            { "worldNormal", half3() },
            { "viewDir", half3() },
        },
        Content{ "cosThetaOut = dot(worldNormal, viewDir);\n" }
    );
        
    ADD_MODULE(NdotV, Inline,
        Outputs{
            { "ndotv", half1() },
        },
        Inputs{
            { "cosThetaOut", half1() },
        },
        Content{ "ndotv = saturate(cosThetaOut);\n" }
    );

    ADD_MODULE(CosThetaIn, Inline,
        Outputs{
            { "cosThetaIn", half1() },
        },
        Inputs{
            { "worldNormal", half3() },
            { "lightDir", half3() },
        },
        Content{ "cosThetaIn = dot(worldNormal, lightDir);\n" }
    );
    
    ADD_MODULE(NdotL, Inline,
        Outputs{
            { "ndotl", half1() },
        },
        Inputs{
            { "cosThetaIn", half1() },
        },
        Content{ "ndotl = saturate(cosThetaIn);\n" }
    );

    // Rusinkiewicz BRDF coordinates
    ADD_MODULE(HalfVector, Inline,
        Outputs{
            { "halfVector", half3(), TEXCOORD },
        },
        Inputs{
            { "lightDir", half3() },
            { "viewDir", half3() },
        },
        Content{ "halfVector = lightDir + viewDir;\n" }
    );

    ADD_MODULE(HalfAngle, Inline,
        Outputs{
            { "halfAngle", half3(), TEXCOORD },
        },
        Inputs{
            { "halfVector", half3() },
        },
        Content{
            "halfAngle = Unity_SafeNormalize(halfVector);\n"
        }
    );

    ADD_MODULE(CosThetaH, Inline,
        Outputs{
            { "cosThetaH", half1() },
        },
        Inputs{
            { "halfAngle", half3() },
            { "worldNormal", half3() },
        },
        Content{
            "cosThetaH = dot(worldNormal, halfAngle);\n"
        }
    );
        
    ADD_MODULE(NdotH, Inline,
        Outputs{
            { "ndoth", half1() },
        },
        Inputs{
            { "cosThetaH", half1() },
        },
        Content{ "ndoth = saturate(cosThetaH);\n" }
    );

    // LdotH
    ADD_MODULE(CosThetaD, Inline,
        Outputs{
            { "cosThetaD", half1() },
        },
        Inputs{
            { "halfAngle", half3() },
            { "lightDir", half3() },
        },
        Content{
            "cosThetaH = dot(lightDir, halfAngle);\n"
        }
    );

    ADD_MODULE(LdotH, Inline,
        Outputs{
            { "ldoth", half1() },
        },
        Inputs{
            { "cosThetaD", half1() },
        },
        Content{ "ldoth = saturate(cosThetaD);\n" }
    );

    ADD_MODULE(CosDoubleThetaD, Inline,
        Outputs{
            { "cosDoubleThetaD", half1() },
        },
        Inputs{
            { "viewDir", half3() },
            { "lightDir", half3() },
        },
        Content{
            "cosDoubleThetaD = dot(viewDir, lightDir);\n"
        }
    );
    
    ADD_MODULE(LdotV, Inline,
        Outputs{
            { "ldotv", half1() },
        },
        Inputs{
            { "cosDoubleThetaD", half1() },
        },
        Content{
            "ldotv = saturate(cosDoubleThetaD);\n"
        }
    );

    ADD_MODULE(ViewRefl, Inline,
        Outputs{
            { "viewRefl", half3(), TEXCOORD },
        },
        Inputs{
            { "worldNormal", half3() },
            { "viewDir", half3() },
        },
        Content{ "viewRefl = reflect(-viewDir, worldNormal);\n" }
    );

    // vertex transform
    ADD_MODULE(WorldNormal, Inline,
        Outputs{
            { "worldNormal", half3(), TEXCOORD },
        },
        Inputs{
            { "normal", half3(), NORMAL },
        },
        Content{
            "worldNormal = UnityObjectToWorldNormal(normal.xyz);\n"
        }
    );
    
    ADD_MODULE(WorldTangent, Inline,
        Outputs{
            { "worldTangent", half3(), TEXCOORD },
        },
        Inputs{
            { "tangent", half4(), TANGENT },
        },
        Content{
            "worldTangent = UnityObjectToWorldDir(tangent.xyz);\n"
        }
    );

    ADD_MODULE(WorldBinormal, Inline,
        Outputs{
            { "worldBinormal", half3(), TEXCOORD },
        },
        Inputs{
            { "binormal", half4(), BINORMAL },
        },
        Content{
            "worldBinormal = UnityObjectToWorldDir(binormal.xyz);\n"
        }
    );
    
    ADD_MODULE(CalculateWorldBinormal, Inline,
        Outputs{
            { "worldBinormal", half3(), TEXCOORD },
        },
        Inputs{
            { "worldTangent", half3() },
            { "worldNormal", half3() },
            { "tangent", half4(), TANGENT },
        },
        Content{
            "worldBinormal = cross(worldNormal, worldTangent) * tangent.w * unity_WorldTransformParams.w;\n"
        }
    );

    ADD_MODULE(PackTangentSpaceAndViewDir, Inline,
        Outputs{
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Inputs{
            { "worldTangent", half3() },
            { "worldBinormal", half3() },
            { "worldNormal", half3() },
            { "viewDir", half3() }
        },
        Content{
            R"(tspace0 = half4(worldTangent.x, worldBinormal.x, worldNormal.x, viewDir.x);
tspace1 = half4(worldTangent.y, worldBinormal.y, worldNormal.y, viewDir.y);
tspace2 = half4(worldTangent.z, worldBinormal.z, worldNormal.z, viewDir.z);
)" }
    );

    ADD_MODULE(UnpackTangent, Inline,
        Outputs{
            { "worldTangent", half3() },
        },
        Inputs{
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Content{
            "worldTangent = half3(tspace0.x, tspace1.x, tspace2.x);\n"
        }
    );

    ADD_MODULE(UnpackBinormal, Inline,
        Outputs{
            { "worldBinormal", half3() },
        },
        Inputs{
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Content{
            "worldBinormal = half3(tspace0.y, tspace1.y, tspace2.y);\n"
        }
    );

    ADD_MODULE(UnpackNormal, Inline,
        Outputs{
            { "worldNormal", half3() },
        },
        Inputs{
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Content{
            "worldNormal = half3(tspace0.z, tspace1.z, tspace2.z);\n"
        }
    );

    ADD_MODULE(UnpackViewDir, Inline,
        Outputs{
            { "viewDir", half3() },
        },
        Inputs{
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Content{
            "viewDir = half3(tspace0.w, tspace1.w, tspace2.w);\n"
        }
    );
    
    ADD_MODULE(NormalizeViewDir, Inline,
        Outputs{
            { "viewDir", half3() },
        },
        Inputs{
            { "viewDir", half3() },
        },
        Content{
            "viewDir = normalize(viewDir);\n"
        }
    );

    // Material
    // Disney PBR
    ADD_MODULE(DefaultBaseColor, Inline,
        Outputs{
            { "baseColor", half3() },
        },
        Content{ "baseColor = half3(0.5h, 0.5h, 0.5h);\n" }
    );

    ADD_MODULE(DefaultTransparency, Inline,
        Outputs{
            { "transparency", half1() },
        },
        Content{ "transparency = 1.0h;\n" }
    );

    ADD_MODULE(DefaultPerceptualRoughness, Inline,
        Outputs{
            { "perceptualRoughness", half1() },
        },
        Content{ "perceptualRoughness = 0.5h;\n" }
    );

    ADD_MODULE(DefaultPerceptualSmoothness, Inline,
        Outputs{
            { "perceptualSmoothness", half1() },
        },
        Content{ "perceptualSmoothness = 0.5h;\n" }
    );

    ADD_MODULE(DefaultMetallic, Inline,
        Outputs{
            { "metallic", half1() },
        },
        Content{ "metallic = 0.0h;\n" }
    );

    ADD_MODULE(DefaultOcclusion, Inline,
        Outputs{
            { "occlusion", half1() },
        },
        Content{ "occlusion = 1.0h;\n" }
    );

    ADD_MODULE(DefaultEmission, Inline,
        Outputs{
            { "emission", half1() },
        },
        Content{ "emission = 0.0h;\n" }
    );

    // Texture
    ADD_MODULE(SampleBaseColor, Inline,
        Attributes{
            { "MainTex", Texture2D },
        },
        Outputs{
            { "baseColor", half3() },
        },
        Inputs{
            { "deviceUV", float2(), TEXCOORD },
        },
        Content{
            "baseColor = tex2D(MainTex, deviceUV).xyz;\n"
        }
    );

    ADD_MODULE(SampleBaseColorTransparency, Inline,
        Attributes{
            { "MainTex", Texture2D },
        },
        Outputs{
            { "baseColor", half3() },
            { "transparency", half1() },
        },
        Inputs{
            { "deviceUV", float2(), TEXCOORD },
        },
        Content{
            R"({
    half4 tmp = tex2D(MainTex, deviceUV);
    baseColor = tmp.xyz;
    transparency = tmp.w;
}
)"
        }
    );

    ADD_MODULE(SampleNormalMap, Inline,
        Attributes{
            { "BumpMap", Texture2D },
        },
        Outputs{
            { "normalTS", half3() },
        },
        Inputs{
            { "deviceUV", float2(), TEXCOORD },
        },
        Content{
            "normalTS = UnpackNormal(tex2D(BumpMap, deviceUV)).xyz;\n"
        }
    );
    
    ADD_MODULE(SampleMaterial,
        Attributes{
            { "Material", Texture2D },
        },
        Outputs{
            { "metallic", half1() },
            { "perceptualSmoothness", half1() },
            { "occlusion", half1() },
        },
        Inputs{
            { "deviceUV", float2(), TEXCOORD },
        },
        Content{
            R"(half3 tmp = tex2D(Material, deviceUV).xyz;
metallic = tmp.x;
perceptualSmoothness = tmp.y;
occlusion = tmp.z;
)"
        }
    );

    // material compute
    ADD_MODULE(PerceptualSmoothnessToPerceptualRoughness, Inline,
        Outputs{
            { "perceptualRoughness", half1() }
        },
        Inputs{
            { "perceptualSmoothness", half1() }
        },
        Content{ "perceptualRoughness = 1.0h - perceptualSmoothness;\n" }
    );

    ADD_MODULE(PerceptualRoughnessToRoughness, Inline,
        Outputs{
            { "roughness", half1() },
        },
        Inputs{
            { "perceptualRoughness", half1() },
        },
        Content{ "roughness = perceptualRoughness * perceptualRoughness;\n" }
    );
    
    ADD_MODULE(WorldShadingNormal, Inline,
        Outputs{
            { "worldNormal", half3() }
        },
        Inputs{
            { "normalTS", half3() },
            { "tspace0", half4(), TEXCOORD },
            { "tspace1", half4(), TEXCOORD },
            { "tspace2", half4(), TEXCOORD },
        },
        Content{ R"(worldNormal.x = dot(half3(tspace0.xyz), normalTS);
worldNormal.y = dot(half3(tspace1.xyz), normalTS);
worldNormal.z = dot(half3(tspace2.xyz), normalTS);
worldNormal = normalize(worldNormal);
)" });

    // Lighting
    ADD_MODULE(LightIntensity, Inline,
        Outputs{
            { "lightInten", half3() },
        },
        Content{ "lightInten = _LightColor0.xyz;\n", UnityCG }        
    );
     
    ADD_MODULE(DirectionalLightDir, Inline,
        Outputs{
            { "lightDir", half3(), TEXCOORD },
        },
        Content{ "lightDir = _WorldSpaceLightPos0.xyz;\n", UnityCG }
    );
    
    ADD_MODULE(LightAttenuation, Inline,
        Outputs{
            { "atten", fixed1(), NoDeclare },
        },
        Inputs{
            { "worldPos", float3() },
        },
        Content{ R"(UNITY_LIGHT_ATTENUATION(atten, IN, worldPos);
)" });
    
    ADD_MODULE(SUnityAmbientOrLightmapUV,
        Outputs{
            { "ambientOrLightmapUV", half4(), TEXCOORD },
        },
        Inputs{
            { "deviceUV1", float2(), TEXCOORD },
            { "deviceUV2", float2(), TEXCOORD },
            { "worldNormal", half3() },
            { "worldPos", float3() },
        },
        Content{ R"(ambientOrLightmapUV = 0;
// Static lightmaps
#ifdef LIGHTMAP_ON
ambientOrLightmapUV.xy = deviceUV1.xy * unity_LightmapST.xy + unity_LightmapST.zw;
ambientOrLightmapUV.zw = 0;
// Sample light probe for Dynamic objects only (no static or dynamic lightmaps)
#elif UNITY_SHOULD_SAMPLE_SH

#ifdef VERTEXLIGHT_ON
// Approximated illumination from non-important point lights
ambientOrLightmapUV.rgb = Shade4PointLights(
    unity_4LightPosX0, unity_4LightPosY0, unity_4LightPosZ0,
    unity_LightColor[0].rgb, unity_LightColor[1].rgb, unity_LightColor[2].rgb, unity_LightColor[3].rgb,
    unity_4LightAtten0, worldPos, worldNormal);
#endif

ambientOrLightmapUV.rgb = ShadeSHPerVertex(worldNormal, ambientOrLightmapUV.rgb);
#endif

#ifdef DYNAMICLIGHTMAP_ON
ambientOrLightmapUV.zw = deviceUV2.xy * unity_DynamicLightmapST.xy + unity_DynamicLightmapST.zw;
#endif
)" });

    ADD_MODULE(SUnityGI,
        Outputs{
            { "gi", ShaderStruct{ "UnityGI" } },
        },
        Inputs{
            { "lightDir", half3() },
            { "worldNormal", half3() },
            { "perceptualSmoothness", half1() },
            { "metallic", half1() },
            { "worldPos", float3() },
            { "viewDir", half3() },
            { "atten", fixed1() },
            { "ambientOrLightmapUV", half4() },
            { "baseColor", half3() },
            { "transparency", half1() },
            { "occlusion", half1() },
            { "lightInten", half3() },
        },
        Content{ R"(#ifdef UNITY_COMPILER_HLSL
SurfaceOutputStandard o = (SurfaceOutputStandard)0;
#else
SurfaceOutputStandard o;
#endif
o.Albedo = baseColor;
o.Normal = worldNormal;
o.Emission = 0.0;
o.Metallic = metallic;
o.Alpha = transparency;
o.Occlusion = occlusion;
o.Smoothness = perceptualSmoothness;

UNITY_INITIALIZE_OUTPUT(UnityGI, gi);
gi.indirect.diffuse = 0;
gi.indirect.specular = 0;
gi.light.color = lightInten;
gi.light.dir = lightDir;

UnityGIInput giInput;
UNITY_INITIALIZE_OUTPUT(UnityGIInput, giInput);
giInput.light = gi.light;
giInput.worldPos = worldPos;
giInput.worldViewDir = viewDir;
giInput.atten = atten;
#if defined(LIGHTMAP_ON) || defined(DYNAMICLIGHTMAP_ON)
giInput.ambient = 0;
giInput.lightmapUV = ambientOrLightmapUV;
#else
giInput.ambient = ambientOrLightmapUV.rgb;
giInput.lightmapUV = 0;
#endif
giInput.probeHDR[0] = unity_SpecCube0_HDR;
giInput.probeHDR[1] = unity_SpecCube1_HDR;
#if defined(UNITY_SPECCUBE_BLENDING) || defined(UNITY_SPECCUBE_BOX_PROJECTION)
giInput.boxMin[0] = unity_SpecCube0_BoxMin; // .w holds lerp value for blending
#endif
#ifdef UNITY_SPECCUBE_BOX_PROJECTION
giInput.boxMax[0] = unity_SpecCube0_BoxMax;
giInput.probePosition[0] = unity_SpecCube0_ProbePosition;
giInput.boxMax[1] = unity_SpecCube1_BoxMax;
giInput.boxMin[1] = unity_SpecCube1_BoxMin;
giInput.probePosition[1] = unity_SpecCube1_ProbePosition;
#endif

LightingStandard_GI(o, giInput, gi);
)" });

    // Shading
    ADD_MODULE(SUnityLightingStandard,
        Outputs{
            { "color", half4() },
        },
        Inputs{
            { "gi", ShaderStruct{ "UnityGI" } },
            { "baseColor", half3() },
            { "transparency", half1() },
            { "perceptualSmoothness", half1() },
            { "metallic", half1() },
            { "worldNormal", half3() },
            { "viewDir", half3() },
        },
        Content{ R"(half oneMinusReflectivity;
half3 specColor;
half3 albedo = DiffuseAndSpecularFromMetallic(baseColor, metallic, /*out*/ specColor, /*out*/ oneMinusReflectivity);

// shader relies on pre-multiply alpha-blend (_SrcBlend = One, _DstBlend = OneMinusSrcAlpha)
// this is necessary to handle transparency in physically correct way - only diffuse component gets affected by alpha
half outputAlpha;
albedo = PreMultiplyAlpha (albedo, transparency, oneMinusReflectivity, /*out*/ outputAlpha);

color = UNITY_BRDF_PBS (albedo, specColor, oneMinusReflectivity, perceptualSmoothness, worldNormal, viewDir, gi.light, gi.indirect);
color.a = outputAlpha;
)", UnityCG }
    );
    
    ADD_MODULE(SUnityUnpackTexcoord, Inline,
        Outputs{
            { "deviceUV", float2(), TEXCOORD },
        },
        Inputs{
            { "texcoord", float4(), TEXCOORD },
        },
        Content{ R"(deviceUV = texcoord.xy;
)", UnityCG }
    );

    ADD_MODULE(SUnityUnpackTexcoord1, Inline,
        Outputs{
            { "deviceUV1", float2(), TEXCOORD },
        },
        Inputs{
            { "texcoord1", float4(), TEXCOORD },
        },
        Content{ R"(deviceUV1 = texcoord1.xy;
)", UnityCG }
    );
    
    ADD_MODULE(SUnityUnpackTexcoord2, Inline,
        Outputs{
            { "deviceUV2", float2(), TEXCOORD },
        },
        Inputs{
            { "texcoord2", float4(), TEXCOORD },
        },
        Content{ R"(deviceUV2 = texcoord2.xy;
)", UnityCG }
    );

    ADD_MODULE(SUnityUnpackTexcoord3, Inline,
        Outputs{
            { "deviceUV3", float2(), TEXCOORD },
        },
        Inputs{
            { "texcoord3", float4(), TEXCOORD },
        },
        Content{ R"(deviceUV3 = texcoord3.xy;
)", UnityCG }
    );
}

}
