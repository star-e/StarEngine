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

/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_NO_DUPLICATE_TAGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/fold.hpp>
#include <boost/mpl/set/set0.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* no_duplicate_tags check at compile-time that a tag list
 * has no duplicate tags.
 * The algorithm deserves some explanation: tags
 * are sequentially inserted into a mpl::set if they were
 * not already present. Due to the magic of mpl::set
 * (mpl::has_key is contant time), this operation takes linear
 * time, and even MSVC++ 6.5 handles it gracefully (other obvious
 * solutions are quadratic.)
 */

struct duplicate_tag_mark{};

struct duplicate_tag_marker
{
  template <typename MplSet,typename Tag>
  struct apply
  {
    typedef mpl::s_item<
      typename mpl::if_<mpl::has_key<MplSet,Tag>,duplicate_tag_mark,Tag>::type,
      MplSet
    > type;
  };
};

template<typename TagList>
struct no_duplicate_tags
{
  typedef typename mpl::fold<
    TagList,
    mpl::set0<>,
    duplicate_tag_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

/* Variant for an index list: duplication is checked
 * across all the indices.
 */

struct duplicate_tag_list_marker
{
  template <typename MplSet,typename Index>
  struct apply:mpl::fold<
    BOOST_DEDUCED_TYPENAME Index::tag_list,
    MplSet,
    duplicate_tag_marker>
  {
  };
};

template<typename IndexList>
struct no_duplicate_tags_in_index_list
{
  typedef typename mpl::fold<
    IndexList,
    mpl::set0<>,
    duplicate_tag_list_marker
  >::type aux;
 
  BOOST_STATIC_CONSTANT(
    bool,value=!(mpl::has_key<aux,duplicate_tag_mark>::value));
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
