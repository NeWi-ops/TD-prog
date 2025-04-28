#include <vector>
#include <iostream>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

void bubble_sort(std::vector<int> & vec)
{
    int n = vec.size();
    bool swapped;
    do {
        swapped = false;
        for (int i{0}; i<n-1; i++)
        {
            if (vec[i] > vec[i+1]){
                std::swap(vec[i],vec[i+1]);
                swapped = true;
            }
        }
        n--;
    } while (swapped);
}

void selection_sort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_index]) {
                min_index = j;
            }
        }
        std::swap(vec[i], vec[min_index]);
    }
}

int main()
{
    std::vector<int> array {1, 9, 4, 3, 8, 2, 6, 5, 7};
if (is_sorted(array)) {
    std::cout << "Le tableau est trié" << std::endl;
} else {
    std::cout << "Le tableau n'est pas trié" << std::endl;
    for (int k : array)
    {
        std::cout<<k;
    }
    std::cout<<std::endl;
    // bubble_sort(array);
    selection_sort(array);
        if (is_sorted(array)) {
            std::cout << "Le tableau est trié" << std::endl;
            for (int k : array)
            {
                std::cout<<k;
            }
        } else {
            std::cout << "Le tableau n'est pas trié" << std::endl;
        }
}

}