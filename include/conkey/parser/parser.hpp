#ifndef CONKEY_PARSER_PARSER_HPP
#define CONKEY_PARSER_PARSER_HPP

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include "conkey/parser/ast/statements/return_statement.hpp"
#include <stdexcept>
#include <map>
#include <functional>

namespace Conkey::Parser {

    enum class OperatorPrecedences : unsigned char {
        LOWEST = 1,
        EQUALS,
        LESSGREATER,
        SUM,
        PRODUCT,
        PREFIX,
        CALL
    };

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
        ExpressionPtr               parseExpression(OperatorPrecedences prec);
        ExpressionPtr               parsePrefixExpression();


        private:
        void                        nextToken();
        void                        expectTokenType(Lexer::TokenType tokenType);

        ExpressionPtr               parseIdentifier();
        ExpressionPtr               parseIntegerLiteral();


        std::map<Lexer::TokenType, PrefixExprParseFN> prefixParseFns_;
        std::map<Lexer::TokenType, InfixExprParseFN> infixParseFns_;
        Lexer::Token currentToken_;
        Lexer::Lexer& lexer_;
    };

    class ParseError : public std::runtime_error {
        public:
        ParseError(const std::string& msg);
    };

}


#endif // CONKEY_PARSER_PARSER_HPP
