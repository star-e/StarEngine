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
#include <StarCompiler/ShaderGraph/SShaderProgram.h>
#include <StarCompiler/ShaderGraph/SShaderGroup.h>
#include <StarCompiler/ShaderGraph/SShaderModules.h>

namespace Star::Graphics::Render::Shader {

class ShaderGroups {
public:
    using PassGroup = std::array<Map<std::string, ShaderGroup>, UpdateEnum::UpdateCount>;

    ShaderGroup* try_getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName);
    ShaderGroup const * try_getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) const;

    ShaderGroup& getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName);
    ShaderGroup const& getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) const;

    void bindProgram(const ShaderProgram& program, std::string_view shaderName,
        std::string_view bundleName, std::string_view pipelineName, std::string_view passName);

    void collectAttributes(const ShaderModules& modules, AttributeDatabase& database) const;
    void buildRootSignatures(const ShaderModules& modules, UpdateEnum frequency);

    Map<std::string, Map<std::string, PassGroup>> mSolutions;
};

}
