#include "DispatcherX11.hpp"

#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <cstdlib>
#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <inttypes.h>

namespace x3d {

  /*
    TODO: C++-ize this
    print names of modifiers present in mask
    code from: https://xcb.freedesktop.org/tutorial/events/
  */
  void
  print_modifiers (uint32_t mask)
  {
    const char *MODIFIERS[] = {
      "Shift", "Lock", "Ctrl", "Alt",
      "Mod2", "Mod3", "Mod4", "Mod5",
      "Button1", "Button2", "Button3", "Button4", "Button5"
    };

    printf ("Modifier mask: ");
    for (const char **modifier = MODIFIERS ; mask; mask >>= 1, ++modifier) {
      if (mask & 1) {
        printf (*modifier);
      }
    }
    printf ("\n");
  }

  void DispatcherX11::start() {
    xcb_connection_t* connection = _screen->getConnection();
    xcb_window_t* window = _screen->getWindow();
    xcb_generic_event_t* event;
    // xcb_wait_for_event (note xcb_poll_for_event available for
    // non-blocking) blocks until an event is queued in the X server,
    // then dequeues it from the queue, then returns it as a newly
    // allocated structure (which is your responsibility to free). May
    // return NULL in event of an error.
    while(!pipeline->isDone() && (event = xcb_wait_for_event(connection))) {
      std::cerr << event->response_type << " "
                <<  (event->response_type == XCB_EXPOSE)
                << std::endl;
      switch(event->response_type & ~0x80) {
      case XCB_EXPOSE:
        pipeline->updateEvent();
        pipeline->drawEvent();

        /* flush the request */
        xcb_flush(connection);

        break;
      case XCB_KEY_RELEASE: {
        xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
        print_modifiers(kr->state);

        printf("Key released in window %"PRIu32"\n",
               kr->event);
        break;
      }
      default:
        /* Unknown event type, ignore it */
        printf("Unknown event: %"PRIu8"\n",
               event->response_type);
        break;
      }
      free(event);
    }
  }

}
