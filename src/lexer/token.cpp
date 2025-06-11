#include "conkey/lexer/token.hpp"
#include <sys/types.h>

namespace Conkey::Lexer {

    std::string stringify(const TokenType tokenType) {
        switch (tokenType) {
            case TokenType::END_OF_FILE:
                return "END_OF_FILE";
            case TokenType::IDENT:
                return "IDENT";
            case TokenType::INT:
                return "INT";
            case TokenType::ASSIGN:
                return "ASSIGN";
            case TokenType::PLUS:
                return "PLUS";
            case TokenType::MINUS:
                return "MINUS";
            case TokenType::BANG:
                return "BANG";
            case TokenType::ASTERISK:
                return "ASTERISK";
            case TokenType::SLASH:
                return "SLASH";
            case TokenType::LT:
                return "LT";
            case TokenType::GT:
                return "GT";
            case TokenType::EQ:
                return "EQ";
            case TokenType::NOT_EQ:
                return "NOT_EQ";
            case TokenType::COMMA:
                return "COMMA";
            case TokenType::SEMICOLON:
                return "SEMICOLON";
            case TokenType::LPAREN:
                return "LPAREN";
            case TokenType::RPAREN:
                return "RPAREN";
            case TokenType::LBRACE:
                return "LBRACE";
            case TokenType::RBRACE:
                return "RBRACE";
            case TokenType::FUNCTION:
                return "FUNCTION";
            case TokenType::LET:
                return "LET";
            case TokenType::TRUE:
                return "TRUE";
            case TokenType::FALSE:
                return "FALSE";
            case TokenType::IF:
                return "IF";
            case TokenType::ELSE:
                return "ELSE";
            case TokenType::RETURN:
                return "RETURN";
            default:
                return "ILLEGAL";
        }
    }

    bool Token::operator==(const Token& other) const {
        return type == other.type && literal == other.literal;
    }

    std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "Token(" << stringify(token.type) << ", '" << token.literal << "')";
        return os;
    }

}
