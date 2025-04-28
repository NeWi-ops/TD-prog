#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "ScopedTimer.hpp"

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max; });
    return vec;
}


void merge_sort_merge(std::vector<int> & vec, size_t left, size_t middle, size_t right) {
    std::vector<int> left_vec(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> right_vec(vec.begin() + middle + 1, vec.begin() + right + 1);

    size_t i = 0, j = 0, k = left;
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
    if (left >= right) return;
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


size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right, size_t pivot_index) {
    int pivot_value = vec[pivot_index];
    std::swap(vec[pivot_index], vec[right]); 
    size_t store_index = left;

    for (size_t i = left; i < right; ++i) {
        if (vec[i] < pivot_value) {
            std::swap(vec[i], vec[store_index]);
            store_index++;
        }
    }
    std::swap(vec[store_index], vec[right]); 
    return store_index;
}

void quick_sort(std::vector<int> & vec, size_t left, size_t right) {
    if (left >= right) return;

    size_t pivot_index = left + (right - left) / 2; 
    pivot_index = quick_sort_partition(vec, left, right, pivot_index);

    if (pivot_index > 0) 
        quick_sort(vec, left, pivot_index - 1);
    quick_sort(vec, pivot_index + 1, right);
}

void quick_sort(std::vector<int> & vec) {
    if (!vec.empty()) {
        quick_sort(vec, 0, vec.size() - 1);
    }
}


int main() {
    const size_t size = 100000; 
    std::vector<int> original = generate_random_vector(size, 1000000);

    
    std::vector<int> vec_merge = original;
    std::vector<int> vec_quick = original;
    std::vector<int> vec_std   = original;

   
    {
        ScopedTimer timer("Merge Sort");
        merge_sort(vec_merge);
    }

    
    {
        ScopedTimer timer("Quick Sort");
        quick_sort(vec_quick);
    }

    
    {
        ScopedTimer timer("std::sort");
        std::sort(vec_std.begin(), vec_std.end());
    }

    return 0;
}

//On remarque que std::sort est bien plus rapide, que les autres, le plus long est merge sort surement parce qu'il fait beaucoup de copies de vecteurs.
//ce n'est pas étonnant std::sort est optimisé pour être le plus rapide et prendre le moins de mémoire possible.
