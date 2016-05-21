#ifndef __X3D_APPLICATIONX11_HPP
#define __X3D_APPLICATIONX11_HPP

#include "Application.hpp"
#include "ScreenX11.hpp"

namespace x3d {

  class ApplicationX11 : public Application {
  protected:
    ScreenX11* screen;
    void setupScreenValues(bool updateWindow);
    virtual void createWindow();
    virtual void eventLoop();

  public:
    virtual void execute();
    const static int default_screen_w = 640;
    const static int default_screen_h = 480;
    const static uint16_t default_event_mask =
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;
  };
}

#endif
