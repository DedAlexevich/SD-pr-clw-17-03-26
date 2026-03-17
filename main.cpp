#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  kuznetsov::Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first << ": " << tests[i].second() << "\n";
  }
}
