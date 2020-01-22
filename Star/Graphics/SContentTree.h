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
#include <Star/Graphics/SContentTreeData.h>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/graph/detail/edge.hpp>
#include <boost/graph/detail/adj_list_edge_iterator.hpp>
#include <boost/graph/adjacency_iterator.hpp>

namespace boost {

template<class VertexProperty, class EdgeProperty>
struct graph_traits<Star::ContentTree<VertexProperty, EdgeProperty>> {
private:
    using graph_type = Star::ContentTree<VertexProperty, EdgeProperty>;
    using out_edge_difference_type = typename std::iterator_traits<typename std::pmr::vector<std::pair<EdgeProperty, size_t>>::iterator>::difference_type;
    using in_edge_difference_type = typename std::iterator_traits<typename boost::container::static_vector<size_t, 1>::iterator>::difference_type;

    template<class BaseIter, class VertexDescriptor, class EdgeDescriptor, class Difference>
    struct OutEdgeIterator : boost::iterators::iterator_adaptor<
        OutEdgeIterator<BaseIter, VertexDescriptor, EdgeDescriptor, Difference>,
        BaseIter, EdgeDescriptor, boost::iterators::use_default, EdgeDescriptor, Difference
    > {
        using super_t = boost::iterators::iterator_adaptor<
            OutEdgeIterator<BaseIter, VertexDescriptor, EdgeDescriptor, Difference>,
            BaseIter, EdgeDescriptor, boost::iterators::use_default, EdgeDescriptor, Difference
        >;

        OutEdgeIterator() {}
        OutEdgeIterator(const BaseIter& i, const VertexDescriptor& src)
            : super_t(i), mSource(src) {}

        inline EdgeDescriptor dereference() const {
            return EdgeDescriptor(mSource, (*this->base()).second, &(*this->base()).first);
        }
        VertexDescriptor mSource;
    };

    template<class BaseIter, class VertexDescriptor, class EdgeDescriptor, class Difference>
    struct InEdgeIterator : boost::iterators::iterator_adaptor<
        InEdgeIterator<BaseIter, VertexDescriptor, EdgeDescriptor, Difference>,
        BaseIter, EdgeDescriptor, boost::iterators::use_default, EdgeDescriptor, Difference
    > {
        using super_t = boost::iterators::iterator_adaptor<
            InEdgeIterator<BaseIter, VertexDescriptor, EdgeDescriptor, Difference>,
            BaseIter, EdgeDescriptor, boost::iterators::use_default, EdgeDescriptor, Difference
        >;

        InEdgeIterator(graph_type& graph)
            : mGraph(graph)
        {}
        InEdgeIterator(graph_type& graph, const BaseIter& i, const VertexDescriptor& src)
            : mGraph(graph)
            , super_t(i), mSource(src)
        {}

        inline EdgeDescriptor dereference() const {
            auto& edges = mGraph.mVertices[mSource].second.mOutEdges;
            for (size_t i = 0; i != edges.size(); ++i) {
                if (*this->base() == edges[i].second) {
                    return EdgeDescriptor(*this->base(), mSource, &edges[i].first);
                }
            }
            throw std::runtime_error("edge not found!");
        }
        graph_type& mGraph;
        VertexDescriptor mSource;
    };

    struct ContentTreeTraversalCategory
        : public virtual vertex_list_graph_tag
        , public virtual adjacency_graph_tag
        , public virtual bidirectional_graph_tag {};
public:
    using vertex_descriptor = size_t;
    using edge_descriptor = typename graph_type::EdgeDescriptor;

    using directed_category = bidirectional_tag;
    using edge_parallel_category = disallow_parallel_edge_tag;

    using vertices_size_type = size_t;
    using edges_size_type = size_t;
    using degree_size_type = size_t;

    using out_edge_iterator = OutEdgeIterator<
        typename graph_type::OutEdgeContainer::iterator,
        vertex_descriptor, edge_descriptor, out_edge_difference_type
    >;

    using in_edge_iterator = InEdgeIterator<
        typename graph_type::InEdgeContainer::iterator,
        vertex_descriptor, edge_descriptor, in_edge_difference_type
    >;

    using adjacency_iterator = adjacency_iterator<graph_type, vertex_descriptor, out_edge_iterator, out_edge_difference_type>;

