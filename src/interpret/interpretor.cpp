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
        ValuePtr returnValue;
        for (const auto& statement : programRef.statements_) {
            returnValue = statement->accept(*this);
        }
        return returnValue;
    }

    ValuePtr Interpretor::visitBooleanLiteral(Parser::BooleanLiteral& expRef) {
        return expRef.value_ ? this->TRUE_VALUE_PTR : this->FALSE_VALUE_PTR;
    }

    ValuePtr Interpretor::visitCallExpression(Parser::CallExpression& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitFunctionLiteral(Parser::FunctionLiteral& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitIdentifierExpression(Parser::Identifier& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitIfExpression(Parser::IfExpression& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitInfixExpression(Parser::InfixExpression& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitIntegerLiteral(Parser::IntegerLiteral& expRef) {
        return std::make_shared<IntegerValue>(expRef.value_);
    }

    ValuePtr Interpretor::visitPrefixExpression(Parser::PrefixExpression& expRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitBlockStatement(Parser::BlockStatement& stmntRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitExpressionStatement(Parser::ExpressionStatement& stmntRef) {
        return stmntRef.value_->accept(*this);
    }

    ValuePtr Interpretor::visitLetStatement(Parser::LetStatement& stmntRef) {
        return this->NULL_VALUE_PTR;
    }

    ValuePtr Interpretor::visitReturnStatement(Parser::ReturnStatement& stmntRef) {
        return this->NULL_VALUE_PTR;
    }

}
