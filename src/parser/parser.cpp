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
#include "conkey/parser/ast/expressions/call_expression.hpp"
#include "conkey/parser/ast/expressions/function_literal.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"
#include "conkey/parser/ast/expressions/if_expression.hpp"
#include "conkey/parser/ast/expressions/infix_expression.hpp"
#include "conkey/parser/ast/expressions/integer_literal.hpp"
#include "conkey/parser/ast/expressions/prefix_expression.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/statements/block_statement.hpp"
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
            {Lexer::TokenType::FALSE, [this](){ return parseBooleanLiteral(); }},       // false
            {Lexer::TokenType::LPAREN, [this](){ return parseGroupedExpression(); }},   // (
            {Lexer::TokenType::IF, [this](){ return parseIfExpression(); }},            // if ...
            {Lexer::TokenType::FUNCTION, [this](){ return parseFunctionLiteral(); }}    // fn (...) ...
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
            {Lexer::TokenType::LPAREN, [this](ExpressionPtr exp){ return parseCallExpression(std::move(exp)); }},
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


        switch(currentToken_.type) {
            case Lexer::TokenType::BANG:
                prefixExprPtr->operator_ = PrefixOperator::BANG;
                break;
            case Lexer::TokenType::MINUS:
                prefixExprPtr->operator_ = PrefixOperator::MINUS;
                break;
            default:
                throw new ParseError("Tried to parse a prefix expression with the unrecognized prefix operator" + currentToken_.literal);
        }
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
        switch(currentToken_.type) {
            case Lexer::TokenType::PLUS:
                exprPtr->operator_ = InfixOperator::ADD;
                break;
            case Lexer::TokenType::MINUS:
                exprPtr->operator_ = InfixOperator::MINUS;
                break;
            case Lexer::TokenType::ASTERISK:
                exprPtr->operator_ = InfixOperator::ASTERISK;
                break;
            case Lexer::TokenType::SLASH:
                exprPtr->operator_ = InfixOperator::SLASH;
                break;
            case Lexer::TokenType::GT:
                exprPtr->operator_ = InfixOperator::GREATER_THAN;
                break;
            case Lexer::TokenType::LT:
                exprPtr->operator_ = InfixOperator::LESS_THAN;
                break;
            case Lexer::TokenType::EQ:
                exprPtr->operator_ = InfixOperator::EQUAL;
                break;
            case Lexer::TokenType::NOT_EQ:
                exprPtr->operator_ = InfixOperator::NOT_EQUAL;
                break;
            default:
                throw new ParseError("Tried to parse an infix expression with the unrecognized infix operator" + currentToken_.literal);
        }
        exprPtr->left_  = std::move(left);
        // left == nullptr, from here
        OperatorPrecedence precedence = getOperatorPrecedence(currentToken_.type);
        nextToken();
        // currentToken_ is now on the first token of the right side expression

        exprPtr->right_ = parseExpression(precedence);

        return exprPtr;
    }


    ExpressionPtr Parser::parseIfExpression() {
        IfExpressionPtr ifExprPtr = std::make_unique<IfExpression>();
        ifExprPtr->alternative_ = nullptr;

        // currentToken_ is expected to be over 'if'
        expectCurrentTokenType(Lexer::TokenType::IF);
        expectPeekTokenType(Lexer::TokenType::LPAREN);

        nextToken();
        nextToken();

        // currentToken_ now holds the first token of the condition expression
        ifExprPtr->condition_ = parseExpression(OperatorPrecedence::LOWEST);
        // currentToken_ now holds the last token of the condition expression

        expectPeekTokenType(Lexer::TokenType::RPAREN);
        nextToken();
        // currentToken_ now holds ')'
        nextToken();
        // currentToken_ should now hold '{'

        ifExprPtr->consequence_ = parseBlockStatement();

        if (peekToken_.type != Lexer::TokenType::ELSE) {
            // Parsed if expression without else branch
            return ifExprPtr;
        }

        nextToken();
        // There is an else branch and currentToken_ holds 'else'
        nextToken();
        // currentToken_ should now hold '{'

        ifExprPtr->alternative_ = parseBlockStatement();

        return ifExprPtr;
    }


    BlockStatementPtr Parser::parseBlockStatement() {
        BlockStatementPtr blockStmntPtr = std::make_unique<BlockStatement>();

        expectCurrentTokenType(Lexer::TokenType::LBRACE);
        nextToken();
        // currentToken should now be on the first
        // token of the first statement in the block

        while (
            currentToken_.type != Lexer::TokenType::RBRACE &&
            currentToken_.type != Lexer::TokenType::END_OF_FILE) {
                blockStmntPtr->statements_.emplace_back(parseStatement());
                nextToken();
        }
        expectCurrentTokenType(Lexer::TokenType::RBRACE);

        return blockStmntPtr;
    }


    FunctionLiteralPtr Parser::parseFunctionLiteral() {
        FunctionLiteralPtr fnLitPtr = std::make_unique<FunctionLiteral>();
        expectCurrentTokenType(Lexer::TokenType::FUNCTION);
        nextToken();
        expectCurrentTokenType(Lexer::TokenType::LPAREN);
        nextToken();
        // currentToken_ should now be on the first parameter or
        // on ')' if there is no parameter

        while (currentToken_.type != Lexer::TokenType::RPAREN) {
            Identifier* rawIdentPtr = static_cast<Identifier*>(parseIdentifier().release());
            fnLitPtr->parameters_.emplace_back(rawIdentPtr);
            if (peekToken_.type != Lexer::TokenType::RPAREN) {
                expectPeekTokenType(Lexer::TokenType::COMMA);
                nextToken();
                // currentToken_ now holds the comma
            }
            nextToken();
        }

        expectPeekTokenType(Lexer::TokenType::LBRACE);
        nextToken();

        fnLitPtr->body_ = parseBlockStatement();

        return fnLitPtr;
    }


    ExpressionPtr Parser::parseCallExpression(ExpressionPtr function) {
        CallExpressionPtr callExpressionPtr = std::make_unique<CallExpression>();
        callExpressionPtr->function_ = std::move(function);
        expectCurrentTokenType(Lexer::TokenType::LPAREN);
        nextToken();

        while (currentToken_.type != Lexer::TokenType::RPAREN) {
            callExpressionPtr->arguments_.push_back(parseExpression(OperatorPrecedence::LOWEST));
            if (peekToken_.type != Lexer::TokenType::RPAREN) {
                expectPeekTokenType(Lexer::TokenType::COMMA);
                nextToken();
            }
            nextToken();
        }

        return callExpressionPtr;
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
