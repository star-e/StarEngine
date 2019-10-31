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

#include "SShaderRegisters.h"

namespace Star::Graphics::Render::Shader {

uint32_t ShaderRegister::get(RootAccessEnum vis, DescriptorType type, uint32_t space) {
    return mSlots[vis][type][space];
}

uint32_t ShaderRegister::increase(RootAccessEnum vis, DescriptorType type, uint32_t space, uint32_t count) {
    auto& slot = mSlots[vis][type][space];
    auto prev = slot;
    slot += count;
    return prev;
}

void ShaderRegister::reserveAll(DescriptorType type, uint32_t space, uint32_t count) {
    uint32_t ps = mSlots[RA_PS][type][space];
    for (uint vis = RA_PS; vis != RA_Count; ++vis) {
        auto& map = mSlots[static_cast<RootAccessEnum>(vis)];
        if (map[type][space] != ps) {
            throw std::runtime_error("register slot inconsistent");
        }
        map[type][space] += count;
    }
}

}
