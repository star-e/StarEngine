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
#include <Star/SMultiIndex.h>
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>
#include <StarCompiler/RenderGraph/SRenderValue.h>

namespace Star {

namespace Graphics {

namespace Render {

inline bool equal(const RenderValue& lhs, const RenderValue& rhs) noexcept {
    return std::forward_as_tuple(lhs.mName, lhs.mData)
        == std::forward_as_tuple(rhs.mName, rhs.mData);
}

inline RenderTargetResource rt(std::string name, Format format,
    Width width, Height height, ClearColor color = {},
    ColorSpace space = Linear, RenderTargetType type = std::monostate()
) {
    RenderTargetResource v;
    v.mName = std::move(name);
    v.mResource.mFormat = format;
    v.mResource.mDimension = Resource2D{
        gsl::narrow_cast<uint16_t>(width.mValue),
        gsl::narrow_cast<uint16_t>(height.mValue),
    };
    v.mResource.mMipMap = MipLevels{ 1 };
    v.mClearColor = std::move(color);
    v.mColorSpace = std::move(space);
    v.mType = std::move(type);
    return v;
}

inline RenderTargetResource rt(std::string name, Format format,
    Width width, Height height, ColorSpace space, RenderTargetType type = std::monostate()
) {
    return rt(std::move(name), std::move(format),
        width, height, ClearColor(), std::move(space), std::move(type));
}

inline RenderTargetResource ds(std::string name, Format format,
    Width width, Height height, ClearDepthStencil color = {}
) {
    RenderTargetResource v;
    v.mName = std::move(name);
    v.mResource.mFormat = format;
    v.mResource.mDimension = Resource2D{
        gsl::narrow_cast<uint16_t>(width.mValue),
        gsl::narrow_cast<uint16_t>(height.mValue),
    };
    v.mResource.mMipMap = MipLevels{ 1 };
    v.mClearColor = std::move(color);
    return v;
}

#define NODE(NAME, ...) \
auto NAME = graph.createNode(RenderNode{ BOOST_PP_STRINGIZE(NAME), __VA_ARGS__ })

#define CONNECT(SRC, DST) \
graph.connectNode(SRC, DST)

}

}

}
