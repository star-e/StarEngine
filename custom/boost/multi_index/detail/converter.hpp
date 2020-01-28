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

#ifndef BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* converter offers means to access indices of a given multi_index_container
 * and for convertibilty between index iterators, so providing a
 * localized access point for get() and project() functions.
 */

template<typename MultiIndexContainer,typename Index>
struct converter
{
  static const Index& index(const MultiIndexContainer& x){return x;}
  static Index&       index(MultiIndexContainer& x){return x;}

  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }

  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
