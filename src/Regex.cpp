/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Regex.hpp"

Regex::Regex()
: regex(""), alias("") { }

Regex::Regex(const std::string& regex, const std::string& alias)
: regex(regex), alias(alias) {
    try {
        tree = DeSimoneTree(regex);
    } catch (unsigned e) {
        throw std::runtime_error("Expressão regular inválida:\n verifique o caractere "
                                 + std::to_string(e));
    }
}

Automaton Regex::to_automaton() {
    return tree.to_automaton();
}

std::string Regex::get_alias() const {
    return alias;
}

std::string Regex::get_regex() const {
    return regex;
}

Regex::operator std::string() {
    return regex;
}
