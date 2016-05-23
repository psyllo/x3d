#ifndef __SCREENINFO_HPP
#define __SCREENINFO_HPP

// See: pg. 111 Linux 3D Graphics Programming
// See: https://xcb.freedesktop.org/colorsandpixmaps/

namespace x3d {

  // a rasterizer talks only to the screen_info, to find out what it needs
  // to know about the display in order to do rasterization.
  //
  // in general, anything (not just rasterization) which needs to query the
  // screen in any way must be able to get its information solely through
  // a screen_info object; furthermore, it is best if such queries always
  // go through the abstract interface - meaning that the abstract interface
  // for l3d_screen_info contains some entries which are not meaningful for
  // all concrete type of l3d_screen_info.
  //
  // this is a fat interface.
  //
  // we could create a complicated inheritance graph of screen_info classes -
  // those indexed or not indexed, those with or without buffer pointers,
  // those with or without color setting routines - one subclass for every
  // possible combination of screen_info features, but this is a bit
  // too much IMHO - such a hierarchy does not bring any useable benefit,
  // and there is no criteria I know of for deciding what groupings of
  // features are logically useful (e.g. here I need an indexed color-settable
  // screeninfo, there I need an rgb color-settable with bufferpointer,
  // and there I need an indexed non-color-settable with bufferpointer).

  constexpr int MAX_LIGHT_LEVELS = 255;
  constexpr int NUM_LIGHT_LEVELS = MAX_LIGHT_LEVELS + 1;

  // max light levels should also be correct for mesa rasterizer, which
  // uses the light levels not as a lookup but as a direct lightmap intensity,
  // RGB of one byte.

  struct ScreenInfo {
    int ext_max_red, ext_max_green, ext_max_blue;
    char bytes_per_pixel;
    virtual unsigned long extToNative(int red, int green, int blue) = 0;
    virtual ~ScreenInfo(void) {};
    // in case of palettes this is a map and possibly a palette alloc too
    // in case of rgb this is just a map to the rgb resolution

    // lookup tables for colors of light and fog
    virtual void computeLightTable(void) = 0;
    virtual void computeFogTable(void) = 0;
    virtual void lightNative(unsigned char *pcolor, int intensity) = 0;
    virtual void fogNative(unsigned char *pcolor, int intensity) = 0;

    virtual void setColor(unsigned long col ) {};
    // currently only needed by mesa screeninfo, where we must call a glColor
    // function to set the color; otherwise with software rasterization we
    // set the colors in the frame buffer directly

    unsigned char *p_screenbuf;
    // only needed by software screeninfo

  };
}
#endif
