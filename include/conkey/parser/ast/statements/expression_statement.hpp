#ifndef CONKEY_PARSER_EXPRESSION_STATEMENT_HPP
#define CONKEY_PARSER_EXPRESSION_STATEMENT_HPP

#include "conkey/parser/ast/ast_base.hpp"

namespace Conkey::Parser {

    class ExpressionStatement : public Statement {
        public:
        ~ExpressionStatement() override = default;
        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;

        ExpressionPtr value_;
    };

    using ExpressionStatementPtr = std::unique_ptr<ExpressionStatement>;

}

#endif // CONKEY_PARSER_EXPRESSION_STATEMENT_HPP
