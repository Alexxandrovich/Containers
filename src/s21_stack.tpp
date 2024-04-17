#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_TPP_

namespace s21 {

template <class T>
stack<T>::stack() : data_() {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : data_(items) {}

template <class T>
stack<T>::stack(const stack<T> &v) : data_(v.data_) {}

template <class T>
stack<T>::stack(stack<T> &&v) : data_(std::move(v.data_)) {}

template <class T>
stack<T>::~stack() {}

template <class T>
stack<T> &stack<T>::operator=(stack<T> &&s) {
  data_ = std::move(s.data_);
  return *this;
}

template <class T>
stack<T> &stack<T>::operator=(const stack<T> &s) {
  data_ = s.data_;
  return *this;
}

template <class T>
typename stack<T>::const_reference stack<T>::top() const {
  return data_.back();
}

template <class T>
bool stack<T>::empty() const {
  return data_.empty();
}

template <class T>
typename stack<T>::size_type stack<T>::size() const {
  return data_.size();
}

template <class T>
void stack<T>::push(const_reference value) {
  data_.push_back(value);
}

template <class T>
void stack<T>::pop() {
  data_.pop_back();
}

template <class T>
void stack<T>::swap(stack<T> &other) {
  data_.swap(other.data_);
}

template <class T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  for (auto p : {args...}) {
    push(p);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_TPP_

