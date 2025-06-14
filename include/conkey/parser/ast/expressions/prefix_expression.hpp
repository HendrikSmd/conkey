#ifndef CONKEY_PARSER_PREFIX_EXPRESSION_HPP
#define CONKEY_PARSER_PREFIX_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include <memory>

namespace Conkey::Parser {

    class PrefixExpression : public Expression {
        public:
        ~PrefixExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        std::string operatorLiteral_;
        ExpressionPtr right_;
    };

    using PrefixExpressionPtr = std::unique_ptr<PrefixExpression>;

}

#endif // CONKEY_PARSER_PREFIX_EXPRESSION_HPP
