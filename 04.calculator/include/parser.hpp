#pragma once

#include <istream>

#include "astnode.hpp"
#include "lexer.hpp"

class Parser {
  public:
    explicit Parser(Lexer &lexer)
        : lexer_(lexer) {}

    Parser(const Parser &other) = delete;

    Parser &operator=(const Parser &other) = delete;

    ~Parser() = default;

    ASTNode *parse();

    bool is_problem() { return problem; }

  private:
    void next_token();

    ASTNode *expr();

    ASTNode *term();

    ASTNode *prim();

    // ASTNode *brace();

    bool problem = false;
    Lexer &lexer_;
    Lexer::Token tok_ = Lexer::Token::None;
    Lexer::Token prev_tok_ = Lexer::Token::Number;
};
