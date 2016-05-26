#ifndef __X3D_APPLICATIONXCB_01_HPP
#define __X3D_APPLICATIONXCB_01_HPP

#include "ApplicationXCB.hpp"

namespace x3d {

  class ApplicationXCB_01 : public ApplicationXCB {
  protected:
    virtual void eventLoop();
  public:
    ApplicationXCB_01() : ApplicationXCB() {}
    virtual ~ApplicationXCB_01() { /* TODO */ }
  };
}

#endif
