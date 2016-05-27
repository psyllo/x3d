#define BOOST_LOG_DYN_LINK 1 // TODO
#include "../config.h"
#include <boost/log/trivial.hpp>
#include <catch.hpp>

#include <Util.hpp>
#include <stdint.h>

using namespace x3d;

TEST_CASE("Util math", "[util]") {
  REQUIRE(Util::iexp(0, 0) == 0);
  REQUIRE(Util::iexp(0, 1) == 0);
  REQUIRE(Util::iexp(0, 10) == 0);
  REQUIRE(Util::iexp(1, 0) == 1);
  REQUIRE(Util::iexp(1, 1) == 1);
  REQUIRE(Util::iexp(1, 2) == 1);
  REQUIRE(Util::iexp(1, 10) == 1);
  REQUIRE(Util::iexp(2, 0) == 1);
  REQUIRE(Util::iexp(2, 1) == 2);
  REQUIRE(Util::iexp(2, 3) == 8);
  REQUIRE(Util::iexp(2, 8) == 256);
  REQUIRE(Util::iexp(2, 16) == 65536);
  REQUIRE(Util::iexp(2, 20) == 1048576);
  REQUIRE(Util::iexp(2, 24) == 16777216);
  REQUIRE(Util::iexp(2, 25) == 33554432);
  REQUIRE(Util::iexp(2, 26) == 67108864);
  REQUIRE(Util::iexp(2, 27) == 134217728);
  REQUIRE(Util::iexp(2, 28) == 268435456);
  REQUIRE(Util::iexp(2, 29) == 536870912);
  REQUIRE(Util::iexp(2, 30) == 1073741824);

  // Check but do not REQUIRE (stop) if they fail since right answer
  // depends on size of an integer an local system. 2^31 could
  // overflow unless integers are bigger than 32-bits
  CHECK(Util::iexp(2, 31) == -2147483648);
  CHECK(Util::iexp(2, 32) == 0);
  CHECK(Util::iexp(2, 33) == 0);
  CHECK(Util::iexp(2, 100) == 0);
}

TEST_CASE("Util reverse bits", "[util]") {
  size_t num_bits = sizeof(uint64_t) * 8;
  uint64_t Oxff_rev = Util::reverseBits(0xff, num_bits);
  REQUIRE(Oxff_rev == 0xff00000000000000);
  REQUIRE(Util::reverseBits(Oxff_rev, num_bits) == 0xff);
}
