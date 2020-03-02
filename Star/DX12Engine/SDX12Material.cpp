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

#include "SDX12Material.h"

namespace Star::Graphics::Render {

const DX12ShaderQueueData& getSubpassData(const DX12MaterialData& material,
    uint32_t solutionID, uint32_t pipelineID, uint32_t renderPassID, uint32_t renderSubpassID,
    uint32_t& shaderSolutionID, uint32_t& shaderPipelineID, uint32_t& shaderQueueID
) {
    auto solutionIter = material.mShader->mSolutionIndex.find(solutionID);
    if (solutionIter != material.mShader->mSolutionIndex.end()) {
        shaderSolutionID = solutionIter->second;
        const auto& shaderSolution = material.mShader->mSolutions.at(shaderSolutionID);
        auto pipelineIter = shaderSolution.mPipelineIndex.find(pipelineID);
        if (pipelineIter != shaderSolution.mPipelineIndex.end()) {
            shaderPipelineID = pipelineIter->second;
            const auto& shaderPipeline = shaderSolution.mPipelines.at(shaderPipelineID);
            auto queueIter = shaderPipeline.mQueueIndex.find(RenderSubpassDesc{ renderPassID, renderSubpassID });

            if (queueIter != shaderPipeline.mQueueIndex.end()) {
                shaderQueueID = queueIter->second;
                const auto& queue = shaderPipeline.mQueues.at(shaderQueueID);
                return queue;
            }
        }

    }
    throw std::runtime_error("shader queue not found");
}

}
