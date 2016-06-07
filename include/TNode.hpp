/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef T_NODE_HPP
#define T_NODE_HPP

#include "Node.hpp"

class TNode : public DeSimoneTree::Node {
 public:
    TNode(char);
    void down_action();
    void up_action();
};


#endif /* T_NODE_HPP */
