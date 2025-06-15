#ifndef CONKEY_PARSER_INFIX_EXPRESSION_HPP
#define CONKEY_PARSER_INFIX_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include <memory>

namespace Conkey::Parser {

    class InfixExpression : public Expression {
        public:
        ~InfixExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        std::string operatorLiteral_;
        ExpressionPtr left_;
        ExpressionPtr right_;
    };

    using InfixExpressionPtr = std::unique_ptr<InfixExpression>;

}

#endif // CONKEY_PARSER_INFIX_EXPRESSION_HPP
