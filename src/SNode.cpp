/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "SNode.hpp"

SNode::SNode() : Node('*'), guard(false) { }

std::set<DeSimoneTree::Node*> SNode::down_action() {
    std::set<DeSimoneTree::Node*> grandsons;
    if (!guard) {
        guard = true;
        auto cousins = th_link->up_action();
        grandsons = left->down_action();
        for (auto node : cousins) {
            grandsons.insert(node);
        }
        guard = false;
    }
    return grandsons;
}

std::set<DeSimoneTree::Node*> SNode::up_action() {
    std::set<DeSimoneTree::Node*> grandsons;
    if (!guard) {
        guard = true;
        auto cousins = th_link->up_action();
        grandsons = left->down_action();
        for (auto node : cousins) {
            grandsons.insert(node);
        }
        guard = false;
    }
    return grandsons;
}