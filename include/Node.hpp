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
    node_ptr get_left();
    node_ptr get_right();
    node_ptr get_father();
    node_ptr get_link();
    char get_symbol();
    operator string() const;

 protected:
    Node(char);
    Node* link_node();

 private:
    char symbol;
    unsigned height;
    node_ptr father;
    node_ptr left;
    node_ptr right;
    node_ptr th_link;
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree::Node&);

#endif /* NODE_HPP */
