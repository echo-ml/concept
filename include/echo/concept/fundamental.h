#pragma once

#include <echo/concept/concept.h>

namespace echo {
namespace concept {

//////////////
// copyable //
//////////////

template <class T>
constexpr bool copyable() {
  return std::is_copy_constructible<T>() && std::is_copy_assignable<T>();
}

///////////////////////////
// default_constructible //
///////////////////////////

template <class T>
constexpr bool default_constructible() {
  return std::is_default_constructible<T>();
}

//////////////////
// destructible //
//////////////////

template <class T>
constexpr bool destructible() {
  return std::is_nothrow_destructible<T>();
}

/////////////////////////
// equality_comparable //
/////////////////////////

namespace detail {
namespace fundamental {

struct EqualityComparable : Concept {
  template <class T>
  auto require(T&& x) -> list<convertible<bool, decltype(x == x)>(),
                              convertible<bool, decltype(x != x)>()>;
};

}  // end namespace fundamental
}  // end namespace detail

template <class T>
constexpr bool equality_comparable() {
  return models<detail::fundamental::EqualityComparable, T>();
}

namespace detail {
namespace fundamental {

struct EqualityComparable2 : Concept {
  template <class U, class V>
  auto require(U&& u, V&& v)
      -> list<equality_comparable<U>(), equality_comparable<V>(),
              convertible<bool, decltype(u == v)>(),
              convertible<bool, decltype(v == u)>(),
              convertible<bool, decltype(u != v)>(),
              convertible<bool, decltype(v != u)>()>;
};
}
}

template <class U, class V>
constexpr bool equality_comparable() {
  return models<detail::fundamental::EqualityComparable2, U, V>();
}

////////////////////
// weakly_ordered //
////////////////////

namespace detail {
namespace fundamental {

struct WeaklyOrdered : Concept {
  template <class T>
  auto require(T&& x) -> list<convertible<bool, decltype(x < x)>(),
                              convertible<bool, decltype(x > x)>(),
                              convertible<bool, decltype(x <= x)>(),
                              convertible<bool, decltype(x >= x)>()>;
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
  auto require(const T& x) -> list<
      same<T*, decltype(new T)>(), valid<decltype(delete new T)>(),
      same<T*, decltype(new T[1])>(), valid<decltype(delete[] new T[1])>()>;
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

//////////////
// integral //
//////////////

template <class T>
constexpr bool integral() {
  return std::is_integral<T>();
}

/////////////////////
// signed_integral //
/////////////////////

template <class T>
constexpr bool signed_integral() {
  return integral<T>() && std::is_signed<T>();
}

//////////////////////
// nullable_pointer //
//////////////////////

namespace detail {
namespace fundamental {

struct NullablePointer : Concept {
  template <class T>
  auto require(T&& x)
      -> list<equality_comparable<T>(), default_constructible<T>(),
              copyable<T>(), destructible<T>(), valid<decltype(T(nullptr))>(),
              same<T&, decltype(x = nullptr)>(),
              convertible<bool, decltype(x == nullptr)>(),
              convertible<bool, decltype(x != nullptr)>()>;
};
}
}

template <class T>
constexpr bool nullable_pointer() {
  return models<detail::fundamental::NullablePointer, T>();
}

}  // end namespace concept
}  // end namespace echo
