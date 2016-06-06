/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef T_NODE_HPP
#define T_NODE_HPP

#include "DSNode.hpp"

class TNode : public DSNode {
 public:
    TNode(char);
    void down_action();
    void up_action();    

 private:

};


#endif /* T_NODE_HPP */
