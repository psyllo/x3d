#include <X3dScreenX11.h>
#include <iostream>
#include <boost/log/trivial.hpp>

X3dScreenX11::X3dScreenX11() : X3dScreen() {
  
}

X3dScreenX11::~X3dScreenX11() {
  
}

bool X3dScreenX11::init() {
  if(initialized) return true;
  connection = xcb_connect(NULL, NULL);
  window = xcb_generate_id(connection);
  screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  initialized = true;
  return true;
}

bool X3dScreenX11::open() {
  if(!initialized) {
    // BOOST_LOG_TRIVIAL(error) << "uninitialized";
    return false;
  }
  /* Create the window */
  window = xcb_generate_id(connection);
  xcb_create_window(connection,                    /* Connection          */
                    XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                    window,                        /* window Id           */
                    screen->root,                  /* parent window       */
                    0, 0,                          /* x, y                */
                    150, 150,                      /* width, height       */
                    10,                            /* border_width        */
                    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                    screen->root_visual,           /* visual              */
                    0, NULL );                     /* masks, not used yet */

  /* Map the window on the screen and flush*/
  xcb_map_window(connection, window);
  xcb_flush(connection);
  return true;
}


bool X3dScreenX11::close() {
  if(!initialized) {
    // BOOST_LOG_TRIVIAL(error) << "uninitialized";
    return false;
  }
  xcb_disconnect(connection);
  return true;
}

