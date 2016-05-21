#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ApplicationX11.hpp"

#include "DispatcherX11.hpp"
#include "ScreenX11.hpp"
#include "PipelineImpl.hpp"
#include <boost/log/trivial.hpp>
#include <memory>
#include <cassert>

namespace x3d {

  void ApplicationX11::createWindow() {
    screen = new ScreenX11; // TODO: unique_ptr

    if(!screen->init()) {
      BOOST_LOG_TRIVIAL(fatal) << "Screen init failed";
      exit(EXIT_FAILURE); // TODO: throw exception
    }

    screen->mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    screen->value_list[0] = XCB_NONE;
    // XCB_NONE for black or screen->getXCBscreen()->white_pixel;

    screen->value_list[1] =
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;

    screen->setWidth(default_screen_w);
    screen->setHeight(default_screen_h);

    assert(screen->open()); // TODO: Throw exception
  }

  void ApplicationX11::eventLoop() {
    DispatcherX11 dispatcher(new PipelineImpl, screen);
    dispatcher.start();
  }

  void ApplicationX11::execute() {
    createWindow();
    eventLoop();
  }

}
