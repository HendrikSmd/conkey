#include "conkey/lexer/lexer.hpp"

#include "conkey/lexer/token.hpp"
#include <iostream>
#include <string_view>
#include <cstdio>

namespace Conkey::Lexer {

    Lexer::Lexer(std::istream& sourceIn, const std::string_view sourceName) :
        sourceIn_(sourceIn),
        sourceName_(sourceName)
    {
        if (sourceIn_) {
            this->currentChar_ = sourceIn_.get();
        } else {
            this->currentChar_ = EOF;
        }
    }

    bool Lexer::noMoreTokens() const {
        return this->currentChar_ == EOF;
    }

    Token Lexer::tryNextToken() {
        Token token;
        this->eatWhitespaces();

        if (this->currentChar_ == EOF) {
            token.type = TokenType::END_OF_FILE;
            token.literal = "";
            return token;
        }

        switch(currentChar_) {
            case '=':
                if (static_cast<char>(sourceIn_.peek()) == '=') {
                    token.type = TokenType::EQ;
                    token.literal = "==";
                    sourceIn_.get();
                } else {
                    token.type = TokenType::ASSIGN;
                    token.literal = "=";
                }
                break;
            case '+':
                token.type = TokenType::PLUS;
                token.literal = "+";
                break;
            case '-':
                token.type = TokenType::MINUS;
                token.literal = "-";
                break;
            case '!':
                if (static_cast<char>(sourceIn_.peek()) == '=') {
                    token.type = TokenType::NOT_EQ;
                    token.literal = "!=";
                    sourceIn_.get();
                } else {
                    token.type = TokenType::BANG;
                    token.literal = "!";
                }
                break;
            case '*':
                token.type = TokenType::ASTERISK;
                token.literal = "*";
                break;
            case '/':
                token.type = TokenType::SLASH;
                token.literal = "/";
                break;
            case '<':
                token.type = TokenType::LT;
                token.literal = "<";
                break;
            case '>':
                token.type = TokenType::GT;
                token.literal = ">";
                break;
            case ',':
                token.type = TokenType::COMMA;
                token.literal = ",";
                break;
            case ';':
                token.type = TokenType::SEMICOLON;
                token.literal = ";";
                break;
            case '(':
                token.type = TokenType::LPAREN;
                token.literal = "(";
                break;
            case ')':
                token.type = TokenType::RPAREN;
                token.literal = ")";
                break;
            case '{':
                token.type = TokenType::LBRACE;
                token.literal = "{";
                break;
            case '}':
                token.type = TokenType::RBRACE;
                token.literal = "}";
                break;
            default:
                if (isLetter()) {
                    token.literal = readIdentifier();
                    token.type = TokenType::IDENT;
                } else if (isDigit()) {
                    token.literal = readNumber();
                    token.type = TokenType::INT;
                } else {
                    token.type = TokenType::ILLEGAL;
                    token.literal = currentChar_;
                }
        }

        if (token.type != TokenType::IDENT && token.type != TokenType::INT) {
            this->currentChar_ = sourceIn_.get();
        }

        if (
            token.type == TokenType::IDENT &&
            keywords_.find(token.literal) != keywords_.end()) {
            token.type = keywords_[token.literal];
        }

        return token;
    }

    void Lexer::eatWhitespaces() {
        while (
            this->currentChar_ == ' ' ||
            this->currentChar_ == '\t' ||
            this->currentChar_ == '\n' ||
            this->currentChar_ == '\r' ||
            this->currentChar_ == '\f' ||
            this->currentChar_ == '\v') {
            this->currentChar_ = sourceIn_.get();
        }
    }

    bool Lexer::isDigit() const {
        return std::isdigit(this->currentChar_);
    }

    bool Lexer::isLetter() const {
        return std::isalpha(this->currentChar_) || this->currentChar_ == '_';
    }

    std::string Lexer::readIdentifier() {
        std::string s;
        while (isLetter()) {
            s += this->currentChar_;
            this->currentChar_ = sourceIn_.get();
        }
        return s;
    }

    std::string Lexer::readNumber() {
        std::string s;
        while (isDigit()) {
            s += this->currentChar_;
            this->currentChar_ = sourceIn_.get();
        }
        return s;
    }

}
