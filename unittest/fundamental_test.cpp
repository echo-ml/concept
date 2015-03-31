#include <echo/concept/fundamental.h>
#include <echo/test.h>
#include <memory>
#include <iostream>

using namespace echo::concept;


TEST_CASE("fundamental") {
  REQUIRE(copyable<double>());
  REQUIRE(!copyable<std::unique_ptr<double>>());
}
