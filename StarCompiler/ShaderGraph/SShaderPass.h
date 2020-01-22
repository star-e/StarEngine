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
#include <StarCompiler/ShaderGraph/SShaderTypes.h>
#include <StarCompiler/ShaderGraph/SShaderProgram.h>

namespace Star::Graphics::Render::Shader {

namespace Unity {

enum class AppData {
    Default,
    Base,
    Tan,
    Full
};

inline const char* getName(AppData data) noexcept {
    switch (data) {
    case AppData::Default: return "appdata";
    case AppData::Base: return "appdata_base";
    case AppData::Tan: return "appdata_tan";
    case AppData::Full: return "appdata_full";
    }
    return "";
}

using Tag = std::pair<std::string, std::string>;
using Tags = std::vector<std::pair<std::string, std::string>>;
struct AlphaToMask_ {} constexpr AlphaToMask;
struct ZWrite {
    bool mEnabled = false;
};
using ZTest = ComparisonFunc;

struct Name {
    std::string mValue;
};

}

class ShaderPass {
public:
    ShaderPass& operator<<(std::pair<std::string, std::string> tag) {
        auto res = mUnityTags.emplace(std::move(tag));
        if (!res.second) {
            throw std::invalid_argument("tag already exists: " + tag.first);
        }
        return *this;
    }

    ShaderPass& operator<<(std::vector<std::pair<std::string, std::string>> tags) {
        for (auto& tag : tags) {
            auto res = mUnityTags.emplace(std::move(tag));
            if (!res.second) {
                throw std::invalid_argument("tag already exists: " + tag.first);
            }
        }
        tags.clear();
        return *this;
    }

    ShaderPass& operator<<(Blend blend) {
        mShaderState.mBlendState.mRenderTargets.emplace_back(blend);
        return *this;
    }
    
    ShaderPass& operator<<(CullMode cull) {
        mShaderState.mRasterizerState.mCullMode = cull;
        return *this;
    }

    ShaderPass& operator<<(Unity::ZWrite z) {
        mShaderState.mDepthStencilState.mDepthWrite = z.mEnabled;
        return *this;
    }
    
    ShaderPass& operator<<(ComparisonFunc comp) {
        mShaderState.mDepthStencilState.mDepthFunc = comp;
        if (std::holds_alternative<Always_>(comp)) {
            mShaderState.mDepthStencilState.mDepthEnabled = false;
        }
        return *this;
    }

    ShaderPass& operator<<(Unity::AlphaToMask_) {
        mShaderState.mBlendState.mAlphaToCoverageEnable = true;
        return *this;
    }

    ShaderPass& operator<<(Unity::Name name) {
        mName = std::move(name.mValue);
        return *this;
    }

    bool isShadowCaster() const {
        const auto& name = at(mUnityTags, "LightMode");
        if (name == "ShadowCaster")
            return true;
        else
            return false;
    }

    bool isMeta() const {
        const auto& name = at(mUnityTags, "LightMode");
        if (name == "Meta")
            return true;
        else
            return false;
    }

    std::string mName;
    ShaderProgram mProgram;
    PipelineState mShaderState;

    Map<std::string, std::string> mUnityTags;
    Unity::AppData mUnityAppData = Unity::AppData::Full;
    bool mUnityInstancing = false;
    bool mUnityFog = false;
    bool mUnityReceiveShadow = false;
};

}
