#include "calculator.h"
#include "node.h"
#include <iostream>

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
      if (node == nullptr) break;
      std::cout << calc.Visit(node) << std::endl;
    }
  }
}