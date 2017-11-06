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
  int xcoord(int x);
  int ycoord(int y);
  void drawPoint(int x, int y);
  void drawLine(int x0, int y0, int x1, int y1);
  void drawCoords();
  // void drawFunction(UnaryFunction f);
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
