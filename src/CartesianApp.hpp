#ifndef __X3D_CARTESIANAPP_HPP
#define __X3D_CARTESIANAPP_HPP

#include "Application.hpp"
#include "ScreenXCB.hpp"
#include <cstdint>

namespace x3d {

  class CartesianApp : public Application {
  protected:
    ScreenXCB* screen;
    virtual void setupScreenValues(bool updateWindow);
    virtual void createWindow();
    virtual void eventLoop();

  public:
    CartesianApp() : screen(NULL) {}
    virtual ~CartesianApp() { /* TODO */ }
    virtual void execute();
  };

  /*
    Factory
   */
  class CartesianAppFactory : public ApplicationFactory {
  public:
    virtual Application* create() { return new CartesianApp; }
  };
}

#endif
