#pragma once

struct Node {
    int value;
    Node* left { nullptr };
    Node* right { nullptr };

    // Méthode pour vérifier si le nœud est une feuille
    bool is_leaf() const;
};

// Fonction pour créer un nœud
Node* create_node(int value);
