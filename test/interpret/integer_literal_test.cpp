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

TEST(InterpretorTest, IntegerLiteralTest1) {
    std::string testExpression = "0;";
    Interpretor interpretor;

    std::istringstream input(testExpression);
    Lexer lexer(input, "baz");
    Parser parser(lexer);
    ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
    ValuePtr returnValue = ePtr->accept(interpretor);

    EXPECT_EQ(returnValue->valueType(), ValueType::INTEGER_VALUE);
    auto castResult = dynamic_cast<IntegerValue*>(returnValue.get());
    EXPECT_TRUE(castResult);
    EXPECT_EQ(castResult->value_, 0);
}

TEST(InterpretorTest, IntegerLiteralTest2) {
    std::string testExpression = "42;";
    Interpretor interpretor;

    std::istringstream input(testExpression);
    Lexer lexer(input, "baz");
    Parser parser(lexer);
    ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
    ValuePtr returnValue = ePtr->accept(interpretor);

    EXPECT_EQ(returnValue->valueType(), ValueType::INTEGER_VALUE);
    auto castResult = dynamic_cast<IntegerValue*>(returnValue.get());
    EXPECT_TRUE(castResult);
    EXPECT_EQ(castResult->value_, 42);
}

TEST(InterpretorTest, IntegerLiteralTest3) {
    std::string testExpression = "9223372036854775807;";
    Interpretor interpretor;

    std::istringstream input(testExpression);
    Lexer lexer(input, "baz");
    Parser parser(lexer);
    ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
    ValuePtr returnValue = ePtr->accept(interpretor);

    EXPECT_EQ(returnValue->valueType(), ValueType::INTEGER_VALUE);
    auto castResult = dynamic_cast<IntegerValue*>(returnValue.get());
    EXPECT_TRUE(castResult);
    EXPECT_EQ(castResult->value_, 9223372036854775807);
}
