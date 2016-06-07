/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Node.hpp"
#include "LNode.hpp"

DeSimoneTree::Node::Node(char c) : symbol(c) { }

char DeSimoneTree::Node::get_symbol() {
    return symbol;
}

bool DeSimoneTree::Node::is_leaf() {
    return false;
}

DeSimoneTree::Node* DeSimoneTree::Node::link_node() {
    if (left) {
        auto temp = left->link_node();
        temp->th_link = node_ptr(this);
    }

    if (right) {
        return right->link_node();
    } else {
        return this;
    }
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree::Node& node) {
    if (node.left) out << *node.left;
    out << " " << node.symbol;
    if (node.th_link) {
        out << "(" << node.th_link->symbol << ")";
    }
    if (node.right) out << *node.right;

    //if (node.father) out << " Debug: " << node.father->symbol;
    return out;
}