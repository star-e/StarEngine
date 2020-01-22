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

#include "SShaderCompiler.h"

// msvc
#include <D3Dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

// Star
#include <Star/SWinRT.h>

namespace Star::Graphics::Render::Shader {

void compileShader(std::pmr::string& buffer, const std::string& target,
    const std::string& name, const std::string& content
) {
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3DCOMPILE_DEBUG;
#endif

    com_ptr<ID3DBlob> shaderBlob;
    com_ptr<ID3DBlob> errorBlob;

    HRESULT hr = S_OK;

    hr = D3DCompile(content.data(), content.size(), name.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", target.c_str(),
        flags, 0, shaderBlob.put(), errorBlob.put());

    if (FAILED(hr)) {
        std::cout << "compile shader: " << name << " failed, " <<
            std::string_view(static_cast<const char*>(errorBlob->GetBufferPointer()),
                errorBlob->GetBufferSize()) << std::endl;
        return;
    }

    buffer.resize(shaderBlob->GetBufferSize());
    std::memcpy(buffer.data(), shaderBlob->GetBufferPointer(), buffer.size());
}

void compileShaderFile(const std::filesystem::path& filename, const std::string& target,
    const std::string& name, const std::string& content
) {
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3DCOMPILE_DEBUG;
#endif

    com_ptr<ID3DBlob> shaderBlob;
    com_ptr<ID3DBlob> errorBlob;

    HRESULT hr = S_OK;

    hr = D3DCompile(content.data(), content.size(), name.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", target.c_str(),
        flags, 0, shaderBlob.put(), errorBlob.put());

    if (FAILED(hr)) {
        std::cout << "compile shader: " << name << " failed, " <<
            std::string_view(static_cast<const char*>(errorBlob->GetBufferPointer()),
                errorBlob->GetBufferSize()) << std::endl;
        return;
    }


    if (exists(filename)) {
        com_ptr<ID3DBlob> origShaderBlob;
        ThrowIfFailed(D3DReadFileToBlob(filename.wstring().c_str(), origShaderBlob.put()));
        if (std::string_view(static_cast<const char*>(origShaderBlob->GetBufferPointer()),
            origShaderBlob->GetBufferSize()) !=
            std::string_view(static_cast<const char*>(shaderBlob->GetBufferPointer()),
                shaderBlob->GetBufferSize()))
        {
            ThrowIfFailed(D3DWriteBlobToFile(shaderBlob.get(), filename.wstring().c_str(), true));
        }
    } else {
        ThrowIfFailed(D3DWriteBlobToFile(shaderBlob.get(), filename.wstring().c_str(), true));
    }
}

void compileShaders(const ShaderGroups& shaderWorks,
    const std::filesystem::path& folder, const std::filesystem::path& binaryFolder
) {
    if (!exists(binaryFolder)) {
        create_directories(binaryFolder);
    }
    std::string filename;
    std::string filename2;
    filename.reserve(500);
    filename2.reserve(500);
    for (const auto& [bundleName, bundle] : shaderWorks.mSolutions) {
        for (const auto& [pipelineName, pipeline] : bundle) {
            for (uint i = 0; i != UpdateCount; ++i) {
                for (const auto& [name, group] : pipeline[i]) {
                    filename += camelToUnderscore(name);
                    if (group.mGenerateRootSignature) {
                        filename = camelToUnderscore(bundleName) + "-";
                        group.getShaderPrefix(filename);

                        filename += "-rs";
                        auto content = readFile(folder / (filename + ".hlsl"));
                        compileShaderFile(binaryFolder / (filename + ".cso"), "rootsig_1_1", filename, content);
                    }

                    for (const auto& [name, pair] : group.mPrograms) {
                        const auto& [pProgram, rsg] = pair;
                        filename = camelToUnderscore(bundleName) + "-";
                        group.getShaderPrefix(filename);

                        for (const auto& [stage, shader] : pProgram->mShaders) {
                            auto filename2 = filename + "-" + camelToUnderscore(name);
                            visit(overload(
                                [&](PS_) {
                                    filename2 += "-ps";
                                    auto content = readFile(folder / (filename2 + ".hlsl"));
                                    compileShaderFile(binaryFolder / (filename2 + ".cso"), "ps_5_0", filename2, content);
                                },
                                [&](GS_) {
                                    filename2 += "-gs";
                                    auto content = readFile(folder / (filename2 + ".hlsl"));
                                    compileShaderFile(binaryFolder / (filename2 + ".cso"), "gs_5_0", filename2, content);
                                },
                                [&](DS_) {
                                    filename2 += "-ds";
                                    auto content = readFile(folder / (filename2 + ".hlsl"));
                                    compileShaderFile(binaryFolder / (filename2 + ".cso"), "ds_5_0", filename2, content);
                                },
                                [&](HS_) {
                                    filename2 += "-hs";
                                    auto content = readFile(folder / (filename2 + ".hlsl"));
                                    compileShaderFile(binaryFolder / (filename2 + ".cso"), "hs_5_0", filename2, content);
                                },
                                [&](VS_) {
                                    filename2 += "-vs";
                                    auto content = readFile(folder / (filename2 + ".hlsl"));
                                    compileShaderFile(binaryFolder / (filename2 + ".cso"), "vs_5_0", filename2, content);
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
