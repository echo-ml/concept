#pragma once

namespace echo {
namespace overload {

constexpr int kMaxOverloads = 10;

//------------------------------------------------------------------------------
// choice
//------------------------------------------------------------------------------
template <int I>
struct choice : choice<I + 1> {
  static_assert(I < kMaxOverloads, "");
};

template <>
struct choice<kMaxOverloads> {};

//------------------------------------------------------------------------------
// selector
//------------------------------------------------------------------------------
struct selector : choice<0> {};

}  // namespace overload
}  // namespace echo
