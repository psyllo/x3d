#ifndef __APPLICATIONX11_HPP
#define __APPLICATIONX11_HPP

#include "Application.hpp"
#include "ScreenX11.hpp"

namespace x3d {

  class ApplicationX11 : public Application {

  protected:
    const static int default_screen_w = 640;
    const static int default_screen_h = 480;
    //Visual *vis;            // X11: Visual (visual info about X server) TODO: xcb equiv
    ScreenX11* screen;           // X11: Display (connection to X server) TODO: xcb equiv
    //xcb_window_t window;               // X11: Window TODO: xcb equiv

    virtual void createWindow();
    virtual void eventLoop();

  public:
    virtual void execute();
  };
}

#endif
