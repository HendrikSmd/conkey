#ifndef CONKEY_PARSER_PROGRAM_HPP
#define CONKEY_PARSER_PROGRAM_HPP

#include <vector>
#include <sstream>
#include <memory>
#include "conkey/interpret/values.hpp"
#include "conkey/interpret/visitor.hpp"
#include "conkey/parser/ast/ast_base.hpp"

namespace Conkey::Parser {

    class Program : Node {
        public:
        void toString(std::stringstream& ss, int depth = 0) override;

        Interpret::ValuePtr accept(Interpret::Visitor<Interpret::ValuePtr>& visitor) override;

        std::vector<StatementPtr> statements_;
    };

    using ProgramPtr = std::unique_ptr<Program>;

}

#endif // CONKEY_PARSER_PROGRAM_HPP
