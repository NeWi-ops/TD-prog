#include <vector>
#include <iostream>

void merge_sort_merge(std::vector<int> & vec, size_t left, size_t middle, size_t right) {
    std::vector<int> left_vec(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> right_vec(vec.begin() + middle + 1, vec.begin() + right + 1);

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < left_vec.size() && j < right_vec.size()) {
        if (left_vec[i] <= right_vec[j]) {
            vec[k++] = left_vec[i++];
        } else {
            vec[k++] = right_vec[j++];
        }
    }

    while (i < left_vec.size()) {
        vec[k++] = left_vec[i++];
    }

    while (j < right_vec.size()) {
        vec[k++] = right_vec[j++];
    }
}

void merge_sort(std::vector<int> & vec, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<int> & vec) {
    if (!vec.empty()) {
        merge_sort(vec, 0, vec.size() - 1);
    }
}

int main() {
    std::vector<int> vec = {5, 2, 9, 1, 5, 6};

    merge_sort(vec);

    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
