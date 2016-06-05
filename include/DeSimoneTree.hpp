/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DE_SIMONE_TREE_HPP
#define DE_SIMONE_TREE_HPP

#include <memory>
#include <regex>
#include <string>

class FSMachine;
class DSNode;

using string = std::string;
using node_ptr = std::shared_ptr<DSNode>;

class DeSimoneTree {
 public:
    DeSimoneTree(string);
    FSMachine to_fsm();

 private:
    std::shared_ptr<DSNode> root;

    node_ptr init_tree(string);
    void reasign_father(node_ptr, node_ptr);
};

#endif /* DE_SIMONE_TREE_HPP */
