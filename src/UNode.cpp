/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "UNode.hpp"
#include "DeSimoneTree.hpp"

UNode::UNode() : Node('|') { }

void UNode::down_action() {
	get_left()->down_action();
	get_right()->down_action();
}

void UNode::up_action() {
    node_ptr tmp = get_right();
    while(tmp->get_right()) tmp = tmp->get_right();
    tmp->up_action();
}
