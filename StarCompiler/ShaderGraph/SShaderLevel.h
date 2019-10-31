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
#include <StarCompiler/ShaderGraph/SShaderPass.h>

namespace Star::Graphics::Render::Shader {

namespace Unity {

struct LOD {
    uint32_t mValue = 0;
};

struct UsePass {
    std::string mName;
};

}

class ShaderLevel {
public:
    AttributeUsageMap getAttributes() const;

    ShaderLevel& operator<<(std::pair<std::string, std::string> tag) {
        auto res = mUnityTags.emplace(std::move(tag));
        if (!res.second) {
            throw std::invalid_argument("tag already exists: " + tag.first);
        }
        return *this;
    }

    ShaderLevel& operator<<(std::vector<std::pair<std::string, std::string>> tags) {
        for (auto& tag : tags) {
            auto res = mUnityTags.emplace(std::move(tag));
            if (!res.second) {
                throw std::invalid_argument("tag already exists: " + tag.first);
            }
        }
        tags.clear();
        return *this;
    }

    ShaderLevel& operator<<(Unity::LOD lod) {
        mUnityLOD = lod.mValue;
        return *this;
    }

    ShaderLevel& operator<<(Unity::UsePass use) {
        if (use.mName.empty()) {
            throw std::invalid_argument("unity use pass name is empty");
        }
        mUnityUsePasses.emplace_back(std::move(use.mName));
        return *this;
    }
    uint32_t mLOD = 0;
    Map<std::string, std::vector<ShaderPass>> mPasses;
    // Unity
    Map<std::string, std::string> mUnityTags;
    uint32_t mUnityLOD = 100;
    std::vector<std::string> mUnityUsePasses;
};

}
