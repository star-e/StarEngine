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

#include "SDX12FrameQueue.h"
#include "SDX12SwapChain.h"
#include <Star/DX12Engine/SDX12Types.h>
#include <Star/Graphics/SCamera.h>

namespace Star::Graphics::Render {

DX12FrameQueue::DX12FrameQueue(ID3D12Device* pDevice,
    const DX12UploadBufferPool& pool,
    const Engine::Configs& configs, const allocator_type& alloc)
    : mDevice(pDevice)
    , mFence(DX12::createFence(pDevice, mNextFrameFence, "FrameQueueFence"))
    , mFenceEvent(DX12::createFenceEvent())
    , mFrames(alloc)
    , mDirectQueue(DX12::createDirectQueue(pDevice))
    , mDescriptors(pDevice, 
        {
            configs.mShaderDescriptorCapacity,
            configs.mShaderDescriptorCircularReserve,
            configs.mFrameQueueSize
        }, alloc)
    , mUploadBuffer(pool, configs.mFrameQueueSize)
{
    mDirectQueue->GetTimestampFrequency(&mCommandQueuePerformanceFrequency);
    mFrames.reserve(configs.mFrameQueueSize);
    for (int i = 0; i != configs.mFrameQueueSize; ++i) {
        mFrames.emplace_back(pDevice, "FrameContext: ", i);
    }
}

void DX12FrameQueue::initPipeline(const DX12SwapChain& sc) {
    auto pContext = beginFrame(sc);

    const auto& pipeline = sc.currentPipeline();
    auto pCL = pContext->mCommandList.get();
    for (int k = 0; k != pipeline.mRTVInitialStates.size(); ++k) {
        auto state = pipeline.mRTVInitialStates[k];
        if (state == RESOURCE_STATE_COMMON || state == RESOURCE_STATE_RENDER_TARGET) {
            continue;
        }
        auto resourceID = sc.currentSolution().mRTVSources[k].mHandle;
        auto resource = sc.mRenderGraph->mRenderGraph.mFramebuffers.at(resourceID);
        D3D12_RESOURCE_BARRIER barriers[] = {
            CD3DX12_RESOURCE_BARRIER::Transition(
                resource.get(),
                static_cast<D3D12_RESOURCE_STATES>(RESOURCE_STATE_RENDER_TARGET),
                static_cast<D3D12_RESOURCE_STATES>(state)),
        };
        pCL->ResourceBarrier(_countof(barriers), barriers);
    }
    pCL->Close();
    ID3D12CommandList* lists[] = { pCL };
    mDirectQueue->ExecuteCommandLists(_countof(lists), lists);

    endFrame(pContext);
}

const DX12FrameContext* DX12FrameQueue::beginFrame(const DX12SwapChain& sc) {
    Expects(sc.mSwapChain);

    // Get/Increment the fence counter
    uint64_t FrameFence = mNextFrameFence;
    mNextFrameFence = mNextFrameFence + 1;

    // Get/Increment the frame ring-buffer index
    uint32_t FrameIndex = mNextFrameIndex;
    mNextFrameIndex = (mNextFrameIndex + 1) % (uint32_t)mFrames.size();

    // Wait for the last frame occupying this slot to be complete
    auto pFrame = &mFrames[FrameIndex];
    DX12::waitForFence(mFence.get(), mFenceEvent.get(), pFrame->mFrameFenceId);
    pFrame->mFrameFenceId = FrameFence;

    // Associate the frame with the swap chain backbuffer & RTV.
    uint32_t backBufferIndex = sc.mSwapChain->GetCurrentBackBufferIndex();
    const auto& backBuffer = sc.getBackBuffer(backBufferIndex);
    pFrame->mBackBufferIndex = backBufferIndex;
    pFrame->mBackBufferCount = sc.mRenderGraph->mRenderGraph.mNumBackBuffers;
    pFrame->mBackBuffer = backBuffer;
    //pFrame->mWrapped11BackBuffer = backBuffer.mWrapped11Buffer.get();
    //pFrame->mD2DRenderTarget = backBuffer.mD2DRenderTarget.get();
    pFrame->mBackBufferRTV = sc.getBackBufferDescriptor(backBufferIndex, false);
    pFrame->mBackBufferRTVsRGB = sc.getBackBufferDescriptor(backBufferIndex, true);

    // Reset the command allocator and list
    V(pFrame->mCommandAllocator->Reset());
    V(pFrame->mCommandList->Reset(pFrame->mCommandAllocator.get(), nullptr));

    // advance frame
    mDescriptors.advanceFrame();
    mUploadBuffer.advanceFrame();

    // resources
    pFrame->mRenderSolution = &sc.currentSolution();
    pFrame->mRenderWorks = &sc.mRenderGraph->mRenderGraph;

    pFrame->mSolutionID = sc.mCurrentSolution;
    pFrame->mPipelineID = sc.mCurrentPipeline;

    return pFrame;
}

void DX12FrameQueue::renderFrame(const DX12FrameContext* pContext, std::pmr::memory_resource* mr) {
    // met BackBuffer's pre-condition
    auto pCommandList = pContext->mCommandList.get();
    {
        D3D12_RESOURCE_BARRIER barriers[] = {
            CD3DX12_RESOURCE_BARRIER::Transition(
                pContext->mRenderWorks->mFramebuffers[pContext->mBackBufferIndex].get(),
                D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET),
        };
        pCommandList->ResourceBarrier(_countof(barriers), barriers);
    }

    // Render Passes
    const auto& rw = *pContext->mRenderSolution;
    const auto& resource = *pContext->mRenderWorks;

    const auto& pipeline = rw.mPipelines[pContext->mPipelineID];

    std::pmr::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvs(mr);
    rtvs.reserve(16);
    std::pmr::vector<D3D12_RESOURCE_BARRIER> barriers(mr);
    barriers.reserve(32);

    std::pmr::vector<std::byte> perPassCB(mr);
    std::pmr::vector<std::byte> perInstanceCB(mr);
    perPassCB.reserve(256);
    perInstanceCB.reserve(256);

    uint32_t solutionID = pContext->mSolutionID;
    uint32_t pipelineID = pContext->mPipelineID;

    ID3D12DescriptorHeap* ppHeaps[] = {
        mDescriptors.get(),
    };
    pCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

    for (uint32_t passID = 0; passID != pipeline.mPasses.size(); ++passID) {
        const auto& pass = pipeline.mPasses[passID];
        if (!pass.mViewports.empty()) {
            Expects(pass.mViewports.size() == 1);
            static_assert(sizeof(D3D12_VIEWPORT) == sizeof(VIEWPORT));
            pCommandList->RSSetViewports(gsl::narrow_cast<uint32_t>(pass.mViewports.size()),
                alias_cast<const D3D12_VIEWPORT*>(&pass.mViewports[0]));
        }
        if (!pass.mScissorRects.empty()) {
            Expects(pass.mScissorRects.size() == 1);
            static_assert(sizeof(D3D12_RECT) == sizeof(RECT));
            pCommandList->RSSetScissorRects(gsl::narrow_cast<uint32_t>(pass.mScissorRects.size()),
                alias_cast<const D3D12_RECT*>(&pass.mScissorRects[0]));
        }
        
        for (uint32_t subpassID = 0; subpassID != pass.mSubpasses.size(); ++subpassID) {
            const auto& subpass = pass.mSubpasses[subpassID];
            //---------------------------------------------------
            // Pre-Subpass
            rtvs.clear();
            for (const auto& rt : subpass.mOutputAttachments) {
                D3D12_CPU_DESCRIPTOR_HANDLE rtv;
                if (rt.mDescriptor.mHandle == 0) {
                    rtv = resource.mRTVs.getCpuHandle(pContext->mBackBufferIndex);
                } else if (rt.mDescriptor.mHandle == pContext->mBackBufferCount) {
                    rtv = resource.mRTVs.getCpuHandle(pContext->mBackBufferIndex + pContext->mBackBufferCount);
                } else {
                    rtv = resource.mRTVs.getCpuHandle(rt.mDescriptor.mHandle);
                }
                rtvs.emplace_back(rtv);

                visit(overload(
                    [&](const ClearColor& v) {
                        pCommandList->ClearRenderTargetView(
                            rtv, v.mClearColor.data(), 0, nullptr);
                    },
                    [&](const ClearDepthStencil& v) {
                        throw std::runtime_error("RTV should not use clear depth stencil");
                    },
                    [](const auto&) {}
                ), rt.mLoadOp);
            }
            D3D12_CPU_DESCRIPTOR_HANDLE dsv{};
            if (subpass.mDepthStencilAttachment) {
                const auto& ds = *subpass.mDepthStencilAttachment;
                dsv = resource.mDSVs.getCpuHandle(ds.mDescriptor.mHandle);
                visit(overload(
                    [&](const ClearColor& v) {
                        throw std::runtime_error("DSV should not use clear color");
                    },
                    [&](const ClearDepthStencil& v) {
                        D3D12_CLEAR_FLAGS flags = {};
                        if (v.mClearDepth)
                            flags |= D3D12_CLEAR_FLAG_DEPTH;
                        if (v.mClearStencil)
                            flags |= D3D12_CLEAR_FLAG_STENCIL;
                        pCommandList->ClearDepthStencilView(dsv, flags,
                            v.mDepthClearValue, v.mStencilClearValue, 0, nullptr);
                    },
                    [](const auto&) {}
                ), ds.mLoadOp);
            }

            if (!rtvs.empty() || subpass.mDepthStencilAttachment) {
                pCommandList->OMSetRenderTargets(
                    gsl::narrow_cast<uint32_t>(rtvs.size()), rtvs.empty() ? nullptr : rtvs.data(),
                    FALSE, subpass.mDepthStencilAttachment ? &dsv : nullptr
                );
            }
            //---------------------------------------------------
            // Subpass
            {
                D3D12_PRIMITIVE_TOPOLOGY prevTopology = {};
                ID3D12PipelineState* pPrevPSO = nullptr;
                for (const auto& queue : subpass.mOrderedRenderQueue) {
                    pCommandList->SetGraphicsRootSignature(subpass.mRootSignature.get());
                    // Per-Subpass
                    Camera cam{};
                    cam.mViewSpace = OpenGL;
                    cam.mNDC = Direct3D;
                    cam.lookAt(Vector3f(0, 0, 0), Vector3f(0, 1, 0), Vector3f(0, 0, 1));
                    //cam.lookTo(Vector3f(0, 1.0f, 0), Vector3f(1.f, 0, 0.0f), Vector3f(0, 1.0f, 0));
                    cam.perspective(0.25f * S_PI, 16.0f / 9.0f, 0.25f, 512.0f);

                    auto sizeCB = sizeof(Matrix4f) * 2;
                    sizeCB = boost::alignment::align_up(sizeCB, 256);
                    perPassCB.resize(sizeCB);
                    memcpy(perPassCB.data(), &cam.mProj, sizeof(cam.mProj));
                    memcpy(perPassCB.data() + sizeof(Matrix4f), &cam.mView, sizeof(cam.mView));
                    auto pos = mUploadBuffer.upload(perPassCB.data(), gsl::narrow_cast<uint32_t>(perPassCB.size()), 1, 256);
                    D3D12_CONSTANT_BUFFER_VIEW_DESC desc{
                        pos.mResource->GetGPUVirtualAddress() + pos.mBufferOffset, (uint32_t)perPassCB.size()
                    };
                    auto range = mDescriptors.allocateCircular(1);
                    for (size_t i = 0; i != 1; ++i) {
                        auto d = mDescriptors.advance(range.first, i);
                        mDevice->CreateConstantBufferView(&desc, d.mCpuHandle);
                    }
                    pCommandList->SetGraphicsRootDescriptorTable(2, range.first.mGpuHandle);

                    for (const auto& pContent : queue.mContents) {
                        const auto& content = *pContent;
                        for (const auto& object : content.mIDs) {
                            visit(overload(
                                [](const DrawCall_&) {},
                                [&](const ObjectBatch_&) {
                                    auto& id = object.mIndex;
                                    const auto& batch = content.mFlattenedObjects.at(id);
                                    Expects(batch.mWorldTransforms.size() == batch.mMeshRenderers.size());
                                    Expects(batch.mWorldTransformInvs.size() == batch.mMeshRenderers.size());
                                    for (size_t i = 0; i != batch.mMeshRenderers.size(); ++i) {
                                        const auto& renderer = batch.mMeshRenderers[i];

                                        size_t materialID = 0;
                                        for (const auto& material : renderer.mMaterials) {
                                            const auto& mesh = *renderer.mMesh;
                                            if (materialID >= mesh.mSubMeshes.size()) {
                                                break;
                                            }
                                            const auto& submesh = mesh.mSubMeshes.at(materialID);

                                            auto solutionIter = material->mShader->mSolutionIndex.find(solutionID);
                                            if (solutionIter != material->mShader->mSolutionIndex.end()) {
                                                auto shaderSolutionID = solutionIter->second;
                                                const auto& shaderSolution = material->mShader->mSolutions.at(shaderSolutionID);
                                                auto pipelineIter = shaderSolution.mPipelineIndex.find(pipelineID);
                                                if (pipelineIter != shaderSolution.mPipelineIndex.end()) {
                                                    auto shaderPipelineID = pipelineIter->second;
                                                    const auto& shaderPipeline = shaderSolution.mPipelines.at(shaderPipelineID);
                                                    auto queueIter = shaderPipeline.mQueueIndex.find(RenderSubpassDesc{ passID, subpassID });
                                                    if (queueIter != shaderPipeline.mQueueIndex.end()) {
                                                        auto shaderQueueID = queueIter->second;
                                                        const auto& queue = shaderPipeline.mQueues.at(shaderQueueID);

                                                        // mesh
                                                        auto primTopology = static_cast<D3D12_PRIMITIVE_TOPOLOGY>(mesh.mIndexBuffer.mPrimitiveTopology);
                                                        if (primTopology != prevTopology) {
                                                            pCommandList->IASetPrimitiveTopology(primTopology);
                                                            prevTopology = primTopology;
                                                        }

                                                        pCommandList->IASetVertexBuffers(0,
                                                            gsl::narrow_cast<uint32_t>(mesh.mVertexBufferViews.size()),
                                                            mesh.mVertexBufferViews.data());

                                                        if (mesh.mIndexBufferView.BufferLocation) {
                                                            pCommandList->IASetIndexBuffer(&mesh.mIndexBufferView);
                                                        } else {
                                                            pCommandList->IASetIndexBuffer(nullptr);
                                                        }

                                                        auto sizeCB = sizeof(Matrix4f);
                                                        sizeCB = boost::alignment::align_up(sizeCB, 256);
                                                        Matrix4f worldView = cam.mView * batch.mWorldTransforms[i].mTransform.matrix();
                                                        perPassCB.clear();
                                                        perPassCB.resize(sizeCB);
                                                        memcpy(perPassCB.data(), worldView.data(), sizeof(worldView));
                                                        auto pos2 = mUploadBuffer.upload(perPassCB.data(), gsl::narrow_cast<uint32_t>(perPassCB.size()), 1, 256);
                                                        Expects(perPassCB.size() == 256);
                                                        D3D12_CONSTANT_BUFFER_VIEW_DESC desc{
                                                            pos2.mResource->GetGPUVirtualAddress() + pos2.mBufferOffset, (uint32_t)perPassCB.size()
                                                        };
                                                        auto range = mDescriptors.allocateCircular(1);
                                                        for (size_t i = 0; i != 1; ++i) {
                                                            auto d = mDescriptors.advance(range.first, i);
                                                            mDevice->CreateConstantBufferView(&desc, d.mCpuHandle);
                                                        }
                                                        pCommandList->SetGraphicsRootDescriptorTable(0, range.first.mGpuHandle);

                                                        // materials
                                                        auto levelID = 0;
                                                        auto variantID = 0;
                                                        auto subpassID = 0;
                                                        for (const auto& shaderSubpass : queue.mLevels.at(levelID).mPasses.at(variantID).mSubpasses) {
                                                            // draw call
                                                            const auto& layoutID = shaderSubpass.mVertexLayoutIndex.at(mesh.mLayoutID);
                                                            if (pPrevPSO != shaderSubpass.mStates.at(layoutID).mObject.get()) {
                                                                pCommandList->SetPipelineState(shaderSubpass.mStates.at(layoutID).mObject.get());
                                                                pPrevPSO = shaderSubpass.mStates.at(layoutID).mObject.get();
                                                            }

                                                            const auto& subpassData = material->mShaderData.at(shaderSolutionID).mPipelines.at(shaderPipelineID).mQueues.at(shaderQueueID).
                                                                mLevels.at(levelID).mPasses.at(variantID).mSubpasses.at(subpassID);
                                                            
                                                            if (subpassData.mPersistentCountSRV) {
                                                                pCommandList->SetGraphicsRootDescriptorTable(1, subpassData.mPersistentGpuOffsetSRV);
                                                            } else {
                                                                pCommandList->SetGraphicsRootDescriptorTable(1, {});
                                                            }

                                                            pCommandList->DrawIndexedInstanced(submesh.mIndexCount, 1, submesh.mIndexOffset, 0, 0);
                                                            ++subpassID;
                                                        } // shader subpass
                                                    } // shader queue
                                                } // shader pipeline
                                            } // shader solution
                                            ++materialID;
                                        } // material
                                    } // mesh renderer
                                } // object batch
                            ), object.mType); // objects
                        } // content
                    } // unordered queue
                } // ordered queue
            } // subpass

            //---------------------------------------------------
            // Post-Subpass
            if (subpass.mPostViewTransitions.empty()) {
                continue;
            }            
            barriers.clear();
            for (const auto& t : subpass.mPostViewTransitions) {
                ID3D12Resource* pResource = nullptr;
                if (t.mFramebuffer.mHandle == 0) {
                    pResource = resource.mFramebuffers[pContext->mBackBufferIndex].get();
                } else {
                    pResource = resource.mFramebuffers[t.mFramebuffer.mHandle].get();
                }
                D3D12_RESOURCE_STATES prev = static_cast<D3D12_RESOURCE_STATES>(t.mSource);
                D3D12_RESOURCE_STATES post = static_cast<D3D12_RESOURCE_STATES>(t.mTarget);

                barriers.emplace_back(CD3DX12_RESOURCE_BARRIER::Transition(pResource, prev, post));
            }
            pCommandList->ResourceBarrier(gsl::narrow_cast<uint32_t>(barriers.size()), barriers.data());                            
        }
    }

    pCommandList->Close();
    ID3D12CommandList* lists[] = { pCommandList };
    mDirectQueue->ExecuteCommandLists(_countof(lists), lists);
}

void DX12FrameQueue::endFrame(const DX12FrameContext* pFrame) {
    // Signal that the frame is complete
    check_hresult(mFence->SetEventOnCompletion(pFrame->mFrameFenceId, mFenceEvent.get()));
    check_hresult(mDirectQueue->Signal(mFence.get(), pFrame->mFrameFenceId));
}

DX12FrameContext::DX12FrameContext(ID3D12Device* pDevice, std::string_view name, uint32_t id) {
    V(pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mCommandAllocator.put())));
    STAR_SET_DEBUG_NAME(mCommandAllocator, std::string(name) + std::to_string(id));

    V(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        mCommandAllocator.get(), nullptr, IID_PPV_ARGS(mCommandList.put())));
    STAR_SET_DEBUG_NAME(mCommandList, std::string(name) + std::to_string(id));

    mCommandList->Close();
}

const DX12RenderPipeline& DX12FrameContext::currentPipeline() const noexcept {
    return mRenderSolution->mPipelines[mPipelineID];
}

DX12RenderPipeline& DX12FrameContext::currentPipeline() noexcept {
    return const_cast<DX12RenderSolution*>(mRenderSolution)->mPipelines[mPipelineID];
}

}
