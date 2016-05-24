#ifndef __X3D_FACTORYMANAGER_HPP
#define __X3D_FACTORYMANAGER_HPP

/*
  Synopsis: Generate any factory from this class.
 */

#include <memory>

using std::shared_ptr;

#ifdef __unix__
// Assume XCB if *nix
#include "ApplicationXCB.hpp"
#include "DispatcherXCB.hpp"
#include "ScreenXCB.hpp"
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
      : applicationFactory(new ApplicationFactoryXCB),
        dispatcherFactory(new DispatcherFactoryXCB),
        screenFactory(new ScreenFactoryXCB)
    { }
#endif

    ApplicationFactory* getApplicationFactory() {return applicationFactory;}
    DispatcherFactory* getDispatcherFactory() {return dispatcherFactory;}
    ScreenFactory* getScreenFactory() {return screenFactory;}
  };

}

#endif
