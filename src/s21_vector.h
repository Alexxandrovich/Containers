#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <cmath>

#include "s21_containers.h"

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<T> &v);
  vector(vector<T> &&v);
  vector<T> &operator=(vector<T> &&v);
  vector<T> &operator=(const vector<T> &v);
  ~vector();

  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type new_cap);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  T *arr_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
