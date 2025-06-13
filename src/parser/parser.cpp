#include "conkey/parser/parser.hpp"

#include<memory>
#include <stdexcept>

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"

namespace Conkey::Parser {

    Parser::Parser(Lexer::Lexer& lexer) :
        lexer_(lexer) {
            nextToken();
    };

    ParseError::ParseError(const std::string& msg) :
        std::runtime_error("Parsing Error: " + msg)
    {};

    void Parser::nextToken() {
        currentToken_ = lexer_.tryNextToken();
    }

    void Parser::expectTokenType(Lexer::TokenType type) {
        if (currentToken_.type != type) {
            throw ParseError("Encountered Unexpected token! Expected "
                                + Lexer::stringify(type)
                                + ", received "
                                + currentToken_.literal
                                + ".");
        }
    }

    ProgramPtr Parser::parseProgram() {
        auto programPtr = std::make_unique<Program>();

        while (currentToken_.type != Lexer::TokenType::END_OF_FILE) {
            programPtr->statements_.push_back(parseStatement());
            nextToken();
        }

        return programPtr;
    }

    StatementPtr Parser::parseStatement() {
        switch(currentToken_.type) {
            case Lexer::TokenType::LET:
                return parseLetStatement();
            default:
                return nullptr;
        }

        return nullptr;
    }

    LetStatementPtr Parser::parseLetStatement() {
        LetStatementPtr letPtr = std::make_unique<LetStatement>();
        expectTokenType(Lexer::TokenType::LET);
        nextToken();

        letPtr->identifier_ = parseIdentifier();

        expectTokenType(Lexer::TokenType::ASSIGN);
        nextToken();

        // Parse Expression here

        expectTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();

        return letPtr;
    }

    IdentifierPtr Parser::parseIdentifier() {
        expectTokenType(Lexer::TokenType::IDENT);
        IdentifierPtr identPtr = std::make_unique<Identifier>(std::move(currentToken_.literal));
        nextToken();
        return identPtr;
    }





}
