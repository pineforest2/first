#include <iostream>
#include <memory>
#include <optional>
#include <cassert>

namespace pineforest {

template <typename T>
class BST2 {
private:
  class Node {
  public:
    int key_;
    T value_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;
    Node(int key, T value):
      key_(key), value_(value),
      left_(nullptr), right_(nullptr) {}
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
  };
  std::unique_ptr<Node> root_;
  size_t size_;
  int insertHelper(Node& subtree, int key, T value) {
    if (subtree.key_ > key) {
      if (subtree.left_ == nullptr) {
        subtree.left_ = std::make_unique<Node>(key, value);
        size_++;
        return 1;
      }
      return insertHelper(*(subtree.left_), key, value);
    } else if (subtree.key_ < key) {
      if (subtree.right_ == nullptr) {
        subtree.right_ = std::make_unique<Node>(key, value);
        size_++;
        return 1;
      }
      return insertHelper(*(subtree.right_), key, value);
    } else {
      subtree.value_ = value;
      return 0;
    }
  }
  std::unique_ptr<Node> removeHelper2(Node& subtree) {
    if ((subtree.left_)->left_ == nullptr) {
      std::unique_ptr<Node> ptr = std::move(subtree.left_);
      subtree.left_ = std::move(ptr->right_);
      return std::move(ptr);
    }
    return removeHelper2(*(subtree.left_));
  }
  int removeHelper(Node& subtree, int key, int& retval) {
    if (subtree.key_ > key) {
      if (subtree.left_ == nullptr) {
        retval = 0;
        return 0;
      }
      switch (removeHelper(*(subtree.left_), key, retval)) {
      case 0:
        break;
      case 1:
        subtree.left_ = nullptr;
        break;
      case 2:
        subtree.left_ = std::move((subtree.left_)->left_);
        break;
      case 3:
        subtree.left_ = std::move((subtree.left_)->right_);
        break;
      case 4:
        break;
      default:
        assert(false);
      }
      retval = 1;
      return 0;
    } else if (subtree.key_ < key) {
      if (subtree.right_ == nullptr) {
        retval = 0;
        return 0;
      }
      switch (removeHelper(*(subtree.right_), key, retval)) {
      case 0:
        break;
      case 1:
        subtree.right_ = nullptr;
        break;
      case 2:
        subtree.right_ = std::move((subtree.right_)->left_);
        break;
      case 3:
        subtree.right_ = std::move((subtree.right_)->right_);
        break;
      case 4:
        break;
      default:
        assert(false);
      }
      retval = 1;
      return 0;
    } else {
      if (subtree.left_ == nullptr && subtree.right_ == nullptr) {
        return 1;
      } else if (subtree.left_ != nullptr && subtree.right_ == nullptr) {
        return 2;
      } else if (subtree.left_ == nullptr && subtree.right_ != nullptr) {
        return 3;
      } else {
        std::unique_ptr<Node> ptr = removeHelper2(*(subtree.right_));
        subtree.key_ = ptr->key_;
        subtree.value_ = ptr->value_;
        retval = 1;
        return 4;
      }
    }
  }
  std::optional<T> searchHelper(Node& subtree, int key) {
    if (subtree.key_ > key) {
      if (subtree.left_ == nullptr) { return std::nullopt; }
      return searchHelper(*(subtree.left_), key);
    } else if (subtree.key_ < key) {
      if (subtree.right_ == nullptr) { return std::nullopt; }
      return searchHelper(*(subtree.right_), key);
    } else {
      return subtree.value_;
    }
  }

  void debugHelper(Node& subtree) {
    if (subtree.left_ != nullptr) debugHelper(*(subtree.left_));
    std::cout << subtree.key_ << ' ';
    if (subtree.right_ != nullptr) debugHelper(*(subtree.right_));
  }
public:
  BST2(): root_(nullptr), size_(0) {}
  BST2(const BST2&) = delete;
  BST2& operator=(const BST2&) = delete;
  BST2(BST2&&) = delete;
  BST2& operator=(BST2&&) = delete;
  int insert(int key, T value) {
    if (root_ == nullptr) {
      root_ = std::make_unique<Node>(key, value);
      size_++;
      return 1;
    }
    return insertHelper(*(root_), key, value);
  }
  int remove(int key) {
    if (root_ == nullptr) { return 0; }
    int retval{0};
    removeHelper(*(root_), key, retval);
    size_ -= retval;
    return retval;
  }
  std::optional<T> search(int key) {
    if (root_ == nullptr) { return std::nullopt; }
    return searchHelper(*(root_), key);
  }
  bool empty() { return size_ == 0; }
  size_t size() { return size_; }

  void debug() {
    std::cout << size_ << ": { ";
    if (root_ == nullptr) return;
    else debugHelper(*root_);
    std::cout << '}' << std::endl;
  }
};

} /* namespace pineforest */

int main() {
  pineforest::BST2<std::string_view> bst;
  bst.insert(9, "9");
  bst.insert(7, "7");
  bst.insert(6, "6");
  bst.insert(5, "5");
  bst.insert(3, "3");
  bst.insert(8, "8");
  bst.insert(20, "20");
  bst.insert(26, "26");
  bst.insert(15, "15");
  bst.insert(12, "12");
  bst.insert(13, "13");
  bst.insert(23, "23");
  bst.insert(25, "25");
  bst.debug();
  bst.remove(5);
  bst.debug();
  bst.remove(20);
  bst.debug();
  bst.remove(12);
  bst.debug();
  bst.remove(9);
  bst.debug();
  bst.remove(3);
  bst.debug();
  std::cout << bst.search(7).value() << std::endl;
  std::cout << bst.search(13).value() << std::endl;
  std::cout << bst.search(25).value() << std::endl;
  std::cout << bst.search(3).has_value() << std::endl;
  std::cout << bst.search(9).has_value() << std::endl;
}