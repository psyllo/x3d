#ifndef __X3D_SCREEN_HPP
#define __X3D_SCREEN_HPP

#include "EventSource.hpp"

namespace x3d {

  class Screen : public EventSource {
  public:
    virtual bool init() = 0;
    virtual bool open() = 0;
    virtual bool close() = 0;
  };
}

#endif
