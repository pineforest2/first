#include <iostream>
#include <memory>
#include <optional>
#include <cassert>

namespace pineforest {

template <typename T>
class BST {
private:
	class Node {
	public:
		int key_;
		T value_;
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		Node(int key, T value):
			key_(key), value_(value),
			left_(nullptr), right_(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		Node(Node&&) = delete;
		Node& operator=(Node&&) = delete;
	};
	std::shared_ptr<Node> root_;
	size_t size_;

	void debugHelper(Node& subtree) {
		if (subtree.left_ != nullptr) debugHelper(*(subtree.left_));
		std::cout << subtree.key_ << ' ';
		if (subtree.right_ != nullptr) debugHelper(*(subtree.right_));
	}
public:
	BST(): root_(nullptr), size_(0) {}
	BST(const BST&) = delete;
	BST& operator=(const BST&) = delete;
	BST(BST&&) = delete;
	BST& operator=(BST&&) = delete;
	int insert(int key, T value) {
		if (root_ == nullptr) {
			root_ = std::make_shared<Node>(key, value);
			size_++;
			return 1;
		}
		std::shared_ptr<Node> ptr1 = nullptr;
		std::shared_ptr<Node> ptr2 = root_;
		while (ptr2 != nullptr) {
			if (ptr2->key_ == key) { // covering old value
				ptr2->value_ = value;
				return 0;
			}
			ptr1 = ptr2;
			if (ptr2->key_ > key) {
				ptr2 = ptr2->left_;
			} else {
				ptr2 = ptr2->right_;
			}
		}
		std::shared_ptr<Node> newnode = std::make_shared<Node>(key, value);
		if (ptr1->key_ > key) {
			ptr1->left_ = newnode;
		} else {
			ptr1->right_ = newnode;
		}
		size_++;
		return 1;
	}
	int remove(int key) {
		if (root_ == nullptr) {
			return 0;
		}
		std::shared_ptr<Node> ptr1 = nullptr;
		std::shared_ptr<Node> ptr2 = root_;
		int flag12 = 0;
		while (ptr2 != nullptr) {
			if (ptr2->key_ == key) {
				break;
			}
			ptr1 = ptr2;
			if (ptr1->key_ > key) {
				flag12 = 1; /* 1 is left */
				ptr2 = ptr1->left_;
			} else {
				flag12 = 2; /* 2 is right */
				ptr2 = ptr1->right_;
			}
		}
		if (ptr2 == nullptr) {
			return 0;
		}
		assert((ptr1 == nullptr) ||
		       ((ptr1 != nullptr) &&
		        ((ptr1->left_ == ptr2 && flag12 == 1) ||
		         (ptr1->right_ == ptr2 && flag12 == 2))));
		if (ptr2->left_ == nullptr || ptr2->right_ == nullptr) {
			/* 被删结点的左右儿子只有一个或者没有 */
			ptr2 = (ptr2->left_ != nullptr) ? (ptr2->left_) : (ptr2->right_);
			if (ptr1 == nullptr) {
				assert(root_->key_ != key);
				root_ = ptr2;
				size_--;
				return 1;
			} else {
				if (flag12 == 1) {
					ptr1->left_ = ptr2;
				} else if (flag12 == 2) {
					ptr1->right_ = ptr2;
				} else {
					assert(false);
				}
				size_--;
				return 1;
			}
		} else {
			/* 被删结点的左右儿子都有  */
			std::shared_ptr<Node> ptr = ptr2;
			ptr1 = ptr2;
			flag12 = 2;
			ptr2 = ptr2->right_;
			while (ptr2->left_ != nullptr) {
				ptr1 = ptr2;
				flag12 = 1;
				ptr2 = ptr1->left_;
			}
			if (flag12 == 1) {
				ptr1->left_ = ptr2->right_;
			} else if (flag12 == 2) {
				ptr1->right_ = ptr2->right_;
			} else {
				assert(false);
			}
			ptr->key_ = ptr2->key_;
			ptr->value_ = ptr2->value_;
			size_--;
			return 1;
		}
	}
	std::optional<T> search(int key) {
		std::shared_ptr<Node> ptr = root_;
		while (ptr != nullptr) {
			if (ptr->key_ > key) {
				ptr = ptr->left_;
			} else if (ptr->key_ < key) {
				ptr = ptr->right_;
			} else {
				return ptr->value_;
			}
		}
		return std::nullopt;
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
	pineforest::BST<std::string_view> bst;
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
	bst.remove(20); // bug
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