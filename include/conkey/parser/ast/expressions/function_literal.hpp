#ifndef CONKEY_PARSER_FUNCTION_LITERAL_HPP
#define CONKEY_PARSER_FUNCTION_LITERAL_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"
#include "conkey/parser/ast/statements/block_statement.hpp"
#include <memory>
#include <vector>

namespace Conkey::Parser {

    class FunctionLiteral : public Expression {
        public:
        ~FunctionLiteral() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        std::vector<IdentifierPtr> parameters_;
        BlockStatementPtr body_;
    };

    using FunctionLiteralPtr = std::unique_ptr<FunctionLiteral>;

}

#endif // CONKEY_PARSER_FUNCTION_LITERAL_HPP
