#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"
#include <boost/log/trivial.hpp>
#include <catch.hpp>

#include <ScreenXCB.hpp>

using namespace x3d;

TEST_CASE("ScreenXCB init-open-close", "[xcb]") {
  ScreenXCB screen;
  // TODO: screen.setValueMask();
  // TODO: screen.setValueList();
  bool init_ok = screen.init();
  REQUIRE(init_ok);
  REQUIRE(screen.open());
  REQUIRE(screen.close());
}
