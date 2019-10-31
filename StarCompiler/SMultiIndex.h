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

namespace Star {

template<class Tag, class Key, typename Value, typename IndexSpecifierList, typename Allocator>
const Value& at(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.get<Tag>().find(key);
    if (iter != container.get<Tag>().end()) {
        return *iter;
    }
    throw std::runtime_error("multi_index value not found");
}

template<class Key, typename Value, typename IndexSpecifierList, typename Allocator>
const Value& at(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.find(key);
    if (iter != container.end()) {
        return *iter;
    }
    throw std::runtime_error("multi_index value not found");
}

template<class Tag, class Key, typename Value, typename IndexSpecifierList, typename Allocator>
bool exists(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.get<Tag>().find(key);
    if (iter != container.get<Tag>().end()) {
        return true;
    }
    return false;
}

template<class Key, typename Value, typename IndexSpecifierList, typename Allocator>
bool exists(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.find(key);
    if (iter != container.end()) {
        return true;
    }
    return false;
}

template<class Tag, class Key, typename Value, typename IndexSpecifierList, typename Allocator>
uint32_t index(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.get<Tag>().find(key);
    if (iter != container.get<Tag>().end()) {
        return gsl::narrow<uint32_t>(
            std::distance(container.get<Index::Index>().begin(), container.project<Index::Index>(iter)));
    }
    throw std::runtime_error("multi_index value not found");
}

template<class Key, typename Value, typename IndexSpecifierList, typename Allocator>
uint32_t index(const boost::multi_index::multi_index_container<Value,
    IndexSpecifierList, Allocator>& container, const Key& key
) {
    auto iter = container.find(key);
    if (iter != container.end()) {
        return gsl::narrow<uint32_t>(
            std::distance(container.get<Index::Index>().begin(), container.project<Index::Index>(iter)));
    }
    throw std::runtime_error("multi_index value not found");
}

}
