#ifndef __X3D_DISPATCHER_HPP
#define __X3D_DISPATCHER_HPP

#include <Pipeline.hpp>
#include <EventSource.hpp>

namespace x3d {

  class Dispatcher {
  protected:
    Pipeline* pipeline;
    EventSource* event_source;
  public:
    Dispatcher(Pipeline* pipeline, EventSource* event_source)
      : pipeline(pipeline), event_source(event_source) {
    }
    EventSource* getEventSource() {return event_source;}
    Pipeline* getPipeline() {return pipeline;}
    virtual void start() = 0;
  };

}
#endif
