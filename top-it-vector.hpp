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
    Vector(size_t size, const T& init);

    T& operator[](size_t i) noexcept;
    const T& operator[](size_t i) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();

    void insert(size_t pos, const T& v);
    void erase(size_t i);
    void erase(size_t start, size_t count);
    void clear();

    T& at(size_t pos);
    const T& at(size_t pos) const;
  private:
    explicit Vector(size_t c);
    T* data_;
    size_t size_, cap_;
  };
  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
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
  size_--;
}

template< class T >
void kuznetsov::Vector< T >::pushBack(const T& v)
{
  if (size_ + 1 < cap_) {
    data_[size_] = v;
    size_++;
    return;
  }
  T* newData = new T[cap_ * 1.5 + 1];
  cap_ = cap_ * 1.5 + 1;
  try {
    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    newData[size_] = v;
    size_++;
  } catch (...) {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
}

template< class T >
T& kuznetsov::Vector<T>::at(size_t pos)
{
  const Vector< T >* cthis = this ;
  return  const_cast< T& >(cthis->at(pos));
}

template< class T >
const T& kuznetsov::Vector<T>::at(size_t pos) const
{
  if (pos >= size_) {
    throw std::out_of_range("Out of size array");
  }
  return (*this)[pos];
}

template< class T >
T& kuznetsov::Vector<T>::operator[](size_t i) noexcept
{
  const Vector* cthis = this;
  return const_cast< T& >((*cthis)[i]);
}

template< class T >
const T& kuznetsov::Vector<T>::operator[](size_t i) const noexcept
{
  return data_[i];
}

template< class T >
kuznetsov::Vector<T>::Vector(const Vector& other): Vector(other.size_)
{
  for (size_t i = 0; i < other.size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template< class T >
kuznetsov::Vector< T >::Vector(size_t c):
  data_(c ? new T[c] : nullptr),
  size_(c),
  cap_(c)
{}

template< class T >
kuznetsov::Vector<T>::Vector(size_t size, const T& init): Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = init;
  }
}

template< class T >
bool kuznetsov::operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
  bool res = lhs.getSize() == rhs.getSize();
  res = res && (lhs.getCapacity() == rhs.getCapacity());
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    res = res && (lhs[i] == rhs[i]);
  }
  return res;
}

#endif


