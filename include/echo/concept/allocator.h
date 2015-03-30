#pragma once

#include <echo/concept/fundamental.h>

namespace echo {
namespace concept {

/////////////////
// allocatable //
/////////////////

CONCEPT(allocator) {
  template <class Allocator>
  auto require(Allocator alloc)
      ->valid<decltype(alloc.allocate(0)),
              decltype(alloc.deallocate(nullptr, 0)),
              has_type<typename Allocator::value_type>,
              has_type<typename Allocator::pointer>,
              has_type<typename Allocator::const_pointer>,
              has_type<typename Allocator::reference>,
              has_type<typename Allocator::const_reference> >;
};

}  // end namespace concept
}  // end namespace echo
