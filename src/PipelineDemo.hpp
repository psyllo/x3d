#ifndef __X3D_PIPELINEDEMO_HPP
#define __X3D_PIPELINEDEMO_HPP

#include "Pipeline.hpp"

namespace x3d {
  class PipelineDemo : public Pipeline {
    bool _done;
  public:
    PipelineDemo() : _done(false) {
    }
    virtual void drawEvent();
    virtual void updateEvent();
    virtual void keyEvent();
    virtual void setDone(bool done) { _done = done; }
    virtual bool isDone() { return _done; }
  };
}

#endif
