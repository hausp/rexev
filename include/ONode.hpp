/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef O_NODE_HPP
#define O_NODE_HPP

#include "DSNode.hpp"

class ONode : public DSNode {
 public:
 	ONode();
 	void down_action();
 	void up_action();
 private:

};

#endif /* O_NODE_HPP */