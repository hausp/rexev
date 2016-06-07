/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef S_NODE_HPP
#define S_NODE_HPP

#include "Node.hpp"

class SNode : public DeSimoneTree::Node {
 public:
    SNode();
    void down_action();
    void up_action();
};

#endif /* S_NODE_HPP */