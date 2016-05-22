#ifndef __RASTERIZER_HPP
#define __RASTERIZER_HPP
namespace x3d {
  class Rasterizer {
  public:
    Rasterizer() { }
    virtual ~Rasterizer() { }
    void drawPoint(int x, int y, unsigned long color);
    void drawLine(int x0, int y0, int x1, int y1, unsigned long color);
  protected:
    unsigned char* addressOfPoint(int x, int y);
    void drawPointAtAddress(unsigned char** p, unsigned long c);
  };
}
#endif
