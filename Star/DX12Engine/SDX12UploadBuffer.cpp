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

#include "SDX12UploadBuffer.h"

namespace Star::Graphics::Render {

DX12UploadBufferBlock::DX12UploadBufferBlock(gsl::not_null<ID3D12Device*> pDevice, size_t size, uint32_t id) {
    size = boost::alignment::align_up(size, sAlignment);

    D3D12_HEAP_PROPERTIES heap{ D3D12_HEAP_TYPE_UPLOAD };

    D3D12_RESOURCE_DESC desc{
        D3D12_RESOURCE_DIMENSION_BUFFER, 0,
        size, 1, 1, 1,
        DXGI_FORMAT_UNKNOWN,{ 1, 0 },
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        D3D12_RESOURCE_FLAG_NONE
    };

    auto hr = pDevice->CreateCommittedResource(
        &heap,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(mBuffer.put()));

    STAR_SET_DEBUG_NAME(mBuffer.get(), "upload buffer " + std::to_string(id));

    if (FAILED(hr)) {
        return;
    }

    void* pData = nullptr;
    D3D12_RANGE readRange{ 0, 0 };
    V(mBuffer->Map(0, &readRange, &pData));
    mDataBegin = reinterpret_cast<std::byte*>(pData);
    mDataCur = mDataBegin;
    mDataEnd = mDataBegin + size;
}

DX12UploadBufferPool::DX12UploadBufferPool(ID3D12Device* pDevice, size_t bufferSize, uint32_t capacity)
    : mDevice(pDevice)
    , mBufferSize(bufferSize)
{
    for (size_t i = 0; i != capacity; ++i) {
        auto ptr = std::make_unique<DX12UploadBufferBlock>(pDevice, mBufferSize,
            gsl::narrow_cast<uint32_t>(mBufferCount++));
        mBuffers.emplace_back(std::move(ptr));
    }
}

std::unique_ptr<DX12UploadBufferBlock> DX12UploadBufferPool::create() const {
    std::unique_ptr<DX12UploadBufferBlock> ptr;
    std::lock_guard<std::mutex> guard(mMutex);
    if (!mBuffers.empty()) {
        ptr.reset(mBuffers.front().release());
        mBuffers.pop_front();
    } else {
        ptr = std::make_unique<DX12UploadBufferBlock>(mDevice, mBufferSize, mBufferCount++);
    }
    return ptr;
}

void DX12UploadBufferPool::recycle(std::unique_ptr<DX12UploadBufferBlock> ptr) const noexcept {
    std::lock_guard<std::mutex> guard(mMutex);
    ptr->clear();
    mBuffers.push_back(std::move(ptr));
}

DX12UploadBuffer::DX12UploadBuffer(const DX12UploadBufferPool& pool, uint32_t frameQueueSize, int64_t frameID)
    : mPool(&pool)
    , mFrameQueueSize(frameQueueSize)
    , mFrameID(frameID)
{}

DX12UploadBuffer::~DX12UploadBuffer() {
    while (!mBuffers.empty()) {
        recycle_front();
    }
}

void DX12UploadBuffer::advanceFrame(int64_t frameID) noexcept {
    mFrameID = frameID;
}

void DX12UploadBuffer::releaseBuffer(int64_t frameID) noexcept {
    while (!mBuffers.empty()) {
        if (mBuffers.front()->frameID() <= frameID) {
            recycle_front();
        } else {
            break;
        }
    }
}

void DX12UploadBuffer::advanceFrame() noexcept {
    ++mFrameID;

    auto previousGpuFrame = mFrameID - mFrameQueueSize;

    while (!mBuffers.empty()) {
        if (mBuffers.front()->frameID() <= previousGpuFrame) {
            recycle_front();
        } else {
            break;
        }
    }
}

std::pair<DX12BufferData, bool> DX12UploadBuffer::try_upload(
    const void* pData, size_t bytesPerData, uint32_t dataCount, size_t alignment
) {
    Expects(DX12UploadBufferBlock::sAlignment >= alignment);

    size_t size = bytesPerData * dataCount;
    size_t alignedSize = boost::alignment::align_up(size, alignment);
    Expects(alignedSize <= mPool->getMaxBufferSize());

    std::byte* pDst = nullptr;
    bool succeeded = false;

    if (!mBuffers.empty()) {
        Expects(mBuffers.back());
        std::tie(pDst, succeeded) = mBuffers.back()->try_suballocate(size, alignment, mFrameID);
    }

    DX12UploadBufferBlock* pBuffer = nullptr;
    if (succeeded) {
        pBuffer = mBuffers.back().get();
    } else {
        if (try_allocate()) {
            pBuffer = mBuffers.back().get();
            Expects(pBuffer);
            std::tie(pDst, succeeded) = pBuffer->try_suballocate(size, alignment, mFrameID);
            Ensures(succeeded);
            if (!succeeded)
                return { DX12BufferData{}, false };
        } else {
            return { DX12BufferData{}, false };
        }
    }

    Expects(pBuffer);
    Ensures(pBuffer->resource());
    Expects(pDst);

    memcpy(pDst, pData, size);

    Expects(pDst >= mBuffers.back()->begin());
    auto diff = gsl::narrow_cast<uint64_t>(pDst - mBuffers.back()->begin());
    return std::pair{ DX12BufferData{ pBuffer->resource(), diff }, true };
}

DX12BufferData DX12UploadBuffer::upload(const void* pData, size_t bytesPerData, uint32_t dataCount, size_t alignment) {
    auto res = try_upload(pData, bytesPerData, dataCount, alignment);
    if (!res.second) {
        throw std::runtime_error("upload gpu buffer failed");
    }
    return res.first;
}

bool DX12UploadBuffer::try_allocate() {
    auto ptr = mPool->create();
    Ensures(ptr);
    if (ptr->begin()) {
        mBuffers.push_back(std::move(ptr));
        return true;
    } else {
        return false;
    }
}

void DX12UploadBuffer::recycle_front() noexcept {
    Expects(!mBuffers.empty());
    mPool->recycle(std::move(mBuffers.front()));
    mBuffers.pop_front();
}

}
