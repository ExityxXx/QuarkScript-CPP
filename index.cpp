#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cctype>

enum class TokenType {
    Plus=0, Minus, Multiply, Divide=3,
    Int=4, Float, LeftParen, RightParen=7,
    Identifier=8, IfKeyword, StdoutKeyword=10,
    SemiColon=11
};

struct Token {
    TokenType type;
    int line;
    int column;
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
    case TokenType::LeftParen: return "LeftParen";
    case TokenType::RightParen: return "RigthParen";
    case TokenType::Identifier: return "Identifier";
    case TokenType::StdoutKeyword: return "Stdout";
    case TokenType::SemiColon: return "SemiColon";
    default:
        return "Unknown";
    }
}
class Lexer
{
    private:
        // Variables
        std::string text;
        char current_char;
        int position = 0;
        int line = 1;
        int column = 1;

        std::unordered_map<std::string, TokenType> keywords
        {
            {"stdout", TokenType::StdoutKeyword}
        };

        std::unordered_map<char, TokenType> operators
        {
            {'+', TokenType::Plus},
            {'-', TokenType::Minus},
            {'*', TokenType::Multiply},
            {'/', TokenType::Divide},
            {'(', TokenType::LeftParen},
            {')', TokenType::RightParen},
            {';', TokenType::SemiColon}
        };
        // Advance Function
        void advance()
        {
            ++position;
            if (text.length() > position) current_char = text[position];
            else current_char = '\0';
        }
        void skipWhiteSpace()
        {
            while (current_char && (current_char == ' ' || current_char == '\t'))
            {
                if (current_char == '\n')
                {
                    line += 1;
                    column = 1;
                }
                else
                {
                    column += 1;
                }
                advance();
            }
        }
        // Number Generate Function
        Token numberGenerate()
        {
            std::string result;
            bool dot_count = false;

            while (isdigit(current_char))
            {
                if (current_char == '.')
                {
                    if (dot_count) break;
                    dot_count = true;

                }
                result += current_char;
                advance();
            }

            return dot_count ? Token{TokenType::Float, line, column, result} : Token{TokenType::Int, line, column, result};
        }

        Token idOrKeywordGenerate()
        {
            std::string result;

            while (isalpha(current_char) || current_char == '_')
            {
                result += current_char;
                advance();
            }

            return !keywords.count(result) ?
            Token{TokenType::Identifier, line, column, result} :
            Token{keywords[result], line, column, result};
        }
    public:
        // Constructor
        Lexer(std::string text) : text(text)
        {
            current_char = text[position];
        }
        
        // Tokenize Function
        std::vector<Token> tokenize() 
        {
            std::vector<Token> tokens;
            while (current_char != '\0')
            {
                skipWhiteSpace();

                if (operators.count(current_char) == 1)
                {
                    tokens.push_back({operators[current_char], line, column, std::string(1, current_char)});
                    advance();
                    continue;
                }
                
                if (isdigit(current_char))
                {
                    Token generated_number = numberGenerate();
                    tokens.push_back(generated_number);
                    continue; 
                }

                if (isalpha(current_char) || current_char == '_')
                {
                    Token gererated_identifier = idOrKeywordGenerate();
                    tokens.push_back(gererated_identifier);
                    continue;
                } 
                else
                {
                    std::cerr << "Illegal Character: " << current_char;
                    break;
                }
              
            }
            
            return tokens;
        }
};


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::string code;
    
    std::cout << "Enter code: ";
    getline(std::cin, code);
    Lexer tokens(code);
    std::vector<Token> tokenize_result = tokens.tokenize();
    
    for (Token &element : tokenize_result) {
        std::cout << "Token(type=" + token_type_to_string(element.type) + ", value='" + element.value + "', line=" + std::to_string(element.line) + ", column=" + std::to_string(element.column) +")\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}

 
