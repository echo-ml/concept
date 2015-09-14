#pragma once

#define DETAIL_NS detail_iterator

#include <echo/concept/fundamental.h>
#include <echo/concept/iterator_traits.h>

#include <iterator>
#include <type_traits>

namespace echo {
namespace concept {

//------------------------------------------------------------------------------
// readable
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct Readable : Concept {
  template <class T>
  auto require(T&& x) -> list<
      semiregular<T>(), same<iterator_traits::reference<T>, decltype(*x)>()>;
};
}  // end namespace detail

template <class T>
constexpr bool readable() {
  return models<DETAIL_NS::Readable, T>();
}

//------------------------------------------------------------------------------
// writable
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct Writable : Concept {
  template <class T>
  auto require(T&& x) -> list<
      semiregular<T>(),
      valid<decltype(*x = std::declval<iterator_traits::value_type<T>>())>()>;
};
}  // namespace detail

template <class T>
constexpr bool writable() {
  return models<DETAIL_NS::Writable, T>();
}

//------------------------------------------------------------------------------
// weakly_incrementable
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct WeaklyIncrementable : Concept {
  template <class T>
  auto require(T&& x)
      -> list<integral<iterator_traits::difference_type<T>>(),
              same<T&, decltype(++x)>(), valid<decltype(x++)>()>;
};
}  // namespace detail

template <class T>
constexpr bool weakly_incrementable() {
  return models<DETAIL_NS::WeaklyIncrementable, T>();
}

//------------------------------------------------------------------------------
// incrementable
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct Incrementable : Concept {
  template <class T>
  auto require(T&& x) -> list<regular<T>(), weakly_incrementable<T>(),
                              same<T, decltype(x++)>()>;
};
}  // namespace detail

template <class T>
constexpr bool incrementable() {
  return models<DETAIL_NS::Incrementable, T>();
}

//------------------------------------------------------------------------------
// weak_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct WeakIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weakly_incrementable<T>(), copyable<T>(), valid<decltype(*x)>()>;
};
}  // namespace detail

template <class T>
constexpr bool weak_iterator() {
  return models<DETAIL_NS::WeakIterator, T>();
}

//------------------------------------------------------------------------------
// iterator
//------------------------------------------------------------------------------
template <class T>
constexpr bool iterator() {
  return weak_iterator<T>() && equality_comparable<T>();
}

//------------------------------------------------------------------------------
// weak_output_iterator
//------------------------------------------------------------------------------
template <class T>
constexpr bool weak_output_iterator() {
  return writable<T>() && weak_iterator<T>();
}

//------------------------------------------------------------------------------
// output_iterator
//------------------------------------------------------------------------------
template <class T>
constexpr bool output_iterator() {
  return weak_output_iterator<T>() && iterator<T>();
}

//------------------------------------------------------------------------------
// weak_input_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct WeakInputIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weak_iterator<T>(), readable<T>(), readable<decltype(x++)>()>;
};
}  // namespace detail

template <class T>
constexpr bool weak_input_iterator() {
  return models<DETAIL_NS::WeakInputIterator, T>();
}

//------------------------------------------------------------------------------
// input_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct InputIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<weak_input_iterator<T>(), echo::concept::iterator<T>(),
              convertible<iterator_traits::iterator_category<T>,
                          std::input_iterator_tag>()>;
};
}  // namespace detail

template <class T>
constexpr bool input_iterator() {
  return models<DETAIL_NS::InputIterator, T>();
}

//------------------------------------------------------------------------------
// forward_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct ForwardIterator : Concept {
  template <class T>
  auto require(T && ) -> list<input_iterator<T>(), incrementable<T>(),
                              convertible<iterator_traits::iterator_category<T>,
                                          std::forward_iterator_tag>()>;
};
}  // namespace detail

template <class T>
constexpr bool forward_iterator() {
  return models<DETAIL_NS::ForwardIterator, T>();
}

//------------------------------------------------------------------------------
// bidirectional_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct BidirectionalIterator : Concept {
  template <class T>
  auto require(T&& x) -> list<
      forward_iterator<T>(), convertible<iterator_traits::iterator_category<T>,
                                         std::bidirectional_iterator_tag>(),
      same<T&, decltype(--x)>(), same<T, decltype(x--)>(),
      same<decltype(*x), decltype(*x--)>()>;
};
}  // namespace detail

template <class T>
constexpr bool bidirectional_iterator() {
  return models<DETAIL_NS::BidirectionalIterator, T>();
}

//------------------------------------------------------------------------------
// random_access_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
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
      convertible<decltype(x[x - x]), iterator_traits::reference<T>>()>;
};
}  // namespace detail

template <class T>
constexpr bool random_access_iterator() {
  return models<DETAIL_NS::RandomAccessIterator, T>();
}

//------------------------------------------------------------------------------
// contiguous_iterator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct ContiguousIterator : Concept {
  template <class T>
  auto require(T&& x)
      -> list<random_access_iterator<T>(),
              convertible<iterator_traits::iterator_category<T>,
                          echo::iterator::contiguous_iterator_tag>()>;
};
}  // namespace detail

template <class T>
constexpr bool contiguous_iterator() {
  return models<DETAIL_NS::ContiguousIterator, T>();
}

//------------------------------------------------------------------------------
// iterator_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct IteratorRange : Concept {
  template <class First, class Last>
  auto require(First&&, Last && )
      -> list<weak_iterator<First>(), regular<Last>(),
              equality_comparable<First, Last>()>;
};
}

template <class First, class Last>
constexpr bool iterator_range() {
  return models<DETAIL_NS::IteratorRange, First, Last>();
}

}  // end namespace concept
}  // end namespace echo

#undef DETAIL_NS
