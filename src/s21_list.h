#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

#include "s21_containers.h"

namespace s21 {

template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = list<T>::ListIterator;
  using const_iterator = list<T>::ListConstIterator;

  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    Node();
    explicit Node(value_type val);
  };

  class ListIterator {
    friend class list;

   public:
    ListIterator();
    explicit ListIterator(Node *ptr);
    ListIterator(Node *ptr, size_type size_);
    ListIterator(Node *ptr1, Node *ptr2, size_type size_, int flag_end);

    value_type operator*();
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);

   private:
    Node *current_ = nullptr;
    Node *end_ = nullptr;
    size_type size_ = 0;
    int flag_end_ = 0;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other) : ListIterator(other) {}

    const_iterator begin() const;
    const_iterator end() const;
    const value_type operator*();
    const const_iterator &operator++();
  };

  // List Functions
  // В этой таблице перечислены основные публичные методы для взаимодействия с
  // классом:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  value_type operator=(list &&l);
  void copy(const list &l);

  // List Element access
  // В этой таблице перечислены публичные методы для доступа к элементам класса:
  const_reference front();
  const_reference back();

  // List Iterators
  // В этой таблице перечислены публичные методы для итерирования по элементам
  // класса (доступ к итераторам):
  iterator begin();
  iterator end();

  // List Capacity
  // В этой таблице перечислены публичные методы для доступа к информации о
  // наполнении контейнера:

  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  // В этой таблице перечислены публичные методы для изменения контейнера:

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  // bonus

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Node *head_;
  Node *tail_;
  size_type size_;
};

template <typename T>
list<T>::Node::Node() {
  prev = nullptr;
  next = nullptr;
}

template <typename T>
list<T>::Node::Node(value_type val) : Node() {
  data = val;
}

template <typename T>
list<T>::ListIterator::ListIterator() : current_(nullptr), end_(nullptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *ptr) : current_(ptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *ptr, size_type size)
    : current_(ptr), size_(size) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *ptr1, Node *ptr2, size_type size,
                                    int flag_end)
    : current_(ptr1), end_(ptr2), size_(size), flag_end_(flag_end) {}

template <typename T>
typename list<T>::value_type list<T>::iterator::operator*() {
  if (flag_end_ == 1) return (value_type)size_;
  return current_->data;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator++() {
  if (flag_end_ == 1) {
    flag_end_ = 0;
    while (current_->prev != nullptr) current_ = current_->prev;
  }
  if (current_->next == nullptr) flag_end_ = 1;
  current_ = current_->next;
  return *this;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator--() {
  if (flag_end_ == 1) {
    flag_end_ = 0;
    if (end_ != nullptr) current_ = end_;
    return *this;
  }
  if (current_) current_ = current_->prev;
  return *this;
}

template <typename T>
bool list<T>::iterator::operator==(const iterator &other) {
  return this->current_ == other.current_;
}

template <typename T>
bool list<T>::iterator::operator!=(const iterator &other) {
  return this->current_ != other.current_;
}

template <typename T>
const typename list<T>::value_type list<T>::const_iterator::operator*() {
  return iterator::operator*();
}

template <typename T>
const typename list<T>::const_iterator &list<T>::const_iterator::operator++() {
  return iterator::operator++();
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::begin() const {
  return iterator::begin();
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::end() const {
  return iterator::end();
}

template <class T>
list<T>::list() {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}

template <class T>
list<T>::list(size_type n) : list() {
  if (n >= max_size()) throw std::out_of_range("Out of container limit");
  if (n > 0)
    for (size_type i = 0; i < n; ++i) push_back(value_type());
}

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto &item : items) push_back(item);
}

template <class T>
list<T>::list(const list &l) : list() {
  Node *tmp = l.head_;
  for (size_type i = 0; i != l.size_; i++) {
    push_back(tmp->data);
    tmp = tmp->next;
  }
}

template <typename T>
list<T>::list(list &&l) : list() {
  swap(l);
}

template <class T>
list<T>::~list() {
  while (head_ != nullptr) pop_front();
  tail_ = nullptr;
}

template <typename T>
typename list<T>::value_type list<T>::operator=(list &&l) {
  this->swap(l);
  return *this;
}

template <typename T>
void list<T>::swap(list &other) {
  using std::swap;
  swap(this->head_, other.head_);
  swap(this->tail_, other.tail_);
  swap(this->size_, other.size_);
}

template <class T>
void list<T>::push_front(const_reference value) {
  Node *ptr = new Node(value);
  ptr->next = head_;
  if (head_ != nullptr) head_->prev = ptr;
  if (tail_ == nullptr) tail_ = ptr;
  head_ = ptr;
  size_++;
}

template <class T>
void list<T>::push_back(const_reference value) {
  Node *ptr = new Node(value);
  ptr->prev = tail_;
  if (tail_ != nullptr) tail_->next = ptr;
  if (head_ == nullptr) head_ = ptr;
  tail_ = ptr;
  size_++;
}

template <class T>
void list<T>::pop_front() {
  if (head_ == nullptr) return;
  Node *ptr = head_->next;
  if (ptr != nullptr)
    ptr->prev = nullptr;
  else
    tail_ = nullptr;
  delete head_;
  head_ = ptr;
  size_--;
}

template <class T>
void list<T>::pop_back() {
  if (tail_ == nullptr) return;
  Node *ptr = tail_->prev;
  if (ptr != nullptr)
    ptr->next = nullptr;
  else
    head_ = nullptr;
  delete tail_;
  tail_ = ptr;
  size_--;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_, size_);
}

template <class T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr, tail_, size_, 1);
}

