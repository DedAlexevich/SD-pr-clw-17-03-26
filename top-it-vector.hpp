#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
template< class T >
struct Vector {
  T* data;
  size_t size, cap;
};

#endif


