#ifndef __X3D_SCREENFACTORY_HPP
#define __X3D_SCREENFACTORY_HPP

#include "Screen.hpp"

namespace x3d {

  class ScreenFactory {
  public:
    virtual Screen* create() = 0;
  };

}

#endif
