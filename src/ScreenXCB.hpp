#ifndef __X3D_SCREENXCB_HPP
#define __X3D_SCREENXCB_HPP

/*
  XCB uses <cstdint> types such as uint16_t, but our X3D uses standard
  C++ types. So for example instead of uint16_t we use unsigned short.
  See: http://en.cppreference.com/w/cpp/language/types
 */

#include "Screen.hpp"

#include <memory>
#include <cassert>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xcb/shm.h>

namespace x3d {

  class ScreenXCB : public Screen {

  private:
    bool _initialized;
    bool _was_opened;
    unsigned int _screen_buffer_size;

    bool initialize(unsigned short desired_width, unsigned short desired_height);
    void freeShmPixmap();

  protected:
    // TODO: use unique_ptr/shared_ptr?
    xcb_connection_t* connection;
    xcb_window_t window;
    xcb_screen_t* screen;
    xcb_get_geometry_reply_t* window_geom;
    ScreenInfo* sinfo; // contains offscreen shared memory buffer
    Polygon2D* view_win;
    unsigned char bytespp;
    const xcb_visualtype_t* vis;

    xcb_connection_t* openConnection();
    bool resetGraphicsContext();
    bool resetShmPixmap();
    void cacheWindowGeometry(); // TODO: mark cache dirtly on XCB_EXPOSE event
    void setupWindow(unsigned short desired_window_width,
                     unsigned short desired_window_height);

  public:
    ScreenXCB() : ScreenXCB(default_window_w, default_window_h)
    { }
    ScreenXCB(unsigned short desired_window_width, unsigned short desired_window_height)
      : _initialized(false),
        _was_opened(false),
        window_geom(nullptr),
        bytespp(0),
        connection(nullptr),
        gc_value_mask(0),
        graphics_context(0),
        pixmap_id(0),
        sinfo(nullptr),
        screen(nullptr),
        shm_version_reply(nullptr),
        vis(nullptr),
        win_value_mask(0)
    { initialize(desired_window_width, desired_window_height); }
    virtual ~ScreenXCB();
    virtual bool open();
    virtual bool close();
    virtual void blit();
    bool isInitialized() {return _initialized;}
    bool wasOpened() {return _was_opened;}
    static xcb_screen_t* getScreenOfDisplay(xcb_connection_t* connection, int screen_number);
    static xcb_screen_t* findFirstScreen(xcb_connection_t* connection);
    static int getConnectionNumber(xcb_connection_t* connection);
    static int getScreenCount(xcb_connection_t* connection);
    static char* getServerVendor(xcb_connection_t* connection);
    static unsigned int getProtocolVersion(xcb_connection_t* connection);
    static unsigned int getProtocolRevision(xcb_connection_t* connection);
    static unsigned long getVendorRelease(xcb_connection_t* connection);
    static unsigned char getScanlinePad(xcb_connection_t* connection);
    static unsigned char getBitmapScanlineUnit(xcb_connection_t* connection);
    static unsigned char getBitmapBitOrder(xcb_connection_t* connection);
    static unsigned char getImageByteOrder(xcb_connection_t* connection);
    xcb_connection_t* getXCBConnection() { return connection; } // TODO: breaks good abstraction
    xcb_window_t* getXCBWindow() { return &window; } // TODO: breaks good abstraction
    xcb_screen_t* getXCBscreen() { return screen; }; // TODO: breaks good abstraction
    short getWindowX();
    short getWindowY();
    unsigned short getWidth() { assert(screen); return screen->width_in_pixels; }
    unsigned short getHeight() { assert(screen); return screen->height_in_pixels; }
    unsigned short getWindowWidth();
    unsigned short getWindowHeight();
    unsigned short getWindowBorderWidth();
    ScreenInfo* getInfo() { return sinfo; }
    Polygon2D* getViewWin() { return view_win; }
    unsigned char getDepth() {assert(screen); return screen->root_depth;}
    xcb_visualid_t getVisualID() {assert(screen); return screen->root_visual;}
    static const xcb_visualtype_t* findVisualType(xcb_screen_t* screen);
    void updateWindowAttributes();
    void windowChanged();
    unsigned int getScreenBufferLength() { return _screen_buffer_size; }

    /*
      Window value mask and value list

      See: xcb/xproto.h
      See: https://xcb.freedesktop.org/manual/group__XCB____API.html
      See: https://xcb.freedesktop.org/tutorial/events/

      IMPORTANT: Order of values in value list much follow order in
      xcb_cw_t enum.

      Event mask values in xcb_event_mask_t enum.
    */
    unsigned int win_value_mask; // Mask values in xcb_cw_t enum

    static const unsigned int WIN_VALUE_LIST_SIZE = 32;
    unsigned int win_value_list[WIN_VALUE_LIST_SIZE] = {0};
    // TODO: is the the best place to initialize win_value_list?

    static const unsigned short default_window_x = 0;
    static const unsigned short default_window_y = 0;
    static const unsigned short default_window_w = 100;// put 320;
    static const unsigned short default_window_h = 1;// put 240
    static const unsigned short default_window_border_width = 0;

    const static uint16_t default_event_mask =
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;

    /*
      Graphics context
      See: xcb_gc_t enum in xcb/xproto.h
     */
    xcb_gcontext_t graphics_context;
    unsigned int gc_value_mask;
    static const unsigned int GC_VALUE_LIST_SIZE = 32; // more than enough
    unsigned int gc_value_list[GC_VALUE_LIST_SIZE] = {0};
    // TODO: is the the best place to initialize gc_value_list?

    /*
      Pixmap will be in shared memory with X server
     */
    xcb_pixmap_t pixmap_id;

    /*
      Shm (shared memory pixmap)
    */
    xcb_shm_query_version_reply_t*  shm_version_reply;
    xcb_shm_segment_info_t          shm_info = {0};

  };

  /*
    Factory
   */
  class ScreenFactoryXCB : public ScreenFactory {
  public:
    virtual Screen* create(unsigned short width, unsigned short height)
    { return new ScreenXCB(width, height); }
  };

}

#endif
