#include <iostream>
#include <string>
#include <sstream>

#include "conkey/lexer/lexer.hpp"

const std::string PROMPT = ">>";

int main() {
    std::string line;

    std::cout << PROMPT;
    while(std::getline(std::cin, line)) {
        std::istringstream input(line);
        Conkey::Lexer::Lexer lexer(input, "cin");
        while (!lexer.noMoreTokens()) {
            std::cout << lexer.tryNextToken() << std::endl;
        }
        std::cout << PROMPT;
    }
}
