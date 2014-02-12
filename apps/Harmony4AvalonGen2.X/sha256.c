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

//Initialize hash values:
//(first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
uint32_t h0 = 0x6a09e667;
uint32_t h1 = 0xbb67ae85;
uint32_t h2 = 0x3c6ef372;
uint32_t h3 = 0xa54ff53a;
uint32_t h4 = 0x510e527f;
uint32_t h5 = 0x9b05688c;
uint32_t h6 = 0x1f83d9ab;
uint32_t h7 = 0x5be0cd19;

//Initialize array of round constants:
//(first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
uint32_t k[] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };



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

int sha256_padding(const uint8_t *input, uint8_t *output, unsigned int count)
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
                return 2 * SHA256_BLOCK_SIZE;
	} else {
		for (i = 0; i < len_rem; i++)
			output[i] = input[i];
		output[i] = 0x80;
		output[60] = ((count*8) & 0xff000000) >> 24;
		output[61] = ((count*8) & 0x00ff0000) >> 16;
		output[62] = ((count*8) & 0x0000ff00) >> 8;
		output[63] = ((count*8) & 0x000000ff);
                return SHA256_BLOCK_SIZE;
	}
}

// Pre-calculate a and e for first 3 rounds, given input.
void sha256_precalc(const uint8_t *input, uint32_t *aa, uint32_t *ee, unsigned int count)
{
	int i;
        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        uint32_t t1, t2, S0, S1, Ch, maj;
        uint32_t *w = (uint32_t *)input;

	for (i = 0; i < 3; i++) {
            S1 = (e >> 6) ^ (e >> 11) ^ (e >> 25);
            Ch = (e & f) ^ ((e ^ 0xffffffff) & g);
            t1 = h + S1 + Ch + k[i] + w[i];
            S0 = (a >> 2) ^ (a >> 13) ^ (a >> 22);
            maj = (a & b) ^ (a & c) ^ (b & c);
            t2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;

            aa[i] = a;
            ee[i] = e;
	}
}
