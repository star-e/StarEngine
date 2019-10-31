// Copyright (C) 2019 star.engine at outlook dot com
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
#include <Star/SGraph.h>

namespace Star {

template<class Graph>
int getNumConnectedComponents(const Graph& graph) {
    boost::adjacency_list<vecS, vecS, undirectedS> uGraph;
    for (int i = 0; i != num_vertices(graph); ++i) {
        add_vertex(uGraph);
    }
    auto range = edges(graph);
    for (auto iter = range.first; iter != range.second; ++iter) {
        add_edge(iter->m_source, iter->m_target, uGraph);
    }

    std::vector<int> components(num_vertices(graph));

    return boost::connected_components(uGraph, components.data());
}

template<class Graph>
bool isSingleComponent(const Graph& graph) {    
    return getNumConnectedComponents(graph) == 1;    
}

template<class Graph>
void sortGraphNodes(Graph& graph, std::vector<size_t>& order) {
    Expects(order.empty());
    boost::topological_sort(graph, std::back_inserter(order));
}

}
