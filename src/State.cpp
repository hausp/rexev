/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"

#include <ostream>

//-------------------------- State implementation ---------------------------//

Automaton::State::State() { }

bool Automaton::State::accepts(const Entry e) const {
    return transitions.count(e) && transitions.at(e) != "";
}

bool Automaton::State::accepts_to(const Entry e, const Key& target) const {
    if (transitions.count(e)) {
        if (transitions.at(e) == target) {
            return true;
        }
    }
    return false;
}

void Automaton::State::make_transition(const Entry e, const Key& target) {
    transitions[e] = target;
}

void Automaton::State::remove_transition(const Entry e) {
    transitions.erase(e);
}

std::map<Entry,Key>::iterator Automaton::State::begin() {
    return transitions.begin();
}

std::map<Entry,Key>::iterator Automaton::State::end() {
    return transitions.end();
}

std::map<Entry,Key>::const_iterator Automaton::State::begin() const {
    return transitions.cbegin();
}

std::map<Entry,Key>::const_iterator Automaton::State::end() const {
    return transitions.cend();
}

Key& Automaton::State::operator[](const Entry e) {
    return transitions[e];
}

const Key& Automaton::State::operator[](const Entry e) const {
    return transitions.at(e);
}
