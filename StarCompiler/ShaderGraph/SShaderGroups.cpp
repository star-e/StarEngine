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

#include "SShaderGroups.h"

namespace Star::Graphics::Render::Shader {

ShaderGroup* ShaderGroups::try_getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) {
    auto bundleIter = mSolutions.find(bundleName);
    if (bundleIter == mSolutions.end())
        return nullptr;
    auto pipelineIter = bundleIter->second.find(pipelineName);
    if (pipelineIter == bundleIter->second.end())
        return nullptr;

    auto passIter = pipelineIter->second.at(UpdateEnum::PerPass).find(passName);
    if (passIter == pipelineIter->second.at(UpdateEnum::PerPass).end())
        return nullptr;
        
    return &passIter->second;
}

ShaderGroup const* ShaderGroups::try_getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) const {
    auto bundleIter = mSolutions.find(bundleName);
    if (bundleIter == mSolutions.end())
        return nullptr;
    auto pipelineIter = bundleIter->second.find(pipelineName);
    if (pipelineIter == bundleIter->second.end())
        return nullptr;

    auto passIter = pipelineIter->second.at(UpdateEnum::PerPass).find(passName);
    if (passIter == pipelineIter->second.at(UpdateEnum::PerPass).end())
        return nullptr;

    return &passIter->second;
}

ShaderGroup& ShaderGroups::getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) {
    auto& bundle = at(mSolutions, bundleName);
    auto& pipeline = at(bundle, pipelineName);
    auto& pass = at(pipeline[UpdateEnum::PerPass], passName);
    return pass;
}

ShaderGroup const& ShaderGroups::getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) const {
    auto& bundle = at(mSolutions, bundleName);
    auto& pipeline = at(bundle, pipelineName);
    auto& pass = at(pipeline[UpdateEnum::PerPass], passName);
    return pass;
}

void ShaderGroups::bindProgram(const ShaderProgram& program, std::string_view shaderName,
    std::string_view bundleName, std::string_view pipelineName, std::string_view passName
) {
    auto* pGroup = try_getGroup(bundleName, pipelineName, passName);
    if (!pGroup)
        return;

    auto& group = getGroup(bundleName, pipelineName, passName);
    Expects(&group == pGroup);

    auto res = group.mPrograms.try_emplace(str(shaderName), std::pair{ &program, RootSignature{} });
    if (!res.second) {
        throw std::invalid_argument("Shader: " + str(shaderName) + " already exists in group: " + str(passName));
    }
}

void ShaderGroups::collectAttributes(const ShaderModules& modules, AttributeDatabase& database) const {
    for (auto& [bundleName, bundle] : mSolutions) {
        for (auto& [pipelineName, pipeline] : bundle) {
            for (uint32_t i = 0; i != UpdateEnum::UpdateCount; ++i) {
                for (auto& [name, group] : pipeline[i]) {
                    group.collectAttributes(modules.mAttributes, database);
                }
            }
        }
    }
}

void ShaderGroups::buildRootSignatures(const ShaderModules& modules, UpdateEnum frequency) {
    // collect shader usages
    for (auto& [bundleName, bundle] : mSolutions) {
        for (auto& [pipelineName, pipeline] : bundle) {
            for (uint32_t i = 0; i != UpdateEnum::UpdateCount; ++i) {
                for (auto& [name, group] : pipeline[i]) {
                    group.buildProgramConstantBuffers(modules.mAttributes);
                    group.collectConstantBuffers();
                    group.collectDescriptors(modules.mAttributes);
                }
            }
        }
    }

    for (auto& [bundleName, bundle] : mSolutions) {
        for (auto& [pipelineName, pipeline] : bundle) {
            for (uint32_t i = 0; i != UpdateEnum::UpdateCount; ++i) {
                for (auto& [name, group] : pipeline[i]) {
                    group.buildRegisters();
                }
            }
        }
    }
}

}
