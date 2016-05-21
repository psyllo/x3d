#ifndef __X3D_SCREENX11_HPP
#define __X3D_SCREENX11_HPP

#include <Screen.hpp>

#include <memory>
#include <xcb/xcb.h>

namespace x3d {

  class ScreenX11 : public Screen {

  private:
    bool _initialized;

  protected:
    // TODO: use unique_ptr/shared_ptr?
    xcb_connection_t* connection;
    xcb_window_t window;
    xcb_screen_t* screen;
    int16_t screen_x, screen_y;
    uint16_t screen_w, screen_h;
    uint16_t border_width;

  public:
    ScreenX11()
      : _initialized(false), connection(NULL), screen(NULL), value_mask(0),
        screen_x(0), screen_y(0), screen_w(0), screen_h(0), border_width(0)
    { }
    virtual ~ScreenX11() {}
    virtual bool init();
    virtual bool open();
    virtual bool close();
    xcb_connection_t* getConnection() { return connection; }
    xcb_window_t* getWindow() { return &window; }
    xcb_screen_t* getXCBscreen() { return screen; };
    int16_t getX() { return screen_x; }
    void setX(int16_t X) { screen_x = X; }
    int16_t getY() { return screen_y; }
    void setY(int16_t Y) { screen_y = Y; }
    uint16_t getWidth() { return screen_w; }
    void setWidth(uint16_t W) { screen_w = W; }
    uint16_t getHeight() { return screen_h; }
    void setHeight(uint16_t H) { screen_h = H; }
    uint16_t getBorderWidth() { return border_width; }
    void setBorderWidth(uint16_t W) { border_width = W; }

    // uint32_t getValueMask() { return mask; }
    // void setValueMask(uint32_t valuemask) { mask = valuemask; }
    // uint32_t* getValueList() { return value_list; }
    // uint32_t getValueListFor(uint index) { return value_list[index]; }
    // void setValueListFor(uint index, uint32_t value) {
    //   value_list[index] = value;
    // }

    uint32_t value_mask;
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
    static const uint32_t VALUE_LIST_SIZE = 20;
    uint32_t value_list[VALUE_LIST_SIZE] = {0}; // TODO: all zeroed per C++ spec AFAIK
    // TODO: consider using uint32_t[hard_coded_number]
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

    void updateWindowAttributes() {
      // TODO: write unit test
      xcb_change_window_attributes(connection, window, value_mask, value_list);
    }

  };

}

#endif
