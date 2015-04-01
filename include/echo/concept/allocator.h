#pragma once

#include <echo/concept/allocator_traits.h>
#include <echo/concept/iterator.h>

namespace echo {
namespace concept {

/////////////////
// allocatable //
/////////////////

namespace detail {
namespace allocator {

struct Allocator : Concept {
  template <class A, class value_type = typename A::value_type,
            class pointer = allocator_traits::pointer<A>,
            class const_pointer = allocator_traits::const_pointer<A>,
            class void_pointer = allocator_traits::void_pointer<A>,
            class const_void_pointer = allocator_traits::const_void_pointer<A>,
            class size_type = allocator_traits::size_type<A>,
            class difference_type = allocator_traits::difference_type<A> >
  auto require(A&& alloc) -> list<
      equality_comparable<A>(), noexcept(A(std::declval<A>())),
      noexcept(A(std::move(std::declval<A>()))),

      nullable_pointer<pointer>(), random_access_iterator<pointer>(),

      nullable_pointer<const_pointer>(),
      random_access_iterator<const_pointer>(),
      convertible<pointer, const_pointer>(),

      nullable_pointer<void_pointer>(), convertible<pointer, void_pointer>(),

      nullable_pointer<const_void_pointer>(),
      convertible<pointer, const_void_pointer>(),
      convertible<const_pointer, const_void_pointer>(),
      convertible<void_pointer, const_void_pointer>(),

      integral<size_type>(), signed_integral<difference_type>(),

      same<value_type&, decltype(*std::declval<pointer>())>(),
      same<const value_type&, decltype(*std::declval<const_pointer>())>(),

      same<pointer, decltype(alloc.allocate(0))>(),
      valid<decltype(alloc.deallocate(std::declval<pointer>(), 0))>()>;
};

}  // end namespace allocator
}  // end namespace detail

template <class A>
constexpr bool allocator() {
  return models<detail::allocator::Allocator, A>();
}

}  // end namespace concept
}  // end namespace echo
