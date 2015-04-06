#pragma once

#include <iterator>

namespace echo {
namespace iterator {
struct contiguous_iterator_tag : std::random_access_iterator_tag {};
}  // namespace iterator
}  // namespace echo
