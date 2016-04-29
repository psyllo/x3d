#define BOOST_LOG_DYN_LINK 1 // TODO

#include "../config.h"
#include <unistd.h>      /* pause() */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <X11/Xlib.h>
#include <xcb/xcb.h>
#include <X3dScreenFactory.h>
#include <boost/log/trivial.hpp>

using std::cout;
using std::endl;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// Main loop flag
bool quit = false;
X3dScreen* x3d_screen;

/*
  https://xcb.freedesktop.org/tutorial/basicwindowsanddrawing/
 */
bool init() {
  bool result = false;

  x3d_screen = X3dScreenFactory::createScreen();
  if(!x3d_screen->init()) {
    BOOST_LOG_TRIVIAL(fatal) << "X3dScreen init failed";
    exit(EXIT_FAILURE);
  }else{
    result = true;
  }

  return result;
}

int main(int argc, char* args[]) {

  // Start up SDL and create window
  if(!init()) {
    BOOST_LOG_TRIVIAL(fatal) << "Failed to initialize!";
    exit(EXIT_FAILURE);
  } else {

    x3d_screen->open();
    pause();    /* hold client until Ctrl-C */
    x3d_screen->close();

    // while(!quit) {
    //   cout << "Ok" << endl;
    //   // Handle events on queue
    // }
  }

  return 0;
}
