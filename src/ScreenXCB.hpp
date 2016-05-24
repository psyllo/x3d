#ifndef __X3D_SCREENXCB_HPP
#define __X3D_SCREENXCB_HPP

/*
  XCB uses <cstdint> types such as uint16_t, but our X3D uses standard
  C++ types. So for example instead of uint16_t we use unsigned short.
  See: http://en.cppreference.com/w/cpp/language/types
 */

#include "Screen.hpp"

#include <memory>
#include <xcb/xcb.h>

namespace x3d {

  class ScreenXCB : public Screen {

  private:
    bool _initialized;

  protected:
    // TODO: use unique_ptr/shared_ptr?
    xcb_connection_t* connection;
    xcb_window_t window;
    xcb_screen_t* screen;
    short screen_x, screen_y;
    unsigned short screen_w, screen_h;
    unsigned short border_width;
    ScreenInfo* info;
    Polygon2D* view_win;

  public:
    ScreenXCB() : ScreenXCB(default_screen_w, default_screen_h) { }
    ScreenXCB(unsigned short screen_width, unsigned short screen_height)
      : _initialized(false),
        border_width(0),
        connection(NULL),
        info(NULL),
        screen(NULL),
        screen_h(screen_height),
        screen_w(screen_width),
        screen_x(0),
        screen_y(0),
        value_mask(0)
    { }
    virtual ~ScreenXCB() { /* TODO */ }
    virtual bool init();
    virtual bool open();
    virtual bool close();
    virtual void blit();
    xcb_connection_t* getXCBConnection() { return connection; } // TODO: breaks good abstraction
    xcb_window_t* getXCBWindow() { return &window; } // TODO: breaks good abstraction
    xcb_screen_t* getXCBscreen() { return screen; }; // TODO: breaks good abstraction
    short getX() { return screen_x; }
    void setX(short X) { screen_x = X; }
    short getY() { return screen_y; }
    void setY(short Y) { screen_y = Y; }
    unsigned short getWidth() { return screen_w; }
    void setWidth(unsigned short W) { screen_w = W; }
    unsigned short getHeight() { return screen_h; }
    void setHeight(unsigned short H) { screen_h = H; }
    unsigned short getBorderWidth() { return border_width; }
    void setBorderWidth(unsigned short W) { border_width = W; }
    ScreenInfo* getInfo() { return info; }
    Polygon2D* getViewWin() { return view_win; }

    // unsigned int getValueMask() { return mask; }
    // void setValueMask(unsigned int valuemask) { mask = valuemask; }
    // unsigned int* getValueList() { return value_list; }
    // unsigned int getValueListFor(uint index) { return value_list[index]; }
    // void setValueListFor(uint index, unsigned int value) {
    //   value_list[index] = value;
    // }

    unsigned int value_mask;
    /* possible mask values (see: typedef enum xcb_cw_t)
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
    static const unsigned int VALUE_LIST_SIZE = 20;
    unsigned int value_list[VALUE_LIST_SIZE] = {0}; // TODO: verify all zeroed (per C++ spec AFAIK)
    // Order of values in value list much follow order in xcb_cw_t enum.
    //
    // Events:
    // For XCB event info see: https://xcb.freedesktop.org/tutorial/events/
    // For values for XCB_CW_EVENT_MASK see xcb_event_mask_t in xcb/xproto.h:
    // typedef enum xcb_event_mask_t {
    //     XCB_EVENT_MASK_NO_EVENT = 0,
    //     XCB_EVENT_MASK_KEY_PRESS = 1,
    //     XCB_EVENT_MASK_KEY_RELEASE = 2,
    //     XCB_EVENT_MASK_BUTTON_PRESS = 4,
    //     XCB_EVENT_MASK_BUTTON_RELEASE = 8,
    //     XCB_EVENT_MASK_ENTER_WINDOW = 16,
    //     XCB_EVENT_MASK_LEAVE_WINDOW = 32,
    //     XCB_EVENT_MASK_POINTER_MOTION = 64,
    //     XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
    //     XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
    //     XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
    //     XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
    //     XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
    //     XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
    //     XCB_EVENT_MASK_BUTTON_MOTION = 8192,
    //     XCB_EVENT_MASK_KEYMAP_STATE = 16384,
    //     XCB_EVENT_MASK_EXPOSURE = 32768,
    //     XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
    //     XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
    //     XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
    //     XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
    //     XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
    //     XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
    //     XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
    //     XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
    //     XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
    // } xcb_event_mask_t;

    static const unsigned short default_screen_w = 640;
    static const unsigned short default_screen_h = 480;

    void updateWindowAttributes() {
      // TODO: write unit test
      xcb_change_window_attributes(connection, window, value_mask, value_list);
    }

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
