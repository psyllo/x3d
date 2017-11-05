#include "Rasterizer.hpp"

/*
  See: l3d_0.4/source/app/lib/raster/ras_sw.h
  See: Page 134 in book Linux 3D Graphics Programming by Norman Lin
 */

#include <cassert>
#include <algorithm>
#include <stdexcept>

namespace x3d {

  // TODO: unchecked boundary, no max-x nor max-y.
  unsigned char* Rasterizer::addressOfPoint(int x, int y) {
    if(x < width && y < height && x >= 0 && y >= 0)
      return sinfo->p_screenbuf + sinfo->bytes_per_pixel * (width*y + x);
    throw std::invalid_argument("Requested point is outside of screen buffer");
  }

  inline void Rasterizer::drawPointAtAddress(unsigned char** p, unsigned int color) {
    register int i;

    // One interation per byte in `color'
    for(i = 0; i < sinfo->bytes_per_pixel; i++) {
      *(*p + i) = color;
      color >>= BITS_PER_BYTE;
    }
  }

  void Rasterizer::drawPoint(int x, int y, unsigned int color) {
    if(x < width && y < height && x >= 0 && y >= 0) {
      unsigned char* point_address = addressOfPoint(x, y);
      drawPointAtAddress(&point_address, color);
    }
  }

  /*
     See: l3d_0.4/source/app/lib/raster/ras_sw.cc

     TODO: LEFT_OFF: write function to draw lines
   */
  void Rasterizer::drawLine(int x0, int y0, int x1, int y1, unsigned int color) {
    float fx,fy,m;
    int x,y,tmp,dx,dy;

    dx = x1 - x0;
    dy = y1 - y0;

    if(abs(dx) > abs(dy)) { //- a "mostly horizontal" line
      //- ensure (x0,y0) is horizontally smaller than (x1,y1)
      if(x1<x0) { tmp=x0;x0=x1;x1=tmp; tmp=y0;y0=y1;y1=tmp;}
      fy = y0;
      m = (float)dy / (float)dx;
      for(x=x0; x<=x1; x++) {
        drawPoint(x,
                  (height, // TODO: Y-reversal?
                   (int) (fy+0.5)),
                  color);
        fy = fy + m;
      }
    }
    else { //- mostly vertical line
      //- ensure (x0,y0) is vertically smaller than (x1,y1)
      if(y1<y0) { tmp=x0;x0=x1;x1=tmp; tmp=y0;y0=y1;y1=tmp;}
      fx = (float)x0;
      if( !(float)dy) return; //- degenerate: line is just a point
      m = (float)dx / (float)dy;
      for(y=y0; y<=y1; y++) {
        drawPoint((int)fx+0.5,
                  (height,y), // TODO: Y-reversal?
                  color);
        fx = fx + m;
      }
    }
  }

  void Rasterizer::drawCircle(float r, int x, int y) {
    double increment = 1/r;
    for(double i = 0.0; i < 2* 3.14; i += increment) {
      drawPoint((int)x+cos(i)*r,
                (int)y+sin(i)*r,
                sinfo->extToNative(204, 102, 0));
    }
  }

}
