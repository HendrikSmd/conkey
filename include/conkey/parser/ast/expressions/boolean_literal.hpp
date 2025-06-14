#ifndef CONKEY_PARSER_BOOLEAN_LITERAL_HPP
#define CONKEY_PARSER_BOOLEAN_LITERAL_HPP

#include "conkey/parser/ast/ast_base.hpp"

namespace Conkey::Parser {

    class BooleanLiteral : public Expression {
        public:
        BooleanLiteral(bool value);
        ~BooleanLiteral() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        bool value_;
    };

    using BooleanLiteralPtr = std::unique_ptr<BooleanLiteral>;

}

#endif // CONKEY_PARSER_BOOLEAN_LITERAL_HPP
