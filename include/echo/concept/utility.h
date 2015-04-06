#pragma once

#include <type_traits>

namespace echo {
namespace concept {
template <class T>
using uncvref_t =
    typename std::remove_cv<typename std::remove_reference<T>::type>::type;
}  // namespace concept
}  // namespace echo
