# bees: native Btrfs csum patch

Target: Zygo/bees `master`

## What the patch does

- Keeps the existing 16-byte hash-table cells (`uint64_t hash + uint64_t address`).
- Adds `BeesHash::from_btrfs_csum()` to convert Btrfs checksum bytes into the
  existing 64-bit table key.
- Changes `BeesBlockData::hash()` to first look up the checksum in the existing
  `BtrfsCsumTreeFetcher`.
- Supports the native Btrfs checksum width without adding crypto-library
  dependencies:
  - 4-byte CRC32C
  - 8-byte XXHASH64
  - 32-byte SHA256
  - 32-byte BLAKE2B
- Keeps the existing CRC64 calculation as a fallback when the Btrfs checksum is
  unavailable, the extent has no CSUM_TREE entry (for example NODATASUM), or
  the requested 4K block is not on a Btrfs sector boundary.
- Preserves bees' full data comparison before dedupe, so the 64-bit projection
  remains only a candidate-selection hash.

## Important limitation

The bees hash table is structurally 64-bit. A 32-byte Btrfs checksum therefore
cannot be stored losslessly without redesigning the table. The patch uses the
first eight checksum bytes as the table key.

For maximum hit rate after switching hash domains, remove/recreate the existing
`beeshash.dat` once.

## Recommended validation

1. Build bees.
2. Run on a disposable/test Btrfs filesystem.
3. Check that both csum-backed and fallback counters appear:
   - `block_hash_btrfs_csum`
   - `block_hash_crc64_fallback`
4. Run a normal dedupe workload and verify `FILE_EXTENT_SAME` results.
5. Inspect the filesystem checksum tree with:
   `btrfs inspect-internal dump-tree -t 7 <device>`
6. Test at least:
   - CRC32C filesystem
   - XXHASH64 filesystem
   - SHA256 filesystem
   - BLAKE2B filesystem
   - compressed extent
   - NODATASUM extent
   - filesystem sector size larger than 4096 bytes

## Patch quality note

This is a source-level patch against the current upstream layout. The generated
environment cannot clone the Git repository itself, so the patch is intentionally
provided rather than claiming a local build/test was performed.
