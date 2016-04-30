#ifndef __X3D_SCREEN_H
#define __X3D_SCREEN_H


#include <cstdlib>

namespace x3d {
  
  class Screen {
  public:
    Screen() {}
    virtual ~Screen() {}
    virtual bool init() {return false;}
    virtual bool open() {return false;}
    virtual bool close() {return false;}
  };
}

#endif
