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
#include "SDesktopApp.h"
#include <Star/Graphics/SRenderEngine.h>
#include <Star/AssetFactory/SAssetFactory.h>

namespace Star {

class LuminousDesktop : public DesktopApp {
public:
    static LuminousDesktop& instance();

    LuminousDesktop(HINSTANCE hInstance, int nCmd, const MetaID& renderGraph,
        std::string_view solutionName, std::string_view pipelineName);
    ~LuminousDesktop();

    void resizeWindow(const Graphics::Render::SwapChainContext& context);
    void startWindow(std::string_view name, HWND hWnd);
    void stopWindow(std::string_view name);
    void renderWindow(std::string_view name);
private:
    void start() override;
    void stop() noexcept override;

    std::vector<std::byte> mPerFrameBuffer;
    std::vector<std::byte> mPerPassBuffer;
    std::vector<std::byte> mPerBatchBuffer;
    std::vector<std::byte> mPerInstanceBuffer;

    std::pmr::monotonic_buffer_resource mPoolMonotonic;
    std::pmr::monotonic_buffer_resource mMonotonic;
    std::pmr::monotonic_buffer_resource mPerFrame;
    std::pmr::monotonic_buffer_resource mPerPass;
    std::pmr::monotonic_buffer_resource mPerBatch;
    std::pmr::monotonic_buffer_resource mPerInstance;

    std::pmr::synchronized_pool_resource mPool;

    std::unique_ptr<Asset::AssetFactory> mAssetManager;
    std::unique_ptr<Graphics::Render::Engine> mEngine;

    int mCmd = 0;
    Map<std::string, uint32_t> mWindows;
};

}
