#ifndef __X3D_SCREEN_H
#define __X3D_SCREEN_H

#include "EventSource.hpp"

namespace x3d {
  
  class Screen : public EventSource {
  public:
    virtual ~Screen() {}
    virtual bool init() = 0;
    virtual bool open() = 0;
    virtual bool close() = 0;
  };
}

#endif
