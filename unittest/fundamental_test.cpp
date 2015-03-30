#include <echo/concept/fundamental.h>
#include <echo/test.h>
#include <memory>

using namespace echo;

TEST_CASE("copyable") {
  REQUIRE(concept::copyable<double>());
  REQUIRE(!concept::copyable<std::unique_ptr<double>>());
}
