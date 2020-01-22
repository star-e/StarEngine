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

#include "SDesktopApp.h"
#include <Star/Core/SManagerFwd.h>

namespace Star {

using namespace winrt;
using namespace winrt::Windows::Foundation;

DesktopSystem::DesktopSystem() {
    // detect memory leak
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    // winrt
    init_apartment();
}

DesktopSystem::~DesktopSystem() = default;

DesktopApp::DesktopApp(HINSTANCE hInstance, const Desc& desc)
    : mInstance(hInstance)
    , mTaskStrand(mTaskService)
    , mRenderStrand(mRenderService)
    , mTaskThreads(desc.mNumTaskThreads)
    , mRenderWork(std::make_shared<boost::asio::io_context::work>(mRenderService))
    , mRenderWorkObserver(mRenderWork)
    , mTaskWork(std::make_shared<boost::asio::io_context::work>(mTaskService))
{
    // text encoding
    if (!checkUnicode())
        throw std::runtime_error("unicode incorrect");

    // logging
    {
        updateLogFolder("log");
        initLogging(boost::log::trivial::debug, ("log/luminous_desktop_" + getDateTimeStr() + ".txt").c_str());

        // start logging
        S_INFO << getDateTimeAscStr();
        S_INFO << "program start";
    }

    // locale
    initLocale("C", true);

    // Core workflow
    Core::Workflow::init(desc.mMaxResourceCount, desc.mMaxTaskCount);
}

DesktopApp::~DesktopApp() {
    Core::Workflow::terminate();
}

bool DesktopApp::try_spawnWindow(uint32_t width, uint32_t height, int nCmdShow,
    std::wstring windowClass, std::wstring title, std::string name, const void* param
) {
    // get render work from observer
    auto renderWork = mRenderWorkObserver.lock();

    if (!renderWork) {
        // render work released, engine has been stopped
        return false;
    }

    // release app render work
    mRenderWork.reset();

    // launch window thread
    auto threadName = name;

    auto res = mWindowThreads.try_emplace(std::move(name));
    if (!res.second) {
        // window thread already exists
        return false;
    }

    res.first->second = std::thread([this, width, height, nCmdShow,
        windowClass = std::move(windowClass), title = std::move(title), threadName = std::move(threadName), param,
        renderWork = std::move(renderWork)
        ]()
    {
        setThreadName(threadName.c_str());

        auto style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
        //auto style = WS_OVERLAPPEDWINDOW;

        RECT rect{ 0, 0, gsl::narrow_cast<int32_t>(width), gsl::narrow_cast<int32_t>(height) };
        AdjustWindowRect(&rect, style, FALSE);

        // normal create window call, just takes the class name and optional create parameters
        LONG winerror = ERROR_SUCCESS;
        auto hWindow = CreateWindow(windowClass.c_str(), title.c_str(), style,
            CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
            NULL, NULL,
            mInstance, const_cast<void*>(param));

        if (!hWindow) {
            winerror = GetLastError();
        }

        if (!!winerror || !hWindow) {
            throw std::runtime_error("create window failed");
        }

        ShowWindow(hWindow, nCmdShow);

        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // erase window thread
        mRenderService.post([this, threadName = std::move(threadName), renderWork = std::move(renderWork)]() {
            auto iter = mWindowThreads.find(threadName);
            if (iter != mWindowThreads.end()) {
                iter->second.join();
                mWindowThreads.erase(iter);
            }
        });
    });

    return true;
}

void DesktopApp::run() {
    // init threads
    {
        std::string name;
        name.reserve(20);
        for (int i = 0; i != mTaskThreads.size(); ++i) {
            mTaskThreads[i] = std::thread([this, i]() {
                mTaskService.run();
                });
            name = "Task thread " + std::to_string(i);
            setThreadName(name.c_str(), mTaskThreads[i]);
        }
    }

    // call derived start
    start();

    // release app renderwork, window should have render work already
    mRenderWork.reset();

    // main engine loop
    mRenderService.run();

    stop();

    // wait for window threads
    for (auto&& [name, thread] : mWindowThreads) {
        thread.join();
    }

    // release task work
    mTaskWork.reset();

    // wait for tasks
    for (auto& thread : mTaskThreads) {
        thread.join();
    }

    // stop core workflow
    Core::Workflow::stop();
}

}
