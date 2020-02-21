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
#include <Star/Graphics/SConfig.h>
#include <Star/Graphics/SContentTypes.h>

namespace Star::Graphics::Render {

STAR_GRAPHICS_API void resize(FlattenedObjects& batch, size_t sz);
STAR_GRAPHICS_API void reserve(FlattenedObjects& batch, size_t sz);

template<class Visitor>
void visitContent(const RenderSwapChain& sc, const Visitor& visitor) {
    for (const auto& solution : sc.mSolutions) {
        for (const auto& pipeline : solution.mPipelines) {
            for (const auto& pass : pipeline.mPasses) {
                for (const auto& subpass : pass.mSubpasses) {
                    for (const auto& queue : subpass.mOrderedRenderQueue) {
                        for (const auto& task : queue.mContents) {
                            visitor(task);
                        }
                    }
                }
            }
        }
    }
}

template<class Visitor>
void visitShaderSubpassData(const ShaderData& sc, const Visitor& visitor) {
    for (const auto& [solutionName, solution] : sc.mSolutions) {
        for (const auto& [pipelineName, pipeline] : solution.mPipelines) {
            for (const auto& [queueName, queue] : pipeline.mQueues) {
                for (const auto& level : queue.mLevels) {
                    for (const auto& [variantName, variant] : level.mPasses) {
                        for (const auto& pass : variant.mSubpasses) {
                            visitor(pass);
                        }
                    }
                }
            }
        }
    }
}

template<class Visitor>
void visitShaderSubpassData(ShaderData& sc, const Visitor& visitor) {
    for (auto&& [solutionName, solution] : sc.mSolutions) {
        for (auto&& [pipelineName, pipeline] : solution.mPipelines) {
            for (auto&& [queueName, queue] : pipeline.mQueues) {
                for (auto&& level : queue.mLevels) {
                    for (auto&& [variantName, variant] : level.mPasses) {
                        for (auto&& pass : variant.mSubpasses) {
                            visitor(pass);
                        }
                    }
                }
            }
        }
    }
}

inline std::pair<const void*, uint32_t> getConstant(const ConstantMap& map, uint32_t key) {
    auto desc = map.mIndex.at(key);
    auto* pSrc = map.mBuffer.data() + desc.mOffset;
    return std::pair{ pSrc, desc.mSize };
}

}
