#include <echo/concept/fundamental.h>
#include <echo/test.h>
#include <memory>
#include <iostream>

using namespace echo::concept;

struct A {};

TEST_CASE("fundamental") {
  REQUIRE(copyable<double>());
  REQUIRE(!copyable<std::unique_ptr<double>>());
  REQUIRE(nullable_pointer<int*>());

  REQUIRE(equality_comparable<int>());
  REQUIRE(equality_comparable<double*>());
  REQUIRE(!equality_comparable<A>());

  REQUIRE(equality_comparable<int, double>());
  REQUIRE(!equality_comparable<A, double>());
  REQUIRE(!equality_comparable<double*, double>());
}
