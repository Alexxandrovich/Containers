#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_TPP_

namespace s21 {

template <class T>
set<T>::set() : size_(0) {
  tree_ = new RBTree<T, T>();
}

template <class T>
set<T>::set(std::initializer_list<value_type> const &items) : size_(0) {
  tree_ = new RBTree<T, T>();
  for (auto it = items.begin(); it != items.end(); ++it) {
    auto p = insert(*it);
  }
}

template <class T>
set<T>::set(const set &s) : size_(0) {
  tree_ = new RBTree<T, T>();
  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    auto p = insert(*it);
  }
}

template <class T>
set<T>::set(set &&s) {
  tree_ = s.tree_;
  size_ = s.size_;

  s.tree_ = nullptr;
  s.size_ = 0;
}

template <class T>
set<T>::~set() {
  delete tree_;
}

template <class T>
set<T> &set<T>::operator=(set &&s) {
  tree_->DeleteTree();

  tree_ = s.tree_;
  size_ = s.size_;

  s.tree_ = nullptr;
  s.size_ = 0;

  return *this;
}

template <class T>
set<T> &set<T>::operator=(const set<T> &s) {
  tree_->delete_tree();
  size_ = 0;

  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    insert(*it);
  }

  return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() {
  if (tree_ == nullptr) {
    return tree_->end();
  }
  return tree_->begin();
}

template <class T>
typename set<T>::iterator set<T>::end() {
  return tree_->end();
}

template <class T>
typename set<T>::const_iterator set<T>::cbegin() const {
  if (tree_ == nullptr) {
    return tree_->cend();
  }
  return tree_->cbegin();
}

template <class T>
typename set<T>::const_iterator set<T>::cend() const {
  return tree_->cend();
}

template <class T>
bool set<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename set<T>::size_type set<T>::size() const {
  return size_;
}

template <class T>
typename set<T>::size_type set<T>::max_size() const {
  return std::numeric_limits<std::ptrdiff_t>::max() / tree_->SizeOfNode();
}

template <class T>
void set<T>::clear() {
  delete tree_;
  tree_ = nullptr;
  size_ = 0;
}

template <class T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  if (tree_ == nullptr) {
    tree_ = new RBTree<T, T>();
  }
  std::pair<iterator, bool> res;
  if (tree_->Find(value)) {
    res.first = nullptr;
    res.second = false;
  } else {
    tree_->Insert(value, value);
    ++size_;
    res.first = find(value);
    res.second = true;
  }

  return res;
}

template <class T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  iterator it = this->begin();
  for (; it != this->end(); ++it) {
    if (*it == key) {
      break;
    }
  }

  return it;
}

template <class T>
bool set<T>::contains(const key_type &key) const {
  return tree_->Find(key);
}

template <class T>
void set<T>::erase(iterator pos) {
  if (pos != this->end()) {
    tree_->DeleteNode(*pos);
    --size_;
  }
}

template <class T>
void set<T>::swap(set &other) {
  RBTree<T, T> *temp = tree_;
  size_type s = size_;

  tree_ = other.tree_;
  size_ = other.size_;

  other.tree_ = temp;
  other.size_ = s;
}

template <class T>
void set<T>::merge(set &other) {
  s21::vector<T> v;
  for (auto it = other.begin(); it != other.end(); ++it) {
    auto p = insert(*it);
    if (p.second == true) {
      v.push_back(*it);
    }
  }

  for (size_type i = 0; i < v.size(); ++i) {
    other.erase(find(v[i]));
  }
}

template <class T>
template <typename... Args>
vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  vector<std::pair<s21::set<T>::iterator, bool>> res;

  for (auto p : {args...}) {
    res.push_back(insert(p));
  }

  return res;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_TPP_
