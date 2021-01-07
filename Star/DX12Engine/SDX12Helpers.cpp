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
    bool debugDXGI = false;
#ifdef STAR_DEV
    com_ptr<IDXGIInfoQueue> dxgiInfoQueue;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.put())))) {
        debugDXGI = true;
        V(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(factory.put())));
        dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
        dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
    }
#endif
    if (!debugDXGI) {
        V(CreateDXGIFactory1(IID_PPV_ARGS(factory.put())));
    }

    // Determines whether tearing support is available for fullscreen borderless windows.
    if (true) {
        BOOL allowTearing = FALSE;

        com_ptr<IDXGIFactory5> factory5 = factory.try_as<IDXGIFactory5>();

        HRESULT hr = S_OK;
        if (factory5) {
            hr = factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
        }

        if (FAILED(hr)) {
            OutputDebugStringA("WARNING: Variable refresh rate displays are not supported.\n");
        }
    }
    return factory;
}

com_ptr<IDXGIAdapter1> getHardwareAdapter(IDXGIFactory4* pFactory) {
    com_ptr<IDXGIAdapter1> adapter;

    for (UINT adapterID = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterID, adapter.put()); ++adapterID) {
        DXGI_ADAPTER_DESC1 desc;
        ThrowIfFailed(adapter->GetDesc1(&desc));

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            // Don't select the Basic Render Driver adapter.
            continue;
        }

        // Check to see if the adapter supports Direct3D 12, but don't create the actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(adapter.get(),
            D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
        {
#ifdef STAR_DEV
            wchar_t buff[256] = {};
            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterID, desc.VendorId, desc.DeviceId, desc.Description);
            OutputDebugStringW(buff);
#endif
            return adapter;
        }
    }

    throw std::runtime_error("no adaptor support d3d12");
}

bool isDirectXRaytracingSupported(IDXGIAdapter1* adapter) {
    com_ptr<ID3D12Device> testDevice;
    D3D12_FEATURE_DATA_D3D12_OPTIONS5 featureSupportData = {};

    return SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(testDevice.put())))
        && SUCCEEDED(testDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &featureSupportData, sizeof(featureSupportData)))
        && featureSupportData.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED;
}

com_ptr<ID3D12Device> createDevice(IDXGIFactory4* pFactory) {
    com_ptr<ID3D12Device> device;
#ifdef STAR_DEV
    {
        com_ptr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.put())))) {
            debugController->EnableDebugLayer();
        } else {
            OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
        }
//#ifdef _DEBUG
//        com_ptr<ID3D12Debug1> debugController1;
//        V(debugController->QueryInterface(IID_PPV_ARGS(debugController1.put())));
//        debugController1->SetEnableGPUBasedValidation(TRUE);
//#endif // _DEBUG
    }
#endif // STAR_DEV

    com_ptr<IDXGIAdapter1> hardwareAdapter = getHardwareAdapter(pFactory);
    //if (!isDirectXRaytracingSupported(hardwareAdapter.get())) {
    //    throw std::runtime_error("ERROR: DirectX Raytracing is not supported by your OS, GPU and/or driver");
    //}

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
    CD3DX12_HEAP_PROPERTIES heapDesc(D3D12_HEAP_TYPE_DEFAULT);
    auto desc = CD3DX12_RESOURCE_DESC::Buffer(size);
    V(pDevice->CreateCommittedResource(
        &heapDesc,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(ptr.put())));

    return ptr;
}

com_ptr<ID3D12Resource> createTexture2D(ID3D12Device* pDevice, const D3D12_RESOURCE_DESC& desc) {
    com_ptr<ID3D12Resource> tex;
    CD3DX12_HEAP_PROPERTIES heapDesc(D3D12_HEAP_TYPE_DEFAULT);
    V(pDevice->CreateCommittedResource(
        &heapDesc,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(tex.put())));
    return tex;
}

}

}
