#include "binarytree.hpp"

// Insèrer une valeur
void BinaryTree::insert(int value) {
    if (root) {
        root->insert(value);
    } else {
        root = create_smart_node(value);
    }
}

// Supprime une valeur 
bool BinaryTree::remove(int value) {
    if (root) {
        return ::remove(root, value);
    }
    return false;
}

// Vide l'arbre 
void BinaryTree::clear() {
    root.reset(); 
}

// Vérifie si une valeur est présente dans l'arbre
bool BinaryTree::contains(int value) const {
    if (!root) return false;
    return ::contains(const_cast<std::unique_ptr<SmartNode>&>(root), value);
}

// Hauteur de larbre
size_t BinaryTree::height() const {
    return root ? root->height() : 0;
}


bool contains(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) return false;
    if (value == node->value) return true;
    if (value < node->value) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}
