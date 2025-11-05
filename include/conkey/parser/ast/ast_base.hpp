#ifndef CONKEY_PARSER_AST_BASE_HPP
#define CONKEY_PARSER_AST_BASE_HPP

#include "conkey/interpret/values.hpp"
#include "conkey/interpret/visitor.hpp"
#include <sstream>
#include <memory>

namespace Conkey::Parser {



    class Node {
        public:
        virtual ~Node() = default;
        virtual void toString(std::stringstream& ss, int depth = 0) = 0;

        virtual Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) = 0;
    };

    class Statement : public Node {
        public:
        virtual ~Statement() = default;
    };

    class Expression : public Node {
        public:
        virtual ~Expression() = default;
    };

    using StatementPtr = std::unique_ptr<Statement>;
    using ExpressionPtr = std::unique_ptr<Expression>;

}

#endif // CONKEY_PARSER_AST_BASE_HPP
