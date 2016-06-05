/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DS_NODE_HPP
#define DS_NODE_HPP

#include "DeSimoneTree.hpp"

class DSNode {
    friend class DeSimoneTree;
    friend std::ostream& operator<<(std::ostream&, const DSNode&);
 public:
    virtual void down_action() = 0;
    virtual void up_action() = 0;
    char get_symbol();

 protected:
    DSNode(char);

 private:
    char symbol;
    node_ptr father;
    node_ptr left;
    node_ptr right;
    node_ptr th_link;
};

inline char DSNode::get_symbol() {
    return symbol;
}

inline DSNode::DSNode(char c) : symbol(c) { }

inline std::ostream& operator<<(std::ostream& out, const DSNode& node) {
    if (node.left) out << *node.left;
    out << " " << node.symbol;
    if (node.right) out << *node.right;

    //if (node.father) out << " Debug: " << node.father->symbol;
    return out;
}

#endif /* DS_NODE_HPP */
