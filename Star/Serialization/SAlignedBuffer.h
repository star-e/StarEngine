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
#include <Star/SAlignedBuffer.h>
#include <Star/Serialization/SPmrVector.h>

#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>


namespace boost::serialization {

template<size_t NAlignment>
struct implementation_level_impl<const Star::AlignedBuffer<NAlignment>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level_impl::type::value);
};

template<size_t NAlignment>
struct tracking_level<Star::AlignedBuffer<NAlignment>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
    /* tracking for a class  */
    BOOST_STATIC_ASSERT((mpl::greater<
        implementation_level<Star::AlignedBuffer<NAlignment>>,
        mpl::int_<primitive_type>>::value));
};

template<class Archive, size_t NAlignment>
void save(Archive& ar, const Star::AlignedBuffer<NAlignment>& v, const unsigned int version) {
    size_t sz = v.size();
    ar << sz;
    ar << boost::serialization::make_array(v.data(), sz);
}

template<class Archive, size_t NAlignment>
void load(Archive& ar, Star::AlignedBuffer<NAlignment>& v, const unsigned int version) {
    size_t sz;
    ar >> sz;
    v.resize(sz);
    ar >> boost::serialization::make_array(v.data(), sz);
}

template<class Archive, size_t NAlignment>
void serialize(Archive& ar, Star::AlignedBuffer<NAlignment>& v, const uint32_t version) {
    split_free(ar, v, version);
}

}
