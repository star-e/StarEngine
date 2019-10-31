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
#include <set>

namespace Star {

template<class Value>
using Set = std::set<Value, std::less<>>;

template<class Value>
using PmrSet = std::set<Value, std::less<>,
    std::pmr::polymorphic_allocator<Value>
>;

template<class Value, class KeyLike, class Allocator>
inline bool exists(const std::set<Value, std::less<>, Allocator>& m, const KeyLike& key) noexcept {
    auto iter = m.find(key);
    return iter != m.end();
}

template<class Value, class Allocator, class KeyLike>
inline typename std::set<Value, std::less<>, Allocator>::mapped_type&
at(std::set<Value, std::less<>, Allocator>& m, const KeyLike& key) {
    auto iter = m.find(key);
    if (iter == m.end()) {
        throw std::out_of_range("at(std::set) out of range");
    }
    return iter->second;
}

template<class Value, class Allocator, class KeyLike>
inline typename std::set<Value, std::less<>, Allocator>::mapped_type const&
at(const std::set<Value, std::less<>, Allocator>& m, const KeyLike& key) {
    auto iter = m.find(key);
    if (iter == m.end()) {
        throw std::out_of_range("at(std::set) out of range");
    }
    return iter->second;
}

}
