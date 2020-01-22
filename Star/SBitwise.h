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
#include <cstdint>
#ifdef _MSC_VER
#include <intrin.h>
#endif

#pragma intrinsic(_BitScanForward)
#pragma intrinsic(_BitScanForward64)

namespace Star {
    
// http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
constexpr uint32_t count_bits(uint32_t i) noexcept {
    // Java: use >>> instead of >>
    // C or C++: use uint32_t
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

inline uint32_t count_bits(uint64_t value) noexcept {
    return count_bits(*(reinterpret_cast<const uint32_t*>(&value))) +
        count_bits(*(reinterpret_cast<const uint32_t*>(&value) + 1));
}

constexpr uint32_t log2i(uint32_t x) noexcept {
    Expects(x > 0);
    uint32_t level = 0;
    while (x >>= 1)
        ++level;
    return level;
}

constexpr bool is_pot(uint32_t x) noexcept {
    return (x != 0) && ((x & (x - 1)) == 0);
}

constexpr bool is_pot_ex(uint32_t x) noexcept {
    return (x & (x - 1)) == 0;
}

constexpr uint64_t set_least_n_bits(uint32_t n) noexcept {
    Expects(n <= 64 && n > 0);
    return n == 64 ? uint64_t(-1) : (uint64_t(1) << n) - 1;
}

#ifdef _MSC_VER
inline uint32_t log2i_intrinsic(uint32_t num) noexcept {
    uint32_t index = 0;
    static_assert(sizeof(unsigned long) == sizeof(uint32_t), "unsigned long size not correct");
    /*uint8_t isNonZero = */_BitScanReverse(reinterpret_cast<unsigned long*>(&index), num);
    return index;
}

inline std::pair<uint32_t, bool> find_lsb(uint32_t mask) {
    unsigned long result;
    auto found = _BitScanForward(&result, mask);
    return std::pair(result, found != 0);
}

inline std::pair<uint32_t, bool> find_msb(uint32_t mask) {
    unsigned long result;
    auto found = _BitScanReverse(&result, mask);
    return std::pair(result, found != 0);
}

#ifdef _M_X64

inline std::pair<uint32_t, bool> find_lsb(uint64_t mask) {
    unsigned long result;
    auto found = _BitScanForward64(&result, mask);
    return std::pair(result, found != 0);
}

inline std::pair<uint32_t, bool> find_msb(uint64_t mask) {
    unsigned long result;
    auto found = _BitScanReverse64(&result, mask);
    return std::pair(result, found != 0);
}

#endif

#endif // _MSC_VER

}
