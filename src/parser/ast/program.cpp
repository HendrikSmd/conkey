#include "conkey/parser/ast/program.hpp"

#include <string>
#include <sstream>

namespace Conkey::Parser {

    void Program::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Program";
        for (const auto& stmntPtr : statements_) {
            stmntPtr->toString(ss, depth + 1);
            ss << "\n";
        }
    }

}
