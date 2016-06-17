/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef U_NODE_HPP
#define U_NODE_HPP

#include "Node.hpp"

class UNode : public DeSimoneTree::Node {
 public:
using node_ptr = std::shared_ptr<Node>;
    UNode();
    void down_action();
    void up_action();
};

#endif /* U_NODE_HPP */
