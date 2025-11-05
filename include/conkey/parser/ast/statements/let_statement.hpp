#ifndef CONKEY_PARSER_LET_STATEMENT_HPP
#define CONKEY_PARSER_LET_STATEMENT_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"

namespace Conkey::Parser {

    class LetStatement : public Statement {
        public:
        ~LetStatement() override = default;
        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;

        IdentifierPtr identifier_;
        ExpressionPtr value_;
    };

    using LetStatementPtr = std::unique_ptr<LetStatement>;

}

#endif // CONKEY_PARSER_LET_STATEMENT_HPP
