#include "crucible/crc64.h"
extern "C"
{
#include <xxhash.h>
}

namespace crucible {

	uint64_t
	Digest::CRC::crc64(const void *p, size_t len)
	{
		return XXH64(p, len, 0);
	}


};
