#ifndef __X3D_FACTORYMANAGER_HPP
#define __X3D_FACTORYMANAGER_HPP

/*
  Synopsis: Generate any factory from this class.
 */

#ifdef __unix__
// Assume XCB if *nix
#include "DispatcherXCB.hpp"
#include "ScreenXCB.hpp"
#elif __APPLE__
// TODO: Apple not supported yet
#elif _WIN32
// TODO: Windows not supported yet
#endif

namespace x3d {

  class FactoryManager {
    //protected:
  public:
    DispatcherFactory* dispatcherFactory;
    ScreenFactory* screenFactory;

#ifdef __unix__
    FactoryManager()
      : dispatcherFactory(new DispatcherFactoryXCB),
        screenFactory(new ScreenFactoryXCB)
    { }
#endif
    DispatcherFactory* getDispatcherFactory() {return dispatcherFactory;}
    ScreenFactory* getScreenFactory() {return screenFactory;}
  };

}

#endif
