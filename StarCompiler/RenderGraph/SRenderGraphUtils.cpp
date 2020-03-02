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

#include "SRenderGraphUtils.h"
#include <StarCompiler/SConsoleColor.h>
#include <Star/Graphics/SRenderFormatUtils.h>
#include <Star/Graphics/SRenderNames.h>
#include <StarCompiler/Graphics/SRenderFormatUtils.h>
#include <StarCompiler/Graphics/SPixelFormatNames.h>
#include <StarCompiler/Graphics/SRenderNames.h>
#include <StarCompiler/RenderGraph/SRenderGraphNames.h>

namespace Star {

namespace Graphics {

namespace Render {

OrderedNameMap<RenderValue> getValues(const RenderNode& node) {
    OrderedNameMap<RenderValue> values;

    for (const auto& v : node.mOutputs) {
        values.emplace(v);
    }

    for (const auto& v : node.mInputs) {
        values.emplace(v);
    }
    return values;
}

const char* getStateName(const TextureViewState& v) {
    return visit(overload(
        [](Common_) { return "Common"; },
        [](RenderTarget_) { return "RenderTarget"; },
        [](UnorderedAccess_) { return "UnorderedAccess"; },
        [](DepthWrite_) { return "DepthWrite"; },
        [](DepthRead_) { return "DepthRead"; },
        [](ShaderResource_) { return "ShaderResource"; },
        [](CopyDest_) { return "CopyDest"; },
        [](CopySource_) { return "CopySource"; },
        [](ResolveDest_) { return "ResolveDest"; },
        [](ResolveSource_) { return "ResolveSource"; },
        [](Present_) { return "Present"; }
    ), v);
}

std::string getRenderTargetStateName(const RenderTargetState& v) {
    return getStateName(v.mState) +
        visit(overload(
            [&](DepthRead_) -> std::string {
                std::string str;
                if (!v.mPixelShaderResource && !v.mNonPixelShaderResource)
                    str = "<Non-SRV>";
                if (v.mPixelShaderResource)
                    str += "<Pixel>";
                if (v.mNonPixelShaderResource)
                    str += "<NonPixel>";
                return str;
            },
            [&](ShaderResource_) -> std::string {
                std::string str;
                if (v.mPixelShaderResource)
                    str += "<Pixel>";
                if (v.mNonPixelShaderResource)
                    str += "<NonPixel>";

                if (!v.mPixelShaderResource && !v.mNonPixelShaderResource) {
                    throw std::runtime_error("shader resource must be pixel, non-pixel or both, possible reason: user has not provided any shader");
                }
                return str;
            },
            [](auto) -> std::string {
                return {};
            }
        ), v.mState);
}

void validateViewConvertion(const ResourceViewType& input, const ResourceViewType& output) {
    // check view convertion
    visit(overload(
        // DSV_
        [](DSV_, DSV_) {},
        [](DSV_, SRV_) {},
        [](DSV_, auto) {
            throw std::invalid_argument("dsv cannot convert to rtv(resolve), uav");
        },
        // RTV_
        [](RTV_, DSV_) {
            throw std::invalid_argument("rtv cannot convert to dsv");
        },
        [](RTV_, UAV_) {
            throw std::invalid_argument("rtv cannot convert to uav");
        },
        [](RTV_, auto) {
            // rtv, srv
        },
        //SRV_
        [](SRV_, auto) {
            // SRV_ can be any view
        },
        // UAV_
        [](UAV_, UAV_) {},
        [](UAV_, SRV_) {},
        [](UAV_, DSV_) {
            throw std::invalid_argument("uav cannot convert to dsv");
        },
        [](UAV_, RTV_) {
            throw std::invalid_argument("uav cannot convert to rtv");
        }
    ), output, input);
}

void validateTextureViewTransition(const TextureViewState& src, const TextureViewState& dst) {
    visit(overload(
        [&](Common_, auto) {},
        [&](RenderTarget_, Common_) {},
        [&](RenderTarget_, RenderTarget_) {},
        [&](RenderTarget_, ShaderResource_) {},
        [&](RenderTarget_, CopyDest_) {},
        [&](RenderTarget_, CopySource_) {},
        [&](RenderTarget_, ResolveDest_) {},
        [&](RenderTarget_, ResolveSource_) {},
        [&](RenderTarget_, Present_) {},
        [&](UnorderedAccess_, Common_) {},
        [&](UnorderedAccess_, UnorderedAccess_) {},
        [&](UnorderedAccess_, ShaderResource_) {},
        [&](UnorderedAccess_, CopyDest_) {},
        [&](UnorderedAccess_, CopySource_) {},
        [&](DepthWrite_, Common_) {},
        [&](DepthWrite_, DepthWrite_) {},
        [&](DepthWrite_, DepthRead_) {},
        [&](DepthWrite_, ShaderResource_) {},
        [&](DepthWrite_, CopyDest_) {},
        [&](DepthWrite_, CopySource_) {},
        [&](DepthWrite_, ResolveSource_) {},
        [&](DepthRead_, Common_) {},
        [&](DepthRead_, DepthWrite_) {},
        [&](DepthRead_, DepthRead_) {},
        [&](DepthRead_, ShaderResource_) {},
        [&](DepthRead_, CopyDest_) {},
        [&](DepthRead_, CopySource_) {},
        [&](DepthRead_, ResolveSource_) {},
        [&](ShaderResource_, Common_) {},
        [&](ShaderResource_, RenderTarget_) {},
        [&](ShaderResource_, UnorderedAccess_) {},
        [&](ShaderResource_, DepthWrite_) {},
        [&](ShaderResource_, DepthRead_) {},
        [&](ShaderResource_, ShaderResource_) {},
        [&](ShaderResource_, CopyDest_) {},
        [&](ShaderResource_, CopySource_) {},
        [&](ShaderResource_, ResolveDest_) {},
        [&](ShaderResource_, ResolveSource_) {},
        [&](CopyDest_, auto) {},
        [&](CopySource_, auto) {},
        [&](ResolveDest_, Common_) {},
        [&](ResolveDest_, ShaderResource_) {},
        [&](ResolveDest_, CopyDest_) {},
        [&](ResolveDest_, CopySource_) {},
        [&](ResolveDest_, ResolveDest_) {},
        [&](ResolveDest_, Present_) {},
        [&](ResolveSource_, Common_) {},
        [&](ResolveSource_, RenderTarget_) {},
        [&](ResolveSource_, ShaderResource_) {},
        [&](ResolveSource_, CopyDest_) {},
        [&](ResolveSource_, CopySource_) {},
        [&](ResolveSource_, ResolveSource_) {},
        [&](Present_, RenderTarget_) {},
        [&](Present_, ResolveDest_) {},
        [&](Present_, Present_) {},
        [&](auto s, auto t) {
            throw std::invalid_argument("cannot transit from " + std::to_string(src.index())
                + " to " + std::to_string(dst.index()));
        }
    ), src, dst);
}

void validateRenderTarget(const RenderTargetResource& r) {
    validateResource(r.mResource);

    // TODO: add dsv validation
    visit(overload(
        [&](Device_) {
            if (!isSRGB(r.mResource.mFormat)) {
                if (supportSRGB(r.mResource.mFormat)) {
                    throw std::invalid_argument("resource data is in device color space, format is not (srgb)");
                } else {
                    CONSOLE_COLOR(Yellow);
                    std::cout << "[warning] " << "resource in device color space, format no srgb. should only be used in device render node" << std::endl;
                }
            }
        },
        [&](Linear_) {
            if (isSRGB(r.mResource.mFormat)) {
                throw std::invalid_argument("linear resource should not be in srgb format");
            }
        }
    ), r.mColorSpace);
}

PixelModel validateRenderTargetBinding(const ColorSpace& cs, const RenderTargetResource& rt) {
    PixelModel model;

    visit(overload(
        [&](Device_, Device_) {
            if (isSRGB(rt.mResource.mFormat)) {
                // change srgb to unorm
                model = UNorm;
            } else {
                // format unchanged
                model = getPixelFormat(rt.mResource.mFormat).mModel;
            }
        },
        [&](Device_, Linear_) {
            // format unchanged, format should not be srgb
            model = getPixelFormat(rt.mResource.mFormat).mModel;
            if (std::holds_alternative<SRGB_>(model)) {
                throw std::runtime_error("format should not be SRGB");
            }
            CONSOLE_COLOR(Yellow);
            std::cout << "[warning] " << "resource is linear, render node is device. (should pow 0.454545 in shader)" << std::endl;
        },
        [&](Linear_, Device_) {
            if (isSRGB(rt.mResource.mFormat)) {
                // normal srgb convertion
                model = getPixelFormat(rt.mResource.mFormat).mModel;
                if (!std::holds_alternative<SRGB_>(model)) {
                    throw std::runtime_error("format should be SRGB");
                }
            } else {
                model = getPixelFormat(rt.mResource.mFormat).mModel;
                if (std::holds_alternative<SRGB_>(model)) {
                    throw std::runtime_error("format should not be SRGB");
                }
                CONSOLE_COLOR(Yellow);
                std::cout << "[warning] " << "resource is device but not srgb, render node is linear. (should pow 2.2 in shader)" << std::endl;
            }
        },
        [&](Linear_, Linear_) {
            model = getPixelFormat(rt.mResource.mFormat).mModel;
            if (std::holds_alternative<SRGB_>(model)) {
                throw std::runtime_error("format should not be SRGB");
            }
        }
    ), cs, rt.mColorSpace);

    return model;
}

bool isMSAA(const RenderTargetResource& r) {
    return visit(overload(
        [](const Multisampling&) {
            return true;
        },
        [](std::monostate) {
            return false;
        }
    ), r.mResource.mSampling);
}

void validateResource(const Resource& r) {
    // check array
    visit(overload(
        [&](const ArraySize&) {
            visit(overload(
                [](const ResourceBuffer&) {
                    throw std::invalid_argument("[resource] buffer array not supported");
                },
                [](const Resource3D&) {
                    throw std::invalid_argument("[resource] tex3d array not supported");
                },
                [](auto) {}
            ), r.mDimension);
        },
        [&](std::monostate) {}
    ), r.mArray);
    
    // check msaa
    visit(overload(
        [&](const Resource2D&) {
            // 2D supports msaa
        },
        [&](auto) { // Buffer, 1D, 3D no msaa support
            visit(overload(
                [](const Multisampling&) {
                    throw std::invalid_argument("[resource] only 2D resource supports msaa");
                },
                [](std::monostate) {}
            ), r.mSampling);
        }
    ), r.mDimension);

    // check mipmap
    visit(overload(
        [&](const auto&) {
            visit(overload(
                [](const ResourceBuffer&) {
                    throw std::invalid_argument("[resource] buffer does not support mipmap");
                },
                [](auto) {}
            ), r.mDimension);

            visit(overload(
                [](const Multisampling&) {
                    throw std::invalid_argument("[resource] mipmap resource does not support msaa");
                },
                [](std::monostate) {}
            ), r.mSampling);
        },
        [&](std::monostate) { // no mipmap
            visit(overload(
                [&](const ResourceBuffer&) {
                    // buffer has no mipmap
                },
                [&](auto) { // 1D, 2D, 3D
                    visit(overload(
                        [](const Multisampling&) { // msaa has no mipmap
                        },
                        [](std::monostate) {
                            throw std::invalid_argument("[resource] non-msaa tex must support mipmap");
                        }
                    ), r.mSampling);
                }
            ), r.mDimension);
        }
    ), r.mMipMap);
}

void validateResourceDataView(const Resource& resource, const ResourceDataView& view) {
    visit(overload(
        [&](const BufferView& view) {
            visit(overload(
                [&](const auto&) {
                    throw std::invalid_argument("[view] buffer view, non-buffer resource");
                },
                [&](const ResourceBuffer& buffer) {
                    auto sz = (view.mFirstElement + (uint64_t)view.mNumElements) * view.mStructureByteStride;
                    if (sz > buffer.mWidth)
                        throw std::invalid_argument("[view] view range exceed buffer with");
                }
            ), resource.mDimension);
        },
        [&](const TextureView& view) {
            // check type
            visit(overload(
                [&](const auto& tex) {
                    // check mipmap range
                    if (std::holds_alternative<std::monostate>(view.mMipView)) {
                        throw std::invalid_argument("[view] non-multisampling texture view must have mip view");
                    }
                    visit(overload(
                        [&](const std::monostate&) {
                            visit(overload(
                                [&](const auto& mip, const MipChain& r) {
                                    // no check
                                },
                                [&](const std::monostate& mip, const MipLevels& r) {
                                    // should never reach here
                                    Ensures(false);
                                },
                                [&](const MipChainView& mip, const MipLevels& r) {
                                    if (mip.mMostDetailedMip >= r.mMipLevels)
                                        throw std::invalid_argument("[view] mip view exceed resource mips");
                                },
                                [&](const MipRangeView& mip, const MipLevels& r) {
                                    if (mip.mMostDetailedMip + mip.mMipLevels > r.mMipLevels)
                                        throw std::invalid_argument("[view] mip view range exceed resource mips");
                                },
                                [&](const auto&, const std::monostate&) {
                                    throw std::runtime_error("[view] texture does not has mipmaps");
                                }
                            ), view.mMipView, resource.mMipMap);
                        },
                        [&](const Multisampling& s) {
                            if (!std::holds_alternative<std::monostate>(view.mMipView)) {
                                throw std::invalid_argument("[view] multisampling texture must not have mip view");
                            }
                        }
                    ), resource.mSampling);

                    // check plane
                    auto pixel = getPixelFormat(resource.mFormat);
                    visit(overload(
                        [&](const Interleaved&) {
                            if (std::holds_alternative<PlaneSlice>(view.mPlaneView)) {
                                throw std::invalid_argument("[view] interleaved resource does not support plane view");
                            }
                        },
                        [&](const Planar& p) {
                            uint32_t count = 0;
                            for (int i = 0; i != 4; ++i) {
                                if (p.mChannels[i])
                                    ++count;
                            }

                            visit(overload(
                                [&](G_BR_) {
                                    count = 2;
                                },
                                [&](auto) {}
                            ), pixel.mLayout);

                            visit(overload(
                                [&](const PlaneSlice& plane) {
                                    if (plane.mPlaneSlice >= count) {
                                        throw std::invalid_argument("[view] slice index larger than total plane count");
                                    }
                                },
                                [&](std::monostate) {
                                    throw std::invalid_argument("[view] planar resource must have plane view");
                                }
                            ), view.mPlaneView);

                            visit(overload(
                                [](std::monostate) {},
                                [](const Multisampling&) {
                                    throw std::invalid_argument("[view] multisampling resource does not support planar resource");
                                }
                            ), resource.mSampling);
                        }
                    ), pixel.mMemoryLayout);

                    // check array, depth, cube
                    visit(overload(
                        [&](const auto&) {
                            if (std::holds_alternative<std::monostate>(resource.mArray)) {
                                throw std::invalid_argument("[view] array/depth/cube view is array, resource is not");
                            }
                        },
                        [&](std::monostate) {
                            if (std::holds_alternative<ArraySize>(resource.mArray)) {
                                throw std::invalid_argument("[view] array/depth/cube view is not array, resource is");
                            }
                        }
                    ), view.mArrayOrDepthView);

                    visit(overload(
                        [&](const ArrayRange& range) {
                            const auto& a = std::get<ArraySize>(resource.mArray);
                            if (range.mFirstArraySlice + range.mArraySize >= a.mArraySize) {
                                throw std::invalid_argument("[view] array range exceeded array size");
                            }
                        },
                        [&](const DepthRange& range) {
                            const auto& a = std::get<ArraySize>(resource.mArray);
                            if (range.mFirstWSlice + range.mWSize >= a.mArraySize) {
                                throw std::invalid_argument("[view] depth/w range exceeded array size");
                            }
                        },
                        [&](const CubeSlice&) {
                            const auto& a = std::get<ArraySize>(resource.mArray);
                            if (a.mArraySize < 6) {
                                throw std::invalid_argument("[view] for cube slice, array size should be greater or equal than 6");
                            }
                        },
                        [&](const CubeRange& range) {
                            const auto& a = std::get<ArraySize>(resource.mArray);
                            if ((range.mFirst2DArrayFace + range.mNumCubes) * 6 > a.mArraySize) {
                                throw std::invalid_argument("[view] cube array range exceeded array size");
                            }
                        },
                        [&](std::monostate) {
                        }
                    ), view.mArrayOrDepthView);
                },
                [&](const ResourceBuffer&) {
                    throw std::invalid_argument("[view] texture view, buffer resource");
                }
            ), resource.mDimension);
        },
        [&](const RaytracingView&) {
            throw std::invalid_argument("[view] raytring not supported yet");
        }
    ), view);
}

void validateResourceView(const Resource& resource,
    const ResourceDataView& view, const ResourceViewType& state
) {
    visit(overload(
        [&](const BufferView&) {
            visit(overload(
                [&](SRV_) {
                },
                [&](UAV_) {
                },
                [&](RTV_) {
                },
                [&](auto) {
                    throw std::invalid_argument("[state] buffer view not supported");
                }
            ), state);
        },
        [&](const TextureView& tex) {
            visit(overload(
                [&](SRV_) {
                },
                [&](UAV_) {
                    if (std::holds_alternative<Multisampling>(resource.mSampling) ||
                        std::holds_alternative<std::monostate>(tex.mMipView))
                    {
                        throw std::invalid_argument("[state] uav does not support multisampling or empty mip view");
                    }

                    visit(overload(
                        [](const CubeSlice&) {
                            throw std::invalid_argument("[state] uav does not support cube");
                        },
                        [](const CubeRange&) {
                            throw std::invalid_argument("[state] uav does not support cube");
                        },
                        [](const auto&) {}
                    ), tex.mArrayOrDepthView);
                },
                [&](DSV_) {
                    visit(overload(
                        [](const CubeSlice&) {
                            throw std::invalid_argument("[state] dsv does not support cube");
                        },
                        [](const CubeRange&) {
                            throw std::invalid_argument("[state] dsv does not support cube");
                        },
                        [](const auto&) {}
                    ), tex.mArrayOrDepthView);
                },
                [&](RTV_) {
                    visit(overload(
                        [](const CubeSlice&) {
                            throw std::invalid_argument("[state] rtv does not support cube");
                        },
                        [](const CubeRange&) {
                            throw std::invalid_argument("[state] rtv does not support cube");
                        },
                        [](const auto&) {}
                    ), tex.mArrayOrDepthView);
                }
            ), state);
        },
        [&](const RaytracingView&) {
            throw std::invalid_argument("[state] raytracing view not supported yet");
        }
    ), view);
}

void validateTextureViewState(const Resource& resource, const ResourceDataView& view,
    const TextureViewState& state, const SourceTarget& st, const API& api
) {
    visit(overload(
        [&](Source_) {
            visit(overload(
                [&](Common_) {
                },
                [&](RenderTarget_) {
                    visit(overload(
                        [&](Direct3D_) {
                            throw std::invalid_argument("d3d12 does not support FBF");
                        },
                        [&](Vulkan_) {},
                        [&](Metal_) {}
                    ), api);
                    validateResourceView(resource, view, RTV);
                },
                [&](UnorderedAccess_) {
                    validateResourceView(resource, view, UAV);
                },
                [&](DepthWrite_) {
                    throw std::invalid_argument("DepthWrite_ is output only");
                },
                [&](DepthRead_) {
                    validateResourceView(resource, view, SRV);
                },
                [&](ShaderResource_) {
                    validateResourceView(resource, view, SRV);
                },
                [&](CopyDest_) {
                    throw std::invalid_argument("source cannot be copy dest");
                },
                [&](CopySource_) {

                },
                [&](ResolveDest_) {
                    throw std::invalid_argument("siource cannot be resolve dest");
                },
                [&](ResolveSource_) {
                    if (std::holds_alternative<std::monostate>(resource.mSampling)) {
                        throw std::invalid_argument("only ms texture supports Resolve Source");
                    }
                },
                [&](Present_) {
                    throw std::invalid_argument("Present_ is output only");
                }
            ), state);
        },
        [&](Target_) {
            visit(overload(
                [&](Common_) {
                },
                [&](RenderTarget_) {
                    validateResourceView(resource, view, RTV);
                },
                [&](UnorderedAccess_) {
                    throw std::invalid_argument("UnorderedAccess_ is input only");
                },
                [&](DepthWrite_) {
                    validateResourceView(resource, view, DSV);
                },
                [&](DepthRead_) {
                    validateResourceView(resource, view, DSV);
                },
                [&](ShaderResource_) {
                    throw std::invalid_argument("ShaderResource_ is input only");
                },
                [&](CopyDest_) {

                },
                [&](CopySource_) {
                    throw std::invalid_argument("target cannot be copy source");
                },
                [&](ResolveDest_) {
                    if (std::holds_alternative<Multisampling>(resource.mSampling)) {
                        throw std::invalid_argument("only plain texture supports Resolve Target");
                    }
                },
                [&](ResolveSource_) {
                    throw std::invalid_argument("target cannot be resolve source");
                },
                [&](Present_) {
                }
            ), state);
        }
    ), st);
}

void validateRenderValue(const Resource& resource, const RenderValue& v,
    const SourceTarget& st, const API& api
) {
    validateResourceDataView(resource, v.mData);
    validateTextureViewState(resource, v.mData, v.mState, st, api);

    visit(overload(
        [](ClearColor, RenderTarget_) {
        },
        [](ClearColor, ResolveDest_) {
        },
        [](ClearColor, auto) {
            throw std::invalid_argument("Only RTV_, Resolve_ supports ClearColor");
        },
        [](ClearDepthStencil, DepthWrite_) {
        },
        [](ClearDepthStencil, DepthRead_) {
            throw std::invalid_argument("Cannot clear depth stencil when DepthRead");
        },
        [](ClearDepthStencil, auto) {
            throw std::invalid_argument("Only DSV_ supports ClearDepthStencil");
        },
        [](auto, auto) {
        }
    ), v.mLoadOp, v.mState);

    visit(overload(
        [](Present_, Discard_) {
            throw std::invalid_argument("present rt should not be marked as discard");
        },
        [](auto, auto) {}
    ), v.mState, v.mStoreOp);
}

// utils
std::ostream& operator<<(std::ostream& oss, const ResourceDataView& view) {
    visit(overload(
        [&](const BufferView& buffer) {
            oss << "[buffer: (" << buffer.mFirstElement << ", " << buffer.mNumElements << ")]";
        },
        [&](const TextureView& tex) {
            oss << "[texture";

            visit(overload(
                [&](const MipChainView& m) {
                    oss << ": mip chain(" << m.mMostDetailedMip << ")";
                },
                [&](const MipRangeView& m) {
                    if (m.mMipLevels == 1) {
                        oss << ": mip slice(" << m.mMostDetailedMip << ")";
                    } else {
                        oss << ": mip range(" << m.mMostDetailedMip << ", " << m.mMipLevels << ")";
                    }
                },
                [&](const std::monostate& m) {
                    oss << ": mip default";
                }
            ), tex.mMipView);

            visit(overload(
                [&](const PlaneSlice& p) {
                    oss << ", plane(" << p.mPlaneSlice << ")";
                },
                [&](const std::monostate&) {
                }
            ), tex.mPlaneView);

            visit(overload(
                [&](const ArrayRange& a) {
                    oss << ", array(" << a.mFirstArraySlice << ", " << a.mArraySize << ")";
                },
                [&](const DepthRange& a) {
                    oss << ", depth(" << a.mFirstWSlice << ", " << a.mWSize << ")";
                },
                [&](const CubeSlice& a) {
                    oss << ", cube";
                },
                [&](const CubeRange& a) {
                    oss << ", cube array(" << a.mFirst2DArrayFace << ", " << a.mNumCubes<< ")";
                },
                [&](const std::monostate&) {
                }
            ), tex.mArrayOrDepthView);

            oss << "]";
        },
        [&](const RaytracingView& ray) {
            oss << "[raytracing]";
        }
    ), view);

    return oss;
}

std::ostream& operator<<(std::ostream& oss, const PixelModel& view) {
    visit(overload(
        [&](const auto&v) {
            oss << getName(v);
        }
    ), view);

    return oss;
}

std::ostream& operator<<(std::ostream& oss, const ShaderDescriptorType& view) {
    visit(overload(
        [&](const auto& v) {
            oss << getName(v);
        }
    ), view);

    return oss;
}

RESOURCE_DESC buildResourceDesc(const Resource& resource) {
    RESOURCE_DESC desc{};
    desc.mDimension = getDimension(resource.mDimension);
    visit(overload(
        [&](const ResourceBuffer& buffer) {
            desc.mWidth = buffer.mWidth;
            desc.mHeight = 1;
            desc.mDepthOrArraySize = 1;
        },
        [&](const Resource1D& tex) {
            desc.mWidth = tex.mWidth;
            desc.mHeight = 1;

            visit(overload(
                [&](const ArraySize& a) {
                    desc.mDepthOrArraySize = a.mArraySize;
                },
                [&](std::monostate) {
                    desc.mDepthOrArraySize = 1;
                }
            ), resource.mArray);
        },
        [&](const Resource2D& tex) {
            desc.mWidth = tex.mWidth;
            desc.mHeight = tex.mHeight;

            visit(overload(
                [&](const ArraySize& a) {
                    desc.mDepthOrArraySize = a.mArraySize;
                },
                [&](std::monostate) {
                    desc.mDepthOrArraySize = 1;
                }
            ), resource.mArray);
        },
        [&](const Resource3D& tex) {
            desc.mWidth = tex.mWidth;
            desc.mHeight = tex.mHeight;
            desc.mDepthOrArraySize = tex.mDepthSize;
        }
    ), resource.mDimension);

    visit(overload(
        [&](const ResourceBuffer& buffer) {
            desc.mMipLevels = 1;
        },
        [&](const auto& tex) {
            visit(overload(
                [&](const MipChain& m) {
                    desc.mMipLevels = 0;
                },
                [&](const MipLevels& m) {
                    desc.mMipLevels = m.mMipLevels;
                },
                [&](std::monostate) {
                    desc.mMipLevels = 1;
                }
            ), resource.mMipMap);
        }
    ), resource.mDimension);

    desc.mFormat = resource.mFormat;

    visit(overload(
        [&](const ResourceBuffer& buffer) {
            desc.mSampleDesc = { 1u, 0u };
        },
        [&](const Resource2D& tex) {
            visit(overload(
                [&](const Multisampling& s) {
                    desc.mSampleDesc = { s.mCount, s.mQuality };
                },
                [&](std::monostate) {
                    desc.mSampleDesc = { 1u, 0u };
                }
            ), resource.mSampling);
        },
        [&](const auto& tex) {
            desc.mSampleDesc = { 1u, 0u };
        }
    ), resource.mDimension);

    visit(overload(
        [&](const ResourceBuffer& buffer) {
            desc.mLayout = TEXTURE_LAYOUT_ROW_MAJOR;
        },
        [&](const auto&) {
            visit(overload(
                [&](RowMajor_) {
                    desc.mLayout = TEXTURE_LAYOUT_ROW_MAJOR;
                },
                [&](UndefinedSwizzle64KB_) {
                    desc.mLayout = TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE;
                },
                [&](StandardSwizzle64KB_) {
                    desc.mLayout = TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE;
                },
                [&](std::monostate) {
                    desc.mLayout = TEXTURE_LAYOUT_UNKNOWN;
                }
            ), resource.mLayout);
        }
    ), resource.mDimension);

    return desc;
}

RENDER_TARGET_VIEW_DESC buildRenderTargetViewDesc(
    const Resource& resource,
    const ResourceDataView& view,
    const PixelModel& viewModel
) {
    RENDER_TARGET_VIEW_DESC desc{};

    auto pixel = getPixelFormat(resource.mFormat);
    if (viewModel != pixel.mModel) {
        visit(overload(
            [&](const SRGB_&, const UNorm_&) {
                desc.mFormat = makeUNormSRGB(resource.mFormat);
            },
            [&](const UNorm_&, const SRGB_&) {
                desc.mFormat = makeTypelessUNorm(makeTypeless(resource.mFormat));
            },
            [](const auto&, const auto&) {
                throw std::runtime_error("format convertion not supported");
            }
        ), viewModel, pixel.mModel);
    } else {
        desc.mFormat = resource.mFormat;
    }

    visit(overload(
        [&](const BufferView& buffer) {
            desc.mViewDimension = RTV_DIMENSION_BUFFER;
            desc.mBuffer = BUFFER_RTV{ buffer.mFirstElement, buffer.mNumElements };
        },
        [&](const TextureView& tex) {
            // mip slice
            uint32_t slice = 0;
            visit(overload(
                [&](std::monostate) {
                    if (std::holds_alternative<std::monostate>(resource.mSampling))
                        throw std::runtime_error("mip default view not supported");
                },
                [&](const MipChainView&) {
                    throw std::runtime_error("mip chain view not supported");
                },
                [&](const MipRangeView& m) {
                    if (m.mMipLevels != 1)
                        throw std::runtime_error("not mip slice view");
                    slice = m.mMostDetailedMip;
                }
            ), tex.mMipView);

            visit(overload(
                [&](const ResourceBuffer& buffer) {
                    throw std::runtime_error("resource is buffer");
                },
                [&](const Resource1D&) {
                    visit(overload(
                        [&](std::monostate a) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE1D;
                            desc.mTexture1D = TEX1D_RTV{ slice };
                        },
                        [&](const ArrayRange& a) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE1DARRAY;
                            desc.mTexture1DArray = TEX1D_ARRAY_RTV{
                                slice, a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](auto) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView);
                },
                [&](const Resource2D&) {
                    uint32_t plane = 0;
                    visit(overload(
                        [&](std::monostate) {},
                        [&](const PlaneSlice& p) {
                            plane = p.mPlaneSlice;
                        }
                    ), tex.mPlaneView);

                    visit(overload(
                        [&](std::monostate a, std::monostate) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE2D;
                            desc.mTexture2D = TEX2D_RTV{ slice, plane };
                        },
                        [&](const ArrayRange& a, std::monostate) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE2DARRAY;
                            desc.mTexture2DArray = TEX2D_ARRAY_RTV{
                                slice, a.mFirstArraySlice, a.mArraySize, plane
                            };
                        },
                        [&](std::monostate a, const Multisampling&) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE2DMS;
                            desc.mTexture2DMS = TEX2DMS_RTV{};
                        },
                        [&](const ArrayRange& a, const Multisampling&) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE2DMSARRAY;
                            desc.mTexture2DMSArray = TEX2DMS_ARRAY_RTV{
                                a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](const auto&, const auto&) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView, resource.mSampling);
                },
                [&](const Resource3D&) {
                    visit(overload(
                        [&](const DepthRange& a) {
                            desc.mViewDimension = RTV_DIMENSION_TEXTURE3D;
                            desc.mTexture3D = TEX3D_RTV{
                                slice, a.mFirstWSlice, a.mWSize
                            };
                        },
                        [&](auto) {
                            throw std::runtime_error("only depth range supported");
                        }
                    ), tex.mArrayOrDepthView);
                }
            ), resource.mDimension);
        },
        [&](const RaytracingView& ray) {
            throw std::runtime_error("ray tracing not supported in rtv");
        }
    ), view);

