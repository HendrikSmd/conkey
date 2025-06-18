#include "conkey/parser/ast/expressions/call_expression.hpp"
#include <cstddef>

namespace Conkey::Parser {

    void CallExpression::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "CallExpression:" << std::endl;
        ss << std::string((depth + 1) * 2, ' ') << "CalledFunction:" << std::endl;
        function_->toString(ss, depth + 2);
        if (!arguments_.empty()) {
            ss << std::endl;
        }
        for (size_t i = 0U; i < arguments_.size(); i++) {
            ss << std::string((depth + 1) * 2, ' ') << "Argument " << i << ":" << std::endl;
            arguments_[i]->toString(ss, depth + 2);
            if (i < arguments_.size()-1) {
                ss << std::endl;
            }
        }
    }


}
