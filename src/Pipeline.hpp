#ifndef __X3D_PIPELINE_HPP
#define __X3D_PIPELINE_HPP

namespace x3d {
  class Pipeline {
  public:
    virtual void drawEvent() = 0;
    virtual void updateEvent() = 0;
    virtual void keyEvent() = 0;
    virtual void setDone(bool done) = 0;
    virtual bool isDone() = 0;
  };
}

#endif
