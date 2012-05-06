/**
 *
 */

#pragma once
#ifndef GSWITCH_PATTERNS_HPP
#define GSWITCH_PATTERNS_HPP

#include <tuple>

namespace gswitch {

namespace details {
    
// Unification
template<int N>
struct _unify
{  
  template <typename T, typename U>
  bool operator()(T& t, U& u)
  {
    if (std::is_reference<typename std::tuple_element<N,T>::type>::value) {
      std::get<N>(t) = std::get<N>(u);
      return _unify<N-1>()(t,u);
    }
    return (std::get<N>(t) == std::get<N>(u)) && (_unify<N-1>()(t,u));
  }
};

template<>
struct _unify<-1>
{
  template <typename T, typename U>
  bool operator()(T&&, U&&)
  { return true; }
};


template <typename T, typename U>
inline bool unify(T t,U u)
{
  return _unify<std::tuple_size<T>::value-1>()(t,u);
}


template <typename T>
struct pattern_fn
{
  T t;
  pattern_fn(const T& _t) : t(_t) { }
  
  template <typename U>
  bool operator()(U&& u) const
  {
    return unify(t,u);
  }
};

} // details namespace

template <typename... Args>
details::pattern_fn<std::tuple<Args...>>
match_(Args&&... args)
{
  return details::pattern_fn<std::tuple<Args...> >(std::tuple<Args...>(std::forward<Args>(args)...));
}

} // gswitch namespace

#endif /* GSWITCH_PATTERNS_HPP */
