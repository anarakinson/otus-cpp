// OTUS C++ basic course homework.
// ASTNode

#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode {
  public:
    // Конструктор листа (узел без дочерних узлов)
    explicit ASTNode(const std::string &repr);
    // Конструктор узла (с одним или двумя дочернимиузлами)
    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    ASTNode(const ASTNode &other) = delete;

    ASTNode &operator=(const ASTNode &other) = delete;

    virtual ~ASTNode();
    // Представления имени узла в виде строки
    std::string repr() const { return repr_; }
    // Печать всего дерева в текстовом виде
    void print(std::ostream &out) const;

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};
