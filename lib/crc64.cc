#include "crucible/crc64.h"

#include <xxhash.h>

#include <iostream>
#include <string>
#include <vector>

#define XXH_STATIC_LINKING_ONLY // Gives access to advanced algorithms like XXH3

namespace crucible {

	uint64_t
	Digest::CRC::crc64(const void *p, size_t len)
	{
    XXH64_hash_t hash64 = XXH3_64bits_withSeed(p, len, 0);
		return hash64;
	}


};
