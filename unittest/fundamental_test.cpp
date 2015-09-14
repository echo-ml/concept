#include <echo/concept/fundamental.h>
#include <echo/test.h>
#include <memory>
#include <iostream>
#include <functional>

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

  REQUIRE(callable<std::plus<double>, double, double>());
  REQUIRE(callable<std::plus<double>, double, int>());
  REQUIRE(!callable<std::plus<double>, double, A>());
  REQUIRE(!callable<int, double, A>());

  REQUIRE(printable<double>());
  REQUIRE(!printable<A>());
}
