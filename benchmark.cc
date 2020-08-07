//
// Created by herlight on 2020/8/7.
//

#include "node.h"
#include "calculator.h"
#include <chrono>
#include <iostream>

int Calculate(Node *node) {
  if (auto nd = dynamic_cast<AddNode *>(node)) {
    return Calculate(nd->lhs) + Calculate(nd->rhs);
  } else if (auto nd = dynamic_cast<SubNode *>(node)) {
    return Calculate(nd->lhs) - Calculate(nd->rhs);
  } else if (auto nd = dynamic_cast<MulNode *>(node)) {
    return Calculate(nd->lhs) * Calculate(nd->rhs);
  } else if (auto nd = dynamic_cast<DivNode *>(node)) {
    return Calculate(nd->lhs) / Calculate(nd->rhs);
  } else if (auto nd = dynamic_cast<NumNode *>(node)) {
    return nd->val;
  }
  throw std::runtime_error("fuck");
}

int main() {
  Node *node = new NumNode(1);
  for (int i = 0; i < 18; ++i) {
    node = new AddNode(node, node);
  }
  {
    int res = Calculate(node);
    std::cout << res << std::endl;
    auto beg = std::chrono::high_resolution_clock::now();
    res = Calculate(node);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << res << std::endl;
    std::cout << std::chrono::duration<double>(end - beg).count() << " s" << std::endl;
  }
  {
    Calculator calc;
    int res = calc.Visit(node);
    std::cout << res << std::endl;
    auto beg = std::chrono::high_resolution_clock::now();
    res = calc.Visit(node);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << res << std::endl;
    std::cout << std::chrono::duration<double>(end - beg).count() << " s" << std::endl;
  }
}