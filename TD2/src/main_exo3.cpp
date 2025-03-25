#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>








enum class Operator { ADD, SUB, MUL, DIV, EXP, OPEN_PAREN, CLOSE_PAREN };


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

Token make_token(std::string const& symbol) {
    if (symbol == "+") return Token{TokenType::OPERATOR, 0.0f, Operator::ADD};
    if (symbol == "-") return Token{TokenType::OPERATOR, 0.0f, Operator::SUB};
    if (symbol == "*") return Token{TokenType::OPERATOR, 0.0f, Operator::MUL};
    if (symbol == "/") return Token{TokenType::OPERATOR, 0.0f, Operator::DIV};
    if (symbol == "^") return Token{TokenType::OPERATOR, 0.0f, Operator::EXP};
    if (symbol == "(") return Token{TokenType::OPERATOR, 0.0f, Operator::OPEN_PAREN};
    if (symbol == ")") return Token{TokenType::OPERATOR, 0.0f, Operator::CLOSE_PAREN};
    throw std::invalid_argument("Token inconnu : " + symbol);
}

size_t operator_priority(Operator op) {
    switch (op) {
        case Operator::ADD: case Operator::SUB: return 1;
        case Operator::MUL: case Operator::DIV: return 2;
        case Operator::EXP: return 3;
        default: return 0;
    }
}


//on convertit en NPI l'expression donnée
std::vector<Token> infix_to_npi_tokens(std::vector<Token> const& infix_tokens) {
    std::vector<Token> output;
    std::stack<Token> op_stack;

    for (const Token& token : infix_tokens) {
        if (token.type == TokenType::OPERAND) {
            output.push_back(token);  // on ajoute directement les nombres
        } 
        else if (token.type == TokenType::OPERATOR) {
            Operator op = token.op;

            if (op == Operator::OPEN_PAREN) {
                op_stack.push(token);
            } 
            else if (op == Operator::CLOSE_PAREN) {
                while (!op_stack.empty() && op_stack.top().op != Operator::OPEN_PAREN) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                op_stack.pop(); // une fois la parenthèse ouvrante prise en compte on la supprime
            } 
            else {
                while (!op_stack.empty() &&
                       operator_priority(op_stack.top().op) >= operator_priority(op)) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                op_stack.push(token);
            }
        }
    }

    // on ajoute le reste les opérateurs restants
    while (!op_stack.empty()) {
        output.push_back(op_stack.top());
        op_stack.pop();
    }

    return output;
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

// on modifie tokenize pour que la fonction prenne en compte les parenthèses et le s exponentielles
std::vector<Token> tokenize(std::vector<std::string> const& words) {
    std::vector<Token> tokens;

    for (const std::string& word : words) {
        if (is_floating(word)) {
            tokens.push_back(make_token(std::stof(word)));
        } else {
            tokens.push_back(make_token(word));
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
                throw std::runtime_error("Rentrer une expression valide svp");
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
                        throw std::runtime_error("division par 0");
                    }
                    result = leftOperand / rightOperand;
                    break;
                case Operator::EXP: result = std::pow(leftOperand, rightOperand); break;
            }

            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("rentrer une expression valide svp");
    }

    return stack.top();
}

//j'avais des problems d'affichage de l'expression en NPI les operateurs apparaissaient comme des nombres donc j'ai fais une fonction pour être sur qu'ils soient des strings
std::string operator_to_string(Operator op) {
    switch (op) {
        case Operator::ADD: return "+";
        case Operator::SUB: return "-";
        case Operator::MUL: return "*";
        case Operator::DIV: return "/";
        case Operator::EXP: return "^";
        default: return "?";
    }
}


int main() {
    std::cout << "Entrez un calcul ";
    std::string input;
    std::getline(std::cin, input);

    // On sépare chaque caractères (tokens)
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

    try {
        
        auto infix_tokens = tokenize(words);

        //on convertit
        auto npi_tokens = infix_to_npi_tokens(infix_tokens);

        // On sort l'expression en NPI
        std::cout << "Expression en NPI : ";
        for (const auto& token : npi_tokens) {
            if (token.type == TokenType::OPERAND) {
                std::cout << token.value << " ";
            } else {
                std::cout << operator_to_string(token.op) << " ";
            }
        }
        std::cout << std::endl;

        // On l'évalue avec le même procédé que l'exercice 1 et 2
        float result = npi_evaluate(npi_tokens);
        std::cout << "Résultat : " << result << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}

