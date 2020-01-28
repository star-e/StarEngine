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

#ifndef BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP
#define BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

namespace boost{

namespace multi_index{

/* dummy type and variable for use in ordered_index::range() */

/* ODR-abiding technique shown at the example attached to
 * http://lists.boost.org/Archives/boost/2006/07/108355.php
 */

namespace detail{class unbounded_helper;}

detail::unbounded_helper unbounded(detail::unbounded_helper);

namespace detail{

class unbounded_helper
{
  unbounded_helper(){}
  unbounded_helper(const unbounded_helper&){}
  friend unbounded_helper multi_index::unbounded(unbounded_helper);
};

typedef unbounded_helper (*unbounded_type)(unbounded_helper);

} /* namespace multi_index::detail */

inline detail::unbounded_helper unbounded(detail::unbounded_helper)
{
  return detail::unbounded_helper();
}

/* tags used in the implementation of range */

namespace detail{

struct none_unbounded_tag{};
struct lower_unbounded_tag{};
struct upper_unbounded_tag{};
struct both_unbounded_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
