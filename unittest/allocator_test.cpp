#include <echo/concept/allocator.h>
#include <echo/test.h>
#include <memory>
#include <iostream>

using namespace echo::concept;

TEST_CASE("allocator") {
  // std::cout << echo::concept::equality_comparable<std::allocator<double>>() << "\n";
  REQUIRE(echo::concept::allocator<std::allocator<double>>());
  REQUIRE(!echo::concept::allocator<double>());
}
