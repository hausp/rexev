/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Node.hpp"
#include "LNode.hpp"

DeSimoneTree::Node::Node(char c)
: father(nullptr), th_link(nullptr), symbol(c) {
}

char DeSimoneTree::Node::get_symbol() const {
    return symbol;
}

DeSimoneTree::Node* DeSimoneTree::Node::left_child() {
    return left.get();
}

DeSimoneTree::Node* DeSimoneTree::Node::right_child() {
    return right.get();
}


DeSimoneTree::Node* DeSimoneTree::Node::link_node() {
    if (left) {
        auto temp = left->link_node();
        temp->th_link = this;
    }

    if (right) {
        return right->link_node();
    }
    return this;
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