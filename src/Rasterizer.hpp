#ifndef __X3D_RASTERIZER_HPP
#define __X3D_RASTERIZER_HPP

/*
  A rasterizer talks only to the ScreenInfo, to find out what it
  needs to know about the display in order to do rasterization.
 */

#include "ScreenInfo.hpp"

namespace x3d {

  class Rasterizer {

  public:
    ScreenInfo* sinfo;
    unsigned short width, height;
    Rasterizer(ScreenInfo *screen_info, unsigned short screen_width, unsigned short screen_height) 
      : sinfo(screen_info), width(screen_width), height(screen_height) { }
    virtual ~Rasterizer() { }
    void drawPoint(int x, int y, unsigned long color);
    void drawLine(int x0, int y0, int x1, int y1, unsigned long color);

  protected:
    unsigned char* addressOfPoint(int x, int y);
    void drawPointAtAddress(unsigned char** p, unsigned long color);
  };
}
#endif
