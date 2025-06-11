#ifndef CONKEY_LEXER_LEXER_HPP
#define CONKEY_LEXER_LEXER_HPP

#include <iostream>
#include <string_view>
#include <unordered_map>
#include "conkey/lexer/token.hpp"

namespace Conkey::Lexer {

    class Lexer {
        public:
        Lexer(std::istream& sourceIn, const std::string_view sourceName);

        Token                   tryNextToken();
        bool                    noMoreTokens() const;

        private:

        void                    eatWhitespaces();
        bool                    isDigit() const;
        bool                    isLetter() const;

        std::string             readIdentifier();
        std::string             readNumber();

        std::unordered_map<std::string, TokenType> keywords_ = {
            {"fn", TokenType::FUNCTION},
            {"let", TokenType::LET},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"return", TokenType::RETURN}
        };

        char currentChar_;
        std::istream& sourceIn_;
        const std::string_view sourceName_;
    };

}



#endif // CONKEY_LEXER_LEXER_HPP
