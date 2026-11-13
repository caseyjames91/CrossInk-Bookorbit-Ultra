#pragma once
// Stable, filesystem-safe identifiers for cached BookOrbit cover thumbnails.
// No dependency on the display or network stack; usable in host tests.
#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>

namespace bookorbit_cover {
inline uint32_t revisionHash(std::string_view revision) {
  uint32_t hash = 2166136261u;  // FNV-1a
  for (unsigned char c : revision) {
    hash ^= c;
    hash *= 16777619u;
  }
  return hash;
}
inline std::string cacheFilename(int64_t bookId, std::string_view revision) {
  if (bookId <= 0) return {};
  char filename[48];
  std::snprintf(filename, sizeof(filename), "%lld-%08lx.bin", static_cast<long long>(bookId),
                static_cast<unsigned long>(revisionHash(revision)));
  return filename;
}
}  // namespace bookorbit_cover
