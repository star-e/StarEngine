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

#include <boost/container/small_vector.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array_wrapper.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/if.hpp>

// default is being compatible with version 1.34.1 files, not 1.35 files
#ifndef BOOST_SERIALIZATION_VECTOR_VERSIONED
#define BOOST_SERIALIZATION_VECTOR_VERSIONED(V) (V==4 || V==5)
#endif

namespace boost { 
namespace serialization {

// the default versions

template<class Archive, class U, size_t N, class Allocator>
inline void save(
    Archive & ar,
    const boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::save_collection<Archive,
        boost::container::small_vector<U, N, Allocator> >(
        ar, t
    );
}

template<class Archive, class U, size_t N, class Allocator>
inline void load(
    Archive & ar,
    boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    const boost::archive::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    item_version_type item_version(0);
    collection_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    if(boost::archive::library_version_type(3) < library_version){
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    t.reserve(count);
    stl::collection_load_impl(ar, t, count, item_version);
}

// the optimized versions

template<class Archive, class U, size_t N, class Allocator>
inline void save(
    Archive & ar,
    const boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    const collection_size_type count(t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    if (!t.empty())
        // explict template arguments to pass intel C++ compiler
        ar << serialization::make_array<const U, collection_size_type>(
            static_cast<const U *>(&t[0]),
            count
        );
}

template<class Archive, class U, size_t N, class Allocator>
inline void load(
    Archive & ar,
    boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    collection_size_type count(t.size());
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    unsigned int item_version=0;
    if(BOOST_SERIALIZATION_VECTOR_VERSIONED(ar.get_library_version())) {
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    if (!t.empty())
        // explict template arguments to pass intel C++ compiler
        ar >> serialization::make_array<U, collection_size_type>(
            static_cast<U *>(&t[0]),
            count
        );
  }

// dispatch to either default or optimized versions

template<class Archive, class U, size_t N, class Allocator>
inline void save(
    Archive & ar,
    const boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int file_version
){
    typedef typename 
    boost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type 
    >::type use_optimized;
    save(ar,t,file_version, use_optimized());
}

template<class Archive, class U, size_t N, class Allocator>
inline void load(
    Archive & ar,
    boost::container::small_vector<U, N, Allocator> &t,
    const unsigned int file_version
){
#ifdef BOOST_SERIALIZATION_VECTOR_135_HPP
    if (ar.get_library_version()==boost::archive::library_version_type(5))
    {
      load(ar,t,file_version, boost::is_arithmetic<U>());
      return;
    }
#endif
    typedef typename 
    boost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type 
    >::type use_optimized;
    load(ar,t,file_version, use_optimized());
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, size_t N, class Allocator>
inline void serialize(
    Archive & ar,
    boost::container::small_vector<U, N, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#include <Star/Serialization/SStaticCollectionTraits.h>

STAR_SERIALIZATION_STATIC_COLLECTION_TRAITS(boost::container::small_vector)
