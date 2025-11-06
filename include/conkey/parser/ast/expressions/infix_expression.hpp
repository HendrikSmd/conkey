#ifndef CONKEY_PARSER_INFIX_EXPRESSION_HPP
#define CONKEY_PARSER_INFIX_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include <memory>

namespace Conkey::Parser {

    enum class InfixOperator {
        ADD, MINUS, ASTERISK, SLASH, GREATER_THAN, LESS_THAN, EQUAL, NOT_EQUAL
    };

    std::string to_string(const InfixOperator& op);

    class InfixExpression : public Expression {
        public:
        ~InfixExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;

        InfixOperator operator_;
        ExpressionPtr left_;
        ExpressionPtr right_;
    };

    using InfixExpressionPtr = std::unique_ptr<InfixExpression>;

}

#endif // CONKEY_PARSER_INFIX_EXPRESSION_HPP
