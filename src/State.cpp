/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"

#include <ostream>

//-------------------------- State implementation ---------------------------//

Automaton::State::State(bool initial, bool final) : initial(initial), final(final) { }

bool Automaton::State::is_initial() const {
    return initial;
}

bool Automaton::State::is_final() const {
    return final;
}

bool Automaton::State::accepts(const char entry) const {
    return transitions.count(entry);
}

void Automaton::State::append_transition(const char entry, const std::string& target) {
    transitions[entry].push_back(target);
}

std::map<char,std::vector<std::string>>::iterator Automaton::State::begin() {
    return transitions.begin();
}

std::map<char,std::vector<std::string>>::iterator Automaton::State::end() {
    return transitions.end();
}

std::map<char,std::vector<std::string>>::const_iterator Automaton::State::begin() const {
    return transitions.cbegin();
}

std::map<char,std::vector<std::string>>::const_iterator Automaton::State::end() const {
    return transitions.cend();
}

std::vector<std::string>& Automaton::State::operator[](const char entry) {
    return transitions[entry];
}

const std::vector<std::string>& Automaton::State::operator[](const char entry) const {
    return transitions.at(entry);
}

Automaton::State::operator std::string() const {
    return label;
}
