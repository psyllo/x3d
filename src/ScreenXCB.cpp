#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ScreenXCB.hpp"

#include "ScreenInfoRgb.hpp"

#include <X11/X.h> // TODO: do not want to depend on this just for vis type class names

#include <boost/log/trivial.hpp>
#include <cassert>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace x3d {

  ScreenXCB::~ScreenXCB() {

    /*
      Shm clean-up
     */
    xcb_shm_detach(connection, shm_info.shmseg); // Detach
    shmdt(shm_info.shmaddr); // Detach

    xcb_free_pixmap(connection, pixmap_id); // free on X server

    /*
      Cleanup window and connection
     */
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);
  }

  /*
    visual_type contains the visual structure, or a NULL visual
    structure if no screen is found code from. xcb_visualtype_t, which
    corresponds to the Xlib Visual.
    See: https://xcb.freedesktop.org/xlibtoxcbtranslationguide/
  */
  const xcb_visualtype_t* ScreenXCB::getVisualType() {
    assert(screen);

    xcb_visualtype_t    *visual_type = NULL; /* the returned visual type */
    xcb_depth_iterator_t depth_iter;

    depth_iter = xcb_screen_allowed_depths_iterator (screen);
    for (; depth_iter.rem; xcb_depth_next (&depth_iter)) {
      xcb_visualtype_iterator_t visual_iter;

      visual_iter = xcb_depth_visuals_iterator (depth_iter.data);
      for (; visual_iter.rem; xcb_visualtype_next (&visual_iter)) {
        if (screen->root_visual == visual_iter.data->visual_id) {
          visual_type = visual_iter.data;
          break;
        }
      }
    }

    return visual_type;
  }

  /*
    code from: https://xcb.freedesktop.org/xlibtoxcbtranslationguide/
  */
  xcb_screen_t* ScreenXCB::screenOfDisplay(int screen_number) {
    assert(connection);

    xcb_screen_iterator_t iter;

    iter = xcb_setup_roots_iterator (xcb_get_setup(connection));
    for (; iter.rem; --screen_number, xcb_screen_next(&iter))
      if (screen_number == 0)
        return iter.data;

    return NULL;
  }

  void ScreenXCB::blit() {
    xcb_copy_area(connection,
                  pixmap_id,
                  window,
                  graphics_context,
                  0, 0, 0, 0,
                  window_w, window_h);
  }

  /*
    Called from constructor
  */
  bool ScreenXCB::initialize() {
    if(_initialized) return false;

    /* Open the connection to the X server */
    connection = xcb_connect(NULL, NULL);

    assert(connection); // TODO: error handling
    assert(!xcb_connection_has_error(connection));

    /* Get the first screen */
    {
      const xcb_setup_t*      setup  = xcb_get_setup(connection);
      xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator(setup);
      screen = iter.data;
    }

    screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

    win_value_mask = 0; // reset

    // Background
    win_value_mask |= XCB_CW_BACK_PIXEL;
    win_value_list[0] = XCB_NONE; // XCB_NONE is black

    // Which events to have sent from server
    win_value_mask |= XCB_CW_EVENT_MASK;
    win_value_list[1] = default_event_mask;

    /* Create the window */
    window = xcb_generate_id(connection);
    xcb_create_window(connection,                      /* Connection          */
                      XCB_COPY_FROM_PARENT,            /* depth (same as root)*/
                      window,                          /* window Id           */
                      screen->root,                    /* parent window       */
                      window_x, window_y,              /* x, y                */
                      window_w, window_h,              /* width, height       */
                      border_width,                    /* border_width        */
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,   /* class               */
                      screen->root_visual,             /* visual              */
                      win_value_mask, win_value_list); /* masks, value list   */

    // NOTE: xcb_map_window() called in open(). We are just preparing here

    bytespp = screen->root_depth / BITS_PER_BYTE;

    const xcb_visualtype_t* vis = getVisualType();
    // From xcb/xproto.h
    // typedef struct xcb_visualtype_t {
    //     xcb_visualid_t visual_id;
    //     uint8_t        _class;
    //     uint8_t        bits_per_rgb_value;
    //     uint16_t       colormap_entries;
    //     uint32_t       red_mask;
    //     uint32_t       green_mask;
    //     uint32_t       blue_mask;
    //     uint8_t        pad0[4];
    // } xcb_visualtype_t;

    switch(vis->_class) {
    case PseudoColor: BOOST_LOG_TRIVIAL(error) << "unsupported visual PseudoColor"; break;
      break;
    case TrueColor:
      BOOST_LOG_TRIVIAL(info) << "Visual type TrueColor";
      sinfo = new ScreenInfoRgb(vis->red_mask, vis->green_mask, vis->blue_mask,
                                bytespp, vis->bits_per_rgb_value);

      // TODO: The following comment was taken from L3D source. Should I care too?
      // FIXME: byte order!!!!!!!!
      // pbuf->byte_order =

      break;
    case GrayScale:   BOOST_LOG_TRIVIAL(error) << "unsupported visual GrayScale"; break;
    case StaticGray:  BOOST_LOG_TRIVIAL(error) << "unsupported visual StaticGray"; break;
    case DirectColor: BOOST_LOG_TRIVIAL(error) << "unsupported visual DirectColor"; break;
    default:
      BOOST_LOG_TRIVIAL(error) << "unsupported visual " << vis->_class; break;
    }

    if(!sinfo) {
      BOOST_LOG_TRIVIAL(error) << "Unable to gather necessary screen info.";
      return false;
    }

    _initialized = true;
    return _initialized;
  }

    
  /*
    Setup Graphics Context

    See: xcb_gc_t enum for XCB_GC_* (xcb/xproto.h).
  */
  bool ScreenXCB::initGraphicsContext() {
    assert(connection);
    assert(screen);

    graphics_context = xcb_generate_id(connection);
    gc_value_mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    gc_value_list[0] = screen->black_pixel;
    gc_value_list[1] = 0;
    xcb_create_gc(connection, graphics_context, window, gc_value_mask, gc_value_list);

    return true;
  }

  /*
    Setup Shm (shared memory pixmap via shm.h, xcb/shm.h, xcb/xcb_image.h)
    See: http://stackoverflow.com/questions/27745131/how-to-use-shm-pixmap-with-xcb
    See: https://xcb.freedesktop.org/manual/group__XCB__Shm__API.html
    See: https://xcb.freedesktop.org/manual/shm_8h_source.html
  */
  bool ScreenXCB::initShm() {
    shm_version_reply = xcb_shm_query_version_reply
      (connection, xcb_shm_query_version(connection), NULL);

    if(!shm_version_reply || !shm_version_reply->shared_pixmaps){
      BOOST_LOG_TRIVIAL(error) << "Shm error";
      return false;
    }

    shm_info.shmid   = shmget(IPC_PRIVATE,
                              window_w * window_h * bytespp,
                              IPC_CREAT | 0777);
    shm_info.shmaddr = (uint8_t*)shmat(shm_info.shmid, NULL, 0); // NULL = auto allocate

    shm_info.shmseg = xcb_generate_id(connection);
    xcb_shm_attach(connection, shm_info.shmseg, shm_info.shmid, 0);
    shmctl(shm_info.shmid, IPC_RMID, 0);

    sinfo->p_screenbuf = shm_info.shmaddr;

    pixmap_id = xcb_generate_id(connection);
    xcb_shm_create_pixmap(connection,
                          pixmap_id,
                          window,
                          window_w, window_h,
                          screen->root_depth,
                          shm_info.shmseg,
                          0);
    return true;
  }

  /*
    Can only be called after initialization
   */
  bool ScreenXCB::open() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    assert(connection);
    assert(screen);
    assert(window);
    assert(initGraphicsContext());
    assert(initShm());

    // Mapping the window will do the opening
    xcb_map_window(connection, window);
    xcb_flush(connection);

    // TODO: DELME: Some debug code
    // int i = 0;
    // while(1){
    //   usleep(10000);

    //   data[i] = 0xFF;
    //   i++;

    //   xcb_copy_area(
    //                 connection,
    //                 pixmap_id,
    //                 window,
    //                 graphics_context,
    //                 0, 0, 0, 0,
    //                 window_w, window_h
    //                 );

    //   xcb_flush(connection);
    // }

    _was_opened = true;
    return true;
  }

  bool ScreenXCB::close() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    xcb_disconnect(connection);
    return true;
  }

}
