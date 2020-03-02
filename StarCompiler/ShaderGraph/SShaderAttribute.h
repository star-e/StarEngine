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
#include <StarCompiler/ShaderGraph/SShaderTypes.h>

namespace Star::Graphics::Render::Shader {

const char* getName(const AttributeType& attr) noexcept;
const char* getHLSLName(const AttributeType& attr) noexcept;

void compileShaderAttribute(ShaderAttribute& attr);
bool isConstant(const ShaderAttribute& attr) noexcept;
DescriptorIndex getDescriptorIndex(const AttributeDescriptor& d, ShaderVisibilityType vis);

uint32_t getDescriptorCapacity(const ShaderAttribute& attr);
uint32_t getDescriptorCapacity(const DescriptorRange& list);

RootParameterType getRootParameterType(const ShaderAttribute& attr);
DescriptorType getDescriptorType(const ShaderAttribute& attr);
TextureView getTextureView(const ShaderAttribute& attr);

void validate(const ShaderAttribute& attr);
void validate(const AttributeUsage& usage);

inline AttributeKey get_key(const ShaderAttribute& attr) {
    return AttributeKey{ attr.mName, attr.mData };
}

inline AttributeKey get_key(const AttributeUsage& attr) {
    return AttributeKey{ attr.mName, attr.mData };
}

using AttributeMap = boost::multi_index::multi_index_container<ShaderAttribute,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::global_fun<const ShaderAttribute&, AttributeKey, &get_key>
        >,
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<ShaderAttribute, std::string, &ShaderAttribute::mName>,
            std::less<>
        >
    >
>;

using AttributeUsageMap = boost::multi_index::multi_index_container<AttributeUsage,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::global_fun<const AttributeUsage&, AttributeKey, &get_key>
        >
    >
>;

void merge(const AttributeUsageMap& src, AttributeUsageMap& dst);

AttributeMap getAttributes(const AttributeMap& attrs, const AttributeUsageMap& usages);

}
