#ifndef AOC2024_BINARY_TREE_H
#define AOC2024_BINARY_TREE_H

#include <array>
#include <memory>

namespace aoc {

template <typename TNode>
class BinaryTreeNode
    : public std::enable_shared_from_this<BinaryTreeNode<TNode>> {
  public:
    BinaryTreeNode(TNode value,
                   const std::shared_ptr<BinaryTreeNode<TNode>> &parent)
        : value(value), children{{nullptr, nullptr}}, parent{parent} {}

    explicit BinaryTreeNode<TNode>(TNode value)
        : BinaryTreeNode(value, nullptr) {}

    std::shared_ptr<BinaryTreeNode<TNode>> get_first_child() const {
        return this->children[0];
    }

    std::shared_ptr<BinaryTreeNode<TNode>> get_second_child() const {
        return this->children[1];
    }

    std::weak_ptr<BinaryTreeNode<TNode>> get_parent() const {
        return this->parent;
    }

    TNode get_value() const { return this->value; }

    bool add_child(TNode item) {
        std::shared_ptr<BinaryTreeNode<TNode>> new_child =
            std::make_shared<BinaryTreeNode<TNode>>(item,
                                                    this->shared_from_this());

        if (!this->children[0]) {
            this->children[0] = new_child;
            return true;
        } else if (!this->children[1]) {
            this->children[1] = new_child;
            return true;
        }

        return false;
    }

  private:
    TNode value;
    std::array<std::shared_ptr<BinaryTreeNode<TNode>>, 2> children;
    std::weak_ptr<BinaryTreeNode<TNode>> parent;
};

template <typename TNode> class BinaryTree {
  public:
    explicit BinaryTree(TNode root)
        : root(std::make_shared<BinaryTreeNode<TNode>>(root)) {}
    std::shared_ptr<BinaryTreeNode<TNode>> get_root() { return this->root; }

  private:
    std::shared_ptr<BinaryTreeNode<TNode>> root;
};

} // namespace aoc

#endif // AOC2024_BINARY_TREE_H