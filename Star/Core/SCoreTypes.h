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
#include <Star/Core/SConfig.h>
#include <Star/Core/SCoreFwd.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Star {

namespace Core {

struct Mesh_ {} static constexpr Mesh;
struct Texture_ {} static constexpr Texture;
struct Shader_ {} static constexpr Shader;
struct Material_ {} static constexpr Material;
struct Content_ {} static constexpr Content;
struct RenderGraph_ {} static constexpr RenderGraph;

using ResourceType = std::variant<Mesh_, Texture_, Shader_, Material_, Content_, RenderGraph_>;

inline bool operator<(const ResourceType& lhs, const ResourceType& rhs) noexcept {
    return lhs.index() < rhs.index();
}

inline bool operator==(const ResourceType& lhs, const ResourceType& rhs) noexcept {
    return lhs.index() == rhs.index();
}

inline bool operator!=(const ResourceType& lhs, const ResourceType& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace Core

} // namespace Star

#ifdef _MSC_VER
#pragma warning(pop)
#endif
