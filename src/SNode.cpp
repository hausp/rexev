/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "SNode.hpp"

SNode::SNode() : Node('*') { }

std::set<DeSimoneTree::Node*> SNode::down_action() {
    auto cousins = th_link->up_action();
    auto grandsons = left->down_action();
    for (auto node : cousins) {
        grandsons.insert(node);
    }
    return grandsons;
}

std::set<DeSimoneTree::Node*> SNode::up_action() {
    auto cousins = th_link->up_action();
    auto grandsons = left->down_action();
    for (auto node : cousins) {
        grandsons.insert(node);
    }
    return grandsons;
}