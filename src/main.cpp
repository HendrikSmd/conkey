#include <iostream>
#include <string>
#include <sstream>

#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/parser.hpp"
#include "conkey/parser/ast/program.hpp"

const std::string PROMPT = ">>";

int main() {
    std::string line;

    std::cout << PROMPT;
    while(std::getline(std::cin, line)) {
        std::istringstream input(line);
        Conkey::Lexer::Lexer lexer(input, "cin");
        Conkey::Parser::Parser parser(lexer);

        std::stringstream ss;
        Conkey::Parser::ProgramPtr programPtr = parser.parseProgram();
        programPtr->toString(ss, 0);
        std::cout << ss.str() << "\n"  <<PROMPT;
    }
}
