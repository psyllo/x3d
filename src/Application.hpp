#ifndef __X3D_APPLICATION_HPP
#define __X3D_APPLICATION_HPP

/*
  An Application is the highest level off abstraction in X3D and
  presumably brings together a Pipeline and Dispatcher etc. In other
  words if we did not have the Application class we would likely write
  such logic in main().
 */

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
