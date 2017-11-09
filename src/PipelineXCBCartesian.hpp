#ifndef __PIPELINEXCBCARTESIAN_HPP
#define __PIPELINEXCBCARTESIAN_HPP

#include "Pipeline.hpp"
#include "Rasterizer.hpp"
#include "Screen.hpp"
#include <algorithm>

using namespace x3d;

class PipelineXCBCartesian : public Pipeline {
  bool _done;
protected:
  Rasterizer* ras;
  Screen* screen;
  unsigned int rgbColor(int r, int g, int b);
  int xcoord(int x);
  int ycoord(int y);
  void drawPoint(int x, int y, unsigned int color);
  void drawLine(int x0, int y0, int x1, int y1, unsigned int color);
  void drawAxis();
  void drawCircle(float r, int x, int y, unsigned int color);
  //void drawFunction(int (*f)(int x));
  void drawFunction(double (*f)(double), double range_start, double range_end,
                    unsigned int color);
  void drawFunction(double (*f)(double), double range_start, double range_end);
public:
  PipelineXCBCartesian(Rasterizer *r, Screen* screen)
    : _done(false), ras(r), screen(screen) { }
  virtual void drawEvent();
  virtual void updateEvent();
  virtual void keyEvent();
  virtual void setDone(bool done) { _done = done; }
  virtual bool isDone() { return _done; }
};


#endif
