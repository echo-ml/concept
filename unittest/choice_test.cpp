#include <echo/concept/overload.h>
#include <echo/concept/concept.h>
#include <echo/test.h>

using namespace echo;

template<class T, 
  CONCEPT_REQUIRES(
      std::is_floating_point<T>::value
  )
>
int f(T, overload::choice<0>) {
  return 3;
}

template<class T, 
  CONCEPT_REQUIRES(
      std::is_integral<T>::value
  )
>
int f(T, overload::choice<1>) {
  return 2;
}

template<class T>
int f(T, overload::choice<2>) {
  return 1;
}


TEST_CASE("overload") {
  REQUIRE(f(2l, overload::selector()) == 2);
}
