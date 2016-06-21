/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef REGEX_HPP
#define REGEX_HPP

#include "DeSimoneTree.hpp"

class Regex {
 public:
    Regex(const string&);

 private:
    string regex;
    DeSimoneTree regex_tree;
};

#endif /* REGEX_HPP */
