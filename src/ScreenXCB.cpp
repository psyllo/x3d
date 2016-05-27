#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ScreenXCB.hpp"

#include "ScreenInfoRgb.hpp"

#include <X11/X.h> // TODO: do not want to depend on this just for vis type class names

#include <boost/log/trivial.hpp>
#include <cassert>
#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace x3d {

  void ScreenXCB::cacheWindowGeometry()  {
    assert(connection);
    assert(window);
    window_geom = xcb_get_geometry_reply
      (connection, xcb_get_geometry(connection, window), NULL);
  }

  void ScreenXCB::windowChanged() {
    resetShmPixmap();
  }

  /*
    code from: https://xcb.freedesktop.org/xlibtoxcbtranslationguide/
  */
  // TODO: untested
  xcb_screen_t* ScreenXCB::getScreenOfDisplay(xcb_connection_t* connection, int screen_number) {
    assert(connection);

    xcb_screen_iterator_t iter;

    iter = xcb_setup_roots_iterator (xcb_get_setup(connection));
    for (; iter.rem; --screen_number, xcb_screen_next(&iter))
      if (screen_number == 0)
        return iter.data;

    return NULL;
  }

  xcb_screen_t* ScreenXCB::findFirstScreen(xcb_connection_t* connection) {
    assert(connection);

    const xcb_setup_t*      setup  = xcb_get_setup(connection);
    xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator(setup);

    return iter.data;
  }

  // TODO: Untested
  int ScreenXCB::getConnectionNumber(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_file_descriptor(connection);
  }

  // TODO: Untested
  int ScreenXCB::getScreenCount(xcb_connection_t* connection) {
    assert(connection);
    return xcb_setup_roots_iterator(xcb_get_setup(connection)).rem;
  }

  /*
    TODO: Untested
    result should be freed by caller
  */
  char* ScreenXCB::getServerVendor(xcb_connection_t* connection) {
    assert(connection);

    char* vendor = NULL;
    int length;
    length = xcb_setup_vendor_length(xcb_get_setup(connection));
    vendor = (char*)malloc(length + 1);
    if (vendor)
      memcpy (vendor, xcb_setup_vendor(xcb_get_setup(connection)), length);
    vendor[length] = '\0';
    return vendor;
  }

  // TODO: Untested
  unsigned int ScreenXCB::getProtocolVersion(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->protocol_major_version;
  }

  // TODO: Untested
  unsigned int ScreenXCB::getProtocolRevision(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->protocol_minor_version;
  }

  // TODO: Untested
  unsigned long ScreenXCB::getVendorRelease(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->release_number;
  }

  // TODO: Untested
  unsigned char ScreenXCB::getScanlinePad(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->bitmap_format_scanline_pad;
  }

  // TODO: Untested
  unsigned char ScreenXCB::getBitmapScanlineUnit(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->bitmap_format_scanline_unit;
  }

  // TODO: Untested
  unsigned char ScreenXCB::getBitmapBitOrder(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->bitmap_format_bit_order;
  }

  // TODO: Untested
  unsigned char ScreenXCB::getImageByteOrder(xcb_connection_t* connection) {
    assert(connection);
    return xcb_get_setup(connection)->image_byte_order;
  }

  // TODO: Untested
  void ScreenXCB::updateWindowAttributes() {
    xcb_change_window_attributes(connection, window, win_value_mask, win_value_list);
    xcb_flush(connection);
  }

  short ScreenXCB::getWindowX()  {
    if(window_geom) return window_geom->x;
    else throw std::invalid_argument("window_geom is NULL");
    return 0;
  }

  short ScreenXCB::getWindowY()  {
    if(window_geom) return window_geom->y;
    else throw std::invalid_argument("window_geom is NULL");
    return 0;
  }

  unsigned short ScreenXCB::getWindowWidth()  {
    if(window_geom) return window_geom->width;
    else throw std::invalid_argument("window_geom is NULL");
    return 0;
  }

  unsigned short ScreenXCB::getWindowHeight()  {
    if(window_geom) return window_geom->height;
    else throw std::invalid_argument("window_geom is NULL");
    return 0;
  }

  unsigned short ScreenXCB::getWindowBorderWidth()  {
    if(window_geom) return window_geom->border_width;
    else throw std::invalid_argument("window_geom is NULL");
    return 0;
  }

  void ScreenXCB::freeShmPixmap() {
    if(connection) xcb_shm_detach(connection, shm_info.shmseg); // Detach
    if(shm_info.shmaddr) shmdt(shm_info.shmaddr); // Detach
    if(connection && pixmap_id) xcb_free_pixmap(connection, pixmap_id); // free on X server
    pixmap_id = 0;
    shm_info = {0};
  }

  ScreenXCB::~ScreenXCB() {
    close();
  }

  /*
    visual_type contains the visual structure, or a NULL visual
    structure if no screen is found code from. xcb_visualtype_t, which
    corresponds to the Xlib Visual.
    See: https://xcb.freedesktop.org/xlibtoxcbtranslationguide/
  */
  const xcb_visualtype_t* ScreenXCB::findVisualType(xcb_screen_t* screen) {
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
    TODO: blit() is spawning unknown events from X server. Why? Is the normal behavior?
   */
  void ScreenXCB::blit() {
    xcb_copy_area(connection,
                  pixmap_id,
                  window,
                  graphics_context,
                  0, 0, 0, 0,
                  window_geom->width, window_geom->height);
  }

  /*
    Creates a window from default values. Mapping the window to the
    connection is left to the caller.
   */
  void ScreenXCB::setupWindow
  (unsigned short desired_window_width, unsigned short desired_window_height) {
    assert(connection);
    assert(screen);

    win_value_mask = 0; // reset

    // Background
    win_value_mask |= XCB_CW_BACK_PIXEL;
    win_value_list[0] = XCB_NONE; // XCB_NONE is black

    // Which events to have sent from server
    win_value_mask |= XCB_CW_EVENT_MASK;
    win_value_list[1] = default_event_mask;

    /* Create the window */
    window = xcb_generate_id(connection);
    xcb_create_window(connection,                      /* connection          */
                      XCB_COPY_FROM_PARENT,            /* depth (same as root)*/
                      window,                          /* window Id           */
                      screen->root,                    /* parent window       */
                      default_window_x,                /* x                   */
                      default_window_y,                /* y                   */
                      desired_window_width,            /* width               */
                      desired_window_height,           /* height              */
                      default_window_border_width,     /* border_width        */
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,   /* class               */
                      screen->root_visual,             /* visual              */
                      win_value_mask, win_value_list); /* masks, value list   */
  }

  xcb_connection_t* ScreenXCB::openConnection() {
    // xcb_connect takes optional arguments display_name and return
    // value screen_number
    xcb_connection_t* connection = xcb_connect(NULL, NULL);

    assert(connection); // TODO: error handling
    assert(!xcb_connection_has_error(connection));

    return connection;
  }

  /*
    Called from constructor
  */
  bool ScreenXCB::initialize(unsigned short desired_window_width,
                             unsigned short desired_window_height) {
    if(_initialized) return false;

    connection = openConnection();
    screen = findFirstScreen(connection);

    setupWindow(desired_window_width, desired_window_height);

    xcb_flush(connection);

    // NOTE: xcb_map_window() called in open()

    vis = findVisualType(screen);

    // I have verified that bit order is reversed from rgb, so it is
    // bgr. In addition, for each pixel there are 4 bytes instead of
    // the expected 3 (for TrueColor 24-bit depth with 8-bits per rgb
    // value).
    //
    // So the bytes per pixel are:
    //   [b][g][r][unknown]
    // 
    // So while I would expect to use (screen->root_depth /
    // BITS_PER_BYTE) to calculate bytes-per-pixel, I am just
    // hard-coding 4.
    //
    // TODO: What is the extra byte for?
    bytespp = 4;
    BOOST_LOG_TRIVIAL(info) << "Bytes per pixel: " << (int)bytespp;

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
  bool ScreenXCB::resetGraphicsContext() {
    assert(connection);
    assert(screen);
    assert(window);

    gc_value_mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    gc_value_list[0] = screen->black_pixel;
    gc_value_list[1] = 0;

    graphics_context = xcb_generate_id(connection);
    xcb_create_gc(connection, graphics_context, window, gc_value_mask, gc_value_list);

    return true;
  }

  /*
    Setup/reset Shm (shared memory pixmap via shm.h, xcb/shm.h, xcb/xcb_image.h)
    See: http://stackoverflow.com/questions/27745131/how-to-use-shm-pixmap-with-xcb
    See: https://xcb.freedesktop.org/manual/group__XCB__Shm__API.html
    See: https://xcb.freedesktop.org/manual/shm_8h_source.html
  */
  bool ScreenXCB::resetShmPixmap() {
    if(sinfo->p_screenbuf) freeShmPixmap();

    cacheWindowGeometry();
    assert(window_geom);
    assert(sinfo);

    shm_version_reply = xcb_shm_query_version_reply
      (connection, xcb_shm_query_version(connection), NULL);

    assert(shm_version_reply && shm_version_reply->shared_pixmaps);

    _screen_buffer_size = window_geom->width * window_geom->height * bytespp;

    shm_info.shmid = shmget(IPC_PRIVATE,
                            _screen_buffer_size,
                            IPC_CREAT | 0777);
    shm_info.shmaddr = (uint8_t*)shmat(shm_info.shmid, NULL, 0); // NULL = auto allocate

    shm_info.shmseg = xcb_generate_id(connection);
    xcb_shm_attach(connection, shm_info.shmseg, shm_info.shmid, 0);
    shmctl(shm_info.shmid, IPC_RMID, 0);

    // TODO: Is memset needed? This is not called every frame so it
    // should be ok even if it is redundant.
    // memset(shm_info.shmaddr, 0, _screen_buffer_size); // zero buffer

    sinfo->p_screenbuf = shm_info.shmaddr;

    pixmap_id = xcb_generate_id(connection);
    xcb_shm_create_pixmap(connection,
                          pixmap_id,
                          window,
                          window_geom->width,
                          window_geom->height,
                          screen->root_depth,
                          shm_info.shmseg,
                          0);

    BOOST_LOG_TRIVIAL(info) << "New Shm Pixmap created with byte length of: " << _screen_buffer_size;
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
    assert(resetGraphicsContext());
    assert(resetShmPixmap());

    // Mapping the window will show it
    xcb_map_window(connection, window);

    xcb_flush(connection);

    _was_opened = true;
    return true;
  }

  bool ScreenXCB::close() {
    freeShmPixmap();

    /*
      Cleanup window and connection
    */
    if(connection) {
      if(window) xcb_destroy_window(connection, window);
      xcb_disconnect(connection);
      connection = NULL;
      window = 0;
    }
    return true;
  }

}
