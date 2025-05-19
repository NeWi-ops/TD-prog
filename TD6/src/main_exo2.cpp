#include <iostream>
#include <vector>
#include "node.hpp"

int main() {

    Node* root = create_node(5);


    std::vector<int> values_to_insert {5, 3, 7, 2, 4, 6, 8, 1, 9, 0};
    for (int value : values_to_insert) {
        root->insert(value);
    }

    std::cout << "Affichage infixe des valeurs de l'arbre:\n";
    root->display_infix();
    std::cout << '\n';

    std::cout << "Valeur minimale : " << root->min() << '\n';
    std::cout << "Valeur maximale : " << root->max() << '\n';

    std::vector<Node const*> prefix_nodes = root->prefix();
    int sum = 0;
    for (auto node : prefix_nodes) {
        sum += node->value;
    }
    std::cout << "Somme des valeurs : " << sum << '\n';

 
    std::cout << "Hauteur de l'arbre : " << root->height() << '\n';


    delete_tree(root);

    return 0;
}
