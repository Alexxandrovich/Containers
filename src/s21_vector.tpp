#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_TPP_

namespace s21 {

template <class T>
vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <class T>
vector<T>::vector(size_type n) {
  if (n > max_size()) {
    throw std::length_error("Size is greater than max_size!");
  }

  arr_ = new T[n]{0};
  size_ = n;
  capacity_ = n;
}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  size_ = items.size();
  capacity_ = size_;
  arr_ = new T[size_];

  int i = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++i) {
    arr_[i] = *it;
  }
}

template <class T>
vector<T>::vector(const vector<T> &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;

  arr_ = new T[capacity_];
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <class T>
vector<T>::vector(vector<T> &&v)
    : arr_(v.arr_), size_(v.size_), capacity_(v.capacity_) {
  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <class T>
vector<T>::~vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] arr_;
}

template <class T>
vector<T> &vector<T>::operator=(vector<T> &&v) {
  delete[] arr_;
  arr_ = v.arr_;
  size_ = v.size_;
  capacity_ = v.capacity_;

  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;

  return *this;
}

template <class T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
  delete[] arr_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = new T[capacity_];

  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }

  return *this;
}

template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index is out range!");

  return arr_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) const {
  return arr_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty!");
  }
  return arr_[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty!");
  }
  return arr_[size_ - 1];
}

template <class T>
T *vector<T>::data() {
  return arr_;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <class T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<std::ptrdiff_t>::max() / sizeof(T);
}

template <class T>
void vector<T>::reserve(size_type new_cap) {
  if (capacity_ > new_cap) return;

  if (new_cap > max_size()) throw std::length_error("Too much new capacity!");

  T *arr = new T[new_cap];
  std::copy(this->begin(), this->end(), arr);
  delete[] arr_;

  arr_ = arr;
  capacity_ = new_cap;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <class T>
void vector<T>::shrink_to_fit() {
  capacity_ = size_;
  T *arr = new T[size_];
  std::copy(this->begin(), this->end(), arr);

  delete[] arr_;
  arr_ = arr;
}

template <class T>
void vector<T>::clear() {
  size_ = 0;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (size_ + 1 > capacity_) {
    if (capacity_) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }
  }

  if (size_ == 0 && pos != begin())
    throw std::out_of_range("Position is out of range !");

  T *arr = new T[capacity_];
  size_ = size_ + 1;
  int j = 0, i = 0;
  int index = 0;
  for (auto it = this->begin(); it != this->end(); ++it) {
    if (it == pos) {
      index = i;
      arr[i++] = value;
    } else {
      arr[i++] = arr_[j++];
    }
  }

  delete[] arr_;
  arr_ = arr;

  pos = begin() + index;

  return pos;
}

template <class T>
void vector<T>::erase(iterator pos) {
  T *arr = new T[capacity_]{0};
  int j = 0, i = 0;

  if (pos < this->begin()) pos = this->begin();

  for (auto it = this->begin(); it != this->end(); ++it, ++i) {
    if (it != pos) {
      arr[j++] = arr_[i];
    }
  }

  size_ = size_ - 1;

  delete[] arr_;
  arr_ = arr;
}

template <class T>
void vector<T>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) {
    if (capacity_) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }

    T *arr = new T[capacity_];
    std::copy(this->begin(), this->end(), arr);
    arr[size_] = value;

    delete[] arr_;
    arr_ = arr;
    size_ += 1;
  } else {
    arr_[size_] = value;
    size_ += 1;
  }
}

template <class T>
void vector<T>::pop_back() {
  if (size_) {
    size_ -= 1;
  }
}

template <class T>
void vector<T>::swap(vector<T> &other) {
  T *arr = arr_;
  arr_ = other.arr_;
  other.arr_ = arr;

  size_type s = size_;
  size_ = other.size_;
  other.size_ = s;

  size_type c = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = c;
}

template <class T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(iterator pos,
                                                    Args &&...args) {
  iterator result = pos;
  int index = pos - begin();

  for (auto p : {args...}) {
    result = insert(result, p);
    ++result;
  }

  return begin() + index;
}

template <class T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (auto p : {args...}) {
    push_back(p);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_TPP_
