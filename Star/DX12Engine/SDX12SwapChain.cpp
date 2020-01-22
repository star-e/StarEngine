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

#include "SDX12SwapChain.h"
#include "SDX12RenderWorks.h"

namespace Star::Graphics::Render {

DX12SwapChain::DX12SwapChain(ID3D12Device* pDevice, const EngineMemory& memory,
    boost::intrusive_ptr<DX12RenderGraphData> render)
    : mMemory(memory)
    , mDevice(pDevice)
    , mRenderGraph(std::move(render))
    , mWaitWork(std::make_shared<boost::asio::io_context::work>(mWaitService))
{
}

bool DX12SwapChain::try_resize(const SwapChainContext& context) {
    if (mWidth != context.mWidth || mHeight != context.mHeight ||
        mMaxFrameLatency != context.mMaxFrameLatency ||
        mUseWaitableObject != context.mUseWaitableObject)
    {
        *static_cast<SwapChainContext*>(this) = context;
        return true;
    }
    return false;
}

void DX12SwapChain::createFramebuffers(IDXGIFactory4* pFactory,
    ID3D12Device* pDevice, ID3D12CommandQueue* pDirectQueue
) {
    Expects(!mSwapChain);
    Expects(mWidth && mHeight);

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    swapChainDesc.Stereo = FALSE;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = mRenderGraph->mRenderGraph.mNumBackBuffers;
    swapChainDesc.Scaling = DXGI_SCALING_NONE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED; // unused
    swapChainDesc.Flags = mUseWaitableObject ?
        DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT : 0;

    swapChainDesc.Width = mWidth;
    swapChainDesc.Height = mHeight;

    com_ptr<IDXGISwapChain1> baseChain;
    auto hWnd = static_cast<HWND>(mWindowHandle);

    V(pFactory->CreateSwapChainForHwnd(
        pDirectQueue,		// Swap chain needs the queue so that it can force a flush on it.
        hWnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        baseChain.put()
    ));

    mSwapChain = baseChain.as<IDXGISwapChain3>();

    V(pFactory->MakeWindowAssociation(hWnd,
        DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN));
    STAR_SET_DEBUG_NAME(mSwapChain, std::string("SwapChain: ") + mName);

    if (swapChainDesc.Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT) {
        V(mSwapChain->SetMaximumFrameLatency(std::max(1u, mMaxFrameLatency)));
        mSwapEvent.attach(mSwapChain->GetFrameLatencyWaitableObject());
    }

    createRenderSolutionRenderTargets(mDevice, mSwapChain.get(), mRenderGraph->mRenderGraph, mCurrentSolution);
}

void DX12SwapChain::resizeFramebuffers() {
    Expects(mSwapChain);

    mRenderGraph->mRenderGraph.mFramebuffers.clear();
    clearRenderTargets(mRenderGraph->mRenderGraph);

    V(mSwapChain->ResizeBuffers(
        mRenderGraph->mRenderGraph.mNumBackBuffers,
        mWidth,
        mHeight,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        mUseWaitableObject ?
        DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT : 0));

    if (mUseWaitableObject) {
        V(mSwapChain->SetMaximumFrameLatency(std::max(1u, mMaxFrameLatency)));
    }

    createRenderSolutionRenderTargets(mDevice, mSwapChain.get(), mRenderGraph->mRenderGraph, mCurrentSolution);
}

void DX12SwapChain::present() {
    mSwapChain->Present(mSyncInterval, 0);
}

}
