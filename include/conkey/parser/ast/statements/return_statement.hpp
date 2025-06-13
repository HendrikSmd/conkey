#ifndef CONKEY_PARSER_RETURN_STATEMENT_HPP
#define CONKEY_PARSER_RETURN_STATEMENT_HPP

#include "conkey/parser/ast/ast_base.hpp"

namespace Conkey::Parser {

    class ReturnStatement : public Statement {
        public:
        ~ReturnStatement() override = default;
        void toString(std::stringstream& ss, int depth = 0) override;

        ExpressionPtr value_;
    };

    using ReturnStatementPtr = std::unique_ptr<ReturnStatement>;

}

#endif // CONKEY_PARSER_RETURN_STATEMENT_HPP
