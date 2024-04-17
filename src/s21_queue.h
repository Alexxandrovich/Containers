#ifndef CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_

#include "s21_containers.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  queue &operator=(queue &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  s21::list<value_type> list;
};

template <typename T>
queue<T>::queue() : list() {}

template <typename T>
queue<T>::queue(const std::initializer_list<value_type> &items) : list(items) {}

template <typename T>
queue<T>::queue(queue<T> &&q) {
  list.swap(q.list);
  q.list.clear();
}

template <typename T>
queue<T>::queue(const queue<T> &q) : list(q.list) {}

template <typename T>
queue<T>::~queue() {
  list.clear();
}

template <typename T>
queue<T> &queue<T>::operator=(queue<T> &&q) {
  list.swap(q.list);
  q.list.clear();
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  return list.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  return list.back();
}

template <typename T>
bool queue<T>::empty() {
  return list.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return list.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  list.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  if (!empty()) {
    list.pop_front();
  } else {
    throw std::out_of_range("Empty queue!");
  }
}

template <typename T>
void queue<T>::swap(queue<T> &other) {
  list.swap(other.list);
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  list.insert_many_back(args...);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
