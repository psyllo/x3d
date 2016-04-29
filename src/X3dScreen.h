#ifndef __X3D_SCREEN_H
#define __X3D_SCREEN_H


#include <cstdlib>

class X3dScreen {
 public:
  X3dScreen();
  virtual ~X3dScreen() {}
  virtual bool init() {return false;}
  virtual bool open() {return false;}
  virtual bool close() {return false;}
};

#endif
