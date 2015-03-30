#pragma once

#include <echo/concept/concept.h>

namespace echo {
namespace concept {

//////////////
// Copyable //
//////////////

CONCEPT(copyable, std::is_copy_constructible<_>, std::is_copy_assignable<_>){};

/////////////////////////
// equality_comparable //
/////////////////////////

CONCEPT(equality_comparable) {
  template <class T>
  auto require(T && x)
      ->valid<decltype(returns<bool>(x == x)), decltype(returns<bool>(x != x))>;
};

////////////////////
// weakly_ordered //
////////////////////

CONCEPT(weakly_ordered) {
  template <class T>
  auto require(T && x)
      ->valid<decltype(returns<bool>(x < x)), decltype(returns<bool>(x > x)),
              decltype(returns<bool>(x <= x)), decltype(returns<bool>(x >= x))>;
};

/////////////////////
// totally_ordered //
/////////////////////

CONCEPT(totally_ordered, weakly_ordered<_>, equality_comparable<_>){};

/////////////////
// allocatable //
/////////////////

CONCEPT(allocatable) {
  template <class T>
  auto require(const T& x)
      ->valid<decltype(returns<T*>(new T)), decltype(delete new T),
              decltype(returns<T*>(new T[1])), decltype(delete[] new T[1])>;
};

//////////////////
// semi_regular //
//////////////////

CONCEPT(semi_regular, std::is_default_constructible<_>,
        std::is_copy_constructible<_>, std::is_destructible<_>,
        std::is_copy_assignable<_>, allocatable<_>){};

/////////////
// regular //
/////////////

CONCEPT(regular, semi_regular<_>, equality_comparable<_>){};

}  // end namespace concept
}  // end namespace echo
