/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "SNode.hpp"

SNode::SNode() : Node('*') { }

void SNode::down_action() {
	get_link()->up_action();
	get_left()->down_action();
}

void SNode::up_action() {
	get_link()->up_action();
	get_left()->down_action();    
}