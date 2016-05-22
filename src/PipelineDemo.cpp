#include "PipelineDemo.hpp"
#include "Rasterizer.hpp"
#include <iostream>
#include <cassert>

namespace x3d {

  void PipelineDemo::drawEvent() {
    Rasterizer ras;
    ras.drawPoint(10, 10, 100);
    // TODO: LEFT_OFF
  }

  void PipelineDemo::updateEvent() {
  }

  void PipelineDemo::keyEvent() {
  }

}
