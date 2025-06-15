#include "conkey/parser/parser.hpp"

#include <cstdint>
#include <functional>
#include<memory>
#include <stdexcept>
#include <string>

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/expressions/boolean_literal.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"
#include "conkey/parser/ast/expressions/infix_expression.hpp"
#include "conkey/parser/ast/expressions/integer_literal.hpp"
#include "conkey/parser/ast/expressions/prefix_expression.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include "conkey/parser/ast/statements/return_statement.hpp"

namespace Conkey::Parser {


    OperatorPrecedence getOperatorPrecedence(Lexer::TokenType type) {
        if (precedences.contains(type)) {
            return precedences.at(type);
        }

        return OperatorPrecedence::LOWEST;
    }


    Parser::Parser(Lexer::Lexer& lexer) :
        currentToken_({.type = Lexer::TokenType::END_OF_FILE, .literal = ""}),
        peekToken_({.type = Lexer::TokenType::END_OF_FILE, .literal = ""}),
        lexer_(lexer),
        prefixParseFns_({
            {Lexer::TokenType::IDENT, [this](){ return parseIdentifier(); }},           // Identifier
            {Lexer::TokenType::INT, [this](){ return parseIntegerLiteral(); }},         // Integer literals
            {Lexer::TokenType::BANG, [this](){ return parsePrefixExpression(); }},      // !
            {Lexer::TokenType::MINUS, [this](){ return parsePrefixExpression(); }},     // -
            {Lexer::TokenType::TRUE, [this](){ return parseBooleanLiteral(); }},        // true
            {Lexer::TokenType::FALSE, [this](){ return parseBooleanLiteral(); }},        // false
            {Lexer::TokenType::LPAREN, [this](){ return parseGroupedExpression(); }}        // (
        }),
        infixParseFns_({
            {Lexer::TokenType::PLUS, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::MINUS, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::SLASH, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::ASTERISK, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::EQ, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::NOT_EQ, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::LT, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
            {Lexer::TokenType::GT, [this](ExpressionPtr exp){ return parseInfixExpression(std::move(exp)); }},
        })
    {
            // Call nextToken() two times, so currentToken_ and peekToken_ are both set
            nextToken();
            nextToken();
    };


    ParseError::ParseError(const std::string& msg) :
        std::runtime_error("Parsing Error: " + msg)
    {};


    inline void Parser::nextToken() {
        currentToken_ = peekToken_;
        peekToken_ = lexer_.tryNextToken();
    }


    inline void Parser::expectCurrentTokenType(Lexer::TokenType type) {
        if (currentToken_.type != type) {
            throw ParseError("Encountered Unexpected token! Expected "
                                + Lexer::stringify(type)
                                + ", received "
                                + stringify(currentToken_.type)
                                + ".");
        }
    }


    inline void Parser::expectPeekTokenType(Lexer::TokenType type) {
        if (peekToken_.type != type) {
            throw ParseError("Encountered Unexpected token! Expected "
                                + Lexer::stringify(type)
                                + ", received "
                                + stringify(peekToken_.type)
                                + ".");
        }
    }


    inline void Parser::expectedPrefixOperatorButGot(Lexer::TokenType type) {
        throw ParseError("Expected prefix operator but got " + Lexer::stringify(type) + ".");
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
            case Lexer::TokenType::RETURN:
                return parseReturnStatement();
            default:
                return parseExpressionStatement();
        }
    }


    LetStatementPtr Parser::parseLetStatement() {
        LetStatementPtr letPtr = std::make_unique<LetStatement>();

        // Let Statement starts with keyword 'let' followed by an identifier
        expectCurrentTokenType(Lexer::TokenType::LET);
        expectPeekTokenType(Lexer::TokenType::IDENT);
        nextToken();
        // currentToken_ now holds the identifier

        Identifier* rawIdentPtr = static_cast<Identifier*>(parseIdentifier().release());
        letPtr->identifier_ = IdentifierPtr(rawIdentPtr);
        expectPeekTokenType(Lexer::TokenType::ASSIGN);

        nextToken();
        nextToken();
        // currentToken_ now holds the first token of the rhs expression

        letPtr->value_ = parseExpression(OperatorPrecedence::LOWEST);

        expectPeekTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();
        // currentToken_ now holds the semicolon

        return letPtr;
    }


