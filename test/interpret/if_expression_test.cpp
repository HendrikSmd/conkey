#include <cstddef>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "conkey/interpret/values.hpp"
#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/parser.hpp"
#include "conkey/interpret/interpretor.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;
using namespace Conkey::Interpret;

TEST(InterpretorTest, ifExpressionTest) {
    std::vector<std::string> testExpressions = {
        "if (true) { 10; };",
        "if (false) { 10; };",
        "if (1) { 10; };",
        "if (1 < 2) {10;};",
        "if (1 > 2) {10;};",
        "if (1 > 2) {10;} else { 20;};",
        "if (1 < 2) {10;} else {20;};"
    };

    std::vector<std::string> expectedInspects = {
        "10", "null", "10", "10", "null", "20", "10"
    };

    std::vector<ValueType> expectedValueTypes = {
        ValueType::INTEGER_VALUE, ValueType::NULL_VALUE, ValueType::INTEGER_VALUE,
        ValueType::INTEGER_VALUE, ValueType::NULL_VALUE, ValueType::INTEGER_VALUE,
        ValueType::INTEGER_VALUE
    };

    Interpretor interpretor;

    for (std::size_t i=0; i < testExpressions.size(); i++) {
        std::istringstream input(testExpressions.at(i));
        Lexer lexer(input, "baz");
        Parser parser(lexer);
        ExpressionStatementPtr ePtr = parser.parseExpressionStatement();
        ValuePtr returnValue = ePtr->accept(interpretor);
        EXPECT_EQ(returnValue->valueType(), expectedValueTypes.at(i));
        EXPECT_EQ(returnValue->inspect(), expectedInspects.at(i));
    }

}
