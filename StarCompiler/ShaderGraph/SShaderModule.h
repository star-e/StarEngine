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
#include<StarCompiler/ShaderGraph/SShaderTypes.h>

namespace Star::Graphics::Render::Shader {

namespace DSL {

using Attributes = IdentityMap<AttributeUsage>;
using Inputs = NameMap<ShaderValue>;
using Outputs = NameMap<ShaderValue>;
using Contents = OrderedVariantIDMap2<Content>;

}

inline ShaderModule createShaderModule(std::string name = "",
    IdentityMap<AttributeUsage> attributes = {},
    NameMap<ShaderValue> outputs = {},
    NameMap<ShaderValue> inputs = {},
    Content content = {}
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), std::move(inputs),
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    IdentityMap<AttributeUsage> attributes = {},
    NameMap<ShaderValue> outputs = {},
    NameMap<ShaderValue> inputs = {},
    Content content = {}
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), std::move(inputs),
        {}, static_cast<ModuleBuilderFlags>(flags)
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    OrderedVariantIDMap2<Content> contents
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), std::move(inputs),
        std::move(contents),
    };
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), std::move(inputs),
        std::move(contents), static_cast<ModuleBuilderFlags>(flags)
    };
    return m;
}

//-----------------------------------------------------------------------
inline ShaderModule createShaderModule(std::string name,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs),
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), {},
        {}, static_cast<ModuleBuilderFlags>(flags)
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), {},
        std::move(contents),
    };
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    IdentityMap<AttributeUsage> attributes,
    NameMap<ShaderValue> outputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), std::move(attributes),
        std::move(outputs), {},
        std::move(contents), static_cast<ModuleBuilderFlags>(flags)
    };
    return m;
}

//-----------------------------------------------------------------------
inline ShaderModule createShaderModule(std::string name,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), std::move(inputs),
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), std::move(inputs),
        {}, static_cast<ModuleBuilderFlags>(flags)
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), std::move(inputs),
        std::move(contents),
    };
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    NameMap<ShaderValue> outputs,
    NameMap<ShaderValue> inputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), std::move(inputs),
        std::move(contents), static_cast<ModuleBuilderFlags>(flags)
    };
    return m;
}

//-----------------------------------------------------------------------
inline ShaderModule createShaderModule(std::string name,
    NameMap<ShaderValue> outputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), {},
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    NameMap<ShaderValue> outputs,
    Content content = {}
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), {},
        {}, static_cast<ModuleBuilderFlags>(flags)
    };
    m.mContents.emplace(std::move(content));
    return m;
}

inline ShaderModule createShaderModule(std::string name,
    NameMap<ShaderValue> outputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), {},
        std::move(contents),
    };
    return m;
}

inline ShaderModule createShaderModule(std::string name, uint32_t flags,
    NameMap<ShaderValue> outputs,
    const OrderedVariantIDMap2<Content>& contents
) {
    ShaderModule m{
        std::move(name), {},
        std::move(outputs), {},
        std::move(contents), static_cast<ModuleBuilderFlags>(flags)
    };
    return m;
}

const std::string& getContent(const ShaderModule& m, Language l);

}
