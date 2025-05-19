#include "node.hpp"
#include <iostream>
#include <algorithm>

// Création d'un nœud
Node* create_node(int value) {
    return new Node{value};
}


bool Node::is_leaf() const {
    return left == nullptr && right == nullptr;
}

// Insertion dans l'arbre
void Node::insert(int v) {
    if (v < value) {
        if (left) left->insert(v);
        else left = create_node(v);
    } else {
        if (right) right->insert(v);
        else right = create_node(v);
    }
}

// Hauteur de l'arbre
int Node::height() const {
    if (is_leaf()) return 1;
    int left_h = left ? left->height() : 0;
    int right_h = right ? right->height() : 0;
    return 1 + std::max(left_h, right_h);
}

// Supprimer récursivement les fils
void Node::delete_children() {
    if (left) {
        left->delete_children();
        delete left;
        left = nullptr;
    }
    if (right) {
        right->delete_children();
        delete right;
        right = nullptr;
    }
}

// Affichage infixe
void Node::display_infix() const {
    if (left) left->display_infix();
    std::cout << value << " ";
    if (right) right->display_infix();
}

// Parcours préfixe
std::vector<Node const*> Node::prefix() const {
    std::vector<Node const*> nodes {this};
    if (left) {
        auto left_nodes = left->prefix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    if (right) {
        auto right_nodes = right->prefix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    return nodes;
}

// Parcours postfixe
std::vector<Node const*> Node::postfix() const {
    std::vector<Node const*> nodes;
    if (left) {
        auto left_nodes = left->postfix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    if (right) {
        auto right_nodes = right->postfix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    nodes.push_back(this);
    return nodes;
}

// Valeur minimale
int Node::min() const {
    const Node* current = this;
    while (current->left) current = current->left;
    return current->value;
}

// Valeur maximale
int Node::max() const {
    const Node* current = this;
    while (current->right) current = current->right;
    return current->value;
}

// Le neud le plus à gauche
Node*& most_left(Node*& node) {
    if (node->left == nullptr) return node;
    return most_left(node->left);
}

// Suppression d'une valeur
bool remove(Node*& node, int value) {
    if (!node) return false;

    if (value < node->value) {
        return remove(node->left, value);
    } else if (value > node->value) {
        return remove(node->right, value);
    } else {
        // Si feuille
        if (node->is_leaf()) {
            delete node;
            node = nullptr;
            return true;
        }

        // Un seul fils
        if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            delete node;
            node = child;
            return true;
        }

        // DEux fils
        Node*& min_node = most_left(node->right);
        node->value = min_node->value;
        return remove(min_node, min_node->value);
    }
}

// Supprimer l'arbre 
void delete_tree(Node* node) {
    if (!node) return;
    node->delete_children();
    delete node;
}
