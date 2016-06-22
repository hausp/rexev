/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "FSMachine.hpp"
#include <iostream>

FSMachine::FSMachine() { }

// FSMachine::FSMachine(const std::map<char,State>& k, const std::set<char>& sigma, char q0, const std::set<char>& f)
//  : states(k), alphabet(sigma), initial_state(q0), final_states(f) {

// }

void FSMachine::insert(const std::string& entry, bool initial, bool final) {
    states[entry] = State(entry, &rejection_state, initial, final);
    if (initial) initial_state = entry;
    if (final) final_states.insert(entry);
}

void FSMachine::make_transition(const std::string& from, char label,
                                const std::string& to) {
    if (!states.count(from)) {
        insert(from);
    }
    if (!states.count(to)) {
        insert(to);
    }
    states.at(from).add_transition(label, {&states.at(to)});
}

State FSMachine::operator[](const std::string& entry) {
    return states.at(entry);
}

const State FSMachine::operator[](const std::string& entry) const {
    return states.at(entry);
}
