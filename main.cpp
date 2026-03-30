#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  kuznetsov::Vector< int > v;
  return v.isEmpty();
}

bool testInititalazeList()
{
  kuznetsov::Vector< int > v = {1, 2, 3, 4, 5, 6};
  bool res = v.getSize() == 6;
  for (size_t i = 1; i <= 6; i++) {
    res = res && v.at(i-1) == i;
  }
  return res;
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

bool testPushBackLValue()
{
  kuznetsov::Vector<std::string> v;
  std::string str = "hello";
  v.pushBack(str);
  bool res = v.getSize() == 1;
  res = res && (v.at(0) == "hello");
  res = res && (str == "hello");
  return res;
}

bool testPushBackRValue()
{
  kuznetsov::Vector<std::string> v;
  v.pushBack(std::string("world"));
  bool res = v.getSize() == 1;
  res = res && (v.at(0) == "world");
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

bool testElementAccess()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  try {
    int& val = v[0];
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  kuznetsov::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementConstAccess()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  const kuznetsov::Vector< int >& cv = v;
  try {
    const int& val = cv[0];
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const kuznetsov::Vector< int > cv;
  try {
    cv.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testCopyConstractor()
{
  kuznetsov::Vector< int > v;
  kuznetsov::Vector< int > cv = v;
  return v == cv;
}

bool testCopyNoneEmptyVector()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  kuznetsov::Vector< int > cv = v;
  return v == cv;
}

bool testMoveConstructor()
{
  kuznetsov::Vector< int > v(4, 2);
  kuznetsov::Vector< int > v2(std::move(v));
  bool res = v.getSize() == 0 && v2.getSize() == 4;
  return res;
}

bool testCopyAssignment()
{
  kuznetsov::Vector< int > v1(5, 3);
  kuznetsov::Vector< int > v2(3, 4);
  v2 = v1;
  bool res = v2.getSize() == v1.getSize();
  for (size_t i = 0; res && i < v1.getSize(); ++i) {
    res = res && v1[i] == v2[i];
  }
  v2.erase(1);
  res = res && (v1.getSize() - v2.getSize() == 1);
  return res;
}

bool testMoveAssignment()
{
  kuznetsov::Vector< int > v1(5, 3);
  kuznetsov::Vector< int > v2(3, 4);
  v2 = std::move(v1);
  bool res = v2.getSize() == 5 && v1.getSize() == 0;
  return res;
}

bool testInsert()
{
  kuznetsov::Vector< int > vect {1, 2, 3, 4, 5};
  int a[] {8, 7, 12, 23};
  vect.insert(1, a[0]);
  vect.insert(3, a[1]);
  vect.insert(5, a[2]);
  vect.insert(0, a[3]);
  int control[] = {23, 1, 8, 2, 7, 3, 12, 4, 5};
  bool res = vect.getSize() == 9;
  for (size_t i = 0; res && i < vect.getSize(); i++) {
    res = res && (vect[i] == control[i]);
  }
  return res;
}

bool testMoveInsert()
{
  kuznetsov::Vector<std::string> vect;
  vect.pushBack("one");
  vect.pushBack("three");

  vect.insert(1, std::move(std::string("two")));

  bool res = vect.getSize() == 3;
  res = res && (vect[0] == "one");
  res = res && (vect[1] == "two");
  res = res && (vect[2] == "three");

  return res;
}

bool testMoveInsertWithIterator()
{
  kuznetsov::Vector<std::string> vect;
  vect.pushBack("one");
  vect.pushBack("three");

  vect.insert(vect.cbegin() + 1, std::move(std::string("two")));

  bool res = vect.getSize() == 3;
  res = res && (vect[0] == "one");
  res = res && (vect[1] == "two");
  res = res && (vect[2] == "three");

  return res;
}

bool testInsertByRange()
{
  kuznetsov::Vector< int > vect;
  vect.pushBack(1);
  vect.pushBack(2);
  vect.pushBack(3);
  vect.pushBack(4);
  vect.pushBack(5);

  kuznetsov::Vector< int > vect2;
  vect2.pushBack(6);
  vect2.pushBack(7);
  vect2.pushBack(8);
  vect2.pushBack(9);
  vect2.pushBack(10);

  vect2.insert(2, vect, 1, 4);
  int control[] = {6, 7, 2, 3, 4, 8, 9, 10};
  bool res = vect2.getSize() == 8;
  for (size_t i = 0; res && i < vect.getSize(); i++) {
    res = res && (vect2[i] == control[i]);
  }
  try {
    vect2.insert(7, vect, 0, 100);
    res = false;
  } catch (const std::out_of_range& e) {}

  return res;
}

bool testErase()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.erase(2);
  int control[] = {1, 2, 4, 5};
  bool res = v.getSize() == 4;
  for (size_t i = 0; i < v.getSize(); ++i) {
    res = res && v[i] == control[i];
  }
  try {
    v.erase(100);
    return false;
  } catch (const std::out_of_range& e) {

  }
  return res;
}

bool testEraseByRange()
{
  kuznetsov::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.pushBack(6);
  v.pushBack(7);
  v.erase(2, 3);
  int control[] = {1, 2, 6, 7};
  bool res = v.getSize() == 4;
  for (size_t i = 0; i < v.getSize(); ++i) {
    res = res && v[i] == control[i];
  }
  try {
    v.erase(100, 3);
    return false;
  } catch (const std::out_of_range& e) {

  }
  return res;
}

bool testInsertWithIterator()
{
  auto vect = kuznetsov::Vector< int >();
  vect.pushBack(1);
  vect.pushBack(2);
  vect.pushBack(3);
  vect.pushBack(4);
  vect.pushBack(5);
  auto it = vect.cbegin() + 1;
  vect.insert(it, 8);
  it = vect.cbegin() + 3;
  vect.insert(it, 7);
  it = vect.cbegin() + 5;
  vect.insert(it, 12);
  it = vect.cbegin();
  vect.insert(it, 23);
  it = vect.cend();
  vect.insert(it, 8);
  int control[] = {23, 1, 8, 2, 7, 3, 12, 4, 5, 8};
  bool res = vect.getSize() == 10;
  for (size_t i = 0; res && i < vect.getSize(); i++) {
    res = res && (vect[i] == control[i]);
  }
  return res;
}

bool testInsertByRangeWithIterator()
{
  kuznetsov::Vector< int > vect;
  vect.pushBack(1);
  vect.pushBack(2);
  vect.pushBack(3);
  vect.pushBack(4);
  vect.pushBack(5);

  kuznetsov::Vector< int > vect2;
  vect2.pushBack(6);
  vect2.pushBack(7);
  vect2.pushBack(8);
  vect2.pushBack(9);
  vect2.pushBack(10);
  auto start = vect.cbegin() + 1;
  auto end = vect.cbegin() + 4;
  vect2.insert(vect2.cbegin() + 2, start, end);
  int control[] = {6, 7, 2, 3, 4, 8, 9, 10};
  bool res = vect2.getSize() == 8;
  for (size_t i = 0; res && i < vect.getSize(); i++) {
    res = res && (vect2[i] == control[i]);
  }
  try {
    vect2.insert(vect2.cbegin() + 100, vect.cbegin(), vect.cend());
    res = false;
  } catch (const std::out_of_range& e) {}

  return res;
}

bool testEraseIterator()
{
  kuznetsov::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);

  auto it = v.cbegin() + 1;
  auto ret = v.erase(it);

  bool res = v.getSize() == 3;
  res = res && (v.at(0) == 1);
  res = res && (v.at(1) == 3);
  res = res && (v.at(2) == 4);
  res = res && (*ret == 3);
  return res;
}

bool testEraseIteratorRange()
{
  kuznetsov::Vector<int> v;
  for (int i = 1; i <= 5; ++i) v.pushBack(i);

  auto start = v.cbegin() + 1;
  auto end = v.cbegin() + 3;
  auto ret = v.erase(start, end);

  bool res = v.getSize() == 3;
  res = res && (v.at(0) == 1);
  res = res && (v.at(1) == 4);
  res = res && (v.at(2) == 5);
  res = res && (*ret == 4);
  return res;
}

bool even(int val)
{
  return val % 2 == 0;
}

bool testErasePredicate()
{
  kuznetsov::Vector<int> v;
  for (int i = 1; i <= 5; ++i) {
    v.pushBack(i);
  }

  auto ret = v.erase(v.cbegin(), v.cend(), even);

  bool res = v.getSize() == 3;
  res = res && (v.at(0) == 1);
  res = res && (v.at(1) == 3);
  res = res && (v.at(2) == 5);
  res = res && (ret == v.cbegin());
  return res;
}

bool testClear()
{
  kuznetsov::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.clear();
  return v.isEmpty();
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Non empty vector with "
     "initializer list", testInititalazeList},
    {"Get Capacity", testGetCapacity},
    {"PushBack LValue", testPushBackLValue},
    {"PushBack RValue", testPushBackRValue},
    {"Pop From Vector", testPopFromVector},
    {"Get Size", testGetSize},
    {"Element Access", testElementAccess},
    {"Element Access Out of Bound", testElementOutOfBoundAccess},
    {"Element const Access", testElementConstAccess},
    {"Element const Access Out of Bound", testElementOutOfBoundConstAccess},
    {"Copy Empty Vector", testCopyConstractor},
    {"Copy None Empty Vector", testCopyNoneEmptyVector},
    {"Move constructor", testMoveConstructor},
    {"Copy Assignment", testCopyAssignment},
    {"Move Assignment", testMoveAssignment},
    {"Insert", testInsert},
    {"Move insert", testMoveInsert},
    {"Move insert with iterator", testMoveInsertWithIterator},
    {"Insert with iterator", testInsertWithIterator},
    {"Insert by range", testInsertByRange},
    {"Insert by range with iterator", testInsertByRangeWithIterator},
    {"Erase", testErase},
    {"Erase by range", testEraseByRange},
    {"Erase Iterator", testEraseIterator},
    {"Erase Iterator Range", testEraseIteratorRange},
    {"Erase Predicate", testErasePredicate},
    {"Clear", testClear},
  };

  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  size_t succesed = 0;
  size_t failed = 0;
  bool pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res  = tests[i].second();
    succesed += res;
    failed += !res;
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }

  std::cout << "Total: " << pass << '\n';
  std::cout << "Passed: " << succesed << '\n';
  std::cout << "Failed: " << failed << '\n';
}
