// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
    // TODO
    // Implement the next classes:
    // Add
    // Sub
    // Mul
    // Div
    // Variable

    // Without implementation that classes this application works only with numbers

    Lexer lexer(std::cin);
    Parser parser(lexer);

    ASTNode *ast = parser.parse();
    bool problem = parser.is_problem();
    if (problem) {
        return 1;
    }
    if (ast) {
        ast->print(std::cout);
    }

    return 0;
}
