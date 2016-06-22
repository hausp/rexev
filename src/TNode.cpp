/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "TNode.hpp"

TNode::TNode(char c) : Node(c) { }

std::set<DeSimoneTree::Node*> TNode::up_action() {
    return th_link->up_action();
}

std::set<DeSimoneTree::Node*> TNode::down_action() {
    return {this};
}
