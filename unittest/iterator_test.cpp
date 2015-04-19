#include <echo/concept/iterator.h>
#include <echo/test.h>
#include <iostream>

using namespace echo;
using namespace echo::concept;

TEST_CASE("iterator") {
  REQUIRE(concept::readable<int*>());
  REQUIRE(concept::writable<int*>());
  REQUIRE(concept::weakly_incrementable<int*>());
  REQUIRE(concept::incrementable<int*>());
  REQUIRE(concept::weak_iterator<int*>());
  REQUIRE(concept::iterator<int*>());
  REQUIRE(concept::weak_output_iterator<int*>());
  REQUIRE(concept::output_iterator<int*>());
  REQUIRE(concept::weak_input_iterator<int*>());
  REQUIRE(concept::input_iterator<int*>());
  REQUIRE(concept::forward_iterator<int*>());
  REQUIRE(concept::bidirectional_iterator<int*>());
  REQUIRE(concept::random_access_iterator<int*>());
  REQUIRE(concept::contiguous_iterator<int*>());

  REQUIRE(!concept::readable<int>());
  REQUIRE(!concept::writable<int>());
  REQUIRE(!concept::weakly_incrementable<int>());
  REQUIRE(!concept::incrementable<int>());
  REQUIRE(!concept::weak_iterator<int>());
  REQUIRE(!concept::iterator<int>());
  REQUIRE(!concept::weak_output_iterator<int>());
  REQUIRE(!concept::output_iterator<int>());
  REQUIRE(!concept::weak_input_iterator<int>());
  REQUIRE(!concept::input_iterator<int>());
  REQUIRE(!concept::forward_iterator<int>());
  REQUIRE(!concept::bidirectional_iterator<int>());
  REQUIRE(!concept::random_access_iterator<int>());
  REQUIRE(!concept::contiguous_iterator<int>());
}
