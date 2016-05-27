#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ApplicationXCB.hpp"

#include "DispatcherXCB.hpp"
#include "FactoryManager.hpp"
#include "ScreenXCB.hpp"
#include <boost/log/trivial.hpp>
#include <cassert>
#include <memory>

#include "PipelineXCBdemo.hpp"

namespace x3d {

  /*
    Set default ScreenXCB values. Order of values in values_list must
    follow order found in the enum xcb_cw_t (see: xcb/xproto.h).
   */
  void ApplicationXCB::setupScreenValues(bool updateWindow) {
    assert(screen);
    // TODO
    // screen->win_value_mask = 0; // reset

    // // Background
    // screen->win_value_mask |= XCB_CW_BACK_PIXEL;
    // screen->win_value_list[0] = XCB_NONE; // XCB_NONE is black

    // // Which events to have sent from server
    // screen->win_value_mask |= XCB_CW_EVENT_MASK;
    // screen->win_value_list[1] = default_event_mask;

    // // Update to the changes we made above
    // if(updateWindow) screen->updateWindowAttributes();
  }

  void ApplicationXCB::createWindow() {
    if(screen) {
      BOOST_LOG_TRIVIAL(warning) << "Screen already created. Freeing previous";
      free(screen);
    }

    screen = new ScreenXCB; // TODO: unique_ptr?

    if(!screen->isInitialized()) {
      BOOST_LOG_TRIVIAL(fatal) << "Screen init failed";
      exit(EXIT_FAILURE); // TODO: print error
    }

    setupScreenValues(false);

    assert(screen->open()); // TODO: print error
  }

  void ApplicationXCB::eventLoop() {
    assert(screen);
    ScreenInfo* screen_info = screen->getInfo();
    Rasterizer* ras = new Rasterizer(screen_info, screen->getWindowWidth(),
                                     screen->getWindowHeight());
    PipelineXCBdemo* pipeline = new PipelineXCBdemo(ras, screen);
    FactoryManager fm;
    Dispatcher* dispatcher = fm.getDispatcherFactory()->create(pipeline, screen);
    dispatcher->start();
  }

  void ApplicationXCB::execute() {
    createWindow();
    eventLoop();
  }

}
