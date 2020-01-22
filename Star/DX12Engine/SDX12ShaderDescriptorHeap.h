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
#include <Star/Graphics/SDescriptorPools.h>
#include <Star/DX12Engine/SDX12DescriptorArray.h>

namespace Star::Graphics::Render {

struct DX12ShaderDescriptorRange {
    DX12DescriptorHandle operator[](size_t offset) const noexcept {
        Expects(mDescriptorSize);

        DX12DescriptorHandle res{
            first.mCpuHandle.ptr + offset * mDescriptorSize,
            first.mGpuHandle.ptr + offset * mDescriptorSize
        };
        Expects(res.mCpuHandle.ptr < second.mCpuHandle.ptr);
        Expects(res.mGpuHandle.ptr < second.mGpuHandle.ptr);
        return res;
    }
    DX12DescriptorHandle first;
    DX12DescriptorHandle second;

    uint32_t mDescriptorSize = 0;
};

class DX12ShaderDescriptorHeap {
public:
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
    allocator_type get_allocator() const noexcept {
        return mCircular.get_allocator().resource();
    }

    struct Desc {
        uint32_t mCapacity = 0;
        uint32_t mCicularReserve = 0;
        uint32_t mFrameSize = 3;
        uint32_t mBlockSize = 64;
        uint32_t mMaxPersistentRangeSize = 8;
    };

    DX12ShaderDescriptorHeap(ID3D12Device* pDevice,
        const Desc& desc, const allocator_type& alloc);

    DX12ShaderDescriptorRange allocateCircular(uint32_t count);
    DX12ShaderDescriptorRange allocatePersistent(uint32_t count);
    DX12ShaderDescriptorRange allocateMonotonic(uint32_t count);

    void deallocatePersistent(D3D12_CPU_DESCRIPTOR_HANDLE curr, uint32_t count) noexcept;
    void advanceFrame();
    DX12DescriptorHandle advance(const DX12DescriptorHandle& prev, size_t sz) const noexcept {
        return DX12DescriptorHandle{
            prev.mCpuHandle.ptr + sz * mHeap.getDescriptorSize(),
            prev.mGpuHandle.ptr + sz * mHeap.getDescriptorSize(),
        };
    }
    ID3D12DescriptorHeap* get() const noexcept {
        return mHeap.get();
    }
private:
    DX12DescriptorArray<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV> mHeap;
    Graphics::DescriptorPool mPool;
    Graphics::CircularDescriptorPool mCircular;
    Graphics::PersistentDescriptorPool mPersistent;
    Graphics::MonotonicDescriptorPool mMonotonic;
};

//PRINT_SIZE(DX12ShaderDescriptorHeap);

}
