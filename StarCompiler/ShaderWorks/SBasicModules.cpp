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

#include "SBasicModules.h"
#include <StarCompiler/ShaderGraph/SShaderDSL.h>

namespace Star::Graphics::Render::Shader {

using namespace DSL;

void createBasicModules(ShaderModules& modules) {
    ADD_ATTRIBUTES({
        { "Time", float4, TypeFrame, Unity::BuiltIn },
        { "Exposure", float1, TypeFrame, Unity::BuiltIn },

        { "View", matrix, TypePass, Unity::BuiltIn },
        { "Proj", matrix, TypePass, Unity::BuiltIn },

        { "World", matrix, TypeInstance, Unity::BuiltIn },
        { "WorldInvT", matrix, TypeInstance, Unity::BuiltIn },
        { "WorldView", matrix, TypeInstance, Unity::BuiltIn },

        { "PointSampler", SamplerState, TypeStaticSampler },
        { "LinearSampler", SamplerState, TypeStaticSampler },

        { "Normal", half3, Texture2D, TypeRenderTarget },
        { "BaseColor", half3, Texture2D, TypeRenderTarget },
        { "Radiance", half3, Texture2D, TypeRenderTarget },
        { "DepthStencil", float1, Texture2D, TypeRenderTarget },

        { "MainTex", half4, Texture2D, TypeMaterial },
        { "NormalMap", half3, Texture2D, TypeMaterial },
    });

    ADD_MODULE(Empty, Inline);

    ADD_MODULE(FullQuadClipPos, Inline,
        Outputs{
            { "clipPos", float4, SV_Position },
        },
        Inputs{
            { "vertexID", uint1, SV_VertexID }
        },
        Content{ R"(clipPos.x = (float)(vertexID % 2) * 4.0f - 1.0f;
clipPos.y = (float)(vertexID / 2) * 4.0f - 1.0f;
clipPos.z = 0.5f;
clipPos.w = 1.0f;
)"});

    ADD_MODULE(FullQuadUV, Inline,
        Outputs{
            { "uv", float2, TEXCOORD }
        },
        Inputs{
            { "vertexID", uint1, SV_VertexID }
        },
        Content{ R"(uv.x = (float)(vertexID % 2) * 2.0f;
uv.y = 1.0 - (float)(vertexID / 2) * 2.0f;
)"});

    ADD_MODULE(ClipPos, Inline,
        Attributes{
            { "WorldView", matrix },
            { "View", matrix },
            { "Proj", matrix },
        },
        Outputs{
            { "clipPos", float4, SV_Position }
        },
        Inputs{
            { "vertex", float4, POSITION }
        },
        Contents{
            { "clipPos = mul(Proj, mul(WorldView, vertex));\n" },
            { "clipPos = UnityObjectToClipPos(vertex);\n", UnityCG },
        }
    );

    ADD_MODULE(WorldPos, Inline,
        Attributes{
            { "World", matrix },
        },
        Outputs{
            { "worldPos", float3, TEXCOORD }
        },
        Inputs{
            { "vertex", float4, POSITION }
        },
        Content{ R"(worldPos = mul(World, vertex).xyz;
)" }
    );
    
    ADD_MODULE(WorldGeometryNormal, Inline,
        Attributes{
            { "WorldInvT", matrix },
        },
        Outputs{
            { "worldNormal", half3, TEXCOORD }
        },
        Inputs{
            { "normal", half4, NORMAL }
        },
        Content{ R"(worldNormal = normalize(mul((float3x3)WorldInvT, normal.xyz));
)" }
    );

    ADD_MODULE(LocalTangent, Inline,
        Attributes{
        },
        Outputs{
            { "tangent", half4, TEXCOORD },
        },
        Inputs{
            { "tangent", half4, TANGENT },
        },
        Content{ R"(
)" }
    );

    ADD_MODULE(ScreenGreen, Inline,
        Attributes{
            { "Time", float4 },
        },
        Outputs{
            { "color", half4  }
        },
        Content{ R"(color = half4(0.0h, 0.5h + 0.5h * fmod(Time.x, 8.0f), 0.0h, 1.0h);
)" }
    );

    ADD_MODULE(CopyRadiance, Inline,
        Attributes{
            { "Radiance", Texture2D },
            { "PointSampler", SamplerState },
        },
        Outputs{
            { "color", half4  }
        },
        Inputs{
            { "uv", float2, TEXCOORD }
        },
        Content{ R"(color = half4(Radiance.Sample(PointSampler, uv).xyz, 1.0h);
)" }
    );

    ADD_MODULE(UnpackGBuffers, Inline,
        Attributes{
            { "BaseColor", Texture2D },
            { "Normal", Texture2D },
            { "DepthStencil", Texture2D },
            { "PointSampler", SamplerState },
        },
        Outputs{
            { "baseColor", half3 },
            { "worldNormal", half3 },
            { "depth", float1 },
        },
        Inputs{
            { "uv", float2, TEXCOORD },
        },
        Content{ R"(baseColor = BaseColor.Sample(PointSampler, uv).xyz;
worldNormal = 2.0h * Normal.Sample(PointSampler, uv).xyz - 1.0h;
depth = DepthStencil.Sample(PointSampler, uv).x;
)" }
    );

    ADD_MODULE(PackGBuffers, Inline,
        Outputs{
            { "color0", half4 },
            { "color1", half4 },
        },
        Inputs{
            { "baseColor", half3  },
            { "transparency", half1 },
            { "worldNormal", half3  },
        },
        Content{ R"(color0 = half4(baseColor, transparency);
color1 = half4(worldNormal * 0.5h + 0.5h, 1.0h);
)" }
    );

    ADD_MODULE(BaseColor, Inline,
        Attributes{
            { "MainTex", Texture2D },
            { "LinearSampler", SamplerState },
        },
        Outputs{
            { "baseColor", half3 },
        },
        Inputs{
            { "uv", float2, TEXCOORD },
        },
        Content{ R"(baseColor = MainTex.Sample(LinearSampler, uv).xyz;
)" }
    );

    ADD_MODULE(BaseColorAndTransparency, Inline,
        Attributes{
            { "MainTex", Texture2D },
            { "LinearSampler", SamplerState },
        },
        Outputs{
            { "baseColor", half3 },
            { "transparency", half1 },
        },
        Inputs{
            { "uv", float2, TEXCOORD },
        },
        Content{ R"({
    half4 tmp = MainTex.Sample(LinearSampler, uv);
    baseColor = tmp.xyz;
    transparency = tmp.w;
}
)" }
    );
    
    ADD_MODULE(InitColor, Inline,
        Attributes{
        },
        Outputs{
            { "color", half4 },
        },
        Inputs{
        },
        Content{ R"(color = half4(0, 0, 0, 1);
)" }
    );
        
    ADD_MODULE(InitTransparency, Inline,
        Attributes{
        },
        Outputs{
            { "transparency", half1 },
        },
        Inputs{
        },
        Content{ R"(transparency = 1.0h;
)" }
    );

    ADD_MODULE(DirectionalLight, Inline,
        Attributes{
        },
        Outputs{
            { "lightDirection", half3 },
            { "lightIntensity", half3 },
        },
        Inputs{
        },
        Content{ R"(lightDirection = normalize(half3(1.0h, 1.0h, 1.0h));
lightIntensity = half3(1.0h, 1.0h, 1.0h);
)" }
    );

    ADD_MODULE(NdotL, Inline,
        Attributes{
        },
        Outputs{
            { "ndotl", half1 },
        },
        Inputs{
            { "worldNormal", half3 },
            { "lightDirection", half3 },
        },
        Content{ R"(ndotl = saturate(dot(worldNormal, lightDirection));
)" }
    );

    ADD_MODULE(EvaluateDirectionalLight, Inline,
        Attributes{
        },
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "color", half4 },
            { "baseColor", half3 },
            { "ndotl", half1 },
            { "lightIntensity", half3 },
        },
        Content{ R"(color.xyz += baseColor * ndotl * lightIntensity;
)" }
    );

