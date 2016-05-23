#ifndef __X3D_APPLICATIONX11_HPP
#define __X3D_APPLICATIONX11_HPP

#include "Application.hpp"
#include "ScreenX11.hpp"

namespace x3d {

  class ApplicationX11 : public Application {
  protected:
    ScreenX11* screen;
    void setupScreenValues(bool updateWindow);
    void createWindow();
    void eventLoop();

  public:
    ApplicationX11() : screen(NULL) {}
    virtual ~ApplicationX11() { /* TODO */ }
    virtual void execute();
    const static int default_screen_w = 640;
    const static int default_screen_h = 480;
    const static uint16_t default_event_mask =
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;
  };

  /*
    Factory
   */
  class ApplicationFactoryX11 : public ApplicationFactory {
  public:
    virtual Application* create() { return new ApplicationX11; }
  };
}

#endif
