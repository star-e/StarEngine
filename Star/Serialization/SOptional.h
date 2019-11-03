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
#include <boost/config.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>

#include <optional>
#include <boost/move/utility_core.hpp>

#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/serialization/detail/is_default_constructible.hpp>
#include <boost/serialization/force_include.hpp>

// function specializations must be defined in the appropriate
// namespace - boost::serialization
namespace boost { 
namespace serialization {

template<class Archive, class T>
void save(
    Archive & ar, 
    const std::optional< T > & t, 
    const unsigned int /*version*/
){
    // It is an inherent limitation to the serialization of optional.hpp
    // that the underlying type must be either a pointer or must have a
    // default constructor.  It's possible that this could change sometime
    // in the future, but for now, one will have to work around it.  This can
    // be done by serialization the optional<T> as optional<T *>
    #if ! defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
        BOOST_STATIC_ASSERT(
            boost::serialization::detail::is_default_constructible<T>::value
            || boost::is_pointer<T>::value
        );
    #endif
    const bool tflag = t.has_value();
    ar << boost::serialization::make_nvp("initialized", tflag);
    if (tflag){
        ar << boost::serialization::make_nvp("value", *t);
    }
}

template<class Archive, class T>
void load(
    Archive & ar, 
    std::optional< T > & t, 
    const unsigned int version
){
    bool tflag;
    ar >> boost::serialization::make_nvp("initialized", tflag);

    if(! tflag){
        t.reset();
        return;
    }
    if(! t.has_value())
        t = T();
    ar >> boost::serialization::make_nvp("value", *t);
}

template<class Archive, class T>
void serialize(
    Archive & ar, 
    std::optional< T > & t, 
    const unsigned int version
){
    boost::serialization::split_free(ar, t, version);
}

template <class T>
struct implementation_level_impl<const std::optional<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level_impl::type::value);
};

template<class T>
struct tracking_level<std::optional<T>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
    /* tracking for a class  */
    BOOST_STATIC_ASSERT((mpl::greater<
        implementation_level<std::optional<T>>,
        mpl::int_<primitive_type>>::value));
};

} // serialization
} // boost
