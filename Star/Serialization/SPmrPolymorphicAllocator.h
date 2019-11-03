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
#include <memory_resource>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>

namespace boost {
namespace serialization {

template <class T>
struct implementation_level_impl<const std::pmr::polymorphic_allocator<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    static const int value = implementation_level_impl::type::value;
};

template<class T>
struct tracking_level<std::pmr::polymorphic_allocator<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    static const int value = tracking_level::type::value;
    
    static_assert((mpl::greater<        
        implementation_level<std::pmr::polymorphic_allocator<T>>,
        mpl::int_<primitive_type>>::value));
};

template<class Archive, class T>
void serialize(Archive & ar, std::pmr::polymorphic_allocator<T>& v, const unsigned int version) {
    // do nothing
}

}
}
