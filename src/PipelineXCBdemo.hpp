#ifndef __PIPELINEDEMO_HPP
#define __PIPELINEDEMO_HPP

#include "Pipeline.hpp"
#include "Rasterizer.hpp"

using namespace x3d;

class PipelineXCBdemo : public Pipeline {
  bool _done;
protected:
  Rasterizer* ras;
public:
  PipelineXCBdemo(Rasterizer *r) : _done(false), ras(r) {}
  virtual void drawEvent();
  virtual void updateEvent();
  virtual void keyEvent();
  virtual void setDone(bool done) { _done = done; }
  virtual bool isDone() { return _done; }
};


#endif
