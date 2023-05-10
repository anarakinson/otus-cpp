#pragma once

#include <string>
#include <iostream>

#include "astnode.hpp"


class Lbrace : public ASTNode {
  public:
    Mul(ASTNode *lhs, ASTNode *rhs):
        ASTNode("*", lhs, rhs) {}
};

class Rbrace : public ASTNode {
  public:
    Div(ASTNode *lhs, ASTNode *rhs):
        ASTNode("/", lhs, rhs) {}
};
