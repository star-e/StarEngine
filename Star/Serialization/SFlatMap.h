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

# pragma once

#include <boost/container/flat_map.hpp>

#include <boost/config.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/move/utility_core.hpp>

namespace boost { 
namespace serialization {

template<class Archive, class Container>
inline void load_flat_map_collection(Archive & ar, Container &s)
{
    s.clear();
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
    s.reserve(count);
    typename Container::iterator hint;
    hint = s.begin();
    while(count-- > 0){
        typedef typename Container::value_type type;
        detail::stack_construct<Archive, type> t(ar, item_version);
        ar >> boost::serialization::make_nvp("item", t.reference());
        typename Container::iterator result =
            s.insert(hint, boost::move(t.reference()));
        ar.reset_object_address(& (result->second), & t.reference().second);
        hint = result;
        ++hint;
    }
}

// map
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const boost::container::flat_map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, 
        boost::container::flat_map<Key, Type, Compare, Allocator> 
    >(ar, t);
}

template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    boost::container::flat_map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_flat_map_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    boost::container::flat_map<Key, Type, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// multimap
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const boost::container::flat_multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, 
        boost::container::flat_multimap<Key, Type, Compare, Allocator> 
    >(ar, t);
}

template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    boost::container::flat_multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_flat_map_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    boost::container::flat_multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost
