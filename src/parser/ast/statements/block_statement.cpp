#include "conkey/parser/ast/statements/block_statement.hpp"

#include <string>
#include <sstream>

namespace Conkey::Parser {

    void BlockStatement::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "BlockStatement:";
        for (const auto& stmntPtr : statements_) {
            ss << "\n";
            stmntPtr->toString(ss, depth + 1);
        }
    }

}
