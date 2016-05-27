#include "Util.hpp"

namespace x3d {

  /*
    Integer exponentation
    See: Hacker's Delight (Warren) pg. 289.
  */
  int Util::iexp(int x, unsigned int n) {
    if(x == 0) return 0;

    int p, y;

    y = 1;
    p = x;
    while(1) {
      if(n & 1) y = p*y;
      n = n >> 1;
      if(n == 0) return y;
      p = p*p;
    }
  }

  uint64_t Util::reverseBits(const uint64_t n, const uint64_t k)
  {
    uint64_t r, i;
    for (r = 0, i = 0; i < k; ++i)
      r |= ((n >> i) & 1) << (k - i - 1);
    return r;
  }

}
