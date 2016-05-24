#ifndef __X3D_DISPATCHERXCB_HPP
#define __X3D_DISPATCHERXCB_HPP

/*
  Forms the connnection between Pipleline and incoming X events
 */

#include "Dispatcher.hpp"
#include "ScreenXCB.hpp"
#include "Pipeline.hpp"

namespace x3d {

  class DispatcherXCB : public Dispatcher {
    ScreenXCB* _screen;
  public:
    DispatcherXCB() {
    }
    DispatcherXCB(Pipeline* pipeline, ScreenXCB* event_source)
      : Dispatcher(pipeline, event_source), _screen(event_source) // TODO verify this constructor works
    {  }
    void start();
  };

  /*
    Factory
  */
  class DispatcherFactoryXCB : public DispatcherFactory {
  public:
    Dispatcher* create() { return new DispatcherXCB; }
  };

}

#endif
