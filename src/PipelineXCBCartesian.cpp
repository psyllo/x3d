#include "PipelineXCBCartesian.hpp"

#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

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

// void PipelineXCBCartesian::drawFunction(UnaryFunction f) {
  
//}

void PipelineXCBCartesian::drawEvent() {
  assert(ras);

  drawAxis();

  drawLine(-10,  10, -100,  50);
  drawLine( 10, -10,  100, -50);
  drawLine(-10, -10, -100, -50);
  drawLine( 10,  10,  100,  50);

  drawCircle(10, 25, 25);

  screen->blit();
}

void PipelineXCBCartesian::updateEvent() {
}

void PipelineXCBCartesian::keyEvent() {
}
