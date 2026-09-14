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
    uint64_t hash64 = XXH64(p, len, 0);
		return hash64;
	}


};
