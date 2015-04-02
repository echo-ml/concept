#include <echo/concept/query_type.h>
#include <echo/test.h>

ECHO_MAKE_TYPE_QUERIER(value_type)

struct A {
  using value_type = int;
};

struct B {};

TEST_CASE("query_type") {
  REQUIRE(has_value_type<A>());
  REQUIRE(!has_value_type<B>());
  REQUIRE(!has_value_type<int>());
  REQUIRE(std::is_same<query_value_type<A>, int>());
  REQUIRE(!std::is_same<query_value_type<B>, int>());
  REQUIRE(std::is_same<query_value_type<int>,
                       echo::type_querier::type_not_found>());
}
