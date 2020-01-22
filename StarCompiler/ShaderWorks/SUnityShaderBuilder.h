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
#include <StarCompiler/ShaderGraph/SShaderPrototype.h>

namespace Star::Graphics::Render::Shader {

class UnityShaderBuilder {
public:
    std::string generateShader(const AttributeMap& attrs, const ShaderPrototype& p) const;
private:
    std::string generateProperties(const AttributeMap& attrMap, const ShaderPrototype& p) const;
    std::string generateSubShaderStates(const ShaderLevel& subshader) const;
    std::string generatePassStates(const ShaderPass& p) const;
    std::string generateProgram(const AttributeMap& attrs, const ShaderPass& p) const;
    std::string generateAttributes(const AttributeMap& attrs, bool instancing) const;
};

}
