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
#include <Star/SSerializationUtils.h>
#include <Star/SObservable.h>

namespace boost {
namespace serialization {

template <class T>
struct implementation_level_impl<const Star::Observable<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    static const int value = implementation_level_impl::type::value;
};

template<class T>
struct tracking_level<Star::Observable<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    static const int value = tracking_level::type::value;
    
    static_assert(mpl::greater<        
        implementation_level<Star::Observable<T>>,
        mpl::int_<primitive_type>>::value);
};

template<class Archive, class T>
void serialize(Archive& ar, Star::Observable<T>& v, const unsigned int version) {
    split_free(ar, v, version);
}

template<class Archive, class T>
void save(Archive& ar, const Star::Observable<T>& v, const unsigned int version) {
    ar << v.mHandle;
}

template<class Archive, class T>
void load(Archive& ar, Star::Observable<T>& v, const unsigned int version) {
    ar >> v.mHandle;
}

}
}
