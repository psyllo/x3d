#ifndef __X3D_SCREEN_FACTORY_H
#define __X3D_SCREEN_FACTORY_H

#include <X3dScreen.h>
#include <X3dScreenX11.h>

class X3dScreenFactory {
 public:
  X3dScreenFactory() {}
  virtual ~X3dScreenFactory() {}
  static X3dScreen* createScreen() {
    return new X3dScreenX11();
  }
};


#endif
