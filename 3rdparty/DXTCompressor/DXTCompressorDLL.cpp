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

// Refer to "Real-Time DXT Compression" by J.M.P. van Waveren for a more thorough discussion of the
// algorithms used in this code.

#include "DXTCompressorDLL.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <emmintrin.h>

#define ALIGN16(x) __declspec(align(16)) x
#define INSET_SHIFT 4 // Inset the bounding box with (range >> shift).
#define C565_5_MASK 0xF8 // 0xFF minus last three bits
#define C565_6_MASK 0xFC // 0xFF minus last two bits
#define R_SHUFFLE_D( x, y, z, w ) (( (w) & 3 ) << 6 | ( (z) & 3 ) << 4 | ( (y) & 3 ) << 2 | ( (x) & 3 ))

namespace DXTC
{
	ALIGN16(static uint8_t SIMD_SSE2_byte_0[16]) = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ALIGN16(static uint8_t SIMD_SSE2_byte_1[16]) = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	ALIGN16(static uint8_t SIMD_SSE2_byte_2[16]) = { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 };
	ALIGN16(static uint8_t SIMD_SSE2_byte_7[16]) = { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07 };

	ALIGN16(static uint8_t SIMD_SSE2_byte_colorMask[16]) = { C565_5_MASK, C565_6_MASK, C565_5_MASK, 0x00, 0x00, 0x00, 0x00, 0x00, C565_5_MASK, C565_6_MASK, C565_5_MASK, 0x00, 0x00, 0x00, 0x00, 0x00 };

	ALIGN16(static uint16_t SIMD_SSE2_word_0[8]) = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
	ALIGN16(static uint16_t SIMD_SSE2_word_1[8]) = { 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001 };
	ALIGN16(static uint16_t SIMD_SSE2_word_2[8]) = { 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002 };

