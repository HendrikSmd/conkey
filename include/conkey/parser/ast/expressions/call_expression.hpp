#ifndef CONKEY_PARSER_CALL_EXPRESSION_HPP
#define CONKEY_PARSER_CALL_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"
#include <memory>
#include <vector>

namespace Conkey::Parser {

    class CallExpression : public Expression {
        public:
        ~CallExpression() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        ExpressionPtr function_;    // IdentifierPtr or FunctionLiteralPtr
        std::vector<ExpressionPtr> arguments_;
    };

    using CallExpressionPtr = std::unique_ptr<CallExpression>;

}

#endif // CONKEY_PARSER_CALL_EXPRESSION_HPP
