#include <echo/concept/range.h>
#include <echo/test.h>
#include <vector>
using namespace echo;

TEST_CASE("range") {
  CHECK(echo::concept::range<std::vector<double>>());
  CHECK(!echo::concept::range<double>());
  CHECK(echo::concept::output_range<std::vector<double>>());
  CHECK(echo::concept::forward_range<std::vector<double>>());
  CHECK(echo::concept::bidirectional_range<std::vector<double>>());
  CHECK(echo::concept::random_access_range<std::vector<double>>());
}
