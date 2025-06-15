#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include "conkey/parser/parser.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;


const std::vector<std::string> EXPECTED_IDENTIFIER_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    Identifier: foobar
)",
R"(Program
  Expression Statement
    Identifier: x_z
)",
R"(Program
  Expression Statement
    Identifier: YYYYY
)"
};


TEST(ParserTest, IdentifierExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "foobar;",
        "x_z;",
        "YYYYY;"
    };
    std::vector<std::string> received;
    for (const auto& testExpr : testExpressions) {
        std::istringstream input(testExpr);
        Lexer lexer(input, "baz");
        Parser parser(lexer);

        ProgramPtr pPtr = parser.parseProgram();
        std::stringstream ss;
        pPtr->toString(ss);
        received.push_back(ss.str());
    };

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_IDENTIFIER_EXPRESSION_ASTS));
}


const std::vector<std::string> EXPECTED_INTEGER_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    Integer: 0
)",
R"(Program
  Expression Statement
    Integer: 1337
)",
R"(Program
  Expression Statement
    Integer: 9223372036854775807
)"
};


TEST(ParserTest, IntegerExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "0;",
        "1337;",
        "9223372036854775807;"
    };
    std::vector<std::string> received;
    for (const auto& testExpr : testExpressions) {
        std::istringstream input(testExpr);
        Lexer lexer(input, "baz");
        Parser parser(lexer);

        ProgramPtr pPtr = parser.parseProgram();
        std::stringstream ss;
        pPtr->toString(ss);
        received.push_back(ss.str());
    };

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_INTEGER_EXPRESSION_ASTS));
}


const std::vector<std::string> EXPECTED_PREFIX_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    PrefixExpression: (Operator='-')
      Identifier: x
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='-')
      Integer: 17
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='!')
      Identifier: y
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='!')
      Integer: 69
)"
};


TEST(ParserTest, PrefixExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "-x;",
        "-17;",
        "!y;",
        "!69;"
    };
    std::vector<std::string> received;
    for (const auto& testExpr : testExpressions) {
        std::istringstream input(testExpr);
        Lexer lexer(input, "baz");
        Parser parser(lexer);

        ProgramPtr pPtr = parser.parseProgram();
        std::stringstream ss;
        pPtr->toString(ss);
        received.push_back(ss.str());
    };

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_PREFIX_EXPRESSION_ASTS));
}
