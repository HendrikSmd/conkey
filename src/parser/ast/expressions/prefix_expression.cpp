#include "conkey/parser/ast/expressions/prefix_expression.hpp"

namespace Conkey::Parser {

    std::string to_string(const PrefixOperator &op) {
        switch(op) {
            case PrefixOperator::BANG:
             return "!";
            case PrefixOperator::MINUS:
             return "-";
        }

        return "";
    }

    void PrefixExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "PrefixExpression: (Operator='" + to_string(operator_) + "')\n";
        right_->toString(ss, depth + 1);
    }

    Interpret::ValuePtr PrefixExpression::accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) {
        return visitor.visitPrefixExpression(*this);
    }


}
