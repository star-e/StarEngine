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
#include <Star/SMathFwd.h>
#include <StarCompiler/ShaderGraph/SShaderSemantics.h>
#include <StarCompiler/ShaderGraph/SShaderModule.h>
#include <StarCompiler/ShaderGraph/SShaderTypes.h>

namespace Star::Graphics::Render::Shader {

namespace DSL {

//static const matrix identity = matrix::Identity();
//static const matrix zero = matrix::Zero();

static const AttributeDescriptor TypeFrame{ PerFrame, Table, Dynamic, EngineSource };
static const AttributeDescriptor TypePass{ PerPass, Table, Dynamic, EngineSource };
static const AttributeDescriptor TypeInstance{ PerInstance, Table, Dynamic, EngineSource };
static const AttributeDescriptor TypeRenderTarget{ PerPass, Table, Persistent, RenderTargetSource };
static const AttributeDescriptor TypeMaterial{ PerBatch, Table, Persistent, MaterialSource };
static const AttributeDescriptor TypeStaticSampler{ PerFrame, SSV, Persistent, EngineSource };

static const ShaderValue global_state = {};

}

}

//--------------------------------------------------------------------
// Shader Attribute
#define ADD_ATTRIBUTES(...) { \
auto attrs = AttributeMap __VA_ARGS__ ; \
for (auto& attr : attrs) { \
    compileShaderAttribute(const_cast<ShaderAttribute&>(attr)); \
    modules.mAttributes.emplace(attr); \
} \
}

//--------------------------------------------------------------------
// Shader Module
#define ADD_MODULE(NAME, ...) {\
    auto res = modules.mModules.emplace(createShaderModule(BOOST_PP_STRINGIZE(NAME), __VA_ARGS__));\
    if (res.second == false) {\
        throw std::invalid_argument("ShaderModule: " + std::string(BOOST_PP_STRINGIZE(NAME)) + " already exists");\
    }\
}

//--------------------------------------------------------------------
// debug
#define PRINT_DEBUG() { \
CONSOLE_COLOR(Green); \
std::cout << "[succeeded]"; \
} \
std::cout << " shader: " << Shader.mName << ", bundle: " << Bundle.mName << ", pipeline: " << Pipeline.mName << ", level " << Level.mLOD <<  std::endl;

//--------------------------------------------------------------------
// Shader Graph
#define PixelShader(...) for (const ShaderStageType S_Stage = OM; Program.stageBegin(S_Stage, NameMap<ShaderValue>{ __VA_ARGS__ }); Program.stageEnd(S_Stage)); \
for (const ShaderStageType S_Stage = PS; Program.stageBegin(S_Stage); Program.stageEnd(S_Stage))
//#define GeometryShader() for (const ShaderStageType S_Stage = GS; Program.stageBegin(S_Stage); Program.stageEnd(S_Stage))
#define VertexShader() for (const ShaderStageType S_Stage = VS; Program.stageBegin(S_Stage); Program.stageEnd(S_Stage), Program.compile())
//--------------------------------------------------------------------
// Shader Group
#define GROUP_ELEM(r, _, i, NAME) BOOST_PP_COMMA_IF(i) BOOST_PP_STRINGIZE(NAME)
#define GROUP_STAGE(STAGE, ...) { \
    ShaderGraph group; \
    modules.createModuleGroup( \
        { BOOST_PP_SEQ_FOR_EACH_I(GROUP_ELEM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))) }, STAGE, \
        group \
    ); \
    group.fillGraph(Program.mGraph); \
}
#define Group(...) GROUP_STAGE(S_Stage, __VA_ARGS__)

#define Node(NAME, ...) { \
    auto m = createShaderModule(BOOST_PP_STRINGIZE(NAME), __VA_ARGS__); \
    ShaderGraph group; \
    group.createNode(m, S_Stage); \
    group.validateNodes(false); \
    group.fillGraph(Program.mGraph); \
}

//--------------------------------------------------------------------
// Shader Prototype
#define S_MAKE_CONST(NAME) if (const auto& NAME##0 = NAME; true) if (const auto& NAME = NAME##0; true)

#define Shader(NAME, ...) std::cout << "compile shader: " << NAME << std::endl; if (auto& Shader = db.mPrototypes.try_emplace(NAME, ShaderPrototype{ NAME, __VA_ARGS__ }).first->second; true)
#define Bundle(NAME) if (auto& Bundle = Shader.mSolutions.try_emplace(NAME, ShaderSolution{ NAME }).first->second; true) S_MAKE_CONST(Shader)
#define Pipeline(NAME) if (auto& Pipeline = Bundle.mPipelines.try_emplace(NAME, ShaderPipeline{ NAME }).first->second; true) S_MAKE_CONST(Bundle)
#define Queue(NAME) if (auto& Queue = Pipeline.mQueues.try_emplace(NAME, ShaderQueue{ NAME }).first->second; true) S_MAKE_CONST(Pipeline)
#define Level(...) if (auto& Level = *Queue.mLevels.insert(Queue.mLevels.end(), ShaderLevel{ __VA_ARGS__ }); true) S_MAKE_CONST(Queue)
#define Subpass(...) if (auto& Subpass = *Level.mPasses[{ __VA_ARGS__ }].insert(Level.mPasses[{ __VA_ARGS__ }].end(), ShaderPass{ __VA_ARGS__ }); true) S_MAKE_CONST(Level)
#define Program(...) if (auto& Program = Subpass.mProgram; true) S_MAKE_CONST(Subpass)

#define SinglePass(BUNDLE, PIPELINE, QUEUE, LEVEL, ...) \
Bundle(BUNDLE) Pipeline(PIPELINE) Queue(QUEUE) Level(LEVEL) Subpass(__VA_ARGS__) if (auto& Pass = Subpass; true) Program()

// Unity
#define UnityVertex(VERTEX_INPUT) \
switch(VERTEX_INPUT) { \
case Unity::AppData::Full: { \
Group(SUnityUnpackTexcoord, SUnityUnpackTexcoord1, SUnityUnpackTexcoord2, SUnityUnpackTexcoord3); \
} break; \
default: { \
Group(SUnityUnpackTexcoord); \
} break; \
}

#define SubShader(...) Bundle("Unity") Pipeline("Default") Queue({ __VA_ARGS__ }) Level() if (auto& SubShader = Level; true)
#define Pass(...) Subpass({ __VA_ARGS__ }) if (auto& Pass = Subpass; true) S_MAKE_CONST(SubShader)

#define BUILD(NAME, PATH) { \
auto content = UnityShaderBuilder().generateShader(modules.mAttributes, db.mPrototypes.at(NAME)); \
updateFile(PATH, content); \
}
