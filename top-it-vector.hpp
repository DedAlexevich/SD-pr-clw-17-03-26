#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
namespace kuznetsov {

  template< class T >
  struct Vector {
    Vector();
    ~Vector();
    bool isEmpty() const noexcept;
  private:
    T* data_;
    size_t size_, cap_;
  };
}

template< class T >
kuznetsov::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  cap_(0)
{
}

template< class T >
kuznetsov::Vector< T >::~Vector()
{

}

template< class T >
bool kuznetsov::Vector<T>::isEmpty() const noexcept
{
  return false;
}

#endif


