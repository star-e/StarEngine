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
#include <Star/SMultiIndex.h>
#include <StarCompiler/RenderGraph/SRenderGraphTypes.h>

namespace Star {

namespace Graphics {

namespace Render {

// validation
void validateResource(const Resource& resource);
void validateResourceDataView(const Resource& resource, const ResourceDataView& view);
void validateResourceView(const Resource& resource, const ResourceDataView& view, const ResourceViewType& state);

void validateTextureViewState(const Resource& resource, const ResourceDataView& view,
    const TextureViewState& state, const SourceTarget& st, const API& api);

void validateRenderTarget(const RenderTargetResource& r);
PixelModel validateRenderTargetBinding(const ColorSpace& cs, const RenderTargetResource& rt);

void validateRenderValue(const Resource& resource, const RenderValue& node,
    const SourceTarget& st, const API& api);

void validateViewConvertion(const ResourceViewType& input, const ResourceViewType& output);
void validateTextureViewTransition(const TextureViewState& input, const TextureViewState& output);

// utils
bool isMSAA(const RenderTargetResource& r);

inline bool isDSV(const RenderTargetResource& rt) noexcept {
    return std::holds_alternative<ClearDepthStencil>(rt.mClearColor);
}

inline bool isRTV(const RenderTargetResource& rt) noexcept {
    return std::holds_alternative<ClearColor>(rt.mClearColor);
}

inline bool isBackBuffer(const RenderTargetResource& r) noexcept {
    return std::holds_alternative<BackBuffer_>(r.mType);
}

OrderedNameMap<RenderValue> getValues(const RenderNode& node);

inline std::tuple<size_t/*nodeID*/, std::string/*name*/, ResourceDataView/*subresource*/>
make_key(size_t nodeID, const RenderValue& v) noexcept {
    return { nodeID, v.mName, v.mData };
}

inline RESOURCE_DIMENSION getDimension(const ResourceType& res) {
    return visit(overload(
        [](const Resource1D& r) { return RESOURCE_DIMENSION_TEXTURE1D; },
        [](const Resource2D& r) { return RESOURCE_DIMENSION_TEXTURE2D; },
        [](const Resource3D& r) { return RESOURCE_DIMENSION_TEXTURE3D; },
        [](const ResourceBuffer& r) { return RESOURCE_DIMENSION_BUFFER; }
    ), res);
}

inline const char* getColorSpaceName(const ColorSpace& v) {
    return visit(overload(
        [](Linear_) {
            return "Linear";
        },
        [](Device_) {
            return "Device";
        }
    ), v);
}

std::ostream& operator<<(std::ostream& oss, const ResourceDataView& view);
std::ostream& operator<<(std::ostream& oss, const PixelModel& view);
std::ostream& operator<<(std::ostream& oss, const ShaderDescriptorType& view);

RESOURCE_DESC buildResourceDesc(const Resource& resource);

RENDER_TARGET_VIEW_DESC buildRenderTargetViewDesc(
    const Resource& resource,
    const ResourceDataView& view,
    const PixelModel& model
);

DEPTH_STENCIL_VIEW_DESC buildDepthStencilViewDesc(
    const Resource& resource,
    const ResourceDataView& view,
    bool bReadOnly
);

inline RESOURCE_STATES buildResourceStates(const RenderTargetState& state) {
    return visit(overload(
        [](Common_) {
            return RESOURCE_STATE_COMMON;
        },
        [](RenderTarget_) {
            return RESOURCE_STATE_RENDER_TARGET;
        },
        [](UnorderedAccess_) {
            return RESOURCE_STATE_UNORDERED_ACCESS;
        },
        [](DepthWrite_) {
            return RESOURCE_STATE_DEPTH_WRITE;
        },
        [&](DepthRead_) {
            uint32_t flags = 0;
            if (state.mPixelShaderResource) {
                flags |= RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
            }
            if (state.mNonPixelShaderResource) {
                flags |= RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
            }
            if (flags == 0) {
                CONSOLE_COLOR(Yellow);
                std::cout << "[warning] unused DepthRead SRV" << std::endl;
                //throw std::invalid_argument("depth read is not pixel or non-pixel");
            }
            flags |= RESOURCE_STATE_DEPTH_READ;
            return static_cast<RESOURCE_STATES>(flags);
        },
        [&](ShaderResource_) {
            uint32_t flags = 0;
            if (state.mPixelShaderResource) {
                flags |= RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
            }
            if (state.mNonPixelShaderResource) {
                flags |= RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
            }
            if (flags == 0) {
                throw std::invalid_argument("shader resource is not pixel or non-pixel");
            }
            return static_cast<RESOURCE_STATES>(flags);
        },
        [&](CopyDest_) {
            return RESOURCE_STATE_COPY_SOURCE;
        },
        [&](CopySource_) {
            return RESOURCE_STATE_COPY_SOURCE;
        },
        [&](ResolveDest_) {
            return RESOURCE_STATE_RESOLVE_DEST;
        },
        [&](ResolveSource_) {
            return RESOURCE_STATE_RESOLVE_SOURCE;
        },
        [](Present_) {
            return RESOURCE_STATE_PRESENT;
        }
    ), state.mState);
}

inline size_t findIndex(const RenderTargetStateTransitions& path, size_t nodeID) {
    size_t i = 0;
    for (; i != path.mFullStates.size(); ++i) {
        const auto& state = path.mFullStates[i];
        if (state.mNodeID == nodeID) {
            break;
        }
    }
    if (i == path.mFullStates.size()) {
        throw std::runtime_error("RenderTargetStateTransitions: nodeID not found");
    }
    return i;
}

inline std::optional<RenderTargetStateTransition> findTransition(
    const RenderTargetStateTransitions& path, size_t nodeID
) {
    std::optional<RenderTargetStateTransition> res;

    size_t i = 0;
    for (; i != path.mTransitions.size(); ++i) {
        const auto& t = path.mTransitions[i];
        if (t.mNodeID == nodeID) {
            res = t;
            break;
        }
    }

    return res;
}

inline const NodeRenderTargetState& getPrevState(
    const RenderTargetStateTransitions& path, size_t i
) {
    Expects(!path.mStates.empty());
    i = (i + 1) % path.mFullStates.size();
    return path.mFullStates[i];
}

inline const NodeRenderTargetState& getNextState(
    const RenderTargetStateTransitions& path, size_t i
) {
    Expects(!path.mStates.empty());
    i = (i + path.mFullStates.size() - 1) % path.mFullStates.size();
    return path.mFullStates[i];
}

inline std::optional<NodeRenderTargetState> getNextDifferentState(
    const RenderTargetStateTransitions& path, size_t i
) {
    std::optional<NodeRenderTargetState> res;

    const auto& state0 = path.mFullStates[i];

    while (i != 0) {
        const auto& state = getNextState(path, i);
        if (state.mRenderTargetState != state0.mRenderTargetState) {
            res = state;
            break;
        }
        --i;
    }
    
    if (i == 0) {
        const auto& state = getNextState(path, i);
        if (state.mRenderTargetState != state0.mRenderTargetState) {
            res = state;
        }
    }

    return res;
}

inline const char* getViewName(const ResourceViewType& v) {
    return visit(overload(
        [](SRV_) {
            return "SRV";
        },
        [](UAV_) {
            return "UAV";
        },
        [](DSV_) {
            return "DSV";
        },
        [](RTV_) {
            return "RTV";
        }
    ), v);
}

const char* getStateName(const TextureViewState& v);
std::string getRenderTargetStateName(const RenderTargetState& v);

}

}

}
