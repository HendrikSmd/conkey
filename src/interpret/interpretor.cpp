#include "conkey/interpret/interpretor.hpp"
#include "conkey/interpret/values.hpp"
#include "conkey/parser/ast/expressions/boolean_literal.hpp"
#include "conkey/parser/ast/expressions/call_expression.hpp"
#include "conkey/parser/ast/expressions/function_literal.hpp"
#include "conkey/parser/ast/expressions/identifier_expression.hpp"
#include "conkey/parser/ast/expressions/if_expression.hpp"
#include "conkey/parser/ast/expressions/infix_expression.hpp"
#include "conkey/parser/ast/expressions/integer_literal.hpp"
#include "conkey/parser/ast/expressions/prefix_expression.hpp"
#include "conkey/parser/ast/program.hpp"
#include "conkey/parser/ast/statements/block_statement.hpp"
#include "conkey/parser/ast/statements/expression_statement.hpp"
#include "conkey/parser/ast/statements/let_statement.hpp"
#include "conkey/parser/ast/statements/return_statement.hpp"
#include <memory>


namespace Conkey::Interpret {

    ValuePtr Interpretor::visitProgram(Parser::Program& programRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitBooleanLiteral(Parser::BooleanLiteral& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitCallExpression(Parser::CallExpression& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitFunctionLiteral(Parser::FunctionLiteral& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitIdentifierExpression(Parser::Identifier& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitIfExpression(Parser::IfExpression& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitInfixExpression(Parser::InfixExpression& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitIntegerLiteral(Parser::IntegerLiteral& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitPrefixExpression(Parser::PrefixExpression& expRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitBlockStatement(Parser::BlockStatement& stmntRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitExpressionStatement(Parser::ExpressionStatement& stmntRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitLetStatement(Parser::LetStatement& stmntRef) {
        return std::make_shared<NullValue>();
    }

    ValuePtr Interpretor::visitReturnStatement(Parser::ReturnStatement& stmntRef) {
        return std::make_shared<NullValue>();
    }

}
