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

#include "SLuminousApp.h"
#include <Star/DX12Engine/SDX12Factory.h>
#include "SLuminousGameWindow.h"

namespace Star {

using namespace Graphics::Render;

namespace {
LuminousDesktop* sApp = nullptr;
}

LuminousDesktop& LuminousDesktop::instance() {
    Expects(sApp);
    return *sApp;
}

LuminousDesktop::LuminousDesktop(HINSTANCE hInstance, int nCmd)
    : DesktopApp(hInstance, DesktopApp::Desc{})
    // buffers
    //, mPerFrameBuffer(4 * 1024 * 1024)
    //, mPerPassBuffer(4 * 1024 * 1024)
    //, mPerBatchBuffer(4 * 1024 * 1024)
    //, mPerInstanceBuffer(4 * 1024 * 1024)
    // memory resources
    //, mPoolMonotonic(64 * 1024 * 1024)
    //, mMonotonic(16 * 1024 * 1024)
    //, mPerFrame(mPerFrameBuffer.data(), mPerFrameBuffer.size(), std::pmr::null_memory_resource())
    //, mPerPass(mPerPassBuffer.data(), mPerPassBuffer.size(), std::pmr::null_memory_resource())
    //, mPerBatch(mPerBatchBuffer.data(), mPerBatchBuffer.size(), std::pmr::null_memory_resource())
    //, mPerInstance(mPerInstanceBuffer.data(), mPerInstanceBuffer.size(), std::pmr::null_memory_resource())
    // pool
    //, mPool(&mPoolMonotonic)
    , mAssetManager(std::make_unique<Asset::AssetFactory>(
        R"(asset)", R"(windows2)",
        std::pmr::get_default_resource()))
    , mCmd(nCmd)
{
    Engine::Configs configs{};
    configs.mNumSwapChains = 1;
    configs.mFrameQueueSize = 3;
    configs.mShaderDescriptorCapacity = 8192;
    configs.mShaderDescriptorCircularReserve = 2048;

    Engine::Context context{
        &mRenderService, &mTaskService,
        &mRenderStrand, &mTaskStrand,
    };

    EngineMemory memory{
        &mPool,
        &mMonotonic,
        &mPerFrame,
        &mPerPass,
        &mPerBatch,
        &mPerInstance
    };

    mEngine = Star::Graphics::Render::createDX12Engine(memory, context, configs);

    Expects(!sApp);
    sApp = this;

    LuminousGameWindow::window_class::Register();
}

LuminousDesktop::~LuminousDesktop() {
    Expects(sApp);
    sApp = nullptr;
}

void LuminousDesktop::resizeWindow(const Graphics::Render::SwapChainContext& context) {
    auto id = mWindows.at(context.mName);
    mEngine->resizeSwapChain(id, context);
}

void LuminousDesktop::startWindow(std::string_view name, HWND hWnd) {
    auto id = at(mWindows, name);
    mEngine->startSwapChain(id, hWnd);
}

void LuminousDesktop::stopWindow(std::string_view name) {
    auto id = at(mWindows, name);
    mEngine->stopSwapChain(id);
}

void LuminousDesktop::renderWindow(std::string_view name) {
    auto id = at(mWindows, name);
    mEngine->renderSwapChain(id);
}

void LuminousDesktop::start() {
    mAssetManager->scan();
    mAssetManager->registerProducers();

    mEngine->start();

    uint32_t id = gsl::narrow_cast<uint32_t>(mWindows.size());
    auto res = mWindows.emplace("GameWindow", id);
    Ensures(res.second);

    try_spawnWindow(1280, 720, mCmd, LuminousGameWindow::class_name(),
        L"Star.Luminous.GameWindow", "GameWindow",
        new LuminousGameWindow::Desc{ "GameWindow" });
}

void LuminousDesktop::stop() noexcept {
    mEngine->stop();
}

}
