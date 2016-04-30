#ifndef __X3D_SCREEN_X11_H
#define __X3D_SCREEN_X11_H

#include <Screen.hpp>
#include <xcb/xcb.h>
// #include <memory> TODO - use unique_ptr

namespace x3d {

  class ScreenX11 : public Screen {

  private:
    bool initialized;

  protected:
    // std::unique_ptr<xcb_connection_t> connection;
    xcb_connection_t *connection;
    xcb_window_t window;
    xcb_screen_t *screen;

  public:
    ScreenX11();
    virtual ~ScreenX11();
    virtual bool init();
    virtual bool open();
    virtual bool close();
  };

}

#endif