    ReturnStatementPtr Parser::parseReturnStatement() {
        ReturnStatementPtr returnStmntPtr = std::make_unique<ReturnStatement>();

        expectCurrentTokenType(Lexer::TokenType::RETURN);
        nextToken();
        // currentToken_ now holds the first token of the expression to be returned

        returnStmntPtr->value_ = parseExpression(OperatorPrecedence::LOWEST);

        expectPeekTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();
        // currentToken_ now holds the semicolon

        return returnStmntPtr;
    }


    ExpressionStatementPtr Parser::parseExpressionStatement() {
        ExpressionStatementPtr exprStmntPtr = std::make_unique<ExpressionStatement>();

        exprStmntPtr->value_ = parseExpression(OperatorPrecedence::LOWEST);

        expectPeekTokenType(Lexer::TokenType::SEMICOLON);
        nextToken();
        // currentToken_ now holds the semicolon

        return exprStmntPtr;
    }


    ExpressionPtr Parser::parseExpression(OperatorPrecedence prec) {
        if (! prefixParseFns_.contains(currentToken_.type)) {
            expectedPrefixOperatorButGot(currentToken_.type);
        }

        const auto& prefixParseFn = prefixParseFns_.at(currentToken_.type);
        ExpressionPtr leftExprPtr = prefixParseFn();

        while (prec < getOperatorPrecedence(peekToken_.type)) {
            if (! infixParseFns_.contains(peekToken_.type)) {
                return leftExprPtr;
            }

            const auto& infixParseFn = infixParseFns_.at(peekToken_.type);
            nextToken();
            // currentToken_ now holds the infix operator token

            leftExprPtr = infixParseFn(std::move(leftExprPtr));
        }

        return leftExprPtr;
    }


    ExpressionPtr Parser::parsePrefixExpression() {
        PrefixExpressionPtr prefixExprPtr = std::make_unique<PrefixExpression>();

        prefixExprPtr->operatorLiteral_ = currentToken_.literal;
        nextToken();

        prefixExprPtr->right_ = parseExpression(OperatorPrecedence::PREFIX);

        return prefixExprPtr;
    }


    ExpressionPtr Parser::parseGroupedExpression() {
        expectCurrentTokenType(Lexer::TokenType::LPAREN);
        nextToken();
        // currentToken_ now holds the first token of the grouped expression

        auto expPtr = parseExpression(OperatorPrecedence::LOWEST);

        expectPeekTokenType(Lexer::TokenType::RPAREN);
        nextToken();
        // currentToken_ now holds the closing parenthesis

        return expPtr;
    }


    ExpressionPtr Parser::parseInfixExpression(ExpressionPtr left) {
        InfixExpressionPtr exprPtr = std::make_unique<InfixExpression>();
        exprPtr->operatorLiteral_ = currentToken_.literal;
        exprPtr->left_  = std::move(left);
        // left == nullptr, from here
        OperatorPrecedence precedence = getOperatorPrecedence(currentToken_.type);
        nextToken();
        // currentToken_ is now on the first token of the right side expression

        exprPtr->right_ = parseExpression(precedence);

        return exprPtr;
    }


    ExpressionPtr Parser::parseIdentifier() {
        expectCurrentTokenType(Lexer::TokenType::IDENT);
        IdentifierPtr identPtr = std::make_unique<Identifier>(std::move(currentToken_.literal));
        return identPtr;
    }

    ExpressionPtr Parser::parseIntegerLiteral() {
        expectCurrentTokenType(Lexer::TokenType::INT);
        try {
            int64_t parsedValue = std::stoll(currentToken_.literal);
            IntegerLiteralPtr intLitPtr = std::make_unique<IntegerLiteral>(parsedValue);
            return intLitPtr;
        } catch (const std::invalid_argument& exc) {
            throw ParseError("Could not parse integer literal " + currentToken_.literal + ". Details are:" + exc.what());
        }
    }


    ExpressionPtr Parser::parseBooleanLiteral() {
        BooleanLiteralPtr boolPtr = std::make_unique<BooleanLiteral>(currentToken_.type == Lexer::TokenType::TRUE);
        return boolPtr;
    }


}