    return desc;
}

DEPTH_STENCIL_VIEW_DESC buildDepthStencilViewDesc(
    const Resource& resource,
    const ResourceDataView& view,
    bool bReadOnly
) {
    DEPTH_STENCIL_VIEW_DESC desc = { resource.mFormat };
    if (bReadOnly) {
        desc.mFlags = static_cast<DSV_FLAGS>(DSV_FLAG_READ_ONLY_DEPTH | DSV_FLAG_READ_ONLY_STENCIL);
    } else {
        desc.mFlags = DSV_FLAG_NONE;
    }
    visit(overload(
        [&](const BufferView& buffer) {
            throw std::runtime_error("buffer not supported in dsv");
        },
        [&](const TextureView& tex) {
            // mip slice
            uint32_t slice = 0;
            visit(overload(
                [&](std::monostate) {
                    if (std::holds_alternative<std::monostate>(resource.mSampling))
                        throw std::runtime_error("mip default view not supported");
                },
                [&](const MipChainView&) {
                    throw std::runtime_error("mip chain view not supported");
                },
                [&](const MipRangeView& m) {
                    if (m.mMipLevels != 1)
                        throw std::runtime_error("not mip slice view");
                    slice = m.mMostDetailedMip;
                }
            ), tex.mMipView);

            visit(overload(
                [&](const ResourceBuffer& buffer) {
                    throw std::runtime_error("resource is buffer");
                },
                [&](const Resource1D&) {
                    visit(overload(
                        [&](std::monostate a) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE1D;
                            desc.mTexture1D = TEX1D_DSV{ slice };
                        },
                        [&](const ArrayRange& a) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE1DARRAY;
                            desc.mTexture1DArray = TEX1D_ARRAY_DSV{
                                slice, a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](auto) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView);
                },
                [&](const Resource2D&) {
                    visit(overload(
                        [&](std::monostate a, std::monostate) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE2D;
                            desc.mTexture2D = TEX2D_DSV{ slice };
                        },
                        [&](const ArrayRange& a, std::monostate) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE2DARRAY;
                            desc.mTexture2DArray = TEX2D_ARRAY_DSV{
                                slice, a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](std::monostate a, const Multisampling&) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE2DMS;
                            desc.mTexture2DMS = TEX2DMS_DSV{};
                        },
                        [&](const ArrayRange& a, const Multisampling&) {
                            desc.mViewDimension = DSV_DIMENSION_TEXTURE2DMSARRAY;
                            desc.mTexture2DMSArray = TEX2DMS_ARRAY_DSV{
                                a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](const auto&, const auto&) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView, resource.mSampling);
                },
                [&](const Resource3D&) {
                    throw std::runtime_error("texture3d not supported");
                }
            ), resource.mDimension);
        },
        [&](const RaytracingView& ray) {
            throw std::runtime_error("ray tracing not supported in rtv");
        }
    ), view);

    return desc;
}

SHADER_RESOURCE_VIEW_DESC buildShaderResourceViewDesc(
    const Resource& resource,
    const ResourceDataView& view,
    const PixelModel& viewModel
) {
    SHADER_RESOURCE_VIEW_DESC desc{};
    auto format = makeTypeless(resource.mFormat);
    auto pixel = getPixelFormat(resource.mFormat);

    visit(overload(
        [&](SNorm_) {
            desc.mFormat = makeTypelessSNorm(format);
        },
        [&](UNorm_) {
            desc.mFormat = makeTypelessUNorm(format);
        },
        [&](SRGB_) {
            desc.mFormat = makeTypelessSRGB(format);
        },
        [&](UFloat_) {
            desc.mFormat = makeTypelessUFloat(format);
        },
        [&](SFloat_) {
            desc.mFormat = makeTypelessSFloat(format);
        },
        [&](UInt_) {
            desc.mFormat = makeTypelessUInt(format);
        },
        [](auto) {}
    ), pixel.mModel);

    visit(overload(
        [&](const BufferView& buffer) {
            desc.mViewDimension = SRV_DIMENSION_BUFFER;
            desc.mBuffer = BUFFER_SRV{ buffer.mFirstElement, buffer.mNumElements };
        },
        [&](const TextureView& tex) {
            // mip slice
            uint32_t mostDetailedMip = 0;
            uint32_t mipLevels = 0;
            float resourceMinLODClamp = 0.0f;

            visit(overload(
                [&](std::monostate) {
                },
                [&](const MipChainView& m) {
                    mostDetailedMip = m.mMostDetailedMip;
                    resourceMinLODClamp = m.mResourceMinLODClamp;
                },
                [&](const MipRangeView& m) {
                    mostDetailedMip = m.mMostDetailedMip;
                    mipLevels = m.mMipLevels;
                    resourceMinLODClamp = m.mResourceMinLODClamp;
                }
            ), tex.mMipView);

            desc.mShader4ComponentMapping = 0x1688; // D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING

            visit(overload(
                [&](const ResourceBuffer& buffer) {
                    throw std::runtime_error("resource is buffer");
                },
                [&](const Resource1D&) {
                    visit(overload(
                        [&](std::monostate a) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE1D;
                            desc.mTexture1D = TEX1D_SRV{ mostDetailedMip, mipLevels, resourceMinLODClamp };
                        },
                        [&](const ArrayRange& a) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE1DARRAY;
                            desc.mTexture1DArray = TEX1D_ARRAY_SRV{
                                mostDetailedMip, mipLevels, a.mFirstArraySlice, a.mArraySize, resourceMinLODClamp
                            };
                        },
                        [&](auto) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView);
                },
                [&](const Resource2D&) {
                    uint32_t plane = 0;
                    visit(overload(
                        [&](std::monostate) {},
                        [&](const PlaneSlice& p) {
                            plane = p.mPlaneSlice;
                        }
                    ), tex.mPlaneView);

                    visit(overload(
                        [&](std::monostate a, std::monostate) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE2D;
                            desc.mTexture2D = TEX2D_SRV{
                                mostDetailedMip, mipLevels, plane, resourceMinLODClamp
                            };
                        },
                        [&](const ArrayRange& a, std::monostate) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE2DARRAY;
                            desc.mTexture2DArray = TEX2D_ARRAY_SRV{
                                mostDetailedMip, mipLevels, a.mFirstArraySlice, a.mArraySize, plane, resourceMinLODClamp
                            };
                        },
                        [&](std::monostate a, const Multisampling&) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE2DMS;
                            desc.mTexture2DMS = TEX2DMS_SRV{};
                        },
                        [&](const ArrayRange& a, const Multisampling&) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE2DMSARRAY;
                            desc.mTexture2DMSArray = TEX2DMS_ARRAY_SRV{
                                a.mFirstArraySlice, a.mArraySize
                            };
                        },
                        [&](const CubeSlice& a, std::monostate) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURECUBE;
                            desc.mTextureCube = TEXCUBE_SRV{
                                mostDetailedMip, mipLevels, resourceMinLODClamp
                            };
                        },
                        [&](const CubeRange& a, std::monostate) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURECUBEARRAY;
                            desc.mTextureCubeArray = TEXCUBE_ARRAY_SRV{
                                mostDetailedMip, mipLevels, a.mFirst2DArrayFace, a.mNumCubes, resourceMinLODClamp
                            };
                        },
                        [&](const auto&, const auto&) {
                            throw std::runtime_error("depth range, cube slice, cube range not supported");
                        }
                    ), tex.mArrayOrDepthView, resource.mSampling);
                },
                [&](const Resource3D&) {
                    visit(overload(
                        [&](const DepthRange& a) {
                            desc.mViewDimension = SRV_DIMENSION_TEXTURE3D;
                            desc.mTexture3D = TEX3D_SRV{
                                mostDetailedMip, mipLevels, resourceMinLODClamp
                            };
                        },
                        [&](auto) {
                            throw std::runtime_error("only depth range supported");
                        }
                    ), tex.mArrayOrDepthView);
                }
            ), resource.mDimension);
        },
        [&](const RaytracingView& ray) {
            throw std::runtime_error("ray tracing not supported in rtv");
        }
    ), view);

    return desc;
}

}

}

}
