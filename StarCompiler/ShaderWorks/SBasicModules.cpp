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
        { "Time", float4(), PerFrame, Unity::BuiltIn },

        { "View", matrix(), PerPass, Unity::BuiltIn },
        { "Proj", matrix(), PerPass, Unity::BuiltIn },

        { "World", matrix(), PerInstance, Unity::BuiltIn },
        { "WorldInvT", matrix(), PerInstance, Unity::BuiltIn },
        { "WorldView", matrix(), PerInstance, Unity::BuiltIn },

        { "PointSampler", SamplerState, PerFrame, RootLevel },
        { "LinearSampler", SamplerState, PerFrame, RootLevel },

        { "BaseColor", Texture2D },
        { "WorldNormalMap", Texture2D },

        { "Normal", Texture2D, PerPass },
        { "Albedo", Texture2D, PerPass },
        { "Radiance", Texture2D, PerPass },
        { "DepthStencil", Texture2D, PerPass },
    });

    ADD_MODULE(Empty, Inline);

    ADD_MODULE(FullQuadClipPos, Inline,
        Outputs{
            { "clipPos", float4(), SV_Position },
        },
        Inputs{
            { "vertexID", uint1(), SV_VertexID }
        },
        Content{ R"(clipPos.x = (float)(vertexID / 2) * 4.0f - 1.0f;
clipPos.y = (float)(vertexID % 2) * 4.0f - 1.0f;
clipPos.z = 0.5f;
clipPos.w = 1.0f;
)"});

    ADD_MODULE(FullQuadUV, Inline,
        Outputs{
            { "uv", float2(), TEXCOORD }
        },
        Inputs{
            { "vertexID", uint1(), SV_VertexID }
        },
        Content{ R"(uv.x = (float)(vertexID / 2) * 2.0f;
uv.y = 1.0 - (float)(vertexID % 2) * 2.0f;
)"});

    ADD_MODULE(ClipPos, Inline,
        Attributes{
            { "WorldView", matrix() },
            { "View", matrix() },
            { "Proj", matrix() },
        },
        Outputs{
            { "clipPos", float4(), SV_Position }
        },
        Inputs{
            { "vertex", float4(), POSITION }
        },
        Contents{
            { "clipPos = mul(Proj, mul(WorldView, vertex));\n" },
            { "clipPos = UnityObjectToClipPos(vertex);\n", UnityCG },
        }
    );

    ADD_MODULE(WorldPos, Inline,
        Attributes{
            { "World", matrix() },
        },
        Outputs{
            { "worldPos", float3(), TEXCOORD }
        },
        Inputs{
            { "vertex", float4(), POSITION }
        },
        Content{ R"(worldPos = mul(World, vertex).xyz;
)" }
    );
    
    ADD_MODULE(WorldGeometryNormal, Inline,
        Attributes{
            { "WorldInvT", matrix() },
        },
        Outputs{
            { "worldNormal", half3(), TEXCOORD }
        },
        Inputs{
            { "normal", half4(), NORMAL }
        },
        Content{ R"(worldNormal = normalize(mul((float3x3)WorldInvT, normal.xyz));
)" }
    );

    ADD_MODULE(VisualizeWorldNormal, Inline,
        Outputs{
            { "color", half4() },
        },
        Inputs{
            { "worldNormal", half3() }
        },
        Content{ R"(color = half4(0.5f * (worldNormal.xyz + 1.0f), 1.0f);
)" }
    );

    ADD_MODULE(ScreenGreen, Inline,
        Attributes{
            { "Time", float4() },
        },
        Outputs{
            { "color", half4()  }
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
            { "color", half4()  }
        },
        Inputs{
            { "uv", float2(), TEXCOORD }
        },
        Content{ R"(color = half4(Radiance.Sample(PointSampler, uv).xyz, 1.0h);
)" }
    );

    ADD_MODULE(UnpackGBuffers, Inline,
        Attributes{
            { "Albedo", Texture2D },
            { "Normal", Texture2D },
            { "DepthStencil", Texture2D },
            { "PointSampler", SamplerState },
        },
        Outputs{
            { "albedo", half3() },
            { "worldNormal", half3() },
            { "depth", float1() },
        },
        Inputs{
            { "uv", float2(), TEXCOORD },
        },
        Content{ R"(albedo = Albedo.Sample(PointSampler, uv).xyz;
worldNormal = Normal.Sample(PointSampler, uv).xyz;
depth = DepthStencil.Sample(PointSampler, uv).x;
)" }
    );

    ADD_MODULE(DeferredLambertian, Inline,
        Outputs{
            { "color", half4() },
        },
        Inputs{
            { "albedo", half3() },
            { "worldNormal", half3() },
            { "depth", float1() },
        },
        Content{ R"(color = half4(albedo * normalize(dot(worldNormal, half3(1, 1, 1))) * depth, 1.0h);
)" }
    );

    ADD_MODULE(PackGBuffers, Inline,
        Outputs{
            { "color0", half4() },
            { "color1", half4() },
        },
        Inputs{
            { "baseColor", half3()  },
            { "transparency", half1(), {} },
            { "worldNormal", half3()  },
        },
        Content{ R"(color0 = half4(baseColor, transparency);
color1 = half4(worldNormal, 1.0h);
)" }
    );

    ADD_MODULE(BaseColorAndTransparency, Inline,
        Attributes{
            { "BaseColor", Texture2D },
            { "LinearSampler", SamplerState },
        },
        Outputs{
            { "baseColor", half3() },
            { "transparency", half1(), {} },
        },
        Inputs{
            { "uv", float2(), TEXCOORD },
        },
        Content{ R"({
half4 tmp = BaseColor.Sample(LinearSampler, uv);
baseColor = tmp.xyz;
transparency = tmp.w;
}
)" }
    );

    ADD_MODULE(WorldNormalMap, Inline,
        Attributes{
            { "WorldNormalMap", Texture2D },
            { "LinearSampler", SamplerState },
        },
        Outputs{
            { "worldNormal", half3() },
        },
        Inputs{
            { "uv", float2(), TEXCOORD },
        },
        Content{ R"(worldNormal = WorldNormalMap.Sample(LinearSampler, uv).xyz;
)" }
    );
}

}
