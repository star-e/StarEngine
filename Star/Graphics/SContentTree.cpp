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

#include "SContentTree.h"

namespace Star{

namespace {

void Test() {
    ContentTree<std::pmr::string, int> tree(std::pmr::get_default_resource());
    auto srcID = add_vertex(tree);
    auto dstID = add_vertex(tree);
    auto e1 = add_edge(srcID, dstID, tree);
    auto e2 = add_edge(srcID, dstID, 10, tree);
    source(e1.first, tree);
    target(e1.first, tree);
    vertices(tree);
    auto range0 = out_edges(srcID, tree);
    auto range1 = in_edges(dstID, tree);
    auto range2 = edges(tree);
    for (auto iter = range0.first; iter != range0.second; ++iter) {
        *iter;
    }
    for (auto iter = range1.first; iter != range1.second; ++iter) {
        *iter;
    }
    for (auto iter = range2.first; iter != range2.second; ++iter) {
        *iter;
    }
    num_edges(tree);
    num_vertices(tree);
    degree(srcID, tree);
    auto range3 = adjacent_vertices(srcID, tree);
    for (auto iter = range3.first; iter != range3.second; ++iter) {
        *iter;
    }
    edge(srcID, dstID, tree);
    remove_edge(e1.first, tree);
    clear_vertex(dstID, tree);
    remove_vertex(dstID, tree);
    tree[e1.first];
}

}

}
