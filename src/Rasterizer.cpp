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

  inline void Rasterizer::drawPointAtAddress(unsigned char** p, unsigned long color) {
    // TODO: LEFT_OFF

    register int i;
    unsigned long mask = MAX_BYTE;
    char shift = 0;

    // stuff the bytes in the unsigned long color into the screen buffer, in
    // little-endian order
    for(i = 0; i < sinfo->bytes_per_pixel; i++) {
      **p = (color & mask) >> shift;
      (*p)++;
      mask <<= BITS_PER_BYTE;
      shift += BITS_PER_BYTE;
    }
  }

  void Rasterizer::drawPoint(int x, int y, unsigned long color) {
    unsigned char* point_address = addressOfPoint(x, y);
    assert(point_address);
    drawPointAtAddress(&point_address, color);
  }

  void drawLine(int x0, int y0, int x1, int y1, unsigned long color) {
    // TODO: write function
  }

}
