#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ostream>
#include <sstream>
#include <vector>
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

const std::vector<std::string> EXPECTED_BOOLEAN_LITERAL_ASTS = {
R"(Program
  Expression Statement
    Boolean: True
)",
R"(Program
  Expression Statement
    Boolean: False
)"
};


TEST(ParserTest, BooleanLiteralTest) {
    const std::vector<std::string> testExpressions = {
        "true;",
        "false;",
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_BOOLEAN_LITERAL_ASTS));
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


const std::vector<std::string> EXPECTED_INFIX_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='-')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='*')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='/')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='>')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='<')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='==')
      Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='!=')
      Integer: 5
      Integer: 5
)"
};


TEST(ParserTest, InfixExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "5 + 5;",
        "5 - 5;",
        "5 * 5;",
        "5 / 5;",
        "5 > 5;",
        "5 < 5;",
        "5 == 5;",
        "5 != 5;"
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_INFIX_EXPRESSION_ASTS));
}

const std::vector<std::string> EXPECTED_COMBINED_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    InfixExpression: (Operator='*')
      PrefixExpression: (Operator='-')
        Identifier: a
      Identifier: b
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='!')
      PrefixExpression: (Operator='-')
        Identifier: a
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      InfixExpression: (Operator='+')
        Identifier: a
        Identifier: b
      Identifier: c
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='-')
      InfixExpression: (Operator='+')
        Identifier: a
        Identifier: b
      Identifier: c
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='*')
      InfixExpression: (Operator='*')
        Identifier: a
        Identifier: b
      Identifier: c
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='/')
      InfixExpression: (Operator='*')
        Identifier: a
        Identifier: b
      Identifier: c
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      Identifier: a
      InfixExpression: (Operator='/')
        Identifier: b
        Identifier: c
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='-')
      InfixExpression: (Operator='+')
        InfixExpression: (Operator='+')
          Identifier: a
          InfixExpression: (Operator='*')
            Identifier: b
            Identifier: c
        InfixExpression: (Operator='/')
          Identifier: d
          Identifier: e
      Identifier: f
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      Integer: 3
      Integer: 4
  Expression Statement
    InfixExpression: (Operator='*')
      PrefixExpression: (Operator='-')
        Integer: 5
      Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='==')
      InfixExpression: (Operator='>')
        Integer: 5
        Integer: 4
      InfixExpression: (Operator='<')
        Integer: 3
        Integer: 4
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='!=')
      InfixExpression: (Operator='<')
        Integer: 5
        Integer: 4
      InfixExpression: (Operator='>')
        Integer: 3
        Integer: 4
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='==')
      InfixExpression: (Operator='+')
        Integer: 3
        InfixExpression: (Operator='*')
          Integer: 4
          Integer: 5
      InfixExpression: (Operator='+')
        InfixExpression: (Operator='*')
          Integer: 3
          Integer: 1
        InfixExpression: (Operator='*')
          Integer: 4
          Integer: 5
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='==')
      InfixExpression: (Operator='+')
        Integer: 3
        InfixExpression: (Operator='*')
          Integer: 4
          Integer: 5
      InfixExpression: (Operator='+')
        InfixExpression: (Operator='+')
          Integer: 3
          Integer: 1
        InfixExpression: (Operator='*')
          Integer: 4
          Integer: 5
)"
};


TEST(ParserTest, CombinedExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "-a * b;",
        "!-a;",
        "a + b + c;",
        "a + b - c;",
        "a * b * c;",
        "a * b / c;",
        "a + b / c;",
        "a + b * c + d / e - f;",
        "3 + 4; -5 * 5;",
        "5 > 4 == 3 < 4;",
        "5 < 4 != 3 > 4;",
        "3 + 4 * 5 == 3 * 1 + 4 * 5;",
        "3 + 4 * 5 == 3 + 1 + 4 * 5;"
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_COMBINED_EXPRESSION_ASTS));
}


const std::vector<std::string> EXPECTED_GROUPED_EXPRESSION_ASTS = {
R"(Program
  Expression Statement
    InfixExpression: (Operator='+')
      InfixExpression: (Operator='+')
        Integer: 1
        InfixExpression: (Operator='+')
          Integer: 2
          Integer: 3
      Integer: 4
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='*')
      InfixExpression: (Operator='+')
        Integer: 5
        Integer: 5
      Integer: 2
)",
R"(Program
  Expression Statement
    InfixExpression: (Operator='/')
      Integer: 2
      InfixExpression: (Operator='+')
        Integer: 5
        Integer: 5
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='-')
      InfixExpression: (Operator='+')
        Integer: 5
        Integer: 5
)",
R"(Program
  Expression Statement
    PrefixExpression: (Operator='!')
      InfixExpression: (Operator='==')
        Boolean: True
        Boolean: True
)"
};


TEST(ParserTest, GroupedExpressionTest) {
    const std::vector<std::string> testExpressions = {
        "1 + (2 + 3) + 4;",
        "(5 + 5) * 2;",
        "2 / (5 + 5);",
        "-(5 + 5);",
        "!(true == true);"
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

    EXPECT_THAT(received, testing::ContainerEq(EXPECTED_GROUPED_EXPRESSION_ASTS));
}
