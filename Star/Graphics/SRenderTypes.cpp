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

#include "SRenderTypes.h"

namespace Star {

namespace Graphics {

namespace Render {

ConstantBuffer::allocator_type ConstantBuffer::get_allocator() const noexcept {
    return allocator_type(mBuffer.get_allocator().resource());
}

ConstantBuffer::ConstantBuffer(const allocator_type& alloc)
    : mBuffer(alloc)
    , mIndex(alloc)
{}

ConstantBuffer::ConstantBuffer(ConstantBuffer const& rhs, const allocator_type& alloc)
    : mBuffer(rhs.mBuffer, alloc)
    , mIndex(rhs.mIndex, alloc)
{}

ConstantBuffer::ConstantBuffer(ConstantBuffer&& rhs, const allocator_type& alloc)
    : mBuffer(std::move(rhs.mBuffer), alloc)
    , mIndex(std::move(rhs.mIndex), alloc)
{}

ConstantBuffer::~ConstantBuffer() = default;

} // namespace Render

} // namespace Graphics

} // namespace Star
