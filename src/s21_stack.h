#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_H_

#include "s21_containers.h"
#include "s21_vector.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack<T> &v);
  stack(stack<T> &&v);
  stack<T> &operator=(stack<T> &&s);
  stack<T> &operator=(const stack<T> &s);
  ~stack();

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack<T> &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  vector<T> data_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_H_

