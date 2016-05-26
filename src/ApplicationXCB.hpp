#ifndef __X3D_APPLICATIONXCB_HPP
#define __X3D_APPLICATIONXCB_HPP

#include "Application.hpp"
#include "ScreenXCB.hpp"
#include <cstdint>

namespace x3d {

  class ApplicationXCB : public Application {
  protected:
    ScreenXCB* screen;
    virtual void setupScreenValues(bool updateWindow);
    virtual void createWindow();
    virtual void eventLoop();

  public:
    ApplicationXCB() : screen(NULL) {}
    virtual ~ApplicationXCB() { /* TODO */ }
    virtual void execute();
  };

  /*
    Factory
   */
  class ApplicationFactoryXCB : public ApplicationFactory {
  public:
    virtual Application* create() { return new ApplicationXCB; }
  };
}

#endif
