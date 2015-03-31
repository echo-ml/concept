#include <echo/concept/concept.h>
#include <echo/test.h>
#include <memory>
#include <iostream>

using namespace echo;

struct incrementable_ : Concept {
  template<class T>
  auto require(T i) -> list<
      valid<decltype(++i)>(),
      valid<decltype(i++)>()
  >;
};

template<class T>
constexpr bool incrementable() {
  return models<incrementable_, T>();
}

struct A {};

template <class T, CONCEPT_REQUIRES(incrementable<T>())>
int test_func(T x) {
  return 1;
}

template <class T, CONCEPT_REQUIRES(!incrementable<T>())>
int test_func(T x) {
  return 2;
}

template <class T>
struct TestClass {
  CONCEPT_MEMBER_REQUIRES(incrementable<T>())
  int f() { return 1; }

  CONCEPT_MEMBER_REQUIRES(!incrementable<T>())
  int f() { return 2; }
};

TEST_CASE("concept") {
  REQUIRE(incrementable<int>());
  REQUIRE(!incrementable<A>());

  REQUIRE(test_func(3) == 1);
  REQUIRE(test_func(A()) == 2);

  REQUIRE(TestClass<int>().f() == 1);
  REQUIRE(TestClass<A>().f() == 2);
}

