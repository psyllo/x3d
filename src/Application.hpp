#ifndef __X3D_APPLICATION_HPP
#define __X3D_APPLICATION_HPP

namespace x3d {

  class Application {
  public:
    virtual void execute() = 0;
  };

  class ApplicationFactory {
  public:
    virtual Application* create() = 0;
  };
}

#endif
