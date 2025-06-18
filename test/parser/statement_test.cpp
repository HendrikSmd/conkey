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


const std::vector<std::string> EXPECTED_FUNCTION_LITERAL_ASTS = {
R"(Program
  Expression Statement
    FunctionLiteral:
      Parameters: []
      BlockStatement:
        Return
          InfixExpression: (Operator='+')
            Integer: 3
            Integer: 4
)",
R"(Program
  Expression Statement
    FunctionLiteral:
      Parameters: [Identifier: x]
      BlockStatement:
        Return
          PrefixExpression: (Operator='!')
            Identifier: x
)",
R"(Program
  Expression Statement
    FunctionLiteral:
      Parameters: [Identifier: x, Identifier: foo, Identifier: bar]
      BlockStatement:
        Return
          InfixExpression: (Operator='+')
            InfixExpression: (Operator='+')
              Identifier: x
              Identifier: foo
            Identifier: bar
)"
};

TEST(ParserTest, FunctionliteralTest) {
    const std::vector<std::string> testExpressions = {
        "fn(){ return 3 + 4; };",
        "fn(x){ return !x; };",
        "fn(x, foo, bar){ return x + foo + bar; };"
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_FUNCTION_LITERAL_ASTS));
}


const std::vector<std::string> EXPECTED_CALL_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    CallExpression:
      CalledFunction:
        FunctionLiteral:
          Parameters: []
          BlockStatement:
            Return
              InfixExpression: (Operator='+')
                Integer: 3
                Integer: 4
)",
R"(Program
  Expression Statement
    CallExpression:
      CalledFunction:
        FunctionLiteral:
          Parameters: [Identifier: x]
          BlockStatement:
            Return
              PrefixExpression: (Operator='!')
                Identifier: x
      Argument 0:
        Boolean: True
)",
R"(Program
  Expression Statement
    CallExpression:
      CalledFunction:
        FunctionLiteral:
          Parameters: [Identifier: foo, Identifier: bar]
          BlockStatement:
            Return
              InfixExpression: (Operator='+')
                Identifier: foo
                Identifier: bar
      Argument 0:
        Integer: 10
      Argument 1:
        Integer: 20
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      CallExpression:
        CalledFunction:
          Identifier: bar
      CallExpression:
        CalledFunction:
          Identifier: foo
        Argument 0:
          Integer: 10
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='*')
      Integer: 5
      CallExpression:
        CalledFunction:
          Identifier: call
        Argument 0:
          Integer: 10
        Argument 1:
          InfixExpression: (Operator='+')
            Integer: 20
            Integer: 15
        Argument 2:
          CallExpression:
            CalledFunction:
              Identifier: bar
)"
};


TEST(ParserTest, CallExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "fn(){ return 3 + 4; }();",
        "fn(x){ return !x; }(true);",
        "fn(foo, bar){ return foo + bar; }(10,20);",
        "bar() + foo(10);",
        "5 * call(10, 20 + 15, bar());"
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_CALL_EXPRESSION_ASTS));
}
