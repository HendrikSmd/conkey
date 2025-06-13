#include "conkey/parser/ast/statements/expression_statement.hpp"

namespace Conkey::Parser {

    void ExpressionStatement::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Expression\n";
        value_->toString(ss, depth + 1);
    }


}
