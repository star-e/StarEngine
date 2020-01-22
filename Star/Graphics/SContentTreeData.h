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

namespace Star {

template<class VertexProperty, class EdgeProperty = std::monostate>
class ContentTree {
    template<class EdgeProperty>
    class EdgeList {
    public:
        using allocator_type = std::pmr::polymorphic_allocator<std::byte>;

        allocator_type get_allocator() const noexcept {
            return mOutEdges.get_allocator().resource();
        }

        EdgeList(const allocator_type & alloc) noexcept
            : mOutEdges(alloc.resource())
            , mInEdges()
        {}

        EdgeList(EdgeList&& rhs, const allocator_type& alloc)
            : mOutEdges(std::move(rhs.mOutEdges), alloc.resource())
            , mInEdges(std::move(rhs.mInEdges))
        {}

        EdgeList& operator=(EdgeList&& rhs) = default;

        std::pmr::vector<std::pair<EdgeProperty, size_t>> mOutEdges;
        boost::container::static_vector<size_t, 1> mInEdges;
    };
public:
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;

    using OutEdgeContainer = std::pmr::vector<std::pair<EdgeProperty, size_t>>;
    using InEdgeContainer = boost::container::static_vector<size_t, 1>;
    using VertexList = std::pmr::vector<EdgeList<EdgeProperty>> ;
    using EdgeDescriptor = boost::detail::edge_desc_impl<boost::bidirectional_tag, size_t>;

    allocator_type get_allocator() const noexcept {
        return mVertices.get_allocator().resource();
    }

    ContentTree(const allocator_type& alloc) noexcept
        : mVertices(alloc)
    {}

    ContentTree(ContentTree&& rhs, const allocator_type & alloc)
        : mVertices(std::move(rhs.mVertices), alloc)
    {}

    ContentTree& operator=(ContentTree&& rhs) = default;

    VertexProperty& operator[](size_t vertID) {
        return mVertices[vertID].second.mProperty;
    }

    const VertexProperty& operator[](size_t vertID) const {
        return mVertices[vertID].second.mProperty;
    }

    EdgeProperty& operator[](const EdgeDescriptor& e) {
        return *const_cast<EdgeProperty*>(static_cast<const EdgeProperty*>(e.get_property()));
    }

    const EdgeProperty& operator[](const EdgeDescriptor& e) const {
        return *static_cast<const EdgeProperty*>(e.get_property());
    }

    std::pmr::vector<std::pair<VertexProperty, EdgeList<EdgeProperty>>> mVertices;
};

}
