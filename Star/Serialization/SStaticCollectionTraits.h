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

#include <boost/config.hpp>
//#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <climits> // ULONG_MAX
#include <boost/serialization/level.hpp>

#define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(T, C)          \
template<size_t N, class A>                                                          \
struct implementation_level< C < T, N, A > > {                            \
    typedef mpl::integral_c_tag tag;                                \
    typedef mpl::int_<object_serializable> type;                    \
    BOOST_STATIC_CONSTANT(int, value = object_serializable);        \
};                                                                  \
/**/

#if defined(BOOST_NO_CWCHAR) || defined(BOOST_NO_INTRINSIC_WCHAR_T)
    #define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_WCHAR(C)
#else
    #define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_WCHAR(C)   \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(wchar_t, C)        \
    /**/
#endif

#if defined(BOOST_HAS_LONG_LONG)
    #define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_INT64(C)    \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(boost::long_long_type, C)  \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(boost::ulong_long_type, C) \
    /**/
#else
    #define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_INT64(C)
#endif

#define STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS(C)                     \
    namespace boost { namespace serialization {                      \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(bool, C)            \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(char, C)            \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(signed char, C)     \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(unsigned char, C)   \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(signed int, C)      \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(unsigned int, C)    \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(signed long, C)     \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(unsigned long, C)   \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(float, C)           \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(double, C)          \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(unsigned short, C)  \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER(signed short, C)    \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_INT64(C)            \
    STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS_HELPER_WCHAR(C)            \
    } }                                                              \
    /**/
