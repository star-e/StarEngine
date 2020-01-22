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
#include <variant>

namespace Star {

struct VariantIndexLess {
    template<class... Ts>
    bool operator()(const std::variant<Ts...>& lhs, const std::variant<Ts...>& rhs) const noexcept {
        return lhs.index() < rhs.index();
    }
};

template<class T, class... Ts>
T make_from_variant(const std::variant<Ts...>& var) {
    return visit(overload([](const auto& v) {
        return T(v);
    }), var);
}

template<class T, class... Ts>
void convert(const std::variant<Ts...>& var, T& res) {
    res = visit(overload([](const auto& v) {
        return T(v);
    }), var);
}

template<class T, class... Types>
constexpr bool IS(const std::variant<Types...>& var) noexcept {
    return std::holds_alternative<T>(var);
}

template<typename VariantType, typename T, size_t index = 0>
constexpr size_t variant_index() {
    if constexpr (index == std::variant_size_v<VariantType>) {
        return index;
    } else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return index;
    } else {
        return variant_index<VariantType, T, index + 1>();
    }
}

}
