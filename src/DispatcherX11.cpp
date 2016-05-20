#include "DispatcherX11.hpp"

#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <cstdlib>

namespace x3d {

  void DispatcherX11::start() {
    xcb_connection_t* connection = _screen->getConnection();
    xcb_window_t* window = _screen->getWindow();
    xcb_generic_event_t* event;
    while (!pipeline->isDone() && (event = xcb_wait_for_event(connection))) {
      switch (event->response_type & ~0x80) {
      case XCB_EXPOSE:
        /* We draw the points */
        // xcb_poly_point (connection, XCB_COORD_MODE_ORIGIN, window, foreground, 4, points);

        /* We draw the polygonal line */
        // xcb_poly_line (connection, XCB_COORD_MODE_PREVIOUS, window, foreground, 4, polyline);

        /* We draw the segments */
        // xcb_poly_segment (connection, window, foreground, 2, segments);

        /* draw the rectangles */
        // xcb_poly_rectangle (connection, window, foreground, 2, rectangles);

        /* draw the arcs */
        // xcb_poly_arc (connection, window, foreground, 2, arcs);

        // pipeline->key_event(ch);  // will be overridden by application
        pipeline->updateEvent();   // will be overridden by application
        pipeline->drawEvent();     // will be overridden by application

        /* flush the request */
        xcb_flush (connection);

        break;
      default: 
        /* Unknown event type, ignore it */
        break;
      }
      free(event);
    }
  }

}
