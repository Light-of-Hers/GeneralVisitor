#include <iostream>
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

extern int yyparse(Node **);
extern int yylineno;

extern void yyerror(Node **, const char *msg) {
  std::cerr << "error: " << yylineno << ": " << msg << std::endl;
//  exit(1);
}

int main() {
  Calculator calc;
  while (true) {
    Node *node;
    if (yyparse(&node) == 0) {
      if (node == nullptr)
        break;
      std::cout << calc.Visit(node) << std::endl;
    }
  }
}