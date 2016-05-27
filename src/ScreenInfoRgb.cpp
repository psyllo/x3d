#include "ScreenInfoRgb.hpp"

/*
  See: l3d_0.4/source/app/lib/tool_2d/si_rgb.cc
*/

#include "../config.h"
#include <stdexcept>
#include <math.h>

namespace x3d {

  ScreenInfoRgb::ScreenInfoRgb
  (unsigned int red_mask, unsigned int green_mask, unsigned int blue_mask,
   unsigned char bytes_per_pixel, unsigned char bits_per_rgb)
    : red_mask(red_mask), green_mask(green_mask), blue_mask(blue_mask),
      bits_per_rgb(bits_per_rgb)
  {
    this->bytes_per_pixel = bytes_per_pixel;

    unsigned int max_rgb_value = ((int)pow(2, bits_per_rgb)) - 1;

    ext_max_red = max_rgb_value;
    ext_max_green = max_rgb_value;
    ext_max_blue = max_rgb_value;
  }

  uint64_t ScreenInfoRgb::reverseBits(const uint64_t n, const uint64_t k)
  {
    uint64_t r, i;
    for (r = 0, i = 0; i < k; ++i)
      r |= ((n >> i) & 1) << (k - i - 1);
    return r;
  }

  unsigned int ScreenInfoRgb::reverseRGB(const unsigned int r_g_or_b_value) {
    return reverseBits(r_g_or_b_value, bits_per_rgb);
  }

  unsigned int ScreenInfoRgb::extToNative(unsigned int red, unsigned int green, unsigned int blue) {
    unsigned int val = 0;

#if HAVE_XCB_XCB_H
    // This works for XCB and probably Xlib
    val = (red);
    val <<= bits_per_rgb;
    val += (green);
    val <<= bits_per_rgb;
    val += (blue);
#else
    // TODO: Write platform independent code
    throw std::invalid_argument("Only X11 supported");
#endif

    return val;
  }

}
