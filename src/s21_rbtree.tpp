#ifndef CPP2_S21_CONTAINERS_SRC_S21_RBTREE_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_RBTREE_TPP_

namespace s21 {

template <class K, class T>
RBTree<K, T>::Node::Node() {
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = Node::BLACK;
}

template <class K, class T>
RBTree<K, T>::Node::Node(K key, T value) {
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = Node::RED;
  this->key = key;
  this->value = value;
}

template <class K, class T>
RBTree<K, T>::Node::~Node() {}

template <class K, class T>
typename RBTree<K, T>::Node *RBTree<K, T>::Grandparent(Node *n) {
  if (n == nullptr || n->parent == nullptr) return nullptr;
  return n->parent->parent;
}

template <class K, class T>
typename RBTree<K, T>::Node *RBTree<K, T>::Uncle(Node *n) {
  Node *g = Grandparent(n);
  Node *u;
  if (g == nullptr) {
    return nullptr;
  }

  if (n->parent == g->left) {
    u = g->right;
  } else {
    u = g->left;
  }

  return u;
}

template <class K, class T>
RBTree<K, T>::RBTree() : root_(nullptr) {}

template <class K, class T>
RBTree<K, T>::~RBTree() {
  DeleteTree(root_);
}

template <class K, class T>
typename RBTree<K, T>::iterator RBTree<K, T>::begin() {
  iterator it(root_);
  return it;
}

template <class K, class T>
typename RBTree<K, T>::iterator RBTree<K, T>::end() {
  iterator it(nullptr);
  return it;
}

template <class K, class T>
typename RBTree<K, T>::const_iterator RBTree<K, T>::cbegin() const {
  const_iterator it(root_);
  return it;
}

template <class K, class T>
typename RBTree<K, T>::const_iterator RBTree<K, T>::cend() const {
  const_iterator it(nullptr);
  return it;
}

template <class K, class T>
void RBTree<K, T>::RotateLeft(Node *n) {
  Node *pivot = n->right;
  pivot->parent = n->parent;

  if (pivot->parent == nullptr) {
    root_ = pivot;
  }

  if (n->parent != nullptr) {
    if (n->parent->left == n) {
      n->parent->left = pivot;
    } else {
      n->parent->right = pivot;
    }
  }

  n->right = pivot->left;

  if (pivot->left != nullptr) {
    pivot->left->parent = n;
  }

  n->parent = pivot;
  pivot->left = n;
}

template <class K, class T>
void RBTree<K, T>::RotateRight(Node *n) {
  Node *pivot = n->left;
  pivot->parent = n->parent;

  if (pivot->parent == nullptr) {
    root_ = pivot;
  }

  if (n->parent != nullptr) {
    if (n->parent->left == n) {
      n->parent->left = pivot;
    } else {
      n->parent->right = pivot;
    }
  }

  n->left = pivot->right;

  if (pivot->right != nullptr) {
    pivot->right->parent = n;
  }

  n->parent = pivot;
  pivot->right = n;
}

template <class K, class T>
void RBTree<K, T>::InsertCase1(Node *n) {
  if (n->parent == nullptr) {
    n->color = Node::BLACK;
    n->left->parent = n;
    n->right->parent = n;
  } else {
    InsertCase2(n);
  }
}

template <class K, class T>
void RBTree<K, T>::InsertCase2(Node *n) {
  if (n->parent->color == Node::BLACK) {
    return;
  }

  InsertCase3(n);
}

template <class K, class T>
void RBTree<K, T>::InsertCase3(Node *n) {
  Node *u = Uncle(n);
  Node *g;

  if (u != nullptr && u->color == Node::RED) {
    n->parent->color = Node::BLACK;
    u->color = Node::BLACK;
    g = Grandparent(n);
    g->color = Node::RED;
    InsertCase1(g);
  } else {
    InsertCase4(n);
  }
}

template <class K, class T>
void RBTree<K, T>::InsertCase4(Node *n) {
  Node *g = Grandparent(n);

  if (n == n->parent->right && n->parent == g->left) {
    RotateLeft(n->parent);
    n = n->left;
  } else if (n == n->parent->left && n->parent == g->right) {
    RotateRight(n->parent);
    n = n->right;
  }

  InsertCase5(n);
}

template <class K, class T>
void RBTree<K, T>::InsertCase5(Node *n) {
  Node *g = Grandparent(n);

  n->parent->color = Node::BLACK;
  g->color = Node::RED;

  if (n == n->parent->left && n->parent == g->left) {
    RotateRight(g);
  } else {
    RotateLeft(g);
  }
}

template <class K, class T>
void RBTree<K, T>::PrintRBTree(const std::string &prefix, const Node *root_,
                               bool isLeft) {
  if (root_ != nullptr && root_->left != nullptr && root_->right != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    // print the value of the node
    std::cout << root_->key << std::endl;

    // enter the next tree level - left and right branch
    PrintRBTree(prefix + (isLeft ? "│   " : "    "), root_->right, true);
    PrintRBTree(prefix + (isLeft ? "│   " : "    "), root_->left, false);
  }
}

template <class K, class T>
void RBTree<K, T>::PrintRBTree() {
  PrintRBTree("", root_, false);
}

template <class K, class T>
void RBTree<K, T>::Insert(K key, T value) {
  Node *node = nullptr;

  if (root_ == nullptr) {
    node = new Node(key, value);
    node->left = new Node();
    node->right = new Node();
    root_ = node;
    InsertCase1(root_);
  } else {
    Node *temp = root_;
    Node *prev = nullptr;
    while (temp->left != nullptr && temp->right != nullptr) {
      if (temp->key >= key) {
        prev = temp;
        temp = temp->left;
      } else {
        prev = temp;
        temp = temp->right;
      }
    }

    if (prev->key >= key) {
      node = prev->left;
    } else {
      node = prev->right;
    }

    node->parent = prev;
    node->value = value;
    node->key = key;
    node->color = Node::RED;
    node->left = new Node();
    node->left->parent = node;
    node->right = new Node();
    node->right->parent = node;

    InsertCase1(node);
  }
}

template <class K, class T>
typename RBTree<K, T>::Node *RBTree<K, T>::Sibling(Node *n) {
  if (n == n->parent->left) {
    return n->parent->right;
  }

  return n->parent->left;
}

template <class K, class T>
void RBTree<K, T>::ReplaceNode(Node *n, Node *child) {
  child->parent = n->parent;
  if (n == n->parent->left) {
    n->parent->left = child;
  } else {
    n->parent->right = child;
  }
}

template <class K, class T>
bool RBTree<K, T>::IsLeaf(Node *n) {
  return n->left == nullptr && n->right == nullptr;
}

template <class K, class T>
void RBTree<K, T>::DeleteOneNode(Node *n) {
  if (!(n == root_ && IsLeaf(n->right) && IsLeaf(n->left))) {
    Node *child = IsLeaf(n->right) ? n->left : n->right;
    Node *s = Sibling(child);
    if (IsLeaf(s)) {
      delete s;
    }

    ReplaceNode(n, child);
    if (n->color == Node::BLACK) {
      if (child->color == Node::RED) {
        child->color = Node::BLACK;
      } else {
        DeleteCase1(child);
      }
    }

  } else {
    root_ = nullptr;

    if (IsLeaf(n->right)) {
      delete n->right;
    }

    if (IsLeaf(n->left)) {
      delete n->left;
    }
  }

  delete n;
}

template <class K, class T>
void RBTree<K, T>::DeleteCase1(Node *n) {
  if (n->parent != nullptr) {
    DeleteCase2(n);
  }
}

template <class K, class T>
void RBTree<K, T>::DeleteCase2(Node *n) {
  Node *s = Sibling(n);
  if (s->color == Node::RED) {
    n->parent->color = Node::RED;
    s->color = Node::BLACK;
    if (n == n->parent->left) {
      RotateLeft(n->parent);
    } else {
      RotateRight(n->parent);
    }
  }

  DeleteCase3(n);
}

template <class K, class T>
void RBTree<K, T>::DeleteCase3(Node *n) {
  Node *s = Sibling(n);

  if (n->parent->color == Node::BLACK && s->color == Node::BLACK &&
      s->left->color == Node::BLACK && s->right->color == Node::BLACK) {
    s->color = Node::RED;
    DeleteCase1(n->parent);
  } else {
    DeleteCase4(n);
  }
}

template <class K, class T>
void RBTree<K, T>::DeleteCase4(Node *n) {
  Node *s = Sibling(n);

  if (n->parent->color == Node::RED && s->color == Node::BLACK &&
      s->left->color == Node::BLACK && s->right->color == Node::BLACK) {
    s->color = Node::RED;
    n->parent->color = Node::BLACK;
  } else {
    DeleteCase5(n);
  }
}

template <class K, class T>
void RBTree<K, T>::DeleteCase5(Node *n) {
  Node *s = Sibling(n);

  if (s->color == Node::BLACK) {
    if (n == n->parent->left && s->right->color == Node::BLACK &&
        s->left->color == Node::RED) {
      s->color = Node::RED;
      s->left->color = Node::BLACK;
      RotateRight(s);
    } else if (n == n->parent->right && s->left->color == Node::BLACK &&
               s->right->color == Node::RED) {
      s->color = Node::RED;
      s->right->color = Node::BLACK;
      RotateLeft(s);
    }
  }
  DeleteCase6(n);
}

template <class K, class T>
void RBTree<K, T>::DeleteCase6(Node *n) {
  Node *s = Sibling(n);

  s->color = n->parent->color;
  n->parent->color = Node::BLACK;

  if (n == n->parent->left) {
    s->right->color = Node::BLACK;
    RotateLeft(n->parent);
  } else {
    s->left->color = Node::BLACK;
    RotateRight(n->parent);
  }
}

template <class K, class T>
bool RBTree<K, T>::Find(K key) {
  Node *n = root_;
  if (n) {
    while (n->left && n->right && key != n->key) {
      if (key > n->key) {
        n = n->right;
      } else {
        n = n->left;
      }
    }
  }

  return n != nullptr && n->left != nullptr && n->right != nullptr;
}

template <class K, class T>
void RBTree<K, T>::DeleteNode(K key) {
  Node *n = root_;

  while (n->left && key != n->key) {
    if (key > n->key) {
      n = n->right;
    } else {
      n = n->left;
    }
  }

  if (n->left == nullptr) {
    return;
  }

  // Find max in left tree, if n is not leaf
  Node *t = n;
  if (n->left->left) {
    t = t->left;
    while (t->right->right) {
      t = t->right;
    }
  } else if (n->right->right) {
    t = t->right;
    while (t->left->left) {
      t = t->left;
    }
  }

  n->key = t->key;
  DeleteOneNode(t);
}

template <class K, class T>
void RBTree<K, T>::DeleteTree(Node *curr) {
  if (curr) {
    DeleteTree(curr->left);
    DeleteTree(curr->right);
    delete curr;
  }
}

template <class K, class T>
void RBTree<K, T>::DeleteTree() {
  DeleteTree(root_);
}

template <class K, class T>
typename RBTree<K, T>::size_type RBTree<K, T>::SizeOfNode() {
  return sizeof(RBTree<K, T>::Node);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_RBTREE_TPP_
