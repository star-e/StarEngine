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

namespace Star {

class DesktopSystem {
public:
    DesktopSystem();
    DesktopSystem(const DesktopSystem&) = delete;
    DesktopSystem& operator=(const DesktopSystem&) = delete;
    ~DesktopSystem();
};

class DesktopApp : DesktopSystem {
public:
    struct Desc {
        uint32_t mNumTaskThreads = 12;
        uint32_t mMaxTaskCount = 8;
        uint32_t mMaxResourceCount = 2048;
    };
    DesktopApp(HINSTANCE hInstance, const Desc& desc);
    DesktopApp(const DesktopApp&) = delete;
    DesktopApp& operator=(const DesktopApp&) = delete;
    ~DesktopApp();

    bool try_spawnWindow(uint32_t width, uint32_t height, int nCmdShow,
        std::wstring windowClass, std::wstring title, std::string name, const void* param);

    void run();
protected:
    virtual void start() = 0;
    virtual void stop() noexcept = 0;

    HINSTANCE mInstance = {};

    std::vector<std::thread> mTaskThreads;
    Map<std::string, std::thread> mWindowThreads;

    boost::asio::io_context mTaskService;
    boost::asio::io_context mRenderService;

    boost::asio::io_context::strand mTaskStrand;
    boost::asio::io_context::strand mRenderStrand;

    std::shared_ptr<boost::asio::io_context::work> mTaskWork;
    std::shared_ptr<boost::asio::io_context::work> mRenderWork;
    std::weak_ptr<boost::asio::io_context::work> mRenderWorkObserver;
};

}
