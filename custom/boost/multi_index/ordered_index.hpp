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

/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_ORDERED_INDEX_HPP
#define BOOST_MULTI_INDEX_ORDERED_INDEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/ord_index_impl.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no augment policy for plain ordered indices */

struct null_augment_policy
{
  template<typename OrderedIndexImpl>
  struct augmented_interface
  {
    typedef OrderedIndexImpl type;
  };

  template<typename OrderedIndexNodeImpl>
  struct augmented_node
  {
    typedef OrderedIndexNodeImpl type;
  };

  template<typename Pointer> static void add(Pointer,Pointer){}
  template<typename Pointer> static void remove(Pointer,Pointer){}
  template<typename Pointer> static void copy(Pointer,Pointer){}
  template<typename Pointer> static void rotate_left(Pointer,Pointer){}
  template<typename Pointer> static void rotate_right(Pointer,Pointer){}

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  template<typename Pointer> static bool invariant(Pointer){return true;}

#endif
};

} /* namespace multi_index::detail */

/* ordered_index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_unique
{
  typedef typename detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_unique_tag,
      detail::null_augment_policy>                        type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_non_unique
{
  typedef detail::ordered_index_args<
    Arg1,Arg2,Arg3>                                index_args;
  typedef typename index_args::tag_list_type::type tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_class
  {
    typedef detail::ordered_index_node<detail::null_augment_policy,Super> type;
  };

  template<typename SuperMeta>
  struct index_class
  {
    typedef detail::ordered_index<
      key_from_value_type,compare_type,
      SuperMeta,tag_list_type,detail::ordered_non_unique_tag,
      detail::null_augment_policy>                            type;
  };
};

} /* namespace multi_index */

} /* namespace boost */

#endif
