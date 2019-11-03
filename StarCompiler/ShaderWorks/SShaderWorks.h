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
#include <StarCompiler/ShaderGraph/SShaderProgram.h>
#include <StarCompiler/ShaderGraph/SShaderGroup.h>

namespace Star::Graphics::Render::Shader {

class ShaderWorks {
public:
    class Pipeline {
    public:
        std::string mName;
        std::array<Map<std::string, ShaderGroup>, UpdateEnum::UpdateCount> mGroups;
    };

    class Bundle {
    public:
        std::string mName;
        Map<std::string, Pipeline> mPipelines;
    };

    ShaderGroup& getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName);
    ShaderProgram& createProgram(std::string_view shaderName);
    void bindProgram(std::string_view shaderName,
        std::string_view bundleName, std::string_view pipelineName, std::string_view passName);

    ShaderGraph createModuleGroup(const std::vector<std::string>& names, ShaderStageType stage) const;

    void buildRootSignatures(UpdateEnum frequency);

    void outputShaders() const;
    void outputRootSignatures() const;

    void saveShaders(const std::filesystem::path& folder) const;

    AttributeMap mAttributes;
    NameMap<ShaderModule> mModules;
    Map<std::string, ShaderProgram> mPrograms;
    Map<std::string, Bundle> mBundles;
};

}
