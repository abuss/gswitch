#include "test.hpp"


int main()
{

  // same type
  vector<int> w1 = {1,2,3};   // ok
  cout << "(1)vector<int> test: "; print(w1); cout << " =>";
  test_vector_int(w1);

  int w2 = 2;					  // ok
  cout << "(2)int(in list) test: " << w2 << "\n =>";
  test_int(w2);

  const char* w3 = "Hello";	  // ok
  cout << "(3)const char* test: " << w3 << "\n =>";
  test_pconstChar(w3);

  string w4 = "Hello";	  // ok
  cout << "(4)string test: " << w4 << "\n =>";
  test_string(w4);

  double w5 = 3.1400001;	  // ok
  cout << "(5)double test: " << w5 << "\n =>";
  test_double(w5);

  char w6 = 'H';	  // ok
  cout << "(6)char test: " << w6 << "\n =>";
  test_char(w6);

  Position2d w7 = {1,2};		  
  cout << "(7)user defined test: "; w7.print(); cout << " =>";
  test_userDefined(w7);

  map<string, int> w8; w8["David"] = 80;
  cout << "(8) map test:\n";  cout << " =>";
  test_map(w8);
  
  cout<< "mixed type test: \n =>";
  test_mixed(w4); 
}

