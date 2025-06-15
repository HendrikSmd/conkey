#include "conkey/parser/ast/expressions/if_expression.hpp"

namespace Conkey::Parser {

    void IfExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "IfExpression:\n";
        condition_->toString(ss, depth + 1);
        ss << "\n";
        consequence_->toString(ss, depth + 1);
        if (alternative_ != nullptr) {
            ss << "\n";
            alternative_->toString(ss, depth + 1);
        }
    }


}
