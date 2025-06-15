#ifndef CONKEY_PARSER_PARSER_HPP
#define CONKEY_PARSER_PARSER_HPP

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/statements/block_statement.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include "conkey/parser/ast/statements/return_statement.hpp"
#include <stdexcept>
#include <map>
#include <functional>

namespace Conkey::Parser {

    enum class OperatorPrecedence : unsigned char {
        LOWEST = 1,
        EQUALS,
        LESSGREATER,
        SUM,
        PRODUCT,
        PREFIX,
        CALL
    };

    const std::map<Lexer::TokenType, OperatorPrecedence> precedences = {
        {Lexer::TokenType::EQ,          OperatorPrecedence::EQUALS},
        {Lexer::TokenType::NOT_EQ,      OperatorPrecedence::EQUALS},
        {Lexer::TokenType::LT,          OperatorPrecedence::LESSGREATER},
        {Lexer::TokenType::GT,          OperatorPrecedence::LESSGREATER},
        {Lexer::TokenType::PLUS,        OperatorPrecedence::SUM},
        {Lexer::TokenType::MINUS,       OperatorPrecedence::SUM},
        {Lexer::TokenType::SLASH,       OperatorPrecedence::PRODUCT},
        {Lexer::TokenType::ASTERISK,    OperatorPrecedence::PRODUCT}
    };


    OperatorPrecedence getOperatorPrecedence(Lexer::TokenType type);


    class Parser {

        using PrefixExprParseFN = std::function<ExpressionPtr()>;
        using InfixExprParseFN = std::function<ExpressionPtr(ExpressionPtr)>;

        public:
        Parser(Lexer::Lexer& lexer);

        ProgramPtr                  parseProgram();
        StatementPtr                parseStatement();
        LetStatementPtr             parseLetStatement();
        ReturnStatementPtr          parseReturnStatement();
        ExpressionStatementPtr      parseExpressionStatement();

        // Pratt Expression Parsing
        ExpressionPtr               parseExpression(OperatorPrecedence prec);
        ExpressionPtr               parsePrefixExpression();
        ExpressionPtr               parseGroupedExpression();
        ExpressionPtr               parseInfixExpression(ExpressionPtr left);
        ExpressionPtr               parseIfExpression();
        BlockStatementPtr           parseBlockStatement();


        private:
        inline void                 nextToken();
        inline void                 expectCurrentTokenType(Lexer::TokenType tokenType);
        inline void                 expectPeekTokenType(Lexer::TokenType tokenType);

        inline void                 expectedPrefixOperatorButGot(Lexer::TokenType tokenType);

        ExpressionPtr               parseIdentifier();
        ExpressionPtr               parseIntegerLiteral();
        ExpressionPtr               parseBooleanLiteral();


        std::map<Lexer::TokenType, PrefixExprParseFN> prefixParseFns_;
        std::map<Lexer::TokenType, InfixExprParseFN> infixParseFns_;

        Lexer::Token currentToken_;
        Lexer::Token peekToken_;

        Lexer::Lexer& lexer_;
    };

    class ParseError : public std::runtime_error {
        public:
        ParseError(const std::string& msg);
    };

}


#endif // CONKEY_PARSER_PARSER_HPP
