#pragma once

#include <iterator>

namespace echo {
namespace iterator_traits {

template <class Iterator>
using difference_type =
    typename std::iterator_traits<Iterator>::difference_type;

template <class Iterator>
using value_type = typename std::iterator_traits<Iterator>::value_type;

template <class Iterator>
using reference = typename std::iterator_traits<Iterator>::reference;

template <class Iterator>
using pointer = typename std::iterator_traits<Iterator>::pointer;

template <class Iterator>
using iterator_category =
    typename std::iterator_traits<Iterator>::iterator_category;

} //end namespace iterator_triats
} //end namespace echo
