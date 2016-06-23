/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Regex.hpp"

Regex::Regex() { }

Regex::Regex(const string& r)
: regex(r), automaton(DeSimoneTree(r).to_fsm()) { }

FSMachine& Regex::get_automaton() {
    return automaton;
}

std::string Regex::get_regex() {
    return regex;
}

Regex::operator std::string() {
    return (std::string)automaton;
}
