#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
  public:
    Add(ASTNode *lhs, ASTNode *rhs):
        ASTNode("+", lhs, rhs) {}
};

class Sub : public ASTNode {
  public:
    Sub(ASTNode *lhs, ASTNode *rhs):
        ASTNode("-", lhs, rhs) {}
};

class Mul : public ASTNode {
  public:
    Mul(ASTNode *lhs, ASTNode *rhs):
        ASTNode("*", lhs, rhs) {}
};

class Div : public ASTNode {
  public:
    Div(ASTNode *lhs, ASTNode *rhs):
        ASTNode("/", lhs, rhs) {}
};
