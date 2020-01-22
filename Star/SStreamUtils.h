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
#include <iosfwd>

namespace Star {

template<class T>
void write_data(std::ostream& os, const T& value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

template<class T>
void read_data(std::istream& is, T& value) {
    is.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template<class T>
void read_data(std::istream& is, T* data, size_t objcount) {
    return is.read(reinterpret_cast<char*>(data), sizeof(T) * objcount);
}

template<class T, class Traits, class Alloc>
const T& value_cast(const std::basic_string<char, Traits, Alloc>& str) {
    Expects(sizeof(T) == str.size());
    return *reinterpret_cast<const T*>(static_cast<const void*>(str.data()));
}

}
