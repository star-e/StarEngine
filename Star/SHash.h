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

// forward declare
namespace boost {

template <class T> 
void hash_combine(std::size_t& seed, T const& v);

}

// hash classes
namespace Star {

struct IdentityHash {
    inline size_t operator()(uint32_t value) const noexcept {
        return static_cast<size_t>(value);
    }

    inline size_t operator()(uint64_t value) const noexcept {
        return static_cast<size_t>(value);
    }
};

struct PairHash {
    template<class T, class U>
    inline size_t operator()(const std::pair<T, U>& pair) const noexcept {
        size_t seed = 0;
        boost::hash_combine(seed, pair.first);
        boost::hash_combine(seed, pair.second);
        return seed;
    }
};

}
