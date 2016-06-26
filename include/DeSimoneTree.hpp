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

#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "types.hpp"

class Automaton;

class DeSimoneTree {
 public:
    class Node;

    DeSimoneTree();
    DeSimoneTree(std::string);
    Automaton to_automaton();
    operator std::string() const;

 private:
    std::set<char> alphabet;
    std::set<char> valid_entries;
    std::unique_ptr<Node> lambda;
    std::unique_ptr<Node> root;

    Node* init_tree(std::string);
    void put_leaf(Node*&, const char);
    void put_union(Node*&);
    void put_concatenation(Node*&);
    void put_kleene_star(Node*&);
    void put_transitive_closure(Node*&);
    void put_option(Node*&);
    unsigned put_subtree(Node*&, std::string&, unsigned);
    void reasign_father(Node*&, Node*&);
    void put_node(Node*&, Node*&);
    bool is_terminal(char);
    bool has_lambda(const std::set<Node*>&);
    std::string new_label(unsigned);
    int search_composition(const std::vector<std::set<Node*>>&,
                           const std::set<Node*>&);
    std::set<Node*> get_composition(const std::set<Node*>&);
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree&);

class DeSimoneTree::Node {    
    friend class DeSimoneTree;
 public:
    char get_symbol() const;

    Node* left_child();
    Node* right_child();
    Node* get_link();
    
    virtual std::set<Node*> down_action() = 0;
    virtual std::set<Node*> up_action() = 0;
    
    operator std::string() const;

 protected:
    Node(char);
    Node* link_node();

    Node* father;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* th_link;
    char symbol;
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree::Node&);

#endif /* DE_SIMONE_TREE_HPP */
