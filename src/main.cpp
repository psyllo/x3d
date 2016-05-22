#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "FactoryManager.hpp"
#include <boost/log/trivial.hpp>

int main(int argc, char* args[]) {
  x3d::FactoryManager fm;
  x3d::ApplicationFactory* appFact = fm.getApplicationFactory();
  std::unique_ptr<x3d::Application> app(appFact->create());
  app->execute();
  return 0;
}
