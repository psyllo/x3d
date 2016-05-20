#ifndef __FACTORYMANAGER_HPP
#define __FACTORYMANAGER_HPP

#include <ApplicationFactoryX11.hpp>
#include <memory>

namespace x3d {

  class FactoryManager {
  protected:
    std::shared_ptr<ApplicationFactory> appfactory;
  public:
    // TODO: App factory is hard-coded since there is currently only one kind
    FactoryManager() : appfactory(new ApplicationFactoryX11) {
    }
    std::shared_ptr<ApplicationFactory> getApplicationFactory() {return appfactory;}
  };

}

#endif
