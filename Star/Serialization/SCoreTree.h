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

#pragma once

#include <Star/Core/SCoreGraph.h>
#include <Star/SSerialization.h>
#include <boost/graph/adj_list_serialize.hpp>

namespace boost {
namespace serialization {

//template<class OEL, class VL, class D, class VP, class EP, class GP, class EL>
//struct tracking_level<boost::adjacency_list<OEL, VL, D, VP, EP, GP, EL> > {
//    typedef mpl::integral_c_tag tag;
//    typedef mpl::int_<track_never> type;
//    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
//};


}
}
