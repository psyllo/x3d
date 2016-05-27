#include "Rasterizer.hpp"

/*
  See: l3d_0.4/source/app/lib/raster/ras_sw.h
  See: Page 134 in book Linux 3D Graphics Programming by Norman Lin
 */

#include <cassert>

namespace x3d {

  // TODO: unchecked boundary, no max-x nor max-y.
  unsigned char* Rasterizer::addressOfPoint(int x, int y) {
    return sinfo->p_screenbuf + sinfo->bytes_per_pixel * (width*y + x);
  }

  inline void Rasterizer::drawPointAtAddress(unsigned char** p, unsigned int color) {
    register int i;

    // One interation per byte in `color'
    for(i = 0; i < sinfo->bytes_per_pixel; i++) {
      *(*p + i) = color;
      color >>= BITS_PER_BYTE;
    }


    // From L3D
    // // stuff the bytes in the unsigned int color into the screen buffer, in
    // // little-endian order
    // register int i;
    // unsigned int mask = MAX_BYTE;
    // char shift = 0;
    // for(i = 0; i < sinfo->bytes_per_pixel; i++) {
    //   **p = (color & mask) >> shift;
    //   (*p)++;
    //   mask <<= BITS_PER_BYTE;
    //   shift += BITS_PER_BYTE;
    // }
  }

  void Rasterizer::drawPoint(int x, int y, unsigned int color) {
    unsigned char* point_address = addressOfPoint(x, y);
    drawPointAtAddress(&point_address, color);
  }

  void drawLine(int x0, int y0, int x1, int y1, unsigned int color) {
    // TODO: LEFT_OFF: write function to draw lines
  }

}
