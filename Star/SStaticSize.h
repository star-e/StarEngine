// Copyright (C) 2019 star.engine at outlook dot com
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

#ifndef NDEBUG
template<int N>
struct print_size_as_warning {
    char operator()() { return N + 256; } //deliberately causing overflow
};

#define PRINT_SIZE(NAME) \
namespace { \
inline void print_size_##NAME() noexcept { \
    ::Star::print_size_as_warning<sizeof(NAME)>()(); \
} \
}

#define PRINT_ALIGN(NAME) \
namespace { \
inline void print_align_##NAME() noexcept { \
    ::Star::print_size_as_warning<alignof(NAME)>()(); \
} \
}

#ifdef _DEBUG
#define CHECK_SIZE(NAME, SIZE) 
#else
#define CHECK_SIZE(NAME, SIZE) static_assert(sizeof(NAME) == SIZE);
#endif

#else

#define PRINT_SIZE(NAME) 
#define CHECK_SIZE(NAME, SIZE) 

#endif

}