    // Normal Mapping
    ADD_MODULE(WorldNormal, Inline,
        Attributes{
            { "WorldInvT", matrix },
        },
        Outputs{
            { "worldNormal", half3, TEXCOORD },
        },
        Inputs{
            { "normal", half3, NORMAL },
        },
        Contents{
            { "worldNormal = normalize(mul(WorldInvT, half4(normal.xyz, 0.0h)).xyz);\n" },
        }
    );
    
    ADD_MODULE(WorldTangent, Inline,
        Attributes{
            { "WorldInvT", matrix },
        },
        Outputs{
            { "worldTangent", half3, TEXCOORD },
        },
        Inputs{
            { "tangent", half4, TANGENT },
        },
        Contents{
            { "worldTangent = normalize(mul(WorldInvT, half4(tangent.xyz, 0.0h)).xyz);\n" },
        }
    );

    ADD_MODULE(CalculateWorldBinormal, Inline,
        Outputs{
            { "worldBinormal", half3, TEXCOORD },
        },
        Inputs{
            { "worldTangent", half3 },
            { "worldNormal", half3 },
            { "tangent", half4, TANGENT },
        },
        Contents{
            { "worldBinormal = cross(worldNormal, worldTangent) * tangent.w;\n" },
        }
    );

    ADD_MODULE(PackTangentSpace, Inline,
        Outputs{
            { "tangentToWorld0", half4, TEXCOORD },
            { "tangentToWorld1", half4, TEXCOORD },
            { "tangentToWorld2", half4, TEXCOORD },
        },
        Inputs{
            { "worldTangent", half3 },
            { "worldBinormal", half3 },
            { "worldNormal", half3 },
        },
        Contents{
            { R"(tangentToWorld0 = half4(worldTangent.x, worldBinormal.x, worldNormal.x, 0.0h);
tangentToWorld1 = half4(worldTangent.y, worldBinormal.y, worldNormal.y, 0.0h);
tangentToWorld2 = half4(worldTangent.z, worldBinormal.z, worldNormal.z, 0.0h);
)" }
        }
    );

