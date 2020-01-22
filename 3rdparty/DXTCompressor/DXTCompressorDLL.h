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

/*
	This code is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This code is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.
*/

#pragma once
#include <cstdint>

namespace DXTC
{
	// DXT compressor (scalar version).
	void CompressImageDXT1(const uint8_t* inBuf, uint8_t* outBuf, int width, int height);
	void CompressImageDXT5(const uint8_t* inBuf, uint8_t* outBuf, int width, int height, unsigned int rowPitch = 0);
	uint16_t ColorTo565(const uint8_t* color);
	void EmitByte(uint8_t*& dest, uint8_t b);
    void EmitWord(uint8_t*& dest, uint16_t s);
    void EmitDoubleWord(uint8_t*& dest, uint32_t i);
    void ExtractBlock(const uint8_t* inPtr, int width, uint8_t* colorBlock);
    void GetMinMaxColors(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor);
    void GetMinMaxColorsWithAlpha(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor);
    void EmitColorIndices(const uint8_t* colorBlock, uint8_t*& outBuf, const uint8_t* minColor, const uint8_t* maxColor);
    void EmitAlphaIndices(const uint8_t* colorBlock,  uint8_t*& outBuf, const uint8_t minAlpha, const uint8_t maxAlpha);

	// DXT compressor (SSE2 version).
	void CompressImageDXT1SSE2(const uint8_t* inBuf, uint8_t* outBuf, int width, int height);
    void CompressImageDXT5SSE2(const uint8_t* inBuf, uint8_t* outBuf, int width, int height, unsigned int rowPitch = 0);
    void ExtractBlock_SSE2(const uint8_t* inPtr, int width, uint8_t* colorBlock);
    void GetMinMaxColors_SSE2(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor);
    void EmitColorIndices_SSE2(const uint8_t* colorBlock, uint8_t*& outBuf, const uint8_t* minColor, const uint8_t* maxColor);
    void EmitAlphaIndices_SSE2(const uint8_t* colorBlock, uint8_t*& outBuf, const uint8_t minAlpha, const uint8_t maxAlpha);
}
