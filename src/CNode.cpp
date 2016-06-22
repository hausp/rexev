/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "CNode.hpp"

CNode::CNode() : Node('.') { }

std::set<DeSimoneTree::Node*> CNode::down_action() {
    return left->down_action();
}

std::set<DeSimoneTree::Node*> CNode::up_action() {
    return right->down_action();
}