/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DS_NODE_HPP
#define DS_NODE_HPP

#include "DeSimoneTree.hpp"

class DSNode {
    friend class DeSimoneTree;
 public:
    virtual void down_action() = 0;
    virtual void up_action() = 0;
    char get_symbol();

 private:
    char symbol;
    node_ptr left;
    node_ptr right;
    node_ptr th_link;
};

inline char DSNode::get_symbol() {
    return symbol;
}

#endif /* DS_NODE_HPP */
