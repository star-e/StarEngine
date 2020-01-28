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

#ifndef BOOST_MULTI_INDEX_INDEXED_BY_HPP
#define BOOST_MULTI_INDEX_INDEXED_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp> 

/* An alias to mpl::vector used to hide MPL from the user.
 * indexed_by contains the index specifiers for instantiation
 * of a multi_index_container.
 */

/* This user_definable macro limits the number of elements of an index list;
 * useful for shortening resulting symbol names (MSVC++ 6.0, for instance,
 * has problems coping with very long symbol names.)
 */

#if !defined(BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE)
#define BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#if BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE<BOOST_MPL_LIMIT_VECTOR_SIZE
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE \
  BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE
#else
#define BOOST_MULTI_INDEX_INDEXED_BY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#define BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM(z,n,var) \
  typename BOOST_PP_CAT(var,n) BOOST_PP_EXPR_IF(n,=mpl::na)

namespace boost{

namespace multi_index{

template<
  BOOST_PP_ENUM(
    BOOST_MULTI_INDEX_INDEXED_BY_SIZE,
    BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM,T)
>
struct indexed_by:
  mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MULTI_INDEX_INDEXED_BY_SIZE,T)>
{
};

} /* namespace multi_index */

} /* namespace boost */

#undef BOOST_MULTI_INDEX_INDEXED_BY_TEMPLATE_PARM
#undef BOOST_MULTI_INDEX_INDEXED_BY_SIZE

#endif
