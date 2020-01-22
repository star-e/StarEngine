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
#include <Star/Graphics/SConfig.h>

namespace Star::Graphics::Render {

struct SwapChainContext {
    const char* mName = "";
    void* mWindowHandle = nullptr;
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
    uint32_t mMaxFrameLatency = 2;
    uint32_t mSyncInterval = 0;
    bool mUseWaitableObject = true;
};

struct EngineMemory {
    std::pmr::synchronized_pool_resource* mPool = nullptr; // thread safe
    std::pmr::monotonic_buffer_resource* mMonotonic = nullptr;
    std::pmr::monotonic_buffer_resource* mPerFrame = nullptr;
    std::pmr::monotonic_buffer_resource* mPerPass = nullptr;
    std::pmr::monotonic_buffer_resource* mPerBatch = nullptr;
    std::pmr::monotonic_buffer_resource* mPerInstance = nullptr;
};

class STAR_GRAPHICS_API Engine {
public:
    struct Context {
        boost::asio::io_context* mRenderService = nullptr;
        boost::asio::io_context* mTaskService = nullptr;

        boost::asio::io_context::strand* mRenderStrand = nullptr;
        boost::asio::io_context::strand* mTaskStrand = nullptr;
    };

    struct Configs {
        uint32_t mNumSwapChains = 0;
        uint32_t mFrameQueueSize = 3;
        uint32_t mShaderDescriptorCapacity = 0;
        uint32_t mShaderDescriptorCircularReserve = 0;
        std::string_view mRenderGraph;
    };

    Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    virtual ~Engine() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void resizeSwapChain(uint32_t id, const SwapChainContext& sc) = 0;

    virtual void startSwapChain(uint32_t id, void* hWnd) = 0;
    virtual void stopSwapChain(uint32_t id) = 0;
    virtual void renderSwapChain(uint32_t id) = 0;
};

}
