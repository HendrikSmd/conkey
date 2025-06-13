#ifndef CONKEY_PARSER_PARSER_HPP
#define CONKEY_PARSER_PARSER_HPP

#include "conkey/lexer/lexer.hpp"
#include "conkey/lexer/token.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include <stdexcept>

namespace Conkey::Parser {

    class Parser {
        public:
        Parser(Lexer::Lexer& lexer);

        ProgramPtr          parseProgram();

        private:
        void                nextToken();
        void                expectTokenType(Lexer::TokenType tokenType);

        StatementPtr        parseStatement();
        LetStatementPtr     parseLetStatement();
        IdentifierPtr       parseIdentifier();

        Lexer::Token currentToken_;
        Lexer::Lexer& lexer_;
    };

    class ParseError : public std::runtime_error {
        public:
        ParseError(const std::string& msg);
    };

}


#endif // CONKEY_PARSER_PARSER_HPP
