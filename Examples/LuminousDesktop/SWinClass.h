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

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

inline HINSTANCE GetCurrentInstance() {
    return ((HINSTANCE)&__ImageBase);
}

template<typename Type>
LRESULT CALLBACK WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

template<typename Type>
class WinClass {
public:
    static LPCWSTR Name() {
        return Type::class_name();
    }

    static ATOM Register() {
        WNDCLASSEX wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);

        // defaults that can be overriden
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.hInstance = GetCurrentInstance();
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wcex.style         = 0;
        wcex.hIcon         = NULL;
        wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wcex.lpszMenuName  = NULL;

        Type::change_class(wcex);

        // not overridable
        wcex.lpszClassName = Name();
        wcex.lpfnWndProc = WindowCallback<Type>;

        return RegisterClassEx(&wcex);
    }

    WinClass() = delete;
    WinClass(const WinClass&) = delete;
    WinClass& operator=(const WinClass&) = delete;
    ~WinClass() = delete;
};

namespace Windows {

template<typename Type>
std::unique_ptr<Type> find(HWND hwnd) {
    return std::unique_ptr<Type>(reinterpret_cast<Type*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)));
}

inline void erase(HWND hwnd) {
    SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
}

template<typename Type>
std::unique_ptr<Type> insert(HWND hwnd, std::unique_ptr<Type> type) {
    if (!type) {
        return nullptr;
    }

    SetLastError(0);

    ON_SCOPE_EXIT(unwind_userdata, [&]() {
        erase(hwnd);
    });

    auto result = SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(type.get()));

    LONG winerror = !result ? GetLastError() : ERROR_SUCCESS;

    if (!!winerror || !!result) {
        return nullptr;
    }

    unwind_userdata.dismiss();
    return type;
}

}

template<typename Type>
LRESULT CALLBACK WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept {
    auto type = Windows::find<Type>(hWnd);
    // don't delete type
    ON_SCOPE_EXIT(unwind_type, [&](){
        type.release();
    });

    if (message == WM_NCCREATE) {
        if  (type) {
            // the slot where we would store our type instance is full. abort.
            return FALSE;
        }
        auto cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        auto param = reinterpret_cast<typename Type::param_type*>(cs->lpCreateParams);
        type = Windows::insert(hWnd, std::unique_ptr<Type>(new (std::nothrow) Type(hWnd, cs, param)));
        if (!type) {
            return FALSE;
        }
    }

    LRESULT lResult = 0;
    bool handled = false;

    if (type) {
        std::tie(handled, lResult) = type->message(hWnd, message, wParam, lParam);
    }

    if (!handled) {
        lResult = DefWindowProc(hWnd, message, wParam, lParam);
    }

    if (message == WM_NCDESTROY) {
        Windows::erase(hWnd);
        // let type destruct
        unwind_type.dismiss();
    }

    return lResult;
}

}
