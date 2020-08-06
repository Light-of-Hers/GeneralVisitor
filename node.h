//
// Created by herlight on 2020/8/3.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include "./general_visitor.h"


class Node {
public:
  virtual ~Node() = default;
};

#define OP_NODE_DECLS ND(AddNode) ND(SubNode) ND(MulNode) ND(DivNode)
#define NODE_DECLS ND(NumNode) OP_NODE_DECLS

#define ND(name) \
class name : public Node { \
public:              \
  name(Node *l, Node *r) : lhs(l), rhs(r) {} \
  Node *lhs, *rhs;   \
};

OP_NODE_DECLS

#undef ND

class NumNode : public Node {
public:
  explicit NumNode(int n) : val(n) {}
  int val;
};

template<typename F>
class NodeVisitor;

template<typename R, typename ...Args>
class NodeVisitor<R(Args...)> : public GeneralVisitor<NodeVisitor<R(Args...)>, Node, R(Args...)> {
public:
  NodeVisitor() {
    this->template Register<AddNode, SubNode, MulNode, DivNode, NumNode>();
  }

#define ND(name) virtual R ImplVisit(name *, Args ...) { throw std::runtime_error("not implemented"); }
  NODE_DECLS
#undef ND
};

#undef NODE_DECLS
#undef OP_NODE_DECLS


#endif //UNTITLED_NODE_H
