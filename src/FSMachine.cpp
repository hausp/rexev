/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "FSMachine.hpp"
#include <iostream>

FSMachine::FSMachine() { }

FSMachine::FSMachine(const std::set<char>& alphabet) : alphabet(alphabet) {

}

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

State& FSMachine::operator[](const std::string& entry) {
    return states.at(entry);
}

const State& FSMachine::operator[](const std::string& entry) const {
    return states.at(entry);
}

void FSMachine::remove_dead_states() {
    unsigned i = 0;
    auto state = states.begin();
    while (i < states.size()) {
        if (state->second.is_dead()) {
            states.erase(state);
            state = states.begin();
        } else {
            i++;
            state++;
        }
    }
}

void FSMachine::remove_unreachable_states() {
    auto state = states[initial_state];
}

FSMachine::operator std::string() const {
    std::string out = "      ";
    for (auto entry : alphabet) {
        out += "| ";
        out += entry;
        out += " ";
    }
    out += "\n";
    for (auto s : states) {
        out += " ";
        if (s.second.is_final()) out += "*";
        else out += " ";
        if (s.second.is_initial()) out += "->";
        else out += "  ";
        out += s.second.get_label();
        out += " ";
        for (auto entry : alphabet) {
            bool test = true;
            out += "| ";
            for (auto t : s.second[entry]) {
                test = false;
                out += t->get_label();
            }
            if (test) out += " ";
            out += " ";
        }
        out += "\n";
    }
    return out;
}