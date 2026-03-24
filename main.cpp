#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  kuznetsov::Vector< int > v;
  return v.isEmpty();
}

bool testGetSize()
{
  kuznetsov::Vector< int > v;
  bool res = v.getSize() == 0;
  v.pushBack(3);
  res = res && v.getSize() == 1;
  return res;
}

bool testGetCapacity()
{
  kuznetsov::Vector< int > v;
  v.pushBack(4);
  v.popBack();
  return v.getCapacity() == 1;
}

bool testPushIntoVector()
{
  kuznetsov::Vector< int > v;
  v.pushBack(3);
  v.pushBack(1);
  bool res = v.getSize() == 2;
  res = res && v.at(0) == 3;
  res = res && v.at(1) == 1;
  return res;
}

bool testPopFromVector()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  bool res = v.getSize() == 1;
  v.popBack();
  res = res && v.getSize() == 0;
  return v.isEmpty();
}


int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Get Capacity", testGetCapacity},
    {"Push Into Vector", testPushIntoVector},
    {"Pop From Vector", testPopFromVector},
    {"Get Size", testGetSize},
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res  = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "Total: " << pass << '\n';
  // count of passed/failed tests
  //Print only failed tests
  //Print nothing if all tests passed
}
