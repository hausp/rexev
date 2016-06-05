/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DE_SIMONE_TREE_HPP
#define DE_SIMONE_TREE_HPP

#include <memory>
#include <string>

#include "DSNode.hpp"
#include "FSMachine.hpp"

using string = std::string;

class DeSimoneTree {
 public:
    DeSimoneTree(const string&);
    FSMachine to_fsm();

 private:
    std::shared_ptr<DSNode> root;

};

#endif /* DE_SIMONE_TREE_HPP */
