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
#include <Star/DX12Engine/SDX12Types.h>
#include <Star/DX12Engine/SDX12SwapChain.h>
#include <Star/DX12Engine/SDX12FrameQueue.h>
#include <Star/Graphics/SContentTypes.h>

namespace Star::Graphics::Render {

class DX12Engine : public Engine {
public:
    DX12Engine(const EngineMemory& memory, const Context& context, const Configs& configs);
    DX12Engine(const DX12Engine&) = delete;
    DX12Engine& operator=(const DX12Engine&) = delete;
    ~DX12Engine();

    void start() override;
    void stop() override;

    void resizeSwapChain(uint32_t id, const SwapChainContext& sc) override;
    void startSwapChain(uint32_t id, void* hWnd) override;
    void stopSwapChain(uint32_t id) override;
    void renderSwapChain(uint32_t id) override;
private:
    void waitForGpu();
    void render(uint32_t id);

    std::thread::id mThreadID = {};
    EngineMemory mMemory;
    Context mContext;

    std::shared_ptr<boost::asio::io_context::work> mTaskWork;

    // Factory
    com_ptr<IDXGIFactory4> mFactory;

    // Device 
    com_ptr<ID3D12Device> mDevice;

    // EngineFence
    com_ptr<ID3D12Fence> mFence;
    winrt::handle mFenceEvent;
    UINT64 mCurrentFence = 0;

    // Upload Buffer Pool
    DX12UploadBufferPool mUploadBufferPool;

    // FrameQueue
    DX12FrameQueue mFrameQueue;

    // Resources
    DX12Resources mPersistentResources;

    // SwapChains    
    std::pmr::vector<std::shared_ptr<DX12SwapChain>> mSwapChains;
};

}
