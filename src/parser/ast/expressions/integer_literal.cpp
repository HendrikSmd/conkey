#include "conkey/parser/ast/expressions/integer_literal.hpp"

namespace Conkey::Parser {

    IntegerLiteral::IntegerLiteral(int64_t value) :
        value_(value) {};

    void IntegerLiteral::toString(std::stringstream& ss, int depth) {
        ss << std::string(depth * 2, ' ') << "Integer: " << value_;
    }

}
