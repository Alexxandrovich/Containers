#ifndef CPP2_S21_CONTAINERS_SRC_S21_RBTREE_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_RBTREE_ITERATOR_TPP_

namespace s21 {

template <class K, class T>
RBTree<K, T>::iterator::iterator() {}

template <class K, class T>
RBTree<K, T>::iterator::iterator(Node *root) {
  if (root) {
    Inorder(root);
  }
}

template <class K, class T>
void RBTree<K, T>::iterator::Inorder(Node *root) {
  if (root->right == nullptr) {
    return;
  }
  Inorder(root->right);
  data_.push(root);
  Inorder(root->left);
}

template <class K, class T>
K RBTree<K, T>::iterator::operator*() {
  return data_.top()->key;
}

template <class K, class T>
typename RBTree<K, T>::iterator &RBTree<K, T>::iterator::operator++() {
  prev_top_ = data_.top();
  data_.pop();
  return *this;
}

template <class K, class T>
typename RBTree<K, T>::iterator &RBTree<K, T>::iterator::operator--() {
  data_.push(prev_top_);
  return *this;
}

template <class K, class T>
bool RBTree<K, T>::iterator::operator==(const iterator &other) const {
  if (!data_.empty() && !other.data_.empty())
    return data_.top() == other.data_.top();
  else if (data_.empty() && other.data_.empty()) {
    return true;
  }

  return false;
}

template <class K, class T>
bool RBTree<K, T>::iterator::operator!=(const iterator &other) const {
  return !(*this == other);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_RBTREE_ITERATOR_TPP_

