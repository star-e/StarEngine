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

#include "SShaderRootSignature.h"
#include "SShaderDescriptor.h"
#include "SShaderAttribute.h"

namespace Star::Graphics::Render::Shader {

void RootSignature::addConstant(const ShaderAttribute& attr, ShaderVisibilityType stageID) {
    IsConstant visitor;
    if (!visit(visitor, attr.mType)) {
        return;
    }
    mDatabase.addAttribute(attr, stageID);
}

void RootSignature::addDescriptor(const ShaderAttribute& attr, ShaderVisibilityType stage) {
    IsConstant visitor;
    if (visit(visitor, attr.mType)) {
        return;
    }
    mDatabase.addAttribute(attr, stage);
}

void RootSignature::reserveCapacities(UpdateEnum update, RootSignature& rhs) const {
    mDatabase.reserveDescriptors(update, rhs.mDatabase);
}

void RootSignature::collectDescriptors(UpdateEnum update, RootSignature& rhs) const {
    mDatabase.collectDescriptors(update, rhs.mDatabase);
}

void RootSignature::mergeConstantBuffers(UpdateEnum update, RootSignature& rhs) const {
    mDatabase.mergeConstantBuffers(update, rhs.mDatabase);
}

void RootSignature::addConstantBuffersDescriptors() {
    mDatabase.addConstantBuffersDescriptors();
}

}
