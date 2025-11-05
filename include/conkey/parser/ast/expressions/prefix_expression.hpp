#ifndef CONKEY_PARSER_PREFIX_EXPRESSION_HPP
#define CONKEY_PARSER_PREFIX_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include <memory>
#include <string>

namespace Conkey::Parser {

    enum class PrefixOperator {
        BANG,
        MINUS
    };

    std::string to_string(const PrefixOperator& op);

    class PrefixExpression : public Expression {
        public:
        ~PrefixExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;

        PrefixOperator operator_;
        ExpressionPtr right_;
    };

    using PrefixExpressionPtr = std::unique_ptr<PrefixExpression>;

}

#endif // CONKEY_PARSER_PREFIX_EXPRESSION_HPP
