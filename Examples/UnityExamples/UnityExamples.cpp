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
#include <StarCompiler/ShaderGraph/SShaderDatabase.h>
#include <StarCompiler/ShaderGraph/SShaderDSL.h>
#include <StarCompiler/ShaderWorks/SUnityShaderBuilder.h>

using namespace Star;
using namespace Star::Graphics;
using namespace Star::Graphics::Render;
using namespace Star::Graphics::Render::Shader;
using namespace Star::Graphics::Render::Shader::Unity;

int buildUnityShaders(const ShaderWorks& shaderWorks, ShaderDatabase& db) {
    Shader("Star/PBR Standard") {

    SubShader() {
    SubShader << Tags{ { "Queue", "Geometry" }, { "RenderType", "Opaque" } };
    SubShader << LOD{ 100 };

    Pass() {
    Pass << Tag{ "LightMode", "ForwardBase" };
    Pass << ZWrite{ true };
    Pass << ZTest{ LessEqual };

    Pass.mUnityReceiveShadow = true;
    Pass.mUnityInstancing = true;

    Program() {
        Program << R"(
#pragma multi_compile_fwdbase
#pragma multi_compile_instancing

#pragma vertex vert
#pragma fragment frag

#include "HLSLSupport.cginc"
#include "UnityCG.cginc"
#include "UnityPBSLighting.cginc"
#include "AutoLight.cginc"
)";
        PixelShader({ "color", half4(), SV_Target }) {
            // Shading
            Group(SUnityLightingStandard);

            // Lighting
            Group(SUnityGI);
            Group(LightIntensity, LightAttenuation, DirectionalLightDir);

            // Surface Geometry
            Group(NormalizeViewDir, WorldShadingNormal);
            Group(UnpackTangent, UnpackBinormal, UnpackNormal, UnpackViewDir);

            // Material
            Group(SampleBaseColor, SampleNormalMap, SampleMaterial);
            Group(DefaultBaseColor, DefaultTransparency, DefaultPerceptualSmoothness, DefaultMetallic, DefaultOcclusion);
        }

        VertexShader() {
            Group(SUnityAmbientOrLightmapUV);
            Group(PackTangentSpaceAndViewDir);
            Group(ViewDir);
            Group(ViewVector, CalculateWorldBinormal);
            Group(ClipPos, WorldPos, WorldNormal, WorldTangent);
            UnityVertex(AppData::Full);
        }
    } // Program
    } // Pass
    } // SubShader
    } // Shader

    BUILD("Star/PBR Standard", "../../Unity/Shaders/PBRStandard.shader");

    return 0;
}

int main() {
    std::cout << "---------------------------------------\n";
    std::cout << "create render graph2\n";
    std::cout << "---------------------------------------\n";

    try {
        ShaderWorks shaderWorks;
        ShaderDatabase shaderDB;
        createUnityModules(shaderWorks);
        buildUnityShaders(shaderWorks, shaderDB);
    } catch (std::invalid_argument & e) {
        {
            CONSOLE_COLOR(Red);
            std::cout << "[error] ";
        }
        std::cout << e.what() << std::endl;
        return 1;
    }

    CONSOLE_COLOR(Green);
    std::cout << "[succeeded]";

    return 0;
}
