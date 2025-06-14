#include "conkey/parser/ast/expressions/boolean_literal.hpp"

namespace Conkey::Parser {

    BooleanLiteral::BooleanLiteral(bool value) :
        value_(value) {};

    void BooleanLiteral::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Boolean: " << (value_ ? "True" : "False");
    }

}
