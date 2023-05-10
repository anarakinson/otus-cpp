#pragma once

#include <string>
#include <iostream>

#include "astnode.hpp"


class Mul : public ASTNode {
  public:
    Mul(ASTNode *lhs, ASTNode *rhs):
        ASTNode("*", lhs, rhs) {
          if (lhs == nullptr || rhs == nullptr) {
            std::cout << "error: incorrect input" << std::endl;
          }
        }
};

class Div : public ASTNode {
  public:
    Div(ASTNode *lhs, ASTNode *rhs):
        ASTNode("/", lhs, rhs) {
          if (lhs == nullptr || rhs == nullptr) {
            std::cout << "error: incorrect input" << std::endl;
          }
        }
};
