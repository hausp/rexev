/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "UNode.hpp"

UNode::UNode() : Node('|') { }

std::set<DeSimoneTree::Node*> UNode::down_action() {
    auto lefty = left->down_action();
    auto righty = right->down_action();
    for (auto node : righty) {
        lefty.insert(node);
    }
    return lefty;
}

std::set<DeSimoneTree::Node*> UNode::up_action() {
    auto temp = right.get();
    while (temp->right_child()) temp = temp->right_child();
    return temp->get_link()->up_action();
}