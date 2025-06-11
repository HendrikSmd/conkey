#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "conkey/lexer/token.hpp"
#include "conkey/lexer/lexer.hpp"
#include <vector>
#include <sstream>
#include <random>
#include <array>

const char* MINIMAL_TOKEN_TEXT_A = R"(
    { , } ( ) * / + - == != < > = let fn if else true false 123 abc
)";

TEST(LexerTest, MinimalTokenTestA) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::ASTERISK, "*"},
        {Conkey::Lexer::TokenType::SLASH, "/"},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::MINUS, "-"},
        {Conkey::Lexer::TokenType::EQ, "=="},
        {Conkey::Lexer::TokenType::NOT_EQ, "!="},
        {Conkey::Lexer::TokenType::LT, "<"},
        {Conkey::Lexer::TokenType::GT, ">"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::FUNCTION, "fn"},
        {Conkey::Lexer::TokenType::IF, "if"},
        {Conkey::Lexer::TokenType::ELSE, "else"},
        {Conkey::Lexer::TokenType::TRUE, "true"},
        {Conkey::Lexer::TokenType::FALSE, "false"},
        {Conkey::Lexer::TokenType::INT, "123"},
        {Conkey::Lexer::TokenType::IDENT, "abc"},
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(MINIMAL_TOKEN_TEXT_A);
    Conkey::Lexer::Lexer lexer(input, "minimal_token_text_a");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* MINIMAL_TOKEN_TEXT_B = R"(
    } fn ( * else + { == let 42 false != ) / if true - abc , = ;
)";

TEST(LexerTest, MinimalTokenTestB) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::FUNCTION, "fn"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::ASTERISK, "*"},
        {Conkey::Lexer::TokenType::ELSE, "else"},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::EQ, "=="},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::INT, "42"},
        {Conkey::Lexer::TokenType::FALSE, "false"},
        {Conkey::Lexer::TokenType::NOT_EQ, "!="},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SLASH, "/"},
        {Conkey::Lexer::TokenType::IF, "if"},
        {Conkey::Lexer::TokenType::TRUE, "true"},
        {Conkey::Lexer::TokenType::MINUS, "-"},
        {Conkey::Lexer::TokenType::IDENT, "abc"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(MINIMAL_TOKEN_TEXT_B);
    Conkey::Lexer::Lexer lexer(input, "minimal_token_text_b");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* MINIMAL_TOKEN_TEXT_C = R"(
    { , ; ( ) } = + == - != * / let true fn false if else 99 xyz 123 }
)";

TEST(LexerTest, MinimalTokenTestC) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::EQ, "=="},
        {Conkey::Lexer::TokenType::MINUS, "-"},
        {Conkey::Lexer::TokenType::NOT_EQ, "!="},
        {Conkey::Lexer::TokenType::ASTERISK, "*"},
        {Conkey::Lexer::TokenType::SLASH, "/"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::TRUE, "true"},
        {Conkey::Lexer::TokenType::FUNCTION, "fn"},
        {Conkey::Lexer::TokenType::FALSE, "false"},
        {Conkey::Lexer::TokenType::IF, "if"},
        {Conkey::Lexer::TokenType::ELSE, "else"},
        {Conkey::Lexer::TokenType::INT, "99"},
        {Conkey::Lexer::TokenType::IDENT, "xyz"},
        {Conkey::Lexer::TokenType::INT, "123"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(MINIMAL_TOKEN_TEXT_C);
    Conkey::Lexer::Lexer lexer(input, "minimal_token_text_c");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* PROGRAM_A = R"(
    let x = 10;
    let y = 20;
    let z = x + y * 3;
)";

TEST(LexerTest, BasicDeclarationAndArithmetic) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "y"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "20"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "z"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::IDENT, "y"},
        {Conkey::Lexer::TokenType::ASTERISK, "*"},
        {Conkey::Lexer::TokenType::INT, "3"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(PROGRAM_A);
    Conkey::Lexer::Lexer lexer(input, "program_a");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* PROGRAM_B = R"(
    fn max(a, b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    }
)";

TEST(LexerTest, FunctionDefinitionAndControlFlow) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::FUNCTION, "fn"},
        {Conkey::Lexer::TokenType::IDENT, "max"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::IDENT, "b"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::IF, "if"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::GT, ">"},
        {Conkey::Lexer::TokenType::IDENT, "b"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::RETURN, "return"},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::ELSE, "else"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::RETURN, "return"},
        {Conkey::Lexer::TokenType::IDENT, "b"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::RBRACE, "}"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(PROGRAM_B);
    Conkey::Lexer::Lexer lexer(input, "program_b");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* PROGRAM_C = R"(
    let isGreater = 5 < 10;
    let isEqual = (x == y);
    let result = true != false;
)";

