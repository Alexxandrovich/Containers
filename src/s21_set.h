#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_H_

#include "s21_containers.h"
#include "s21_rbtree.h"
#include "s21_vector.h"

namespace s21 {

template <class T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<T, T>::iterator;
  using const_iterator = typename RBTree<T, T>::const_iterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  set<T> &operator=(set &&s);
  set<T> &operator=(const set<T> &s);
  ~set();

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);

  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key) const;

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  RBTree<key_type, value_type> *tree_;
  size_type size_;
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_H_
