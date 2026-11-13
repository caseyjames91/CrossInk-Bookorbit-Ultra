#include "../../src/components/BookOrbitCoverCacheKey.h"
#include <cassert>
int main() {
  using bookorbit_cover::cacheFilename;
  assert(cacheFilename(0, "v1").empty());
  assert(cacheFilename(-1, "v1").empty());
  assert(cacheFilename(123, "v1") == cacheFilename(123, "v1"));
  assert(cacheFilename(123, "v1") != cacheFilename(123, "v2"));
  assert(cacheFilename(123, "v1") != cacheFilename(124, "v1"));
  assert(cacheFilename(123, "../weird/path") .find('/') == std::string::npos);
}
