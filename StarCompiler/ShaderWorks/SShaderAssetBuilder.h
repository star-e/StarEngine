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
#include <Star/Graphics/SContentTypes.h>
#include <StarCompiler/ShaderGraph/SShaderDatabase.h>
#include <StarCompiler/ShaderGraph/SShaderGroups.h>

namespace Star::Graphics::Render::Shader {

class ShaderAssetBuilder {
public:
    ShaderAssetBuilder()
        : mShaders(std::pmr::get_default_resource())
    {

    }
    ShaderAssetBuilder(const ShaderAssetBuilder&) = delete;
    ShaderAssetBuilder& operator=(const ShaderAssetBuilder&) = delete;

    void buildShaders(const ShaderDatabase& database, const ShaderGroups& sw, const ShaderModules& modules);

    void build(Resources& resources) const;

    PmrStringMap<ShaderData> mShaders;
};

void buildShaderData(const ShaderPrototype& prototype, const ShaderModules& modules,
    const ShaderGroups& sw, ShaderData& prototypeData, bool bCompile = true);
void buildShaderText(std::ostream& oss, const ShaderData& prototypeData);
void buildShaderText2(std::ostream& oss, const ShaderData& prototype);

}
