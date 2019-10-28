// Copyright (C) 2019 star.engine@outlook.com
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
#include <memory>
#include <boost/container/flat_map.hpp>

// for std::less<> the transparent comparator
// see https://stackoverflow.com/questions/20317413/what-are-transparent-comparators

namespace Star {

template<class Key, class Value>
using FlatMap = boost::container::flat_map<Key, Value, std::less<>>;

template<class Key, class Value>
using PmrFlatMap = boost::container::flat_map<Key, Value, std::less<>,
    std::pmr::polymorphic_allocator<std::pair<Key, Value>>
>;

template<class Value>
using FlatStringMap = boost::container::flat_map<std::string, Value, std::less<>>;

template<class Value>
using PmrFlatStringMap = boost::container::flat_map<std::pmr::string, Value, std::less<>,
    std::pmr::polymorphic_allocator<std::pair<std::pmr::string, Value>>
>;

template<class Value>
using FlatUInt32Map = boost::container::flat_map<uint32_t, Value>;

template<class Value>
using PmrFlatUInt32Map = boost::container::flat_map<uint32_t, Value, std::less<uint32_t>,
    std::pmr::polymorphic_allocator<std::pair<uint32_t, Value>>
>;

template<class Value>
using FlatUInt64Map = boost::container::flat_map<uint64_t, Value>;

template<class Value>
using PmrFlatUInt64Map = boost::container::flat_map<uint64_t, Value, std::less<uint64_t>,
    std::pmr::polymorphic_allocator<std::pair<uint64_t, Value>>
>;

template<class Key, class Value, class Allocator, class KeyLike>
inline bool exists(const boost::container::flat_map<Key, Value, std::less<>, Allocator>& m, const KeyLike& key) noexcept {
    auto iter = m.find(key);
    return iter != m.end();
}

template<class Key, class Value, class Allocator, class KeyLike>
inline typename boost::container::flat_map<Key, Value, std::less<>, Allocator>::mapped_type&
at(boost::container::flat_map<Key, Value, std::less<>, Allocator>& m, const KeyLike& key) {
    auto iter = m.find(key);
    if (iter == m.end()) {
        throw std::out_of_range("at(boost::container::flat_map) out of range");
    }
    return iter->second;
}

template<class Key, class Value, class KeyLike, class Allocator>
inline typename boost::container::flat_map<Key, Value, std::less<>, Allocator>::mapped_type const&
at(const boost::container::flat_map<Key, Value, std::less<>, Allocator>& m, const KeyLike& key) {
    auto iter = m.find(key);
    if (iter == m.end()) {
        throw std::out_of_range("at(boost::container::flat_map) out of range");
    }
    return iter->second;
}

}
