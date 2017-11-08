#include "PipelineXCBCartesian.hpp"

#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace x3d;

int PipelineXCBCartesian::xcoord(int x) {
  return x + (ras->width)/2;
}

int PipelineXCBCartesian::ycoord(int y) {
  return -y + (ras->height)/2;
}

void PipelineXCBCartesian::drawPoint(int x, int y) {
  ras->drawPoint(xcoord(x), ycoord(y),
                 screen->getInfo()->extToNative(204, 102, 0));
}

void PipelineXCBCartesian::drawLine(int x0, int y0, int x1, int y1) {
  ras->drawLine(xcoord(x0), ycoord(y0), xcoord(x1), ycoord(y1),
                screen->getInfo()->extToNative(204, 102, 0));
}

void PipelineXCBCartesian::drawAxis() {
  ras->drawLine(0, ras->height/2, ras->width-1, ras->height/2,
                screen->getInfo()->extToNative(204, 102, 0));
  ras->drawLine(ras->width/2, 0, ras->width/2, ras->height-1,
                screen->getInfo()->extToNative(204, 102, 0));
}

void PipelineXCBCartesian::drawCircle(float r, int x, int y) {
  ras->drawCircle(r, x + (ras->width-1)/2, -y + (ras->height-1)/2);
}

void PipelineXCBCartesian::drawFunction(double (*f)(double),
                                        double range_start, double range_end)
{
  int end_x   = ras->width/2;
  int start_x = -end_x;
  int x, y, y_prev, y_diff = 0;
  double f_arg, f_result = 0.0;
  for(x = start_x; x < end_x; x++) {
    f_arg = x * (range_end - range_start) / ras->width;
    f_result = (*f)(f_arg) * 50; // TODO: scale this by some other arg or state
    y = f_result; // TODO: Not rounding up looks better?
    y_diff = y - y_prev;
    if(x == start_x) {
      drawPoint(x, y);
    }else if(y_diff > 1) {
      drawLine(x, y + 1, x, y);
    }else if(y_diff < -1){
      drawLine(x, y - 1, x, y);
    }else{
      drawPoint(x, y);
    }
    y_prev = y;
  }
}

void PipelineXCBCartesian::drawEvent() {
  assert(ras);

  // drawAxis();

  // drawLine(10,  10, 10, 5);
  // drawLine( 10, -10,  100, -50);
  // drawLine(-10, -10, -100, -50);
  // drawLine( 10,  10,  100,  50);

  //drawCircle(50, 25, 25);

  // drawFunction(cos, -3.14 * 3, 3.14 * 3);
  drawFunction(sin, -3.14 * 3, 3.14 * 3);

  screen->blit();
}

void PipelineXCBCartesian::updateEvent() {
}

void PipelineXCBCartesian::keyEvent() {
}
