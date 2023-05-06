#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode {
  public:
    Number(int val)
        : ASTNode(std::to_string(val))
        , val_(val) {}

    int value() const { return val_; }

  private:
    int val_;
};

class Variable : public ASTNode {
  public:
    Variable(std::string val)
        : ASTNode(val)
        , val_(val) {}

    std::string value() const { return val_; }

  private:
    std::string val_;
};
