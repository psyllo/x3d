#ifndef __X3D_DISPATCHERX11_HPP
#define __X3D_DISPATCHERX11_HPP

/*
  Forms the connnection between Pipleline and incoming X events
 */

#include "Dispatcher.hpp"
#include "ScreenX11.hpp"
#include "Pipeline.hpp"

namespace x3d {

  class DispatcherX11 : public Dispatcher {
    ScreenX11* _screen;
  public:
    DispatcherX11() {
    }
    DispatcherX11(Pipeline* pipeline, ScreenX11* event_source)
      : Dispatcher(pipeline, event_source), _screen(event_source) // TODO verify this constructor works
    {  }
    void start();
  };

  /*
    Factory
  */
  class DispatcherFactoryX11 : public DispatcherFactory {
  public:
    Dispatcher* create() { return new DispatcherX11; }
  };

}

#endif
