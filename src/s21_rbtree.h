#ifndef CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_

#include <iostream>
#include <string>

#include "s21_stack.h"

namespace s21 {

template <class K, class T>
class RBTree {
 public:
  using size_type = size_t;

  class iterator;
  class const_iterator;

  RBTree();
  ~RBTree();
  void Insert(K key, T data);
  bool Find(K key);
  void DeleteNode(K key);
  void PrintRBTree();
  void DeleteTree();

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  size_type SizeOfNode();

 private:
  class Node {
   public:
    Node();
    Node(K key, T value);
    ~Node();

    Node *parent, *left, *right;
    K key;
    T value;
    enum { RED, BLACK } color;
  };

  Node *Grandparent(Node *n);
  Node *Uncle(Node *n);
  Node *Sibling(Node *n);
  void RotateLeft(Node *n);
  void RotateRight(Node *n);

  void InsertCase1(Node *n);
  void InsertCase2(Node *n);
  void InsertCase3(Node *n);
  void InsertCase4(Node *n);
  void InsertCase5(Node *n);
  void PrintRBTree(const std::string &prefix, const Node *node, bool isLeft);

  void ReplaceNode(Node *n, Node *child);
  void DeleteOneNode(Node *n);
  bool IsLeaf(Node *n);

  void DeleteCase1(Node *n);
  void DeleteCase2(Node *n);
  void DeleteCase3(Node *n);
  void DeleteCase4(Node *n);
  void DeleteCase5(Node *n);
  void DeleteCase6(Node *n);
  void DeleteTree(Node *curr);

  Node *root_;
};

template <class K, class T>
class RBTree<K, T>::iterator {
 public:
  iterator();
  iterator(Node *root);
  K operator*();
  iterator &operator++();
  iterator &operator--();
  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;

 private:
  void Inorder(Node *root);
  stack<Node *> data_;
  Node *prev_top_;
};

template <class K, class T>
class RBTree<K, T>::const_iterator {
 public:
  const_iterator();
  const_iterator(Node *root);
  K operator*() const;
  const_iterator &operator++();
  const_iterator &operator--();
  bool operator==(const const_iterator &other) const;
  bool operator!=(const const_iterator &other) const;

 private:
  void Inorder(Node *root);
  stack<Node *> data_;
  Node *prev_top_;
};

}  // namespace s21

#include "s21_rbtree.tpp"
#include "s21_rbtree_const_iterator.tpp"
#include "s21_rbtree_iterator.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_RBTREE_H_
