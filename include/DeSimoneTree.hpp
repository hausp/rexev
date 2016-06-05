/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DS_NODE_HPP
#define DS_NODE_HPP

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

#endif /* DS_NODE_HPP */