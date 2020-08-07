//
// Created by herlight on 2020/8/7.
//

#ifndef UNTITLED_CALCULATOR_H
#define UNTITLED_CALCULATOR_H

#include "node.h"

#define OP_NODE_DECLS OP(AddNode, +) OP(SubNode, -) OP(DivNode, /) OP(MulNode, *)

class Calculator : public NodeVisitor<int()> {
#define OP(name, op) int ImplVisit(name *node) override { return Visit(node->lhs) op Visit(node->rhs); }
  OP_NODE_DECLS
#undef OP

  int ImplVisit(NumNode *node) override {
    return node->val;
  }
};

#undef OP_NODE_DECLS


#endif //UNTITLED_CALCULATOR_H
