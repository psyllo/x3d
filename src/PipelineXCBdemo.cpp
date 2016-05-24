#include "PipelineXCBdemo.hpp"

#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

using namespace x3d;

void PipelineXCBdemo::drawEvent() {
  assert(ras);
  ras->drawPoint(10, 10, 100); // TODO: 100 is supposed to be a color
  // TODO: LEFT_OFF: Use rasterizer to draw stuff
}

void PipelineXCBdemo::updateEvent() {
}

void PipelineXCBdemo::keyEvent() {
}
