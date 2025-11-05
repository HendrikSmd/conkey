#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "conkey/interpret/values.hpp"
#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/parser.hpp"
#include "conkey/interpret/interpretor.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;
using namespace Conkey::Interpret;

TEST(InterpretorTest, IntegerLiteralTest) {
    const std::vector<std::string> testExpressions = {
        "1;",
        "10;",
        "-20;"
    };
    std::vector<ValuePtr> received;
    Interpretor interpretor;

    for (const auto& testExpr : testExpressions) {
        std::istringstream input(testExpr);
        Lexer lexer(input, "baz");
        Parser parser(lexer);

        ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
        received.push_back(ePtr->accept(interpretor));
    };
}
