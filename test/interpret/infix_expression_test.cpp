#include <cstdint>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

#include "conkey/interpret/values.hpp"
#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/parser.hpp"
#include "conkey/interpret/interpretor.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;
using namespace Conkey::Interpret;

TEST(InterpretorTest, ArithmeticInfixWithNumericalOperators) {
    std::vector<std::string> testExpressions = {
        "5 + 5 + 5 + 5 - 10;",
        "2 * 2 * 2 * 2 * 2;",
        "-50 + 100 + -50;",
        "5 * 2 + 10;",
        "5 + 2 * 10;",
        "20 + 2 * -10;",
        "50 / 2 * 2 + 10;",
        "2 * (5 + 10);",
        "3 * 3 * 3 + 10;",
        "3 * (3 * 3) + 10;",
        "(5 + 10 * 2 + 15 / 3) * 2 + -10;"
    };

    std::vector<std::int64_t> expectedResults = {
        10, 32, 0, 20, 25, 0, 60, 30, 37, 37, 50
    };
    std::vector<std::int64_t> receivedResults;
    Interpretor interpretor;

    for (const auto& testExpression : testExpressions) {
        std::istringstream input(testExpression);
        Lexer lexer(input, "baz");
        Parser parser(lexer);
        ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
        ValuePtr returnValue = ePtr->accept(interpretor);
        EXPECT_EQ(returnValue->valueType(), ValueType::INTEGER_VALUE);
        auto castResult = dynamic_cast<IntegerValue*>(returnValue.get());
        EXPECT_TRUE(castResult);
        receivedResults.push_back(castResult->value_);
    }
    EXPECT_THAT(receivedResults, testing::ContainerEq(expectedResults));

}

TEST(InterpretorTest, ComparingInfixWithNumericalOperands) {
    std::vector<std::string> testExpressions = {
        "1 < 2;",
        "1 > 2;",
        "1 < 1;",
        "1 > 1;",
        "1 == 1;",
        "1 != 1;",
        "1 == 2;",
        "1 != 2;"
    };

    std::vector<bool> expectedResults = {
        true, false, false, false, true, false, false, true
    };
    std::vector<bool> receivedResults;
    Interpretor interpretor;

    for (const auto& testExpression : testExpressions) {
        std::istringstream input(testExpression);
        Lexer lexer(input, "baz");
        Parser parser(lexer);
        ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
        ValuePtr returnValue = ePtr->accept(interpretor);
        EXPECT_EQ(returnValue->valueType(), ValueType::BOOLEAN_VALUE);
        auto castResult = dynamic_cast<BooleanValue*>(returnValue.get());
        EXPECT_TRUE(castResult);
        receivedResults.push_back(castResult->value_);
    }
    EXPECT_THAT(receivedResults, testing::ContainerEq(expectedResults));

}

TEST(InterpretorTest, ComparingInfixWithBooleanOperands) {
    std::vector<std::string> testExpressions = {
        "true == true;",
        "false == false;",
        "true == false;",
        "true != false;",
        "false != true;",
        "(1 < 2) == true;",
        "(1 < 2) == false;",
        "(1 > 2) == true;",
        "(1 > 2) == false;"
    };

    std::vector<bool> expectedResults = {
        true, true, false, true, true, true, false, false, true
    };
    std::vector<bool> receivedResults;
    Interpretor interpretor;

    for (const auto& testExpression : testExpressions) {
        std::istringstream input(testExpression);
        Lexer lexer(input, "baz");
        Parser parser(lexer);
        ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
        ValuePtr returnValue = ePtr->accept(interpretor);
        EXPECT_EQ(returnValue->valueType(), ValueType::BOOLEAN_VALUE);
        auto castResult = dynamic_cast<BooleanValue*>(returnValue.get());
        EXPECT_TRUE(castResult);
        receivedResults.push_back(castResult->value_);
    }
    EXPECT_THAT(receivedResults, testing::ContainerEq(expectedResults));

}
