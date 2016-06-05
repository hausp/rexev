/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>

#include "DeSimoneTree.hpp"

int main(int argc, char** argv) {
    DeSimoneTree tree("a.c|((b|a)|(b.c)*.d)");
    std::cout << tree << std::endl;
}