    ADD_MODULE(NormalMap, Inline,
        Attributes{
            { "NormalMap", Texture2D },
            { "LinearSampler", SamplerState },
        },
        Outputs{
            { "tangentNormal", half3 },
        },
        Inputs{
            { "uv", float2, TEXCOORD },
        },
        Content{ R"(tangentNormal = NormalMap.Sample(LinearSampler, uv).xyz * 2 - 1;
)" }
    );

    ADD_MODULE(TangentNormalToWorld, Inline,
        Outputs{
            { "worldNormal", half3 }
        },
        Inputs{
            { "tangentNormal", half3 },
            { "tangentToWorld0", half4, TEXCOORD },
            { "tangentToWorld1", half4, TEXCOORD },
            { "tangentToWorld2", half4, TEXCOORD },
        },
        Content{ R"(worldNormal.x = dot(tangentToWorld0.xyz, tangentNormal);
worldNormal.y = dot(tangentToWorld1.xyz, tangentNormal);
worldNormal.z = dot(tangentToWorld2.xyz, tangentNormal);
worldNormal = normalize(worldNormal);
)" });
    
    ADD_MODULE(UnpackTangent, Inline,
        Outputs{
            { "worldTangent", half3 },
        },
        Inputs{
            { "tangentToWorld0", half4, TEXCOORD },
            { "tangentToWorld1", half4, TEXCOORD },
            { "tangentToWorld2", half4, TEXCOORD },
        },
        Contents{
            { "worldTangent = half3(tangentToWorld0.x, tangentToWorld1.x, tangentToWorld2.x);\n" }
        }
    );

    ADD_MODULE(UnpackBinormal, Inline,
        Outputs{
            { "worldBinormal", half3 },
        },
        Inputs{
            { "tangentToWorld0", half4, TEXCOORD },
            { "tangentToWorld1", half4, TEXCOORD },
            { "tangentToWorld2", half4, TEXCOORD },
        },
        Contents{
            { "worldBinormal = half3(tangentToWorld0.y, tangentToWorld1.y, tangentToWorld2.y);\n" }
        }
    );

    ADD_MODULE(UnpackNormal, Inline,
        Outputs{
            { "worldNormal", half3 },
        },
        Inputs{
            { "tangentToWorld0", half4, TEXCOORD },
            { "tangentToWorld1", half4, TEXCOORD },
            { "tangentToWorld2", half4, TEXCOORD },
        },
        Contents{
            { "worldNormal = half3(tangentToWorld0.z, tangentToWorld1.z, tangentToWorld2.z);\n" }
        }
    );
    
    ADD_MODULE(VisualizeWorldTangent, Inline,
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "worldTangent", half3 }
        },
        Content{ R"(color = saturate(half4(0.5f * (worldTangent.xyz + 1.0f), 1.0f));
color.xyz = pow(color.xyz, 2.2h);
)" }
    );

    ADD_MODULE(VisualizeWorldBinormal, Inline,
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "worldBinormal", half3 }
        },
        Content{ R"(color = saturate(half4(0.5f * (worldBinormal.xyz + 1.0f), 1.0f));
color.xyz = pow(color.xyz, 2.2h);
)" }
    );

    ADD_MODULE(VisualizeWorldNormal, Inline,
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "worldNormal", half3 }
        },
        Content{ R"(color = saturate(half4(0.5f * (worldNormal.xyz + 1.0f), 1.0f));
color.xyz = pow(color.xyz, 2.2h);
)" }
    );

    ADD_MODULE(VisualizeTangentW, Inline,
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "tangent", half4, TEXCOORD },
        },
        Content{ R"(color.xyz = tangent.w * 0.5h + 0.5h;
color.w = 1.0h;
)" }
    );

    ADD_MODULE(VisualizeNormalMap, Inline,
        Outputs{
            { "color", half4 },
        },
        Inputs{
            { "tangentNormal", half3 },
        },
        Content{ R"(color = saturate(half4(0.5f * (tangentNormal.xyz + 1.0f), 1.0f));
color.xyz = pow(color.xyz, 2.2h);
)" }
    );

    // Alpha Test
    ADD_MODULE(AlphaTest, Inline,
        Outputs{
            {}, // global state
        },
        Inputs{
            {}, // global state
            { "transparency", half1 },
        },
        Content{ R"(clip(transparency - 0.5f);
)" }
    );
}

}
