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

namespace Star::Graphics::Render {

class DX12DescriptorHandle {
public:
    const D3D12_CPU_DESCRIPTOR_HANDLE mCpuHandle;
    const D3D12_GPU_DESCRIPTOR_HANDLE mGpuHandle;
};

struct DX12DescriptorArrayBase {
    DX12DescriptorArrayBase() = default;
    DX12DescriptorArrayBase(ID3D12Device* Device, uint32_t Size,
        D3D12_DESCRIPTOR_HEAP_TYPE HeapType,
        D3D12_DESCRIPTOR_HEAP_FLAGS HeapFlags);

    void resize(ID3D12Device* Device, uint32_t Size, D3D12_DESCRIPTOR_HEAP_TYPE HeapType,
        D3D12_DESCRIPTOR_HEAP_FLAGS HeapFlags);

    uint32_t size() const noexcept {
        return mArraySize;
    }

    bool empty() const noexcept {
        return mArraySize == 0;
    }

    void clear() noexcept;

    DX12DescriptorHandle operator[](uint32_t i) const noexcept {
        Expects(i < mArraySize);
        return { getCpuHandle(i), getGpuHandle(i) };
    }

    D3D12_CPU_DESCRIPTOR_HANDLE getCpuHandle(size_t i) const noexcept {
        auto h = mCpuBase;
        h.ptr += i * mDescriptorSize;
        return h;
    }

    D3D12_GPU_DESCRIPTOR_HANDLE getGpuHandle(size_t i) const noexcept {
        auto h = mGpuBase;
        h.ptr += i * mDescriptorSize;
        return h;
    }

    ID3D12DescriptorHeap* get() const noexcept {
        return mHeap.get();
    }

    const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_begin() const noexcept {
        return mCpuBase;
    }
    const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_begin() const noexcept {
        return mGpuBase;
    }
    uint32_t getIndex(D3D12_CPU_DESCRIPTOR_HANDLE handle) const noexcept {
        Expects(handle.ptr >= mCpuBase.ptr);
        Expects((handle.ptr - mCpuBase.ptr) % mDescriptorSize == 0);
        return gsl::narrow_cast<uint32_t>((handle.ptr - mCpuBase.ptr) / mDescriptorSize);
    }
    uint32_t getDescriptorSize() const noexcept {
        return mDescriptorSize;
    }
private:
    com_ptr<ID3D12DescriptorHeap> mHeap;
    uint32_t mArraySize = 0;
    uint32_t mDescriptorSize = 0;
    D3D12_CPU_DESCRIPTOR_HANDLE mCpuBase = {};
    D3D12_GPU_DESCRIPTOR_HANDLE mGpuBase = {};
};

template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
struct DX12DescriptorArray : DX12DescriptorArrayBase {
    DX12DescriptorArray() = default;
    DX12DescriptorArray(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_FLAGS flags, UINT sz)
        : DX12DescriptorArrayBase(pDevice, sz, HeapType, flags)
    {}

    void resize(ID3D12Device* Device, uint32_t Size, D3D12_DESCRIPTOR_HEAP_FLAGS HeapFlags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE) {
        DX12DescriptorArrayBase::resize(Device, Size, HeapType, HeapFlags);
    }
};

}
