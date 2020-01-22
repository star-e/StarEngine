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
#include <Star/DX12Engine/SDX12Types.h>

namespace Star::Graphics::Render {

class DX12UploadBufferPool;

class DX12UploadBufferBlock {
public:
    // https://docs.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_resource_desc
    // buffer alighment must be 64KB (D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT) or 0,
    // which is effectively 64KB
    static const size_t sAlignment = 64 * 1024;

    DX12UploadBufferBlock(gsl::not_null<ID3D12Device*> pDevice, size_t size, uint32_t id);
    DX12UploadBufferBlock(const DX12UploadBufferBlock&) = delete;
    DX12UploadBufferBlock& operator=(const DX12UploadBufferBlock&) = delete;

    std::pair<std::byte*, bool> try_suballocate(size_t uSize, size_t uAlign, int64_t frameID) noexcept {
        auto pDst = static_cast<std::byte*>(boost::alignment::align_up(mDataCur, uAlign));
        bool succeeded = false;
        if (pDst + uSize > mDataEnd) {
            succeeded = false;
        } else {
            mDataCur = pDst + uSize;
            mLastFrame = frameID;
            succeeded = true;
        }
        return { pDst, succeeded };
    }

    void clear() noexcept {
        mDataCur = mDataBegin;
    }
    ID3D12Resource* resource() noexcept {
        return mBuffer.get();
    }
    D3D12_GPU_VIRTUAL_ADDRESS gpu_data() noexcept {
        return mBuffer->GetGPUVirtualAddress();
    }
    std::byte* begin() noexcept {
        return mDataBegin;
    }
    std::byte* end() noexcept {
        return mDataEnd;
    }
    int64_t frameID() const noexcept {
        return mLastFrame;
    }
private:
    com_ptr<ID3D12Resource> mBuffer;
    D3D12_GPU_VIRTUAL_ADDRESS mGpuVirtualAddress = {};
    std::byte* mDataBegin = nullptr;
    std::byte* mDataCur = nullptr;
    std::byte* mDataEnd = nullptr;
    int64_t mLastFrame = -1;
};
static_assert(sizeof(DX12UploadBufferBlock) == 48);

class DX12UploadBufferPool {
public:
    DX12UploadBufferPool(ID3D12Device* pDevice, size_t bufferSize, uint32_t capacity);
    DX12UploadBufferPool(const DX12UploadBufferPool&) = delete;
    DX12UploadBufferPool& operator=(const DX12UploadBufferPool&) = delete;

    size_t getMaxBufferSize() const noexcept {
        return mBufferSize;
    }

    std::unique_ptr<DX12UploadBufferBlock> create() const;
    void recycle(std::unique_ptr<DX12UploadBufferBlock> ptr) const noexcept;
private:
    gsl::not_null<ID3D12Device*> mDevice;
    size_t mBufferSize = 0;
    mutable uint32_t mBufferCount = 0;
    mutable std::mutex mMutex;
    mutable std::deque<std::unique_ptr<DX12UploadBufferBlock>> mBuffers;
};

class DX12UploadBuffer {
public:
    DX12UploadBuffer(const DX12UploadBufferPool& pool, uint32_t frameQueueSize, int64_t frameID = -1);
    DX12UploadBuffer(const DX12UploadBuffer&) = delete;
    DX12UploadBuffer& operator=(const DX12UploadBuffer&) = delete;
    ~DX12UploadBuffer();

    void advanceFrame(int64_t frameID) noexcept;
    void releaseBuffer(int64_t frameID) noexcept;
    void advanceFrame() noexcept;

    std::pair<DX12BufferData, bool> try_upload(const void* pData,
        size_t bytesPerData, uint32_t dataCount = 1, size_t alignment = 16);

    DX12BufferData upload(const void* pData,
        size_t bytesPerData, uint32_t dataCount = 1, size_t alignment = 16);
private:
    bool try_allocate();
    void recycle_front() noexcept;

    gsl::not_null<const DX12UploadBufferPool*> mPool;
    std::deque<std::unique_ptr<DX12UploadBufferBlock>> mBuffers;
    uint32_t mFrameQueueSize = 0;
    int64_t mFrameID = -1;
};

}
