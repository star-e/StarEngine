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
#include <Star/Core/SCoreTypes.h>
#include <Star/DX12Engine/SDX12UploadBuffer.h>

namespace Star::Graphics::Render {

class DX12UploadBuffer;
class DX12ShaderDescriptorHeap;

struct CreationContext {
    void record() {
        mUploadBuffer->advanceFrame(mNextFrameFence);
        mCommandList->Reset(mCommandAllocator, nullptr);
    }
    void flush() {
        V(mCommandList->Close());
        ID3D12CommandList* ppCommandLists[] = { mCommandList };
        mDirectQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
        auto fenceID = mNextFrameFence;
        check_hresult(mDirectQueue->Signal(mFence.get(), mNextFrameFence));
        ++mNextFrameFence;

        check_hresult(mFence->SetEventOnCompletion(fenceID, mFenceEvent.get()));
        WaitForSingleObject(mFenceEvent.get(), INFINITE);
        mCommandAllocator->Reset();
        mMemoryAllocated = 0;
        mUploadBuffer->releaseBuffer(fenceID);
    }
    DX12BufferData upload(const std::pmr::vector<char>& buffer, size_t alignment) {
        auto accumulatedSize = mMemoryAllocated + buffer.size();
        if (accumulatedSize > mMaxUploadSize) {
            flush();
            record();
        }
        mMemoryAllocated += buffer.size();
        return mUploadBuffer->upload(buffer.data(), buffer.size(), 1, alignment);
    }
    DX12BufferData upload(const void* data, size_t sz, size_t alignment) {
        auto accumulatedSize = mMemoryAllocated + sz;
        if (accumulatedSize > mMaxUploadSize) {
            flush();
            record();
        }
        mMemoryAllocated += sz;
        return mUploadBuffer->upload(data, sz, 1, alignment);
    }
    ID3D12Device* mDevice = nullptr;
    ID3D12CommandQueue* mDirectQueue = nullptr;
    ID3D12CommandAllocator* mCommandAllocator = nullptr;
    ID3D12GraphicsCommandList* mCommandList = nullptr;
    std::pmr::monotonic_buffer_resource* mMemoryArena = nullptr;
    size_t mMaxUploadSize = 0;
    MetaID mRenderGraph = {};
    DX12UploadBuffer* mUploadBuffer = nullptr;
    DX12ShaderDescriptorHeap* mDescriptorHeap = nullptr;
    com_ptr<ID3D12Fence> mFence;
    winrt::handle mFenceEvent;
    uint64_t mNextFrameFence = 1;
    size_t mMemoryAllocated = 0;
};

bool try_createDX12(CreationContext&context,
    DX12Resources& resources, const MetaID& metaID, Core::ResourceType tag, bool async = true);

inline bool try_streamDX12(DX12Resources& resources, const MetaID& metaID) {
    return false;
}

}
