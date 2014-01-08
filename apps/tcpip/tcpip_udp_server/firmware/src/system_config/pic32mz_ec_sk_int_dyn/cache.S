#include <xc.h>

#define C0_CONFIG       $16

#define CFG1_ILSHIFT    19
#define CFG1_DLSHIFT    10
#define CFG1_ISSHIFT    22
#define CFG1_DSSHIFT    23
#define CFG1_IASHIFT    16
#define CFG1_DASHIFT    07
#define C0_TAGLO        $28

#define K0_MASK         0x07
#define CACHE_MODE      0x03
/* #define CACHE_MODE      0x00 */

.set noreorder
.text
.global icache_init
.ent icache_init
icache_init:

    /* Determine how big the I$ is */
    mfc0 v0, C0_CONFIG, 1 /* read C0_Config1 */

    /* Isolate I$ Line Size */
    ext v1, v0, CFG1_ILSHIFT, 3

    /* Skip ahead if No I$ */
    beq v1, zero, done_icache
    nop

    li a2, 2
    sllv v1, a2, v1 /* Now have true I$ line size in bytes */

    ext a1, v0, CFG1_ISSHIFT, 3 /* extract IS */

    li a2, 64
    sllv a0, a2, a0 /* I$ Sets per way */

    /* Config1IA == I$ Assoc - 1 */
    ext a1, v0, CFG1_IASHIFT, 3
    add a1, 1

    mul a0, a0, a1 /* Total number of sets */

    lui a2, 0x9D00 /* Get a KSeg0 address for cache ops */

    /* Clear TagLo register */
    mtc0 zero, C0_TAGLO /* write C0_ITagLo */

    move a3, a0

next_icache_tag:
    /* Index Store Tag Cache Op */
    /* Will invalidate the tag entry, clear the lock bit, and clear */
    /* the LRF bit */
    cache 0x8, 0(a2)

    add a3, -1 /* Decrement set counter */
    bne a3, zero, next_icache_tag
    add a2, v1 /* Get next line address */

done_icache:
    jr ra
    nop
.end icache_init

.global dcache_init
.ent dcache_init
dcache_init:

    /* Determine how big the D$ is */
    mfc0 v0, C0_CONFIG, 1 /* read C0_Config1 */

    /* Isolate I$ Line Size */
    ext v1, v0, CFG1_DLSHIFT, 3

    /* Skip ahead if No D$ */
    beq v1, zero, done_dcache
    nop

    li a2, 2
    sllv v1, a2, v1 /* Now have true D$ line size in bytes */

    ext a1, v0, CFG1_DSSHIFT, 3 /* extract DS */

    li a2, 64
    sllv a0, a2, a0 /* D$ Sets per way */

    /* Config1IA == D$ Assoc - 1 */
    ext a1, v0, CFG1_DASHIFT, 3
    add a1, 1

    mul a0, a0, a1 /* Total number of sets */

    lui a2, 0x8000 /* Get a KSeg0 address for cache ops */

    /* Clear TagLo register */
    mtc0 zero, C0_TAGLO /* write C0_ITagLo */

    move a3, a0

next_dcache_tag:
    cache 0x9, 0(a2)

    add a3, -1 /* Decrement set counter */
    bne a3, zero, next_dcache_tag
    add a2, v1 /* Get next line address */

done_dcache:
    jr ra
    nop
.end dcache_init

.global cache_enable
.ent cache_enable
cache_enable:

    mfc0 v0, C0_CONFIG
    ori v0, K0_MASK
    xori v0, K0_MASK
    or v0, v0, a0
    mtc0 v0, C0_CONFIG

    jr ra
    nop

.end cache_enable
