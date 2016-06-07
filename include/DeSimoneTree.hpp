/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * De Simone Tree class definition:
 *  This is a data structure used to store a Regular Expression
 *  as a tree, read from left to right, the terminal terms and
 *  the regex operators form the tree, terminals are leaves and
 *  non-terminal are used to make the path through tree.
 *
 **/
#ifndef DE_SIMONE_TREE_HPP
#define DE_SIMONE_TREE_HPP

#include <memory>
#include <string>
#include <ostream>

class FSMachine;

using std::string;

class DeSimoneTree {
    friend std::ostream& operator<<(std::ostream&, const DeSimoneTree&);
 public:
    class Node;
    DeSimoneTree(string);
    FSMachine to_fsm();

 private:
    using node_ptr = std::shared_ptr<Node>;
    node_ptr root;
    node_ptr init_tree(string);
    void put_leaf(node_ptr&, const char);
    void put_union(node_ptr&);
    void put_concatenation(node_ptr&);
    void put_kleene_star(node_ptr&);
    void put_option(node_ptr&);
    void put_subtree(node_ptr&, std::string&);
    void reasign_father(node_ptr&, node_ptr&);
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree&);
#endif /* DE_SIMONE_TREE_HPP */
