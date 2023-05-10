#pragma once

#include <string>
#include <iostream>

#include "astnode.hpp"

class Add : public ASTNode {
  public:
    Add(ASTNode *lhs, ASTNode *rhs):
        ASTNode("+", lhs, rhs) {
          if (lhs == nullptr || rhs == nullptr) {
            std::cout << "error: incorrect input" << std::endl;
          }
        }
};

class Sub : public ASTNode {
  public:
    Sub(ASTNode *lhs, ASTNode *rhs):
        ASTNode("-", lhs, rhs) {
          if (lhs == nullptr || rhs == nullptr) {
            std::cout << "error: incorrect input" << std::endl;
          }
        }
};
