/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef C_NODE_HPP
#define C_NODE_HPP

#include "Node.hpp"

class CNode : public DeSimoneTree::Node {
 public:
    CNode();
    void down_action();
    void up_action();
};

#endif /* C_NODE_HPP */