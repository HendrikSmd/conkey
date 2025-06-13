#ifndef CONKEY_PARSER_IDENTIFIER_EXPRESSION_HPP
#define CONKEY_PARSER_IDENTIFIER_EXPRESSION_HPP

#include "conkey/parser/ast/ast_base.hpp"

#include <string>

namespace Conkey::Parser {

    class Identifier : public Expression {
        public:
        Identifier(const std::string&& ident);
        ~Identifier() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        std::string value_;
    };

    using IdentifierPtr = std::unique_ptr<Identifier>;

}

#endif // CONKEY_PARSER_IDENTIFIER_EXPRESSION_HPP
