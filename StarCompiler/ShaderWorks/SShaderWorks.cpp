// Copyright (C) 2019 star.engine at outlook dot com
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

#include "SShaderWorks.h"
#include "SHLSLGenerator.h"
#include <StarCompiler/ShaderGraph/SShaderAttribute.h>
#include <StarCompiler/SMathNames.h>
#include <StarCompiler/Graphics/SRenderNames.h>
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include <Star/SBitwise.h>

namespace Star::Graphics::Render::Shader {

ShaderGroup& ShaderWorks::getGroup(std::string_view bundleName, std::string_view pipelineName, std::string_view passName) {
    auto& bundle = at(mBundles, bundleName);
    auto& pipeline = at(bundle.mPipelines, pipelineName);
    auto& pass = at(pipeline.mGroups[UpdateEnum::PerPass], passName);
    return pass;
}

ShaderProgram& ShaderWorks::createProgram(std::string_view shaderName) {
    auto res = mPrograms.emplace(std::pair{ str(shaderName), ShaderProgram{ str(shaderName) } });
    if (!res.second) {
        throw std::invalid_argument("Shader: " + str(shaderName) + " already exists");
    }
    return res.first->second;
}

void ShaderWorks::bindProgram(std::string_view shaderName,
    std::string_view bundleName, std::string_view pipelineName, std::string_view passName
) {
    auto& program = at(mPrograms, shaderName);
    auto& group = getGroup(bundleName, pipelineName, passName);
    auto res = group.mPrograms.try_emplace(str(shaderName), std::pair{ &program, RootSignature{} });
    if (!res.second) {
        throw std::invalid_argument("Shader: " + str(shaderName) + " already exists in group: " + str(passName));
    }
}

ShaderGraph ShaderWorks::createModuleGroup(const std::vector<std::string>& names, ShaderStageType stage) const {
    ShaderGraph graph;
    for (const auto& name : names) {
        const auto& m = at(mModules, name);
        graph.createNode(m, stage);
    }
    graph.validateNodes(false);
    return graph;
}

void ShaderWorks::buildRootSignatures(UpdateEnum frequency) {
    // collect shader usages
    for (auto& [bundleName, bundle] : mBundles) {
        for (auto& [pipelineName, pipeline] : bundle.mPipelines) {
            for (uint32_t i = 0; i != UpdateEnum::UpdateCount; ++i) {
                for (auto& [name, group] : pipeline.mGroups[i]) {
                    group.buildConstantBuffers(mAttributes);
                    group.collectConstantBuffers();
                    group.collectDescriptors(mAttributes);
                }
            }
        }
    }
}

void ShaderWorks::outputShaders() const {
    auto outputConstantBuffer = [](const DescriptorIndex& index, const ShaderConstantBuffer& cb) {
        {
            CONSOLE_COLOR(Cyan);
            std::cout << "ConstantBuffer[" << getName(index.mUpdate) << "]: ";
        }
        int count = 0;
        for (const auto& attr : cb.mValues) {
            if (count++)
                std::cout << ", ";
            std::cout << getName(attr.mType) << " " << attr.mName;
        }
        std::cout << std::endl;
    };

    auto outputRootSignature = [](const std::map<DescriptorIndex, DescriptorTable>& tables) {
        for (const auto& [index, table] : tables) {
            {
                CONSOLE_COLOR(Cyan);
                std::cout << getVariantName(index.mType);
            }
            std::cout << ": " << getName(index.mUpdate) << "[" << getName(index.mVisibility) << "]";
            auto prev = DescriptorType{};
            int count = 0;
            for (const auto& d : table.mDescriptors) {
                if (count) {
                    if (prev != d.mType) {
                        CONSOLE_COLOR(Magenta);
                        std::cout << getVariantName(d.mType) << ": ";
                    }
                    prev = d.mType;
                } else {
                    CONSOLE_COLOR(Magenta);
                    std::cout << getVariantName(d.mType) << ": ";
                    prev = d.mType;
                }
                if (count) {
                    std::cout << ", ";
                }
                std::cout << getVariantName(d.mModel) << " " << d.mName;
                visit(overload(
                    [&](const auto& d) {
                        if (std::holds_alternative<DescriptorRange>(d)) {
                            visit(overload(
                                [&](const RangeBounded& v) {
                                    std::cout << "(" << v.mCount << ")";
                                },
                                [&](RangeUnbounded) {
                                    std::cout << "(unbounded)";
                                }
                            ), std::get<DescriptorRange>(d));
                        }
                    }
                ), d.mModel);
                if (d.mSpace)
                    std::cout << d.mSpace;
                ++count;
            }
            std::cout << "\n";
        }
    };

    for (const auto& [bundleName, bundle] : mBundles) {
        std::cout << "Bundle: " << bundleName << std::endl;
        for (const auto& [pipelineName, pipeline] : bundle.mPipelines) {
            Expects(pipeline.mGroups[PerFrame].size() == 1);
            const auto& group = pipeline.mGroups[PerFrame].begin()->second;
            std::cout << "Pipeline: " << pipelineName << std::endl;
            for (const auto& [index, cb] : group.mRootSignature.mConstantBuffers) {
                outputConstantBuffer(index, cb);
            }
            outputRootSignature(group.mRootSignature.mTables);
            for (const auto& [name, group] : pipeline.mGroups[PerPass]) {
                std::cout << "RenderSubPass: " << name << std::endl;
                for (const auto& [index, cb] : group.mRootSignature.mConstantBuffers) {
                    if (index.mUpdate == PerPass) {
                        outputConstantBuffer(index, cb);
                    }
                }
                outputRootSignature(group.mRootSignature.mTables);
                std::cout << std::endl;
                for (const auto& [name, pair] : group.mPrograms) {
                    const auto& [program, rsg] = pair;
                    HLSLGenerator hlsl(*program);

                    std::cout << "Program: " << name << std::endl;
                    for (const auto& [index, cb] : rsg.mConstantBuffers) {
                        if (index.mUpdate < PerPass) {
                            outputConstantBuffer(index, cb);
                        }
                    }
                    outputRootSignature(rsg.mTables);
                    std::cout << hlsl.generateModules() << std::endl;
                    for (const auto& [stage, shader] : hlsl.mProgram.mShaders) {
                        std::cout << hlsl.generateShader(stage) << std::flush;
                    }
                }
            }
        }
    }
}

void ShaderWorks::outputRootSignatures() const {
    for (const auto& [bundleName, bundle] : mBundles) {
        for (const auto& [pipelineName, pipeline] : bundle.mPipelines) {
            Expects(pipeline.mGroups[PerFrame].size() == 1);
            for (const auto& [name, group] : pipeline.mGroups[PerFrame]) {
                std::cout << "Pipeline: " << pipelineName << std::endl;
                if (group.mGenerateRootSignature) {
                    std::cout << group.generateRootSignature();
                }
                for (const auto& [name, pGroup] : group.mGroups) {
                    const auto& group = *pGroup;
                    std::cout << "RenderSubPass: " << name << std::endl;
                    if (group.mGenerateRootSignature) {
                        std::cout << group.generateRootSignature();
                    }
                }
            }
        }
    }
}

void ShaderWorks::saveShaders(const std::filesystem::path& folder) const {
    if (!exists(folder)) {
        create_directories(folder);
    }

    std::string filename;
    filename.reserve(500);
    for (const auto& [bundleName, bundle] : mBundles) {
        for (const auto& [pipelineName, pipeline] : bundle.mPipelines) {
            for (uint i = 0; i != UpdateCount; ++i) {
                for (const auto&[name, group] : pipeline.mGroups[i]) {
                    filename += camelToUnderscore(name);

                    if (group.mGenerateRootSignature) {
                        filename = camelToUnderscore(bundleName) + "-";
                        group.getShaderPrefix(filename);
                        filename += "-rs.hlsl";
                        auto content = group.generateRootSignature();
                        updateFile(folder / filename, content);
                    }

                    if (!group.mPrograms.empty()) {
                        filename = camelToUnderscore(bundleName) + "-";
                        group.getShaderPrefix(filename);
                    }

                    for (const auto& [name, pair] : group.mPrograms) {
                        const auto& [pProgram, rsg] = pair;
                        auto filename2 = filename + "-" + camelToUnderscore(name);

                        HLSLGenerator hlsl(*pProgram);
                        for (const auto& [stage, shader] : pProgram->mShaders) {
                            std::ostringstream oss;
                            std::string space;
                            oss << hlsl.generateAttributes(mAttributes, stage, group.getRootSignatureShaderGroup(), rsg);
                            if (!oss.str().empty())
                                oss << "\n";
                            oss << hlsl.generateModules();
                            //if (!oss.str().empty())
                            //    oss << "\n";
                            oss << hlsl.generateShader(stage);

                            visit(overload(
                                [&](PS_) {
                                    updateFile(folder / (filename2 + "-ps.hlsl"), oss.str());
                                },
                                [&](GS_) {
                                    updateFile(folder / (filename2 + "-gs.hlsl"), oss.str());
                                },
                                [&](DS_) {
                                    updateFile(folder / (filename2 + "-ds.hlsl"), oss.str());
                                },
                                [&](HS_) {
                                    updateFile(folder / (filename2 + "-hs.hlsl"), oss.str());
                                },
                                [&](VS_) {
                                    updateFile(folder / (filename2 + "-vs.hlsl"), oss.str());
                                },
                                [](auto) {}
                            ), stage);
                        }
                    }
                }
            }
        }
    }
}

}
