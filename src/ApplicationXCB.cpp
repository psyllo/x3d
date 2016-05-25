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
    follow order found in the enum xcb_cw_t.

    Enum xcb_cw_t copied here for convenience (see: xcb/xproto.h):

    XCB_CW_BACK_PIXMAP       = 1L<<0,
    XCB_CW_BACK_PIXEL        = 1L<<1,
    XCB_CW_BORDER_PIXMAP     = 1L<<2,
    XCB_CW_BORDER_PIXEL      = 1L<<3,
    XCB_CW_BIT_GRAVITY       = 1L<<4,
    XCB_CW_WIN_GRAVITY       = 1L<<5,
    XCB_CW_BACKING_STORE     = 1L<<6,
    XCB_CW_BACKING_PLANES    = 1L<<7,
    XCB_CW_BACKING_PIXEL     = 1L<<8,
    XCB_CW_OVERRIDE_REDIRECT = 1L<<9,
    XCB_CW_SAVE_UNDER        = 1L<<10,
    XCB_CW_EVENT_MASK        = 1L<<11,
    XCB_CW_DONT_PROPAGATE    = 1L<<12,
    XCB_CW_COLORMAP          = 1L<<13,
    XCB_CW_CURSOR            = 1L<<14

   */
  void ApplicationXCB::setupScreenValues(bool updateWindow) {
    assert(screen);

    screen->value_mask = 0; // reset

    // Background
    screen->value_mask |= XCB_CW_BACK_PIXEL;
    screen->value_list[0] = XCB_NONE; // XCB_NONE is black

    // Which events to have sent from server
    screen->value_mask |= XCB_CW_EVENT_MASK;
    screen->value_list[1] = default_event_mask;

    // Update to the changes we made above
    if(updateWindow) screen->updateWindowAttributes();
  }

  void ApplicationXCB::createWindow() {
    if(screen) {
      BOOST_LOG_TRIVIAL(warning) << "Screen already created. Freeing previous";
      free(screen);
    }

    screen = new ScreenXCB; // TODO: unique_ptr?

    if(!screen->isInitialized()) {
      BOOST_LOG_TRIVIAL(fatal) << "Screen init failed";
      exit(EXIT_FAILURE); // TODO: throw exception
    }

    setupScreenValues(false);

    assert(screen->open()); // TODO: Throw exception
  }

  void ApplicationXCB::eventLoop() {
    // TODO: LEFT_OFF
    assert(screen);
    ScreenInfo* screen_info = screen->getInfo(); // TODO: LEFT_OFF: making getInfo() work
    Rasterizer* ras = new Rasterizer(screen_info, screen->getWidth(), screen->getHeight());
    PipelineXCBdemo* pipeline = new PipelineXCBdemo(ras);
    FactoryManager fm;
    Dispatcher* dispatcher = fm.getDispatcherFactory()->create(pipeline, screen);
    dispatcher->start();
  }

  void ApplicationXCB::execute() {
    createWindow();
    eventLoop();
  }

}
