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

TEST(InterpretorTest, BooleanLiteralTest1) {
    std::string testExpression = "true;";
    Interpretor interpretor;

    std::istringstream input(testExpression);
    Lexer lexer(input, "baz");
    Parser parser(lexer);
    ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
    ValuePtr returnValue = ePtr->accept(interpretor);

    EXPECT_EQ(returnValue->valueType(), ValueType::BOOLEAN_VALUE);
    auto castResult = dynamic_cast<BooleanValue*>(returnValue.get());
    EXPECT_TRUE(castResult);
    EXPECT_TRUE(castResult->value_);
}

TEST(InterpretorTest, BooleanLiteralTest2) {
    std::string testExpression = "false;";
    Interpretor interpretor;

    std::istringstream input(testExpression);
    Lexer lexer(input, "baz");
    Parser parser(lexer);
    ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
    ValuePtr returnValue = ePtr->accept(interpretor);

    EXPECT_EQ(returnValue->valueType(), ValueType::BOOLEAN_VALUE);
    auto castResult = dynamic_cast<BooleanValue*>(returnValue.get());
    EXPECT_TRUE(castResult);
    EXPECT_FALSE(castResult->value_);
}
