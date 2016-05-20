#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include <FactoryManager.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::endl;


int main(int argc, char* args[]) {
  x3d::FactoryManager fm;
  std::unique_ptr<x3d::Application> app(fm.getApplicationFactory()->create());
  app->execute();

  return 0;
}
