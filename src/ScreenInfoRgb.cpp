#include "ScreenInfoRgb.hpp"

/*
  See: l3d_0.4/source/app/lib/tool_2d/si_rgb.cc
 */

namespace x3d {

  ScreenInfoRgb::ScreenInfoRgb
  (unsigned long red_mask, unsigned long green_mask, unsigned long blue_mask,
   char bytes_per_pixel, char bytes_per_rgb)
    : red_mask(red_mask), green_mask(green_mask), blue_mask(blue_mask),
      bytes_per_rgb(bytes_per_rgb)
    {
      this->bytes_per_pixel = bytes_per_pixel;

      //- initial reasonable default values for external max rgb values; these
      //- can be overridden just before actually reading rgb values from an
      //- external source
      ext_max_red = 255;
      ext_max_green = 255;
      ext_max_blue = 255;

      computeColorResolution();
    }


  unsigned long ScreenInfoRgb::extToNative(int red, int green, int blue) {
    unsigned long red_rescaled, green_rescaled, blue_rescaled;

    red_rescaled = red * red_max / ext_max_red;
    green_rescaled = green * green_max / ext_max_green;
    blue_rescaled = blue * blue_max / ext_max_blue;

    return (red_rescaled<<red_shift)
      | (green_rescaled<<green_shift)
      | (blue_rescaled<<blue_shift);
  }

  void ScreenInfoRgb::computeColorResolution() {
    int red_mask_tmp=red_mask,
      green_mask_tmp=green_mask,
      blue_mask_tmp=blue_mask;

    // determine number of bits of resolution for r, g, and b

    // note that the max values go from 0 to xxx_max, meaning the total
    // count (as needed in for loops for instance) is xxx_max+1

    for(red_shift=0;
        (red_mask_tmp & 0x01) == 0 ;
        red_shift++, red_mask_tmp>>=1);
    for(red_max=1;
        (red_mask_tmp & 0x01) == 1 ;
        red_max*=2, red_mask_tmp>>=1);
    red_max--;

    for(green_shift=0;
        (green_mask_tmp & 0x01) == 0 ;
        green_shift++, green_mask_tmp>>=1);
    for(green_max=1;
        (green_mask_tmp & 0x01) == 1 ;
        green_max*=2, green_mask_tmp>>=1);
    green_max--;

    for(blue_shift=0;
        (blue_mask_tmp & 0x01) == 0 ;
        blue_shift++, blue_mask_tmp>>=1);
    for(blue_max=1;
        (blue_mask_tmp & 0x01) == 1 ;
        blue_max*=2, blue_mask_tmp>>=1);
    blue_max--;

  }
}
