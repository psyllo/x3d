#ifndef __X3D_SCREENINFORGB_HPP
#define __X3D_SCREENINFORGB_HPP

#include "ScreenInfo.hpp"
#include <stdint.h>

namespace x3d {

  class ScreenInfoRgb : public ScreenInfo {

  private:
    uint64_t reverseBits(const uint64_t n, const uint64_t k);

  protected:
    unsigned int reverseRGB(const unsigned int r_g_or_b_value);

  public:
    unsigned char bits_per_rgb;
    unsigned int red_mask, green_mask, blue_mask;
    unsigned int red_max, green_max, blue_max;

    ScreenInfoRgb(unsigned int red_mask, unsigned int green_mask,
                  unsigned int blue_mask, unsigned char bytes_per_pixel,
                  unsigned char bits_per_rgb);

    virtual ~ScreenInfoRgb() { }

    virtual unsigned int extToNative(unsigned int red, unsigned int green, unsigned int blue);
  };
}

#endif
