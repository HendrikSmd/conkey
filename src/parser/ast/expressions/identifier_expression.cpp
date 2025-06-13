#include "conkey/parser/ast/expressions/identifier_expression.hpp"

namespace Conkey::Parser {

    Identifier::Identifier(const std::string&& ident) :
        value_(ident) {};

    void Identifier::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Identifier: " << value_;
    }

}
