#include "conkey/parser/parser.hpp"

#include <cstdint>
#include <functional>
#include<memory>
#include <stdexcept>
#include <string>

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"
#include "conkey/parser/ast/expressions/integer_literal.hpp"
#include "conkey/parser/ast/expressions/prefix_expression.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include "conkey/parser/ast/statements/return_statement.hpp"

namespace Conkey::Parser {

    Parser::Parser(Lexer::Lexer& lexer) :
        lexer_(lexer),
        prefixParseFns_({
            {Lexer::TokenType::IDENT, [this](){ return parseIdentifier(); }},       // Identifier
            {Lexer::TokenType::INT, [this](){ return parseIntegerLiteral(); }},     // Integer literals
            {Lexer::TokenType::BANG, [this](){ return parsePrefixExpression(); }},    // !
            {Lexer::TokenType::MINUS, [this](){ return parsePrefixExpression(); }}    // -
        })
    {
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
                                + stringify(currentToken_.type)
                                + ".");
        }
    }

    ProgramPtr Parser::parseProgram() {
        auto programPtr = std::make_unique<Program>();

        while (currentToken_.type != Lexer::TokenType::END_OF_FILE) {
            programPtr->statements_.push_back(parseStatement());
        }

        return programPtr;
    }

    StatementPtr Parser::parseStatement() {
        switch(currentToken_.type) {
            case Lexer::TokenType::LET:
                return parseLetStatement();
            case Lexer::TokenType::RETURN:
                return parseReturnStatement();
            default:
                return parseExpressionStatement();
        }

        return nullptr;
    }

    LetStatementPtr Parser::parseLetStatement() {
        LetStatementPtr letPtr = std::make_unique<LetStatement>();
        expectTokenType(Lexer::TokenType::LET);
        nextToken();

        Identifier* rawIdentPtr = static_cast<Identifier*>(parseIdentifier().release());
        letPtr->identifier_ = IdentifierPtr(rawIdentPtr);
        expectTokenType(Lexer::TokenType::ASSIGN);
        nextToken();

        letPtr->value_ = parseExpression(OperatorPrecedences::LOWEST);

        expectTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();

        return letPtr;
    }

    ReturnStatementPtr Parser::parseReturnStatement() {
        ReturnStatementPtr returnStmntPtr = std::make_unique<ReturnStatement>();

        expectTokenType(Lexer::TokenType::RETURN);
        nextToken();

        // Parse Expression here

        expectTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();

        return returnStmntPtr;
    }

    ExpressionStatementPtr Parser::parseExpressionStatement() {
        ExpressionStatementPtr exprStmntPtr = std::make_unique<ExpressionStatement>();

        exprStmntPtr->value_ = parseExpression(OperatorPrecedences::LOWEST);
        nextToken();

        expectTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();

        return exprStmntPtr;
    }

    ExpressionPtr Parser::parseExpression(OperatorPrecedences prec) {
        if (! prefixParseFns_.contains(currentToken_.type)) {
            throw ParseError("Tried to use " + Lexer::stringify(currentToken_.type) + " as prefix operator!");
        }

        const auto& prefixParseFn = prefixParseFns_.at(currentToken_.type);
        ExpressionPtr leftExprPtr = prefixParseFn();

        return leftExprPtr;
    }

    ExpressionPtr Parser::parsePrefixExpression() {
        PrefixExpressionPtr prefixExprPtr = std::make_unique<PrefixExpression>();

        prefixExprPtr->operatorLiteral_ = currentToken_.literal;
        nextToken();

        prefixExprPtr->right_ = parseExpression(OperatorPrecedences::PREFIX);

        return prefixExprPtr;
    }

    ExpressionPtr Parser::parseIdentifier() {
        expectTokenType(Lexer::TokenType::IDENT);
        IdentifierPtr identPtr = std::make_unique<Identifier>(std::move(currentToken_.literal));
        nextToken();
        return identPtr;
    }

    ExpressionPtr Parser::parseIntegerLiteral() {
        expectTokenType(Lexer::TokenType::INT);
        try {
            int64_t parsedValue = std::stoll(currentToken_.literal);
            IntegerLiteralPtr intLitPtr = std::make_unique<IntegerLiteral>(parsedValue);
            nextToken();
            return intLitPtr;
        } catch (const std::invalid_argument& exc) {
            throw ParseError("Could not parse integer literal " + currentToken_.literal + ". Details are:" + exc.what());
        }
    }





}
