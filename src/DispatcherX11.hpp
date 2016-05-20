#ifndef __DISPATCHERX11_HPP
#define __DISPATCHERX11_HPP

#include "Dispatcher.hpp"
#include "ScreenX11.hpp"
#include "Pipeline.hpp"

namespace x3d {

  class DispatcherX11 : public Dispatcher {
    ScreenX11* _screen;
  public:
    DispatcherX11(Pipeline* pipeline, ScreenX11* event_source)
      : Dispatcher(pipeline, event_source), _screen(event_source) // TODO verify this constructor works
    {  }
    void start();
  };

}

#endif
