/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "CNode.hpp"

CNode::CNode() : Node('.') { }

void CNode::down_action() {
	get_left()->down_action();
}

void CNode::up_action() {
    get_right()->down_action();
}