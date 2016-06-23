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
    std::map<std::string, State> reachable_states;
    reachable_states.at(initial_state) = states.at(initial_state);
    for (auto st : reachable_states) {
        for (auto t : alphabet) {
            for (auto s : st.second[t]) reachable_states.at(s->get_label()) = *s;
        }
    }
    states = reachable_states;
}

FSMachine FSMachine::complement() {
    std::set<std::string> non_final_states; 
    for (auto st : states) {
        non_final_states.insert(st.first);
    }
    for (auto f : non_final_states) {
        if (final_states.count(f)) non_final_states.erase(non_final_states.find(f));
    }
    FSMachine complemented = *this;
    complemented.final_states = non_final_states;
    return complemented;
}

FSMachine FSMachine::union_operation(const FSMachine& fsm) {
    std::set<char> united_alphabet;
    for (auto c : alphabet) {
        united_alphabet.insert(c);
    }
    for (auto c : fsm.alphabet) {
        united_alphabet.insert(c);
    }
    FSMachine united_machine (united_machine);
    
    bool initial_is_final = false;
    if (final_states.count(initial_state) && fsm.final_states.count(fsm.initial_state)) {
        initial_is_final = true;
    }
    
    std::string initial_label = initial_state+"\'"+"\'";
    State initial (initial_label, nullptr, true, initial_is_final);
    for (auto st : states) {
        united_machine[st.first] = st.second;
    }
    for (auto st : fsm.states) {
        st.second.set_label(st.first+"\'");
        united_machine[st.first+"\'"] = st.second;
    }
    united_machine[initial_label] = initial;
    united_machine.initial_state = initial_label;

    for (auto c : united_machine.alphabet) {
        if (!united_machine[initial_state][c].empty()) {
            for (auto t : united_machine[initial_state][c]) {
                united_machine.make_transition(initial_label, c, t->get_label());
            }
        }
        if (!united_machine[initial_state+"\'"][c].empty()) {
            for (auto t : united_machine[initial_state+"\'"][c]) {
                united_machine.make_transition(initial_label, c, t->get_label());
            }
        }
    }

    return united_machine;
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