#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <cctype>
#include <stack>
#include <cmath>


std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s); // transforme une chaîne en flux de caractères, cela simule un flux comme l'est std::cin
    // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque élément est séparé par un espace
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

bool is_floating(std::string const& s)
{
    bool point_found = false;


    if (s.empty()) return false;

    //On écrit ces 3 lignes pour être sûr que le calcul fonctionne quand même si l'utilisateur a rentré un premier token avec un signe collé au chiffre sans espace.
    size_t start = 0;
    if ((s[0] == '+' || s[0] == '-') && s.length() > 1) {
        start = 1;  
    }

    
    for (size_t i = start; i < s.length(); ++i)
    {
        char c = s[i];

        if (c == '.') {
            if (point_found) {
                return false;  
            }
            point_found = true;  
        }
        else if (!std::isdigit(c)) {
            return false;  
        }
    }

    return true;  
}


 

float npi_evaluate(std::vector<std::string> const& tokens)
{
    std::stack<float> stack;  

    
    for (const std::string& token : tokens)
    {
        if (is_floating(token))  
        {
            
            stack.push(std::stof(token));  
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")  
        {
            
            if (stack.size() < 2)
                throw std::invalid_argument("Expression invalide, pas de quoi faire l'opération");

            
            float rightOperand = stack.top();
            stack.pop();
            float leftOperand = stack.top();
            stack.pop();

            
            float result = 0;
            if (token == "+")
                result = leftOperand + rightOperand;
            else if (token == "-")
                result = leftOperand - rightOperand;
            else if (token == "*")
                result = leftOperand * rightOperand;
            else if (token == "^")
                result = std::pow(leftOperand,rightOperand);
            else if (token == "/")
            {
                
                if (rightOperand == 0)
                    throw std::invalid_argument("Division par zéro.");
                result = leftOperand / rightOperand;
            }

            
            stack.push(result);
        }
        else
        {
            throw std::invalid_argument("Opérateur inconnu : " + token);
        }
    }

   
    if (stack.size() != 1)
        throw std::invalid_argument("Expression invalide pas assez d'éléments");

   
    return stack.top();
}


int main() {
    
    std::string expression;
    std::cout << "Entrez une expression en NPI : "<<std::endl;
    std::getline(std::cin, expression); 

    
    std::cout << "Expression saisie : " << expression << std::endl;

    std::vector<std::string> tokens = split_string(expression);

    
    std::cout << "Les tokens de l'expression NPI sont :\n";
    for (const auto& token : tokens)
    {
        std::cout << token << "\n";
    }

    float result = npi_evaluate(tokens);
    std::cout<< "Le résultat est : "<< result << std::endl;

    return 0;
}

