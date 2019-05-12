#include <iostream>
#include <unordered_set>

template <typename T>
class BinaryTree {
private:
    template <typename N>
    struct Node {
        N value;
        Node *left;
        Node *right;
        Node *parent;

        Node(N value, Node *parent) {
            this->value = value;
            parent = parent;
            left = nullptr;
            right = nullptr;
        }
    };

    Node<T> *root;

    void add(T val, Node<T> *node) {
        if (val < node->value) {
            if (node->left != nullptr) {
                add(val, node->left);
            } else {
                node->left = new Node<T>(val, node);
            }
        } else if (val >= node->value) {
            if (node->right != nullptr) {
                add(val, node->right);
            } else {
                node->right = new Node<T>(val, node);
            }
        }
    }

    void print(Node<T> *node, int space, std::ostream &os) const {
        int count = 10;

        if (node == nullptr)
            return;

        space += count;

        print(node->right, space, os);

        os << std::endl;
        for (int i = count; i < space; i++)
            os << " ";
        os << node->value << std::endl;

        print(node->left, space, os);
    }

public:
    BinaryTree(T root_value) : root{new Node<T>(root_value, nullptr)} {}

    void add(T val) {
        add(val, root);
    }

    friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree) {
        tree.print(tree.root, 0, os);
        return os;
    }

    friend bool check_bin_tree_duplicates(const Node<T> *node, std::unordered_set<T> &s) {
        if (node == nullptr) {
            return false;
        }

        if (s.find(node->value) != s.end()) {
            return true;
        }

        s.insert(node->value);

        return (
            check_bin_tree_duplicates(node->left, s) || check_bin_tree_duplicates(node->right, s));
    }

    friend bool check_bin_tree_duplicates(const BinaryTree<T> &tree) {
        std::unordered_set<T> s;
        return check_bin_tree_duplicates(tree.root, s);
    }
};

int main() {
    BinaryTree<int> tree{1};
    tree.add(1);
    tree.add(2);
    tree.add(-1);
    tree.add(1);

    std::cout << tree << std::endl;
    std::cout << "duplicates: " << check_bin_tree_duplicates(tree) << std::endl;

    return 0;
}
