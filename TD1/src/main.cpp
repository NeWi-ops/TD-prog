#include <iostream>
#include "fraction.hpp"

int main()
{
    Fraction f1 { 3, 4 };
    Fraction f2 { 1, 2 };

    std::cout << "f1 = "<<f1;

    std::cout << " f2 = "<<f2;

    std::cout << std::endl;

    
  

    std::cout << "f1+f2 = "<<(f1+f2);


    std::cout << std::endl << "f1-f2 = "<<(f1-f2);


    std::cout << std::endl << "f1*f2 = "<<(f1*f2);

    
    std::cout << std::endl << "f1/f2 = "<<(f1/f2)<<std::endl;

    if (f1==f2)
    {
        std::cout << std::endl << "f1 est égal à f2 ? : Vrai";
    }
    else 
    {
        std::cout << std::endl << "f1 est égal à f2 ? : Faux";

    }

    if (f1!=f2)
    {
        std::cout << std::endl << "f1 n'est pas égal à f2 ? : Vrai"<<std::endl;
    }
    else 
    {
        std::cout << std::endl << "f1 n'est pas égal à f2 ? : Faux"<<std::endl;

    }

    if  (f1<f2)
    {
        std::cout << std::endl << "f1 plus petit que f2 ? : Vrai";

    }
    else
    {
        std::cout << std::endl << "f1 plus petit que f2 ? : Faux";

    }

    if (f1<=f2)
    {
        std::cout << std::endl << "f1 plus petit ou égal à f2 ? : Vrai";
    }
    else
    {
        std::cout << std::endl << "f1 plus petit ou égal à f2 ? : Faux";

    }

    if (f1>f2)
    {
        std::cout << std::endl << "f1 plus grand que f2 ? : Vrai";
    }
    else
    {
        std::cout << std::endl << "f1 plus grand que f2 ? : Faux";
    }

    if (f1>=f2)
    {
        std::cout << std::endl << "f1 plus grand ou égal à f2 ? : Vrai"<<std::endl;
        
    }
    else
    {
        std::cout << std::endl << "f1 plus grand ou égal à f2 ? : Faux"<<std::endl;
        
    }


    std::cout << std::endl << "1/6+2/6 = "<<(Fraction{1, 6}+Fraction{2, 6})<<std::endl;


    //test de la conversion en float : 



    
    float f1_float = f1.to_float();
    float f2_float = static_cast<float>(f2); 

    std::cout << "f1 en float : " << f1_float << std::endl;
    std::cout << "f2 en float : " << f2_float << std::endl;

    int i = 2;

    std::cout << "f1 + i = " << (f1 + i) << "\n";
    std::cout << "i + f1 = " << (i + f1) << "\n";
    std::cout << "f1 - i = " << (f1 - i) << "\n";
    std::cout << "i - f1 = " << (i - f1) << "\n";
    std::cout << "f1 * i = " << (f1 * i) << "\n";
    std::cout << "i * f1 = " << (i * f1) << "\n";
    std::cout << "f1 / i = " << (f1 / i) << "\n";
    std::cout << "i / f1 = " << (i / f1) << "\n";

    

    

    return 0;
}