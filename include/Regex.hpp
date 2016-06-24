/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef REGEX_HPP
#define REGEX_HPP

#include "DeSimoneTree.hpp"
#include "Automaton.hpp"

class Regex {
 public:
    Regex();
    Regex(const std::string&, const std::string& = "");

    std::string get_alias() const;
    std::string get_regex() const;
    Automaton to_automaton();
    operator std::string();

 private:
    std::string regex;
    std::string alias;
    DeSimoneTree tree;
};

#endif /* REGEX_HPP */
