#ifndef __X3D_APPLICATION_HPP
#define __X3D_APPLICATION_HPP

namespace x3d {
  class Application {
  public:
    virtual ~Application() {}
    virtual void execute() = 0;
  };
}

#endif
