// Copyright (C) 2019 star.engine@outlook.com
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
#include <Star/Graphics/SConfig.h>
#include <Star/Graphics/SRenderFormat.h>

namespace Star::Graphics::Render {

STAR_GRAPHICS_API bool isTypeless(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypeless(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessUNorm(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessSNorm(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessUScaled(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessSScaled(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessUInt(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessSInt(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessSRGB(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessXRBias(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessUFloat(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessSFloat(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessDouble(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessDepthStencil(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessDepthOnly(Format format) noexcept;
STAR_GRAPHICS_API Format makeTypelessStencilOnly(Format format) noexcept;

STAR_GRAPHICS_API bool supportSRGB(Format format) noexcept;
STAR_GRAPHICS_API bool isSRGB(Format format) noexcept;
STAR_GRAPHICS_API Format makeUNormSRGB(Format format) noexcept;

}
