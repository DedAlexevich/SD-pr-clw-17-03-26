#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
namespace kuznetsov {

  template< class T >
  struct Vector {
    Vector();
    ~Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();

    void insert(size_t pos, const T& v);
    void erase(size_t i);
    void erase(size_t start, size_t count);
    void clear();
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
  delete[] data_;
}

template< class T >
bool kuznetsov::Vector< T >::isEmpty() const noexcept
{
  return !size_ or !data_;
}

template< class T >
size_t kuznetsov::Vector<T>::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t kuznetsov::Vector<T>::getCapacity() const noexcept
{
  return cap_;
}

template< class T >
void kuznetsov::Vector<T>::popBack()
{
}

template< class T >
void kuznetsov::Vector< T >::pushBack(const T& v)
{

}

#endif


