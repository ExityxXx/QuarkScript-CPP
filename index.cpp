#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    Plus=0, Minus, Multiply, Divide=3,
};

struct Token {
    TokenType type;
    std::string value;
};

std::string token_type_to_string(TokenType &token_type) {
    switch (token_type)
    {
    case TokenType::Plus:
        return "Plus";
    case TokenType::Minus:
        return "Minus";
    case TokenType::Multiply:
        return "Multiply";
    case TokenType::Divide:
        return "Divide";
    default:
        return "Unknown";
    }
}
class Lexer {
    private:
        std::string text;
        int position = 0;
        char current_char;
        // Functions
        void advance() {
            ++position;
            if (text.length() > position) current_char = text[position];
            else current_char = '\0';
        }
    public:
        // Constructor
        Lexer(std::string text) {
            this->text = text;
            current_char = text[position];
        }

        
    
        // Tokenize Function
        std::vector<Token> tokenize() {
            std::vector <Token> tokens;
            while (current_char) {
                if (current_char == ' ' || current_char == '\t') {
                    advance();
                    continue;
                }

                if (current_char == '+') {
                    tokens.push_back({TokenType::Plus, "+"});
                    advance();
                    continue;
                }
                if (current_char == '-') {
                    tokens.push_back({TokenType::Minus, "-"});
                    advance();
                    continue;
                }
                if (current_char == '/') {
                    tokens.push_back({TokenType::Divide, "/"});
                    advance();
                    continue;
                }
                if (current_char == '*') {
                    tokens.push_back({TokenType::Multiply, "*"});
                    advance();
                    continue;
                }
            }
            return tokens;
        }
};
int main() {
    Lexer tokens("++ - / *");
    std::vector<Token> tokenize_result = tokens.tokenize();

    for (Token &element : tokenize_result) {
        std::cout << "Token(type=" << token_type_to_string(element.type) << ", value='" << element.value << "')\n"; 
    }
}

