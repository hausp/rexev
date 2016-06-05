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
    void reasign_father(node_ptr&, node_ptr&);
};

std::ostream& operator<<(std::ostream&, const DeSimoneTree&);
#endif /* DE_SIMONE_TREE_HPP */
