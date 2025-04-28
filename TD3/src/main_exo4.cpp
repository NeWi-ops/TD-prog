#include <iostream>
#include <vector>

int search(const std::vector<int>& vec, int value) {
    size_t left = 0;
    size_t right = vec.size() - 1;

    while (left <= right) {
        size_t middle = left + (right - left) / 2;

        if (vec[middle] == value) {
            return static_cast<int>(middle);
        }
        else if (vec[middle] < value) {
            left = middle + 1;
        }
        else {
            if (middle == 0) break;
            right = middle - 1;
        }
    }

    return -1; 
}

void test_search(const std::vector<int>& vec, int value) {
    int index = search(vec, value);
    std::cout << "Recherche de " << value << " : ";
    if (index != -1) {
        std::cout << "Trouvé à l'indice " << index << std::endl;
    } else {
        std::cout << "Non trouvé" << std::endl;
    }
}

int main() {
    std::vector<int> tab1 = {1, 2, 2, 3, 4, 8, 12};
    std::vector<int> tab2 = {1, 2, 3, 3, 6, 14, 12, 15};
    std::vector<int> tab3 = {2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::vector<int> tab4 = {5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<int> tab5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    test_search(tab1, 8);
    test_search(tab2, 15);
    test_search(tab3, 16);
    test_search(tab4, 6);
    test_search(tab5, 10);

    return 0;
}
