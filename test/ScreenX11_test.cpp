#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"
#include <boost/log/trivial.hpp>
#include <catch.hpp>

#include <ScreenX11.hpp>

using namespace x3d;

TEST_CASE("ScreenX11 basics", "[x11]") {
  ScreenX11 screen;
  REQUIRE(screen.init());
}
