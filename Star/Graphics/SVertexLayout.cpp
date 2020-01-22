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

// Copyright (C) 2015-2017 Zhou Zhenglong <zlzhou.sh@outlook.com>
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "SVertexLayout.h"

namespace Star {

namespace Graphics {

static_assert(sizeof(VertexElement) == sizeof(int32_t) * 2, "sizeof VertexElement must be 8 bytes");
static_assert(std::is_standard_layout<VertexElement>::value, "VertexElement must be standard layout");
//static_assert(std::is_standard_layout<VertexLayout>::value, "VertexLayout must be standard layout");
static_assert(sizeof(VertexLayout) == sizeof(VertexElement) * 16, "VertexLayout size incorrect");

}

}
