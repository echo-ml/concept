#pragma once

#define DETAIL_NS detail_allocator_traits

#include <echo/concept/query_type.h>
#include <memory>

namespace echo {
namespace allocator_traits {

namespace DETAIL_NS {
ECHO_MAKE_TYPE_QUERIER(pointer)
ECHO_MAKE_TYPE_QUERIER(const_pointer)
ECHO_MAKE_TYPE_QUERIER(void_pointer)
ECHO_MAKE_TYPE_QUERIER(const_void_pointer)
ECHO_MAKE_TYPE_QUERIER(difference_type)
ECHO_MAKE_TYPE_QUERIER(size_type)
}

//------------------------------------------------------------------------------
// value_type
//------------------------------------------------------------------------------
template <class Allocator>
using value_type = typename Allocator::value_type;

//------------------------------------------------------------------------------
// pointer
//------------------------------------------------------------------------------
template <class Allocator>
using pointer = std::conditional_t<DETAIL_NS::has_pointer<Allocator>(),
                                   DETAIL_NS::query_pointer<Allocator>,
                                   value_type<Allocator>*>;

//------------------------------------------------------------------------------
// const_pointer
//------------------------------------------------------------------------------
template <class Allocator>
using const_pointer =
    std::conditional_t<DETAIL_NS::has_const_pointer<Allocator>(),
                       DETAIL_NS::query_const_pointer<Allocator>,
                       typename std::pointer_traits<pointer<Allocator>>::
                           template rebind<const value_type<Allocator>>>;

//------------------------------------------------------------------------------
// void_pointer
//------------------------------------------------------------------------------
template <class Allocator>
using void_pointer = std::conditional_t<
    DETAIL_NS::has_void_pointer<Allocator>(),
    DETAIL_NS::query_void_pointer<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::template rebind<void>>;

//------------------------------------------------------------------------------
// const_void_pointer
//------------------------------------------------------------------------------
template <class Allocator>
using const_void_pointer =
    std::conditional_t<DETAIL_NS::has_const_void_pointer<Allocator>(),
                       DETAIL_NS::query_const_void_pointer<Allocator>,
                       typename std::pointer_traits<
                           pointer<Allocator>>::template rebind<const void>>;

//------------------------------------------------------------------------------
// difference_type
//------------------------------------------------------------------------------
template <class Allocator>
using difference_type = std::conditional_t<
    DETAIL_NS::has_difference_type<Allocator>(),
    DETAIL_NS::query_difference_type<Allocator>,
    typename std::pointer_traits<pointer<Allocator>>::difference_type>;

//------------------------------------------------------------------------------
// size_type
//------------------------------------------------------------------------------
template <class Allocator>
using size_type =
    std::conditional_t<DETAIL_NS::has_size_type<Allocator>(),
                       DETAIL_NS::query_size_type<Allocator>,
                       std::make_unsigned_t<difference_type<Allocator>>>;

}  // end namespace allocator_traits
}  // end namespace echo

#undef DETAIL_NS
