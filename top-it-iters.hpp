#ifndef TOP_IT_ITERS_HPP
#define TOP_IT_ITERS_HPP
#include <cstddef>
namespace kuznetsov {

  template< class T >
  struct CIter {
    explicit CIter(T* ptr):
      ptr_(ptr)
    {}
    const T& operator*();
    CIter& operator++();
    CIter& operator--();
    CIter& operator+=(size_t n);
    CIter& operator-=(size_t n);
    CIter operator+(size_t n);
    CIter operator-(size_t n);
    size_t operator-(const CIter&);
    bool operator==(const CIter&);
    bool operator!=(const CIter&);
    bool operator>(const CIter&);
    bool operator>=(const CIter&);
    bool operator<(const CIter&);
    bool operator<=(const CIter&);
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



#endif

