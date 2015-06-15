#include <echo/concept/fundamental.h>
#include <echo/test.h>
#include <memory>
#include <iostream>
#include <functional>

using namespace echo::concept;

struct A {};

struct Indexed3 {
  void operator()(echo::index_t, echo::index_t, echo::index_t) {}
};

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

  CHECK(!k_indexed<2, Indexed3>());
  CHECK(k_indexed<3, Indexed3>());
  CHECK(!k_indexed<3, A>());
}
