#include <memory>
#include <iostream>

enum class Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;
    Node<T>* parent;

    explicit Node<T>(const T& data) : data(data), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}

    void insert(const T& value) {
        auto new_node = std::make_unique<Node<T>>(value);
        if (!root) {
            new_node->color = Color::BLACK;
            root = std::move(new_node);
        } else {
            insertNode(root.get(), new_node.get());
        }
    }

    bool search(const T& value) const {
        return searchNode(root.get(), value);
    }

    void remove(const T& value) {
        Node<T>* node = findNode(root.get(), value);
        if (node) {
            deleteNode(node);
        }
    }

private:
    std::unique_ptr<Node<T>> root;

    void insertNode(Node<T>* current, Node<T>* new_node) {
        if (new_node->data < current->data) {
            if (current->left) {
                insertNode(current->left.get(), new_node);
                return;
            }
            current->left = std::move(new_node);
            new_node = current->left.get();
        } else {
            if (current->right) {
                insertNode(current->right.get(), new_node);
                return;
            }
            current->right = std::move(new_node);
            new_node = current->right.get();
        }

        new_node->parent = current;
        fixTreeAfterInsertion(new_node);
    }
    bool searchNode(const Node<T>* current, const T& value) const {
        if (!current) {
            return false;
        }
        if (value == current->data) {
            return true;
        }
        if (value < current->data) {
            return searchNode(current->left.get(), value);
        }
        return searchNode(current->right.get(), value);
    }

    Node<T>* findNode(Node<T>* current, const T& value) const {
        if (!current || value == current->data) {
            return current;
        }
        if (value < current->data) {
            return findNode(current->left.get(), value);
        }
        return findNode(current->right.get(), value);
    }

    void deleteNode(Node<T>* node) {
        if (!node->left && !node->right) {
            // Узел без потомков
            if (node->parent) {
                if (node->parent->left.get() == node) {
                    node->parent->left.reset();
                } else if (node->parent->right.get() == node) {
                    node->parent->right.reset();
                }
            } else {
                root.reset();
            }
        } else if (node->left && node->right) {
            // Узел с двумя потомками
            Node<T>* successor = findSuccessor(node);
            node->data = successor->data;
            deleteNode(successor);
        } else {
            // Узел с одним потомком
            Node<T>* child = node->left ? node->left.get() : node->right.get();
            replaceNode(node, child);
            if (node->color == Color::BLACK) {
                if (child && child->color == Color::RED) {
                    child->color = Color::BLACK;
                } else {
                    fixTreeAfterDeletion(child, node->parent);
                }
            }
        }
    }

    Node<T>* findSuccessor(Node<T>* node) const {
        if (node->right) {
            node = node->right.get();
            while (node->left) {
                node = node->left.get();
            }
        } else {
            while (node->parent && node->parent->right.get() == node) {
                node = node->parent;
            }
            node = node->parent;
        }
        return node;
    }

    void replaceNode(Node<T>* oldNode, Node<T>* newNode) {
        if (oldNode->parent) {
            if (oldNode->parent->left.get() == oldNode) {
                oldNode->parent->left.reset(newNode);
            } else {
                oldNode->parent->right.reset(newNode);
            }
        } else {
            root.reset(newNode);
        }
        if (newNode) {
            newNode->parent = oldNode->parent;
        }
    }

    void fixTreeAfterDeletion(Node<T>* node, Node<T>* parent) {
        while (node != root.get() && (!node || node->color == Color::BLACK)) {
            if (node == parent->left.get()) {
                Node<T>* sibling = parent->right.get();
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotateLeft(parent);
                    sibling = parent->right.get();
                }
                if ((!sibling->left || sibling->left->color == Color::BLACK) &&
                    (!sibling->right || sibling->right->color == Color::BLACK)) {
                    sibling->color = Color::RED;
                    node = parent;
                    parent = node ? node->parent : nullptr;
                } else {
                    if (!sibling->right || sibling->right->color == Color::BLACK) {
                        sibling->left->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotateRight(sibling);
                        sibling = parent->right.get();
                    }
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                    sibling->right->color = Color::BLACK;
                    rotateLeft(parent);
                    node = root.get();
                }
            } else {
                Node<T>* sibling = parent->left.get();
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotateRight(parent);
                    sibling = parent->left.get();
                }
                if ((!sibling->left || sibling->left->color == Color::BLACK) &&
                    (!sibling->right || sibling->right->color == Color::BLACK)) {
                    sibling->color = Color::RED;
                    node = parent;
                    parent = node ? node->parent : nullptr;
                } else {
                    if (!sibling->left || sibling->left->color == Color::BLACK) {
                        sibling->right->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotateLeft(sibling);
                        sibling = parent->left.get();
                    }
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                    sibling->left->color = Color::BLACK;
                    rotateRight(parent);
                    node = root.get();
                }
            }
        }
        if (node) {
            node->color = Color::BLACK;
        }
    }

    void fixTreeAfterInsertion(Node<T>* node) {
        while (node->parent && node->parent->color == Color::RED) {
            if (node->parent == node->parent->parent->left.get()) {
                auto uncle = node->parent->parent->right.get();
                if (uncle && uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right.get()) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                auto uncle = node->parent->parent->left.get();
                if (uncle && uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left.get()) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    void rotateLeft(Node<T>* node) {
        Node<T>* right_child = node->right.get();
        node->right = std::move(right_child->left);
        if (right_child->left) {
            right_child->left->parent = node;
        }
        right_child->parent = node->parent;
        if (!node->parent) {
            root.reset(right_child);
        } else if (node == node->parent->left.get()) {
            node->parent->left.reset(right_child);
        } else {
            node->parent->right.reset(right_child);
        }
        right_child->left.reset(node);
        node->parent = right_child;
    }

    void rotateRight(Node<T>* node) {
        Node<T>* left_child = node->left.get();
        node->left = std::move(left_child->right);
        if (left_child->right) {
            left_child->right->parent = node;
        }
        left_child->parent = node->parent;
        if (!node->parent) {
            root.reset(left_child);
        } else if (node == node->parent->right.get()) {
            node->parent->right.reset(left_child);
        } else {
            node->parent->left.reset(left_child);
        }
        left_child->right.reset(node);
        node->parent = left_child;
    }
};

int main() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    return 0;
}
