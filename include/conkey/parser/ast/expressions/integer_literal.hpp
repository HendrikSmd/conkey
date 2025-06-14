#ifndef CONKEY_PARSER_INTEGER_LITERAL_HPP
#define CONKEY_PARSER_INTEGER_LITERAL_HPP

#include "conkey/parser/ast/ast_base.hpp"

#include <cstdint>

namespace Conkey::Parser {

    class IntegerLiteral : public Expression {
        public:
        IntegerLiteral(int64_t value);
        ~IntegerLiteral() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        int64_t value_;
    };

    using IntegerLiteralPtr = std::unique_ptr<IntegerLiteral>;

}

#endif // CONKEY_PARSER_INTEGER_LITERAL_HPP
