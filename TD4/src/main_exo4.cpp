#include <iostream>
#include <vector>
#include <numeric>

int somme_carrés(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0, [](int acc, int val) {
        return acc + val * val; // On ajoute le carré de chaque élément
    });
}

int produit_pairs(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 1, [](int acc, int val) {
        return (val % 2 == 0) ? acc * val : acc; // Multiplie les éléments pairs
    });
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    int somme = somme_carrés(vec);
    std::cout << "La somme des carrés des éléments est : " << somme << std::endl;

    int produit = produit_pairs(vec);
    std::cout << "Le produit des éléments pairs est : " << produit << std::endl;

    return 0;
}
