#include "DispatcherXCB.hpp"

#include <xcb/xcb.h>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>

namespace x3d {

  /*
    TODO: C++-ize this (or just delete it)
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

  void DispatcherXCB::start() {
    assert(pipeline);
    assert(_screen);

    xcb_connection_t* connection = _screen->getXCBConnection();
    xcb_window_t* window = _screen->getXCBWindow();
    xcb_generic_event_t* event;
    // xcb_wait_for_event (note xcb_poll_for_event available for
    // non-blocking) blocks until an event is queued in the X server,
    // then dequeues it from the queue, then returns it as a newly
    // allocated structure (which is your responsibility to free). May
    // return NULL in event of an error.
    while(!pipeline->isDone() && (event = xcb_wait_for_event(connection))) {

      switch(event->response_type & ~0x80) {

      case XCB_EXPOSE: {

        xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

        printf ("Window %"PRIu32" exposed. Region to be redrawn at location (%"PRIu16",%"PRIu16"), with dimension (%"PRIu16",%"PRIu16")\n",
                expose->window, expose->x, expose->y, expose->width, expose->height );
        break;
      }
      case XCB_BUTTON_PRESS: {
        xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;
        print_modifiers (bp->state);

        switch (bp->detail) {
        case 4:
          printf ("Wheel Button up in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                  bp->event, bp->event_x, bp->event_y );
          break;
        case 5:
          printf ("Wheel Button down in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                  bp->event, bp->event_x, bp->event_y );
          break;
        default:
          printf ("Button %"PRIu8" pressed in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                  bp->detail, bp->event, bp->event_x, bp->event_y );
          break;
        }
        break;
      }
      case XCB_BUTTON_RELEASE: {
        xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
        print_modifiers(br->state);

        printf ("Button %"PRIu8" released in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                br->detail, br->event, br->event_x, br->event_y );
        break;
      }
      case XCB_MOTION_NOTIFY: {
        xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

        printf ("Mouse moved in window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                motion->event, motion->event_x, motion->event_y );
        break;
      }
      case XCB_ENTER_NOTIFY: {
        xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

        printf ("Mouse entered window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                enter->event, enter->event_x, enter->event_y );
        break;
      }
      case XCB_LEAVE_NOTIFY: {
        xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;

        printf ("Mouse left window %"PRIu32", at coordinates (%"PRIi16",%"PRIi16")\n",
                leave->event, leave->event_x, leave->event_y );
        break;
      }
      case XCB_KEY_PRESS: {
        xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
        print_modifiers(kp->state);

        printf ("Key pressed in window %"PRIu32"\n",
                kp->event);
        break;
      }
      case XCB_KEY_RELEASE: {
        xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
        print_modifiers(kr->state);

        printf ("Key released in window %"PRIu32"\n",
                kr->event);
        break;
      }
      default:
        /* Unknown event type, ignore it */
        printf ("Unknown event: %"PRIu8" - window size %ix%i\n",
                event->response_type, _screen->getWindowWidth(), _screen->getWindowHeight());
        break;
      }

      // TODO: LEFT_OFF
      pipeline->updateEvent();
      pipeline->drawEvent();

      /* flush the request */
      xcb_flush(connection);
      // NOTE: int xcb_aux_sync(xcb_connection_t *c) is the blocking version

      free(event);
    }
  }

}
