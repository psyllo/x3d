#ifndef __X3D_DISPATCHER_HPP
#define __X3D_DISPATCHER_HPP

#include "Pipeline.hpp"
#include "EventSource.hpp"

namespace x3d {

  class Dispatcher {
  protected:
    Pipeline* pipeline;
    EventSource* event_source;
  public:
    Dispatcher() : pipeline(nullptr), event_source(nullptr) {}
    Dispatcher(Pipeline* p, EventSource* evsrc) : pipeline(p), event_source(evsrc) {}
    virtual ~Dispatcher() {}
    EventSource* getEventSource() {return event_source;}
    Pipeline* getPipeline() {return pipeline;}
    virtual void start() = 0;
  };

  class DispatcherFactory {
  public:
    virtual Dispatcher* create(Pipeline* pipeline, EventSource* evsrc) = 0;
  };

}
#endif
