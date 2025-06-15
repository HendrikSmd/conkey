#include <iostream>
#include <string>
#include <sstream>

#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/parser.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;

const std::string PROMPT = ">>";

int main() {
    std::string line;

    std::cout << PROMPT;
    while(std::getline(std::cin, line)) {
        std::istringstream input(line);
        Lexer lexer(input, "cin");
        Parser parser(lexer);

        std::stringstream ss;
        try {
            ProgramPtr programPtr = parser.parseProgram();
            programPtr->toString(ss, 0);
        } catch (const ParseError& exc) {
            std::cout << exc.what() << std::endl;
        }
        std::cout << ss.str() << "\n"  <<PROMPT;
    }
}
