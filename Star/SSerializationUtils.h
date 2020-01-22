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
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>

#define STAR_SERIALIZATION_SPLIT_FREE(T)       \
template<class Archive>                         \
inline void serialize(                          \
        Archive & ar,                               \
        T & t,                                      \
        const unsigned int file_version             \
){                                              \
        split_free(ar, t, file_version);            \
}

#define STAR_CLASS_TRACKING(T, E)           \
template<>                                   \
struct tracking_level< T >                   \
{                                            \
    typedef mpl::integral_c_tag tag;         \
    typedef mpl::int_< E> type;              \
    BOOST_STATIC_CONSTANT(                   \
        int,                                 \
        value = tracking_level::type::value  \
    );                                       \
    /* tracking for a class  */              \
    BOOST_STATIC_ASSERT((                    \
        mpl::greater<                        \
            /* that is a prmitive */         \
            implementation_level< T >,       \
            mpl::int_<primitive_type>        \
        >::value                             \
    ));                                      \
};

#define STAR_CLASS_IMPLEMENTATION(T, E)                 \
template <>                                          \
struct implementation_level_impl< const T >                     \
{                                                    \
    typedef mpl::integral_c_tag tag;                 \
    typedef mpl::int_< E > type;                     \
    BOOST_STATIC_CONSTANT(                           \
        int,                                         \
        value = implementation_level_impl::type::value    \
    );                                               \
};

#define STAR_SERIALIZE_BINARY(T) \
STAR_CLASS_IMPLEMENTATION(T, object_serializable);\
STAR_CLASS_TRACKING(T, track_never);\
template<class Archive>\
void serialize(Archive& ar, T& v, const uint32_t version) {\
    static_assert(std::is_standard_layout_v<T>);\
    ar & make_binary_object(&v, sizeof(v));\
}

#define STAR_SERIALIZE_TAG(T) \
STAR_CLASS_IMPLEMENTATION(T, object_serializable);\
STAR_CLASS_TRACKING(T, track_never);\
template<class Archive>\
void serialize(Archive& ar, T& v, const uint32_t version) {}
