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

#include "SShaderAttribute.h"
#include <StarCompiler/SMathNames.h>
#include <StarCompiler/ShaderGraph/SShaderNames.h>
#include "SShaderDescriptor.h"

namespace Star::Graphics::Render::Shader {

namespace {

struct AttributeDescriptorTypeVisitor {
    template<class Scalar, int Rows, int Cols>
    DescriptorType operator()(const Eigen::Matrix<Scalar, Rows, Cols>& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const float& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const uint32_t& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const int32_t& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const half& v) const noexcept {
        return CBV;
    }

    DescriptorType operator()(const FloatRange& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const HalfRange& v) const noexcept {
        return CBV;
    }

    DescriptorType operator()(const InputPatch_& v) const {
        throw std::invalid_argument("InputPatch not supported");
    }
    DescriptorType operator()(const OutputPatch_& v) const {
        throw std::invalid_argument("OutputPatch not supported");
    }

    DescriptorType operator()(const CBuffer_& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const Buffer_& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const ByteAddressBuffer_& v) const noexcept {
        return CBV;
    }
    DescriptorType operator()(const StructuredBuffer_& v) const noexcept {
        return CBV;
    }

    DescriptorType operator()(const Texture1D_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture1DArray_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture2D_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture2DArray_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture2DMS_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture2DMSArray_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const Texture3D_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const TextureCube_& v) const noexcept {
        return SRV;
    }
    DescriptorType operator()(const TextureCubeArray_& v) const noexcept {
        return SRV;
    }

    template<class T>
    DescriptorType operator()(const T& v) const noexcept {
        return UAV;
    }

    DescriptorType operator()(const SamplerState_& v) const noexcept {
        return SSV;
    }
};

}

RootParameterType getRootParameterType(const ShaderAttribute& attr) {
    return attr.mDescriptor.mRootParameterType;
}

DescriptorType getDescriptorType(const ShaderAttribute& attr) {
    AttributeDescriptorTypeVisitor visitor;
    return visit(visitor, attr.mType);
}

TextureView getTextureView(const ShaderAttribute& attr) {
    return visit(overload(
        [&](Texture1D_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    return TextureView{ MipRangeView{ 0, 1 } };
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture1DArray_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    throw std::invalid_argument("shader attribute array size must be specified");
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture2D_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    return TextureView{ MipRangeView{ 0, 1 } };
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture2DArray_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    throw std::invalid_argument("shader attribute array size must be specified");
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture2DMS_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    return TextureView{ MipRangeView{ 0, 1 } };
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture2DMSArray_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    throw std::invalid_argument("shader attribute array size must be specified");
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](Texture3D_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    throw std::invalid_argument("shader attribute depth size must be specified");
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](TextureCube_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    return TextureView{ MipRangeView{ 0, 1 }, PlaneView{}, CubeSlice{} };
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](TextureCubeArray_) {
            return visit(overload(
                [&](DefaultView_) -> TextureView {
                    throw std::invalid_argument("shader attribute cube array size must be specified");
                },
                [&](const TextureView& view) {
                    return view;
                }
            ), attr.mData);
        },
        [&](auto) -> TextureView {
            throw std::invalid_argument("shader attribute is not srv: " + attr.mName);
        }
    ), attr.mType);
}

void validate(const ShaderAttribute& attr) {
    if (attr.mFlags & RootConstant) {
        auto type = getDescriptorType(attr);
        if (!std::holds_alternative<CBV_>(type)) {
            throw std::invalid_argument("only cbv can be root constant");
        }
        if (attr.mFlags & UnboundedSize) {
            throw std::invalid_argument("unbounded resource cannot be root constant");
        }
    }
}

void validate(const AttributeUsage& usage) {

}

void merge(const AttributeUsageMap& src, AttributeUsageMap& dst) {
    for (const auto& attr : src) {
        dst.emplace(attr);
    }
}

const char* getName(const AttributeType& attr) noexcept {
    return visit(overload(
        [&](const auto& v) {
            using namespace Star;
            return getName(v);
        }
    ), attr);
}

const char* getHLSLName(const AttributeType& attr) noexcept {
    return visit(overload(
#define FOR_NAME_ELEM(r, __, i, NAME) [&](const BOOST_PP_CAT(NAME, _)&) { return BOOST_PP_STRINGIZE(NAME); },
#define FOR_NAME(...) BOOST_PP_SEQ_FOR_EACH_I(FOR_NAME_ELEM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))
        FOR_NAME(matrix, float4, uint4, int4, float2, uint2, int2, half4, half2, fixed4, float1, uint1, int1, half1)
#undef FOR_NAME
#undef FOR_NAME_ELEM
        [&](const auto& v) {
            using namespace Star;
            return getName(v);
        }
    ), attr);
}

void compileShaderAttribute(ShaderAttribute& attr) {
    attr.mDescriptor.mDescriptorType = getDescriptorType(attr);
    attr.mDescriptor.mName = attr.mName;
}

bool isConstant(const ShaderAttribute& attr) {
    IsConstant visitor;
    return visit(visitor, attr.mType);
}

DescriptorIndex getDescriptorIndex(const AttributeDescriptor& d, ShaderVisibilityType vis) {
    return DescriptorIndex{
        d.mUpdate,
        d.mRootParameterType,
        vis,
        d.mPersistency,
    };
}

uint32_t getDescriptorCapacity(const ShaderAttribute& attr) {
    uint32_t capacity = 0;
    visit(overload(
        [&](DefaultView_) {
            capacity += 1;
        },
        [&](const TextureView& view) {
            uint32_t sz = 0;
            visit(overload(
                [&](std::monostate) {
                    sz = 1;
                },
                [&](const ArrayRange& range) {
                    sz = range.mArraySize;
                },
                [&](const DepthRange& range) {
                    sz = 1;
                },
                [&](const CubeSlice& range) {
                    sz = 1;
                },
                [&](const CubeRange& range) {
                    sz = range.mNumCubes;
                }
            ), view.mArrayOrDepthView);
            capacity += sz;
        }
    ), attr.mData);
    return capacity;
}

uint32_t getDescriptorCapacity(const DescriptorRange& range) {
    uint32_t capacity = 0;
    for (const auto& [source, subrange] : range.mSubranges) {
        for (const auto& attr : subrange.mAttributes) {
            capacity += getDescriptorCapacity(attr);
        }
    }
    return capacity;
}

AttributeMap getAttributes(const AttributeMap& attrs, const AttributeUsageMap& usages) {
    AttributeMap result;
    for (const auto& usage : usages) {
        auto iter = attrs.find(get_key(usage));
        if (iter == attrs.end()) {
            throw std::invalid_argument("attribute: " + usage.mName + " not found");
        }
        result.emplace(*iter);
    }
    return result;
}

}
