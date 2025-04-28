#include <iostream>
#include <vector>
#include <string>

size_t folding_string_hash(std::string const& s, size_t max){
    size_t hash_value = 0;

    for (char c : s){
        hash_value += static_cast<size_t>(c);
    }

    return hash_value % max;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max){
    size_t hash_value = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        hash_value += static_cast<size_t>(s[i]) * (i + 1);
    }

    return hash_value % max;
}

size_t polynomial_rolling_hash(const std::string& s, size_t p, size_t m){
    size_t hash_value = 0;
    size_t power = 1; 
    for (char c : s) {
        hash_value = (hash_value + (static_cast<size_t>(c) * power) % m) % m;
        power = (power * p) % m;
    }
    return hash_value;
}

int main(){
    std::string phrase;
    std::cout<<"entrez une phrase"<<std::endl;
    std::getline(std::cin, phrase);

    size_t max_value {1024};
    size_t p {11};
    size_t m {1000000009};


    std::cout<<"Hash de "<<phrase<<" sans prise en compte de l'ordre : "<<folding_string_hash(phrase, max_value)<<std::endl;
    std::cout<<"Hash de "<<phrase<<" avec prise en compte de l'ordre : "<<folding_string_ordered_hash(phrase, max_value)<<std::endl;
    std::cout<<"Hash de "<<phrase<<" avec polynomial rolling hash : "<<polynomial_rolling_hash(phrase, p, m)<<std::endl;



    return 0;
}