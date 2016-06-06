/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "DSNode.hpp"
#include "LNode.hpp"

DSNode::DSNode(char c) : symbol(c) { }

char DSNode::get_symbol() {
    return symbol;
}

bool DSNode::is_leaf() {
    return false;
}

std::ostream& operator<<(std::ostream& out, const DSNode& node) {
    if (node.left) out << *node.left;
    out << " " << node.symbol;
    if (node.right) out << *node.right;

    //if (node.father) out << " Debug: " << node.father->symbol;
    return out;
}