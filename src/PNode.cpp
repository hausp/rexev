/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "PNode.hpp"

PNode::PNode() : Node('+') { }

std::set<DeSimoneTree::Node*> PNode::down_action() {
    return left->down_action();
}

std::set<DeSimoneTree::Node*> PNode::up_action() {
    auto cousins = th_link->up_action();
    auto grandsons = left->down_action();
    for (auto node : cousins) {
        grandsons.insert(node);
    }
    return grandsons;
}