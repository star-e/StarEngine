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

struct AttributeDescriptorVisitor {
    const ShaderAttribute& mAttribute;
    uint32_t mSpace = 0;

    template<class Scalar, int Rows, int Cols>
    Descriptor operator()(const Eigen::Matrix<Scalar, Rows, Cols>& v) {
        throw std::invalid_argument("constants not supported");
    }

    Descriptor operator()(const FloatRange& v) {
        throw std::invalid_argument("FloatRange not supported");
    }
    Descriptor operator()(const HalfRange& v) {
        throw std::invalid_argument("HalfRange not supported");
    }

    Descriptor operator()(const InputPatch_& v) {
        throw std::invalid_argument("InputPatch not supported");
    }
    Descriptor operator()(const OutputPatch_& v) {
        throw std::invalid_argument("OutputPatch not supported");
    }

    Descriptor operator()(const ConstantBuffer_& v) {
        DescriptorCBV model = (mAttribute.mFlags & Unbounded) ? DescriptorCBV{ RangeUnbounded() } : v;
        return Descriptor{ CBV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Buffer_& v) {
        DescriptorCBV model = (mAttribute.mFlags & Unbounded) ? DescriptorCBV{ RangeUnbounded() } : v;
        return Descriptor{ CBV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const ByteAddressBuffer_& v) {
        DescriptorCBV model = (mAttribute.mFlags & Unbounded) ? DescriptorCBV{ RangeUnbounded() } : v;
        return Descriptor{ CBV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const StructuredBuffer_& v) {
        DescriptorCBV model = (mAttribute.mFlags & Unbounded) ? DescriptorCBV{ RangeUnbounded() } : v;
        return Descriptor{ CBV, mSpace, model, mAttribute.mName };
    }

    Descriptor operator()(const Texture1D_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture1DArray_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture2D_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture2DArray_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture2DMS_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture2DMSArray_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const Texture3D_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const TextureCube_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }
    Descriptor operator()(const TextureCubeArray_& v) {
        DescriptorSRV model = (mAttribute.mFlags & Unbounded) ? DescriptorSRV{ RangeUnbounded() } : v;
        return Descriptor{ SRV, mSpace, model, mAttribute.mName };
    }

    template<class T>
    Descriptor operator()(const T& v) {
        DescriptorUAV model = (mAttribute.mFlags & Unbounded) ? DescriptorUAV{ RangeUnbounded() } : v;
        return Descriptor{ UAV, mSpace, model, mAttribute.mName };
    }

    Descriptor operator()(const SamplerState_& v) {
        return Descriptor{ SSV, mSpace, v, mAttribute.mName };
    }
};

struct AttributeDescriptorTypeVisitor {
    const ShaderAttribute& mAttribute;
    uint32_t mSpace = 0;

    template<class Scalar, int Rows, int Cols>
    DescriptorType operator()(const Eigen::Matrix<Scalar, Rows, Cols>& v) {
        return CBV;
    }

    DescriptorType operator()(const FloatRange& v) {
        return CBV;
    }
    DescriptorType operator()(const HalfRange& v) {
        return CBV;
    }

    DescriptorType operator()(const InputPatch_& v) {
        throw std::invalid_argument("InputPatch not supported");
    }
    DescriptorType operator()(const OutputPatch_& v) {
        throw std::invalid_argument("OutputPatch not supported");
    }

    DescriptorType operator()(const ConstantBuffer_& v) {
        return CBV;
    }
    DescriptorType operator()(const Buffer_& v) {
        return CBV;
    }
    DescriptorType operator()(const ByteAddressBuffer_& v) {
        return CBV;
    }
    DescriptorType operator()(const StructuredBuffer_& v) {
        return CBV;
    }

    DescriptorType operator()(const Texture1D_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture1DArray_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture2D_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture2DArray_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture2DMS_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture2DMSArray_& v) {
        return SRV;
    }
    DescriptorType operator()(const Texture3D_& v) {
        return SRV;
    }
    DescriptorType operator()(const TextureCube_& v) {
        return SRV;
    }
    DescriptorType operator()(const TextureCubeArray_& v) {
        return SRV;
    }

    template<class T>
    DescriptorType operator()(const T& v) {
        return UAV;
    }

    DescriptorType operator()(const SamplerState_& v) {
        return SSV;
    }
};

}

RootSignatureType getRootSignatureType(const ShaderAttribute& attr) {
    auto type = getDescriptorType(attr);

    return visit(overload(
        [&](CBV_) -> RootSignatureType {
            if (attr.mFlags & RootConstant) {
                return Constants;
            } else if (attr.mFlags & RootLevel) {
                return CBV;
            } else {
                return Table;
            }
        },
        [&](auto v) -> RootSignatureType {
            if (attr.mFlags & RootLevel) {
                return v;
            } else {
                return Table;
            }
        }
    ), type);
}

DescriptorType getDescriptorType(const ShaderAttribute& attr) {
    AttributeDescriptorTypeVisitor visitor{ attr, 0 };
    return visit(visitor, attr.mType);
}

Descriptor getDescriptor(const ShaderAttribute& attr, uint32_t space) {
    AttributeDescriptorVisitor visitor{ attr, space };
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
        if (attr.mFlags & Unbounded) {
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
#define FOR_NAME_ELEM(r, _, i, NAME) [&](const NAME&) { return BOOST_PP_STRINGIZE(NAME); },
#define FOR_NAME(...) BOOST_PP_SEQ_FOR_EACH_I(FOR_NAME_ELEM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))
        FOR_NAME(matrix, float4, uint4, int4, float2, uint2, int2, half4, half2, fixed4)
#undef FOR_NAME
#undef FOR_NAME_ELEM
        [&](const float1&) {
            return "float";
        },
        [&](const uint1&) {
            return "uint";
        },
        [&](const int1&) {
            return "int";
        },
        [&](const half1&) {
            return "half";
        },
        [&](const auto& v) {
            using namespace Star;
            return getName(v);
        }
    ), attr);
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
