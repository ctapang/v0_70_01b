/*
 * Author: Xiangfu Liu <xiangfu@openmobilefree.net>
 * Bitcoin:	1CanaaniJzgps8EV6Sfmpb7T8RutpaeyFn
 *
 * This is free and unencumbered software released into the public domain.
 * For details see the UNLICENSE file at the root of the source tree.
 */

#ifndef _SHA256_H_
#define _SHA256_H_

#include <stdint.h>

//#define SHA256_DIGEST_SIZE (256 / 8)
//#define SHA256_BLOCK_SIZE  (512 / 8)
//
//
///* SHA256
// * Please read http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf
// * Example here: http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
// * 1. Write the CMD_INIT
// * 2. Wait the CMD_DONE when write every 512bits data
// *    You may need pad the data to 512bits
// * 3. Wait teh CMD_DONE. read the result out
// */
//
//typedef struct pic_sha256 {
//	volatile unsigned int cmd;
//	volatile unsigned int din;
//	volatile unsigned int hash;
//	volatile unsigned int hi;
//	volatile unsigned int pre; /* Please read the A3255 datasheet */
//} pic32_sha256;
//

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

typedef struct
{
    uint32 total[2];
    uint32 state[8];
    uint8 buffer[64];
    bool precalc;
}
sha256_context;

void flip4SPI(void *dest_p, const uint8_t *src_p, size_t len);
void sha256_precalc(const uint32 *h, const uint8_t *input, unsigned int count, uint8_t *state);

void sha256_starts( sha256_context *ctx, const uint32 *midstate, bool precalc );
void sha256_update( sha256_context *ctx, const uint8 *input, uint32 length );
void sha256_finish( sha256_context *ctx, uint8 digest[32] , int par2 /* = 0 */);

int sha256_test();

#endif	/* _SHA256_H_ */
