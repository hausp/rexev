/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef L_NODE_HPP
#define L_NODE_HPP

#include "Node.hpp"

class LNode : public DeSimoneTree::Node {
 public:
    LNode();
    std::set<Node*> down_action();
    std::set<Node*> up_action();
    bool is_leaf() override;
};

#endif /* L_NODE_HPP */