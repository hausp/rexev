/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DE_SIMONE_TREE_HPP
#define DE_SIMONE_TREE_HPP

#include <memory>
#include <regex>
#include <string>
#include <ostream>

class FSMachine;
class DSNode;

using string = std::string;
using node_ptr = std::shared_ptr<DSNode>;

class DeSimoneTree {
    friend std::ostream& operator<<(std::ostream&, const DeSimoneTree&);
 public:
    DeSimoneTree(string);
    FSMachine to_fsm();

 private:
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
