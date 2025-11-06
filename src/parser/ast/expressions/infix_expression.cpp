#include "conkey/parser/ast/expressions/infix_expression.hpp"

namespace Conkey::Parser {

    void InfixExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "InfixExpression: (Operator='" + to_string(operator_) + "')\n";
        left_->toString(ss, depth + 1);
        ss << "\n";
        right_->toString(ss, depth + 1);
    }

    std::string to_string(const InfixOperator& op) {
        switch(op) {
            case InfixOperator::ADD:
                return "+";
            case InfixOperator::MINUS:
                return "-";
            case InfixOperator::ASTERISK:
                return "*";
            case InfixOperator::SLASH:
                return "/";
            case InfixOperator::GREATER_THAN:
                return ">";
            case InfixOperator::LESS_THAN:
                return "<";
            case InfixOperator::EQUAL:
                return "==";
            case InfixOperator::NOT_EQUAL:
                return "!=";
            default:
                return "";
        }
    }

    Interpret::ValuePtr InfixExpression::accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) {
        return visitor.visitInfixExpression(*this);
    }


}
