#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ScreenX11.hpp"

#include <boost/log/trivial.hpp>
#include <cstdint>
#include <iostream>

namespace x3d {

  void ScreenX11::blit() {
    // TODO: write this function
  }

  bool ScreenX11::init() {
    if(_initialized) return false;

    /* Open the connection to the X server */
    connection = xcb_connect(NULL, NULL);

    /* Get the first screen */
    {
      const xcb_setup_t*      setup  = xcb_get_setup(connection);
      xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator(setup);
      screen = iter.data;
    }

    connection = xcb_connect(NULL, NULL);
    window = xcb_generate_id(connection);
    screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
    _initialized = true;
    return _initialized;
  }

  /*
    See: https://xcb.freedesktop.org/tutorial/basicwindowsanddrawing/
   */
  bool ScreenX11::open() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    /* Create the window */
    window = xcb_generate_id(connection);
    xcb_create_window(connection,                    /* Connection          */
                      XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                      window,                        /* window Id           */
                      screen->root,                  /* parent window       */
                      screen_x, screen_y,            /* x, y                */
                      screen_w, screen_h,            /* width, height       */
                      border_width,                  /* border_width        */
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                      screen->root_visual,           /* visual              */
                      value_mask, value_list);       /* masks, value_list   */

    /* Map the window on the screen and flush */
    xcb_map_window(connection, window);
    xcb_flush(connection);
    return true;
  }


  bool ScreenX11::close() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    xcb_disconnect(connection);
    return true;
  }

}
