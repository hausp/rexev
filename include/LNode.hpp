/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef L_NODE_HPP
#define L_NODE_HPP

#include "Node.hpp"

class LNode : public DeSimoneTree::Node {
 public:
    LNode();
    void down_action();
    void up_action();
    bool is_leaf() override;
};

#endif /* L_NODE_HPP */