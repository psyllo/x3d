#ifndef __RASTERIZER_HPP
#define __RASTERIZER_HPP

/*
  A rasterizer talks only to the ScreenInfo, to find out what it
  needs to know about the display in order to do rasterization.
 */

#include "ScreenInfo.hpp"

namespace x3d {

  class Rasterizer {

  public:
    ScreenInfo* scninfo;

    Rasterizer(ScreenInfo *screen_info) : scninfo(screen_info) { }
    virtual ~Rasterizer() { }
    void drawPoint(int x, int y, unsigned long color);
    void drawLine(int x0, int y0, int x1, int y1, unsigned long color);

  protected:
    unsigned char* addressOfPoint(int x, int y);
    void drawPointAtAddress(unsigned char** p, unsigned long c);
  };
}
#endif
