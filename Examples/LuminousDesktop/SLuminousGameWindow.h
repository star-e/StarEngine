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
#include "SWinMessages.h"
#include "SWinClass.h"

namespace Star {

class LuminousGameWindow : public WinMessages {
public:
    struct Desc {
        std::string mName;
    };
    using window_class = WinClass<LuminousGameWindow>;
    using param_type = Desc;

    static const wchar_t* class_name();
    static void change_class(WNDCLASSEX& wcex);

    // called during WM_NCCREATE
    LuminousGameWindow(HWND w, LPCREATESTRUCT ptr, Desc* pDesc);

    // called during WM_NCDESTROY
    ~LuminousGameWindow();
private:
    void OnPaint();
    void OnResize();
    void OnPresent();
    void OnKeyDown();
    void OnMovesWhileLButtonDown();
    void OnDoubleClick();

private:
    std::string mName;
    HWND mWindow = {};
    POINTS mPosition = {};
    Graphics::Render::SwapChainContext mContext;
};

}
