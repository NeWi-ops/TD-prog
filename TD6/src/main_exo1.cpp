// src/main.cpp
#include <iostream>
#include "node.hpp"

int main() {
    Node* root = create_node(42);
    std::cout << "Le noeud est une feuille ? " << (root->is_leaf() ? "Oui" : "Non") << std::endl;

    root->left = create_node(10);
    std::cout << "Le noeud est une feuille après ajout à gauche ? " << (root->is_leaf() ? "Oui" : "Non") << std::endl;

    // Nettoyage mémoire
    delete root->left;
    delete root;

    return 0;
}
