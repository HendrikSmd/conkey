#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ostream>
#include <sstream>
#include <vector>
#include "conkey/parser/parser.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;


const std::vector<std::string> EXPECTED_LET_STATEMENT_ASTS = {
R"(Program
  Let
    Identifier: x
    InfixExpression: (Operator='+')
      Integer: 2
      Integer: 2
)",
R"(Program
  Let
    Identifier: y
    Boolean: True
)",
R"(Program
  Let
    Identifier: name
    PrefixExpression: (Operator='-')
      Identifier: a
)"
};

TEST(ParserTest, LetStatementTest) {
    const std::vector<std::string> testExpressions = {
        "let x = 2 + 2;",
        "let y = true;",
        "let name = -a;"
    };
    std::vector<std::string> received;
    for (const auto& testExpr : testExpressions) {
        std::istringstream input(testExpr);
        Lexer lexer(input, "baz");
        Parser parser(lexer);

        ProgramPtr pPtr = parser.parseProgram();
        std::stringstream ss;
        pPtr->toString(ss);
        std::cout << ss.str() << std::endl;
        received.push_back(ss.str());
    };

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_LET_STATEMENT_ASTS));
}

const std::vector<std::string> EXPECTED_IF_STATEMENT_ASTS = {
R"(Program
  Expression Statement
    IfExpression:
      InfixExpression: (Operator='<')
        Identifier: x
        Identifier: y
      BlockStatement:
        Expression Statement
          Identifier: x
)",
R"(Program
  Expression Statement
    IfExpression:
      InfixExpression: (Operator='<')
        Identifier: x
        Identifier: y
      BlockStatement:
        Expression Statement
          Identifier: x
      BlockStatement:
        Expression Statement
          Identifier: y
)"
};


TEST(ParserTest, IfStatementTest) {
    const std::vector<std::string> testExpressions = {
        "if (x < y) { x; };",
        "if (x < y) { x; } else { y; };",
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_IF_STATEMENT_ASTS));
}
