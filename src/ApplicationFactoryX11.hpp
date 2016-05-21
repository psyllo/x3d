#ifndef __X3D_APPLICATIONFACTORYX11_HPP
#define __X3D_APPLICATIONFACTORYX11_HPP

#include "ApplicationFactory.hpp"
#include "ApplicationX11.hpp"

namespace x3d {
  class ApplicationFactoryX11 : public ApplicationFactory {
  public:
    virtual Application* create();
  };
}

#endif
