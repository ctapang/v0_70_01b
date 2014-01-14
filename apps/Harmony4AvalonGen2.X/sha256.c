/*
 * Author: Xiangfu Liu <xiangfu@openmobilefree.net>
 * Bitcoin:	1CanaaniJzgps8EV6Sfmpb7T8RutpaeyFn
 *
 * This is free and unencumbered software released into the public domain.
 * For details see the UNLICENSE file at the root of the source tree.
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//#include "system_config.h"
#include "byte_manipulation.h"
#include "sha256.h"


inline uint32_t ReverseBits( uint32_t value )
{
    uint32_t outValue = 0;
    uint32_t probe = 1;
    uint32_t bitSet = 0x80000000;
    while(probe)
    {
        if (value & probe)
            outValue |= bitSet;
        probe <<= 1;
        bitSet >>= 1;
    }
    return outValue;
}

inline uint8_t ReverseEightBits( uint8_t value )
{
    uint8_t outValue = 0;
    uint8_t probe = 1;
    uint8_t bitSet = 0x80;
    while(probe)
    {
        if (value & probe)
            outValue |= bitSet;
        probe <<= 1;
        bitSet >>= 1;
    }
    return outValue;
}

void flip32bytes(void *dest_p, const uint8_t *src_p)
{
    uint32_t *dest = dest_p;
    uint32_t *src = (uint32_t *)src_p;
    int i;
    for (i = 0; i < 8; i++)
    {
        dest[i] = ReverseBits(src[i]);
    }
}

void flip32bytesbybyte(void *dest_p, const uint8_t *src_p)
{
    uint8_t *dest = dest_p;
    int i;
    for (i = 0; i < 32; i++)
    {
        dest[i] = ReverseEightBits(src_p[i]);
    }
}

void flip64bytes(void *dest_p, const uint8_t *src_p)
{
    uint32_t *dest = dest_p;
    uint32_t *src = (uint32_t *)src_p;
    int i;
    for (i = 0; i < 16; i++)
    {
        dest[i] = ReverseBits(src[i]);
    }
}

void flip64bytesbybyte(void *dest_p, const uint8_t *src_p)
{
    uint8_t *dest = dest_p;
    int i;
    for (i = 0; i < 64; i++)
    {
        dest[i] = ReverseEightBits(src_p[i]);
    }
}

void sha256_padding(const uint8_t *input, uint8_t *output, unsigned int count)
{
	int i, len_rem, block_nb;

	memset(output, 0, 2 * SHA256_BLOCK_SIZE);

	len_rem = count % SHA256_BLOCK_SIZE;
	block_nb = ((SHA256_BLOCK_SIZE - 9) < (len_rem % SHA256_BLOCK_SIZE));


	if (block_nb) {
		for (i = 0; i < len_rem; i++)
			output[i] = input[i];
		output[i] = 0x80;

		output[124] = ((count*8) & 0xff000000) >> 24;
		output[125] = ((count*8) & 0x00ff0000) >> 16;
		output[126] = ((count*8) & 0x0000ff00) >> 8;
		output[127] = ((count*8) & 0x000000ff);
	} else {
		for (i = 0; i < len_rem; i++)
			output[i] = input[i];
		output[i] = 0x80;
		output[60] = ((count*8) & 0xff000000) >> 24;
		output[61] = ((count*8) & 0x00ff0000) >> 16;
		output[62] = ((count*8) & 0x0000ff00) >> 8;
		output[63] = ((count*8) & 0x000000ff);
	}
}

// FIXME: not sure about this
void sha256_precalc(const uint8_t *h, const uint8_t *input, uint8_t *output, unsigned int count)
{
	int i;
	uint8_t temp[64];

	for (i = 0; i < 32; i += 4) {
		memcpy(temp + i, h + i, 4);
	}

        //sha256_padding(input + (count / SHA256_BLOCK_SIZE) * SHA256_BLOCK_SIZE, count);
}
