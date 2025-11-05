#include <iostream>
#include <string>
#include <sstream>

#include "conkey/interpret/interpretor.hpp"
#include "conkey/lexer/lexer.hpp"
#include "conkey/parser/parser.hpp"

using namespace Conkey::Lexer;
using namespace Conkey::Parser;
using namespace Conkey::Interpret;


const std::string PROMPT = ">>";

int main() {
    std::string line;
    Interpretor interpretor;

    std::cout << PROMPT;
    while(std::getline(std::cin, line)) {
        std::istringstream input(line);
        Lexer lexer(input, "cin");
        Parser parser(lexer);

        std::stringstream ss;
        try {
            ProgramPtr programPtr = parser.parseProgram();
            auto value = programPtr->accept(interpretor);
            std::cout << value->inspect() << std::endl;
        } catch (const ParseError& exc) {
            std::cout << exc.what() << std::endl;
        }
        std::cout << ss.str() << "\n"  <<PROMPT;
    }
}
