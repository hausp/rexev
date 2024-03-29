/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef O_NODE_HPP
#define O_NODE_HPP

#include "Node.hpp"

class ONode : public DeSimoneTree::Node {
 public:
 	ONode();
 	std::set<Node*> down_action();
 	std::set<Node*> up_action();
};

#endif /* O_NODE_HPP */