#ifndef CONKEY_PARSER_AST_BASE_HPP
#define CONKEY_PARSER_AST_BASE_HPP

#include <sstream>
#include <memory>

namespace Conkey::Parser {

    class Node {
        public:
        virtual ~Node() = default;
        virtual void toString(std::stringstream& ss, int depth = 0) = 0;
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