    using vertex_iterator = typename integer_range<vertex_descriptor>::iterator;
    using edge_iterator = detail::adj_list_edge_iterator<vertex_iterator, out_edge_iterator, graph_type>;

    using traversal_category = ContentTreeTraversalCategory;
};

} // namespace boost

namespace Star {

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor
source(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor e,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    return e.m_source;
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor
target(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor e,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    return e.m_target;
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_iterator,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_iterator
> vertices(const ContentTree<VertexProperty, EdgeProperty>& g
) {
    using vertex_descriptor = typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor;
    boost::integer_range<vertex_descriptor> range(0, g.mVertices.size());
    return std::make_pair(range.begin(), range.end());
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_iterator,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_iterator>
edges(const ContentTree<VertexProperty, EdgeProperty>& g_) {
    using vertex_descriptor = typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor;
    using edge_iterator = typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_iterator;
    ContentTree<VertexProperty, EdgeProperty>& g = const_cast<ContentTree<VertexProperty, EdgeProperty>&>(g_);
    boost::integer_range<vertex_descriptor> range(0, g.mVertices.size());
    return std::make_pair(
        edge_iterator(range.begin(), range.begin(), range.end(), g),
        edge_iterator(range.begin(), range.end(), range.end(), g));
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::out_edge_iterator,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::out_edge_iterator
> out_edges(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
        const ContentTree<VertexProperty, EdgeProperty>& g_
) {
    auto& g = const_cast<ContentTree<VertexProperty, EdgeProperty>&>(g_);

    using out_edge_iterator = typename boost::graph_traits<
        ContentTree<VertexProperty, EdgeProperty>>::out_edge_iterator;
    return std::make_pair(
        out_edge_iterator(g.mVertices[u].second.mOutEdges.begin(), u),
        out_edge_iterator(g.mVertices[u].second.mOutEdges.end(), u));
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::in_edge_iterator,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::in_edge_iterator>
in_edges(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    const ContentTree<VertexProperty, EdgeProperty>& g_
) {
    auto& g = const_cast<ContentTree<VertexProperty, EdgeProperty>&>(g_);

    using in_edge_iterator = typename boost::graph_traits<
        ContentTree<VertexProperty, EdgeProperty>>::in_edge_iterator;

    return std::make_pair(
        in_edge_iterator(g, g.mVertices[u].second.mInEdges.begin(), u),
        in_edge_iterator(g, g.mVertices[u].second.mInEdges.end(), u));
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::adjacency_iterator,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::adjacency_iterator>
adjacent_vertices(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    using adjacency_iterator = typename boost::graph_traits<
        ContentTree<VertexProperty, EdgeProperty>>::adjacency_iterator;

    const auto&[first, last] = out_edges(u, g);
    return std::make_pair(adjacency_iterator(first, &g), adjacency_iterator(last, &g));
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::degree_size_type
out_degree(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    return g.mVertices[u].second.mOutEdges.size();
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertices_size_type
num_vertices(const ContentTree<VertexProperty, EdgeProperty>& g) {
    return g.mVertices.size();
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edges_size_type
num_edges(const ContentTree<VertexProperty, EdgeProperty>& g
) {
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edges_size_type edgeCount = 0;
    for (auto[vi, vi_end] = vertices(g); vi != vi_end; ++vi)
        edgeCount += out_degree(*vi, g);
    return edgeCount;
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::degree_size_type
in_degree(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    return g.mVertices[u].second.mInEdges.size();
} 

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::degree_size_type
degree(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    const ContentTree<VertexProperty, EdgeProperty>& g
) {
    return out_degree(u, g) + in_degree(u, g);
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor
add_vertex(ContentTree<VertexProperty, EdgeProperty>& g) {
    auto desc = g.mVertices.size();
    g.mVertices.emplace_back();
    return desc;
}

template<class VertexProperty, class EdgeProperty>
inline typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor
add_vertex(const VertexProperty& vp, ContentTree<VertexProperty, EdgeProperty>& g) {
    auto desc = g.mVertices.size();
    g.mVertices.emplace_back(vp);
    return desc;
}

template<class VertexProperty, class EdgeProperty>
inline void remove_edge(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor v,
    ContentTree<VertexProperty, EdgeProperty>& g
) noexcept {
    auto& target = g.mVertices[v].second;
    if (auto iter = std::find(std::execution::seq,
        target.mInEdges.begin(), target.mInEdges.end(), u);
        iter != target.mInEdges.end())
    {
        target.mInEdges.erase(iter);
    }

    auto& source = g.mVertices[u].second;
    if (auto iter = std::find_if(std::execution::seq,
        source.mOutEdges.begin(), target.mOutEdges.end(),
        [&v](const auto& e) {
            return e.second == v;
        });
        iter != source.mOutEdges.end())
    {
        source.mOutEdges.erase(iter);
    }
}

template<class VertexProperty, class EdgeProperty>
inline void remove_edge(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor e,
    ContentTree<VertexProperty, EdgeProperty>& g
) noexcept {
    remove_edge(e.m_source, e.m_target, g);
}

template<class VertexProperty, class EdgeProperty>
inline void clear_vertex(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    ContentTree<VertexProperty, EdgeProperty>& g
) {
    auto& node = g.mVertices[u].second;

    for (const auto& e : node.mOutEdges) {
        Expects(g.mVertices[e.second].second.mInEdges.size() == 1);
        Expects(g.mVertices[e.second].second.mInEdges[0] == u);
        g.mVertices[e.second].second.mInEdges.clear();
    }

    node.mOutEdges.clear();

    for (const auto& src : node.mInEdges) {
        auto& srcNode = g.mVertices[src].second;
        for (auto iter = srcNode.mOutEdges.begin(); iter != srcNode.mOutEdges.end(); ++iter) {
            if (iter->second == u) {
                srcNode.mOutEdges.erase(iter);
                break;
            }
        }
    }
    node.mInEdges.clear();
}

template<class VertexProperty, class EdgeProperty>
inline void remove_vertex(
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    ContentTree<VertexProperty, EdgeProperty>& g
) {
    g.mVertices.erase(g.mVertices.begin() + u);
    auto v = num_vertices(g);
    if (u != v) {
        for (auto i = 0; i < v; ++i) {
            auto& vertex = g.mVertices[i].second;
            for (auto& e : vertex.mOutEdges) {
                if (e.second > u)
                    --e.second;
            }
            for (auto& e : vertex.mInEdges) {
                if (e > u) {
                    --e;
                }
            }
        }
    }
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor, bool>
edge(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor v,
    ContentTree<VertexProperty, EdgeProperty>& g
) {
    using edge_descriptor = typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor;
    for (const auto& src : g.mVertices[v].second.mInEdges) {
        if (src == u) {
            const auto& srcNode = g.mVertices[u];
            for (const auto& e : srcNode.second.mOutEdges) {
                if (e.second == v) {
                    return std::make_pair(edge_descriptor(u, v, &e.first), true);
                }
            }
            Ensures(false);
        }
    }

    return std::make_pair(edge_descriptor(u, v, nullptr), false);
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor, bool>
add_edge(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor v,
    ContentTree<VertexProperty, EdgeProperty>& g
) {
    using edge_descriptor = typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor;
    for (const auto& src : g.mVertices[v].second.mInEdges) {
        if (src == u) {
            const auto& edges = g.mVertices[src].second.mOutEdges;
            for (const auto& e : edges) {
                if (e.second == v) {
                    return std::make_pair(edge_descriptor(src, v, &e.first), false);
                }
            }
            throw std::runtime_error("out edge not found");
        } else {
            //return std::make_pair(edge_descriptor(src, v, nullptr), false);
            throw std::invalid_argument("this graph is a tree, multiple incidences");
        }
    }

    g.mVertices[v].second.mInEdges.emplace_back(u);
    auto& e = g.mVertices[u].second.mOutEdges.emplace_back();
    e.second = v;
    return std::make_pair(edge_descriptor(u, v, &e.first), true);
}

template<class VertexProperty, class EdgeProperty>
inline std::pair<typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::edge_descriptor, bool>
add_edge(typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor u,
    typename boost::graph_traits<ContentTree<VertexProperty, EdgeProperty>>::vertex_descriptor v,
    const EdgeProperty& et,
    ContentTree<VertexProperty, EdgeProperty>& g
) {
    auto res = add_edge(u, v, g);
    if (res.second) {
        *(static_cast<EdgeProperty*>(res.first.get_property())) = et;
    }
    return res;
}

} // namespace Star