TEST(LexerTest, BooleanExpressionsAndComparisons) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "isGreater"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "5"},
        {Conkey::Lexer::TokenType::LT, "<"},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},

        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "isEqual"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::EQ, "=="},
        {Conkey::Lexer::TokenType::IDENT, "y"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},

        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "result"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::TRUE, "true"},
        {Conkey::Lexer::TokenType::NOT_EQ, "!="},
        {Conkey::Lexer::TokenType::FALSE, "false"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(PROGRAM_C);
    Conkey::Lexer::Lexer lexer(input, "program_c");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* PROGRAM_D = R"(
    let a = 5 * (3 + 2);
    let b = fnCall(a, 10);
    let c = if (b != 0) { -a } else { a };
)";

TEST(LexerTest, MixedOperationsAndFunctionCalls) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "5"},
        {Conkey::Lexer::TokenType::ASTERISK, "*"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::INT, "3"},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::INT, "2"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},

        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "b"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::IDENT, "fnCall"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},

        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "c"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::IF, "if"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "b"},
        {Conkey::Lexer::TokenType::NOT_EQ, "!="},
        {Conkey::Lexer::TokenType::INT, "0"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::MINUS, "-"},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::ELSE, "else"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::IDENT, "a"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},

    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(PROGRAM_D);
    Conkey::Lexer::Lexer lexer(input, "program_d");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* INVALID_PROGRAM_A = R"(
    let @x = 10;
)";

TEST(LexerTest, InvalidProgramTestA) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::ILLEGAL, "@"},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(INVALID_PROGRAM_A);
    Conkey::Lexer::Lexer lexer(input, "invalid_program_a");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* INVALID_PROGRAM_B = R"(
    let identifier = 800 % 56;
)";

TEST(LexerTest, InvalidProgramTestB) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "identifier"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "800"},
        {Conkey::Lexer::TokenType::ILLEGAL, "%"},
        {Conkey::Lexer::TokenType::INT, "56"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"}
    };

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(INVALID_PROGRAM_B);
    Conkey::Lexer::Lexer lexer(input, "invalid_program_b");

    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}

const char* WHITESPACES = R"(







                                    )";

TEST(LexerTest, OnlyWhitespaceTest) {
    std::istringstream input(WHITESPACES);
    Conkey::Lexer::Lexer lexer(input, "whitespaces");
    EXPECT_EQ(lexer.tryNextToken().type, Conkey::Lexer::TokenType::END_OF_FILE);
    EXPECT_TRUE(lexer.noMoreTokens());
}

TEST(LexerTest, RandomFormattingTest) {
    std::vector<Conkey::Lexer::Token> expectedTokens = {
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "five"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "5"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "ten"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "add"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::IDENT, "y"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::LBRACE, "{"},
        {Conkey::Lexer::TokenType::RETURN, "return"},
        {Conkey::Lexer::TokenType::IDENT, "x"},
        {Conkey::Lexer::TokenType::PLUS, "+"},
        {Conkey::Lexer::TokenType::IDENT, "y"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::RBRACE, "}"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "result"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::IDENT, "add"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::INT, "5"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::INT, "10"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
        {Conkey::Lexer::TokenType::LET, "let"},
        {Conkey::Lexer::TokenType::IDENT, "result"},
        {Conkey::Lexer::TokenType::ASSIGN, "="},
        {Conkey::Lexer::TokenType::IDENT, "add"},
        {Conkey::Lexer::TokenType::LPAREN, "("},
        {Conkey::Lexer::TokenType::IDENT, "five"},
        {Conkey::Lexer::TokenType::COMMA, ","},
        {Conkey::Lexer::TokenType::IDENT, "ten"},
        {Conkey::Lexer::TokenType::RPAREN, ")"},
        {Conkey::Lexer::TokenType::SEMICOLON, ";"},
    };

    std::array<char, 3> whitespaces = {' ', '\t', '\n'};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> amountDist(1, 5);
    std::uniform_int_distribution<> typeDist(0, whitespaces.size() - 1);

    std::stringstream ss;
    for (const auto& token : expectedTokens) {
        int amount = amountDist(gen);
        char whitespace = whitespaces[typeDist(gen)];

        ss << std::string(amount, whitespace) << token.literal;
    }

    std::vector<Conkey::Lexer::Token> receivedTokens;
    std::istringstream input(ss.str());
    Conkey::Lexer::Lexer lexer(input, "random_format_program");
    while (!lexer.noMoreTokens()) {
        receivedTokens.push_back(lexer.tryNextToken());
    }
    if (receivedTokens.back().type == Conkey::Lexer::TokenType::END_OF_FILE) {
        receivedTokens.resize(receivedTokens.size() - 1);
    }

    ASSERT_THAT(receivedTokens, expectedTokens);
}
