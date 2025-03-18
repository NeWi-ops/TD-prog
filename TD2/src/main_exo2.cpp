#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <cmath>








enum class Operator { ADD, SUB, MUL, DIV };


enum class TokenType { OPERATOR, OPERAND };


struct Token 
{
    TokenType type; 
    float value;    
    Operator op;
};    

Token make_token(float value) {
    return Token{TokenType::OPERAND, value, Operator::ADD};
}

Token make_token(Operator op) {
    return Token{TokenType::OPERATOR, 0.0f, op};
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

std::vector<Token> tokenize(std::vector<std::string> const& words) {
    std::vector<Token> tokens; 

    for (const std::string& word : words) { 
        if (is_floating(word)) { 
            tokens.push_back(make_token(std::stof(word))); 
        } 
        else if (word == "+") { 
            tokens.push_back(make_token(Operator::ADD)); 
        } 
        else if (word == "-") { 
            tokens.push_back(make_token(Operator::SUB)); 
        } 
        else if (word == "*") { 
            tokens.push_back(make_token(Operator::MUL)); 
        } 
        else if (word == "/") { 
            tokens.push_back(make_token(Operator::DIV)); 
        } 
        else { 
            throw std::invalid_argument("Token inconnu : " + word); 
        } 
    }
    return tokens;
}



float npi_evaluate(std::vector<Token> const& tokens) {
    std::stack<float> stack; 

    for (const Token& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            stack.push(token.value); 
        } 
        else if (token.type == TokenType::OPERATOR) {
            if (stack.size() < 2) {
                throw std::runtime_error("Expression NPI invalide : pas assez d'opérandes !");
            }

            
            float rightOperand = stack.top(); stack.pop();
            float leftOperand = stack.top(); stack.pop();
            float result = 0.0f;

            switch (token.op) {
                case Operator::ADD: result = leftOperand + rightOperand; break;
                case Operator::SUB: result = leftOperand - rightOperand; break;
                case Operator::MUL: result = leftOperand * rightOperand; break;
                case Operator::DIV: 
                    if (rightOperand == 0.0f) {
                        throw std::runtime_error("Erreur : Division par zéro !");
                    }
                    result = leftOperand / rightOperand;
                    break;
            }

            stack.push(result); 
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Expression NPI invalide : trop d'opérandes !");
    }

    return stack.top(); 
}

