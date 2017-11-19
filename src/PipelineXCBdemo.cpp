#include "PipelineXCBdemo.hpp"

#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

using namespace x3d;

void PipelineXCBdemo::drawEvent() {
  assert(ras);

  // Draw pixels. This draws some colors in the upper left.
  for(int i = 0 ; i < 5; i++) {
    ras->drawPoint( 0 + i, 0, screen->getInfo()->extToNative(255, 255, 255));
    ras->drawPoint(10 + i, 0, screen->getInfo()->extToNative(255,   0, 0));
    ras->drawPoint(20 + i, 0, screen->getInfo()->extToNative(0,   255, 0));
    ras->drawPoint(30 + i, 0, screen->getInfo()->extToNative(0,     0, 255));
    ras->drawPoint(40 + i, 0, screen->getInfo()->extToNative(204, 102, 0));
    ras->drawPoint(50 + i, 0, screen->getInfo()->extToNative(178, 102, 255));
    ras->drawPoint(60 + i, 0, screen->getInfo()->extToNative(153,   0, 76));
  }

  // Draw lines
  // ras->drawLine(10, 10, 200, 200, screen->getInfo()->extToNative(204, 102, 0)); // diag
  // ras->drawLine(20, 10, 200, 200, screen->getInfo()->extToNative(178, 102, 255)); // x > y
  // ras->drawLine(10, 20, 200, 200, screen->getInfo()->extToNative(153,   0, 76)); // y > x

  // Draw circles
  ras->drawCircle(165, 160, 160, screen->getInfo()->extToNative(88, 34, 10));

  // Draw Triangle
  // ras->drawTriangle(0, 0, 100, 150, 300, 200, screen->getInfo()->extToNative(248, 202, 40));
  // ras->pointillation = 2;
  // ras->drawTriangle(200, 200, 100, 100, 9, 221, screen->getInfo()->extToNative(178, 102, 255));
  // ras->pointillation = 3;
  // ras->drawTriangle(50, 50, 90, 150, 290, 20, screen->getInfo()->extToNative(100, 230, 100));
  // ras->pointillation = 0;

  // Draw Polygon
  point2_t** ps = (point2_t**) malloc(4 * sizeof(point2_t*));
  ps[0] = (point2_t*) malloc(sizeof(point2_t));
  ps[1] = (point2_t*) malloc(sizeof(point2_t));
  ps[2] = (point2_t*) malloc(sizeof(point2_t));
  ps[3] = (point2_t*) malloc(sizeof(point2_t));
  ps[0]->x = 100;
  ps[0]->y = 100;
  ps[1]->x = 150;
  ps[1]->y = 100;
  ps[2]->x = 200;
  ps[2]->y = 180;
  ps[3]->x = 250;
  ps[3]->y = 250;

  ras->drawPolygon(ps, 4, screen->getInfo()->extToNative(160, 160, 160));

  // Draw images
  // ras->drawImage("/usr/share/pixmaps/faces/baseball.jpg", 0, 0, 200, 200);

  screen->blit();
}

void PipelineXCBdemo::updateEvent() {
}

void PipelineXCBdemo::keyEvent() {
}
