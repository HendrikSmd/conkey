#include "conkey/parser/ast/statements/return_statement.hpp"

namespace Conkey::Parser {

    void ReturnStatement::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Return\n";
        value_->toString(ss, depth + 1);
    }


}
