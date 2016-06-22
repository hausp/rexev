/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef REGEX_HPP
#define REGEX_HPP

#include "DeSimoneTree.hpp"
#include "FSMachine.hpp"

class Regex {
 public:
    Regex();
    Regex(const string&);

    FSMachine& get_automaton();
    std::string get_regex();
    operator std::string();

 private:
    std::string regex;
    FSMachine automaton;
};

#endif /* REGEX_HPP */
