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

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector.hpp: serialization for stl vector templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <vector>

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

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace boost { 
namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector< T >

// the default versions

template<class Archive, class U>
inline void save(
    Archive & ar,
    const std::pmr::vector<U> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::save_collection<Archive, STD::pmr::vector<U> >(
        ar, t
    );
}

template<class Archive, class U>
inline void load(
    Archive & ar,
    std::pmr::vector<U> &t,
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

    t.resize(count);
    typename std::pmr::vector<U>::iterator hint;
    hint = t.begin();
    while (count-- > 0) {
        ar >> boost::serialization::make_nvp("item", *hint++);
    }
}

// the optimized versions

template<class Archive, class U>
inline void save(
    Archive & ar,
    const std::pmr::vector<U> &t,
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

template<class Archive, class U>
inline void load(
    Archive & ar,
    std::pmr::vector<U> &t,
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

template<class Archive, class U>
inline void save(
    Archive & ar,
    const std::pmr::vector<U> &t,
    const unsigned int file_version
){
    typedef typename 
    boost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type 
    >::type use_optimized;
    save(ar,t,file_version, use_optimized());
}

template<class Archive, class U>
inline void load(
    Archive & ar,
    std::pmr::vector<U> &t,
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
template<class Archive, class U>
inline void serialize(
    Archive & ar,
    std::pmr::vector<U> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector<bool>
template<class Archive>
inline void save(
    Archive & ar,
    const std::pmr::vector<bool> &t,
    const unsigned int /* file_version */
){
    // record number of elements
    collection_size_type count (t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    std::vector<bool>::const_iterator it = t.begin();
    while(count-- > 0){
        bool tb = *it++;
        ar << boost::serialization::make_nvp("item", tb);
    }
}

template<class Archive>
inline void load(
    Archive & ar,
    std::pmr::vector<bool> &t,
    const unsigned int /* file_version */
){
    // retrieve number of elements
    collection_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    for(collection_size_type i = collection_size_type(0); i < count; ++i){
        bool b;
        ar >> boost::serialization::make_nvp("item", b);
        t[i] = b;
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive>
inline void serialize(
    Archive & ar,
    std::pmr::vector<bool> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(std::pmr::vector)
#undef STD
