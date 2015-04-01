#include <echo/concept/iterator.h>
#include <echo/test.h>
#include <iostream>

using namespace echo;
using namespace echo::concept;

TEST_CASE("iterator") {
  REQUIRE(readable<int*>());
  REQUIRE(writable<int*>());
  REQUIRE(weakly_incrementable<int*>());
  REQUIRE(incrementable<int*>());
  REQUIRE(weak_iterator<int*>());
  REQUIRE(iterator<int*>());
  REQUIRE(weak_output_iterator<int*>());
  REQUIRE(output_iterator<int*>());
  REQUIRE(weak_input_iterator<int*>());
  REQUIRE(input_iterator<int*>());
  REQUIRE(forward_iterator<int*>());
  REQUIRE(bidirectional_iterator<int*>());
  REQUIRE(random_access_iterator<int*>());

  REQUIRE(!readable<int>());
  REQUIRE(!writable<int>());
  REQUIRE(!weakly_incrementable<int>());
  REQUIRE(!incrementable<int>());
  REQUIRE(!weak_iterator<int>());
  REQUIRE(!iterator<int>());
  REQUIRE(!weak_output_iterator<int>());
  REQUIRE(!output_iterator<int>());
  REQUIRE(!weak_input_iterator<int>());
  REQUIRE(!input_iterator<int>());
  REQUIRE(!forward_iterator<int>());
  REQUIRE(!bidirectional_iterator<int>());
  REQUIRE(!random_access_iterator<int>());
}
