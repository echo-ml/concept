#pragma once

#include <echo/concept/utility.h>
#include <iterator>

namespace echo {
namespace range_traits {
using std::begin;

//------------------------------------------------------------------------------
// value_type
//------------------------------------------------------------------------------
template <class Range>
using value_type = concept::uncvref_t<decltype(*begin(std::declval<Range>()))>;
}
}
