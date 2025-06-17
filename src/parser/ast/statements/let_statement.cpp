#include "conkey/parser/ast/statements/let_statement.hpp"

namespace Conkey::Parser {

    void LetStatement::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Let\n";
        identifier_->toString(ss, depth + 1);
        ss << "\n";
        value_->toString(ss, depth + 1);
    }


}
