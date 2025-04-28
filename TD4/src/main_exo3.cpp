#include <iostream>
#include <string>
#include <algorithm>

bool is_palindrome(std::string const& str) {
    return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin());
}

int main() {
    std::string mot;

    std::cout << "Entrez un mot : ";
    std::cin >> mot;

    if (is_palindrome(mot)) {
        std::cout << mot << " est un palindrome !" << std::endl;
    } else {
        std::cout << mot << " n'est pas un palindrome." << std::endl;
    }

    return 0;
}
