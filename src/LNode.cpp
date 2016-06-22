/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "LNode.hpp"

LNode::LNode() : Node('~') { }

std::set<DeSimoneTree::Node*> LNode::down_action() {
    return {this};
}

std::set<DeSimoneTree::Node*> LNode::up_action() {
    return {this};
}

bool LNode::is_leaf() {
    return true;
}