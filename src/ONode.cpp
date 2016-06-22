/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "ONode.hpp"

ONode::ONode() : Node('?') { }

std::set<DeSimoneTree::Node*> ONode::down_action() {
    auto cousins = th_link->up_action();
    auto grandsons = left->down_action();
    for (auto node : cousins) {
        grandsons.insert(node);
    }
    return grandsons;
}

std::set<DeSimoneTree::Node*> ONode::up_action() {
    return th_link->up_action();
}