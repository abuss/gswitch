#include "gswitch.hpp"

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
using namespace gswitch;


// w1
void test_vector_int(vector<int> vec) {
  switch_(vec,
     case_({2,5}),       [=] { cout << "{2,5}\n"; },
     case_({1,2}),       [=] { cout << "{1,2}\n"; },
     case_({1,2,3,4}),   [=] { cout << "{1,2,3,4}\n"; },
     case_({1,2,3}),     [=] { cout << "{1,2,3}\n"; },
     default_(),         [=] { cout << "undefined\n";}
  );
}

// w2
void test_int(int ii) {
  switch_(ii,
     //case_({2,5}),     [=] { cout << "in {2,5}\n"; },
     //case_({1,2}),     [=] { cout << "in {1,2}\n"; },
     case_({1,2,3,4}),   [=] { cout << "in {1,2,3}\n"; },
     case_(4),           [=] { cout << "4\n"; },
     case_(5),           [=] { cout << "5\n"; },
     default_(),         [=] { cout << "undefined\n";}
  );

}
  
// w3
void test_pconstChar(const char* cc)
{
  switch_(cc,
     case_({"Hello","yo"}),   [=] { cout << "in {Hello,yo}\n"; },
     case_({"Hi"}),           [=] { cout << "in {Hi}\n"; },
     default_(),              [=] { cout << "undefined\n";}
  );
}

// w4
void test_string(string cc)
{
  switch_(cc,
     case_({"Hello","yo"}), [=] { cout << "in {Hello,yo}\n"; },
     case_({"Hi"}),         [=] { cout << "in {Hi}\n"; },
     default_(),            [=] { cout << "undefined\n";}
  );
}

// w5
void test_double(double cc)
{
  switch_(cc,
     case_({1.200001, 3.400001}),   [=] { cout << "in {1.2,3.4}\n"; },
     case_({3.1400001, 1.3}),       [=] { cout << "in {3.14,1.3}\n"; },
     case_(2.1400001),              [=] { cout << "2.14\n"; },
     default_(),                    [=] { cout << "undefined\n";}
  );
}

// w6
void test_char(char cc)
{
  switch_(cc,
     case_({'H','y'}),   [=] { cout << "in {H,y}\n"; },
     case_({'i'}),       [=] { cout << "in {i}\n"; },
     default_(),         [=] { cout << "undefined\n";}
  );
}

struct Position2d
{
  int x;
  int y;
  void print() {
    cout << "{ ";
    cout << x << ", " << y;  
    cout << " }\n";
  }
};

bool eval_guard(Position2d const& guard, 
                Position2d const& pp )
{
  return guard.x == pp.x && 
   guard.y == pp.y; 
}

// w7
void test_userDefined(Position2d pp)
{
  Position2d p1 = {1,2};
  Position2d p2 = {5,6};
  switch_(pp,
     case_(p1),     [=] { cout << "{1,2}\n"; },
     case_(p2),     [=] { cout << "{5,6}\n"; },
     default_(),    [=] { cout << "undefined\n";}
  );

}

void test_map(map<string, int> aa) {
  map<string, int> t1,t2,t3;
  t1["David"] = 70; t2["John"] = 80; t3["David"] = 80;
  switch_(aa,
     case_(t1),       [=] { cout << "{David, 70}\n"; },
     case_(t2),       [=] { cout << "{John, 80}\n"; },
     case_(t3),       [=] { cout << "{David, 80}\n"; },
     default_(),      [=] { cout << "undefined\n";}
  );
}

template <typename In>
void test_mixed(In xx)
{
  vector<int> v = {1,2,3,4};
  Position2d p = {1,2};
  switch_(xx,
     case_(v), [=] { cout << "vector<int>, {1,2,3,4}\n"; },
     case_(5),       [=] { cout << "int, 8\n"; },
     case_("Hello"), [=] { cout << "string, Hello\n"; },
     case_(3.14),    [=] { cout << "float, 3.14\n"; },
     case_('a'),     [=] { cout << "char, a\n"; },
     case_(p),      [=] { cout << "Position2d, {1,2}\n"; },
     default_(),     [=] { cout << "undefined\n";}
  );
}

// some utilities
// print: prints all elements of a container.
template<typename Container>
void gprint(const Container& c) {
  for(auto e : c)
    std::cout << e << ", ";
  std::cout << std::endl;
}

template<typename T>
void print(const vector<T>& vec) {
  cout << "{ ";
  for(int i=0; i < vec.size(); ++i) 
 cout << vec[i] << " ";  
  cout << "}\n";
}

void print(Position2d pp) {
  cout << "{ ";
 cout << pp.x << " " << pp.y;  
  cout << " }\n";
}

