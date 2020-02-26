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

inline void SetName(ID3D12Object* obj, const wchar_t* str) {
    V(obj->SetName(str));
}

inline void SetName(IDXGIObject* obj, const wchar_t* name) {
    V(obj->SetPrivateData(WKPDID_D3DDebugObjectName, (uint32_t)wcslen(name), name));
}

template<class T>
void SetName(com_ptr<T>& obj, const wchar_t* str) {
    SetName(obj.get(), str);
}

#ifdef STAR_DEV
#define STAR_SET_DEBUG_NAME(OBJECT, NAME) SetName(OBJECT, fromUTF8(NAME).data())
#else
#define STAR_SET_DEBUG_NAME(OBJECT, NAME) 
#endif

namespace DX12 {

uint64_t waitForFence(ID3D12Fence* Fence, HANDLE FenceEvent, uint64_t WaitValue);

com_ptr<IDXGIFactory4> createFactory();

com_ptr<IDXGIAdapter1> getHardwareAdapter(IDXGIFactory4* pFactory);

bool isDirectXRaytracingSupported(IDXGIAdapter1* adapter);

com_ptr<ID3D12Device> createDevice(IDXGIFactory4* pFactory);

com_ptr<ID3D12CommandQueue> createDirectQueue(ID3D12Device* pDevice);

com_ptr<ID3D12Fence> createFence(ID3D12Device* pDevice,
    uint64_t& nextFrame, std::string_view, bool increment = true);

winrt::handle createFenceEvent();

com_ptr<ID3D12Resource> createBuffer(ID3D12Device* pDevice, uint64_t size);
com_ptr<ID3D12Resource> createTexture2D(ID3D12Device* pDevice, const D3D12_RESOURCE_DESC& desc);

}

}
