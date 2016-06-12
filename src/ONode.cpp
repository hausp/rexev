/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "ONode.hpp"

ONode::ONode() : Node('?') { }

void ONode::down_action() {
	father->up_action();
	left->down_action();
}

void ONode::up_action() {
	th_link->up_action();
}