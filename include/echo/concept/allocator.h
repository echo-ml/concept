#pragma once

#include <echo/concept/concept.h>

namespace echo {
namespace concept {

/////////////////
// allocatable //
/////////////////

namespace detail { namespace allocator {

struct Allocator : Concept {
  template <class T>
  auto require(T&& alloc) ->list<
    valid<typename T::value_type>(),
    same<typename T::value_type&, decltype(*typename std::allocator_traits<T>::pointer())>(),
    valid<decltype(alloc.allocate(0))>(),
    valid<decltype(alloc.deallocate(nullptr, 0))>()

    // valid<std::allocator_traits<
    // valid<typename T::value_type>(),
    // valid<typename T::po>(),
    // valid<typename T::value_type>(),

  >;
  // valid<decltype(alloc.allocate(0))>()
  // >;
      // -> list<valid<decltype(alloc.allocate(0))>,
      //         valid<decltype(alloc.deallocate(nullptr, 0))>,
      //         valid<typename T::value_type>, valid<typename T::pointer>,
      //         valid<typename T::const_pointer>, valid<typename T::reference>,
      //         valid<typename T::const_reference>>;
};

} //end namespace allocator
} //end namespace detail

template<class T>
constexpr bool allocator() {
  return models<detail::allocator::Allocator, T>();
}

}  // end namespace concept
}  // end namespace echo
