#include "smartNode.hpp"
#include <algorithm> 

bool SmartNode::is_leaf() const {
    return !left && !right;
}

void SmartNode::insert(int value) {
    if (value < this->value) {
        if (left) {
            left->insert(value);
        } else {
            left = std::make_unique<SmartNode>(SmartNode{value});
        }
    } else {
        if (right) {
            right->insert(value);
        } else {
            right = std::make_unique<SmartNode>(SmartNode{value});
        }
    }
}

size_t SmartNode::height() const {
    size_t left_height = left ? left->height() : 0;
    size_t right_height = right ? right->height() : 0;
    return 1 + std::max(left_height, right_height);
}

int SmartNode::min() const {
    const SmartNode* current = this;
    while (current->left) {
        current = current->left.get();
    }
    return current->value;
}

int SmartNode::max() const {
    const SmartNode* current = this;
    while (current->right) {
        current = current->right.get();
    }
    return current->value;
}


std::unique_ptr<SmartNode> create_smart_node(int value) {
    return std::make_unique<SmartNode>(SmartNode{value});
}


std::unique_ptr<SmartNode>& SmartNode::most_left(std::unique_ptr<SmartNode>& node) {
    if (!node->left) {
        return node;
    }
    return most_left(node->left);
}


bool remove(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) return false;

    if (value < node->value) {
        return remove(node->left, value);
    } else if (value > node->value) {
        return remove(node->right, value);
    } else {
       
        if (node->is_leaf()) {
            node.reset(); 
            return true;
        }
        
        else if (node->left && !node->right) {
            node = std::move(node->left);
            return true;
        }
       
        else if (!node->left && node->right) {
            node = std::move(node->right);
            return true;
        }

        else {
            std::unique_ptr<SmartNode>& leftmost = SmartNode::most_left(node->right);
            node->value = leftmost->value;
            return remove(node->right, leftmost->value);
        }
    }
}
