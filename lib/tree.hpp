#ifndef AOC2024_TREE_H
#define AOC2024_TREE_H

#include <cassert>
#include <memory>
#include <vector>

namespace aoc {

template <typename TNode>
class TreeNode : public std::enable_shared_from_this<TreeNode<TNode>> {
  public:
    TreeNode(TNode value, const std::shared_ptr<TreeNode<TNode>> &parent)
        : value(value),
          children(std::vector<std::shared_ptr<TreeNode<TNode>>>()),
          parent{parent} {}

    explicit TreeNode<TNode>(TNode value) : TreeNode(value, nullptr) {}

    std::shared_ptr<TreeNode<TNode>> get_child(int index) const {
        assert(index >= 0 && index < static_cast<int>(this->children.size()) &&
               "get_child: bounds check failure");

        return this->children[index];
    }

    std::weak_ptr<TreeNode<TNode>> get_parent() const { return this->parent; }

    TNode get_value() const { return this->value; }

    void add_child(TNode item) {
        this->children.push_back(
            std::make_shared<TreeNode<TNode>>(item, this->shared_from_this()));
    }

  private:
    TNode value;
    std::vector<std::shared_ptr<TreeNode<TNode>>> children;
    std::weak_ptr<TreeNode<TNode>> parent;
};

template <typename TNode> class Tree {
  public:
    explicit Tree(TNode root) : root(std::make_shared<TreeNode<TNode>>(root)) {}
    std::shared_ptr<TreeNode<TNode>> get_root() { return this->root; }

  private:
    std::shared_ptr<TreeNode<TNode>> root;
};

} // namespace aoc

#endif // AOC2024_TREE_H