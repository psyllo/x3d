#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ApplicationX11.hpp"

#include "DispatcherX11.hpp"
#include "ScreenX11.hpp"
#include "PipelineImpl.hpp"
#include <boost/log/trivial.hpp>
#include <memory>
#include <unistd.h>      /* pause() */

namespace x3d {

  void ApplicationX11::createWindow() {
    screen = new ScreenX11; // TODO: unique_ptr
    if(!screen->init()) {
      BOOST_LOG_TRIVIAL(fatal) << "Screen init failed";
      exit(EXIT_FAILURE);
    }
    screen->open();
  }

  void ApplicationX11::eventLoop() {
    pause(); // TODO - use Dispatcher to connect events to pipeline
    DispatcherX11 dispatcher(new PipelineImpl, screen);
    dispatcher.start();
  }

  void ApplicationX11::execute() {
    createWindow();
    eventLoop();
  }

}
