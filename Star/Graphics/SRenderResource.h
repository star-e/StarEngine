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
#include <Star/Core/SCoreTypes.h>
#include <Star/Graphics/SContentFwd.h>

namespace Star::Graphics::Render {

constexpr Core::ResourceType getTag(const MeshData* data) noexcept {
    return Core::Mesh;
}

constexpr Core::ResourceType getTag(const TextureData* data) noexcept {
    return Core::Texture;
}

constexpr Core::ResourceType getTag(const ShaderData* data) noexcept {
    return Core::Shader;
}

constexpr Core::ResourceType getTag(const MaterialData* data) noexcept {
    return Core::Material;
}

constexpr Core::ResourceType getTag(const ContentData* data) noexcept {
    return Core::Content;
}

constexpr Core::ResourceType getTag(const RenderGraphData* data) noexcept {
    return Core::RenderGraph;
}

}
