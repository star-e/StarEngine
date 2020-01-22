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
#include <atomic>

namespace Star {

// https://stackoverflow.com/questions/10268737/c11-atomics-and-intrusive-shared-pointer-reference-count

inline bool atomicAddRef(std::atomic_int32_t& v) noexcept {
    return std::atomic_fetch_add_explicit(&v, 1, std::memory_order_relaxed) == 0;
}

inline bool atomicAddRef(volatile std::atomic_int32_t& v) noexcept {
    return std::atomic_fetch_add_explicit(&v, 1, std::memory_order_relaxed) == 0;
}

inline bool atomicDecRef(std::atomic_int32_t& v) noexcept {
    auto res = std::atomic_fetch_sub_explicit(&v, 1, std::memory_order_release);
    Expects(res > 0);
    return res == 1;
}

inline bool atomicDecRef(volatile std::atomic_int32_t& v) noexcept {
    auto res = std::atomic_fetch_sub_explicit(&v, 1, std::memory_order_release);
    Expects(res > 0);
    return res == 1;
}

inline void atomicReleaseFence() noexcept {
    std::atomic_thread_fence(std::memory_order_acquire);
}

}
