/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef C_NODE_HPP
#define C_NODE_HPP

#include "DSNode.hpp"

class CNode : public DSNode {
 public:
    CNode();
    void down_action();
    void up_action();
};

#endif /* C_NODE_HPP */