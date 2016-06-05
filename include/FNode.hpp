/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef F_NODE_HPP
#define F_NODE_HPP

#include "DSNode.hpp"

class FNode : public DSNode {
 public:
    FNode();
    void down_action();
    void up_action();
};

#endif /* F_NODE_HPP */