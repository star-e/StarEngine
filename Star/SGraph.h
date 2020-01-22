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
#include <memory>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>

namespace Star {
    
using boost::adjacency_list;

using boost::undirectedS;
using boost::directedS;
using boost::bidirectionalS;

using boost::no_property;
using boost::vecS;
using boost::listS;
using boost::setS;
using boost::mapS;
using boost::multisetS;
using boost::multimapS;
using boost::hash_setS;
using boost::hash_mapS;
using boost::hash_multisetS;
using boost::hash_multimapS;

struct pmr_vecS {};
struct pmr_listS {};

template <class VertexProperty = no_property,
    class EdgeProperty = no_property,
    class GraphProperty = no_property,
    class EdgeListS = listS
> using Graph = boost::adjacency_list<vecS, vecS, bidirectionalS,
    VertexProperty, EdgeProperty, GraphProperty, EdgeListS>;

}

namespace boost {

template<class T>
struct container_gen<Star::pmr_vecS, T> {
    typedef std::pmr::vector<T> type;
};

template<class T>
struct container_gen<Star::pmr_listS, T> {
    typedef std::pmr::list<T> type;
};

template <>
struct parallel_edge_traits<Star::pmr_vecS> {
    typedef allow_parallel_edge_tag type;
};

template <>
struct parallel_edge_traits<Star::pmr_listS> {
    typedef allow_parallel_edge_tag type;
};

template <class K, class H, class C, class A, class T>
bool set_contains(const std::unordered_set<K, H, C, A>& s, const T& x) {
    return s.find(x) != s.end();
}

template <class K, class V, class H, class C, class A, class T>
bool set_contains(const std::unordered_map<K, V, H, C, A>& s, const T& x) {
    return s.find(x) != s.end();
}

namespace detail {

template <>
struct is_random_access<Star::pmr_vecS> {
    enum { value = true };
    typedef mpl::true_ type;
};

}

template <typename OEL, typename D, typename VP, typename EP, typename GP, typename EL>
struct graph_mutability_traits< adjacency_list<OEL, Star::pmr_vecS, D, VP, EP, GP, EL> > {
    typedef add_only_property_graph_tag category;
};

}
