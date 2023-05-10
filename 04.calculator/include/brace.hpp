#pragma once

#include <string>
#include <iostream>

#include "astnode.hpp"


class Lbrace : public ASTNode {
  public:
    Lbrace(std::string val)
        : ASTNode(val)
        , val_(val) {}

    std::string value() const { return val_; }

  private:
    std::string val_;
};

class Rbrace : public ASTNode {
  public:
    Rbrace(std::string val)
        : ASTNode(val)
        , val_(val) {}

    std::string value() const { return val_; }

  private:
    std::string val_;
};