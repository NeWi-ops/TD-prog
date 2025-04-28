#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <numeric>


int main() {
    const int taille {10};
    std::vector<int> nombres(taille);

    std::srand(std::time(nullptr));

    for (int& nombre : nombres){
        nombre = std::rand() % 101;
    } 

    std::cout<<"nombres générés : "<<std::endl;
    // for (const int& nombre : nombres){
    //     std::cout<<nombre<<std::endl;
    // }

    // for (std::vector<int>::iterator it = nombres.begin(); it != nombres.end(); ++it)
    for (auto it = nombres.begin(); it != nombres.end(); ++it)
    {
        std::cout<< *it <<std::endl;
    }

    int nombreUser {};
    std::cout<<"Quel nombre voulez vous trouver ?"<<std::endl;
    std::cin>>nombreUser;

    auto it = std::find(nombres.begin(), nombres.end(), nombreUser);

    if (it != nombres.end()){
        std::cout<<"Le nombre recherché est bien dans la liste"<<std::endl;
    }
    else{
        std::cout<<"Le nombre recherché n'est pas dans la liste"<<std::endl;

    }

    int occurences = std::count(nombres.begin(), nombres.end(), nombreUser);
    std::cout<<"Ce nombre est présent "<<occurences<<" fois."<<std::endl;

    std::sort(nombres.begin(), nombres.end());
    std::cout<<"tableau trié :"<<std::endl; 
    for (int nb : nombres)
    {
        std::cout<< nb <<std::endl;
    }

    int somme = accumulate(nombres.begin(), nombres.end(), 0);
    std::cout<<"la somme des éléments du tableau est : "<<somme<<std::endl;

    return 0;
}