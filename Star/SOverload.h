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

template<class ...Fs> struct overload_set;

template<class F1, class... Fs>
struct overload_set<F1, Fs...> : F1, overload_set<Fs...>::type {
    using type = overload_set;

    overload_set(F1 head, Fs... tail)
        : F1(head), overload_set<Fs...>::type(tail...)
    { }

    using F1::operator();
    using overload_set<Fs...>::type::operator();
};

template<class F>
struct overload_set<F>: F {
    using type = F;
    using F::operator();
};

template<class... Fs>
struct overload_visitor : overload_set<Fs...>::type {
    using type = overload_visitor;
    using overload_set<Fs...>::type::operator();

    overload_visitor(Fs... funcs)
        : overload_set<Fs...>::type(funcs...) {
    }
};

template<class... Fs>
const typename overload_visitor<Fs...>::type overload(Fs... x) {
    return overload_visitor<Fs...>(x...);
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}
