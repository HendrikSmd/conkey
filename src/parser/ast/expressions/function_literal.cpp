#include "conkey/parser/ast/expressions/function_literal.hpp"
#include <cstddef>

namespace Conkey::Parser {

    void FunctionLiteral::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "FunctionLiteral:" << std::endl;
        ss << std::string((depth + 1) * 2, ' ') << "Parameters: [";
        for (size_t i = 0U; i < parameters_.size(); i++) {
            parameters_[i]->toString(ss);
            if (i < parameters_.size()-1) {
                ss << ", ";
            }
        }
        ss << "]" << std::endl;
        body_->toString(ss, depth + 1);
    }

    Interpret::ValuePtr FunctionLiteral::accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) {
        return visitor.visitFunctionLiteral(*this);
    }


}