	ALIGN16(static uint16_t SIMD_SSE2_word_div_by_3[8]) = { (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1, (1 << 16) / 3 + 1 };
	ALIGN16(static uint16_t SIMD_SSE2_word_div_by_7[8]) = { (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1, (1 << 16) / 7 + 1 };
	ALIGN16(static uint16_t SIMD_SSE2_word_div_by_14[8]) = { (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1, (1 << 16) / 14 + 1 };

	ALIGN16(static uint16_t SIMD_SSE2_word_scale66554400[8]) = { 6, 6, 5, 5, 4, 4, 0, 0 };
	ALIGN16(static uint16_t SIMD_SSE2_word_scale11223300[8]) = { 1, 1, 2, 2, 3, 3, 0, 0 };

	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask0[4]) = { 7 << 0, 0, 7 << 0, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask1[4]) = { 7 << 3, 0, 7 << 3, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask2[4]) = { 7 << 6, 0, 7 << 6, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask3[4]) = { 7 << 9, 0, 7 << 9, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask4[4]) = { 7 << 12, 0, 7 << 12, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask5[4]) = { 7 << 15, 0, 7 << 15, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask6[4]) = { 7 << 18, 0, 7 << 18, 0 };
	ALIGN16(static uint32_t SIMD_SSE2_dword_alpha_bit_mask7[4]) = { 7 << 21, 0, 7 << 21, 0 };

	// Compress an image using DXT1 compression. Use the inBuf parameter to point to an image in
	// 4-byte RGBA format. The width and height parameters specify the size of the image in pixels.
	// The buffer pointed to by outBuf should be large enough to store the compressed image. This
	// implementation has an 8:1 compression ratio.
	void CompressImageDXT1(const uint8_t* inBuf, uint8_t* outBuf, int width, int height)
	{
		ALIGN16(uint8_t block[64]);
		ALIGN16(uint8_t minColor[4]);
		ALIGN16(uint8_t maxColor[4]);

		for(int j = 0; j < height; j += 4, inBuf += width * 4 * 4)
		{
			for(int i = 0; i < width; i += 4)
			{
				ExtractBlock(inBuf + i * 4, width, block);
				GetMinMaxColors(block, minColor, maxColor);
				EmitWord(outBuf, ColorTo565(maxColor));
				EmitWord(outBuf, ColorTo565(minColor));
				EmitColorIndices(block, outBuf, minColor, maxColor);
			}
		}
	}

	// Compress an image using DXT5 compression. Use the inBuf parameter to point to an image in
	// 4-byte RGBA format. The width and height parameters specify the size of the image in pixels.
	// The buffer pointed to by outBuf should be large enough to store the compressed image. This
	// implementation has an 4:1 compression ratio.
	void CompressImageDXT5(const uint8_t* inBuf, uint8_t* outBuf, int width, int height, unsigned int rowPitch)
	{
		ALIGN16(uint8_t block[64]);
		ALIGN16(uint8_t minColor[4]);
		ALIGN16(uint8_t maxColor[4]);

        if (rowPitch == 0)
            rowPitch = width * 4;

		for(int j = 0; j < height; j += 4, inBuf += width * 4 * 4)
		{
			for(int i = 0; i < width; i += 4)
			{
				ExtractBlock(inBuf + i * 4, width, block);
				GetMinMaxColorsWithAlpha(block, minColor, maxColor);
				EmitByte(outBuf, maxColor[3]);
				EmitByte(outBuf, minColor[3]);
				EmitAlphaIndices(block, outBuf, minColor[3], maxColor[3]);
				EmitWord(outBuf, ColorTo565(maxColor));
				EmitWord(outBuf, ColorTo565(minColor));
				EmitColorIndices(block, outBuf, minColor, maxColor);
			}
            outBuf += (rowPitch - width * 4);
		}
	}

	// Convert a color in 24-bit RGB888 format to 16-bit RGB565 format.
	uint16_t ColorTo565(const uint8_t* color)
	{
		return ((color[0] >> 3) << 11) | ((color[1] >> 2) << 5) | (color[2] >> 3);
	}

	// Write a single byte to dest.
	void EmitByte(uint8_t*& dest, uint8_t b)
	{
		dest[0] = b;
		dest += 1;
	}

	// Write a word to dest.
	void EmitWord(uint8_t*& dest, uint16_t s)
	{
		dest[0] = (s >> 0) & 255;
		dest[1] = (s >> 8) & 255;
		dest += 2;
	}

	// Write a double word to dest.
	void EmitDoubleWord(uint8_t*& dest, uint32_t i)
	{
		dest[0] = (i >> 0) & 255;
		dest[1] = (i >> 8) & 255;
		dest[2] = (i >> 16) & 255;
		dest[3] = (i >> 24) & 255;
		dest += 4;
	}

	// Extract a 4 by 4 block of pixels from inPtr and store it in colorBlock. The width parameter
	// specifies the size of the image in pixels.
	void ExtractBlock(const uint8_t* inPtr, int width, uint8_t* colorBlock)
	{
		for(int j = 0; j < 4; j++)
		{
			memcpy(&colorBlock[j * 4 * 4], inPtr, 4 * 4);
			inPtr += width * 4;
		}
	}

	// Find a line of best fit through the color space of colorBlock. The line is approximated using
	// the extents of the bounding box of the color space. This function does not include the alpha
	// channel.
	void GetMinMaxColors(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor)
	{
		int i;
		uint8_t inset[3];

		minColor[0] = minColor[1] = minColor[2] = 255;
		maxColor[0] = maxColor[1] = maxColor[2] = 0;

		// Find the bounding box (defined by minimum and maximum color).
		for(i = 0; i < 16; i++)
		{
			if(colorBlock[i * 4 + 0] < minColor[0])
			{
				minColor[0] = colorBlock[i * 4 + 0];
			}
			if(colorBlock[i * 4 + 1] < minColor[1])
			{
				minColor[1] = colorBlock[i * 4 + 1];
			}
			if(colorBlock[i * 4 + 2] < minColor[2])
			{
				minColor[2] = colorBlock[i * 4 + 2];
			}
			if(colorBlock[i * 4 + 0] > maxColor[0])
			{
				maxColor[0] = colorBlock[i * 4 + 0];
			}
			if(colorBlock[i * 4 + 1] > maxColor[1])
			{
				maxColor[1] = colorBlock[i * 4 + 1];
			}
			if(colorBlock[i * 4 + 2] > maxColor[2])
			{
				maxColor[2] = colorBlock[i * 4 + 2];
			}
		}

		// Inset the bounding box by 1/16 of it's size. (i.e. shift right by 4).
		inset[0] = (maxColor[0] - minColor[0]) >> INSET_SHIFT;
		inset[1] = (maxColor[1] - minColor[1]) >> INSET_SHIFT;
		inset[2] = (maxColor[2] - minColor[2]) >> INSET_SHIFT;

		// Clamp the inset bounding box to 255.
		minColor[0] = (minColor[0] + inset[0] <= 255) ? minColor[0] + inset[0] : 255;
		minColor[1] = (minColor[1] + inset[1] <= 255) ? minColor[1] + inset[1] : 255;
		minColor[2] = (minColor[2] + inset[2] <= 255) ? minColor[2] + inset[2] : 255;

		// Clamp the inset bounding box to 0.
		maxColor[0] = (maxColor[0] >= inset[0]) ? maxColor[0] - inset[0] : 0;
		maxColor[1] = (maxColor[1] >= inset[1]) ? maxColor[1] - inset[1] : 0;
		maxColor[2] = (maxColor[2] >= inset[2]) ? maxColor[2] - inset[2] : 0;
	}

	// Find a line of best fit through the color space of colorBlock. The line is approximated using
	// the extents of the bounding box of the color space. This function includes the alpha channel.
	void GetMinMaxColorsWithAlpha(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor)
	{
		int i;
		uint8_t inset[4];

		minColor[0] = minColor[1] = minColor[2] = minColor[3] = 255;
		maxColor[0] = maxColor[1] = maxColor[2] = maxColor[3] = 0;

		// Find the bounding box (defined by minimum and maximum color).
		for(i = 0; i < 16; i++)
		{
			if(colorBlock[i * 4 + 0] < minColor[0])
			{
				minColor[0] = colorBlock[i * 4 + 0];
			}
			if(colorBlock[i * 4 + 1] < minColor[1])
			{
				minColor[1] = colorBlock[i * 4 + 1];
			}
			if(colorBlock[i * 4 + 2] < minColor[2])
			{
				minColor[2] = colorBlock[i * 4 + 2];
			}
			if(colorBlock[i * 4 + 3] < minColor[3])
			{
				minColor[3] = colorBlock[i * 4 + 3];
			}
			if(colorBlock[i * 4 + 0] > maxColor[0])
			{
				maxColor[0] = colorBlock[i * 4 + 0];
			}
			if(colorBlock[i * 4 + 1] > maxColor[1])
			{
				maxColor[1] = colorBlock[i * 4 + 1];
			}
			if(colorBlock[i * 4 + 2] > maxColor[2])
			{
				maxColor[2] = colorBlock[i * 4 + 2];
			}
			if(colorBlock[i * 4 + 3] > maxColor[3])
			{
				maxColor[3] = colorBlock[i * 4 + 3];
			}
		}

		// Inset the bounding box by 1/16 of it's size. (i.e. shift right by 4).
		inset[0] = (maxColor[0] - minColor[0]) >> INSET_SHIFT;
		inset[1] = (maxColor[1] - minColor[1]) >> INSET_SHIFT;
		inset[2] = (maxColor[2] - minColor[2]) >> INSET_SHIFT;
		inset[3] = (maxColor[3] - minColor[3]) >> INSET_SHIFT;

		// Clamp the inset bounding box to 255.
		minColor[0] = (minColor[0] + inset[0] <= 255) ? minColor[0] + inset[0] : 255;
		minColor[1] = (minColor[1] + inset[1] <= 255) ? minColor[1] + inset[1] : 255;
		minColor[2] = (minColor[2] + inset[2] <= 255) ? minColor[2] + inset[2] : 255;
		minColor[3] = (minColor[3] + inset[3] <= 255) ? minColor[3] + inset[3] : 255;

		// Clamp the inset bounding box to 0.
		maxColor[0] = (maxColor[0] >= inset[0]) ? maxColor[0] - inset[0] : 0;
		maxColor[1] = (maxColor[1] >= inset[1]) ? maxColor[1] - inset[1] : 0;
		maxColor[2] = (maxColor[2] >= inset[2]) ? maxColor[2] - inset[2] : 0;
		maxColor[3] = (maxColor[3] >= inset[3]) ? maxColor[3] - inset[3] : 0;
	}

	// Quantize the pixels of the colorBlock to 4 colors that lie on the line through the color space
	// of colorBlock.  The paramaters minColor and maxColor approximate the line through the color
	// space.  32 bits (2 bits per pixel) are written to outBuf, which represent the indices of the 4
	// colors. This function does not include the alpha channel.
	void EmitColorIndices(const uint8_t* colorBlock,  uint8_t*& outBuf, const uint8_t* minColor, const uint8_t* maxColor)
	{
		uint16_t colors[4][4];
		uint32_t result = 0;

		colors[0][0] = (maxColor[0] & C565_5_MASK) | (maxColor[0] >> 5);
		colors[0][1] = (maxColor[1] & C565_6_MASK) | (maxColor[1] >> 6);
		colors[0][2] = (maxColor[2] & C565_5_MASK) | (maxColor[2] >> 5);
		colors[1][0] = (minColor[0] & C565_5_MASK) | (minColor[0] >> 5);
		colors[1][1] = (minColor[1] & C565_6_MASK) | (minColor[1] >> 6);
		colors[1][2] = (minColor[2] & C565_5_MASK) | (minColor[2] >> 5);
		colors[2][0] = (2 * colors[0][0] + 1 * colors[1][0]) / 3;
		colors[2][1] = (2 * colors[0][1] + 1 * colors[1][1]) / 3;
		colors[2][2] = (2 * colors[0][2] + 1 * colors[1][2]) / 3;
		colors[3][0] = (1 * colors[0][0] + 2 * colors[1][0]) / 3;
		colors[3][1] = (1 * colors[0][1] + 2 * colors[1][1]) / 3;
		colors[3][2] = (1 * colors[0][2] + 2 * colors[1][2]) / 3;

		for(int i = 15; i >= 0; i--)
		{
			int c0 = colorBlock[i * 4 + 0];
			int c1 = colorBlock[i * 4 + 1];
			int c2 = colorBlock[i * 4 + 2];

			int d0 = abs(colors[0][0] - c0) + abs(colors[0][1] - c1) + abs(colors[0][2] - c2);
			int d1 = abs(colors[1][0] - c0) + abs(colors[1][1] - c1) + abs(colors[1][2] - c2);
			int d2 = abs(colors[2][0] - c0) + abs(colors[2][1] - c1) + abs(colors[2][2] - c2);
			int d3 = abs(colors[3][0] - c0) + abs(colors[3][1] - c1) + abs(colors[3][2] - c2);

			int b0 = d0 > d3;
			int b1 = d1 > d2;
			int b2 = d0 > d2;
			int b3 = d1 > d3;
			int b4 = d2 > d3;

			int x0 = b1 & b2;
			int x1 = b0 & b3;
			int x2 = b0 & b4;

			result |= (x2 | ((x0 | x1) << 1)) << (i << 1);
		}

		EmitDoubleWord(outBuf, result);
	}

	// Quantize the alpha channel of the pixels in colorBlock to 8 alpha values that are equally
	// spaced along the interval defined by minAlpha and maxAlpha. 48 bits (3 bits per alpha) are
	// written to outBuf, which represent the indices of the 8 alpha values.
	void EmitAlphaIndices(const uint8_t* colorBlock,  uint8_t*& outBuf, const uint8_t minAlpha, const uint8_t maxAlpha)
	{
		assert(maxAlpha >= minAlpha);

		uint8_t indices[16];

		uint8_t mid = (maxAlpha - minAlpha) / (2 * 7);

		uint8_t ab1 = minAlpha + mid;
		uint8_t ab2 = (6 * maxAlpha + 1 * minAlpha) / 7 + mid;
		uint8_t ab3 = (5 * maxAlpha + 2 * minAlpha) / 7 + mid;
		uint8_t ab4 = (4 * maxAlpha + 3 * minAlpha) / 7 + mid;
		uint8_t ab5 = (3 * maxAlpha + 4 * minAlpha) / 7 + mid;
		uint8_t ab6 = (2 * maxAlpha + 5 * minAlpha) / 7 + mid;
		uint8_t ab7 = (1 * maxAlpha + 6 * minAlpha) / 7 + mid;

		colorBlock += 3;

		for(int i = 0; i < 16; i++)
		{
			uint8_t a = colorBlock[i * 4];
			int b1 = (a <= ab1);
			int b2 = (a <= ab2);
			int b3 = (a <= ab3);
			int b4 = (a <= ab4);
			int b5 = (a <= ab5);
			int b6 = (a <= ab6);
			int b7 = (a <= ab7);
			int index = (b1 + b2 + b3 + b4 + b5 + b6 + b7 + 1) & 7;
			indices[i] = index ^ (2 > index);
		}

		EmitByte(outBuf, (indices[0] >> 0) | (indices[1] << 3) | (indices[2] << 6));
		EmitByte(outBuf, (indices[2] >> 2) | (indices[3] << 1) | (indices[4] << 4) | (indices[ 5] << 7));
		EmitByte(outBuf, (indices[5] >> 1) | (indices[6] << 2) | (indices[7] << 5));
		EmitByte(outBuf, (indices[8] >> 0) | (indices[9] << 3) | (indices[10] << 6));
		EmitByte(outBuf, (indices[10] >> 2) | (indices[11] << 1) | (indices[12] << 4) | (indices[13] << 7));
		EmitByte(outBuf, (indices[13] >> 1) | (indices[14] << 2) | (indices[15] << 5));
	}

	// Compress an image using SSE2-optimized DXT1 compression. Use the inBuf parameter to point to an
	// image in 4-byte RGBA format. The address pointed to by inBuf must be 16-byte aligned. The width
	// and height parameters specify the size of the image in pixels. The buffer pointed to by outBuf
	// must be 16-byte aligned and should be large enough to store the compressed image. This
	// implementation has an 8:1 compression ratio.
	void CompressImageDXT1SSE2(const uint8_t* inBuf, uint8_t* outBuf, int width, int height)
	{
		ALIGN16(uint8_t block[64]);
		ALIGN16(uint8_t minColor[4]);
		ALIGN16(uint8_t maxColor[4]);

		for(int j = 0; j < height; j += 4, inBuf += width * 4 * 4)
		{
			for(int i = 0; i < width; i += 4)
			{
				ExtractBlock_SSE2(inBuf + i * 4, width, block);
				GetMinMaxColors_SSE2(block, minColor, maxColor);
				EmitWord(outBuf, ColorTo565(maxColor));
				EmitWord(outBuf, ColorTo565(minColor));
				EmitColorIndices_SSE2(block, outBuf, minColor, maxColor);
			}
		}
	}

	// Compress an image using SSE2-optimized DXT5 compression. Use the inBuf parameter to point to an
	// image in 4-byte RGBA format. The address pointed to by inBuf must be 16-byte aligned. The width
	// and height parameters specify the size of the image in pixels. The buffer pointed to by outBuf
	// must be 16-byte aligned and should be large enough to store the compressed image. This
	// implementation has an 4:1 compression ratio.
	void CompressImageDXT5SSE2(const uint8_t* inBuf, uint8_t* outBuf, int width, int height, unsigned int rowPitch)
	{
		ALIGN16(uint8_t block[64]);
		ALIGN16(uint8_t minColor[4]);
		ALIGN16(uint8_t maxColor[4]);

        if (rowPitch == 0)
            rowPitch = width * 4;

		for(int j = 0; j < height; j += 4, inBuf += width * 4 * 4)
		{
			for(int i = 0; i < width; i += 4)
			{
				ExtractBlock_SSE2(inBuf + i * 4, width, block);
				GetMinMaxColors_SSE2(block, minColor, maxColor);
				EmitByte(outBuf, maxColor[3]);
				EmitByte(outBuf, minColor[3]);
				EmitAlphaIndices_SSE2(block, outBuf, minColor[3], maxColor[3]);
				EmitWord(outBuf, ColorTo565(maxColor));
				EmitWord(outBuf, ColorTo565(minColor));
				EmitColorIndices_SSE2(block, outBuf, minColor, maxColor);
			}
            outBuf += (rowPitch - width * 4);
		}
	}

	// Extract a 4 by 4 block of pixels from inPtr and store it in colorBlock. The width parameter
	// specifies the size of the image in pixels.
	void ExtractBlock_SSE2(const uint8_t* inPtr, int width, uint8_t* colorBlock)
	{
		// Compute the stride.
		const int stride = width * 4;

		// Copy the first row of pixels from inPtr into colorBlock.
		_mm_store_si128((__m128i*)colorBlock, _mm_load_si128((__m128i*)inPtr));
		inPtr += stride;

		// Copy the second row of pixels from inPtr into colorBlock.
		_mm_store_si128((__m128i*)(colorBlock + 16), _mm_load_si128((__m128i*)inPtr));
		inPtr += stride;

		// Copy the third row of pixels from inPtr into colorBlock.
		_mm_store_si128((__m128i*)(colorBlock + 32), _mm_load_si128((__m128i*)inPtr));
		inPtr += stride;

		// Copy the forth row of pixels from inPtr into colorBlock.
		_mm_store_si128((__m128i*)(colorBlock + 48), _mm_load_si128((__m128i*)inPtr));
	}

	// Find a line of best fit through the color space of colorBlock. The line is approximated using
	// the extents of the bounding box of the color space. This function does not include the alpha
	// channel.
	void GetMinMaxColors_SSE2(const uint8_t* colorBlock, uint8_t* minColor, uint8_t* maxColor)
	{
		// Compute the min/max of each column of pixels.
		__m128i min = _mm_load_si128((__m128i*)colorBlock);
		__m128i max = _mm_load_si128((__m128i*)colorBlock);
		min = _mm_min_epu8(min, *((__m128i*)(colorBlock + 16)));
		max = _mm_max_epu8(max, *((__m128i*)(colorBlock + 16)));
		min = _mm_min_epu8(min, *((__m128i*)(colorBlock + 32)));
		max = _mm_max_epu8(max, *((__m128i*)(colorBlock + 32)));
		min = _mm_min_epu8(min, *((__m128i*)(colorBlock + 48)));
		max = _mm_max_epu8(max, *((__m128i*)(colorBlock + 48)));

		// Compute the min/max of the 1st and 3rd uint32_t and the 2nd and 4th uint32_t.		
		__m128i minShuf = _mm_shuffle_epi32(min, R_SHUFFLE_D(2, 3, 2, 3));
		__m128i maxShuf = _mm_shuffle_epi32(max, R_SHUFFLE_D(2, 3, 2, 3));
		min = _mm_min_epu8(min, minShuf);
		max = _mm_max_epu8(max, maxShuf);

		// Compute the min/max of the 1st and 2nd uint32_t.
		minShuf = _mm_shufflelo_epi16(min, R_SHUFFLE_D(2, 3, 2, 3));
		maxShuf = _mm_shufflelo_epi16(max, R_SHUFFLE_D(2, 3, 2, 3));
		min = _mm_min_epu8(min, minShuf);
		max = _mm_max_epu8(max, maxShuf);

		// Compute the inset value.
		min = _mm_unpacklo_epi8(min, *((__m128i*)SIMD_SSE2_byte_0));
		max = _mm_unpacklo_epi8(max, *((__m128i*)SIMD_SSE2_byte_0));
		__m128i inset = _mm_sub_epi16(max, min);
		inset = _mm_srli_epi16(inset, INSET_SHIFT);

		// Inset the bounding box.
		min = _mm_add_epi16(min, inset);
		max = _mm_sub_epi16(max, inset);

		// Store the bounding box.
		min = _mm_packus_epi16(min, min);
		max = _mm_packus_epi16(max, max);
		*((int*)minColor) = _mm_cvtsi128_si32(min);
		*((int*)maxColor) = _mm_cvtsi128_si32(max);
	}

	// Quantize the pixels of the colorBlock to 4 colors that lie on the line through the color space
	// of colorBlock.  The paramaters minColor and maxColor approximate the line through the color
	// space.  32 bits (2 bits per pixel) are written to outBuf, which represent the indices of the 4
	// colors. This function does not include the alpha channel.
	void EmitColorIndices_SSE2(const uint8_t* colorBlock, uint8_t*& outBuf, const uint8_t* minColor, const uint8_t* maxColor)
	{
		const __m128i RGB565Mask = _mm_load_si128((__m128i*)SIMD_SSE2_byte_colorMask);
		const __m128i zero = _mm_setzero_si128();

		// Find 4 colors on the line through maxColor and minColor.
		// Compute color0 (maxColor).
		__m128i color0 = _mm_cvtsi32_si128(*((int*)maxColor));
		color0 = _mm_and_si128(color0, RGB565Mask);
		color0 = _mm_unpacklo_epi8(color0, zero);
		__m128i redBlue = _mm_shufflelo_epi16(color0, R_SHUFFLE_D(0, 3, 2, 3));
		__m128i green = _mm_shufflelo_epi16(color0, R_SHUFFLE_D(3, 1, 3, 3));
		redBlue = _mm_srli_epi16(redBlue, 5);
		green = _mm_srli_epi16(green, 6);
		color0 = _mm_or_si128(color0, redBlue);
		color0 = _mm_or_si128(color0, green);

		// Compute color1 (minColor).
		__m128i color1 = _mm_cvtsi32_si128(*((int*)minColor));
		color1 = _mm_and_si128(color1, RGB565Mask);
		color1 = _mm_unpacklo_epi8(color1, zero);
		redBlue = _mm_shufflelo_epi16(color1, R_SHUFFLE_D(0, 3, 2, 3));
		green = _mm_shufflelo_epi16(color1, R_SHUFFLE_D(3, 1, 3, 3));
		redBlue = _mm_srli_epi16(redBlue, 5);
		green = _mm_srli_epi16(green, 6);
		color1 = _mm_or_si128(color1, redBlue);
		color1 = _mm_or_si128(color1, green);

		// Compute and pack color3.
		__m128i color3 = _mm_add_epi16(color1, color1);
		color3 = _mm_add_epi16(color0, color3);
		color3 = _mm_mulhi_epi16(color3, *((__m128i*)SIMD_SSE2_word_div_by_3));
		color3 = _mm_packus_epi16(color3, zero);
		color3 = _mm_shuffle_epi32(color3, R_SHUFFLE_D(0, 1, 0, 1));

		// Compute and pack color2.
		__m128i color2 = _mm_add_epi16(color0, color0);
		color2 = _mm_add_epi16(color2, color1);
		color2 = _mm_mulhi_epi16(color2, *((__m128i*)SIMD_SSE2_word_div_by_3));
		color2 = _mm_packus_epi16(color2, zero);
		color2 = _mm_shuffle_epi32(color2, R_SHUFFLE_D(0, 1, 0, 1));

		// Pack color1.
		color1 = _mm_packus_epi16(color1, zero);
		color1 = _mm_shuffle_epi32(color1, R_SHUFFLE_D(0, 1, 0, 1));

		// Pack color0.
		color0 = _mm_packus_epi16(color0, zero);
		color0 = _mm_shuffle_epi32(color0, R_SHUFFLE_D(0, 1, 0, 1));

		// Assign a color index for each of the 16 colors in the colorblock.
		// This loop iterates twice (computes 8 indexes per iteration).
		__m128i result = zero;
		for(int i = 32; i >= 0; i -= 32)
		{
			// Load 4 colors.
			__m128i colorHi = _mm_loadl_epi64((__m128i*)(colorBlock + i));
			colorHi = _mm_shuffle_epi32(colorHi, R_SHUFFLE_D(0, 2, 1, 3));
			__m128i colorLo = _mm_loadl_epi64((__m128i*)(colorBlock + i + 8));
			colorLo = _mm_shuffle_epi32(colorLo, R_SHUFFLE_D(0, 2, 1, 3));

			// Compute the sum of absolute differences for each color.
			__m128i dHi = _mm_sad_epu8(colorHi, color0);
			__m128i dLo = _mm_sad_epu8(colorLo, color0);
			__m128i d0 = _mm_packs_epi32(dHi, dLo);
			dHi = _mm_sad_epu8(colorHi, color1);
			dLo = _mm_sad_epu8(colorLo, color1);
			__m128i d1 = _mm_packs_epi32(dHi, dLo);
			dHi = _mm_sad_epu8(colorHi, color2);
			dLo = _mm_sad_epu8(colorLo, color2);
			__m128i d2 = _mm_packs_epi32(dHi, dLo);
			dHi = _mm_sad_epu8(colorHi, color3);
			dLo = _mm_sad_epu8(colorLo, color3);
			__m128i d3 = _mm_packs_epi32(dHi, dLo);

			// Load 4 more colors.
			colorHi = _mm_loadl_epi64((__m128i*)(colorBlock + i + 16));
			colorHi = _mm_shuffle_epi32(colorHi, R_SHUFFLE_D(0, 2, 1, 3));
			colorLo = _mm_loadl_epi64((__m128i*)(colorBlock + i + 24));
			colorLo = _mm_shuffle_epi32(colorLo, R_SHUFFLE_D(0, 2, 1, 3));

			// Compute the sum of absolute differences for each color.  Pack result into previous 4 results.
			dHi = _mm_sad_epu8(colorHi, color0);
			dLo = _mm_sad_epu8(colorLo, color0);
			dLo = _mm_packs_epi32(dHi, dLo);
			d0 = _mm_packs_epi32(d0, dLo);
			dHi = _mm_sad_epu8(colorHi, color1);
			dLo = _mm_sad_epu8(colorLo, color1);
			dLo = _mm_packs_epi32(dHi, dLo);
			d1 = _mm_packs_epi32(d1, dLo);
			dHi = _mm_sad_epu8(colorHi, color2);
			dLo = _mm_sad_epu8(colorLo, color2);
			dLo = _mm_packs_epi32(dHi, dLo);
			d2 = _mm_packs_epi32(d2, dLo);
			dHi = _mm_sad_epu8(colorHi, color3);
			dLo = _mm_sad_epu8(colorLo, color3);
			dLo = _mm_packs_epi32(dHi, dLo);
			d3 = _mm_packs_epi32(d3, dLo);

			// Compare the distances.
			__m128i b0 = _mm_cmpgt_epi16(d0, d3);
			__m128i b1 = _mm_cmpgt_epi16(d1, d2);
			__m128i b2 = _mm_cmpgt_epi16(d0, d2);
			__m128i b3 = _mm_cmpgt_epi16(d1, d3);
			__m128i b4 = _mm_cmpgt_epi16(d2, d3);

			// Compute the color index.
			__m128i x0 = _mm_and_si128(b2, b1);
			__m128i x1 = _mm_and_si128(b3, b0);
			__m128i x2 = _mm_and_si128(b4, b0);
			__m128i indexBit0 = _mm_or_si128(x0, x1);
			indexBit0 = _mm_and_si128(indexBit0, *((__m128i*)SIMD_SSE2_word_2));
			__m128i indexBit1 = _mm_and_si128(x2, *((__m128i*)SIMD_SSE2_word_1));
			__m128i index = _mm_or_si128(indexBit1, indexBit0);

			// Pack the index into the result.
			__m128i indexHi = _mm_shuffle_epi32(index, R_SHUFFLE_D(2, 3, 0, 1));
			indexHi = _mm_unpacklo_epi16(indexHi, *((__m128i*)SIMD_SSE2_word_0));
			indexHi = _mm_slli_epi32(indexHi, 8);
			__m128i indexLo = _mm_unpacklo_epi16(index, *((__m128i*)SIMD_SSE2_word_0));
			result = _mm_slli_epi32(result, 16);
			result = _mm_or_si128(result, indexHi);
			result = _mm_or_si128(result, indexLo);
		}

		// Pack the 16 2-bit color indices into a single 32-bit value.
		__m128i result1 = _mm_shuffle_epi32(result, R_SHUFFLE_D(1, 2, 3, 0));
		__m128i result2 = _mm_shuffle_epi32(result, R_SHUFFLE_D(2, 3, 0, 1));
		__m128i result3 = _mm_shuffle_epi32(result, R_SHUFFLE_D(3, 0, 1, 2));
		result1 = _mm_slli_epi32(result1, 2);
		result2 = _mm_slli_epi32(result2, 4);
		result3 = _mm_slli_epi32(result3, 6);
		result = _mm_or_si128(result, result1);
		result = _mm_or_si128(result, result2);
		result = _mm_or_si128(result, result3);

		// Store the result.
		*((int*)outBuf) = _mm_cvtsi128_si32(result);

		outBuf += 4;
	}

	// Quantize the alpha channel of the pixels in colorBlock to 8 alpha values that are equally
	// spaced along the interval defined by minAlpha and maxAlpha. 48 bits (3 bits per alpha) are
	// written to outBuf, which represent the indices of the 8 alpha values.
	void EmitAlphaIndices_SSE2(const uint8_t* colorBlock, uint8_t*& outBuf, const uint8_t minAlpha, const uint8_t maxAlpha)
	{
		// Pack the alpha values of the first two rows of colorBlock.
		__m128i alpha1 = _mm_load_si128((__m128i*)colorBlock);
		alpha1 = _mm_srli_epi32(alpha1, 24);
		__m128i alpha2 = _mm_load_si128((__m128i*)(colorBlock + 16));
		alpha2 = _mm_srli_epi32(alpha2, 24);
		alpha1 = _mm_packus_epi16(alpha1, alpha2);

		// Pack the alpha values of the last two rows of colorBlock.
		__m128i alpha3 = _mm_load_si128((__m128i*)(colorBlock + 32));
		alpha3 = _mm_srli_epi32(alpha3, 24);
		__m128i alpha4 = _mm_load_si128((__m128i*)(colorBlock + 48));
		alpha4 = _mm_srli_epi32(alpha4, 24);
		alpha3 = _mm_packus_epi16(alpha3, alpha4);

		// Pack all 16 alpha values together.
		__m128i alpha = _mm_packus_epi16(alpha1, alpha3);

		// Unpack the maximum alpha value.
		__m128i max = _mm_cvtsi32_si128(maxAlpha);
		max = _mm_shufflelo_epi16(max, R_SHUFFLE_D(0, 0, 0, 0));
		max = _mm_shuffle_epi32(max, R_SHUFFLE_D(0, 0, 0, 0));

		// Unpack the minimum alpha value.
		__m128i min = _mm_cvtsi32_si128(minAlpha);
		min = _mm_shufflelo_epi16(min, R_SHUFFLE_D(0, 0, 0, 0));
		min = _mm_shuffle_epi32(min, R_SHUFFLE_D(0, 0, 0, 0));

		// Compute the midpoint offset between any two interpolated alpha values.
		__m128i mid = _mm_sub_epi16(max, min);
		mid = _mm_mulhi_epi16(mid, *((__m128i*)SIMD_SSE2_word_div_by_14));

		// Compute the first midpoint.
		__m128i ab1 = min;
		ab1 = _mm_add_epi16(ab1, mid);
		ab1 = _mm_packus_epi16(ab1, ab1);

		// Compute the next three midpoints.
		__m128i max456 = _mm_mullo_epi16(max, *((__m128i*)SIMD_SSE2_word_scale66554400));
		__m128i min123 = _mm_mullo_epi16(min, *((__m128i*)SIMD_SSE2_word_scale11223300));
		__m128i ab234 = _mm_add_epi16(max456, min123);
		ab234 = _mm_mulhi_epi16(ab234, *((__m128i*)SIMD_SSE2_word_div_by_7));
		ab234 = _mm_add_epi16(ab234, mid);
		__m128i ab2 = _mm_shuffle_epi32(ab234, R_SHUFFLE_D(0, 0, 0, 0));
		ab2 = _mm_packus_epi16(ab2, ab2);
		__m128i ab3 = _mm_shuffle_epi32(ab234, R_SHUFFLE_D(1, 1, 1, 1));
		ab3 = _mm_packus_epi16(ab3, ab3);
		__m128i ab4 = _mm_shuffle_epi32(ab234, R_SHUFFLE_D(2, 2, 2, 2));
		ab4 = _mm_packus_epi16(ab4, ab4);

		// Compute the last three midpoints.
		__m128i max123 = _mm_mullo_epi16(max, *((__m128i*)SIMD_SSE2_word_scale11223300));
		__m128i min456 = _mm_mullo_epi16(min, *((__m128i*)SIMD_SSE2_word_scale66554400));
		__m128i ab567 = _mm_add_epi16(max123, min456);
		ab567 = _mm_mulhi_epi16(ab567, *((__m128i*)SIMD_SSE2_word_div_by_7));
		ab567 = _mm_add_epi16(ab567, mid);
		__m128i ab5 = _mm_shuffle_epi32(ab567, R_SHUFFLE_D(2, 2, 2, 2));
		ab5 = _mm_packus_epi16(ab5, ab5);
		__m128i ab6 = _mm_shuffle_epi32(ab567, R_SHUFFLE_D(1, 1, 1, 1));
		ab6 = _mm_packus_epi16(ab6, ab6);
		__m128i ab7 = _mm_shuffle_epi32(ab567, R_SHUFFLE_D(0, 0, 0, 0));
		ab7 = _mm_packus_epi16(ab7, ab7);

		// Compare the alpha values to the midpoints.
		__m128i b1 = _mm_min_epu8(ab1, alpha);
		b1 = _mm_cmpeq_epi8(b1, alpha);
		b1 = _mm_and_si128(b1, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b2 = _mm_min_epu8(ab2, alpha);
		b2 = _mm_cmpeq_epi8(b2, alpha);
		b2 = _mm_and_si128(b2, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b3 = _mm_min_epu8(ab3, alpha);
		b3 = _mm_cmpeq_epi8(b3, alpha);
		b3 = _mm_and_si128(b3, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b4 = _mm_min_epu8(ab4, alpha);
		b4 = _mm_cmpeq_epi8(b4, alpha);
		b4 = _mm_and_si128(b4, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b5 = _mm_min_epu8(ab5, alpha);
		b5 = _mm_cmpeq_epi8(b5, alpha);
		b5 = _mm_and_si128(b5, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b6 = _mm_min_epu8(ab6, alpha);
		b6 = _mm_cmpeq_epi8(b6, alpha);
		b6 = _mm_and_si128(b6, *((__m128i*)SIMD_SSE2_byte_1));
		__m128i b7 = _mm_min_epu8(ab7, alpha);
		b7 = _mm_cmpeq_epi8(b7, alpha);
		b7 = _mm_and_si128(b7, *((__m128i*)SIMD_SSE2_byte_1));

		// Compute the alpha indexes.
		__m128i index = _mm_adds_epu8(b1, b2);
		index = _mm_adds_epu8(index, b3);
		index = _mm_adds_epu8(index, b4);
		index = _mm_adds_epu8(index, b5);
		index = _mm_adds_epu8(index, b6);
		index = _mm_adds_epu8(index, b7);

		// Convert natural index ordering to DXT index ordering.
		__m128i byte1 = _mm_load_si128((__m128i*)SIMD_SSE2_byte_1);
		index = _mm_adds_epu8(index, byte1);
		__m128i byte7 = _mm_load_si128((__m128i*)SIMD_SSE2_byte_7);
		index = _mm_and_si128(index, byte7);
		__m128i byte2 = _mm_load_si128((__m128i*)SIMD_SSE2_byte_2);
		__m128i swapMinMax = _mm_cmpgt_epi8(byte2, index);
		swapMinMax = _mm_and_si128(swapMinMax, byte1);
		index = _mm_xor_si128(index, swapMinMax);

		// Pack the 16 3-bit indices into 6 bytes.
		__m128i alphaBitMask0 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask0);
		__m128i index0 = _mm_and_si128(index, alphaBitMask0);
		__m128i index1 = _mm_srli_epi64(index, 8 - 3);
		__m128i alphaBitMask1 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask1);
		index1 = _mm_and_si128(index1, alphaBitMask1);
		__m128i index2 = _mm_srli_epi64(index, 16 - 6);
		__m128i alphaBitMask2 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask2);
		index2 = _mm_and_si128(index2, alphaBitMask2);
		__m128i index3 = _mm_srli_epi64(index, 24 - 9);
		__m128i alphaBitMask3 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask3);
		index3 = _mm_and_si128(index3, alphaBitMask3);
		__m128i index4 = _mm_srli_epi64(index, 32 - 12);
		__m128i alphaBitMask4 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask4);
		index4 = _mm_and_si128(index4, alphaBitMask4);
		__m128i index5 = _mm_srli_epi64(index, 40 - 15);
		__m128i alphaBitMask5 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask5);
		index5 = _mm_and_si128(index5, alphaBitMask5);
		__m128i index6 = _mm_srli_epi64(index, 48 - 18);
		__m128i alphaBitMask6 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask6);
		index6 = _mm_and_si128(index6, alphaBitMask6);
		__m128i index7 = _mm_srli_epi64(index, 56 - 21);
		__m128i alphaBitMask7 = _mm_load_si128((__m128i*)SIMD_SSE2_dword_alpha_bit_mask7);
		index7 = _mm_and_si128(index7, alphaBitMask7);
		index = _mm_or_si128(index0, index1);
		index = _mm_or_si128(index, index2);
		index = _mm_or_si128(index, index3);
		index = _mm_or_si128(index, index4);
		index = _mm_or_si128(index, index5);
		index = _mm_or_si128(index, index6);
		index = _mm_or_si128(index, index7);

		// Store the indexes.
		*((int*)outBuf) = _mm_cvtsi128_si32(index);
		index = _mm_shuffle_epi32(index, R_SHUFFLE_D(2, 3, 0, 1));
		*((int*)(outBuf + 3)) = _mm_cvtsi128_si32(index);

		outBuf += 6;
	}
}
