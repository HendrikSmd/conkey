#include "conkey/parser/ast/expressions/infix_expression.hpp"

namespace Conkey::Parser {

    void InfixExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "InfixExpression: (Operator='" + operatorLiteral_ + "')\n";
        left_->toString(ss, depth + 1);
        ss << "\n";
        right_->toString(ss, depth + 1);
    }

    Interpret::ValuePtr InfixExpression::accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) {
        return visitor.visitInfixExpression(*this);
    }


}
