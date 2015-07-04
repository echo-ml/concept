#pragma once

#define DETAIL_NS detail_iterator_traits

#include <echo/concept/iterator_category.h>

#include <iterator>

namespace echo {
namespace iterator_traits {

//------------------------------------------------------------------------------
// difference_type
//------------------------------------------------------------------------------
template <class Iterator>
using difference_type =
    typename std::iterator_traits<Iterator>::difference_type;

//------------------------------------------------------------------------------
// value_type
//------------------------------------------------------------------------------
template <class Iterator>
using value_type = typename std::iterator_traits<Iterator>::value_type;

//------------------------------------------------------------------------------
// reference
//------------------------------------------------------------------------------
template <class Iterator>
using reference = typename std::iterator_traits<Iterator>::reference;

//------------------------------------------------------------------------------
// pointer
//------------------------------------------------------------------------------
template <class Iterator>
using pointer = typename std::iterator_traits<Iterator>::pointer;

//------------------------------------------------------------------------------
// iterator_category
//------------------------------------------------------------------------------
namespace DETAIL_NS {
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
}  // namespace detail

template <class Iterator>
using iterator_category = typename DETAIL_NS::IteratorCategory<
    Iterator, typename std::iterator_traits<Iterator>::iterator_category>::type;

}  // namespace iterator_traits
}  // end namespace echo

#undef DETAIL_NS
