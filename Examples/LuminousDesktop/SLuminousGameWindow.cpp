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

#include "SLuminousGameWindow.h"
#include "SLuminousApp.h"
#include <Star/Graphics/SWindowMessages.h>

namespace Star {

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;
using namespace std::chrono_literals;

const wchar_t* LuminousGameWindow::class_name() {
    return L"Star.Luminous.GameWindow";
}

void LuminousGameWindow::change_class(WNDCLASSEX& wcex) {
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    //wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    //wcex.hInstance = hInstance;
    //wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_IRONYPLAYER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    //wcex.lpszClassName = className;
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
}

LuminousGameWindow::LuminousGameWindow(HWND w, LPCREATESTRUCT, Desc* pDesc)
    : mName(pDesc ? pDesc->mName : "Star.Luminous.GameWindow")
    , mWindow(w)
    , mPosition{ 40, 10 }
    , mContext{ mName.c_str(), w }
{
    std::unique_ptr<Desc> ptr(pDesc);
    std::ignore = ptr;

    OnPaint();
    OnResize();
    OnPresent();
    OnKeyDown();
    OnMovesWhileLButtonDown();
    OnDoubleClick();

    LuminousDesktop::instance().startWindow(mName, w);
}

LuminousGameWindow::~LuminousGameWindow() {
    LuminousDesktop::instance().stopWindow(mName);
    PostQuitMessage(0);
}

void LuminousGameWindow::OnPaint() {
    messages<WM_PAINT>(). 
        subscribe([this](auto m) {
            m.handled(); // skip DefWindowProc

            PAINTSTRUCT ps;
            BeginPaint(mWindow, &ps);
            EndPaint(mWindow, &ps);
        });
}

void LuminousGameWindow::OnResize() {
    auto ob = messages<WM_SIZE, int64_t>() |
        map([this](auto m) {
            m.handled();
            return m;
        }) |
        debounce(std::chrono::milliseconds(10), observe_on_new_thread());

    ob.subscribe([this](auto m) {
        mContext.mWidth = LOWORD(m.lParam);
        mContext.mHeight = HIWORD(m.lParam);
        if (mContext.mWidth && mContext.mHeight) {
            LuminousDesktop::instance().resizeWindow(mContext);
        }
        S_INFO << "debounced resize: " << "w: " << mContext.mWidth << ", h: " << mContext.mHeight;
    });
}

void LuminousGameWindow::OnPresent() {
    messages<Graphics::Render::WM_STAR_RENDER>(). 
        subscribe([this](auto m) {
            m.handled(); // skip DefWindowProc
            LuminousDesktop::instance().renderWindow(mName);
        });
}

void LuminousGameWindow::OnKeyDown() {
    messages<WM_KEYDOWN>().
        subscribe([this](auto m) {
            m.handled();

            //MessageBox(window, L"KeyDown", L"LuminousGameWindow", MB_OK);
            // NOTE: MessageBox pumps messages, but this subscription only
            // receives messages if it is suspended by 'for await', so any
            // WM_KEYDOWN arriving while the message box is up is not delivered.
            // the other subscriptions will receive messages.
        });
}

void LuminousGameWindow::OnMovesWhileLButtonDown() {
    auto moves_while_lbutton_down = messages<WM_LBUTTONDOWN>().
        map([this](auto m) {
            m.handled();
            return this->messages<WM_MOUSEMOVE>().
                take_until(this->messages<WM_LBUTTONUP>());
        }).
        merge();

    moves_while_lbutton_down.
        subscribe([this](auto m) {
            Expects(m.message == WM_MOUSEMOVE);
            m.handled();            
            //position = MAKEPOINTS(m.lParam);
        });

    moves_while_lbutton_down.
        debounce(std::chrono::milliseconds(100), observe_on_new_thread()).
        subscribe([this](auto m) {
            std::ignore = m;
            S_INFO << "drag";
        });
}

void LuminousGameWindow::OnDoubleClick() {
    //messages<WM_ACTIVATE>().subscribe([](auto m) {
    //        if (LOWORD(m.wParam) != 0)
    //            S_INFO << "activate true";
    //        else
    //            S_INFO << "activate false";
    //    });
    //messages<WM_LBUTTONDOWN>().subscribe([](auto m) {
    //        S_INFO << "WM_LBUTTONDOWN";
    //    });
    //messages<WM_LBUTTONUP>().subscribe([](auto m) {
    //        S_INFO << "WM_LBUTTONUP";
    //    });

    auto click = messages<WM_LBUTTONDOWN>().timestamp().
        combine_latest(messages<WM_LBUTTONUP>().timestamp()).
        filter([](auto m) {
            auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::get<1>(m).second - std::get<0>(m).second);

            auto clicked = interval > 0ms && interval < 200ms;
            if (clicked) {
                std::get<0>(m).first.handled();
                std::get<1>(m).first.handled();
            }
            return clicked;
        }).
        map([](auto m) {
            std::ignore = m;
            return 1;
        });

    auto singleClick = click.
        time_interval().
        filter([](auto d) {
            return std::chrono::duration_cast<std::chrono::milliseconds>(d) >= 300ms;
        });

    auto doubleClick = click.
        time_interval().
        filter([](auto d) {
            return std::chrono::duration_cast<std::chrono::milliseconds>(d) < 300ms;
        });

    singleClick.
        subscribe([](auto m) {
            std::ignore = m;
            static int sCount = 0;
            S_INFO << "single click: " << sCount++;
        });

    doubleClick.
        subscribe([](auto m) {
            std::ignore = m;
            static int sCount = 0;
            S_INFO << "double click: " << sCount++;
        });
}

}
