#ifndef __X3D_APPLICATIONFACTORY_HPP
#define __X3D_APPLICATIONFACTORY_HPP

#include "Application.hpp"

namespace x3d {

  class ApplicationFactory {
  public:
    virtual Application* create() = 0;
  };

}

#endif
