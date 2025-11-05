#ifndef CONKEY_INTERPRET_INTERPRETOR_HPP
#define CONKEY_INTERPRET_INTERPRETOR_HPP

#include "conkey/interpret/values.hpp"
#include "conkey/interpret/visitor.hpp"
#include <memory>

namespace Conkey::Interpret {

    struct Interpretor : public Visitor<ValuePtr> {
        public:
        ~Interpretor() override = default;

        virtual ValuePtr visitProgram(Parser::Program& programPtr) override;

        // Expressions
        virtual ValuePtr visitBooleanLiteral(Parser::BooleanLiteral& exprRef) override;
        virtual ValuePtr visitCallExpression(Parser::CallExpression& exprRef) override;
        virtual ValuePtr visitFunctionLiteral(Parser::FunctionLiteral& exprRef) override;
        virtual ValuePtr visitIdentifierExpression(Parser::Identifier& exprRef) override;
        virtual ValuePtr visitIfExpression(Parser::IfExpression& exprRef) override;
        virtual ValuePtr visitInfixExpression(Parser::InfixExpression& exprRef) override;
        virtual ValuePtr visitIntegerLiteral(Parser::IntegerLiteral& exprRef) override;
        virtual ValuePtr visitPrefixExpression(Parser::PrefixExpression& exprRef) override;

        // Statements
        virtual ValuePtr visitBlockStatement(Parser::BlockStatement& stmntRef) override;
        virtual ValuePtr visitExpressionStatement(Parser::ExpressionStatement& stmntRef) override;
        virtual ValuePtr visitLetStatement(Parser::LetStatement& stmntRef) override;
        virtual ValuePtr visitReturnStatement(Parser::ReturnStatement& stmntRef) override;

        private:
        const std::shared_ptr<BooleanValue>     TRUE_VALUE_PTR = std::make_shared<BooleanValue>(true);
        const std::shared_ptr<BooleanValue>     FALSE_VALUE_PTR = std::make_shared<BooleanValue>(false);
        const std::shared_ptr<NullValue>        NULL_VALUE_PTR = std::make_shared<NullValue>();
    };


}

#endif //CONKEY_INTERPRET_INTERPRETOR_HPP
