#include "tests.h"
#include "crucible/crc64.h"

#include <cassert>

using namespace crucible;

static
void
test_getcrc64_byte_arrays()
{
	assert(Digest::CRC::crc64("John", 4) == 5942451273432301568);
	assert(Digest::CRC::crc64("Paul", 4) == 5838402100630913024);
	assert(Digest::CRC::crc64("George", 6) == 6714394476893704192);
	assert(Digest::CRC::crc64("Ringo", 5) == 6038837226071130112);
	assert(Digest::CRC::crc64("", 0) == 0);
	assert(Digest::CRC::crc64("\377\277\300\200", 4) == 15615382887346470912ULL);
	assert(Digest::XXHASH::xxh("John", 4) == 0x46034394ee588447ULL);
	assert(Digest::XXHASH::xxh("Paul", 4) == 0xa3c9fd9dff86779aULL);
	assert(Digest::XXHASH::xxh("George", 6) == 0x88290fd774650a6aULL);
	assert(Digest::XXHASH::xxh("Ringo", 5) == 0xb8cf4b3e794e8447ULL);
	assert(Digest::XXHASH::xxh("", 0) == 0xef46db3751d8e999ULL);
	assert(Digest::XXHASH::xxh("\xff\xbf\xc0\x80", 4) == 0xa27779a498caa211ULL);
}

int
main(int, char**)
{
	RUN_A_TEST(test_getcrc64_byte_arrays());

	exit(EXIT_SUCCESS);
}
