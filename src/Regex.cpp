/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Regex.hpp"

Regex::Regex() { }

Regex::Regex(const string& r)
: regex(r) {
    try {
        automaton = DeSimoneTree(r).to_fsm();
    } catch (unsigned& e) {
        throw std::runtime_error("Expressão regular inválida:\n verifique o caractere "
                                 + std::to_string(e));
    }
}

FSMachine& Regex::get_automaton() {
    return automaton;
}

std::string Regex::get_regex() {
    return regex;
}

Regex::operator std::string() {
    return (std::string)automaton;
}
