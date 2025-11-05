#include "conkey/parser/ast/expressions/prefix_expression.hpp"

namespace Conkey::Parser {

    void PrefixExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "PrefixExpression: (Operator='" + operatorLiteral_ + "')\n";
        right_->toString(ss, depth + 1);
    }

    Interpret::ValuePtr PrefixExpression::accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) {
        return visitor.visitPrefixExpression(*this);
    }


}
