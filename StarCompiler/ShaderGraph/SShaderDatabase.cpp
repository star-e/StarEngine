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

#include "SShaderDatabase.h"

namespace Star::Graphics::Render::Shader {

void ShaderDatabase::fillShaderGroups(ShaderGroups& sg) const {
    for (const auto& [prototypeName, prototype] : mPrototypes) {
        for (const auto& [bundleName, bundle] : prototype.mSolutions) {
            for (const auto& [pipelineName, pipeline] : bundle.mPipelines) {
                for (const auto& [queueName, queue] : pipeline.mQueues) {
                    for (const auto& level : queue.mLevels) {
                        for (const auto& [passName, pass] : level.mPasses) {
                            size_t k = 0;
                            for (const auto& subpass : pass) {
                                auto shaderName = std::to_string(k++) + "/";
                                if (passName.empty())
                                    shaderName += "@";
                                else
                                    shaderName += passName;
                                shaderName = shaderName + "/" + prototypeName;
                                sg.bindProgram(subpass.mProgram, shaderName, bundleName, pipelineName, queueName);
                                ++k;
                            } // subpass
                        } // pass
                    } // level
                } // queue
            } // pipeline
        } // bundle
    } // prototype
}

}
