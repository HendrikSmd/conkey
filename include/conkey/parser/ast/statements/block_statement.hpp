#ifndef CONKEY_PARSER_BLOCK_STATEMENT_HPP
#define CONKEY_PARSER_BLOCK_STATEMENT_HPP

#include <vector>
#include <sstream>
#include <memory>
#include "conkey/parser/ast/ast_base.hpp"

namespace Conkey::Parser {

    /*
     * {
     *      <statement>;
     *          ...
     *      <statement>;
     * }
     */
    class BlockStatement : Statement {
        public:
        ~BlockStatement() override = default;

        void toString(std::stringstream& ss, int depth = 0) override;

        std::vector<StatementPtr> statements_;
    };

    using BlockStatementPtr = std::unique_ptr<BlockStatement>;

}

#endif // CONKEY_PARSER_BLOCK_STATEMENT_HPP
