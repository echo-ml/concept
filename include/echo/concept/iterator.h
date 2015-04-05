#pragma once

#include <echo/concept/fundamental.h>
#include <echo/concept/iterator_traits.h>

#include <iterator>
#include <type_traits>

namespace echo {
namespace concept {

//////////////
// Readable //
//////////////

namespace detail {
namespace iterator {

struct Readable : Concept {
  template <class T>
  auto require(T&& x) -> list<
      semiregular<T>(), same<iterator_traits::reference<T>, decltype(*x)>()>;
};

}  // end namespace iterator
}  // end namespace detail

template <class T>
constexpr bool readable() {
  return models<detail::iterator::Readable, T>();
}

//////////////
// writable //
//////////////

namespace detail {
namespace iterator {

struct Writable : Concept {
  template <class T>
  auto require(T&& x) -> list<
      semiregular<T>(),
      valid<decltype(*x = std::declval<iterator_traits::value_type<T>>())>()>;
};
}
}

template <class T>
constexpr bool writable() {
  return models<detail::iterator::Writable, T>();
}

//////////////////////////
// weakly_incrementable //
//////////////////////////

namespace detail {
namespace iterator {

struct WeaklyIncrementable : Concept {
  template <class T>
  auto require(T&& x)
      -> list<integral<iterator_traits::difference_type<T>>(),
              same<T&, decltype(++x)>(), valid<decltype(x++)>()>;
};
}
}

template <class T>
constexpr bool weakly_incrementable() {
  return models<detail::iterator::WeaklyIncrementable, T>();
}

///////////////////
// incrementable //
///////////////////

namespace detail {
namespace iterator {

struct Incrementable : Concept {
  template <class T>
  auto require(T&& x) -> list<regular<T>(), weakly_incrementable<T>(),
                              same<T, decltype(x++)>()>;
};
}
}

template <class T>
constexpr bool incrementable() {
  return models<detail::iterator::Incrementable, T>();
}

///////////////////
// weak_iterator //
///////////////////

namespace detail {
namespace iterator {

struct WeakIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weakly_incrementable<T>(), copyable<T>(), valid<decltype(*x)>()>;
};
}
}

template <class T>
constexpr bool weak_iterator() {
  return models<detail::iterator::WeakIterator, T>();
}

//////////////
// iterator //
//////////////

template <class T>
constexpr bool iterator() {
  return weak_iterator<T>() && equality_comparable<T>();
}

//////////////////////////
// weak_output_iterator //
//////////////////////////

template <class T>
constexpr bool weak_output_iterator() {
  return writable<T>() && weak_iterator<T>();
}

//////////////////////////
// weak_output_iterator //
//////////////////////////

template <class T>
constexpr bool output_iterator() {
  return weak_output_iterator<T>() && iterator<T>();
}

/////////////////////////
// weak_input_iterator //
/////////////////////////

namespace detail {
namespace iterator {

struct WeakInputIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weak_iterator<T>(), readable<T>(), readable<decltype(x++)>()>;
};
}
}

template <class T>
constexpr bool weak_input_iterator() {
  return models<detail::iterator::WeakInputIterator, T>();
}

////////////////////
// input_iterator //
////////////////////

namespace detail {
namespace iterator {

struct InputIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weak_input_iterator<T>(), echo::concept::iterator<T>(),
              convertible<iterator_traits::iterator_category<T>,
                          std::input_iterator_tag>()>;
};
}
}

template <class T>
constexpr bool input_iterator() {
  return models<detail::iterator::InputIterator, T>();
}

//////////////////////
// forward_iterator //
//////////////////////

namespace detail {
namespace iterator {

struct ForwardIterator : Concept {
  template <class T>
  auto require(T && ) -> list<input_iterator<T>(), incrementable<T>(),
                              convertible<iterator_traits::iterator_category<T>,
                                          std::forward_iterator_tag>()>;
};
}
}

template <class T>
constexpr bool forward_iterator() {
  return models<detail::iterator::ForwardIterator, T>();
}

////////////////////////////
// bidirectional_iterator //
////////////////////////////

namespace detail {
namespace iterator {

struct BidirectionalIterator : Concept {
  template <class T>
  auto require(T&& x) -> list<
      forward_iterator<T>(), convertible<iterator_traits::iterator_category<T>,
                                         std::bidirectional_iterator_tag>(),
      same<T&, decltype(--x)>(), same<T, decltype(x--)>(),
      same<decltype(*x), decltype(*x--)>()>;
};
}
}

template <class T>
constexpr bool bidirectional_iterator() {
  return models<detail::iterator::BidirectionalIterator, T>();
}

////////////////////////////
// random_access_iterator //
////////////////////////////

namespace detail {
namespace iterator {

struct RandomAccessIterator : Concept {
  template <class T>
  auto require(T&& x) -> list<
      bidirectional_iterator<T>(), totally_ordered<T>(),
      convertible<iterator_traits::iterator_category<T>,
                  std::random_access_iterator_tag>(),
      signed_integral<decltype(x - x)>(),
      same<iterator_traits::difference_type<T>, decltype(x - x)>(),
      same<T, decltype(x + (x - x))>(), same<T, decltype((x - x) + x)>(),
      same<T, decltype(x - (x - x))>(), same<T&, decltype(x += (x - x))>(),
      same<T&, decltype(x -= (x - x))>(),
      same<iterator_traits::reference<T>, decltype(x[x - x])>()>;
};
}
}

template <class T>
constexpr bool random_access_iterator() {
  return models<detail::iterator::RandomAccessIterator, T>();
}

/////////////////////////
// contiguous_iterator //
/////////////////////////

namespace detail {
namespace iterator {

struct ContiguousIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<random_access_iterator<T>(),
              convertible<iterator_traits::iterator_category<T>,
                          echo::iterator::contiguous_iterator_tag>()>;
};
}
}

template <class T>
constexpr bool contiguous_iterator() {
  return models<detail::iterator::ContiguousIterator, T>();
}

}  // end namespace concept
}  // end namespace echo
