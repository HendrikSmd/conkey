#ifndef CONKEY_INTERPRET_VISTOR_HPP
#define CONKEY_INTERPRET_VISTOR_HPP

namespace Conkey::Parser {
    class Program;
    class BooleanLiteral;
    class CallExpression;
    class FunctionLiteral;
    class Identifier;
    class IfExpression;
    class InfixExpression;
    class IntegerLiteral;
    class PrefixExpression;

    class BlockStatement;
    class ExpressionStatement;
    class LetStatement;
    class ReturnStatement;
}

namespace Conkey::Interpret {

    template<typename ResultType>
    struct Visitor {
        virtual ~Visitor() = default;

        virtual ResultType visitProgram(Parser::Program& programPtr) = 0;

        // Expressions
        virtual ResultType visitBooleanLiteral(Parser::BooleanLiteral& exprRef) = 0;
        virtual ResultType visitCallExpression(Parser::CallExpression& exprRef) = 0;
        virtual ResultType visitFunctionLiteral(Parser::FunctionLiteral& exprRef) = 0;
        virtual ResultType visitIdentifierExpression(Parser::Identifier& exprRef) = 0;
        virtual ResultType visitIfExpression(Parser::IfExpression& exprRef) = 0;
        virtual ResultType visitInfixExpression(Parser::InfixExpression& exprRef) = 0;
        virtual ResultType visitIntegerLiteral(Parser::IntegerLiteral& exprRef) = 0;
        virtual ResultType visitPrefixExpression(Parser::PrefixExpression& exprRef) = 0;

        // Statements
        virtual ResultType visitBlockStatement(Parser::BlockStatement& stmntRef) = 0;
        virtual ResultType visitExpressionStatement(Parser::ExpressionStatement& stmntRef) = 0;
        virtual ResultType visitLetStatement(Parser::LetStatement& stmntRef) = 0;
        virtual ResultType visitReturnStatement(Parser::ReturnStatement& stmntRef) = 0;

    };

}

#endif // CONKEY_INTERPRET_VISTOR_HPP
