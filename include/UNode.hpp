/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef U_NODE_HPP
#define U_NODE_HPP

#include "Node.hpp"

class UNode : public DeSimoneTree::Node {
 public:
    UNode();
    std::set<Node*> down_action();
    std::set<Node*> up_action();
};

#endif /* U_NODE_HPP */
