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

#define SHA256_DIGEST_SIZE (256 / 8)
#define SHA256_BLOCK_SIZE  (512 / 8)


/* SHA256
 * Please read http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf
 * Example here: http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
 * 1. Write the CMD_INIT
 * 2. Wait the CMD_DONE when write every 512bits data
 *    You may need pad the data to 512bits
 * 3. Wait teh CMD_DONE. read the result out
 */

typedef struct pic_sha256 {
	volatile unsigned int cmd;
	volatile unsigned int din;
	volatile unsigned int hash;
	volatile unsigned int hi;
	volatile unsigned int pre; /* Please read the A3255 datasheet */
} pic32_sha256;

void flip4SPI(void *dest_p, const uint8_t *src_p, size_t len);
void sha256_padding(const uint8_t *input, uint8_t *output, unsigned int count);
//void sha256_precalc(const uint8_t *h, const uint8_t *input, uint8_t *output, unsigned int count);

#endif	/* _SHA256_H_ */
