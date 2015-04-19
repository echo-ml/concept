#pragma once

#include <echo/concept/query_type.h>
#include <memory>

namespace echo {
namespace allocator_traits {

namespace detail { namespace allocator_traits {

ECHO_MAKE_TYPE_QUERIER(pointer)
ECHO_MAKE_TYPE_QUERIER(const_pointer)
ECHO_MAKE_TYPE_QUERIER(void_pointer)
ECHO_MAKE_TYPE_QUERIER(const_void_pointer)
ECHO_MAKE_TYPE_QUERIER(difference_type)
ECHO_MAKE_TYPE_QUERIER(size_type)

}}

template <class Allocator>
// using value_type = typename std::allocator_traits<Allocator>::value_type;
using value_type = typename Allocator::value_type;

// template <class Allocator>
// using pointer = typename std::allocator_traits<Allocator>::pointer;

template<class Allocator>
using pointer = 
  std::conditional_t<
    detail::allocator_traits::has_pointer<Allocator>(),
    detail::allocator_traits::query_pointer<Allocator>,
    value_type<Allocator>*
    >;

template<class Allocator>
using const_pointer = 
  std::conditional_t<
    detail::allocator_traits::has_const_pointer<Allocator>(),
    detail::allocator_traits::query_const_pointer<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::template rebind<const value_type<Allocator>>
    >;

template<class Allocator>
using void_pointer = 
  std::conditional_t<
    detail::allocator_traits::has_void_pointer<Allocator>(),
    detail::allocator_traits::query_void_pointer<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::template rebind<void>
    >;

template<class Allocator>
using const_void_pointer = 
  std::conditional_t<
    detail::allocator_traits::has_const_void_pointer<Allocator>(),
    detail::allocator_traits::query_const_void_pointer<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::template rebind<const void>
    >;

template<class Allocator>
using difference_type = 
  std::conditional_t<
    detail::allocator_traits::has_difference_type<Allocator>(),
    detail::allocator_traits::query_difference_type<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::difference_type
    >;

template<class Allocator>
using size_type = 
  std::conditional_t<
    detail::allocator_traits::has_size_type<Allocator>(),
    detail::allocator_traits::query_size_type<Allocator>,
    std::make_unsigned_t<difference_type<Allocator>>
    >;

// template <class Allocator>
// using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
//
// template <class Allocator>
// using void_pointer = typename std::allocator_traits<Allocator>::void_pointer;
//
// template <class Allocator>
// using const_void_pointer =
//     typename std::allocator_traits<Allocator>::const_void_pointer;
//
// template <class Allocator>
// using difference_type =
//     typename std::allocator_traits<Allocator>::difference_type;
//
// template <class Allocator>
// using size_type = typename std::allocator_traits<Allocator>::size_type;
//
// template <class Allocator>
// using propagate_on_container_copy_assignment = typename std::allocator_traits<
//     Allocator>::propagate_on_container_copy_assignment;
//
// template <class Allocator>
// using propagate_on_container_move_assignment = typename std::allocator_traits<
//     Allocator>::propagate_on_container_move_assignment;
//
// template <class Allocator>
// using propagate_on_container_swap =
//     typename std::allocator_traits<Allocator>::propagate_on_container_swap;
//
// template <class Allocator>
// using is_always_equal =
//     typename std::allocator_traits<Allocator>::is_always_equal;

}  // end namespace allocator_traits
}  // end namespace echo
