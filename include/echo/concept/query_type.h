#pragma once

#include <echo/concept/concept.h>

namespace echo {
namespace type_querier {
struct type_not_found {};
}  // namespace type_querier
}  // namespace echo

#define ECHO_MAKE_TYPE_QUERIER(TYPE)                           \
  template <class T, class = typename T::TYPE>                 \
  constexpr bool has_##TYPE##_impl(int) {                      \
    return true;                                               \
  }                                                            \
  template <class T>                                           \
  constexpr bool has_##TYPE##_impl(...) {                      \
    return false;                                              \
  }                                                            \
  template <class T>                                           \
  constexpr bool has_##TYPE() {                                \
    return has_##TYPE##_impl<T>(0);                            \
  }                                                            \
  template <class T>                                           \
  typename T::TYPE query_##TYPE##_impl(int);                   \
  template <class T>                                           \
  echo::type_querier::type_not_found query_##TYPE##_impl(...); \
  template <class T>                                           \
  using query_##TYPE = decltype(query_##TYPE##_impl<T>(0));
