#ifndef __X3D_SCREEN_X11_H
#define __X3D_SCREEN_X11_H

#include <X3dScreen.h>
#include <xcb/xcb.h>
// #include <memory> TODO - use unique_ptr

class X3dScreenX11 : public X3dScreen {

 private:
  bool initialized;

 protected:
  // std::unique_ptr<xcb_connection_t> connection;
  xcb_connection_t *connection;
  xcb_window_t window;
  xcb_screen_t *screen;

 public:
  X3dScreenX11();
  virtual ~X3dScreenX11();
  virtual bool init();
  virtual bool open();
  virtual bool close();
};

#endif
