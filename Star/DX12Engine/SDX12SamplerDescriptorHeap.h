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

namespace Star::Graphics::Render {

class DX12SamplerDescriptorHeap {
public:
    com_ptr<ID3D12DescriptorHeap> mHeap_SAMPLER;
    uint32_t mNum_SAMPLER = 0;
    uint32_t mSize_SAMPLER = 0;
    size_t mOffset_SAMPLER = 0;
    size_t mGpuOffset_SAMPLER = 0;
};

}
