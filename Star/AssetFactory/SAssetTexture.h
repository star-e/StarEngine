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
#include <Star/Graphics/SContentTypes.h>
#include <Star/AssetFactory/SAssetTypes.h>

namespace Star::Asset {

void loadPNG(std::istream& is, std::pmr::memory_resource* mr, const TextureImportSettings& settings, Graphics::Render::TextureData& tex);
void loadTGA(std::istream& is, std::pmr::memory_resource* mr, const TextureImportSettings& settings, Graphics::Render::TextureData& tex);

void loadDDS(std::istream& is, std::pmr::memory_resource* mr, Graphics::Render::TextureData& tex, bool bSrgb);
void saveDDS(std::ostream& os, const Graphics::Render::TextureData& tex);

}
