#pragma once

#include <echo/concept/fundamental.h>

#include <iterator>
#include <type_traits>

namespace echo {
namespace concept {

CONCEPT(readable, semi_regular<_>) {
  template <class T>
  auto require(T x)
      ->valid<decltype(
          returns<typename std::iterator_traits<T>::reference>(*x))>;
};

CONCEPT(writable, semi_regular<_>) {
  template <class T>
  auto require(T x)
      ->valid<decltype(
          *x = std::declval<typename std::iterator_traits<T>::value_type>())>;
};

CONCEPT(weakly_incrementable, semi_regular<_>) {
  template <class T>
  auto require(T x)
      ->valid<has_type<typename std::iterator_traits<T>::difference_type,
                       std::is_integral<_>>,
              decltype(returns<T&>(++x)), decltype(x++)>;
};

CONCEPT(incrementable, weakly_incrementable<_>, regular<_>){};

CONCEPT(weak_iterator, weakly_incrementable<_>, copyable<_>){};

CONCEPT(iterator, weak_iterator<_>, equality_comparable<_>){};

CONCEPT(weak_output_iterator, writable<_>, weak_iterator<_>){};

CONCEPT(output_iterator, weak_output_iterator<_>, iterator<_>){};

CONCEPT(weak_input_iterator, weak_iterator<_>, readable<_>) {
  template <class T>
  auto require(T x)->valid<decltype(returns<readable<_>>(x++))>;
};

CONCEPT(input_iterator, weak_input_iterator<_>, iterator<_>) {
  template <class T>
  auto require(T x)
      ->valid<is_true<std::is_convertible<
          typename std::iterator_traits<T>::iterator_category,
          std::input_iterator_tag>>>;
};

CONCEPT(forward_iterator, input_iterator<_>, incrementable<_>) {
  template <class T>
  auto require(T x)
      ->valid<is_true<std::is_convertible<
          typename std::iterator_traits<T>::iterator_category,
          std::forward_iterator_tag>>>;
};

CONCEPT(bidirectional_iterator, forward_iterator<_>) {
  template <class T>
  auto require(T x)
      ->valid<is_true<std::is_convertible<
                  typename std::iterator_traits<T>::iterator_category,
                  std::bidirectional_iterator_tag>>,
              decltype(returns<T&>(--x)), decltype(returns<T>(x--)),
              is_true<std::is_same<decltype(*x), decltype(*x--)>>>;
};

CONCEPT(random_access_iterator, bidirectional_iterator<_>, totally_ordered<_>) {
  template <class T>
  auto require(T x)
      ->valid<
          is_true<std::is_convertible<
              typename std::iterator_traits<T>::iterator_category,
              std::random_access_iterator_tag>>,
          decltype(returns<std::is_integral<_>>(x - x)),
          decltype(returns<std::is_signed<_>>(x - x)),
          decltype(returns<typename std::iterator_traits<T>::difference_type>(
              x - x)),
          decltype(returns<T>(x + (x - x))), decltype(returns<T>((x - x) + x)),
          decltype(returns<T>(x - (x - x))),
          decltype(returns<T&>(x += (x - x))),
          decltype(returns<T&>(x -= (x - x))),
          decltype(
              returns<typename std::iterator_traits<T>::reference>(x[x - x]))>;
};

}  // end namespace concept
}  // end namespace echo
