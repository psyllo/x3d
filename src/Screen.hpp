#ifndef __X3D_SCREEN_HPP
#define __X3D_SCREEN_HPP

#include "EventSource.hpp"
#include "Polygon2D.hpp"
#include "ScreenInfo.hpp"
#include <cstdint>

namespace x3d {

  class Screen : public EventSource {
  public:
    virtual ~Screen() { }
    virtual bool init() = 0;
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual void blit() = 0;
    virtual void refreshPalette() { };
    virtual ScreenInfo* getInfo() = 0;
    virtual Polygon2D* getViewWin() = 0;
    virtual unsigned short getWidth() = 0;
    virtual unsigned short getHeight() = 0;
  };

  class ScreenFactory {
  public:
    virtual Screen* create(unsigned short width, unsigned short height) = 0;
  };
}

#endif
