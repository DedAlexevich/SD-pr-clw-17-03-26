#ifndef TOP_IT_ITERS_HPP
#define TOP_IT_ITERS_HPP
#include <cstddef>
namespace kuznetsov {

  template< class T >
  struct CIter {
    explicit CIter(T* ptr):
      ptr_(ptr)
    {}
    const T& operator*() const;
    CIter& operator++();
    CIter& operator--();
    CIter& operator+=(size_t n);
    CIter& operator-=(size_t n);
    CIter operator+(size_t n) const noexcept;
    CIter operator-(size_t n) const noexcept;
    int operator-(const CIter&) const noexcept;
    bool operator==(const CIter&) const noexcept;
    bool operator!=(const CIter&) const noexcept;
    bool operator>(const CIter&) const noexcept;
    bool operator>=(const CIter&) const noexcept;
    bool operator<(const CIter&) const noexcept;
    bool operator<=(const CIter&) const noexcept;
  private:
    T* ptr_;
  };

  template< class T >
  struct Iter {
    explicit Iter(T* ptr):
      ptr_(ptr)
    {}
    T& operator*();
    Iter& operator++();
    Iter& operator--();
    Iter& operator+=(size_t n);
    Iter& operator-=(size_t n);
    Iter operator+(size_t n);
    Iter operator-(size_t n);
    size_t operator-(const Iter&);
    bool operator==(const Iter&);
    bool operator!=(const Iter&);
    bool operator>(const Iter&);
    bool operator>=(const Iter&);
    bool operator<(const Iter&);
    bool operator<=(const Iter&);
  private:
    T* ptr_;
  };
}

template< class T >
const T& kuznetsov::CIter<T>::operator*() const
{
  return *ptr_;
}

template< class T >
kuznetsov::CIter<T>& kuznetsov::CIter<T>::operator++()
{
  ++ptr_;
  return *this;
}

template< class T >
kuznetsov::CIter<T>& kuznetsov::CIter<T>::operator--()
{
  --ptr_;
  return *this;
}

template< class T >
kuznetsov::CIter<T>& kuznetsov::CIter<T>::operator+=(size_t n)
{
  ptr_ += n;
  return *this;
}

template< class T >
kuznetsov::CIter<T>& kuznetsov::CIter<T>::operator-=(size_t n)
{
  ptr_ -= n;
  return *this;
}

template< class T >
kuznetsov::CIter<T> kuznetsov::CIter<T>::operator+(size_t n) const noexcept
{
  return CIter< T >{ptr_ + n};
}

template< class T >
kuznetsov::CIter<T> kuznetsov::CIter<T>::operator-(size_t n) const noexcept
{
  return CIter< T >{ptr_ - n};
}

template< class T >
int kuznetsov::CIter<T>::operator-(const CIter& rhs) const noexcept
{
  return this->ptr_ - rhs.ptr_;
}

template< class T >
bool kuznetsov::CIter<T>::operator==(const CIter& rhs) const noexcept
{
  return this->ptr_ == rhs.ptr_;
}

template< class T >
bool kuznetsov::CIter<T>::operator!=(const CIter& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
bool kuznetsov::CIter<T>::operator>(const CIter& rhs) const noexcept
{
  return this->ptr_ > rhs.ptr_;
}

template< class T >
bool kuznetsov::CIter<T>::operator>=(const CIter& rhs) const noexcept
{
  return this->ptr_ >= rhs.ptr_;
}

template< class T >
bool kuznetsov::CIter<T>::operator<(const CIter& rhs) const noexcept
{
  return this->ptr_ < rhs.ptr_;
}

template< class T >
bool kuznetsov::CIter<T>::operator<=(const CIter& rhs) const noexcept
{
  return this->ptr_ <= rhs.ptr_;
}

#endif

