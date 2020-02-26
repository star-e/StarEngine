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

#include "Star/Graphics/SRenderGraphReflection.h"
#include <Star/Graphics/SRenderGraphTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

namespace Descriptor {

bool try_getType(std::string_view name, Type& type) noexcept {
    static const std::unordered_map<std::string_view, Type> index{
        { std::string_view(""), Type(std::in_place_type_t<ConstantBuffer_>()) },
        { std::string_view("BaseColor"), Type(std::in_place_type_t<BaseColor_>()) },
        { std::string_view("LinearSampler"), Type(std::in_place_type_t<LinearSampler_>()) },
    };

    auto iter = index.find(name);
    if (iter != index.end()) {
        type = iter->second;
        return true;
    } else {
        return false;
    }
}

void getType(std::string_view name, Type& type) {
    if (!try_getType(name, type)) {
        throw std::out_of_range("getType(Type)");
    }
}

} // namespace Descriptor

namespace Data {

bool try_getType(std::string_view name, Type& type) noexcept {
    static const std::unordered_map<std::string_view, Type> index{
        { std::string_view("Proj"), Type(std::in_place_type_t<Proj_>()) },
        { std::string_view("View"), Type(std::in_place_type_t<View_>()) },
        { std::string_view("WorldView"), Type(std::in_place_type_t<WorldView_>()) },
        { std::string_view("WorldInvT"), Type(std::in_place_type_t<WorldInvT_>()) },
    };

    auto iter = index.find(name);
    if (iter != index.end()) {
        type = iter->second;
        return true;
    } else {
        return false;
    }
}

void getType(std::string_view name, Type& type) {
    if (!try_getType(name, type)) {
        throw std::out_of_range("getType(Type)");
    }
}

} // namespace Data

} // namespace Render

} // namespace Graphics

} // namespace Star
