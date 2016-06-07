/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "LNode.hpp"

LNode::LNode() : Node('~') { }

void LNode::down_action() {

}

void LNode::up_action() {
    
}

bool LNode::is_leaf() {
    return true;
}