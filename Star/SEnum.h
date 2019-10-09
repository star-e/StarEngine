// Copyright (C) 2019 star.engine@outlook.com
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

#pragma once
#include <type_traits>

namespace Star {

template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

}

#define S_ENUM_POT_ELEM(r, PREFIX, i, NAME)\
    BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(PREFIX, NAME) = (1 << i)
#define S_ENUM_POT(PREFIX, TUPLE) \
    BOOST_PP_SEQ_FOR_EACH_I(S_ENUM_POT_ELEM, PREFIX, BOOST_PP_TUPLE_TO_SEQ(TUPLE))

#define S_ENUM_SUM_ELEM(r, PREFIX, i, NAME)\
    BOOST_PP_EXPR_IF(i, |) BOOST_PP_CAT(PREFIX, NAME) 
#define S_ENUM_SUM(PREFIX, TUPLE) \
    BOOST_PP_SEQ_FOR_EACH_I(S_ENUM_SUM_ELEM, PREFIX, BOOST_PP_TUPLE_TO_SEQ(TUPLE))
