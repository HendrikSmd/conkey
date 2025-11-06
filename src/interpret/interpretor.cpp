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
#include <cstdint>
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
        auto leftValue = expRef.left_->accept(*this);
        auto rightValue = expRef.right_->accept(*this);
        return applyInfixOperator(expRef.operator_, leftValue, rightValue);
    }

    ValuePtr Interpretor::visitIntegerLiteral(Parser::IntegerLiteral& expRef) {
        return std::make_shared<IntegerValue>(expRef.value_);
    }

    ValuePtr Interpretor::visitPrefixExpression(Parser::PrefixExpression& expRef) {
        auto rightValue = expRef.right_->accept(*this);
        switch (expRef.operator_) {
            case Parser::PrefixOperator::BANG:
                return this->applyBangPrefixOperator(rightValue);
            case Parser::PrefixOperator::MINUS:
                return this->applyMinusPrefixOperator(rightValue);
        }

        return NULL_VALUE_PTR;
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

    ValuePtr Interpretor::applyBangPrefixOperator(const ValuePtr& vPtr) const {
        switch(vPtr->valueType()) {
            case ValueType::BOOLEAN_VALUE:
                return static_cast<BooleanValue*>(vPtr.get())->value_ ? FALSE_VALUE_PTR : TRUE_VALUE_PTR;
            case ValueType::INTEGER_VALUE:
                return FALSE_VALUE_PTR;
            case ValueType::NULL_VALUE:
                return TRUE_VALUE_PTR;
        }

        return FALSE_VALUE_PTR;
    }

    ValuePtr Interpretor::applyMinusPrefixOperator(const ValuePtr& vPtr) const {
        std::int64_t value;
        switch(vPtr->valueType()) {
            case ValueType::INTEGER_VALUE:
                value = static_cast<IntegerValue*>(vPtr.get())->value_;
                return std::make_shared<IntegerValue>(-value);
            default:
                return NULL_VALUE_PTR;
        }
    }

    ValuePtr Interpretor::applyInfixOperator(
        const Parser::InfixOperator& op,
        const ValuePtr& leftValuePtr,
        const ValuePtr& rightValuePtr) const {
            if (leftValuePtr->valueType() == ValueType::INTEGER_VALUE && rightValuePtr->valueType() == ValueType::INTEGER_VALUE) {
                int64_t leftInt = static_cast<IntegerValue*>(leftValuePtr.get())->value_;
                int64_t rightInt = static_cast<IntegerValue*>(rightValuePtr.get())->value_;
                switch(op) {
                    case Conkey::Parser::InfixOperator::ADD:
                        return std::make_shared<IntegerValue>(leftInt + rightInt);
                    case Conkey::Parser::InfixOperator::MINUS:
                        return std::make_shared<IntegerValue>(leftInt - rightInt);
                    case Conkey::Parser::InfixOperator::ASTERISK:
                        return std::make_shared<IntegerValue>(leftInt * rightInt);
                    case Conkey::Parser::InfixOperator::SLASH:
                        return std::make_shared<IntegerValue>(leftInt / rightInt);
                    case Conkey::Parser::InfixOperator::GREATER_THAN:
                        return leftInt > rightInt ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                    case Conkey::Parser::InfixOperator::LESS_THAN:
                        return leftInt < rightInt ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                    case Conkey::Parser::InfixOperator::EQUAL:
                        return leftInt == rightInt ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                    case Conkey::Parser::InfixOperator::NOT_EQUAL:
                        return leftInt != rightInt ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                }
            } else if (leftValuePtr->valueType() == ValueType::BOOLEAN_VALUE && rightValuePtr->valueType() == ValueType::BOOLEAN_VALUE) {
                switch(op) {
                    case Conkey::Parser::InfixOperator::EQUAL:
                        return leftValuePtr == rightValuePtr ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                    case Conkey::Parser::InfixOperator::NOT_EQUAL:
                        return leftValuePtr != rightValuePtr ? TRUE_VALUE_PTR : FALSE_VALUE_PTR;
                }
            }

            return NULL_VALUE_PTR;
        }


}
