// src/node.cpp
#include "node.hpp"

Node* create_node(int value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}

bool Node::is_leaf() const {
    return left == nullptr && right == nullptr;
}
