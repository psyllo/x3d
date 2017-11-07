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
  for(int i = -ras->width/2; i < ras->width/2; i++) {
    double x = i * (range_end - range_start) / ras->width;
    double y = (*f)(x) * 50;
    drawPoint(i, (int)y);
  }
}

// void cosine(float rad){
// }

void PipelineXCBCartesian::drawEvent() {
  assert(ras);

  drawAxis();

  drawLine(-10,  10, -100,  50);
  drawLine( 10, -10,  100, -50);
  drawLine(-10, -10, -100, -50);
  drawLine( 10,  10,  100,  50);

  drawCircle(50, 25, 25);

  drawFunction(cos, -3.14 * 3, 3.14 * 3);

  screen->blit();
}

void PipelineXCBCartesian::updateEvent() {
}

void PipelineXCBCartesian::keyEvent() {
}
