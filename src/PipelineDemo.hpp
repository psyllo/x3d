#ifndef __X3D_PIPELINEDEMO_HPP
#define __X3D_PIPELINEDEMO_HPP

#include "Pipeline.hpp"
#include "Rasterizer.hpp"

namespace x3d {
  class PipelineDemo : public Pipeline {
    bool _done;
  protected:
    Rasterizer* ras;
  public:
    PipelineDemo(Rasterizer *r) : _done(false), ras(r) {}
    virtual void drawEvent();
    virtual void updateEvent();
    virtual void keyEvent();
    virtual void setDone(bool done) { _done = done; }
    virtual bool isDone() { return _done; }
  };
}

#endif
