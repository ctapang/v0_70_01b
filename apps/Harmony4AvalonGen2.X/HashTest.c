// Hash Test
// Test both firmware and hashing chips
// Centerus Inc.

#include "app.h"
#include "sha256.h"
#include "GenericTypeDefs.h"
#include "condominer.h"

#define	bswap_16(value)  \
 	((((value) & 0xff) << 8) | ((value) >> 8))

#define	bswap_32(value)	\
 	(((uint32_t)bswap_16((uint16_t)((value) & 0xffff)) << 16) | \
 	(uint32_t)bswap_16((uint16_t)((value) >> 16)))

#define	bswap_64(value)	\
 	(((uint64_t)bswap_32((uint32_t)((value) & 0xffffffff)) \
 	    << 32) | \
 	(uint64_t)bswap_32((uint32_t)((value) >> 32)))


/* This assumes htobe32 is a macro in endian.h, and if it doesn't exist, then
 * htobe64 also won't exist */
#ifndef htobe32
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define htole16(x) (x)
#  define le16toh(x) (x)
#  define htole32(x) (x)
#  define htole64(x) (x)
#  define le32toh(x) (x)
#  define le64toh(x) (x)
#  define be32toh(x) bswap_32(x)
#  define be64toh(x) bswap_64(x)
#  define htobe16(x) bswap_16(x)
#  define htobe32(x) bswap_32(x)
#  define htobe64(x) bswap_64(x)
# elif __BYTE_ORDER == __BIG_ENDIAN
#  define htole16(x) bswap_16(x)
#  define le16toh(x) bswap_16(x)
#  define htole32(x) bswap_32(x)
#  define le32toh(x) bswap_32(x)
#  define le64toh(x) bswap_64(x)
#  define htole64(x) bswap_64(x)
#  define be32toh(x) (x)
#  define be64toh(x) (x)
#  define htobe16(x) (x)
#  define htobe32(x) (x)
#  define htobe64(x) (x)
#else
#error UNKNOWN BYTE ORDER
#endif
#endif

extern WORKSTATUS Status;
extern uint32 hInitial[];

static void regen_hash(WORKTASK *work)
{
    uint32_t *data32 = (uint32_t *)(work->Data);
    unsigned char swap[80];
    uint32_t *swap32 = (uint32_t *)swap;
    unsigned char hash1[32];

    sha256_context ctx;
    unsigned char buf[1000];
    unsigned char sha256sum[32];

//    flip80(swap32, data32);
//    sha256(swap, 80, hash1);
//    sha256(hash1, 32, (unsigned char *)(work->hash));
    // first pass
    sha256_starts( &ctx, hInitial, false );
    sha256_update( &ctx, swap, 80);
}

/* Fills in the work nonce and builds the output data in work->hash */
static void rebuild_nonce(WORKTASK *work, uint32_t nonce)
{
	uint32_t *work_nonce = (uint32_t *)(work->Data + 64 + 12);

	*work_nonce = htole32(nonce);

	regen_hash(work);
}

/* For testing a nonce against diff 1 */
bool test_nonce(WORKTASK *work, uint32_t nonce)
{
	uint32_t *hash_32 = (uint32_t *)(work->Hash + 28);

	rebuild_nonce(work, nonce);
	return (*hash_32 == 0);
}

/* For testing a nonce against an arbitrary diff */
bool test_nonce_diff(WORKTASK *work, uint32_t nonce, double diff)
{
	uint64_t *hash64 = (uint64_t *)(work->Hash + 24), diff64;

	rebuild_nonce(work, nonce);
	diff64 = 0x00000000ffff0000ULL;
	diff64 /= diff;

	return (le64toh(*hash64) <= diff64);
}

