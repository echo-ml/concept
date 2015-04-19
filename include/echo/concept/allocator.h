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
  template <class A>
  auto require(A&& alloc) -> list<
      equality_comparable<A>(), noexcept(A(std::declval<A>())),
      noexcept(A(std::move(std::declval<A>()))),

      nullable_pointer<allocator_traits::pointer<A>>(),
      random_access_iterator<allocator_traits::pointer<A>>(),

      nullable_pointer<allocator_traits::const_pointer<A>>(),
      random_access_iterator<allocator_traits::const_pointer<A>>(),
      convertible<allocator_traits::pointer<A>,
                  allocator_traits::const_pointer<A>>(),

      // These checks break intel's compiler so disable for now.
      // nullable_pointer<allocator_traits::void_pointer<A>>(),
      // convertible<allocator_traits::pointer<A>,
      //             allocator_traits::void_pointer<A>>(),
      //
      // nullable_pointer<allocator_traits::const_void_pointer<A>>(),
      // convertible<allocator_traits::pointer<A>,
      //             allocator_traits::const_void_pointer<A>>(),
      // convertible<allocator_traits::const_pointer<A>,
      //             allocator_traits::const_void_pointer<A>>(),
      // convertible<allocator_traits::void_pointer<A>,
      //             allocator_traits::const_void_pointer<A>>(),

      integral<allocator_traits::size_type<A>>(),
      signed_integral<allocator_traits::difference_type<A>>(),

      same<allocator_traits::value_type<A>&,
           decltype(*std::declval<allocator_traits::pointer<A>>())>(),
      same<const allocator_traits::value_type<A>&,
           decltype(*std::declval<allocator_traits::const_pointer<A>>())>(),

      same<allocator_traits::pointer<A>, decltype(alloc.allocate(0))>(),
      valid<decltype(alloc.deallocate(
          std::declval<allocator_traits::pointer<A>>(), 0))>()
          >;
};

}  // end namespace allocator
}  // end namespace detail

template <class A>
constexpr bool allocator() {
  return models<detail::allocator::Allocator, A>();
}

}  // end namespace concept
}  // end namespace echo
