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

#include "pch.h"
#include "SDX12ShaderDescriptorHeap.h"
#include "SDX12Helpers.h"

namespace Star::Graphics::Render {

DX12ShaderDescriptorHeap::DX12ShaderDescriptorHeap(ID3D12Device* pDevice,
    const Desc& desc, const allocator_type& alloc)
    : mHeap(pDevice, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, desc.mCapacity)
    , mPool(desc.mBlockSize, desc.mCapacity, alloc)
    , mCircular(desc.mCapacity, desc.mCicularReserve,
        &mPool, desc.mFrameSize, desc.mBlockSize, alloc)
    , mPersistent(desc.mCapacity, &mPool, desc.mFrameSize, desc.mBlockSize,
        desc.mMaxPersistentRangeSize, alloc)
    , mMonotonic(&mPool, alloc)
{}

DX12ShaderDescriptorRange DX12ShaderDescriptorHeap::allocateCircular(uint32_t count) {
    auto range = mCircular.allocate(count);
    Ensures(range.first != range.second);

    return { mHeap[range.first], mHeap[range.second], mHeap.getDescriptorSize() };
}

DX12ShaderDescriptorRange DX12ShaderDescriptorHeap::allocatePersistent(uint32_t count) {
    Expects(count);
    auto range = mPersistent.allocate(count);
    Ensures(range.first != range.second);

    return { mHeap[range.first], mHeap[range.second], mHeap.getDescriptorSize() };
}

DX12ShaderDescriptorRange DX12ShaderDescriptorHeap::allocateMonotonic(uint32_t count) {
    auto range = mMonotonic.allocate(count);
    Ensures(range.first != range.second);

    return { mHeap[range.first], mHeap[range.second], mHeap.getDescriptorSize() };
}

void DX12ShaderDescriptorHeap::deallocatePersistent(
    D3D12_CPU_DESCRIPTOR_HANDLE curr, uint32_t count
) noexcept {
    Expects(count);
    mPersistent.deallocate(mHeap.getIndex(curr), count);
}

void DX12ShaderDescriptorHeap::advanceFrame() {
    mCircular.advanceFrame();
    mPersistent.advanceFrame();
}

}
