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

#include "SDX12Helpers.h"

namespace Star::Graphics::Render {

namespace DX12 {

uint64_t waitForFence(ID3D12Fence* pFence, HANDLE FenceEvent, uint64_t waitValue) {
    uint64_t completedValue;
    while ((completedValue = pFence->GetCompletedValue()) < waitValue) {
        if (FenceEvent) {
            WaitForSingleObject(FenceEvent, INFINITE);
        } else {
            Sleep(1);
        }
    }
    return completedValue;
}

com_ptr<IDXGIFactory4> createFactory() {
    com_ptr<IDXGIFactory4> factory;
    UINT dxgiFactoryFlags = 0;
#ifndef NDEBUG
    dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
    V(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(factory.put())));
    return factory;
}

com_ptr<IDXGIAdapter1> getHardwareAdapter(IDXGIFactory4* pFactory) {
    com_ptr<IDXGIAdapter1> pAdapter;

    for (UINT adapterIndex = 0; ; ++adapterIndex) {
        if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, pAdapter.put())) {
            // No more adapters to enumerate.
            break;
        }

        // Check to see if the adapter supports Direct3D 12, but don't create the
        // actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(pAdapter.get(),
            D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
        {
#ifndef NDEBUG
            DXGI_ADAPTER_DESC chosenAdapterDesc;
            V(pAdapter->GetDesc(&chosenAdapterDesc));
            OutputDebugStringW(L"Chosen adapter: ");
            OutputDebugStringW(chosenAdapterDesc.Description);
            OutputDebugStringW(L"\n");
#endif
            return pAdapter;
        }
    }

    throw std::runtime_error("no adaptor support d3d12");
}

com_ptr<ID3D12Device> createDevice(IDXGIFactory4* pFactory) {
    com_ptr<ID3D12Device> device;

#ifdef STAR_DEV
    com_ptr<ID3D12Debug> debugController;
    V(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.put())));
    debugController->EnableDebugLayer();
#ifdef _DEBUG
    com_ptr<ID3D12Debug1> debugController1;
    V(debugController->QueryInterface(IID_PPV_ARGS(debugController1.put())));
    debugController1->SetEnableGPUBasedValidation(TRUE);
#endif // _DEBUG
#endif // NDEBUG

    com_ptr<IDXGIAdapter1> hardwareAdapter = getHardwareAdapter(pFactory);

    V(D3D12CreateDevice(hardwareAdapter.get(),
        D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.put())
    ));
    STAR_SET_DEBUG_NAME(device, "D3D12Device(11_0)");

    // Set InfoQueue
    com_ptr<ID3D12InfoQueue> infoQueue = device.try_as<ID3D12InfoQueue>();
    if (infoQueue) {
        //V(infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE));
        //V(infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE));
        //V(infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, FALSE));
        //V(infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_INFO, FALSE));
        //V(infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_MESSAGE, FALSE));

        //D3D12_MESSAGE_ID hide[] =
        //{
        //    D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
        //    D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
        //    D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,
        //};
        //D3D12_INFO_QUEUE_FILTER filter;
        //memset(&filter, 0, sizeof(filter));
        //filter.DenyList.NumIDs = _countof(hide);
        //filter.DenyList.pIDList = hide;
        //infoQueue->AddStorageFilterEntries(&filter);
    }

    return device;
}

com_ptr<ID3D12CommandQueue> createDirectQueue(ID3D12Device* pDevice) {
    com_ptr<ID3D12CommandQueue> cq;
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    V(pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(cq.put())));
    STAR_SET_DEBUG_NAME(cq, "DirectQueue");

    return cq;
}

com_ptr<ID3D12Fence> createFence(ID3D12Device* pDevice, uint64_t& nextFrame,
    std::string_view name, bool increment
) {
    com_ptr<ID3D12Fence> fence;
    V(pDevice->CreateFence(nextFrame, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.put())));
    STAR_SET_DEBUG_NAME(fence, name);

    if (increment)
        ++nextFrame;

    return fence;
}

winrt::handle createFenceEvent() {
    winrt::handle fenceEvent(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    if (!fenceEvent) {
        V(HRESULT_FROM_WIN32(GetLastError()));
    }
    return fenceEvent;
}

com_ptr<ID3D12Resource> createBuffer(ID3D12Device* pDevice, uint64_t size) {
    com_ptr<ID3D12Resource> ptr;
    HRESULT hr = S_OK;

    V(pDevice->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(size),
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(ptr.put())));

    return ptr;
}

com_ptr<ID3D12Resource> createTexture2D(ID3D12Device* pDevice, const D3D12_RESOURCE_DESC& desc) {
    com_ptr<ID3D12Resource> tex;
    V(pDevice->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(tex.put())));
    return tex;
}

}

}
