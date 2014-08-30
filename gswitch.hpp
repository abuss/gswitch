/**
 * gswitch Library
 */

#ifndef GSWITCH_HPP
#define GSWITCH_HPP

// #include <iostream>
#include <algorithm>
#include <string>

namespace gswitch {

namespace guard {
    
template <typename Guard, typename T>
bool eval_guard(Guard g, T x)
{
  return false;
}


template <template<typename,typename> class C, typename T, typename A>
bool eval_guard(const std::initializer_list<T>& guard, const C<T,A>& x)
{
  return (x.size()==guard.size()) && (std::equal(x.begin(),x.end(),guard.begin()));
}


template <typename T, typename U>
bool eval_guard(const std::initializer_list<T>& guard, const U& x)
{
  return (std::find(guard.begin(),guard.end(),x)!=guard.end());    
}


template <typename T>
bool eval_guard(const T& g, const T& x)
{
  return (g==x);    
}

bool eval_guard(const char* g, const std::string& x)
{
  return x.compare(g)==0;    
}

bool eval_guard(const char* g, const char* x)
{
  return eval_guard(g, std::string(x));
}


template <typename Guard>
struct case_fn
{
  const Guard& guard;
  case_fn(const Guard& _g) : guard(_g) {}
  
  template <typename T>
  bool operator()(const T& x) const
  {
    return eval_guard(guard,x);
  }
};

} // guard namespace


template <typename Guard>
guard::case_fn<Guard>
case_(const Guard& g)
{
  return guard::case_fn<Guard>(g);
}

template <typename T>
guard::case_fn<std::initializer_list<T>>
case_(std::initializer_list<T> const& g)
{
  return guard::case_fn<std::initializer_list<T>>(g);
}


struct default_ {
  template <typename T>
  bool operator()(T const&) const
  {
    return true;
  }
};


void break_() {}

template <typename T>
void switch_(T const& x)
{ }


template <typename T, typename Guard, typename Body, typename... Cases>
void switch_(const T& x, const Guard& guard, const Body& body, const Cases&... cases)
{
  if (guard(x))
    body();
  else
    switch_(x,cases...);
}


template <typename T, typename Guard0, typename Guard1, typename... Cases>
void switch_(const T& x, const guard::case_fn<Guard0>& guard0, const guard::case_fn<Guard1>& guard1, const Cases&... cases)
{
  if (guard0(x))
    switch_(x,case_(x),cases...);
  else
    switch_(x,guard1,cases...);
}

} // gswitch namespace

#endif /* GSWITCH_HPP */


