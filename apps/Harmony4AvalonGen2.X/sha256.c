/*
 * Author: C. Tapang
 * Copyright(R): Centerus Inc.
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "peripheral/spi/plib_spi.h"
#include "system/common/sys_common.h"
#include "byte_manipulation.h"
#include "sha256.h"


inline SPI_DATA_TYPE ReverseBits( SPI_DATA_TYPE value )
{
    SPI_DATA_TYPE outValue = 0;
    SPI_DATA_TYPE probe = 1;
    SPI_DATA_TYPE bitSet = 1 << (8 * sizeof(SPI_DATA_TYPE) - 1); // 0x80000000;
    while(probe)
    {
        if (value & probe)
            outValue |= bitSet;
        probe <<= 1;
        bitSet >>= 1;
    }
    return outValue;
}

void flip4SPI(void *dest_p, const uint8_t *src_p, size_t len)
{
    SYS_ASSERT(((len % sizeof(SPI_DATA_TYPE)) == 0), "buffer length has to be a multiple of SPI_DATA_TYPE size");
    SPI_DATA_TYPE *dest = dest_p;
    SPI_DATA_TYPE *src = (SPI_DATA_TYPE *)src_p;
    int count = len / sizeof(SPI_DATA_TYPE);
    int i;
    for (i = 0; i < count; i++)
    {
        dest[i] = ReverseBits(src[i]);
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
