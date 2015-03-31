#pragma once

#include <memory>

namespace echo {
namespace allocator_traits {

template <class Allocator>
using value_type = typename std::allocator_traits<Allocator>::value_type;

template <class Allocator>
using pointer = typename std::allocator_traits<Allocator>::pointer;

template <class Allocator>
using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

template <class Allocator>
using void_pointer = typename std::allocator_traits<Allocator>::void_pointer;

template <class Allocator>
using const_void_pointer =
    typename std::allocator_traits<Allocator>::const_void_pointer;

template <class Allocator>
using difference_type =
    typename std::allocator_traits<Allocator>::difference_type;

template <class Allocator>
using size_type = typename std::allocator_traits<Allocator>::size_type;

template <class Allocator>
using propagate_on_container_copy_assignment = typename std::allocator_traits<
    Allocator>::propagate_on_container_copy_assignment;

template <class Allocator>
using propagate_on_container_move_assignment = typename std::allocator_traits<
    Allocator>::propagate_on_container_move_assignment;

template <class Allocator>
using propagate_on_container_swap =
    typename std::allocator_traits<Allocator>::propagate_on_container_swap;

template <class Allocator>
using is_always_equal =
    typename std::allocator_traits<Allocator>::is_always_equal;

}  // end namespace allocator_traits
}  // end namespace echo
