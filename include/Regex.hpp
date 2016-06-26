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
    unsigned get_automaton_key() const;
    void set_automaton_key(unsigned);
    Automaton to_automaton();
    operator std::string();

 private:
    std::string regex;
    std::string alias;
    DeSimoneTree tree;
    unsigned automaton_key;
};

#endif /* REGEX_HPP */
