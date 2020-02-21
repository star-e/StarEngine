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

template<size_t NAlignment>
class AlignedBuffer {
    struct alignas(NAlignment) DataBlock : public std::array<std::byte, NAlignment> {};
public:
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept {
        return allocator_type(mBuffer.get_allocator().resource());
    }
    AlignedBuffer() = delete;
    AlignedBuffer(const AlignedBuffer&) = delete;

    AlignedBuffer(const allocator_type& alloc)
        : mBuffer(alloc.resource())
    {
    }

    AlignedBuffer(AlignedBuffer&& rhs, const allocator_type& alloc)
        : mBuffer(std::move(rhs.mBuffer), alloc)
    {}

    AlignedBuffer(const AlignedBuffer& rhs, const allocator_type& alloc)
        : mBuffer(rhs.mBuffer, alloc)
    {}

    size_t resize_aligned(size_t sz) {
        static_assert(std::is_pod_v<DataBlock>);
        static_assert(sizeof(DataBlock) == NAlignment);
        static_assert(sizeof(std::byte) == 1);

        sz = boost::alignment::align_up(sz, NAlignment);
        Expects(sz % NAlignment == 0);
        size_t count = sz / NAlignment;
        mBuffer.resize(count);
        Expects(sz == 0 || (sz && boost::alignment::is_aligned(NAlignment, mBuffer.data())));
        return sz;
    }

    bool empty() const noexcept {
        return mBuffer.empty();
    }

    size_t size() const noexcept {
        return mBuffer.size() * NAlignment;
    }

    void clear() noexcept {
        mBuffer.clear();
    }

    const std::byte* data() const noexcept {
        return alias_cast<const std::byte*>(mBuffer.data());
    }

    std::byte* data() noexcept {
        return alias_cast<std::byte*>(mBuffer.data());
    }

private:
    std::pmr::vector<DataBlock> mBuffer;
};

using AlignedBuffer16 = AlignedBuffer<16>;

}
