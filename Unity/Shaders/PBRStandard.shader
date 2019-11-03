Shader "Star/PBR Standard" {

Properties {
    _BumpMap("BumpMap", 2D) = "white" {}
    _MainTex("MainTex", 2D) = "white" {}
    _Material("Material", 2D) = "white" {}
}

SubShader {

Tags { "Queue" = "Geometry" "RenderType" = "Opaque" }

LOD 100

Pass {

Tags { "LightMode" = "ForwardBase" }

ZWrite On

ZTest LEqual

CGPROGRAM

#pragma multi_compile_fwdbase
#pragma multi_compile_instancing

#pragma vertex vert
#pragma fragment frag

#include "HLSLSupport.cginc"
#include "UnityCG.cginc"
#include "UnityPBSLighting.cginc"
#include "AutoLight.cginc"

sampler2D _BumpMap;
sampler2D _MainTex;
sampler2D _Material;

void SUnityGI(half4 ambientOrLightmapUV, half atten, half3 baseColor, half3 lightDir, half3 lightInten, half metallic, half occlusion, half perceptualSmoothness, half transparency, half3 viewDir, half3 worldNormal, float3 worldPos, out UnityGI gi) {
#ifdef UNITY_COMPILER_HLSL
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
}

void SUnityLightingStandard(half3 baseColor, UnityGI gi, half metallic, half perceptualSmoothness, half transparency, half3 viewDir, half3 worldNormal, out half4 color) {
    half oneMinusReflectivity;
    half3 specColor;
    half3 albedo = DiffuseAndSpecularFromMetallic(baseColor, metallic, /*out*/ specColor, /*out*/ oneMinusReflectivity);

    // shader relies on pre-multiply alpha-blend (_SrcBlend = One, _DstBlend = OneMinusSrcAlpha)
    // this is necessary to handle transparency in physically correct way - only diffuse component gets affected by alpha
    half outputAlpha;
    albedo = PreMultiplyAlpha (albedo, transparency, oneMinusReflectivity, /*out*/ outputAlpha);

    color = UNITY_BRDF_PBS (albedo, specColor, oneMinusReflectivity, perceptualSmoothness, worldNormal, viewDir, gi.light, gi.indirect);
    color.a = outputAlpha;
}

void SampleMaterial(float2 deviceUV, out half metallic, out half occlusion, out half perceptualSmoothness) {
    half3 tmp = tex2D(_Material, deviceUV).xyz;
    metallic = tmp.x;
    perceptualSmoothness = tmp.y;
    occlusion = tmp.z;
}

void SUnityAmbientOrLightmapUV(float2 deviceUV1, float2 deviceUV2, half3 worldNormal, float3 worldPos, out half4 ambientOrLightmapUV) {
    ambientOrLightmapUV = 0;
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
}

struct v2f {
    float3 worldPos : TEXCOORD0;
    float2 deviceUV : TEXCOORD1;
    half4 ambientOrLightmapUV : TEXCOORD2;
    half4 tspace0 : TEXCOORD3;
    half4 tspace1 : TEXCOORD4;
    half4 tspace2 : TEXCOORD5;
    float4 pos : SV_Position;
    UNITY_SHADOW_COORDS(6)
    UNITY_VERTEX_INPUT_INSTANCE_ID
};

v2f vert(appdata_full v) {
    v2f o;
    UNITY_INITIALIZE_OUTPUT(v2f, o);
    UNITY_SETUP_INSTANCE_ID(v);
    half3 normal = v.normal;
    half4 tangent = v.tangent;
    float4 texcoord = v.texcoord;
    float4 texcoord1 = v.texcoord1;
    float4 texcoord2 = v.texcoord2;
    float4 vertex = v.vertex;

    float2 deviceUV2;
    deviceUV2 = texcoord2.xy;

    float2 deviceUV1;
    deviceUV1 = texcoord1.xy;

    float2 deviceUV;
    deviceUV = texcoord.xy;

    half3 worldTangent;
    worldTangent = UnityObjectToWorldDir(tangent.xyz);

    half3 worldNormal;
    worldNormal = UnityObjectToWorldNormal(normal.xyz);

    float3 worldPos;
    worldPos = mul(unity_ObjectToWorld, vertex).xyz;

    float4 clipPos;
    clipPos = UnityObjectToClipPos(vertex);

    half3 worldBinormal;
    worldBinormal = cross(worldNormal, worldTangent) * tangent.w * unity_WorldTransformParams.w;

    float3 viewVector;
    viewVector = _WorldSpaceCameraPos - worldPos;

    half3 viewDir;
    viewDir = normalize(viewVector);

    half4 tspace0;
    half4 tspace1;
    half4 tspace2;
    tspace0 = half4(worldTangent.x, worldBinormal.x, worldNormal.x, viewDir.x);
    tspace1 = half4(worldTangent.y, worldBinormal.y, worldNormal.y, viewDir.y);
    tspace2 = half4(worldTangent.z, worldBinormal.z, worldNormal.z, viewDir.z);

    half4 ambientOrLightmapUV;
    SUnityAmbientOrLightmapUV(deviceUV1, deviceUV2, worldNormal, worldPos, ambientOrLightmapUV);

    o.worldPos = worldPos;
    o.deviceUV = deviceUV;
    o.ambientOrLightmapUV = ambientOrLightmapUV;
    o.tspace0 = tspace0;
    o.tspace1 = tspace1;
    o.tspace2 = tspace2;
    o.pos = clipPos;

    UNITY_TRANSFER_SHADOW(o, texcoord1.xy);
    return o;
}

void frag(v2f IN, out half4 color : SV_Target0) {
    float3 worldPos = IN.worldPos;
    float2 deviceUV = IN.deviceUV;
    half4 ambientOrLightmapUV = IN.ambientOrLightmapUV;
    half4 tspace0 = IN.tspace0;
    half4 tspace1 = IN.tspace1;
    half4 tspace2 = IN.tspace2;

    half transparency;
    transparency = 1.0h;

    half metallic;
    half occlusion;
    half perceptualSmoothness;
    SampleMaterial(deviceUV, metallic, occlusion, perceptualSmoothness);

    half3 normalTS;
    normalTS = UnpackNormal(tex2D(_BumpMap, deviceUV)).xyz;

    half3 baseColor;
    baseColor = tex2D(_MainTex, deviceUV).xyz;

    half3 viewDir;
    viewDir = half3(tspace0.w, tspace1.w, tspace2.w);

    half3 worldNormal;
    worldNormal.x = dot(half3(tspace0.xyz), normalTS);
    worldNormal.y = dot(half3(tspace1.xyz), normalTS);
    worldNormal.z = dot(half3(tspace2.xyz), normalTS);
    worldNormal = normalize(worldNormal);

    viewDir = normalize(viewDir);

    half3 lightDir;
    lightDir = _WorldSpaceLightPos0.xyz;

    UNITY_LIGHT_ATTENUATION(atten, IN, worldPos);

    half3 lightInten;
    lightInten = _LightColor0.xyz;

    UnityGI gi;
    SUnityGI(ambientOrLightmapUV, atten, baseColor, lightDir, lightInten, metallic, occlusion, perceptualSmoothness, transparency, viewDir, worldNormal, worldPos, gi);

    SUnityLightingStandard(baseColor, gi, metallic, perceptualSmoothness, transparency, viewDir, worldNormal, color);
}

ENDCG

} // Pass end

} // SubShader end

} // Shader end
