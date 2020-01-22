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
#include <Star/DX12Engine/SConfig.h>
#include <Star/Graphics/SRenderEngine.h>

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif
    STAR_VE_API Star::Graphics::Render::Engine*
        createDX12EngineImpl(
            const Star::Graphics::Render::EngineMemory& memory,
            const Star::Graphics::Render::Engine::Context& context,
            const Star::Graphics::Render::Engine::Configs& configs
        );
#ifdef __cplusplus
}
#endif

namespace Star::Graphics::Render {

inline std::unique_ptr<Engine> createDX12Engine(
    const EngineMemory& memory,
    const Engine::Context& context,
    const Engine::Configs& configs
) {
    return std::unique_ptr<Engine>(createDX12EngineImpl(memory, context, configs));
}

}
