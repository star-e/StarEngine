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
#include <Star/DX12Engine/SDX12Fwd.h>

namespace Star::Graphics::Render {

void intrusive_ptr_add_ref(DX12MeshData* p);
void intrusive_ptr_release(DX12MeshData* p);

void intrusive_ptr_add_ref(DX12TextureData* p);
void intrusive_ptr_release(DX12TextureData* p);

void intrusive_ptr_add_ref(DX12ShaderData* p);
void intrusive_ptr_release(DX12ShaderData* p);

void intrusive_ptr_add_ref(DX12MaterialData* p);
void intrusive_ptr_release(DX12MaterialData* p);

void intrusive_ptr_add_ref(DX12ContentData* p);
void intrusive_ptr_release(DX12ContentData* p);

void intrusive_ptr_add_ref(DX12RenderGraphData* p);
void intrusive_ptr_release(DX12RenderGraphData* p);

}
