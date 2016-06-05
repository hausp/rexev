/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef S_NODE_HPP
#define S_NODE_HPP

#include "DSNode.hpp"

class SNode : public DSNode {
 public:
    SNode();
    void down_action();
    void up_action();
};

#endif /* S_NODE_HPP */