#include <iostream>
#include <vector>

void counting_sort(std::vector<int>& vec, int const max) {
    std::vector<int> count(max + 1, 0);

    for (int num : vec) {
        count[num]++;
    }

    size_t index = 0;
    for (int value = 0; value <= max; ++value) {
        while (count[value] > 0) {
            vec[index++] = value;
            count[value]--;
        }
    }
}

void print_vector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {4, 2, 2, 8, 3, 3, 1};

    std::cout << "Avant tri : ";
    print_vector(vec);

    counting_sort(vec, 8);

    std::cout << "Après tri : ";
    print_vector(vec);

    return 0;
}
