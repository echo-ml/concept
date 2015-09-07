#pragma once

#define DETAIL_NS detail_range

#include <echo/concept/iterator.h>
#include <echo/concept/range_traits.h>

namespace echo {
namespace concept {

//------------------------------------------------------------------------------
// range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
using std::begin;
using std::end;
struct Range : Concept {
  template <class T>
  auto require(T&& range)
      -> list<iterator_range<decltype(begin(range)), decltype(end(range))>()>;
};
}

template <class T>
constexpr bool range() {
  return models<DETAIL_NS::Range, T>();
}

//------------------------------------------------------------------------------
// output_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct OutputRange : Concept {
  template<class T>
  auto require(T&& range) -> list<
    concept::range<T>(),
    output_iterator<decltype(begin(range))>()
  >;
};
}

template<class T>
constexpr bool output_range() {
  return models<DETAIL_NS::OutputRange, T>();
}

//------------------------------------------------------------------------------
// input_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct InputRange : Concept {
  template<class T>
  auto require(T&& range) -> list<
    concept::range<T>(),
    input_iterator<decltype(begin(range))>()
  >;
};
}

template<class T>
constexpr bool input_range() {
  return models<DETAIL_NS::InputRange, T>();
}

//------------------------------------------------------------------------------
// forward_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct ForwardRange : Concept {
  template<class T>
  auto require(T&& range) -> list<
    concept::range<T>(),
    forward_iterator<decltype(begin(range))>()
  >;
};
}

template<class T>
constexpr bool forward_range() {
  return models<DETAIL_NS::ForwardRange, T>();
}

//------------------------------------------------------------------------------
// bidirectional_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct BidirectionalRange : Concept {
  template<class T>
  auto require(T&& range) -> list<
    concept::range<T>(),
    bidirectional_iterator<decltype(begin(range))>()
  >;
};
}

template<class T>
constexpr bool bidirectional_range() {
  return models<DETAIL_NS::BidirectionalRange, T>();
}

//------------------------------------------------------------------------------
// random_access_range
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct RandomAccessRange : Concept {
  template<class T>
  auto require(T&& range) -> list<
    concept::range<T>(),
    random_access_iterator<decltype(begin(range))>()
  >;
};
}

template<class T>
constexpr bool random_access_range() {
  return models<DETAIL_NS::RandomAccessRange, T>();
}

}
}

#undef DETAIL_NS
