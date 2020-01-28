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

#ifndef BOOST_MULTI_INDEX_ORDERED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_ORDERED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/detail/ord_index_args.hpp>
#include <boost/multi_index/detail/ord_index_impl_fwd.hpp>

namespace boost{

namespace multi_index{

/* ordered_index specifiers */

template<typename Arg1,typename Arg2=mpl::na,typename Arg3=mpl::na>
struct ordered_unique;

template<typename Arg1,typename Arg2=mpl::na,typename Arg3=mpl::na>
struct ordered_non_unique;

} /* namespace multi_index */

} /* namespace boost */

#endif
