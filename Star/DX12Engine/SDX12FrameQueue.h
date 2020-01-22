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
#include <Star/Graphics/SRenderEngine.h>
#include <Star/Graphics/SRenderFwd.h>
#include <Star/Graphics/SRenderGraphFwd.h>
#include <Star/DX12Engine/SDX12Fwd.h>
#include <Star/DX12Engine/SDX12ShaderDescriptorHeap.h>
#include <Star/DX12Engine/SDX12SamplerDescriptorHeap.h>
#include <Star/DX12Engine/SDX12UploadBuffer.h>

namespace Star::Graphics::Render {

class DX12SwapChain;
class DX12RenderResources;

struct DX12FrameContext {
    DX12FrameContext(ID3D12Device* pDevice, std::string_view name, uint32_t id);

    DX12RenderPipeline const& currentPipeline() const noexcept;
    DX12RenderPipeline& currentPipeline() noexcept;

    uint64_t mFrameFenceId = 0;
    uint32_t mFrameIndex = 0;
    uint32_t mBackBufferIndex = 0;
    uint32_t mBackBufferCount = 0;
    ID3D12Resource* mBackBuffer = nullptr;
    D3D12_CPU_DESCRIPTOR_HANDLE mBackBufferRTV = {};
    D3D12_CPU_DESCRIPTOR_HANDLE mBackBufferRTVsRGB = {};
    com_ptr<ID3D12CommandAllocator> mCommandAllocator;
    com_ptr<ID3D12GraphicsCommandList> mCommandList;

    const DX12RenderSolution* mRenderSolution = nullptr;
    const DX12RenderWorks* mRenderWorks = nullptr;
    uint32_t mSolutionID = 0;
    uint32_t mPipelineID = 0;
};

class DX12FrameQueue {
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mDescriptors.get_allocator();
    }

    DX12FrameQueue(ID3D12Device* pDevice,
        const DX12UploadBufferPool& pool,
        const Engine::Configs& configs,
        const allocator_type& alloc);

    void initPipeline(const DX12SwapChain& sc);

    const DX12FrameContext* beginFrame(const DX12SwapChain& sc);
    void renderFrame(const DX12FrameContext* pContext, std::pmr::memory_resource* mr);
    void endFrame(const DX12FrameContext* pFrame);

    // Fence
    ID3D12Device* mDevice = nullptr;
    uint64_t mNextFrameFence = 0;
    com_ptr<ID3D12Fence> mFence;
    winrt::handle mFenceEvent;

    // Frames
    std::pmr::vector<DX12FrameContext> mFrames;
    uint32_t mNextFrameIndex = 0;

    // DirectQueue
    com_ptr<ID3D12CommandQueue> mDirectQueue;
    uint64_t mCommandQueuePerformanceFrequency = 0;

    // Descriptors
    DX12ShaderDescriptorHeap mDescriptors;
    DX12SamplerDescriptorHeap mSamplerDH;

    // Upload Buffer
    DX12UploadBuffer mUploadBuffer;
};

}
