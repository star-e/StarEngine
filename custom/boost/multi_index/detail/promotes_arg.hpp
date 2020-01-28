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

/* Copyright 2003-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP
#define BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

/* Metafunctions to check if f(arg1,arg2) promotes either arg1 to the type of
 * arg2 or viceversa. By default, (i.e. if it cannot be determined), no
 * promotion is assumed.
 */

#if BOOST_WORKAROUND(BOOST_MSVC,<1400)

namespace boost{

namespace multi_index{

namespace detail{

template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:mpl::false_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#else

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/multi_index/detail/is_transparent.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost{

namespace multi_index{

namespace detail{
  
template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg1,Arg2>,
    is_transparent<F,Arg2,Arg2>
  >
{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg2,Arg1>,
    is_transparent<F,Arg1,Arg1>
  >
{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif
