#include "PipelineImpl.hpp"
#include <iostream>
#include <cassert>

namespace x3d {

  void PipelineImpl::drawEvent() {
  }

  void PipelineImpl::updateEvent() {
    std::cerr << "updateEvent()" << std::endl;
  }

  void PipelineImpl::keyEvent() {
  }

}