template <class T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<T>::max() / sizeof(list) / 2;
}

template <typename T>
bool list<T>::empty() {
  return size_ == (size_type)0;
}

template <class T>
typename list<T>::const_reference list<T>::front() {
  if (head_ == nullptr) throw "Collection is empty";
  return head_->data;
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  if (tail_ == nullptr) throw "Collection is empty";
  return tail_->data;
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *right(pos.current_);
  if (right == nullptr) {
    push_back(value);
    return iterator(this->head_, size_);
  }
  Node *left = right->prev;
  if (left == nullptr) {
    push_front(value);
    return iterator(this->head_, size_);
  }
  Node *ptr = new Node(value);
  ptr->prev = left;
  ptr->next = right;
  left->next = ptr;
  right->prev = ptr;
  size_++;
  return iterator(ptr, size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (!this->empty() && !other.empty()) {
    iterator iter_this = this->begin();
    iterator iter_other = other.begin();
    while (iter_this != this->end()) {
      if (iter_other != other.end()) {
        if (iter_this.current_->data >= iter_other.current_->data) {
          this->insert(iter_this, iter_other.current_->data);
          ++iter_other;
        } else {
          ++iter_this;
        }
      } else {
        break;
      }
    }
    while (iter_other != other.end()) {
      this->insert(iter_this, iter_other.current_->data);
      ++iter_other;
    }
  } else if (this->empty() && !other.empty()) {
    this->copy(other);
  }
  other.clear();
}

template <typename T>
void list<T>::copy(const list &l) {
  Node *current = l.head_;
  for (size_type i = 0; i != l.size_; i++) {
    push_back(current->data);
    current = current->next;
  }
}

template <class T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node *node = head_;
    for (size_type i = 0; i < size_; ++i) {
      std::swap(node->prev, node->next);
      node = node->prev;
    }
    std::swap(head_, tail_);
  }
}

template <class T>
void list<T>::erase(iterator pos) {
  if (pos.current_ == nullptr) return;
  Node *ptr(pos.current_);
  if (ptr->prev == nullptr) {
    pop_front();
    return;
  }
  if (ptr->next == nullptr) {
    pop_back();
    return;
  }
  Node *left = ptr->prev;
  Node *right = ptr->next;
  left->next = right;
  right->prev = left;
  delete ptr;
  size_--;
}

template <class T>
void list<T>::unique() {
  if (!this->empty()) {
    for (iterator it_last = begin(); it_last != end();) {
      iterator it_next = it_last;
      ++it_next;
      if (it_next.current_ == nullptr) {
        return;
      } else if (*it_last == *it_next) {
        erase(it_next);
      } else {
        ++it_last;
      }
    }
  }
}

template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    for (Node *i = tail_->prev; i != head_; i = i->prev) {
      for (Node *j = head_; j != tail_; j = j->next) {
        if (j->data > j->next->data) {
          value_type tmp_val = j->data;
          j->data = j->next->data;
          j->next->data = tmp_val;
        }
      }
    }
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args &&...args) {
  std::initializer_list<value_type> items{args...};
  iterator iter = pos;
  iterator res;
  for (auto val : items) {
    res = insert(iter, val);
  }
  return res;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(begin(), args...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  std::initializer_list<value_type> items{args...};
  for (auto val : items) {
    push_back(val);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

