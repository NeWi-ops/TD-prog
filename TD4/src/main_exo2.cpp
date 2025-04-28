#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

size_t nombreLettres(const std::string& phrase){
    
    auto it = std::find(phrase.begin(), phrase.end(), ' ');
    if (it != phrase.end()){
        return std::distance(phrase.begin(), it); 
    } 
    else{
        return phrase.length();
    }
}

std::vector<std::string> split_string(std::string const& str) {
    std::vector<std::string> mots;
    auto const is_space = [](char letter) { return letter == ' '; };

    auto start = str.begin();
    auto end = str.begin();
    end = std::find_if(start, str.end(), is_space);

    while(start != end){
        end = std::find_if(start, str.end(), is_space);
        mots.push_back(std::string(start,end));
        start = (end == str.end() ? end : std::find_if_not(end, str.end(), is_space));
    }

    return mots;
}


int main() {
    // petit 1
    std::string phrase;
    // std::cout<<"Entrez une phrase svp"<<std::endl;
    // std::getline(std::cin, phrase);

    // std::cout<<"Le nombre de lettres du premier mot est : "<<nombreLettres(phrase)<<std::endl;

    // return 0;

    
    std::cout<<"Entrez une phrase svp"<<std::endl;
    std::getline(std::cin, phrase);

    std::vector<std::string> mots = split_string(phrase);

    std::cout << "Les mots dans la phrase sont :"<<std::endl;
    for (auto mot : mots) {
        std::cout << mot << std::endl;
    }

    return 0;
}