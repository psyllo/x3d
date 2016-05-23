#ifndef __X3D_FACTORYMANAGER_HPP
#define __X3D_FACTORYMANAGER_HPP

/*
  Synopsis: Generate any factory from this class.
 */

#include <memory>

using std::shared_ptr;

#ifdef __unix__
// Assume X11 if *nix
#include "ApplicationX11.hpp"
#include "DispatcherX11.hpp"
#include "ScreenX11.hpp"
#elif __APPLE__
// TODO: Apple not supported yet
#elif _WIN32
// TODO: Windows not supported yet
#endif
#include <memory>

namespace x3d {

  class FactoryManager {
    //protected:
  public:
    ApplicationFactory* applicationFactory;
    DispatcherFactory* dispatcherFactory;
    ScreenFactory* screenFactory;

#ifdef __unix__
    FactoryManager()
      : applicationFactory(new ApplicationFactoryX11),
        dispatcherFactory(new DispatcherFactoryX11),
        screenFactory(new ScreenFactoryX11)
    { }
#endif

    ApplicationFactory* getApplicationFactory() {return applicationFactory;}
    DispatcherFactory* getDispatcherFactory() {return dispatcherFactory;}
    ScreenFactory* getScreenFactory() {return screenFactory;}
  };

}

#endif
