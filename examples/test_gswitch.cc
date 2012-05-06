#include <iostream>
#include "gswitch.hpp"
#include "pattern.hpp"

using namespace std;
using namespace gswitch;

int test(int w)
{
  switch_(w,
    case_({1,3,4}), [=]{ std::cout << "ok "; return w+100; },
    case_({2,5}),   [=]{ std::cout << "fail "; return w+1; },
    case_(8),       [=]{ std::cout << "is 8 "; return w+10; },
    default_(),     [=]{ std::cout << "undefined "; return 0; }
  );
}

int test2(int w)
{
  switch_(w,
    case_({1,3,4}), [=]{ std::cout << "ok "; return w+100; },
    case_({2,5}),   [=]{ std::cout << "fail "; return w+1; },
    case_(8),       [=]{ std::cout << "is 8 "; return w+10; },
    [](int x){ return x>=9;}, [=]{ std::cout << ">= 9 "; return 0; }
  );
  return -1;
}

void test3(std::string s)
{
  std::cout << s;
  switch_(s,
    case_("hello"), [=]{ std::cout << " world\n"; },
    case_("foo"),   [=]{ std::cout << " bar \n"; },
    default_(),     [=]{ std::cout << " no idea! \n"; }
  );
}

int test4(int w)
{
  switch_(w,
    case_(1),
    case_(3),
    case_(4),       [=]{ std::cout << "ok "; return w+100; },
    case_(2),
    case_(5),       [=]{ std::cout << "fail "; return w+1; },
    case_(8),       [=]{ std::cout << "is 8 "; return w+10; },
    default_(),     [=]{ std::cout << "undefined "; return 0; }
  );
}


int test5(int w)
{
  switch_(w,
         case_(1),
         case_(3),
         case_(4),       [=]{ std::cout << "ok "; break_(); },
         case_(2),
         case_(5),       [=]{ std::cout << "fail "; break_(); },
         case_(8),       [=]{ std::cout << "is 8 "; break_(); },
         default_(),     [=]{ std::cout << "undefined "; }
  );
}


// template <typename P>
// int test6(const P& w)
// {
//   int x,y,z;
//   switch_(w,
//       match_<int,int&,int&>(3,y,z), [&] { std::cout << "first id 3 with y:" << y
//                                                      <<" and z:"<< z;},
//       match_<int&,int,int>(x,5,6), [&] { std::cout << "second is 5 and third is 6 "
//                                                     <<" with x:" << x;},
//       match_<int&,int,int&>(x,5,z), [&] { std::cout << "second is 5 with x:" << x
//                                                      <<" and z:" << z;},
//       default_(),                     [=]{ std::cout << "undefined\n"; }
//   );
// }

template <typename P>
int test7(const P& w)
{
  int x,y,z;
  switch_(w,
     match_(make_tuple(3,ref(y),ref(z))), [&] { std::cout << "first id 3 with y:" << y
                                                       <<" and z:"<< z;},
     match_(make_tuple(ref(x),5,6)),      [&] { std::cout << "second is 5 and third is 6 "
                                                       <<" with x:" << x;},
     match_(make_tuple(ref(x),5,ref(z))), [&] { std::cout << "second is 5 with x:" << x
                                                       <<" and z:" << z;},
     default_(),                          [=]{ std::cout << "undefined\n"; }
  );
}

// template <typename P>
// int test7(const P& w)
// {
//   int x,y,z;
//   switch_(w,
//      match_(make_tuple(3,ref(y),ref(z))), [&] { std::cout << "first id 3 with y:" << y
//                                                        <<" and z:"<< z;},
//      match_(make_tuple(ref(x),5,6)),      [&] { std::cout << "second is 5 and third is 6 "
//                                                        <<" with x:" << x;},
//      match_(make_tuple(ref(x),5,ref(z))), [&] { std::cout << "second is 5 with x:" << x
//                                                        <<" and z:" << z;},
//      default_(),                          [=]{ std::cout << "undefined\n"; }
//   );
// }

template <typename P>
int test8(const P& w)
{
  int x,y,z;
  switch_(w,
      match_(3,y,z), [&] { std::cout << "first id 3 with y:" << y
                                       <<" and z:"<< z;},
      match_(x,5,6), [&] { std::cout << "second is 5 and third is 6 "
                                       <<" with x:" << x;},
      match_(x,5,z), [&] { std::cout << "second is 5 with x:" << x
                                       <<" and z:" << z;},
      default_(),    [=]{ std::cout << "undefined\n"; }
  );
}


int main(int argc, char const **argv)
{
  int y = 8;

  std::cout << "result test(2): " << test(2) << std::endl;
  std::cout << "result test(1): " << test(1) << std::endl;
  std::cout << "result test(8): " << test(y) << std::endl;
  std::cout << "result test(9): " << test(9) << std::endl;
  std::cout << "result test2(9): " << test2(9) << std::endl;

  std::cout << "test3" << std::endl;
  test3("hello");
  test3("foo");
  test3("yes");

  std::cout << "test4"<< std::endl;
  std::cout << "result test4(2): " << test4(2) << std::endl;
  std::cout << "result test4(3): " << test4(3) << std::endl;
  std::cout << "result test4(8): " << test4(y) << std::endl;

  std::cout << "test5" << std::endl;
  std::cout << "result test5(2): "; test5(2); std::cout << std::endl;
  std::cout << "result test5(3): "; test5(3); std::cout << std::endl;
  std::cout << "result test5(8): "; test5(y); std::cout << std::endl;

  // std::cout << "test6" << std::endl;
  // std::cout << "result test6(P(3,80,9)): "; test6( make_tuple(3,80,9)); std::cout << std::endl;
  // std::cout << "result test6(P(9,5,10)): "; test6( make_tuple(9,5,10)); std::cout << std::endl;
  // std::cout << "result test6(P(10,5,6)): "; test6( make_tuple(10,5,6)); std::cout << std::endl;
  // std::cout << "result test6(P(10,6,5)): "; test6( make_tuple(10,6,5)); std::cout << std::endl;

  std::cout << "test7" << std::endl;
  std::cout << "result test7(P(3,80,9)): "; test7( make_tuple(3,80,9)); std::cout << std::endl;
  // std::cout << "result test7(P(9,5,10)): "; test7( make_tuple(9,5,10)); std::cout << std::endl;
  // std::cout << "result test7(P(10,5,6)): "; test7( make_tuple(10,5,6)); std::cout << std::endl;
  // std::cout << "result test7(P(10,6,5)): "; test7( make_tuple(10,6,5)); std::cout << std::endl;

  std::cout << "test8" << std::endl;
  std::cout << "result test8(P(3,80,9)): "; test8( make_tuple(3,80,9)); std::cout << std::endl;
  std::cout << "result test8(P(9,5,10)): "; test8( make_tuple(9,5,10)); std::cout << std::endl;
  std::cout << "result test8(P(10,5,6)): "; test8( make_tuple(10,5,6)); std::cout << std::endl;
  std::cout << "result test8(P(10,6,5)): "; test8( make_tuple(10,6,5)); std::cout << std::endl;
}
