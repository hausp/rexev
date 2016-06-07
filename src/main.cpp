/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>

#include "DeSimoneTree.hpp"
#include "LNode.hpp"

int main(int argc, char** argv) {
    DeSimoneTree tree("b*(ab*ab*)*ab*");
    std::cout << tree << std::endl;
}
