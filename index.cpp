#include <iostream>
#include <string>
#include <vector>
#include <chrono>

enum class TokenType {
    Plus=0, Minus, Multiply, Divide=3,
    Int=4, Float
};

struct Token {
    TokenType type;
    std::string value;
};

std::string token_type_to_string(TokenType &token_type) {
    switch (token_type)
    {
    case TokenType::Plus: return "Plus";
    case TokenType::Minus: return "Minus";
    case TokenType::Multiply: return "Multiply";
    case TokenType::Divide: return "Divide";
    case TokenType::Int: return "Int";
    case TokenType::Float: return "Float";
    default:
        return "Unknown";
    }
}
class Lexer {
    private:
        // Variables
        std::string text;
        int position = 0;
        char current_char;
        // Advance Function
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

        
        // Number Generate Function
        Token numberGenerate() {
            std::string result;
            bool dot_count = false;

            while (current_char && (current_char >= '0' && current_char <= '9') || current_char == '.') {
                if (current_char == '.') {
                    if (dot_count) break;
                    dot_count = true;

                }
                result += current_char;
                advance();
            }

            return dot_count ? Token{TokenType::Float, result} : Token{TokenType::Int, result};
        }
        // Tokenize Function
        std::vector<Token> tokenize() {
            std::vector<Token> tokens;
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
                if (current_char >= '0' || current_char <= '9') {
                    Token generated_number = numberGenerate();
                    tokens.push_back(generated_number);
                    continue; 
                }
            }
            return tokens;
        }
};


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Lexer tokens("5 + 5 - 10 * 2 / 50.5 * 234 3029894098320948320948320948 * 342 ");
    std::vector<Token> tokenize_result = tokens.tokenize();
    
    for (Token &element : tokenize_result) {
        std::cout << "Token(type=" + token_type_to_string(element.type) + ", value'" + element.value + "')\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}

