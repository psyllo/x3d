#ifndef __X3D_DISPATCHERFACTORY_HPP
#define __X3D_DISPATCHERFACTORY_HPP

#include "Dispatcher.hpp"

namespace x3d {
  class DispatcherFactory {
  public:
    virtual Dispatcher* create() = 0;
  };
}

#endif
