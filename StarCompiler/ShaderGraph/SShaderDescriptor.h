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

namespace Star::Graphics::Render::Shader {

struct IsConstant {
    template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
    bool operator()(const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& m) const noexcept {
        return true;
    }

    template<class T>
    bool operator()(const T&) const noexcept {
        return false;
    }
};

bool isUnbounded(const DescriptorModel& model) noexcept;

DescriptorRangeType getDescriptorType(const DescriptorModel& model);

DescriptorArray getDescriptorRange(const DescriptorModel& model, uint32_t count) noexcept;
Descriptor makeDescriptorRange(const DescriptorRangeType& type, uint32_t space, const DescriptorArray& range);

ShaderVisibilityType getShaderVisibilityType(ShaderStageType stage);
ShaderStageType getShaderStageType(ShaderVisibilityType e);

const char* getRootDescriptorName(const DescriptorRangeType& type) noexcept;
char getRegisterPrefix(const DescriptorRangeType& type) noexcept;

}
