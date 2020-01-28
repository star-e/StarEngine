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

#ifndef BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP
#define BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace safe_mode{

/* Error codes for Boost.MultiIndex safe mode. These go in a separate
 * header so that the user can include it when redefining
 * BOOST_MULTI_INDEX_SAFE_MODE_ASSERT prior to the inclusion of
 * any other header of Boost.MultiIndex.
 */

enum error_code
{
  invalid_iterator=0,
  not_dereferenceable_iterator,
  not_incrementable_iterator,
  not_decrementable_iterator,
  not_owner,
  not_same_owner,
  invalid_range,
  inside_range,
  out_of_bounds,
  same_container
};

} /* namespace multi_index::safe_mode */

} /* namespace multi_index */

} /* namespace boost */

#endif
