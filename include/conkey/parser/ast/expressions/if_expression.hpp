#ifndef CONKEY_PARSER_IF_EXPRESSION_HPP
#define CONKEY_PARSER_IF_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include "conkey/parser/ast/statements/block_statement.hpp"
#include <memory>

namespace Conkey::Parser {

    class IfExpression : public Expression {
        public:
        ~IfExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;


        ExpressionPtr condition_;
        BlockStatementPtr consequence_;
        BlockStatementPtr alternative_;
    };

    using IfExpressionPtr = std::unique_ptr<IfExpression>;

}

#endif // CONKEY_PARSER_IF_EXPRESSION_HPP
