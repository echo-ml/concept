#pragma once

#include <echo/concept/concept.h>

namespace echo {
namespace concept {

//////////////
// Copyable //
//////////////

template <class T>
constexpr bool copyable() {
  return std::is_copy_constructible<T>() && std::is_copy_assignable<T>();
}

/////////////////////////
// equality_comparable //
/////////////////////////

namespace detail {
namespace fundamental {

struct EqualityComparable : Concept {
  template <class T>
  auto require(T&& x)
      -> list<convertible_to<bool>(x == x), convertible_to<bool>(x != x)>;
};

}  // end namespace fundamental
}  // end namespace detail

template <class T>
constexpr bool equality_comparable() {
  return models<detail::fundamental::EqualityComparable, T>();
}

////////////////////
// weakly_ordered //
////////////////////

namespace detail {
namespace fundamental {

struct WeaklyOrdered : Concept {
  template <class T>
  auto require(T&& x)
      -> list<convertible_to<bool>(x < x), convertible_to<bool>(x > x),
              convertible_to<bool>(x <= x), convertible_to<bool>(x >= x)>;
};

}  // end namespace fundamental
}  // end namespace detail

template <class T>
constexpr bool weakly_ordered() {
  return models<detail::fundamental::WeaklyOrdered, T>();
}

/////////////////////
// totally_ordered //
/////////////////////

template <class T>
constexpr bool totally_ordered() {
  return weakly_ordered<T>() && equality_comparable<T>();
}

/////////////////
// allocatable //
/////////////////

namespace detail {
namespace fundamental {

struct Allocatable : Concept {
  template <class T>
  auto require(const T& x)
      -> list<has_type<T*>(new T), valid<decltype(delete new T)>,
              has_type<T*>(new T[1]), valid<decltype(delete[] new T[1])> >;
};

}  // end namespace fundamental
}  // end namespace detail

template <class T>
constexpr bool allocatable() {
  return models<detail::fundamental::Allocatable, T>();
}

/////////////////
// semiregular //
/////////////////

template <class T>
constexpr bool semiregular() {
  return std::is_default_constructible<T>() &&
         std::is_copy_constructible<T>() && std::is_destructible<T>() &&
         std::is_copy_assignable<T>() && allocatable<T>();
}

/////////////
// regular //
/////////////

template <class T>
constexpr bool regular() {
  return semiregular<T>() && equality_comparable<T>();
}

}  // end namespace concept
}  // end namespace echo
