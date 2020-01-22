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

#include "SDX12Engine.h"
#include <Star/Graphics/SContentSerialization.h>
#include <Star/Graphics/SRenderGraphSerialization.h>
#include <Star/Graphics/SContentUtils.h>
#include <Star/Graphics/SRenderFormatTextureUtils.h>
#include <Star/Graphics/SWindowMessages.h>
#include "SDX12Utils.h"
#include <boost/uuid/uuid_io.hpp>
#include "SDX12Helpers.h"

namespace Star::Graphics::Render {

DX12Engine::DX12Engine(
    const EngineMemory& memory,
    const Context& context,
    const Configs& configs)
    : mThreadID(std::this_thread::get_id())
    , mMemory(memory)
    , mContext(context)
    , mTaskWork(std::make_shared<boost::asio::io_context::work>(*context.mTaskService))
    , mFactory(DX12::createFactory())
    , mDevice(DX12::createDevice(mFactory.get()))
    , mFence(DX12::createFence(mDevice.get(), mCurrentFence, "EngineFence", false))
    , mFenceEvent(DX12::createFenceEvent())
    , mUploadBufferPool(mDevice.get(), 4 * 1024 * 1024, 8)
    , mFrameQueue(mDevice.get(), mUploadBufferPool, configs, mMemory.mMonotonic)
    , mPersistentResources(mMemory.mPool)
    , mSwapChains(configs.mNumSwapChains, mMemory.mMonotonic)
{

}

DX12Engine::~DX12Engine() = default;

void DX12Engine::stop() {
    Expects(std::this_thread::get_id() == mThreadID);
    mTaskWork.reset();
    waitForGpu();
}

void DX12Engine::start() {
    Expects(std::this_thread::get_id() == mThreadID);

    {
        std::ifstream ifs(R"(windows2\settings.star)", std::ios::binary);
        ifs.exceptions(std::istream::failbit);
        if (ifs) {
            PmrBinaryInArchive ia(ifs, mPersistentResources.mSettings.get_allocator().resource());
            ia >> mPersistentResources.mSettings;
        }
    }

    DX12UploadBuffer uploadBuffer(mUploadBufferPool,
        gsl::narrow_cast<uint32_t>(mFrameQueue.mFrames.size()), 0);

    CreationContext creation{ mDevice.get(), mFrameQueue.mDirectQueue.get(),
        mFrameQueue.mFrames.at(mFrameQueue.mNextFrameIndex).mCommandAllocator.get(),
        mFrameQueue.mFrames.at(mFrameQueue.mNextFrameIndex).mCommandList.get(),
        mMemory.mPerFrame,
        4 * 1024 * 1024, {},
        &uploadBuffer,
        &mFrameQueue.mDescriptors,
        DX12::createFence(mDevice.get(), mCurrentFence, "CreationFence", false),
        DX12::createFenceEvent()
    };

    creation.record();
    {
        // default textures
        auto& white = mPersistentResources.mDefaultTextures.emplace_back();
        white.mFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

        D3D12_RESOURCE_DESC desc{};
        desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        desc.Alignment = 0;
        desc.Width = 1;
        desc.Height = 1;
        desc.DepthOrArraySize = 1;
        desc.MipLevels = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
        desc.SampleDesc = { 1, 0 };
        white.mTexture = DX12::createTexture2D(mDevice.get(), desc);

        fixed4 pixel{ 255, 255, 255, 255 };
        //uploadBuffer.upload(&pixel, sizeof(pixel), )
        auto buffer = creation.upload(&pixel, sizeof(pixel), sSliceAlignment);
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout{};
        layout.Offset = buffer.mBufferOffset;
        layout.Footprint.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
        layout.Footprint.Width = 1;
        layout.Footprint.Height = 1;
        layout.Footprint.Depth = 1;
        layout.Footprint.RowPitch = sPitchAlignment;

#ifdef STAR_DEV
        {
            uint64_t RequiredSize = 0;
            D3D12_RESOURCE_DESC Desc = white.mTexture->GetDesc();
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout0{};
            uint32_t rowCount = 0;
            uint64_t rowSize = 0;
            mDevice->GetCopyableFootprints(&Desc, 0, 1, buffer.mBufferOffset, &layout0, &rowCount, &rowSize, &RequiredSize);
            Expects(sizeof(pixel) == RequiredSize);
            Expects(layout.Footprint.RowPitch == layout0.Footprint.RowPitch);
        }
#endif
        D3D12_TEXTURE_COPY_LOCATION Src{ buffer.mResource, D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT, layout };
        D3D12_TEXTURE_COPY_LOCATION Dst{ white.mTexture.get(), D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, 0 };
        creation.mCommandList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);

        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(white.mTexture.get(),
            D3D12_RESOURCE_STATE_COPY_DEST,
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        creation.mCommandList->ResourceBarrier(1, &barrier);
    }
    creation.flush();
    
    MetaID metaID{};
    std::stringstream ss;
    ss << "823b599a-677e-4bb6-83c4-cd28818f3e82";
    ss >> metaID;
    creation.mRenderGraph = metaID;

    creation.record();
    try_createDX12(creation, mPersistentResources, metaID, Core::RenderGraph, false);
    creation.flush();

    mMemory.mPerFrame->release();
}

void DX12Engine::waitForGpu() {
    uint64_t current_fence = ++mCurrentFence;
    mFrameQueue.mDirectQueue->Signal(mFence.get(), current_fence);
    mFence->SetEventOnCompletion(current_fence, mFenceEvent.get());
    WaitForSingleObject(mFenceEvent.get(), INFINITE);
}

void DX12Engine::render(uint32_t id) {
    Expects(std::this_thread::get_id() == mThreadID);

    auto sc = mSwapChains.at(id);

    if (!sc->created()) {
        PostMessageA(reinterpret_cast<HWND>(sc->mWindowHandle), WM_STAR_RENDER, int(true), 0);
        return;
    }

    auto pFrameContext = mFrameQueue.beginFrame(*sc);
    mFrameQueue.renderFrame(pFrameContext, mMemory.mPerFrame);
    mFrameQueue.endFrame(pFrameContext);

    sc->present();

    mMemory.mPerFrame->release();

    auto work = sc->mWaitWork;
    auto& service = sc->mWaitService;
    post(service, [this, sc = std::move(sc), work = std::move(work)]() {
        if (WaitForSingleObjectEx(sc->mSwapEvent.get(), INFINITE, TRUE)) {
            throw std::runtime_error("wait for present failed");
        }
        PostMessageA(reinterpret_cast<HWND>(sc->mWindowHandle), WM_STAR_RENDER, int(true), 0);
    });
}

void DX12Engine::resizeSwapChain(uint32_t id, const SwapChainContext& sc) {
    post(*mContext.mRenderStrand, [=]() {
        Expects(std::this_thread::get_id() == mThreadID);
        Expects(mSwapChains[id]);

        if (mSwapChains[id]->created()) {
            Expects(mSwapChains[id]->mSwapChain);
            // TODO: here we have some performance issue
            if (mSwapChains[id]->try_resize(sc)) {
                waitForGpu();
                mSwapChains[id]->resizeFramebuffers();
                mFrameQueue.initPipeline(*mSwapChains[id]);
            }
        } else {
            mSwapChains[id]->try_resize(sc);
            mSwapChains[id]->createFramebuffers(mFactory.get(), mDevice.get(), mFrameQueue.mDirectQueue.get());
            mFrameQueue.initPipeline(*mSwapChains[id]);
        }
    });
}

void DX12Engine::startSwapChain(uint32_t id, void* hWnd) {
    post(*mContext.mRenderStrand, [=]() {
        MetaID metaID{};
        std::stringstream ss;
        ss << "823b599a-677e-4bb6-83c4-cd28818f3e82";
        ss >> metaID;
        auto iter = mPersistentResources.mRenderGraphs.find(metaID);

        Expects(!mSwapChains.at(id));
        auto& sc = mSwapChains.at(id);
        sc = std::make_shared<DX12SwapChain>(mDevice.get(), mMemory,
            boost::intrusive_ptr<DX12RenderGraphData>(const_cast<DX12RenderGraphData*>(&*iter)));

        sc->mWindowHandle = hWnd;

        sc->mWaitThread = std::thread([sc]() {
            sc->mWaitService.run();
        });

        PostMessageA(reinterpret_cast<HWND>(sc->mWindowHandle), WM_STAR_RENDER, int(true), 0);
    });
}

void DX12Engine::stopSwapChain(uint32_t id) {
    post(*mContext.mRenderStrand, [=]() {
        Expects(std::this_thread::get_id() == mThreadID);
        auto& sc = mSwapChains.at(id);
        Expects(sc);
        sc->mWaitWork.reset();
        sc->mWaitThread.join();
        waitForGpu();
        sc.reset();
    });
}

void DX12Engine::renderSwapChain(uint32_t id) {
    post(*mContext.mRenderStrand, [=]() {
        Expects(std::this_thread::get_id() == mThreadID);
        render(id);
    });
}

}
