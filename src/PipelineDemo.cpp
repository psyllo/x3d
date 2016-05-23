#include "PipelineDemo.hpp"
#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

namespace x3d {

  void PipelineDemo::drawEvent() {
    assert(ras);
    ras->drawPoint(10, 10, 100); // TODO: 100 is supposed to be a color
    // TODO: LEFT_OFF: Use rasterizer to draw stuff
  }

  void PipelineDemo::updateEvent() {
  }

  void PipelineDemo::keyEvent() {
  }

}
