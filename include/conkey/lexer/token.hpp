#ifndef CONKEY_LEXER_TOKEN_HPP
#define CONKEY_LEXER_TOKEN_HPP

#include <ostream>
#include <string>

namespace Conkey::Lexer {

    enum class TokenType {
        // Special tokens
        ILLEGAL,
        END_OF_FILE,

        // Identifiers + literals
        IDENT,
        INT,

        // Operators
        ASSIGN,
        PLUS,
        MINUS,
        BANG,
        ASTERISK,
        SLASH,
        LT,
        GT,
        EQ,
        NOT_EQ,

        // Delimiters
        COMMA,
        SEMICOLON,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,

        // Keywords
        FUNCTION,
        LET,
        TRUE,
        FALSE,
        IF,
        ELSE,
        RETURN
    };

    std::string stringify(const TokenType tokenType);

    struct Token {

        bool operator==(const Token& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Token& token);

        TokenType type;
        std::string literal;
    };

}


#endif // CONKEY_LEXER_TOKEN_HPP
