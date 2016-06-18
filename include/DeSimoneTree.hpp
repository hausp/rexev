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
#include <unordered_set>
#include <iostream>

#define RECENT_COMPILER 0
#define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl
#define TRACE_L(x,y) std::cout << (x) << " = " << (y) << std::endl
#define ECHO(x) std::cout << (x) << std::endl

class FSMachine;

using std::string;

class DeSimoneTree {
 public:
    class Node;

    DeSimoneTree();
    DeSimoneTree(string);
    FSMachine to_fsm();
    operator string() const;

 private:
    std::unordered_set<char> alphabet;
    std::unique_ptr<Node> lambda;
    std::unique_ptr<Node> root;

    Node* init_tree(string);
    void put_leaf(Node*&, const char);
    void put_union(Node*&);
    void put_concatenation(Node*&);
    void put_kleene_star(Node*&);
    void put_option(Node*&);
    void put_subtree(Node*&, std::string&);
    void reasign_father(Node*&, Node*&);
    bool is_terminal(char);
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree&);

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

#endif /* DE_SIMONE_TREE_HPP */
