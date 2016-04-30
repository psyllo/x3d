#ifndef __X3D_SCREEN_FACTORY_H
#define __X3D_SCREEN_FACTORY_H

#include <Screen.hpp>
#include <ScreenX11.hpp>

namespace x3d {

  class ScreenFactory {
  public:
    ScreenFactory() {}
    virtual ~ScreenFactory() {}
    static Screen* createScreen() {
      return new ScreenX11();
    }
  };

}

#endif
