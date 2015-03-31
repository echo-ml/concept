#include <echo/concept/allocator.h>
#include <echo/test.h>
#include <memory>

using namespace echo::concept;

TEST_CASE("allocator") {
  std::allocator<double> alloc;
  alloc.allocate(3);
  REQUIRE(allocator<std::allocator<double>>());
}
