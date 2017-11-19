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
    void drawPoint(int x, int y, unsigned int color);
    void drawLine(int x0, int y0, int x1, int y1, unsigned int color);
    void drawCircle(float r, int x, int y, unsigned int color);
    void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2,
                      unsigned int color);
    void drawPolygon(int *p, unsigned int color);
    void drawImage(char* path, int x, int y, int width, int height); // TODO

    // effects
    int pointillation = 0;
  protected:
    unsigned char* addressOfPoint(int x, int y);
    void drawPointAtAddress(unsigned char** p, unsigned int color);
  };
}
#endif
