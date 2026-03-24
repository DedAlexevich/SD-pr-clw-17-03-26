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

    void swap(Vector< T >& rhs) noexcept;
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();

    void insert(size_t pos, const T& v);
    void insert(size_t pos, const Vector< T >& v, size_t start, size_t end);

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
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    res = res && (lhs[i] == rhs[i]);
  }
  return res;
}

template< class T >
void kuznetsov::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(cap_, rhs.cap_);
}

template< class T >
kuznetsov::Vector<T>& kuznetsov::Vector<T>::operator=(const Vector& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
kuznetsov::Vector<T>::Vector(Vector&& o):
  data_(o.data_),
  size_(o.size_),
  cap_(o.cap_)
{
  o.data_ = nullptr;
}

template< class T >
kuznetsov::Vector<T>& kuznetsov::Vector<T>::operator=(Vector&& o)
{
  if (this == std::addressof(o)) {
    return *this;
  }
  Vector< T > cpy(std::move(o));
  swap(cpy);
  return *this;
}

template< class T >
void kuznetsov::Vector< T >::insert(size_t pos, const T& v)
{
  if (pos > size_) {
    throw std::out_of_range("position out of range");
  }
  size_t newCap = cap_ * 1.5 + 1;
  if (size_ + 1 < cap_) {
    newCap = cap_;
  }
  T* newData = new T[newCap];
  try {
    size_t i = 0;
    for (; i < pos; ++i) {
      newData[i] = data_[i];
    }
    newData[pos] = v;
    for (; i < size_; ++i) {
      newData[i + 1] = data_[i];
    }
  } catch (...) {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_++;
  cap_ = newCap;
}

template< class T >
void kuznetsov::Vector< T >::insert(size_t pos, const Vector< T >& v, size_t start, size_t end)
{
  if (pos > size_) {
    throw std::out_of_range("position out of range");
  }
  size_t count = (end - start);
  size_t newCap = cap_ + count;
  if (size_ + count < cap_) {
    newCap = cap_;
  }
  T* newData = new T[newCap];
  try {
    size_t i = 0;
    for (; i < pos; ++i) {
      newData[i] = data_[i];
    }
    size_t j = 0;
    for (;j < count; ++j) {
      newData[i + j] = v.at(start + j);
    }
    for (; i < size_; ++i) {
      newData[i + j] = data_[i];
    }
  } catch (...) {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_ += count;
  cap_ = newCap;
}

template< class T >
void kuznetsov::Vector<T>::clear()
{
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

template< class T >
void kuznetsov::Vector<T>::erase(size_t pos)
{
  T* copy = new T[size_];
  try {
    size_t i = 0;
    for (; i < pos; ++i) {
      copy[i] = data_[i];
    }
    for (; i < size_ - 1; ++i) {
      copy[i] = data_[i + 1];
    }
  } catch (...) {
    delete[] copy;
    throw;
  }
  delete[] data_;
  data_ = copy;
  size_--;
}

template< class T >
void kuznetsov::Vector<T>::erase(size_t start, size_t stop)
{
  T* copy = new T[size_];
  size_t count = stop - start;
  try {
    size_t i = 0;
    for (; i < start; ++i) {
      copy[i] = data_[i];
    }
    for (; i < size_ - count; ++i) {
      copy[i] = data_[i + count];
    }
  } catch (...) {
    delete[] copy;
    throw;
  }
  delete[] data_;
  data_ = copy;
  size_ = size_ - count;
}


// Strong guaratia
// Tests
//erase диапазон

// HOMEWORK
// Iterators random access
// Several insert erase with iterators (3 per method + tests)



#endif


