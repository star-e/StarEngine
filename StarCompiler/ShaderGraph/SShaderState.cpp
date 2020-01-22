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

#include "SShaderState.h"

namespace Star::Graphics::Render::Shader {

BLEND_DESC getRenderType(const BlendState& blend) noexcept {
    BLEND_DESC desc;
    desc.mAlphaToCoverageEnable = blend.mAlphaToCoverageEnable;
    desc.mIndependentBlendEnable = blend.mRenderTargets.size() > 1;

    if (blend.mRenderTargets.empty()) {
        auto& rt = desc.mRenderTarget[0];
        rt.mBlendEnable = false;
        rt.mLogicOpEnable = false;
        rt.mSrcBlend = BLEND_ONE;
        rt.mDestBlend = BLEND_ZERO;
        rt.mBlendOp = BLEND_OP_ADD;
        rt.mSrcBlendAlpha = BLEND_ONE;
        rt.mDestBlendAlpha = BLEND_ZERO;
        rt.mBlendOpAlpha = BLEND_OP_ADD;
        rt.mLogicOp = LOGIC_OP_NOOP;
        rt.mRenderTargetWriteMask = COLOR_WRITE_ENABLE_ALL;
    }

    for (size_t i = 0; i != blend.mRenderTargets.size(); ++i) {
        auto& dst = desc.mRenderTarget[i];
        const auto& src = blend.mRenderTargets[i];

        dst.mBlendEnable = true;
        visit(overload(
            [&](NoOp_) {
                dst.mLogicOpEnable = false;
            },
            [&](auto) {
                dst.mLogicOpEnable = true;
            }
        ), src.mLogicOp);
        
        auto blendSetter = overload(
            [](Zero_) { return BLEND_ZERO; },
            [](One_) { return BLEND_ONE; },
            [](SrcColor_) { return BLEND_SRC_COLOR; },
            [](InvSrcColor_) { return BLEND_INV_SRC_COLOR; },
            [](SrcAlpha_) { return BLEND_SRC_ALPHA; },
            [](InvSrcAlpha_) { return BLEND_INV_SRC_ALPHA; },
            [](DstAlpha_) { return BLEND_DEST_ALPHA; },
            [](InvDstAlpha_) { return BLEND_INV_DEST_ALPHA; },
            [](DstColor_) { return BLEND_DEST_COLOR; },
            [](InvDstColor_) { return BLEND_INV_DEST_COLOR; },
            [](SrcAlphaSat_) { return BLEND_SRC_ALPHA_SAT; },
            [](BlendFactor_) { return BLEND_BLEND_FACTOR; },
            [](InvBlendFactor_) { return BLEND_INV_BLEND_FACTOR; },
            [](Src1Color_) { return BLEND_SRC1_COLOR; },
            [](InvSrc1Color_) { return BLEND_INV_SRC1_COLOR; },
            [](Src1Alpha_) { return BLEND_SRC1_ALPHA; },
            [](InvSrc1Alpha_) { return BLEND_INV_SRC1_ALPHA; }
        );

        auto blendOpSetter = overload(
            [](Add_) { return BLEND_OP_ADD; },
            [](Subtract_) { return BLEND_OP_SUBTRACT; },
            [](RevSubtract_) { return BLEND_OP_REV_SUBTRACT; },
            [](Min_) { return BLEND_OP_MIN; },
            [](Max_) { return BLEND_OP_MAX; }
        );

        dst.mSrcBlend = visit(blendSetter, src.mSrcBlend);
        dst.mDestBlend = visit(blendSetter, src.mDstBlend);
        dst.mBlendOp = visit(blendOpSetter, src.mBlendOp);

        dst.mSrcBlendAlpha = visit(blendSetter, src.mSrcBlendAlpha);
        dst.mDestBlendAlpha = visit(blendSetter, src.mDstBlendAlpha);
        dst.mBlendOpAlpha = visit(blendOpSetter, src.mBlendOpAlpha);

        dst.mLogicOp = visit(overload(
            [](Clear_) { return LOGIC_OP_CLEAR; },
            [](Set_) { return LOGIC_OP_SET; },
            [](Copy_) { return LOGIC_OP_COPY; },
            [](CopyInverted_) { return LOGIC_OP_COPY_INVERTED; },
            [](NoOp_) { return LOGIC_OP_NOOP; },
            [](Invert_) { return LOGIC_OP_INVERT; },
            [](And_) { return LOGIC_OP_AND; },
            [](Nand_) { return LOGIC_OP_NAND; },
            [](Or_) { return LOGIC_OP_OR; },
            [](Nor_) { return LOGIC_OP_NOR; },
            [](Xor_) { return LOGIC_OP_XOR; },
            [](Equiv_) { return LOGIC_OP_EQUIV; },
            [](AndReverse_) { return LOGIC_OP_AND_REVERSE; },
            [](AndInverted_) { return LOGIC_OP_AND_INVERTED; },
            [](OrReverse_) { return LOGIC_OP_OR_REVERSE; },
            [](OrInverted_) { return LOGIC_OP_OR_INVERTED; }
        ), src.mLogicOp);

        dst.mRenderTargetWriteMask = src.mRenderTargetWriteMask;
    }

    return desc;
}

RASTERIZER_DESC getRenderType(const RasterizerState& rs) noexcept {
    RASTERIZER_DESC desc;
    desc.mFillMode = visit(overload(
        [](Wireframe_) { return FILL_MODE_WIREFRAME; },
        [](Solid_) { return FILL_MODE_SOLID; }
    ), rs.mFillMode);
    desc.mCullMode = visit(overload(
        [](None_) { return CULL_MODE_NONE; },
        [](Front_) { return CULL_MODE_FRONT; },
        [](Back_) {return CULL_MODE_BACK; }
    ), rs.mCullMode);
    desc.mFrontCounterClockwise = rs.mFrontCounterClockwise;
    desc.mDepthBias = rs.mDepthBias;
    desc.mDepthBiasClamp = rs.mDepthBiasClamp;
    desc.mSlopeScaledDepthBias = rs.mSlopeScaledDepthBias;
    desc.mDepthClipEnable = rs.mDepthClipEnabled;
    desc.mMultisampleEnable = rs.mMultisampleEnable;
    desc.mAntialiasedLineEnable = rs.mAntialiasedLineEnable;
    desc.mForcedSampleCount = rs.mForcedSampleCount;
    desc.mConservativeRaster = rs.mConservativeRaster ?
        CONSERVATIVE_RASTERIZATION_MODE_ON : CONSERVATIVE_RASTERIZATION_MODE_OFF;

    return desc;
}

DEPTH_STENCIL_DESC getRenderType(const DepthStencilState& ds) noexcept {
    DEPTH_STENCIL_DESC desc;
    desc.mDepthEnable = ds.mDepthEnabled;
    desc.mDepthWriteMask = ds.mDepthWrite ? DEPTH_WRITE_MASK_ALL : DEPTH_WRITE_MASK_ZERO;
    auto compFunc = overload(
        [](Never_) { return COMPARISON_FUNC_NEVER; },
        [](Less_) { return COMPARISON_FUNC_LESS; },
        [](Equal_) { return COMPARISON_FUNC_EQUAL; },
        [](LessEqual_) { return COMPARISON_FUNC_LESS_EQUAL; },
        [](Greater_) { return COMPARISON_FUNC_GREATER; },
        [](NotEqual_) { return COMPARISON_FUNC_NOT_EQUAL; },
        [](GreaterEqual_) { return COMPARISON_FUNC_GREATER_EQUAL; },
        [](Always_) { return COMPARISON_FUNC_ALWAYS; }
    );
    desc.mDepthFunc = visit(compFunc, ds.mDepthFunc);
    desc.mStencilEnable = ds.mStencilEnable;
    desc.mStencilReadMask = ds.mStencilReadMask;
    desc.mStencilWriteMask = ds.mStencilWriteMask;
    auto stencilFunc = overload(
        [](Keep_) { return STENCIL_OP_KEEP; },
        [](Zero_) { return STENCIL_OP_ZERO; },
        [](Replace_) { return STENCIL_OP_REPLACE; },
        [](IncrSat_) { return STENCIL_OP_INCR_SAT; },
        [](DecrSat_) { return STENCIL_OP_DECR_SAT; },
        [](Invert_) { return STENCIL_OP_INVERT; },
        [](Incr_) { return STENCIL_OP_INCR; },
        [](Decr_) { return STENCIL_OP_DECR; }
    );
    desc.mFrontFace.mStencilFailOp = visit(stencilFunc, ds.mFrontFace.mStencilFailOp);
    desc.mFrontFace.mStencilDepthFailOp = visit(stencilFunc, ds.mFrontFace.mStencilDepthFailOp);
    desc.mFrontFace.mStencilPassOp = visit(stencilFunc, ds.mFrontFace.mStencilPassOp);
    desc.mFrontFace.mStencilFunc = visit(compFunc, ds.mFrontFace.mStencilFunc);

    desc.mBackFace.mStencilFailOp = visit(stencilFunc, ds.mBackFace.mStencilFailOp);
    desc.mBackFace.mStencilDepthFailOp = visit(stencilFunc, ds.mBackFace.mStencilDepthFailOp);
    desc.mBackFace.mStencilPassOp = visit(stencilFunc, ds.mBackFace.mStencilPassOp);
    desc.mBackFace.mStencilFunc = visit(compFunc, ds.mBackFace.mStencilFunc);

    return desc;
}

}
