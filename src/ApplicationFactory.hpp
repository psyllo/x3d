#ifndef __APPLICATIONFACTORY_HPP
#define __APPLICATIONFACTORY_HPP

#include "Application.hpp"

namespace x3d {

  class ApplicationFactory {
  public:
    virtual Application* create() = 0;
  };

}

#endif
