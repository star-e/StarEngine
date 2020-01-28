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

#ifndef BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP
#define BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/call_traits.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Value,typename KeyFromValue,typename Compare>
struct value_comparison
{
  typedef Value first_argument_type;
  typedef Value second_argument_type;
  typedef bool  result_type;

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }

  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }

private:
  KeyFromValue key;
  Compare      comp;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
