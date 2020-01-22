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
#include <Star/SSerializationUtils.h>
#include <Star/Graphics/SRenderTypes.h>

namespace boost {

namespace serialization {

STAR_SERIALIZE_BINARY(Star::Graphics::Render::VIEWPORT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RECT);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::CLEAR_VALUE);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RESOURCE_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RENDER_TARGET_VIEW_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_VIEW_DESC);

// pso
STAR_SERIALIZE_BINARY(Star::Graphics::Render::BLEND_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::RASTERIZER_DESC);
STAR_SERIALIZE_BINARY(Star::Graphics::Render::DEPTH_STENCIL_DESC);

STAR_SERIALIZATION_SPLIT_FREE(Star::Graphics::Render::GRAPHICS_PIPELINE_STATE_DESC);
template<class Archive>
void save(Archive& ar, const Star::Graphics::Render::GRAPHICS_PIPELINE_STATE_DESC& v, const uint32_t version) {
    ar << v.mBlendState;
    ar << v.mRasterizerState;
    ar << v.mDepthStencilState;
}

template<class Archive>
void load(Archive& ar, Star::Graphics::Render::GRAPHICS_PIPELINE_STATE_DESC& v, const uint32_t version) {
    ar >> v.mBlendState;
    ar >> v.mRasterizerState;
    ar >> v.mDepthStencilState;
}

}

}
