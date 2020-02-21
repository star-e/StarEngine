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

#include "SDX12Pointer.h"
#include "SDX12Types.h"
#include "SDX12ShaderDescriptorHeap.h"

namespace Star::Graphics::Render {

void intrusive_ptr_add_ref(DX12MeshData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12MeshData* p) {
    if (--p->mRefCount == 0) {
        p->mVertexBuffers.clear();
        p->mVertexBufferViews.clear();
        p->mSubMeshes.clear();
        p->mIndexBuffer.mBuffer = nullptr;
        p->mMeshData.reset();
        p->mLayoutID = 0;
        p->mLayoutName.clear();
    }
}

void intrusive_ptr_add_ref(DX12TextureData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12TextureData* p) {
    if (--p->mRefCount == 0) {
        p->mTexture = nullptr;
        p->mTextureData.reset();
    }
}

void intrusive_ptr_add_ref(DX12ShaderData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12ShaderData* p) {
    if (--p->mRefCount == 0) {
        p->mSolutions.clear();
        p->mSolutionIndex.clear();
        p->mShaderData.reset();
    }
}

void intrusive_ptr_add_ref(DX12MaterialData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12MaterialData* p) {
    if (--p->mRefCount == 0) {
        for (size_t solutionID = 0; solutionID != p->mShaderData.size(); ++solutionID) {
            const auto& solution = p->mShaderData[solutionID];
            for (size_t pipelineID = 0; pipelineID != solution.mPipelines.size(); ++pipelineID) {
                const auto& pipeline = solution.mPipelines[pipelineID];
                for (size_t queueID = 0; queueID != pipeline.mQueues.size(); ++queueID) {
                    const auto& queue = pipeline.mQueues[queueID];
                    for (size_t levelID = 0; levelID != queue.mLevels.size(); ++levelID) {
                        const auto& level = queue.mLevels[levelID];
                        for (size_t variantID = 0; variantID != level.mPasses.size(); ++variantID) {
                            const auto& variant = level.mPasses[variantID];
                            for (size_t passID = 0; passID != variant.mSubpasses.size(); ++passID) {
                                const auto& subpass = variant.mSubpasses[passID];
                                for (const auto& collection : subpass.mCollections) {
                                    if (std::holds_alternative<Persistent_>(collection.mIndex.mPersistency)) {
                                        for (const auto& list : collection.mResourceViewLists) {
                                            p->mDescriptorHeap->deallocatePersistent(list.mCpuOffset, list.mCapacity);
                                        }
                                        for (const auto& list : collection.mSamplerLists) {
                                            p->mDescriptorHeap->deallocatePersistent(list.mCpuOffset, list.mCapacity);
                                        }
                                    }
                                } // descriptor collection
                            } // subpasses
                        } // passes
                    } // level
                } // queue
            } // pipeline
        } // solution

        p->mShader.reset();
        p->mShaderData.clear();
        p->mMaterialData.reset();
        p->mConstantMap.mBuffer.clear();
        p->mConstantMap.mIndex.clear();

        p->mDescriptorHeap = nullptr;
    }
}

void intrusive_ptr_add_ref(DX12ContentData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12ContentData* p) {
    if (--p->mRefCount == 0) {
        p->mIDs.clear();
        p->mDrawCalls.clear();
        p->mFlattenedObjects.clear();
        p->mContentData.reset();
    }
}

void intrusive_ptr_add_ref(DX12RenderGraphData* p) {
    ++p->mRefCount;
}

void intrusive_ptr_release(DX12RenderGraphData* p) {
    if (--p->mRefCount == 0) {
        p->mRenderGraph.mSolutions.clear();
        p->mRenderGraph.mFramebuffers.clear();
        p->mRenderGraph.mRTVs.clear();
        p->mRenderGraph.mDSVs.clear();
        p->mRenderGraph.mNumBackBuffers = 0;
        p->mRenderGraph.mSolutionIndex.clear();
        p->mShaderIndex.clear();
        p->mRenderGraphData.reset();
    }
}

}
