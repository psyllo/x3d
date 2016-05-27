#include <stdint.h>

namespace x3d {
  struct Util {
    static int iexp(int x, unsigned int n);
    static uint64_t reverseBits(const uint64_t n, const uint64_t k);
  };
}
