#ifndef __X3D_SCREENINFORGB_HPP
#define __X3D_SCREENINFORGB_HPP

#include "ScreenInfo.hpp"

namespace x3d {

  // TODO: LEFT_OFF
  class ScreenInfoRgb : public ScreenInfo {

  public:
    char bytes_per_rgb;
    unsigned long red_mask, green_mask, blue_mask;
    int red_shift, green_shift, blue_shift,
    red_max, green_max, blue_max;

    ScreenInfoRgb(unsigned long red_mask, unsigned long green_mask,
                  unsigned long blue_mask, char bytes_per_pixel, char bytes_per_rgb);

    virtual ~ScreenInfoRgb() { }

    virtual unsigned long extToNative(int red, int green, int blue);

    void computeColorResolution();
  };
}

#endif
