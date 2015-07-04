#pragma once

#define DETAIL_NS detail_concept

#include <echo/variadic_operator.h>
#include <type_traits>

namespace echo {
namespace concept {

//------------------------------------------------------------------------------
// Concept
//------------------------------------------------------------------------------
class Concept {
 protected:
  // list
  template <bool... Values>
  using list = std::integral_constant<bool, and_c<Values...>()>;

  // valid
  template <class T>
  static constexpr bool valid() {
    return true;
  }

  // same
  template <class A, class B>
  static constexpr bool same() {
    return std::is_same<A, B>();
  }

  // convertible
  template <class A, class B>
  static constexpr bool convertible() {
    return std::is_convertible<A, B>();
  }
};

//------------------------------------------------------------------------------
// models
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <
    class Concept, class... Args,
    typename T = decltype(std::declval<Concept>().template require<Args...>(
        std::declval<Args>()...)),
    typename std::enable_if<std::is_same<T, std::true_type>::value, int>::type =
        0>
std::true_type models_(Args&&... args);

template <class Concept, class... Args>
std::false_type models_(...);

}  // end namespace detail

template <class Concept, class... Args>
constexpr bool models() {
  using Result =
      decltype(DETAIL_NS::models_<Concept, Args...>(std::declval<Args>()...));
  return Result{};
}

}  // end namespace concept

using echo::concept::Concept;
using echo::concept::models;

}  // end namespace echo

#define CONCEPT_PP_CAT_(X, Y) X##Y
#define CONCEPT_PP_CAT(X, Y) CONCEPT_PP_CAT_(X, Y)

#define CONCEPT_REQUIRES(...)                                        \
  int CONCEPT_PP_CAT(                                                \
      _concept_requires_,                                            \
      __LINE__) = 1,                                                 \
      typename std::enable_if <                                      \
              (CONCEPT_PP_CAT(_concept_requires_, __LINE__) == 2) || \
          (__VA_ARGS__),                                             \
      int > ::type = 0

#define CONCEPT_REQUIRES_REDECLARATION(...)                                    \
  int CONCEPT_PP_CAT(_concept_requires_, __LINE__),                            \
      typename std::enable_if<(CONCEPT_PP_CAT(_concept_requires_, __LINE__) == \
                               2) ||                                           \
                                  (__VA_ARGS__),                               \
                              int>::type

#define CONCEPT_MEMBER_REQUIRES(...)                                    \
  template <int CONCEPT_PP_CAT(_concept_requires_, __LINE__) = 1,       \
            typename std::enable_if<(CONCEPT_PP_CAT(_concept_requires_, \
                                                    __LINE__) == 2) ||  \
                                        (__VA_ARGS__),                  \
                                    int>::type = 0>

#define CONCEPT_ASSERT(...) static_assert((__VA_ARGS__), "Concept check failed")

#define CONCEPT_ASSERT_MSG static_assert

#undef DETAIL_NS
