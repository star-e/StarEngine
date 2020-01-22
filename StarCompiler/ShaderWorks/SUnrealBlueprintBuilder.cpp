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

#include "SUnrealBlueprintBuilder.h"
#include <StarCompiler/ShaderGraph/SShaderNames.h>

namespace Star::Graphics::Render::Shader {

UnrealBlueprintBuilder::UnrealBlueprintBuilder() {
#define VIEW_UNIFORM_BUFFER_MEMBER(A, NAME) \
mViewMap.emplace(BOOST_PP_STRINGIZE(NAME), BOOST_PP_STRINGIZE(NAME));

#define VIEW_UNIFORM_BUFFER_MEMBER_EX(A, NAME, C) \
mViewMap.emplace(BOOST_PP_STRINGIZE(NAME), BOOST_PP_STRINGIZE(NAME));

#define VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(A, NAME, C) \
mViewMap.emplace(BOOST_PP_STRINGIZE(NAME), BOOST_PP_STRINGIZE(NAME));

#define VIEW_UNIFORM_BUFFER_MEMBER_TABLE \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, TranslatedWorldToClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, WorldToClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ClipToWorld)  \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, TranslatedWorldToView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ViewToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, TranslatedWorldToCameraView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, CameraViewToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ViewToClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ViewToClipNoAA) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ClipToView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ClipToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, SVPositionToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ScreenToWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ScreenToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, ViewForward, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, ViewUp, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, ViewRight, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, HMDViewNoRollUp, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, HMDViewNoRollRight, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, InvDeviceZToWorldZTransform) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector4, ScreenPositionScaleBias, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, WorldCameraOrigin) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, TranslatedWorldCameraOrigin) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, WorldViewOrigin) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, PreViewTranslation) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevProjection) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevViewProj) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevViewRotationProj) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevViewToClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevClipToView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevTranslatedWorldToClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevTranslatedWorldToView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevViewToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevTranslatedWorldToCameraView) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevCameraViewToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, PrevWorldCameraOrigin) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, PrevWorldViewOrigin) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, PrevPreViewTranslation) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevInvViewProj) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, PrevScreenToTranslatedWorld) \
	VIEW_UNIFORM_BUFFER_MEMBER(FMatrix, ClipToPrevClip) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, TemporalAAJitter) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, GlobalClippingPlane) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector2D, FieldOfViewWideAngles) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector2D, PrevFieldOfViewWideAngles) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector4, ViewRectMin, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, ViewSizeAndInvSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, BufferSizeAndInvSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, BufferBilinearUVMinMax) \
	VIEW_UNIFORM_BUFFER_MEMBER(int32, NumSceneColorMSAASamples) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, PreExposure, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, OneOverPreExposure, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector4, DiffuseOverrideParameter, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector4, SpecularOverrideParameter, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector4, NormalOverrideParameter, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector2D, RoughnessOverrideParameter, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, PrevFrameGameTime) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, PrevFrameRealTime) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, OutOfBoundsMask, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, WorldCameraMovementSinceLastFrame) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, CullingSign) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, NearPlane, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, AdaptiveTessellationFactor) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, GameTime) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, RealTime) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DeltaTime) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, MaterialTextureMipBias) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, MaterialTextureDerivativeMultiply) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, Random) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, FrameNumber) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, StateFrameIndexMod8) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, StateFrameIndex) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, CameraCut, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, UnlitViewmodeMask, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FLinearColor, DirectionalLightColor, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(FVector, DirectionalLightDirection, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(FVector4, TranslucencyLightingVolumeMin, [TVC_MAX]) \
	VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(FVector4, TranslucencyLightingVolumeInvSize, [TVC_MAX]) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, TemporalAAParams) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector4, CircleDOFParams) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldSensorWidth) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldFocalDistance) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldScale) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldFocalLength) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldFocalRegion) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldNearTransitionRegion) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, DepthOfFieldFarTransitionRegion) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, MotionBlurNormalizedToPixel) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, bSubsurfacePostprocessEnabled) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, GeneralPurposeTweak) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, DemosaicVposOffset, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, IndirectLightingColorScale) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, HDR32bppEncodingMode, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, AtmosphericFogSunDirection) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogSunPower, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogPower, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogDensityScale, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogDensityOffset, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogGroundOffset, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogDistanceScale, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogAltitudeScale, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogHeightScaleRayleigh, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogStartDistance, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogDistanceOffset, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, AtmosphericFogSunDiscScale, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, AtmosphericFogRenderMask) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, AtmosphericFogInscatterAltitudeSampleNum) \
	VIEW_UNIFORM_BUFFER_MEMBER(FLinearColor, AtmosphericFogSunColor) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, NormalCurvatureToRoughnessScaleBias) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, RenderingReflectionCaptureMask) \
	VIEW_UNIFORM_BUFFER_MEMBER(FLinearColor, AmbientCubemapTint) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, AmbientCubemapIntensity) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, SkyLightParameters) \
	VIEW_UNIFORM_BUFFER_MEMBER(FLinearColor, SkyLightColor) \
	VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(FVector4, SkyIrradianceEnvironmentMap, [7]) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, MobilePreviewMode) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, HMDEyePaddingOffset) \
	VIEW_UNIFORM_BUFFER_MEMBER_EX(float, ReflectionCubemapMaxMip, EShaderPrecisionModifier::Half) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, ShowDecalsMask) \
	VIEW_UNIFORM_BUFFER_MEMBER(uint32, DistanceFieldAOSpecularOcclusionMode) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, IndirectCapsuleSelfShadowingIntensity) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, ReflectionEnvironmentRoughnessMixingScaleBiasAndLargestWeight) \
	VIEW_UNIFORM_BUFFER_MEMBER(int32, StereoPassIndex) \
	VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(FVector4, GlobalVolumeCenterAndExtent, [GMaxGlobalDistanceFieldClipmaps]) \
	VIEW_UNIFORM_BUFFER_MEMBER_ARRAY(FVector4, GlobalVolumeWorldToUVAddAndMul, [GMaxGlobalDistanceFieldClipmaps]) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, GlobalVolumeDimension) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, GlobalVolumeTexelSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, MaxGlobalDistance) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, bCheckerboardSubsurfaceProfileRendering) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricFogInvGridSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricFogGridZParams) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector2D, VolumetricFogSVPosToVolumeUV) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, VolumetricFogMaxDistance) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricLightmapWorldToUVScale) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricLightmapWorldToUVAdd) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricLightmapIndirectionTextureSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, VolumetricLightmapBrickSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(FVector, VolumetricLightmapBrickTexelSize) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, StereoIPD) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, IndirectLightingCacheShowFlag) \
	VIEW_UNIFORM_BUFFER_MEMBER(float, EyeToPixelSpreadAngle)

    VIEW_UNIFORM_BUFFER_MEMBER_TABLE

#undef VIEW_UNIFORM_BUFFER_MEMBER
#undef VIEW_UNIFORM_BUFFER_MEMBER_EX
#undef VIEW_UNIFORM_BUFFER_MEMBER_ARRAY
}

std::string UnrealBlueprintBuilder::generate(const ShaderModules& modules0, std::vector<std::string> modules) const {
    std::ostringstream oss;
    std::string space;

    for (const auto& name : modules) {
        const auto& m = at(modules0.mModules, name);
        if (!m.mAttributes.empty()) {
            oss << "\n";
            oss << "// ";
        }
        uint32_t count = 0;
        for (const auto& attr : m.mAttributes) {
            if (count++)
                oss << ", ";
            bool isView = false;
            if (exists(mViewMap, attr.mName))
                isView = true;
            oss << getHLSLName(attr.mType) << " ";
            if (isView)
                oss << "View.";
            oss << attr.mName;
        }

        oss << "\n";
        oss << "// ";
        count = 0;
        for (const auto& input : m.mInputs) {
            if (count++)
                oss << ", ";
            //oss << getVariantName(input.mValue) << " " << input.mName;
			std::ignore = input;
		}

        auto content = at(m.mContents, Language(HLSL).index()).mContent;
    }

    return std::string();
}

}
