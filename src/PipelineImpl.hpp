#ifndef __X3D_PIPELINEIMPL_HPP
#define __X3D_PIPELINEIMPL_HPP

#include <Pipeline.hpp>

namespace x3d {
  class PipelineImpl : public Pipeline {
    bool _done;
  public:
    PipelineImpl() : _done(false) {
    }
    virtual void drawEvent();
    virtual void updateEvent();
    virtual void keyEvent();
    virtual void setDone(bool done) { _done = done; }
    virtual bool isDone() { return _done; }
  };
}

#endif
