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

class WinMessages {
public:
    struct Result {
        LRESULT lres = 0;
        bool handled = false;
    };

    struct Message {
        template<UINT WM>
        static auto is() noexcept {
            return [](Message m) {
                return m.message == WM;
            };
        }

        HWND hWnd;
        UINT message;
        WPARAM wParam;
        LPARAM lParam;
        Result* result;

        void handled() noexcept {
            result->handled = true;
        }
        void lresult(LRESULT lres) noexcept {
            result->lres = lres;
        }

        template<class T>
        T wparam_cast() noexcept {
            return *reinterpret_cast<T*>(std::addressof(wParam));
        }

        template<class T>
        T lparam_cast() noexcept {
            return *reinterpret_cast<T*>(std::addressof(lParam));
        }
    };

    template<class WPARAM_t = WPARAM, class LPARAM_t = LPARAM>
    struct TypedMessage {
        static auto as() noexcept {
            return [](Message m) {
                return TypedMessage{ m };
            };
        }

        TypedMessage(Message m) noexcept
            : hWnd(m.hWnd)
            , message(m.message)
            , wParam(m.wparam_cast<WPARAM_t>())
            , lParam(m.lparam_cast<LPARAM_t>())
            , result(m.result)
        {}

        HWND hWnd;
        UINT message;
        WPARAM_t wParam;
        LPARAM_t lParam;
        Result* result;

        void handled() noexcept {
            result->handled = true;
        }
        void lresult(LRESULT lres) noexcept {
            result->lres = lres;
        }
    };

public:
    WinMessages();
    ~WinMessages();

    std::tuple<bool, LRESULT> message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    rxcpp::observable<Message> messages() {
        return subject.get_observable();
    }

    template<UINT WM>
    rxcpp::observable<Message> messages() {
        return messages().filter(Message::is<WM>());
    }

    template<UINT WM, class WPARAM_t, class LPARAM_t = LPARAM>
    rxcpp::observable<TypedMessage<WPARAM_t, LPARAM_t>> messages() {
        return messages<WM>().map(TypedMessage<WPARAM_t, LPARAM_t>::as());
    }

private:
    rxcpp::subjects::subject<Message> subject;
    rxcpp::subscriber<Message> sub;
};

template<class Derived, UINT WM>
class EnableSendCall {
public:
    static LRESULT send_call(HWND w, std::function<LRESULT(Derived&)> f) {
        auto fp = reinterpret_cast<LPARAM>(std::addressof(f));
        return SendMessage(w, WM, 0, fp);
    }

    EnableSendCall() {
        OnSendCall();
    }

    void OnSendCall() {
        auto derived = static_cast<Derived*>(this);
        derived->messages<WM, WPARAM, std::function<LRESULT(Derived&)>*>().subscribe([=](auto m) {
            m.handled(); // skip DefWindowProc
            m.lresult((*m.lParam)(*derived));
        });
    }
};

}
