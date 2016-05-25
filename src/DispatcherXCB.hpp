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
    DispatcherXCB() : Dispatcher() {}
    DispatcherXCB(Pipeline* pipeline, EventSource* screen_xcb)
      : Dispatcher(pipeline, screen_xcb) , _screen((ScreenXCB*)screen_xcb)
    {} // TODO: Verify pipeline and event_source get initialized
    void start();
  };

  /*
    Factory
  */
  class DispatcherFactoryXCB : public DispatcherFactory {
  public:
    Dispatcher* create(Pipeline* pipeline, EventSource* screen_xcb)
    { return new DispatcherXCB(pipeline, screen_xcb); }
  };

}

#endif
