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

template<typename Function>
class ScopeExit {
public:
    explicit ScopeExit(Function* functionArg) noexcept
        : function(functionArg)
    {}
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;

    ~ScopeExit() noexcept {
        if (function) {
            (*function)();
        }
    }

    void dismiss() {
        function = nullptr;
    }

    ScopeExit& operator=(std::nullptr_t) {
        dismiss();
        return *this;
    }
private:
    Function* function = nullptr;
};

#define ON_SCOPE_EXIT_EXPLICIT(FunctionName, ScopeExitName, Function) \
	auto FunctionName = (Function); \
	::Star::ScopeExit<decltype(FunctionName)> ScopeExitName(std::addressof(FunctionName))

#define ON_SCOPE_EXIT(Name, Function) \
	ON_SCOPE_EXIT_EXPLICIT(scope_exit_ ## Name, Name, Function)

}
