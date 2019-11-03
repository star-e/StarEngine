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
#include <string>
#include <cstdint>
#include <Star/SSerializationUtils.h>

namespace boost {
namespace serialization {

STAR_CLASS_IMPLEMENTATION(std::pmr::string, object_serializable);
STAR_CLASS_TRACKING(std::pmr::string, track_never);
STAR_SERIALIZATION_SPLIT_FREE(std::pmr::string)

template<class Archive>
void save(Archive& ar, const std::pmr::string& v, const uint32_t version) {
    uint32_t sz = static_cast<uint32_t>(v.size());
    ar << sz;
    if (sz) {
        ar << make_binary_object(v.data(), sz);
    }
}

template<class Archive>
void load(Archive& ar, std::pmr::string& v, const uint32_t version) {
    uint32_t sz = 0;
    ar >> sz;
    if (sz) {
        v.resize(sz);
        ar >> make_binary_object(v.data(), sz);
    }
}

}
}
