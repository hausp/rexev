/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * Node class definition:
 *  This is the structure used to store information
 *  from each node of the De Simone Tree data structure.
 *  More info in: *Node.hpp files
 *  
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "DeSimoneTree.hpp"

class DeSimoneTree::Node {    
    friend class DeSimoneTree;
 public:
    virtual void down_action() = 0;
    virtual void up_action() = 0;
    virtual bool is_leaf();
    char get_symbol();
    operator string() const;
    ~Node() { ECHO("Node destroyed"); }
 protected:
    Node(char);
    Node* link_node();

 private:
    char symbol;
    Node* father;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* th_link;
    unsigned height;
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree::Node&);

#endif /* NODE_HPP */
