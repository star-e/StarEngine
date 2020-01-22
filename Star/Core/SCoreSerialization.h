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

namespace boost {

namespace serialization {

STAR_CLASS_IMPLEMENTATION(Star::Core::Mesh_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::Mesh_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::Mesh_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Core::Texture_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::Texture_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::Texture_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Core::Shader_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::Shader_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::Shader_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Core::Material_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::Material_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::Material_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Core::Content_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::Content_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::Content_& v, const uint32_t version) {
}

STAR_CLASS_IMPLEMENTATION(Star::Core::RenderGraph_, object_serializable);
STAR_CLASS_TRACKING(Star::Core::RenderGraph_, track_never);
template<class Archive>
void serialize(Archive& ar, Star::Core::RenderGraph_& v, const uint32_t version) {
}

} // namespace serialization

} // namespace boost
