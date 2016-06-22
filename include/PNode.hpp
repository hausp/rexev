/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef P_NODE_HPP
#define P_NODE_HPP

#include "Node.hpp"

class PNode : public DeSimoneTree::Node {
 public:
    PNode();
    std::set<Node*> down_action();
    std::set<Node*> up_action();
};

#endif /* P_NODE_HPP */