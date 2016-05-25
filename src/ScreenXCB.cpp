#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ScreenXCB.hpp"

#include "ScreenInfoRgb.hpp"

#include <X11/X.h> // TODO: do not want to depend on this just for vis type class names

#include <boost/log/trivial.hpp>
#include <cassert>
#include <iostream>


namespace x3d {

  constexpr unsigned char BITS_PER_BYTE = 4;

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

  void ScreenXCB::createBuffer() {
    assert(sinfo);
    assert(screen_w > 0);
    assert(screen_h > 0);
    assert(bytespp > 0);

    buffer = new unsigned char [screen_w * screen_h * bytespp];
    sinfo->p_screenbuf = buffer;
  }

  void ScreenXCB::blit() {
    // TODO: write this function
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
    // DELME: window = xcb_generate_id(connection);
    window = screen->root;

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

    createBuffer();

    // TODO: Get GC?

    _initialized = true;
    return _initialized;
  }

  /*
    See: https://xcb.freedesktop.org/tutorial/basicwindowsanddrawing/
   */
  bool ScreenXCB::open() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    assert(screen);

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


  bool ScreenXCB::close() {
    if(!_initialized) {
      BOOST_LOG_TRIVIAL(error) << "uninitialized";
      return false;
    }
    xcb_disconnect(connection);
    return true;
  }

}
