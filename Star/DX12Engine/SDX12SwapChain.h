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

namespace Star::Graphics::Render {

class DX12SwapChain : public SwapChainContext {
public:
    DX12SwapChain(ID3D12Device* pDevice, const EngineMemory& memory, boost::intrusive_ptr<DX12RenderGraphData> render);
    DX12SwapChain(const DX12SwapChain&) = delete;
    DX12SwapChain& operator=(const DX12SwapChain&) = delete;

    bool created() const noexcept {
        return mSwapChain != nullptr;
    }

    void createFramebuffers(IDXGIFactory4* pFactory,
        ID3D12Device* pDevice,
        ID3D12CommandQueue* pDirectQueue);

    bool try_resize(const SwapChainContext& context);
    void resizeFramebuffers();

    void present();

    ID3D12Resource* getBackBuffer(uint32_t id) const noexcept {
        Expects(id < mRenderGraph->mRenderGraph.mNumBackBuffers);
        return mRenderGraph->mRenderGraph.mFramebuffers[id].get();
    }

    D3D12_CPU_DESCRIPTOR_HANDLE getBackBufferDescriptor(uint32_t id, bool sRGB) const noexcept {
        Expects(id < mRenderGraph->mRenderGraph.mNumBackBuffers);
        return mRenderGraph->mRenderGraph.mRTVs.getCpuHandle(size_t(id) + sRGB * mRenderGraph->mRenderGraph.mNumBackBuffers);
    }

    const DX12RenderSolution& currentSolution() const noexcept {
        Expects((size_t)mCurrentSolution < mRenderGraph->mRenderGraph.mSolutions.size());
        return mRenderGraph->mRenderGraph.mSolutions[mCurrentSolution];
    }

    const DX12RenderPipeline& currentPipeline() const noexcept {
        const auto& rw = currentSolution();
        Expects(mCurrentPipeline < rw.mPipelines.size());
        return rw.mPipelines[mCurrentPipeline];
    }

    // BackBuffers
    ID3D12Device* mDevice = nullptr;
    EngineMemory mMemory = {};
    com_ptr<IDXGISwapChain3> mSwapChain;
    winrt::handle mSwapEvent;
    uint32_t mCurrentSolution = 0;
    uint32_t mCurrentPipeline = 0;
    boost::intrusive_ptr<DX12RenderGraphData> mRenderGraph;

    boost::asio::io_context mWaitService;
    std::shared_ptr<boost::asio::io_context::work> mWaitWork;
    std::thread mWaitThread;
};

}
