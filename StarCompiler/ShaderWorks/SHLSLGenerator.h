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

#pragma once
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderProgram.h>

namespace Star::Graphics::Render::Shader {

class ShaderGroup;

class HLSLGenerator {
public:
    HLSLGenerator(const ShaderProgram& program, Language l = HLSL);
    HLSLGenerator(const HLSLGenerator&) = delete;
    HLSLGenerator& operator=(const HLSLGenerator&) = delete;

    std::string generateShader(const ShaderStageType& stage) const;

    std::string generateModules() const;
    std::string generateAttributes(const AttributeMap& attrs,
        const ShaderStageType& stage, const ShaderGroup& group, const RootSignature& rsg) const;
    std::string generateInput(const ShaderStageType& stage) const;
    std::string generateOutput(const ShaderStageType& stage) const;
    std::string generateMain(const ShaderStageType& stage) const;
private:
    // helpers
    std::string renameAttributes(const ShaderModule& node) const;
    std::string generateModule(const ShaderModule& node) const;
    std::string_view getContent(const ShaderModule& node) const;

    // main body generator
    std::string generateMainSignature(const ShaderStage& shader, std::set<std::string>& locals) const;
    std::string generateMainSignatureByParameters(const ShaderStage& shader, std::set<std::string>& locals) const;
    std::string generateInputCopy(const ShaderStage& shader, std::set<std::string>& locals) const;
    std::string generateModuleExec(const ShaderModule& node, std::set<std::string>& locals) const;
    std::string generateOutputCopy(const ShaderStage& shader) const;
    std::string generateMainReturn(const ShaderStage& shader) const;
public:
    const ShaderProgram& mProgram;
    std::string mAttributeRegex = "m$1";
    std::string mAttributeInstancingRegex = "m$1";
    std::map<ShaderStageType, ShaderStageContent> mNamings;
    std::map<ShaderStageType, IdentityMap<ShaderSemanticValue>> mInputs;
    std::map<ShaderStageType, IdentityMap<ShaderSemanticValue>> mOutputs;
    Language mLanguage;
    bool mDebug = true;
};

}
