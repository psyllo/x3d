#include "PipelineXCBdemo.hpp"

#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

using namespace x3d;

void PipelineXCBdemo::drawEvent() {
  assert(ras);
  ras->drawPoint(5, 5, screen->getInfo()->extToNative(150, 150, 150));
  // TODO: LEFT_OFF: Use rasterizer to draw stuff
  screen->blit();
}

void PipelineXCBdemo::updateEvent() {
}

void PipelineXCBdemo::keyEvent() {
}
