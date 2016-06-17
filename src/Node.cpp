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

DeSimoneTree::node_ptr DeSimoneTree::Node::get_link() {
    return th_link;
}

DeSimoneTree::node_ptr DeSimoneTree::Node::get_right() {
    return right;
}

DeSimoneTree::node_ptr DeSimoneTree::Node::get_father() {
    return father;
}

DeSimoneTree::node_ptr DeSimoneTree::Node::get_left() {
    return left;
}

DeSimoneTree::Node::operator string() const {
    string out;
    if (left) out += *left;
    out += " ";
    out += symbol;
    if (th_link) {
        out += "(";
        out += th_link->symbol;
        out += ")";
    }
    if (right) out += *right;
    return out;
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree::Node& node) {
    return out << (string)node;
}
