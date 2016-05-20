#include "ApplicationFactoryX11.hpp"

namespace x3d {

  Application* ApplicationFactoryX11::create() {
    return new ApplicationX11;
  }

}
