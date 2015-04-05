#pragma once

#include <echo/concept/iterator_category.h>

#include <iterator>

namespace echo {
namespace iterator_traits {

/////////////////////
// difference_type //
/////////////////////

template <class Iterator>
using difference_type =
    typename std::iterator_traits<Iterator>::difference_type;

////////////////
// value_type //
////////////////

template <class Iterator>
using value_type = typename std::iterator_traits<Iterator>::value_type;

///////////////
// reference //
///////////////

template <class Iterator>
using reference = typename std::iterator_traits<Iterator>::reference;

/////////////
// pointer //
/////////////

template <class Iterator>
using pointer = typename std::iterator_traits<Iterator>::pointer;

///////////////////////
// iterator_category //
///////////////////////

namespace detail {
namespace iterator_traits {

template <class Iterator, class StdIteratorCategory>
struct IteratorCategory {
  using type = StdIteratorCategory;
};

template <class T, class StdIteratorCategory>
struct IteratorCategory<T*, StdIteratorCategory> {
  using type = iterator::contiguous_iterator_tag;
};

template <class T, class StdIteratorCategory>
struct IteratorCategory<const T*, StdIteratorCategory> {
  using type = iterator::contiguous_iterator_tag;
};
}
}

template <class Iterator>
using iterator_category = typename detail::iterator_traits::IteratorCategory<
    Iterator, typename std::iterator_traits<Iterator>::iterator_category>::type;

}  // end namespace iterator_triats
}  // end namespace echo
