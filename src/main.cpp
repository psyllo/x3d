#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"

#include "ApplicationXCB.hpp"
#include <boost/log/trivial.hpp>

int main(int argc, char* args[]) {
  x3d::ApplicationXCB app;
  app.execute();
  return 0;
}
