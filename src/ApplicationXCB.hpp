#ifndef __X3D_APPLICATIONXCB_HPP
#define __X3D_APPLICATIONXCB_HPP

#include "Application.hpp"
#include "ScreenXCB.hpp"
#include <cstdint>

namespace x3d {

  class ApplicationXCB : public Application {
  protected:
    ScreenXCB* screen;
    virtual void setupScreenValues(bool updateWindow);
    virtual void createWindow();
    virtual void eventLoop();

  public:
    ApplicationXCB() : screen(NULL) {}
    virtual ~ApplicationXCB() { /* TODO */ }
    virtual void execute();
    const static uint16_t default_event_mask =
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;
  };

  /*
    Factory
   */
  class ApplicationFactoryXCB : public ApplicationFactory {
  public:
    virtual Application* create() { return new ApplicationXCB; }
  };
}

#endif
